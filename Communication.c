#include "Headerfile.h"

struct stat obj;

extern struct sockaddr_in server; 
extern char ip[INET_ADDRSTRLEN];
extern pthread_t recvt;

void *Communication(void *socknew){

char buf[100], command[5], filename[100], *f;
      int k, size, status;
       int choice;
      int filehandle;
      int sock = *((int *)socknew);
int i = 1;
      while(1)
        {
          printf("ENTER YOUR CHOICE:\n1. LIST FILES\n2. UPLOAD FILE\n3. DOWNLOAD FILE\n4. DELETE FILE \n5. SHARE FILE \n6. SHOW LOG\n7. SIGN OUT \n8. PWD\n9. CD \n");
          scanf("%d", &choice);
          switch(choice)
      {
      case 1:
              strcpy(buf, "ls");
              send(sock, buf, 100, 0);
              recv(sock, &size, sizeof(int), 0);

              f = malloc(size);
              recv(sock, f, size, 0);
              filehandle = creat("temp.txt", O_WRONLY);
              write(filehandle, f, size);
              close(filehandle);
              printf("|<-----------------THE LIST OF FILES ARE-------------------->|\n");
              system("cat temp.txt");
              printf("|<---------------------------ENDED-------------------------->|\n");
        break;

      case 2:
              printf("ENTER THE PATH OF THE FILE: ");
                       scanf("%s", filename);
             filehandle = open(filename, O_RDONLY);
          if(filehandle == -1)
            {
              printf("\nNo such file on the local directory\n\n");
              break;
            }
          strcpy(buf, "put ");
    strcat(buf, filename);
    send(sock, buf, 100, 0);
    stat(filename, &obj);
    size = obj.st_size;
    send(sock, &size, sizeof(int), 0);
    sendfile(sock, filehandle, NULL, size);
    recv(sock, &status, sizeof(int), 0);
    if(status)
      printf("File stored successfully\n");
    else
      printf("File failed to be stored to remote machine\n");
    break;
      case 3:
              printf("ENTER THE FILE NAME TO DOWNLOAD: ");
              scanf("%s", filename);
              strcpy(buf, "get ");
              strcat(buf, filename);
              send(sock, buf, 100, 0);
              recv(sock, &size, sizeof(int), 0);
              if(!size)
                {
                  printf("No such file on the remote directory\n\n");
                  break;
                }
              f = malloc(size);
              recv(sock, f, size, 0);
              while(1)
              {
                filehandle = open(filename, O_CREAT | O_EXCL | O_WRONLY, 0666);
              if(filehandle == -1)
              {
                sprintf(filename + strlen(filename), "%d", i);
              }
              else break;
              }
                write(filehandle, f, size);
               close(filehandle);
               strcpy(buf, "cat ");
               strcat(buf, filename);
               //system(buf);
        break;
      case 4:
              printf("ENTER THE FILE NAME TO DELETE: ");
              scanf("%s", filename);
              strcpy(buf, "rm ");
              send(sock, buf, 100, 0);
              send(sock, filename, 100, 0);
              recv(sock, &size, sizeof(int), 0);
              if(size==0)
                printf("\n%s CAN NOT BE DELETED !\n",filename);
              else
                 printf("\n%s IS DELETED \n",filename);
        break;


      case 5:
              
              strcpy(command,"ln");
              send(sock,command,50,0);
              printf("ENTER THE FILE NAME TO SHARE : ");
              scanf("%s", filename);
        
              send(sock, filename, 100, 0);
              printf("ENTER THE USER NAME WITH YOU WANT TO SHARE THE FILE: ");
              scanf("%s", buf);
              send(sock,buf,100,0);
              recv(sock, &size, sizeof(int), 0);
              if(size==0)
                printf("\n%s CAN NOT BE SHARED !\n",filename);
              else
                 printf("\n%s IS SHARED \n",filename);
        break;

      case 6:
          
              strcpy(buf, "show");
              send(sock, buf, 100, 0);
              recv(sock, &size, sizeof(int), 0);

              f = malloc(size);
              recv(sock, f, size, 0);
              filehandle = creat("show_log.txt", O_WRONLY|O_CREAT);
              write(filehandle, f, size);
              close(filehandle);
              
              printf("\n|<----------------------THE ACTIVITY BOX----------------->|\n");
              system("cat show_log.txt");
              printf("\n|<------------------------ENDED-------------------------->|\n");

              break;


/*

       FILE *fp1;
        char file_name[50];
        strcpy(file_name,buf2);
        strcpy(file_name+strlen(file_name),"/");

        strcpy(file_name+strlen(file_name),"show_log.txt");

        fp1=fopen(filename,"r");
        if(fp1==NULL)
          printf("ERROR IN SHOW LOG\n");
        char f1[50];
        char f2[50];
        char f3[50];
        fscanf(fp1,"%s %s %s ",f1,f2,f3);*/
            
      case 7:
              strcpy(buf, "quit");
              send(sock, buf, 100, 0);
              recv(sock, &status, 100, 0);
        if(status)
          {
            
            printf("Server closed\nQuitting..\n");
            exit(0);
          }
          printf("Server failed to close connection\n");
          break;

      case 8:
            
            strcpy(buf, "pwd");
            send(sock, buf, 100, 0);
            recv(sock, buf, 100, 0);
            printf("The path of the remote directory is: %s\n", buf);
        break;
      case 9:

        strcpy(buf, "cd ");
        printf("Enter the path to change the remote directory: ");
        scanf("%s", buf + 3);
              send(sock, buf, 100, 0);
        recv(sock, &status, sizeof(int), 0);
              if(status)
                printf("Remote directory successfully changed\n");
              else
                printf("Remote directory failed to change\n");
              break;
        break;
      }

        }


  
}
