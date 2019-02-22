#include "ServerHeader.h"


struct sockaddr_in server,client;
 int sock1,sock2;

void Socket(){

  sock1 = socket(AF_INET, SOCK_STREAM, 0);
      if(sock1 == -1)
        {
          printf("Socket creation failed");
          exit(1);
        }
}

void Bind(){

      server.sin_family=AF_INET; 
      server.sin_port = htons(PORT);
      server.sin_addr.s_addr =inet_addr("10.0.17.57");
      bzero(&(server.sin_zero),8);
     int kbind = bind(sock1,(struct sockaddr*)&server,sizeof(server));
      if(kbind == -1)
        {
          printf("Binding error");
          exit(1);
        }


}

void Listen(){

   int  k = listen(sock1,5);
      if(k == -1)
        {
          printf("Listen failed");
          exit(1);
        }

}

int Accept(){


      int len = sizeof(client);
      sock2 = accept(sock1,(struct sockaddr*)&client, &len);
      if(sock2==-1)
      {
        printf("Error in Accept function call !");
        exit(1);
      }
      
return sock2;
}
