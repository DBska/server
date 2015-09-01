Downloading Server Code
=======================

Usage:

for complete repository:

$ git clone  https://github.com/DarthVeder/server.git

for only branch *branch* version:

$ git clone -b *branch* --single-branch https://github.com/DarthVeder/server.git

The repository is as follows:

*master*: A fictitious oda.proto is used between client and server. The code
works, however one MUST define in mysql a table Proposal with the following
fields: id (int) and title (varchar(40)). Otherwise soci lib does not work.

*pht*: a new PHT message structure. A proto directory is also present,
describing the structure of the message. A makefile is provided to generate all
the necessary C++ classes. In directory server/server is also present a
directory mysql with a DDL.sql that should be used to build a db named PHT for
testing the soci connection with the db from the server code. The db should be
build before running the code.

Directory structure
===================

After downloading the repository you will find the following structure inside the server directory:
```
server/
├── client
│   ├── client.cpp
│   ├── makefile
├── makefile
├── proto
│   ├── CoAuthors.pb.cc
│   ├── CoAuthors.pb.h
│   ├── makefile
│   ├── PHTmessage.pb.cc
│   ├── PHTmessage.pb.h
│   ├── ProposalEditors.pb.cc
│   ├── ProposalEditors.pb.h
│   ├── Proposals.pb.cc
│   ├── Proposals.pb.h
│   ├── ProposalStatus.pb.cc
│   ├── ProposalStatus.pb.h
│   ├── ProposalType.pb.cc
│   ├── ProposalType.pb.h
│   ├── Reviews.pb.cc
│   ├── Reviews.pb.h
│   ├── ScienceGoals.pb.cc
│   ├── ScienceGoals.pb.h
│   ├── SupportingDocuments.pb.cc
│   ├── SupportingDocuments.pb.h
│   ├── TACReviews.pb.cc
│   └── TACReviews.pb.h
├── README.md
├── server
│   ├── makefile
│   └── server.cpp
└── TODO
```

Installation
============

First, the mysql db PHT  must be build. Inside server/server/mysql one must run:

$ mysql -p < DDL.sql

Connect to mysql to check that a database named PHT is present. There should be
a certain number of tables inside it.

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
a db on another machine. If you are not on alcor, then you have a problem.....
