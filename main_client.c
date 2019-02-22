#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
int main() 
{ 
        
    system("gcc client.c -lpthread Headerfile.h network.c signup.c signin.c interface.c Communication.c -o client");
        
    system("./client");
       
      
    return 0; 
} 
