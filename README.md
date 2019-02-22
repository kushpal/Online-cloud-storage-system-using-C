This is an online cloud storage system
===========
I have implemented an online server using  c program which can accept multiple client request at a time. 
It works like FTP (File transfer protocol) but it uses only one port which can be used to send control and data messages on the same port.
Functionalities
==========
1. Multiple clients can login to the system at a time.
2. User can upload/download/delete any number of files he/she wishes to. One user can share his/her files with other users too.
3. No user should be allowed to browse other users’ directory. If a new user signs up, a new empty directory should be created inside the root directory (if not already present).
4. Server is maintaining a log file for each user. The file has following details: file name, action (upload/download/delete/share), IP address (of the user machine), date and time.

User Actions which are allowed in the system
========

a) Sign in/ Sign up
=======
b) Delete file
=======
c) Upload/ Download file
======
d) Share file 
======
e) Show log
======
f) Sign out
======
