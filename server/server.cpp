/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

void processing(int);
void error(string msg)
{
    perror(msg.c_str());
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno;
     pid_t pid;
     socklen_t clilen;
     //char buffer[256];
     string buffer; // a vector<char> should be better...
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     if (argc < 2) {
         cerr<<"ERROR, no port provided\n";
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        cerr<<"ERROR opening socket";
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              cerr<<"ERROR on binding";
     listen(sockfd,5);
     clilen = sizeof(cli_addr);

     while (1)
     {
         newsockfd = accept(sockfd, 
                     (struct sockaddr *) &cli_addr, 
                     &clilen);
         if (newsockfd < 0) 
              cerr<<"ERROR on accept";

         signal(SIGCHLD,SIG_IGN); // this is needed to avoid zombies until the parent is dead
         pid = fork();
	 if (pid>0) cout<<"Forking with child PID "<<pid<<endl; // Parent process
 	 if (pid<0)
	    cerr<<"ERROR on fork";
	 if (pid==0)
	 {
	     close(sockfd);
	     processing(newsockfd);
	     exit(0);
	 }
	 else close(newsockfd);
     } /* end of while for server listening */
     close(sockfd);
     return 0; /* never here */
}	    

void processing(int sock)
{
     string buffer;
     char string_tmp[256];
     int n;

     bzero(string_tmp,256);
     n = read(sock,string_tmp,255);
     buffer = string_tmp;
     if (n < 0) cerr<<"ERROR reading from socket";
     cout<<"Here is the message: "<<buffer<<endl;
     n = write(sock,"I got your message",18);
     if (n < 0) cerr<<"ERROR writing to socket";
}
