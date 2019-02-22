/*FTP Client*/
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <string.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <arpa/inet.h>
/* for threading */
    #include <pthread.h>
    /*for getting file size using stat()*/
    #include<sys/stat.h>
     
    /*for sendfile()*/
    #include<sys/sendfile.h>
     
    /*for O_RDONLY*/
    #include<fcntl.h>
    #define PORT 12349





pthread_t recvt;
char ip[INET_ADDRSTRLEN];
struct sockaddr_in server;
