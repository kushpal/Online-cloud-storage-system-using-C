#include "Headerfile.h"
extern void Socket(void);
extern void Connect(void);
extern int Interface(void);
extern void *Communication(void *);
extern  int sock;

extern struct sockaddr_in server; 
extern char ip[INET_ADDRSTRLEN];
extern pthread_t recvt;

int Signin(){

    char arr1[50],arr2[50];
    printf("\n*************************************************************************\n");
    printf("\n|+++------------------------------------------------------------------+++|\n");
    printf("|+++------------------------------------------------------------------+++|\n");
    printf("|+++----------------------------SIGNIN -------------------------------+++|\n");
    printf("|                                                                        |\n");
    printf("|                            USER NAME :                                 |\n");
    printf("|                                       ");
    scanf("%s",arr1);
    printf("|                            PASSWORD :                                  |\n");
    printf("|                                      ");
    scanf("%s",arr2);
    printf("|+++------------------------------------------------------------------+++|\n");
    printf("|+++------------------------------------------------------------------+++|\n");
    
   if(sock==-1)
   {
    Socket();
    Connect();
   }
   int status=1;
   send(sock,&status,sizeof(int), 0);
   send(sock, arr1, 50, 0);
   send(sock, arr2, 50, 0);
   recv(sock, &status, sizeof(int), 0);
   if(status==1){
  
    inet_ntop(AF_INET, (struct sockaddr *)&server, ip, INET_ADDRSTRLEN);
    printf("connected to %s\n\n",ip);
    
    
   printf("\n                                               | LOGED IN USER : %s |\n",arr1);
 pthread_create(&recvt,NULL,Communication,&sock);
   }
   else if(status==2){
    printf("\n|+++---------------YOU ARE ALREADY LOGED IN---------------------+++|\n\n");
              return Interface();
             }
  else{
    printf("\n|+++------------USERNAME AND PASSWORD ARE INCORRECT-------------+++|\n\n");
   return Interface();
  }

  }
