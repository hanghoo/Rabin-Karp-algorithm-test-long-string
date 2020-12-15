/* compiles with command line  g++ test.c */
/* run with command line  ./a.out sample.txt forbidden.txt */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <string>

using namespace std;

int LENGTH, NUMBER;


int is_prime(int a){
	int a_sqrt, i;
	a_sqrt = (int)sqrt((double)a);
	for(i=2; i<=a_sqrt; i++){
		if(a%i==0){
			break;
		}
	}

	if(i>a_sqrt){
		//printf("%d is prime.\n", a);
		return 1;
	}
	else{
		//printf("%d isn't prime.\n", a);
		return 0;
	}
}

int customize_pow(int a, int b, int prime){
	int value = 1;
	for(int i=0; i<b; i++){
		value = value * a % prime;
	}
	return value;
}


void creat_hash(FILE *forbidden, int prime, int *hash_table, string *forbidden_str){
	char ch[LENGTH];
   	string tmp;   	
   	int count=0;
   	int length, number;
   	fscanf(forbidden, "%d %d\n", &length, &number);
   	while(!feof(forbidden)){
   		fscanf(forbidden, "%s\n", ch);
   		tmp = ch;
   		//printf("%s\n", tmp.c_str()); 
   		int hash_val=0;  		
   		count++;
   		for(int i=0; i<LENGTH; i++){
   			hash_val = hash_val + int( tmp[i] * customize_pow(256, (LENGTH-1-i), prime) );	
   		}
   		hash_val = hash_val % prime;
   		//printf("hash_val %d\n", hash_val);
   			   	
   		// need to consider collision
   		while(hash_table[hash_val] != 0){
   			hash_val += 1;
   			hash_val = hash_val % prime;
   		}
   		hash_table[hash_val] = hash_val;
   		forbidden_str[hash_val] = tmp;  
   		//printf(" hash table value is %d forbidden string is %s\n", hash_table[hash_val], forbidden_str[hash_val].c_str());
 		//break;
 	}

   	printf("count is %d\n", count);
}


void search_forbidden(FILE *sample, int prime, int *hash_table, string *forbidden_str){
	char c;
	char ch[LENGTH];
	int hash_est=0; 
	int hash_next=0;
	int str_count=0;
	int index=0;

	/* initialization */
	for(int i=0; i<LENGTH; i++){
		c = fgetc(sample);
		ch[i] = c;
		hash_est = hash_est + int( c * customize_pow(256, (LENGTH-1-i), prime) );
   	}
   	hash_est = hash_est % prime;
   	hash_next = hash_est;
	//printf("ch[] is %s\n", ch);
   	//printf("hash_est1 is %d\n", hash_est);

   	// compare procedure
   	if(hash_table[hash_est] == 0){ // value not exist
   	}
   	else if(hash_table[hash_est] == hash_est){ // value equal
   		int idx=0;
   		for(int i=0; i<LENGTH; i++){
   			if(forbidden_str[hash_est][i] != ch[i]){
   				break;
   			}
   			idx++;
   		}
   		if(idx == LENGTH && forbidden_str[hash_est][LENGTH-1] == ch[LENGTH-1]){
   			//printf("I come here\n");
   			printf("forbidden substring: %s, start position: %d\n", ch, index);
   			str_count++;
   		}
   		else{ // need to check next(collision)
   			printf("I come here else\n");
   			while(hash_table[hash_est] != 0){
   			hash_est = (hash_est + 1) % prime;
   			int idx=0;
	   		for(int i=0; i<LENGTH; i++){
	   			if(forbidden_str[hash_est][i] != ch[i]){
	   				break;
	   			}
	   			idx++;
	   		}
	   		if(idx == LENGTH && forbidden_str[hash_est][LENGTH-1] == ch[LENGTH-1]){
	   			printf("forbidden substring: %s, start position: %d\n", ch, index);
	   			str_count++;
	   			}
   			}
   		} 

   	}
   	else{ // value not equal, check next(collision)
   		while(hash_table[hash_est] != 0){
   			hash_est = (hash_est + 1) % prime;
   			int idx=0;
	   		for(int i=0; i<LENGTH; i++){
	   			if(forbidden_str[hash_est][i] != ch[i]){
	   				break;
	   			}
	   			idx++;
	   		}
	   		if(idx == LENGTH && forbidden_str[hash_est][LENGTH-1] == ch[LENGTH-1]){
	   			printf("forbidden substring: %s, start position: %d\n", ch, index);
	   			str_count++;
	   		}
   		}
   	}

   	/* enrolling hash function */
	while(!feof(sample)){
		hash_est = hash_next;
		//printf("hash_est2 is %d\n", hash_est);
		c = fgetc(sample);
		//printf("%c", c);
		index++;
		hash_est = ( (hash_est + prime - int(ch[0] * customize_pow(256, (LENGTH-1), prime) ) % prime ) * 256 + int(c) ) % prime;
		hash_next = hash_est;
		//printf("hash_est3 is %d\n", hash_est);
		
		/* update ch[LENGTH] */
		ch[0] = ch[1];
		ch[1] = ch[2];
		ch[2] = ch[3];
		ch[3] = ch[4];
		ch[4] = ch[5];
		ch[5] = ch[6];
		ch[6] = c;
		// break;

		// compare procedure
	   	if(hash_table[hash_est] == 0){ // value not exist
	   		//printf("None\n");
	   	}
	   	else if(hash_table[hash_est] == hash_est){ // value equal
	   		int idx=0;
	   		for(int i=0; i<LENGTH; i++){
	   			if(forbidden_str[hash_est][i] != ch[i]){
	   				break;
	   			}
	   			idx++;
	   		}
	   		if(idx == LENGTH && forbidden_str[hash_est][LENGTH-1] == ch[LENGTH-1]){
	   			printf("forbidden substring: %s, start position: %d\n", ch, index);
	   			str_count++;
	   		}
	   		else{ // need to check next(collision)
	   			while(hash_table[hash_est] != 0){
	   			hash_est = (hash_est + 1) % prime;
	   			int idx=0;
		   		for(int i=0; i<LENGTH; i++){
		   			if(forbidden_str[hash_est][i] != ch[i]){
		   				break;
		   			}
		   			idx++;
		   		}
		   		if(idx == LENGTH && forbidden_str[hash_est][LENGTH-1] == ch[LENGTH-1]){
		   			printf("forbidden substring: %s, start position: %d\n", ch, index);
		   			str_count++;
		   			}
	   			}
	   			//printf("None\n");
	   		} 

	   	}
	   	else{ // value not equal, check next(collision)
	   		while(hash_table[hash_est] != 0){
	   			hash_est = (hash_est + 1) % prime;
	   			int idx=0;
		   		for(int i=0; i<LENGTH; i++){
		   			if(forbidden_str[hash_est][i] != ch[i]){
		   				break;
		   			}
		   			idx++;
		   		}
		   		if(idx == LENGTH && forbidden_str[hash_est][LENGTH-1] == ch[LENGTH-1]){
		   			printf("forbidden substring: %s, start position: %d\n", ch, index);
		   			str_count++;
		   		}
		   		//printf("None\n");
	   		}
	   	}

	}
	printf("Total number of forbidden substring is: %d\n", str_count);
}



int main(int argc, char **argv){
	/* check the argv */
	FILE *sample;
	FILE *forbidden;
	if( argc == 3 )
	{	
	 	sample = fopen( argv[1], "r");
	 	if( sample != NULL )
	   		printf("opened sample file %s\n", argv[1] );
	 	else
	   	{  	printf("cannot open sample file %s\n", argv[1] );
	  		exit( 0 );
	   	}

	   	forbidden = fopen(argv[2], "r");
	   	if( forbidden != NULL )
	   		printf("opened forbidden file %s\n", argv[2] );
	 	else
	   	{  	printf("cannot open forbidden file %s\n", argv[2] );
	  		exit( 0 );
	   	}
	}

   	/* read the number of 1st line */   	
   	fscanf(forbidden, "%d %d\n", &LENGTH, &NUMBER);
   	printf("LENGTH: %d, NUMBER: %d\n", LENGTH, NUMBER);


	/* forbidden string */
	/* find the minimum prime number */
	unsigned int prime = LENGTH*NUMBER; // replace by 400000 * 7
	int is_loop = 0;
	while(1){
		is_loop = is_prime(prime);
		if(is_loop == 1){
			break;
		}
		else{
			prime++;
		}
	}
	printf("Minimum prime number is: %d\n", prime);

	/* creat harsh table */   	
   	int* hash_table;
   	string* forbidden_str;
   	hash_table = (int *)malloc(prime * sizeof(int));
   	forbidden_str = new string[prime];

   	/* creat hash table */
   	creat_hash(forbidden, prime, hash_table, forbidden_str);
   	fclose(forbidden);  

	/* compare sample txt */
	search_forbidden(sample, prime, hash_table, forbidden_str);
	fclose(sample);

	free(hash_table);
	delete [] forbidden_str;	
}