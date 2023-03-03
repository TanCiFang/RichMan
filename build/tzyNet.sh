#!/bin/bash      

HOST='127.0.0.1'
PORT=9000
PROCESS_NUM=5
PUBLIC="/data/server/richMan/build/public/src/"

declare -A CONFIG=(
    ['PROCESS']="index.cgi"
    ['SELF']="tzyNet.sh"
    ['FCGI']="spawn-fcgi"
)


if [ $1 = "-start" ];then
    cmake ..
    make

    sudo killall -9 ${CONFIG["PROCESS"]}
    echo -e "\n=========killed=========\n"
    sudo ./${CONFIG["FCGI"]} -a $HOST -p $PORT -f ${PUBLIC}/${CONFIG["PROCESS"]} -F $PROCESS_NUM

    echo -e "\n==========done==========\n"
    ps -ef | grep ${CONFIG["PROCESS"]}
    echo -e "SUCCESS: [tzyNet] SERVER START!"

elif [ $1 = "-stop" ];then

    sudo killall -9 ${CONFIG["PROCESS"]}
    echo -e "SUCCESS: [tzyNet] SERVER STOP!"

elif [ $1 = "-clean" ];then

    for file in `ls .`; do
        if echo ${CONFIG[@]} | grep -w $file &>/dev/null; then
            continue;
        fi

        rm -rf $file
    done
 
    echo -e "SUCCESS: [tzyNet] THE BUILD DIR IS CLEAN!"

elif [ $1 = "-help" ];then

    echo -e "[tzyNet] A simple server application"
    echo -e "Options:"
    echo -e "   -start  :   server start"
    echo -e "   -stop   :   server stop"
    echo -e "   -clean  :   to make build dir clean\n"

else 
    echo -e "ERROR: The script param is undefind! try to use \"tzyNet.sh -help\" to get help"
fi


