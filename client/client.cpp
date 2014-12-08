#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

using namespace std;

void error(string msg)
{
    perror(msg.c_str());
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    //char buffer[256];
    string buffer;

    if (argc < 3) {
       cerr<<"usage: "<<argv[0]<<" hostname port\n";
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        cerr<<"ERROR, no such host\n";
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    cout<<"Please enter the message: ";
    //bzero(buffer,256);
    //fgets(buffer,255,stdin);
    getline(cin,buffer);
    n = write(sockfd,buffer.c_str(),buffer.length());
    if (n < 0) 
         error("ERROR writing to socket");
    //bzero(buffer,256);
    buffer.clear();
    char string_tmp[256];
    bzero(string_tmp,256); // need to zeroes the string to avoid junk stuff from read. Why???
    n = read(sockfd,string_tmp,255);
    buffer = string_tmp;
    if (n < 0) 
         error("ERROR reading from socket");
    cout<<buffer.c_str()<<endl;
    close(sockfd);
    return 0;
}
