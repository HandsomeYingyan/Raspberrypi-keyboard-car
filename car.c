///////car Test program
//// w forward s back a left d right
/// use gpio 11 12 13 15
#include <termio.h>
#include <stdio.h> 
#include <wiringPi.h>
#include <stdlib.h>

int scan()
{
 int in;
 struct termios new_settings;
 struct termios stored_settings;
 tcgetattr(0,&stored_settings);
 new_settings = stored_settings;
 new_settings.c_lflag &= (~ICANON);
 new_settings.c_cc[VTIME] = 0;
 tcgetattr(0,&stored_settings);
 new_settings.c_cc[VMIN] = 1;
 tcsetattr(0,TCSANOW,&new_settings);
 in = getchar();
 tcsetattr(0,TCSANOW,&stored_settings);
 return in;
}


void clean_gpio()
{
	digitalWrite(0, LOW);
	digitalWrite(1, LOW);
	digitalWrite(2, LOW);
	digitalWrite(3, LOW);
}

int main()
{
 int input;
 if(wiringPiSetup() == -1)
 {
	printf("Please run this program as root!\n");
	return -1; 
 }
 pinMode(0,OUTPUT); //11
 pinMode(1,OUTPUT); //12
 pinMode(2,OUTPUT); //13
 pinMode(3,OUTPUT); //15
 while(1)
 {
   input=scan();
   //printf("%d",input);
   if(input == 119)
   {
	   printf("Forward!\n");
           digitalWrite(0, LOW);
           digitalWrite(1, HIGH);
           digitalWrite(2, LOW);
           digitalWrite(3, HIGH);
           system("sleep 0.25");
	   clean_gpio();
   }
   else if(input == 115)
   {
	   printf("Back!\n");
           digitalWrite(0, HIGH);
           digitalWrite(1, LOW);
           digitalWrite(2, HIGH);
           digitalWrite(3, LOW);
           system("sleep 0.25");
	   clean_gpio();
   }
   else if(input == 97)
   {
	   printf("left!\n");
	   digitalWrite(0, LOW);
	   digitalWrite(1, HIGH);
	   digitalWrite(2, HIGH);
	   digitalWrite(3, LOW);
           system("sleep 0.25");
	   clean_gpio();
   }
   else if(input == 100)
   {
	   printf("right!\n");
	   digitalWrite(0, HIGH);
	   digitalWrite(1, LOW);
	   digitalWrite(2, LOW);
	   digitalWrite(3, HIGH);
           system("sleep 0.25");
	   clean_gpio();
   }
   else
   break;
 }
}


