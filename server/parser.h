#ifndef _PARSER_H_
#define _PARSER_H_

#include <string>
#include <vector>
#include <google/protobuf/message.h>
#include "PHTmessage.pb.h"
#include "data_struct.h"

using namespace std;
using namespace PHT;
using namespace google::protobuf;

//vector<string> parsingMessage(PHTmessage *);
data_s parsingMessage(PHTmessage *);
//vector<string> writeTableCommand(const Message *, const Descriptor *, const Reflection *);
data_s writeTableCommand(const Message *, const Descriptor *, const Reflection *);
string returnField(const Message *, const FieldDescriptor *, const Reflection *);


#endif



