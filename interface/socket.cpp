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

int Connect::receiveMessage(string &message)
{
    // The message is received in two parts: 1) its lengths 2) the message
    // 1) The length of the message to be received
    uint32_t mLength;
    read(sockfd,&mLength,sizeof(uint32_t)); // Receive the message length
    mLength = ntohl(mLength); // Ensure host system byte order
    int dataLength = static_cast<int>(mLength);
    cout<<"Message of "<<dataLength<<" elements arrived!\n";
	
    // 2) The message itself. It is stored in a char [], however a vector<char> could and should be used.
    vector<uint8_t> msg; // Allocating a buffer of approriate length
    msg.resize(mLength,0x00);

    int n;
    n = read(sockfd,&(msg[0]),mLength); // Receive the string data

    // Convert message data into a string for de-serialization
    message.assign(reinterpret_cast<const char*>(&(msg[0])),msg.size());

    return n;
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
