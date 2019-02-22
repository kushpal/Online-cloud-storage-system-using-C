#include "Headerfile.h"

extern struct sockaddr_in server; 
extern volatile int sock,conc; 
void Socket(){
   
   int s=socket(AF_INET, SOCK_STREAM, 0);
   if(s==-1)
    {
      printf(" Error in socket creation !");
      exit(1);
    }
    sock=s;

  }

  void Connect(){

      server.sin_family = AF_INET;
      server.sin_port =htons(PORT);
      server.sin_addr.s_addr =inet_addr("10.0.17.57");
      int k = connect(sock,(struct sockaddr*)&server, sizeof(server));

    if(k==-1)
    {
      printf(" Error in connecting to the Server !");
      exit(1);
    }
    conc=k;

  }
  
  void AboutTheSystem(){

    


  }
