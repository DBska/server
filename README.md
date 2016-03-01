Downloading Server Code
=======================
Downloading *pht* branch:
$ git clone -b pht --single-branch https://github.com/DarthVeder/server.git

Generic usage:

for complete repository:

$ git clone  https://github.com/DarthVeder/server.git

for only branch *branch* version:

$ git clone -b *branch* --single-branch https://github.com/DarthVeder/server.git

The repository contains the following branches:

*master*: A fictitious oda.proto is used between client and server. The code
works, however one MUST define in mysql a table Proposal with the following
fields: id (int) and title (varchar(40)). Otherwise soci lib does not work.

*pht*: a new PHT message structure. A proto directory is also present,
describing the structure of the message. A makefile is provided to generate all
the necessary C++ classes. In directory server/server it is also present a
directory mysql with a DDL.sql. That file should be used to build a db named PHT for
testing the soci connection from the server code. The db should be
build before running the code. This is the current working code.

Required libraries
==================

To run, the software requires the following libraries:
1. SOCI - The C++ Database Access Library. Version: 3.2.2
2. BOOST C++ Libraries. Version: 1.59.0
3. Google Protocol Buffer. Version: 2.6.1

To compile java code from protocol buffer, one need to generate the com.google.protocol buffer javas. Follow this step:
Inside the protoc-2.6.1 directory, go inside java. Run "mvn install" and then
"protoc --java_out=src/main/java -I../src ../src/google/protobuf/descriptor.proto"
After these two steps it is possibile to copy from inside src/main the package com.google.protocol and use it to compile the java code.

Directory structure
===================

After downloading the repository you will find the following structure inside the server directory:
```
server/
├── client
│   ├── client.cpp
│   └── makefile
├── interface
│   ├── interface.cpp
│   ├── interface.h
│   ├── makefile
│   ├── socket.cpp
│   └── socket.h
├── makefile
├── proto
│   ├── CoAuthors.proto
│   ├── makefile
│   ├── PHT Class DiagramV2.png
│   ├── PHTmessage.proto
│   ├── ProposalEditors.proto
│   ├── Proposals.proto
│   ├── ProposalStatus.proto
│   ├── ProposalType.proto
│   ├── Reviews.proto
│   ├── ScienceGoals.proto
│   ├── src
│   │   └── makefile
│   ├── SupportingDocuments.proto
│   └── TACReviews.proto
├── README.md
├── server
│   ├── connectDB.cpp
│   ├── connectDB.h
│   ├── data_struct.h
│   ├── makefile
│   ├── mysql
│   │   ├── DDL.sql
│   │   └── README
│   ├── parser.cpp
│   ├── parser.h
│   ├── server.cpp
│   └── server_error.txt
├── TODO
├── tool
│   ├── include
│   │   ├── CoAuthors.pb.h
│   │   ├── interface.h
│   │   ├── PHTmessage.pb.h
│   │   ├── ProposalEditors.pb.h
│   │   ├── Proposals.pb.h
│   │   ├── ProposalStatus.pb.h
│   │   ├── ProposalType.pb.h
│   │   ├── Reviews.pb.h
│   │   ├── ScienceGoals.pb.h
│   │   ├── socket.h
│   │   ├── SupportingDocuments.pb.h
│   │   └── TACReviews.pb.h
│   ├── library
│   ├── makefile
│   └── tool.cpp
└── VERSION
```

Installation
============

First, the mysql db PHT  must be build. Inside server/server/mysql one must run:

$ mysql -p < DDL.sql

Connect to mysql to check that a database named PHT is present. There should be
a certain number of tables inside it. 

Install the required software.

Then, to compile both the server and client codes, in server/ write:

$ make

This should generate the two executables *client/client* and *server/server*. The server should be running
before the client is invoked. 

For different make options, at server directory level use:

$ make help

Usage
=====

$ ./server *port_number*

*port_number* should be any integer number above 3000. Attention should be given for any reserved
port numbers.

$ ./client *host_name* *port_number*

*host_name* can also be localhost. *port_nuber* is obviously the same number used for the server.
If everything goes well, the server should be able to add a new row in the database and print the
new table on screen.

Warning
=======

For the time being, the database is assumed to be on alcor and there is no option for selecting 
a db on another machine, or a specific user. If you are not on alcor or do not know the user for connection, 
then you have a problem.....
