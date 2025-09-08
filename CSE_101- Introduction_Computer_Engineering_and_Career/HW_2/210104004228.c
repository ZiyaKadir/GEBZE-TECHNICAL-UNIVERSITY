#include <stdio.h>   /* Standard input/output definitions */
#include <time.h>
#include <sys/types.h>
#include <stdlib.h> 
#include <stdint.h>   /* Standard types */
#include <string.h>   /* String function definitions */
#include <unistd.h>   /* UNIX standard function definitions */
#include <fcntl.h>    /* File control definitions */
#include <errno.h>    /* Error number definitions */
#include <termios.h>  /* POSIX terminal control definitions */
#include <sys/ioctl.h>
#include <getopt.h>

   void Arduino_Write(int c) 
{ 	
    FILE *file;
    file = fopen("/dev/ttyUSB0","w"); //cihazi açar
    //printf("%c",file);
    fprintf(file,"%d",c); //cihaza yazar
    fclose(file);
}

int Arduino_Read() 
{ 	
    FILE *file;
    file = fopen("/dev/ttyUSB0","r"); //cihazi açar
    int b=0;
    fscanf(file,"%d",&b); 	//cihazdan okur
    fclose(file);
    return b;
}

int main(){
int ptr2,sayi2,i,sayi3;
  int portName = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);
  struct termios options;
  tcgetattr(portName, &options);
  cfsetispeed(&options, B9600);
  cfsetospeed(&options, B9600);
  options.c_cflag |= (CLOCAL | CREAD);
  tcsetattr(portName, TCSANOW, &options);
  //8 bit characters  
  options.c_cflag &= ~CSIZE; /* Mask the character size bits */
  options.c_cflag |= CS8;    /* Select 8 data bits */
  //No parity
  options.c_cflag &= ~PARENB;
  options.c_cflag &= ~CSTOPB;
  
  //Send Take Sample command to arduino
  printf("\t\t ### WELCOME TO THE SERIAL COMMUNICATION PROGRAM ###\n");
  
  printf("\n\t\t### THIS IS GEBZE TECHNICAL UNIVERSITY ARDUINO LAB ###"
       "\n\t\t     ### ZIYA KADIR TOKLUOGLU CSE 101 FIRST FALL TERM ###\n");
  
    printf("\n>>> ARDUINO MENU <<<\n"
  "\n (1) TURN ON THE LED"
    "\n (2) TURN OFF THE LED"
    "\n (3) FLASH THE LED 3 TIMES"
    "\n (4) SQUARE A NUMBER"
    "\n (5) BUTTON PRESS COUNTER"
    "\n (0) EXIT\n");
    
    while(1)
   {   
  	 int c;
        scanf("%d",&c);
        if (c<4 && c>0){
        
        Arduino_Write(c);
        printf("%d\n",c);
        }
        if(c==4) {
          int sayi;
          char enter[]="\n";
          char ptr[] = "3";

                    printf("\nENTER A NUMBER: ");
       	    scanf("%s",ptr);
     		 	 write(portName,ptr,1);
      			 write(portName,enter,1) ;

    		  sleep(3);
      			  //printf("\nTHE RESULT IS ");
 		 sayi=read(portName, ptr,64);
  ptr[sayi] = 0;
  
  printf(" sonuc %s", ptr);
  }
  if(c==5) { 
   char ptr2[] = "3";
   printf("kaça kadar saymak istersiniz?");
   scanf("%d",&sayi2);
  
     for(i=1;i<sayi2;i++){

                  sleep(2);
       
  sayi3=read(portName, ptr2,64);
  ptr2[sayi3] = 1;

  printf(" %s\n",ptr2);
  }
  }
   
    
    }
return 0;
}
