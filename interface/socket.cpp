#include "socket.h"

int Connect::openSocket()
{
    cout<<"Opening socket: "<<portno<<" "<<hostname<<endl;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        cerr<<"ERROR: cannot open socket\n";
        return -1;
    }
    server = gethostbyname(hostname.c_str());
    if (server == NULL) 
    {
        cerr<<"ERROR: hostname not correct\n";
        return -1;
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
    {
        cerr<<"ERROR: problem during connection\n";
        return -1;
    }

    return 0;
}

int Connect::sendMessage(string &message)
{
    int n;
    uint32_t dataLength = htonl(message.size()); // convert int to network byte order. 

    // The message e is divided in two parts:
    // 1) First the length of the message with the serialization
    n = write(sockfd,&dataLength,sizeof(uint32_t));
    cout<<n<<endl;
    if (n < 0) 
        cerr<<"ERROR: sending the message length failed";
    
    // 2) The actual message. n stores the actual length sent.
    n = write(sockfd,message.c_str(),dataLength);
    cout<<n<<endl;
    if (n < 0) 
        cerr<<"ERROR: sending message via socket failed";

    return n;
}
