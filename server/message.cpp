#include "message.h"

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

    PHTmessage p_msg;
    string reply_msg;
    Answer *a = new Answer;
    
    cout<<"Preparing the reply..\n";
    if ( e_msg.size() == 0 ) // no error(s). Operation ok, must return the ID
    {
        reply_msg = new_proposal_id;
        p_msg.set_type(PHTmessage::ANSWER);

        a->set_answer(reply_msg);
    }
    else // error(s). Must return the error.
    {
        reply_msg = e_msg;
        p_msg.set_type(PHTmessage::ERROR);

        a->set_answer(reply_msg);
    }

    cout<<"Preparing the reply..\n";
    // Serializing and sending of reply
    p_msg.set_allocated_answer(a);

    string msg;
    p_msg.SerializeToString(&msg);
    replyToClient(sock,msg);
}


void allProposalsWithStatus(int sock)
{

}

void replyToClient(int sock, string reply_msg)
{
    int n;

    // Sendig back to tool DB results
    uint32_t dataLength_s = htonl(reply_msg.size()); // convert int to network byte order. 

    // The message e is divided in two parts:
    // 1) First message sent is the length of the message with the serialization
    cout<<"Sending "<<reply_msg.size()<<" elements to tool\n";
    n = write(sock,&dataLength_s,sizeof(uint32_t));
    if (n < 0)
    {
        cerr<"ERROR writing to socket the message length";
    }
    
    // 2) The actual message is sent. n stores the actual length sent.
    n = write(sock,reply_msg.c_str(),dataLength_s);
    if (n < 0) 
    {
        cerr<"ERROR writing to the message socket";
    }
}
