//tzy
#include "common.h"
#include "cmd.h"
#include "net.h"

int main (void)
{
    int count = 0;
    long pid = getpid();

    std::streambuf * cin_streambuf  = std::cin.rdbuf();
    std::streambuf * cout_streambuf = std::cout.rdbuf();
    std::streambuf * cerr_streambuf = std::cerr.rdbuf();

    FCGX_Request request;

    FCGX_Init();
    FCGX_InitRequest(&request, 0, 0);

    while (FCGX_Accept_r(&request) == 0)
    {
        // Note that the default bufsize (0) will cause the use of iostream
        // methods that require positioning (such as peek(), seek(),
        // unget() and putback()) to fail (in favour of more efficient IO).
        fcgi_streambuf cin_fcgi_streambuf(request.in);
        fcgi_streambuf cout_fcgi_streambuf(request.out);
        fcgi_streambuf cerr_fcgi_streambuf(request.err);


        std::cin.rdbuf(&cin_fcgi_streambuf);
        std::cout.rdbuf(&cout_fcgi_streambuf);
        std::cerr.rdbuf(&cerr_fcgi_streambuf);

        char * clientBuf;
        unsigned long clen = tzyNet::gstdin(&request, &clientBuf);

        std::string strUrl = FCGX_GetParam("REQUEST_URI" ,request.envp);
        std::string reqBuf = clientBuf;
        
        std::cout << "Content-type: text/html\r\n"
                "\r\n"
                "<TITLE>myecho</TITLE>\n";

        //  解析请求
        tzyNet::Url* reqUrl = new tzyNet::Url(strUrl);
        tzyNet::Request* reqData = new tzyNet::Request(reqBuf);

        //  构造实例
        rttr::type t2 = rttr::type::get_by_name(reqData->api);
        rttr::constructor ctor = t2.get_constructor();  
	    rttr::variant var = ctor.invoke();
        
        //  调用方法
	    rttr::method meth = rttr::type::get(var).get_method(reqData->ctrl);
	    meth.invoke(var, reqData->param);

        if (clientBuf){
            delete []clientBuf;
        }

        // If the output streambufs had non-zero bufsizes and
        // were constructed outside of the accept loop (i.e.
        // their destructor won't be called here), they would
        // have to be flushed here.
    }

    std::cin.rdbuf(cin_streambuf);
    std::cout.rdbuf(cout_streambuf);
    std::cerr.rdbuf(cerr_streambuf);

    return 0;
}
