#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUMBER 1000000
int main(int argc, char **argv)
{  FILE * fp; int i,j; time_t t; char c1,c2;
   fp = fopen("sample.txt", "w");
   if( argc>1 )
   {  sscanf(argv[1], "%d", &j);
      if( j%2==1 ) {printf("position must be even"); exit(0);}
   }
   else
     j = NUMBER +1;
   srand( (unsigned) time(&t));
   for( i=0; i< NUMBER; )
     { if(i==j){ fprintf(fp, "abbbbba"); i+=7;}
       else
	 { c1 = (char) (( (int)'a') + (rand()%20) );
	   c2 = (char) (( (int)'b') + (rand()%10) );
	 fprintf(fp, "%c%c", c1, c2);
	 i+=2;
       }
     }
   fclose(fp);
   return(1);
}
