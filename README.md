This is an online cloud storage system
===========

I have implemented an online server using c programming which can accept multiple client requests at a time. 
It works like FTP (File transfer protocol) but it uses only one port which can be used to send control and data messages on the same port.

Functionality
==========

1. Multiple clients can log in to the system at a time.
2. A user can upload/download/delete any number of files he/she wishes to. One user can share his/her files with other users too.
3. No user is allowed to browse other user's directory. If a new user signs up, a new empty directory created inside the root directory (if not already present).
4. The server is maintaining a log file for each user. The file has following details: file name, action (upload/download/delete/share), IP address (of the user machine), date and time.

User Actions which are allowed in the system
========

a) Sign in/ Sign up

b) Delete file

c) Upload/ Download file

d) Share file 

e) Show log

f) Sign out

How to compile
=====
Client side on the terminal just type : gcc client.c -lpthread Headerfile.h network.c signup.c signin.c interface.c Communication.c -o client
if this compiles successfully then execute ./client

Server side on the terminal just type : gcc -Wall -Wextra -pedantic -pthread server.c -pthread ServerHeader.h Server_Network_file.c Start_login.c Validation.c -o server

if this compiles successfully then execute ./server
