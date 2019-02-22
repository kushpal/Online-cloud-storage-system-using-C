#include "ServerHeader.h"

extern void Socket(void);
extern void Bind(void);
extern void Listen(void);
extern int Accept(void); 
extern int check_validation(int k ,char s1[],char s2[]);

   char ip[INET_ADDRSTRLEN];
    pthread_t recvt;
 int clients[100];
  pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

struct stat obj;

  struct client_info {
    int sockno;
    char username[500];
    char ip[INET_ADDRSTRLEN];
};

void format_time(char *output){
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    sprintf(output, "[%d %d %d %d:%d]",timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900, timeinfo->tm_hour, timeinfo->tm_min);
}


void *Start_login(void *socknew ){


    char arr1[50],arr2[50],arr3[50],arr4[50];
    char buf[100], command[5], filename[100];
    int  i, size, c;
    int filehandle;
    int status;
    struct client_info cl;
    cl = *((struct client_info *)socknew);

 pthread_mutex_lock(&mutex);  
l1:
 recv(cl.sockno,&status,sizeof(int),0);

FILE *fp;
if(status==1)
{

fp=fopen("/home/kushpal/Desktop/CN/SERVER/login.txt","a+");
  if(fp==NULL)
  {
    printf("Login file Can not be opened %d\n",cl.sockno);
    exit(0);
  }

   recv(cl.sockno, arr1, 50, 0);
   recv(cl.sockno, arr2, 50, 0);
   
int k=check_validation(0,arr1,arr2);

if(k==1){
 strcpy(cl.username,arr1);
 printf("Login user:%s\n",cl.username);
}
  send(cl.sockno, &k, sizeof(int), 0);
  
fclose(fp);

if(k==0)
goto l1;
}

else{
  fp=fopen("/home/kushpal/Desktop/CN/SERVER/login.txt","a+");
  if(fp==NULL)
  {
    printf("Login file can not be opened \n");
    exit(0);
  }
   recv(cl.sockno, arr1, 50, 0);
   recv(cl.sockno, arr2, 50, 0);
   recv(cl.sockno, arr3, 50, 0);
   recv(cl.sockno, arr4, 50, 0);
int k=check_validation(1,arr3,arr4);
//printf("k=%d %s \n", k,arr3);
if(k==0){
fprintf(fp, "%s ",arr1);
fprintf(fp, "%s ",arr2);
fprintf(fp, "%s ",arr3);
fprintf(fp, "%s ",arr4);
fprintf(fp, "%d ",0);
fprintf(fp, "\n");
status=1;
   send(cl.sockno, &status, sizeof(int), 0);
   
   char buf[]="/home/kushpal/Desktop/CN/SERVER/";
   strcpy(buf+strlen(buf),arr3);
   mkdir(buf,0777);
   
   if(chmod(buf,S_IRUSR|S_IRGRP|S_IROTH)<0)
    printf("Error in chmod   !\n");
   fclose(fp);
   goto l1;
 }
 else
 {
   send(cl.sockno, &k, sizeof(int), 0);
  fclose(fp);
  goto l1;
 }

}
pthread_mutex_unlock(&mutex);

i = 1;
      while(1)
        {
         
          recv(cl.sockno, buf, 100, 0);
          sscanf(buf, "%s", command);
          printf("com=%s ,sock:%d\n",command,cl.sockno );
          char buf2[]="/home/kushpal/Desktop/CN/SERVER/";
        strcpy(buf2+strlen(buf2),cl.username);
         chdir(buf2);
         printf("cdir=%s\n",buf2 );       
          if(!strcmp(command, "ls"))
         {
        pthread_mutex_lock(&mutex);
        
        system("ls -l | awk -f /home/kushpal/Desktop/CN/SERVER/myscript >temps.txt");
        i = 0;
        
        stat("temps.txt",&obj);
        size = obj.st_size;
        
        send(cl.sockno, &size, sizeof(int),0);
        filehandle = open("temps.txt", O_RDONLY);
        sendfile(cl.sockno,filehandle,NULL,size);
        pthread_mutex_unlock(&mutex);
      }
      else if(!strcmp(command, "rm"))
      {
         pthread_mutex_lock(&mutex);
         recv(cl.sockno, buf, 100, 0);
         char buf3[50];
          strcpy(buf3,"rm ");
         strcpy(buf3+strlen(buf3),buf2);
          strcpy(buf3+strlen(buf3),"/");
         strcpy(buf3+strlen(buf3),buf);


        FILE *fp1;
        char file_name[50];
        strcpy(file_name,buf2);
        strcpy(file_name+strlen(file_name),"/");

        strcpy(file_name+strlen(file_name),"show_log.txt");

        fp1=fopen(file_name,"a+");
        if(fp1==NULL)
          printf("ERROR IN SHOW LOG\n");
        char f[50];
        format_time(f);
        fprintf(fp1, " %s %s  %s\n",buf,f,"DELETED");
        fclose(fp1);


         int c=0;
         int a = WEXITSTATUS(system(buf3));
         if(a!=-1)
           c=1;

          send(cl.sockno, &c, sizeof(int), 0);

          pthread_mutex_unlock(&mutex);

      }


      else if(!strcmp(command, "ln"))
      {
         pthread_mutex_lock(&mutex);
         recv(cl.sockno, buf, 100, 0);
         char user[101];
         char new[101];
         char new1[101];
         char data[101];   
        recv(cl.sockno,user,100,0);

         strcpy(data,buf);
        
        strcpy(new1,buf2);
        strcpy(new,"/home/kushpal/Desktop/CN/SERVER/");
        
        strcpy(new+strlen(new),user);
        strcpy(new+strlen(new),"/");
        strcpy(new1+strlen(new1),"/");
        strcpy(new1+strlen(new1),buf);
        int i=0;


        for ( i = 0; i < strlen(buf); ++i)
        {
          if(buf[i]=='.')
            break;
        }
        buf[i+1]='\0';

     

        strcpy(buf+strlen(buf),"symlink");
       strcpy(new+strlen(new),buf);

       // printf("new1=%s new=%s\n",new1,new);
 
         int c=0;
        if(symlink(new1,new)==-1)
          printf("Error in symlink");
        else{
          c=1;
    FILE *fp1;
        char file_name[50];
        strcpy(file_name,buf2);
        strcpy(file_name+strlen(file_name),"/");

 /* LOG FILE */

        strcpy(file_name+strlen(file_name),"show_log.txt");

        fp1=fopen(file_name,"a+");
        if(fp1==NULL)
          printf("ERROR IN SHOW LOG\n");
        char f[50];
        format_time(f);
        fprintf(fp1, " %s %s  %s \n",data,f,"SHARED");
        fclose(fp1);



        }
        send(cl.sockno, &c, sizeof(int), 0);
      
pthread_mutex_unlock(&mutex);
      }

          else if(!strcmp(command,"get"))
      {
        pthread_mutex_lock(&mutex);

        sscanf(buf, "%s%s", filename, filename);
        stat(filename, &obj);
        filehandle = open(filename, O_RDONLY);
        size = obj.st_size;
        if(filehandle == -1)
            size = 0;
        send(cl.sockno, &size, sizeof(int), 0);
        if(size)
        sendfile(cl.sockno, filehandle, NULL, size);

           int c = 0, len,k=0;
  
    char fg[50];

    for(k=strlen(filename)-1;k>=0;k--)
    {
      if(filename[k]=='/')
        break;
    }
     for (int i = k+1; i <strlen(filename); ++i)
     {
    
       fg[c++]=filename[i];
     }
      fg[c]='\0';

 FILE *fp1;
        char file_name[50];
        strcpy(file_name,buf2);
        strcpy(file_name+strlen(file_name),"/");

        strcpy(file_name+strlen(file_name),"show_log.txt");

        fp1=fopen(file_name,"a+");
        if(fp1==NULL)
          printf("ERROR IN SHOW LOG\n");
        char f[50];
        format_time(f);
        fprintf(fp1, " %s %s %s\n",fg,f,"DOWNLOADED");
        fclose(fp1);




        pthread_mutex_unlock(&mutex);  
      }
          else if(!strcmp(command, "put"))
            {

              pthread_mutex_lock(&mutex);
        int c = 0, len,k=0;
    char *f;
    char fg[50],fgh[50];
    sscanf(buf+strlen(command), "%s", filename);

    for(k=strlen(filename)-1;k>=0;k--)
    {
      if(filename[k]=='/')
        break;
    }
     for (int i = k+1; i <strlen(filename); ++i)
     {
    
       fg[c++]=filename[i];
     }
      fg[c]='\0';
    
    recv(cl.sockno, &size, sizeof(int), 0);
    i = 1;
    while(1)
      {
        filehandle = open(fg, O_CREAT | O_EXCL | O_WRONLY, 0666);
        if(filehandle == -1)
    {
      
      sprintf(fgh, "%d", i);
      strcpy(fgh+strlen(fgh),fg);
      strcpy(fg,fgh);
      i++;
    }
        else
    break;
      }
    f = malloc(size);
    recv(cl.sockno, f, size, 0);
    c = write(filehandle, f, size);
    close(filehandle);
    send(cl.sockno, &c, sizeof(int), 0);


     FILE *fp1;
        char file_name[50];
        strcpy(file_name,buf2);
        strcpy(file_name+strlen(file_name),"/");

        strcpy(file_name+strlen(file_name),"show_log.txt");
        
        fp1=fopen(file_name,"a+");
        if(fp1==NULL)
          printf("ERROR IN SHOW LOG\n");
        char f1[50];
        format_time(f1);
        fprintf(fp1, " %s %s %s\n",fg,f1,"UPLOADED");
        fclose(fp1);


        pthread_mutex_unlock(&mutex);
            }

          else if(!strcmp(command, "pwd"))
      {
        system("pwd>temp.txt");
        i = 0;
              FILE *f = fopen("temp.txt","r");
              while(!feof(f))
                buf[i++] = fgetc(f);
              buf[i-1] = '\0';
        fclose(f);
              send(cl.sockno, buf, 100, 0);
      }
          else if(!strcmp(command, "cd"))
            {
              if(chdir(buf+3) == 0)
          c = 1;
        else
          c = 0;
              send(cl.sockno, &c, sizeof(int), 0);
            }
     
     
          else if(!strcmp(command, "bye") || !strcmp(command, "quit"))
      {
        printf("USER : %s------>",cl.username );
        printf("FTP server quitting..\n");

        i = 1;
        send(cl.sockno, &i, sizeof(int), 0);
        close(cl.sockno);

        break;
      }

      else if(!strcmp(command, "show"))
      {
        pthread_mutex_lock(&mutex);
        printf("show------------------->\n");
        stat("show_log.txt",&obj);
        size = obj.st_size;
        
        send(cl.sockno, &size, sizeof(int),0);
        filehandle = open("show_log.txt", O_RDONLY|O_CREAT);
        sendfile(cl.sockno,filehandle,NULL,size);
        pthread_mutex_unlock(&mutex);
      }



        }




}


     
int main()
    {
      
     int n=0;
     int sock;
     struct sockaddr_in server;
     struct client_info cl;
  Socket();
  Bind();
  Listen();

  while((sock=Accept())>0){
    printf("USER %d: starting.......\n",n+1);

    pthread_mutex_lock(&mutex);

    inet_ntop(AF_INET, (struct sockaddr *)&server, ip, INET_ADDRSTRLEN);
    printf("%s connected\n",ip);
    cl.sockno = sock;
    strcpy(cl.ip,ip);
    clients[n] = sock;
    n++;
    pthread_create(&recvt,NULL,Start_login,&cl);
   
   pthread_mutex_unlock(&mutex);
     

    }
      return 0;
    }
