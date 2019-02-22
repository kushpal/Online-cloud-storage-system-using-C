/*FTP server*/
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <string.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include<sys/types.h>
    #include <unistd.h>
     #include <arpa/inet.h>
     #include <pthread.h>
     #include<time.h>
    /*for getting file size using stat()*/
    #include<sys/stat.h>
     
    /*for sendfile()*/
    #include<sys/sendfile.h>
    
    /*for O_RDONLY*/
    #include<fcntl.h>
    #define PORT 12349
