#include "message.h"



void writeToSocket(int sock, string message, Error &err)
{
    int r_s = message.size();
    char bytes[BUF_SIZE];
    bzero(bytes,sizeof(bytes));
    bytes[0] = (r_s >> 24) & 0xFF;
    bytes[1] = (r_s >> 16) & 0xFF;
    bytes[2] = (r_s >> 8) & 0xFF;
    bytes[3] = r_s & 0xFF;
    
    int n;
    n= write(sock,bytes,sizeof(bytes));
    cout<<"Sending message of size: "<<r_s<<" /// "<<n<<endl;
    n = write(sock,message.c_str(),r_s);
    if (n < 0) err.writeErrorMessage("ERROR writing to socket");
}

bool readFromSocket(int sock, string &answer, Error &err)
{
    bool red = false;
    // Exchanging message length:
    char buffer[BUF_SIZE];
    bzero(buffer,BUF_SIZE);

    int n = 0;
    n = read(sock,buffer,BUF_SIZE);
    //fstream output("blobIN.bin", ios::out | ios::binary);
    //output<<buffer[0]<<buffer[1]<<buffer[2]<<buffer[3];
    //output.close();

    if (n < 0) err.writeErrorMessage("ERROR reading from socket");
    if ( n>BUF_SIZE) err.writeErrorMessage("ERROR int too big");
    if (n != 0)
    {
        cout<<"START READING... "<<endl;
        int val = 0;
	
	val =   buffer[3] & 0xFF | 
	       (buffer[2] & 0xFF) << 8  |
	       (buffer[1] & 0xFF) << 16 |
               (buffer[0] & 0xFF) << 24;

        
        cout<<"value: "<<val<<" //// n: "<<n<<endl;
     
        char message[val+1];
        bzero(message,val);

        // Reading message:
        n = read(sock,message,sizeof(message));
        cout<<"red: "<<n<<" out of "<<val<<endl;
        if (n<val) 
        {
            cout<<"Error in sending data..aborting\n";
            exit(1);
        }
        for (int j=0; j<val; j++)
            answer.push_back(message[j]);
        cout<<answer.length()<<" "<<val<<" "<<val+1<<endl;
        cout<<" $$$$ "<<n-val<<endl;
        cout<<"STOP READING...\n";
        
        //fstream output2("blob2.bin", ios::out | ios::binary);
        //for (int i=0; i<val; i++)
        //    output2<<message[i];
        //output2.close();
        
        red = true;
    }

    return red;
}

void insertProposal(int sock, data_s dat, Error &err)
{
    // inserting the data into the DB
    string new_proposal_id;
    stringstream e_msg_;
    string e_msg;

    try
    {
        new_proposal_id = writeToDB(dat);
    }
    catch (mysql_soci_error const &e)
    {
        e_msg_ <<"MYSQL ERROR: " << e.err_num_ << " " <<  e.what();
        string tmp = e_msg_.str();
        err.writeErrorMessage(tmp);
    }
    //catch (soci_error const &e)
    catch (exception const &e)
    {
        e_msg_ << "SOCI ERROR: " <<e.what();
        string tmp = e_msg_.str();
        err.writeErrorMessage(tmp);
    }
    e_msg = e_msg_.str();

    // If msg.size() == 0 no error has been detected by soci: the proposal id
    // can be returned. Otherwise there are some errors that must be returned to
    // the client.

    PHTmessage *p_msg = new PHTmessage;
    string reply_msg;
    Answer *a = new Answer;
    
    cout<<"Preparing the reply..\n";
    if ( e_msg.size() == 0 ) // no error(s). Operation ok, must return the ID
    {
        reply_msg = new_proposal_id;
        p_msg->set_type(PHTmessage::ANSWER);

        a->set_answer(reply_msg);
        cout<<"   sending ANSWER\n";
    }
    else // error(s). Must return the error.
    {
        reply_msg = e_msg;
        p_msg->set_type(PHTmessage::ERROR);

        a->set_answer(reply_msg);
        cout<<"   sending ERROR\n";
    }
cout<<"rrrrrrrrrrrrrrrrrrr "<<reply_msg<<endl;
    // Serializing and sending of reply
    p_msg->set_allocated_answer(a);
cout<<p_msg->DebugString();

    string msg;
    p_msg->SerializeToString(&msg);
    //replyToClient(sock,msg);
    writeToSocket(sock,msg,err);
}


void allProposalsWithStatus(int sock, int p_stat, Error &err)
{
    cout<<"HERE\n";
    vector<Proposals *> p_s;

    p_s = readAllProposalsFromDB(p_stat);
    cout<<"Size: "<<p_s.size()<<endl;
    //cout<<p_s[0]->proposal_id()<<" "<<p_s[0]->abstract()<<endl;
    PHTmessage *p_msg = new PHTmessage;
    p_msg->set_type(PHTmessage::DATA);

    for (int ip=0; ip<p_s.size(); ip++)
    {
        Proposals *p_tmp = NULL;
        p_tmp = p_msg->add_proposal();
        *p_tmp = *p_s[ip];
    }
    //p_msg.set_allocated_proposal(p_s[0]);

    cout<<"Number of proposals: "<<p_msg->proposal_size()<<endl;
    //p_msg->DebugString();
    // Serializing to a string the data to send
    string message;
    if (!p_msg->SerializeToString(&message))
    {
	    cerr<<"ERROR: Can not serialize the message.\n";
    }
    //cout<<p_msg->DebugString();
    print("list.bin",message);
    writeToSocket(sock,message,err);
    //replyToClient(sock,message);
}

void proposalWithID(int sock, int pid, Error &err)
{
    cout<<"HERE\n";
    Proposals *p_s;
    p_s = readProposalFromDB(pid);
    
    PHTmessage *p_msg = new PHTmessage;
    p_msg->set_type(PHTmessage::DATA);

    Proposals *p_tmp = NULL;
    p_tmp = p_msg->add_proposal();
    *p_tmp = *p_s;

    // Serializing to a string the data to send
    string message;
    if (!p_msg->SerializeToString(&message))
    {
	    cerr<<"ERROR: Can not serialize the message.\n";
    }
    //cout<<p_msg->DebugString();
    writeToSocket(sock,message,err);
}

