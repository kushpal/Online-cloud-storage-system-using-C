#include "Headerfile.h"

extern int Signup(void);
extern int Signin(void);
extern int Interface(void);
extern void AboutTheSystem(void);
/* GLOBALS */

int sock=-1,conc=-1;
extern struct sockaddr_in server; 
extern char ip[INET_ADDRSTRLEN];
extern pthread_t recvt;
     
int main(int argc,char *argv[])
    {
    
     int k;
lo:
     k=Interface();
      
      switch(k){

            case 1:
                    if(Signup()==1)
                    {
                      printf("\n|--------YOU SIGNED UP SUCCESSFULLY-----------|\n\n");
                      k=Signin();
                      if(k==1)
                        goto lo;

                    }
                    else
                      {
          
                      printf("\n|--------YOU HAVE ALREADY IN OUR SYSTEM -----------|\n\n");
                      Interface();

                      }

              break;
           case 2:
                    k=Signin();
                    if(k==1)
                      goto lo;
                    break;
          case 3:
                     AboutTheSystem();
                    exit(1);
                    break;
      
      }
           pthread_join(recvt,NULL);
            close(sock);

       
      return 0;

    }
