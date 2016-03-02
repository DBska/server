/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sstream>
#include <unistd.h>
//#include <ctime>
//#include <algorithm>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include "PHTmessage.pb.h"
//#include "soci.h"
//#include "mysql/soci-mysql.h"
#include "connectDB.h"
#include "parser.h"
#include "error.h"
#include "message.h"
#include "data_struct.h"
#include "pst.h"

using namespace std;
using namespace PHT; // namespace for using google protocol buffer
using namespace soci; // namespace for using soci library 

const int portno = 3303; 

void processing(int sock, Error &err);


int main(int argc, char *argv[])
{
    bool demonized = false;

    if (demonized) daemon(0,0);
    // Creating lerr stringstream to send back to the client for managing
    // errors.
    //stringstream lerr;
    
    // Redirecting cerr output to file "server_error.txt" in server/server
    // directory:
    //ofstream out("server_error.txt",ios_base::app);
    //streambuf *old_cerr = cerr.rdbuf();
    //cerr.rdbuf( out.rdbuf() );

    Error err("server_error.txt");

    int sockfd, newsockfd;
    //int portno;
    pid_t pid;
    socklen_t clilen;
     
    string buffer; // a vector<char> should be better...
    struct sockaddr_in serv_addr, cli_addr;
    int n;

    // Checking the calling statement of the program is correct:
    // server port
    if (argc < 2 && !demonized)
    {
        //error("ERROR, no port provided\n");
        cout<<"usage: "<<argv[0]<<" port\n";
        exit(1);
    }
    // Opening the socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
    {
        string emsg = "ERROR: socket not opened";
        err.writeErrorMessage(emsg);
       //cerr<<"ERROR opening socket";
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    //portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0) 
    {
             //cerr<<"ERROR on binding";
             string emsg = "ERROR: binding";
             err.writeErrorMessage(emsg);
    }

    listen(sockfd,5);
     
    clilen = sizeof(cli_addr);

    // starting the listening loop. 
    while (1)
    {
    	newsockfd = accept(sockfd, 
                          (struct sockaddr *) &cli_addr, 
              	           &clilen);
        //cout<<newsockfd<<endl;
        if (newsockfd < 0)
        {
            //time_t now = time(0);
            //string dt = ctime(&now);
            //dt.erase( remove(dt.begin(), dt.end(), '\n'), dt.end() );
            //cerr<<dt<<" "<<"ERROR on accept\n";
            string emsg = "ERROR: on accept";
            err.writeErrorMessage(emsg);
            exit(1);
        }

        signal(SIGCHLD,SIG_IGN); // this is needed to avoid zombies until the parent is dead

        // The following fork() is used to allow different client to connect to the server
        pid = fork();
	if (pid>0) cout<<"Forking with child PID "<<pid<<endl; // Parent process
 	if (pid<0)
        {
            string emsg = "ERROR: no fork";
            err.writeErrorMessage(emsg);
            //cerr<<"ERROR on fork";
        }
	 if (pid==0)
	 {
	    close(sockfd);
            // The following try-catch block prints error from DB operations to
            // err.
            //try
            //{
	        processing(newsockfd,err);
	        exit(0);
            //}
            //catch (mysql_soci_error const &e)
            //{
            //    string msg;
            //    msg = "MYSQL ERROR: " + e.err_num_ + space + e.what() + "\n";
            //    err.writeErrorMessage(msg);
                //cerr<<"MySQL error: "<<e.err_num_<<" "<<e.what()<<endl;
            //}
            //catch (exception const &e)
            //{
            //    stringstream tmp;
            //    string msg;
            //    tmp<<e.what();
            //   msg = "SOCI ERROR: " + tmp.str() + "\n";
            //    err.writeErrorMessage(msg);
                //cerr<<"Soci error: "<<e.what()<<endl;
            //}
	 }
	 else close(newsockfd);
    } /* end of while for server listening */

    //Closing the socket
    close(sockfd); // Should also be moved into try-catch block (?)
    // Redirecting cerr to original stream
    //out.close();
    //cerr.rdbuf(old_cerr);

    return 0; /* never here */
   }	    

void processing(int sock, Error &err)
{
    bool is_a_message = false;
    string message;
    is_a_message = readFromSocket(sock,message,err);
    if ( !is_a_message ) return;

    // De-serialization starts here
    PHTmessage *p_oda = new PHTmessage;
    // The following check should fail only if the message is corrupted.
    cout<<"Parsing...\n"<<endl;
    if (!p_oda->ParseFromString(message))
    {
        string emsg = "ERROR. Can not parse the received message.";
        err.writeErrorMessage(emsg);
		cout<<"!!! ERROR in PARSING !!!"<<endl;
        cout<<p_oda->DebugString();
		exit(-1);
    }
    //cout<<"Printing debug message string\n";
    //cout<<p_oda->DebugString();
    //cout<<"done"<<endl;
    // Parsing the message. Only one proposal at a time can be inserted.
    data_s dat;
    dat = parsingMessage(p_oda);

    // Check message type:
    switch ( p_oda->type() )
    {
        case PHTmessage::DATA:
            insertProposal(sock,dat,err);
            break;
        case PHTmessage::QUERY:
            {
                cout<<"Query found...\n";
				Query *m_query = p_oda->mutable_query();
                //cout<< (p_oda->mutable_query())->query() <<endl;
				if ( m_query->file_to_upload() )
				{
					uploadFile(m_query->file_name(), m_query->file_data());	
				}
				else
				{
		            int p_status = m_query->query();
			        if (p_status > 0)
		        	{
		            	allProposalsWithStatus(sock,p_status,err);
			        }
		        	if (p_status<0)
		            {
			            p_status = (-1) * p_status;
		        		proposalWithID(sock,p_status,err);
		        	}
				 }
                break;
            }
		case PHTmessage::PST:
			break;
        default:
            string emsg = "ERROR: message type not yet implemented";
            err.writeErrorMessage(emsg);
    }

    // Cleaning memory
    delete p_oda;

    cout<<"done\n";
}
