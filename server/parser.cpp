#include <iostream>
#include <sstream>
#include <assert.h>
#include "parser.h"

vector<string> parsingMessage(PHTmessage *p_oda)
{
    vector<string> command;
    const Descriptor *d = p_oda->GetDescriptor();
    const Reflection *r = p_oda->GetReflection();
    const FieldDescriptor *msg_type = d->FindFieldByName("type");
    
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
                cout<<"in\n";
                command = writeTableCommand(mData,fdData->message_type(),mData->GetReflection());
                cout<<"out\n";
            }
            if ( type->number() == PHTmessage::QUERY )
                cout<<"QUERY Message Found\n";
            if ( type->number() == PHTmessage::ANSWER )
                cout<<"ANSWER Message Found\n";

        }
    }
    else
    {
        cout<<"Error: expecting Message type\n";
        exit(1);
    }

    return command;
}

vector<string> writeTableCommand(const Message *m, const Descriptor *d, const Reflection *r)
{
    vector< const FieldDescriptor * > fj;
    r->ListFields(*m,&fj);
    
    vector<string> command;
    stringstream data;

    cout<<"IN\n";
    data<<".table name: "<<d->name()<<" ";
    //cout<<"Number of fields: "<<d->field_count()<<endl;

    bool found_new_message = false;
    bool build_new_commands = false;
    const Message *mnew = 0;
    const Reflection *rnew = 0;
    const Descriptor *dnew = 0;
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
            data<<"("<<fj[i]->name()<<";"<<returnField(m,fj[i],r)<<") ";
        }
    }
    command.push_back(data.str());
    cout<<"OUT\n";

   
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

/*    TYPE_FLOAT = = 2;
    TYPE_INT64 = = 3,
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

