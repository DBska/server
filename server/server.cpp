/* A simple server in the internet domain using TCP-IP
   The port number is passed as an argument */
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <signal.h>
#include <unistd.h>
#include <sstream>
#include <map>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include "oda.pb.h"
#include "soci.h"
#include "mysql/soci-mysql.h"
#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>

using namespace std;
using namespace oda; // namespace for using google protocol buffer
using namespace soci; // namespace for using soci library 
using namespace google::protobuf;

void processing(int sock);
void error(string msg)
{
    perror(msg.c_str());
    exit(1);
}

int main(int argc, char *argv[])
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	
	int sockfd, newsockfd, portno;
    pid_t pid;
    socklen_t clilen;
     
	string buffer; // a vector<char> should be better...
    struct sockaddr_in serv_addr, cli_addr;
    int n;

	// Checking the calling statement of the program is correct:
	// server port
    if (argc < 2) 
        error("ERROR, no port provided\n");

	// Opening the socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
       error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0) 
             error("ERROR on binding");
    listen(sockfd,5);
     
	clilen = sizeof(cli_addr);

	// starting the listening loop. It has a brutal stop: Ctrl-C....
    while (1)
    {
    	newsockfd = accept(sockfd, 
                          (struct sockaddr *) &cli_addr, 
              	           &clilen);
        if (newsockfd < 0) 
           error("ERROR on accept");

        signal(SIGCHLD,SIG_IGN); // this is needed to avoid zombies until the parent is dead

	    // The following fork() is used to allow different client to connect to the server
        pid = fork();
	 	if (pid>0) cout<<"Forking with child PID "<<pid<<endl; // Parent process
 	 	if (pid<0)
	    	error("ERROR on fork");
	 	if (pid==0)
	 	{
	    	close(sockfd); // why here??
	     	processing(newsockfd);
	     	exit(0);
	 	}
	 	else close(newsockfd);
    } /* end of while for server listening */
    
	//Closing the socket
	close(sockfd);
    return 0; /* never here */
}	    

void processing(int sock)
{
	// The message is received in two parts.
	// 1) The length of the message to be received
	uint32_t mLength;
	read(sock,&mLength,sizeof(uint32_t)); // Receive the message length
	mLength = ntohl(mLength); // Ensure host system byte order
	int dataLength = static_cast<int>(mLength);
	cout<<"Message of "<<dataLength<<" elements arrived!\n";
	
	// 2) The message itself. It is stored in a char [], however a vector<char> could and should be used.
	char buff[dataLength]; // Allocating a buffer of approriate length
	int n;
	n = read(sock,buff,dataLength); // Receive the string data

	string message;
	message = buff;   // Convert char [] buff into string for de-serialization 

	// De-serialization starts here. The only assumption is that each field inside message Oda is a table. Query messages
	// are not yet implemented.
	//Oda oda_data;
	Message *oda_data = new Oda;
	// The following check should fail only if the message is corrupted.
	if (!oda_data->ParseFromString(message))
	{
		cerr<<"ERROR. Can not parse the received message.";
		exit(-1);
	}
	// parsing the data and printing to screen. The loop allows for more than one identical submission
	// (ie there is no check on the data already present in the database)

	const Descriptor *descriptor = oda_data->GetDescriptor();
	//const Reflection *reflection = oda_data->GetReflection();
	int nFields = descriptor->field_count();

	cout<<"Found "<<nFields<<" field(s)\n";

	vector< map<string,int> > field_map; // contains for each table, all the data that are not
										 // a message themselves. To access table k:
										 // map<string,int> fieldk = field_map[k];
	vector<string> table_name; // contains the name of each table in the message Oda

	// This loop allows to retrive the different tables and each fields inside the
	// tables. The vector<string> and maps should be modified: the value of i MUST be kept if
	// I need to access the message data outside the loop. I do not know if this is necessesary. Maybe
	// everything can be done here and the maps discarded...
	for (int i=0; i<nFields; i++)
	{
	 	//cout<<"--- "<<descriptor->name()<<endl; // Oda
		const FieldDescriptor *field = descriptor->field(i);
		//cout<<field->name()<<endl; // proposal
		//cout<<field->full_name()<<endl; // oda.Oda.proposal
		//cout<<field->type()<<endl; // 11
		//cout<<field->type_name()<<endl; // message
		if (field->type()==FieldDescriptor::TYPE_MESSAGE)
		{
			// if here, the field inside Oda is another message. I am assuming it is a table that must be inserted
			// in the database
			const Descriptor *table = field->message_type();
			string tmp_name = table->name();
			table_name.push_back(tmp_name);
			int nTableEntries = table->field_count();
			cout<<"Table: "<<tmp_name<<endl;
			//cout<<table->field_count()<<endl;// 3
			//cout<<" 222 ---- "<<table_name<<endl; // Proposal

			// The following loop stores the name and type of each table entries in a map[name,type]
			// so that with a Reflection the data can be examined. This loop extracts
			// and print the table data onto the screen.
			
			map<string, int> tmp_map;
			for (int j=0; j<nTableEntries; j++)
			{
				const FieldDescriptor *field = table->field(j);
				switch ( field->type() )
				{
					case FieldDescriptor::TYPE_INT32 :
						tmp_map[field->name()] = FieldDescriptor::TYPE_INT32;
						break;
					case FieldDescriptor::TYPE_STRING :
						tmp_map[field->name()] = FieldDescriptor::TYPE_STRING;
						break;
				}
				if ( tmp_map.size()>0 )
					field_map.push_back(tmp_map);
			}			
		}
	}
	cout<<"done\n";

	// The following loop is crucial to obtain data and message fields. The GPB idea is as follows:
	// 1) to see what types are in a message -> use class Descriptor
	// 2) to retrieve/modify data -> use class Reflection
	// if there is a message (inner) inside a message (outer), the inner is obtained with a reflection from the outer:
	// const Message *minner = &(router->GetRepeatedMessage(mouter,FieldDescriptor outer,int));
	const Reflection *r = oda_data->GetReflection(); // entering data inside message Oda
	vector< const FieldDescriptor * > v; // this vector will store all types inside message Oda
	r->ListFields(*oda_data,&v); // Loading vector v

	for (int j=0; j<v.size(); j++) // looping on all entries. Only other messages are interesting at this moment.
	{
		if (v[j]->type()==FieldDescriptor::TYPE_MESSAGE) // ok, I found an inner message.
		{
			// I will now examine the inner message. Obviously this should be called each time an inner field is a message..
			const Message *mj = &(r->GetRepeatedMessage(*oda_data,v[j],j));
			const Reflection *rj = mj->GetReflection(); // Finding data inside this message
			vector< const FieldDescriptor * > fj; // this vectore will stores all fields inside the inner message
			rj->ListFields(*mj,&fj);

			// Looping inside the inner fields
			for (int i=0; i<fj.size(); i++) 
			{
				// I need to check which field is under scrutiny
				switch (fj[i]->type())
				{
					case FieldDescriptor::TYPE_INT32 :
						cout<<fj[i]->name()<<": "<<rj->GetInt32(*mj,fj[i])<<endl;
						break;
					case FieldDescriptor::TYPE_STRING :
						cout<<fj[i]->name()<<": "<<rj->GetString(*mj,fj[i])<<endl;
						break;
				}
			}
		}
	}

	// Ok, now I can delete the new.	
	delete oda_data;
    
	/* 
	// Inserting the data into the DB with SOCI. I know it is only ONE data. The following part of the code
	// should be put in the for(i) above.
	session sql(mysql, "db=oda user=marco password=marco");
	const Proposal& proposal = oda_data.proposal(0); // ad-hoc retrieving of the only data present in the message

	// before inserting, printing the currente number of Proposals
	int count;
	sql<<"select count(*) from Proposal", into(count);
	cout<<"Table Proposal has "<<count<<" entries"<<endl;


	// Inserting the data
	sql<<"insert into Proposal (id,title) values(:idp, :titlep)", use(proposal.id()), use(proposal.title());
	sql<<"select count(*) from Proposal", into(count);
	cout<<"Table Proposal now has "<<count<<" entries"<<endl;

	// Printing the new table on screen
	rowset<row> rs = (sql.prepare << "select id, title from Proposal");

	// iteration through the resultset:
	int r = 1;
	for (rowset<row>::const_iterator it = rs.begin(); it != rs.end(); ++it)
	{
    	row const& row = *it;

    	// dynamic data extraction from each row:
    	cout << r <<") " << "Id: " << row.get<int>(0)
        	 << " Title: " << row.get<string>(1)  << endl;
		r++;
	}
	*/
}
