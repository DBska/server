#ifndef _SOCKET_H_
#define _SOCKET_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <strings.h>
#include <vector>

using namespace std;

class Connect
{
    private:
        int portno;
        int sockfd;
        string hostname;
        struct sockaddr_in serv_addr;
        struct hostent *server;

    public:
        Connect() { portno = 3303; hostname = "localhost"; };
       // Connect() { portno = 5200; hostname = "spock.oats.inaf.it"; };
        ~Connect() { };
        void Close() { close(sockfd); };
        int openSocket();
        int sendMessage(string &);
        int receiveMessage(string &);
};

#endif
