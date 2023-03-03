#include <stdlib.h>
#ifdef _WIN32
#include <process.h>
#else
#include <unistd.h>
extern char ** environ;
#endif
#include "fcgio.h"
#include "fcgi_config.h"  // HAVE_IOSTREAM_WITHASSIGN_STREAMBUF

using namespace std;


//tzy
#include "common.h"
#include "cmd.h"
#include <vector>

namespace tzyNet{

    std::vector<std::string> Common::strSplit(const std::string &str, const std::string &pattern)
    {
        vector<string> res;
        if (str == "")
            return res;

        //在字符串末尾也加入分隔符，方便截取最后一段
        string strs = str + pattern;
        size_t pos = strs.find(pattern);

        while (pos != strs.npos)
        {
            string temp = strs.substr(0, pos);
            res.push_back(temp);
            //去掉已分割的字符串,在剩下的字符串中进行分割
            strs = strs.substr(pos + 1, strs.size());
            pos = strs.find(pattern);
        }

        return res;
    }


    long gstdin(FCGX_Request * request, char ** content)
    {
        char * clenstr = FCGX_GetParam("CONTENT_LENGTH", request->envp);
        unsigned long clen = STDIN_MAX;

        if (clenstr)
        {
            clen = strtol(clenstr, &clenstr, 10);
            if (*clenstr)
            {
                cerr << "can't parse \"CONTENT_LENGTH="
                    << FCGX_GetParam("CONTENT_LENGTH", request->envp)
                    << "\"\n";
                clen = STDIN_MAX;
            }

            // *always* put a cap on the amount of data that will be read
            if (clen > STDIN_MAX) clen = STDIN_MAX;

            *content = new char[clen];

            cin.read(*content, clen);
            clen = cin.gcount();
        }
        else
        {
            // *never* read stdin when CONTENT_LENGTH is missing or unparsable
            *content = 0;
            clen = 0;
        }

        // Chew up any remaining stdin - this shouldn't be necessary
        // but is because mod_fastcgi doesn't handle it correctly.

        // ignore() doesn't set the eof bit in some versions of glibc++
        // so use gcount() instead of eof()...
        do cin.ignore(1024); while (cin.gcount() == 1024);

        return clen;
    }

}
