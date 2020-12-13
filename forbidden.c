#include <stdio.h>

/*don't change*/
#define NUMBER 400000
#define LENGTH 7
int main()
{  FILE * fp; char c1,c2,c3,c4,c5; int i1, i2, i3, i4, i5;
   fp = fopen("forbidden.txt", "w");
   fprintf(fp, "%d %d\n", LENGTH, NUMBER );
   for(i1=0; i1 < 20; i1++)
     for(i2=0; i2 < 10; i2++)
       for(i3=0; i3 < 10; i3++)
	 for(i4=0; i4 < 10; i4++)
	   for(i5=0; i5 < 20; i5++)
	     {  c1 = (char) (( (int)'b') + i1);
	        c2 = (char) (( (int)'a') + i2);
		c3 = (char) (( (int)'b') + i3);
		c4 = (char) (( (int)'a') + i4);
		c5 = (char) (( (int)'b') + i5);
		fprintf(fp, "a%c%c%c%c%ca\n",c1,c2,c3,c4,c5 );
	     }
   return(1);
}
