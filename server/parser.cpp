#include <iostream>
#include <sstream>
#include <assert.h>
#include "parser.h"


/*! Parse the string after being de-serialized by the google protocol buffer
 * function.
 *
 * \param *p_oda a pointer to the global message
 * \return a vector<string> where each line is an SQL command
 */
vector<string> parsingMessage(PHTmessage *p_oda)
{
    vector<string> command;
    const Descriptor *d = p_oda->GetDescriptor();
    const Reflection *r = p_oda->GetReflection();
    const FieldDescriptor *msg_type = d->FindFieldByName("type");
   
    // This first check determines which part of the message is filled. There
    // are actually only three types:
    // PHTmessage::DATA : a proposal (and any related data) to be inserted into the DB
    // PHTmessage::QUERY : a string with a query to be sent to the DB
    // PHTmessage::ANSWER : a string with all the messages from the server to the tool
    
    if ( msg_type )
    {
        if ( msg_type->type() == FieldDescriptor::TYPE_ENUM )
        {
            cout<<"Type Ok.\n";

            const EnumValueDescriptor *type = r->GetEnum(*p_oda, msg_type);
            if ( type->number() == PHTmessage::DATA )
            {
                cout<<"DATA Message Found\n";
                const FieldDescriptor *fdData = d->FindFieldByName("proposal");
                assert (fdData != 0);
                const Message *mData = &(r->GetMessage(*p_oda,fdData));
                assert (mData != 0);
                command = writeTableCommand(mData,fdData->message_type(),mData->GetReflection());
            }
            if ( type->number() == PHTmessage::QUERY )
                cout<<"QUERY Message Found. Not Implemented yet.\n";
            if ( type->number() == PHTmessage::ANSWER )
            {
                cout<<"ANSWER Message Found. Error.\n";
                exit(1);
            }
        }
    }
    else
    {
        // If here the PHTmessage.type has not be set
        cerr<<"ERROR: expecting Message type\n";
        exit(1);
    }
 
    // Here I am returning all the commands. If the vector<string> is empty, no
    // commands have been defined.
    return command;
}

/*! This function is recursive, and decompose the data in the PHTmessage into
 * tables and variables name; values. The assumption is that a message is a
 * TABLE. Any non message type field inside the message under consideration, is
 * assumed to be a couple of (name,value) to be inserted into the table.
 * If everything goes as assumed, the following command to soci is isseed:
 *
 * INSERT INTO message_name (name1,name2,..) VALUES (value1,value2,...);
 *
 */ 
vector<string> writeTableCommand(const Message *m, const Descriptor *d, const Reflection *r)
{
    // The following two commands extract all the fields set into this message.
    vector< const FieldDescriptor * > fj;
    r->ListFields(*m,&fj);
   
    // The vector<string> contains the SQL commands for inserting values
    vector<string> command;
    stringstream data;

    cout<<"IN\n";
    data<<"INSERT INTO "<<d->name()<<" (";

    bool found_new_message = false;
    bool build_new_commands = false;
    const Message *mnew = 0;
    const Reflection *rnew = 0;
    const Descriptor *dnew = 0;
    vector<string> name;
    vector<string> value;

    // The strategy of this block of code is as follows: of the message m
    // examined a reflection r is extracted. All the field data are stored in
    // fj. Looping (i) on all fj, if the fj[i] TYPE_MESSAGE is found a new table
    // is identified. Before examining the new table, all basic types (string,
    // float,...) are stored in two vectors: one for the names (name) and one
    // for the corresponding values (value). A check on value to see if it is
    // set is also done.
    for (int i=0; i<fj.size(); i++) 
    {
        if ( fj[i]->type() == FieldDescriptor::TYPE_MESSAGE)
        {
            found_new_message = true;
            mnew = &(r->GetMessage(*m,fj[i]));
            dnew = fj[i]->message_type();
            rnew = mnew->GetReflection();

            cout<<"Found new table:"<<fj[i]->name()<<endl;
        }
        else
        {
            // Check to see if the value has been inserted. If not, the field is
            // discarded
            if ( r->HasField(*m,fj[i]) )
            {
                cout<<"----"<<fj[i]->name()<<endl;
                name.push_back( fj[i]->name() );
                value.push_back( returnField(m,fj[i],r) );
                //data<<"("<<fj[i]->name()<<";"<<returnField(m,fj[i],r)<<") ";
            }
        }
    }
    assert( name.size()==value.size() ); // the number of names must be equal to the number of values
    for (int n=0; n<name.size(); n++)
    {
        if ( n==name.size()-1 )
        {
            data<<name[n]<<")";
        }
        else
        {
            data<<name[n]<<",";
        }
    }
    data<<" VALUES (\"";
    for (int v=0; v<value.size(); v++)
    {
        if ( v==value.size()-1 )
        {
            data<<value[v]<<"\")";
        }
        else
        {
            data<<value[v]<<"\",\"";
        }
    }
    data<<";";
    // Storing the SQL insert command 
    command.push_back(data.str());
    cout<<"OUT\n";


    // This block is the recursive part. If a table has been identified, now it
    // is parsed. I think that if the message contains two tables, this part of
    // code does not work. A test must be performed.
    if (found_new_message)
    {
        vector<string> new_command;
        new_command = writeTableCommand(mnew,dnew,rnew);
        for (int j=0; j<new_command.size(); j++)
            command.push_back(new_command[j]);
    }

    return command;
}


string returnField(const Message *m, const FieldDescriptor *fd, const Reflection *r)
{
    stringstream sstr;

    switch ( fd->type() )
    {
        case FieldDescriptor::TYPE_DOUBLE:
            sstr<<r->GetDouble(*m,fd);
            break;
        case FieldDescriptor::TYPE_STRING:
            sstr<<r->GetString(*m,fd);
            break;
        case FieldDescriptor::TYPE_INT32:
            sstr<<r->GetInt32(*m,fd);
            break;
        case FieldDescriptor::TYPE_ENUM:
            sstr<<(r->GetEnum(*m,fd))->name();
            break;
        case FieldDescriptor::TYPE_INT64:
            sstr<<(r->GetInt64(*m,fd));
            break;

/*    TYPE_FLOAT = = 2;
    TYPE_UINT64 = = 4,
    TYPE_INT32 = = 5,
    TYPE_FIXED64 = = 6,
    TYPE_FIXED32 = = 7,
    TYPE_BOOL = = 8,
    TYPE_GROUP = = 10,
    TYPE_MESSAGE = = 11,
    TYPE_BYTES = = 12,
    TYPE_UINT32 = = 13,
    TYPE_ENUM = = 14,
    TYPE_SFIXED32 = = 15,
    TYPE_SFIXED64 = = 16,
    TYPE_SINT32 = = 17,
    TYPE_SINT64 = = 18,
    MAX_TYPE = = 18
*/
    }

    return sstr.str();
}

