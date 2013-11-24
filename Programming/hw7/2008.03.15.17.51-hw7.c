#include<stdio.h>
#define size 1000
 char cond[size]={'\0'};
 char sour[size]={'\0'};

int main()
{
 FILE *fptr1;
 FILE *fptr2;
 
 fptr2 = fopen("hw7_out.txt", "w");
 
 if( ( fptr1 = fopen("hw7_in.txt", "r") ) == NULL )
 {
  	 printf( "File could not be opened\n" ); 	 
 }
 else
 {
  	 printf("Please enter the keyword: ");
 	 scanf("%s",&cond);
 	 
 	 while( !feof( fptr1 ) )
     {
 	  fgets(sour, 100, fptr1) ;

 	  if( strstr(sour, cond) != NULL )
	   {  
 	   	  fputs(sour,fptr2);
	   }	   
	 } 	  	 	 
     fclose (fptr1);   	  	 
 }
 
 return 0;	
}
