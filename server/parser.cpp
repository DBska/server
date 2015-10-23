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
//vector<string> parsingMessage(PHTmessage *p_oda)
data_s parsingMessage(PHTmessage *p_oda)
{
    cout<<"parsing...\n";
    cout<<p_oda->DebugString();
    //vector<string> command;
    data_s dat;
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
                const Message *mData = &(r->GetRepeatedMessage(*p_oda,fdData,0));
                //const Message *mData = &(r->GetMessage(*p_oda,fdData));
                assert (mData != 0);
                dat = writeTableCommand(mData,fdData->message_type(),mData->GetReflection());
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


    // printing all tables and field on screen:
    int nt = dat.table.size();
    for (int t = 0; t<nt; t++)
    {
        cout<<"Table: "<<dat.table[t]<<endl;
        cout<<" Fields Values: "<<endl;
        int nf = dat.name[t].size();
        for (int c = 0; c<nf; c++)
        {
            cout<<dat.name[t][c]<<" "<<dat.value[t][c]<<endl;
        }
    }
    cout<<"out of parser...\n";
    return dat;
    // return command;
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
//vector<string> writeTableCommand(const Message *m, const Descriptor *d, const Reflection *r)
data_s writeTableCommand(const Message *m, const Descriptor *d, const Reflection *r)
{
    // The vector<string> contains the SQL commands for inserting values
    vector<string> command;
    stringstream data;

    cout<<"IN\n";
    data<<"INSERT INTO "<<d->name()<<" (";

    bool loop_message = true;
    const Message *mc = m;
    const Reflection *rc = r;
    const Descriptor *dc = d;
    const Message *mnew = m;
    const Reflection *rnew = r;
    const Descriptor *dnew = d;
    data_s dat;

    // The strategy of this block of code is as follows: of the message m
    // examined a reflection r is extracted. All the field data are stored in
    // fj. Looping (i) on all fj, if the fj[i] TYPE_MESSAGE is found a new table
    // is identified. Before examining the new table, all basic types (string,
    // float,...) are stored in two vectors: one for the names (name) and one
    // for the corresponding values (value). A check on value to see if it is
    // set is also done.
    while (loop_message)
    {
        bool found_new_message = false;
        // The following two commands extract all the fields set into this message.
        vector< const FieldDescriptor * > fj;
        rc->ListFields(*mc,&fj);
        dat.table.push_back(dc->name());
        int t = dat.table.size() - 1;

        for (int i=0; i<fj.size(); i++) 
        {
            if ( fj[i]->type() == FieldDescriptor::TYPE_MESSAGE)
            {
                found_new_message = true;
                mnew = &(rc->GetMessage(*mc,fj[i]));
                dnew = fj[i]->message_type();
                rnew = mnew->GetReflection();

                cout<<"Found new table:"<<fj[i]->name()<<endl;
            }
            else
            {
                // Check to see if the value has been inserted. If not, the field is
                // discarded
                if ( rc->HasField(*mc,fj[i]) )
                {
                    cout<<"----"<<fj[i]->name()<<endl;
                    dat.name[t].push_back( fj[i]->name() );
                    dat.value[t].push_back( returnField(mc,fj[i],rc) );
                    data<<"("<<fj[i]->name()<<";"<<returnField(mc,fj[i],rc)<<") ";
                }
            }
        }
        // Checking if the message and its structure has been fully parsed
        if ( !found_new_message ) 
        {
            loop_message = false;
        }
        else
        {
            mc = mnew;
            rc = rnew;
            dc = dnew;
        }
    }
    cout<<"OUT\n";

    return dat;
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

