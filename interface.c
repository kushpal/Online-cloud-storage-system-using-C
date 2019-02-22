#include "Headerfile.h"
  int Interface(){

      printf("|+++------------------------------------------------------------------+++|\n");
      printf("|+++------------------------------------------------------------------+++|\n");
      printf("|+++---------------WELCOME TO THE CLOUD STORAGE SYSTEM----------------+++|\n");
      printf("|+++------------------------------------------------------------------+++|\n");
      printf("|+++------------------------------------------------------------------+++|\n");
      printf("|                                                                        |\n");
      printf("|                                                                        |\n");
      printf("|                                                                        |\n");
      printf("|               PRESS 1 : >>>>>> |           SIGNUP         |            |\n");
      printf("|               PRESS 2 : >>>>>> |           SIGNIN         |            |\n");
      printf("|               PRESS 3 : >>>>>> | TO KNOW ABOUT THE SYSTEM |            |\n");
      printf("|               PRESS 4 : >>>>>> |           TO QUIT        |            |\n");
      printf("|                                                                        |\n");
      printf("|                                                                        |\n");
      printf("|                                                                        |\n");
      printf("|+++------------------------------------------------------------------+++|\n");
      printf("|+++------------------------------------------------------------------+++|\n");
      int in;
      scanf("%d",&in);
      if(in==4)
        exit(0);
      if(in==1 || in==2 || in==3)
        return in;
      else
      {
          printf("\n ENTER THE VALID  NUMBER \n\n");
          Interface();
        }
        
      

  }
