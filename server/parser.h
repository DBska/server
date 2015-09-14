#ifndef _PARSER_H_
#define _PARSER_H_

#include <string>
#include <vector>
#include <google/protobuf/message.h>
#include "PHTmessage.pb.h"

using namespace std;
using namespace PHT;
using namespace google::protobuf;

vector<string> parsingMessage(PHTmessage *);
vector<string> writeTableCommand(const Message *, const Descriptor *, const Reflection *);
string returnField(const Message *, const FieldDescriptor *, const Reflection *);


#endif



