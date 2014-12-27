Downloading Server Code
=======================

Usage:

for complete repository:
git clone  https://github.com/DarthVeder/server.git

for only branch *branch* version:
git clone -b *branch* --single-branch https://github.com/DarthVeder/server.git

Directory structure
===================

After downloading the repository you will find the following structure:

'''
server
├── client
│   ├── client.cpp
│   ├── makefile
│   ├── oda.pb.cpp
│   └── oda.pb.h
├── makefile
├── oda.proto
├── README.md
└── server
    ├── makefile
    ├── oda.pb.cpp
    ├── oda.pb.h
    └── server.cpp
'''

Installation
============

Simply perform:

$make

This should generate the two executables client/client and server/server. The server should be running
before the client is invoked. 

Usage
=====

$ server port_number

port_number should be any integere number above 3000. Attention should be used for reserved
port numbers.

$ client hot_name port_number

If everything goee well, the server should be able to add a new row in the database and print the
new table.

Warning
=======

For the time being, the database is assumed to be on alcor and there is no option for changing
the db. If you are not on alcor, then you have a problem.....
