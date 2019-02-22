#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
int main() 
{ 
        
        system("gcc -Wall -Wextra -pedantic -pthread server.c -pthread ServerHeader.h Server_Network_file.c Start_login.c Validation.c -o server");
        
        system("./server");
       
      
    return 0; 
} 
