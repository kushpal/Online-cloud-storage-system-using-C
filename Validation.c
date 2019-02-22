#include "ServerHeader.h"


int check_validation(int k ,char s1[],char s2[]){
char c1[50],c2[50],c4[50],c3[50],m[100];
FILE *fp;
int t2=0;
fp=fopen("/home/kushpal/Desktop/CN/SERVER/login.txt","r");
if(fp==NULL)
  printf("LOGIN ERROR\n");
if(k==0){

while(fgets(m,100,fp)!=NULL)
{
  //printf("m=%s",m);
  sscanf(m,"%s%s%s%s%d",c4,c3,c1,c2,&t2);
  //printf("c1=%s s1=%s c2=%s s2=%s\n",c1,s1,c2,s2);
  if(strcmp(c1,s1)==0 && strcmp(c2,s2)==0)
  {
    //t2=1;
  //fprintf(fp,"%s %s %s %s %d",c4,c3,c1,c2,t2);

      fclose(fp);
      return 1;

  }
}


fclose(fp);
return 0;

}

else
{
while(fgets(m,100,fp)!=NULL)
{
  //printf("m=%s",m);
  sscanf(m,"%s%s%s%s%d",c4,c3,c1,c2,&t2);
  //printf("c1=%s s1=%s c2=%s s2=%s\n",c1,s1,c2,s2);
  if(strcmp(c1,s1)==0){
    fclose(fp);
  return 2;
  }
}
fclose(fp);
return 0;
}


}
