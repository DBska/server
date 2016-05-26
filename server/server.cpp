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
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include "PHTmessage.pb.h"
#include "connectDB.h"
#include "parser.h"
#include "error.h"
#include "message.h"
#include "data_struct.h"
#include "soci.h"
#include "mysql/soci-mysql.h"


using namespace std;
using namespace PHT; // namespace for using google protocol buffer
using namespace soci; // namespace for using soci library

int portno = 5200; // default port if code is demonized
const string use_db = "db=PHT user=root password=Administrator";
//const string use_db = "db=PHT user=controls password=Wrufu6ac";


void* processing(void *);

int main(int argc, char *argv[])
{

    // Flag to activate demonization of the server.
    bool demonized = false;

    if (demonized) daemon(0,0);

    Error err("server_error.txt");

    int socket_desc, new_socket;
    int *new_sock;
    socklen_t clilen;

    string buffer;
    struct sockaddr_in serv_addr, cli_addr;

    // Checking the calling statement of the program is correct:
    // $server port_no
    if (argc < 2 && !demonized)
    {
        cout<<"usage: "<<argv[0]<<" port\n";
        exit(1);
    }
    // Opening the socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc < 0)
    {
        string emsg = "ERROR: socket not opened";
        err.writeErrorMessage(emsg);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    if (!demonized)
        portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(socket_desc, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
        string emsg = "ERROR: binding";
        err.writeErrorMessage(emsg);
    }

    listen(socket_desc,5);

    clilen = sizeof(cli_addr);

    // starting the listening loop.
    while ( (new_socket = accept(socket_desc,(struct sockaddr *) &cli_addr, &clilen)) )
    {
        cout<<new_socket<<" "<<&new_socket<<endl;
        pthread_t sniffer_thread;
        new_sock = (int*)malloc(1);
        *new_sock = new_socket;
        if ( pthread_create(&sniffer_thread, NULL, processing, (void *) new_sock) <0 )
        {
            string emsg = "ERROR: on accept";
            err.writeErrorMessage(emsg);
            exit(1);
        }
    } /* end of while for server listening */

    /* never here */

    return 0;
   }

void* processing(void *socket_desc)
{
    // Opening connection to the DB:
    session sql(mysql, use_db);
    
    Error err("server_error_processing.txt");
    bool is_a_message = false;
    string message;
    int sock = *(int*)socket_desc;
    cout<<"inside\n";

    is_a_message = readFromSocket(sock,message,err);
    if ( !is_a_message ) return 0;

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
            insertProposal(sock,dat,err,sql);
            break;
        case PHTmessage::QUERY:
            {
                cout<<"Query found...\n";
		Query *m_query = p_oda->mutable_query();
                //cout<< (p_oda->mutable_query())->query() <<endl;
		if ( m_query->file_to_upload() ) /* File to upload request */
		{
		    uploadFile(sock, m_query->file_name(), m_query->file_data(), err);
		}
		if ( m_query->delete_file() ) /* File to delete */
                {
		   // If here, m_query->query() stores the proposal's pid
		   deleteFile(m_query->query() , m_query->file_name(), sql);	
		}
		if ( !m_query->delete_file() && !m_query->file_to_upload() ) 
		{
		    int p_status = m_query->query();
		    if (p_status > 0)
		    {
		        allProposalsWithStatus(sock,p_status,err,sql);
		    }
		    if (p_status<0)
		    {
		        p_status = (-1) * p_status;
		        proposalWithID(sock,p_status,err,sql);
		    }
		}
                break;
            }
        default:
            string emsg = "ERROR: message type not yet implemented";
            err.writeErrorMessage(emsg);
    }

    // Cleaning memory
    delete p_oda;
    sql.close();

    // Free the socket pointer
    //free(socket_desc);
    //delete socket_desc;

    cout<<"done\n";

    return 0;
}
