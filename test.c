#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <string>

using namespace std;

struct Forbidden_str
{
	char c0, c1, c2, c3, c4, c5, c6;
};

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
	   		printf("opened forbidden file %s\n", argv[1] );
	 	else
	   	{  	printf("cannot open forbidden file %s\n", argv[1] );
	  		exit( 0 );
	   	}
	}

   	/* read the number of 1st line */
   	int LENGTH, NUMBER;
   	fscanf(forbidden, "%d %d\n", &LENGTH, &NUMBER);
   	printf("LENGTH: %d, NUMBER: %d\n", LENGTH, NUMBER);


	/* forbidden string */
	/* find the minimum prime number */
	unsigned int prime = LENGTH*NUMBER; // could replace by 400000 * 7
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
   	vector<int> hash_table;
   	hash_table.resize(prime);
   	vector<string> forbidden_str;
   	forbidden_str.resize(prime);
   	printf("hash size is: %ld\n", hash_table.size());
   	printf("forbidden size is: %ld\n", forbidden_str.size());

   	char ch[LENGTH];
   	string tmp;
   	int hash_val=0;
   	int count=0;
   	while(!feof(forbidden)){
   		fscanf(forbidden, "%c%c%c%c%c%c%c\n", &ch[0],&ch[1],&ch[2],&ch[3],&ch[4],&ch[5],&ch[6]);
   		for(int i=0; i<LENGTH; i++){
   			tmp[i] = ch[i];
   		}
   		//printf("%s\n", tmp.c_str());
   		count++;

   		for(int i=0; i<LENGTH; i++){
   			hash_val = ( hash_val + int(tmp[i] * pow(89, (LENGTH-1-i)) ) ) % prime;
   		}
   		//printf("%d\n", hash_val);

   		// need to consider collision
   		while(hash_table[hash_val] != 0){
   			hash_val += 1;
   			hash_val = hash_val % prime;
   		}
   		// hash_table[tmp_val] == 0
   		hash_table[hash_val] = hash_val;
   		forbidden_str[hash_val] = tmp;   		
 	}
	printf("count is %d\n", count);
	fclose(forbidden);

	/* compare sample txt */
	char c;
	int hash_est, hash_next;
	int str_count=0;
	int index=0;
	/* initialization */
	for(int i=0; i<LENGTH; i++){
		c = fgetc(sample);
		ch[i] = c;
		hash_est = ( hash_est + int(c * pow(89, (LENGTH-1-i)) ) ) % prime;
   	}
   	hash_next = hash_est;

   	printf("hash_est is %d\n", hash_est);
   	// compare procedure
   	if(hash_table[hash_est] == 0){ // value not exist
   		printf("None\n");
   	}
   	else if(hash_table[hash_est] == hash_est){ // value equal
   		int i=0;
   		for(i=0; i<LENGTH; i++){
   			if(forbidden_str[hash_est][i] != ch[i]){
   				break;
   			}
   		}
   		if(i == LENGTH-1){
   			printf("forbidden substring: %s\n", ch);
   			str_count++;
   		}
   		else{ // need to check next(collision)
   			while(hash_table[hash_est] != 0){
   			hash_est = (hash_est + 1) % prime;
   			int i=0;
	   		for(i=0; i<LENGTH; i++){
	   			if(forbidden_str[hash_est][i] != ch[i]){
	   				break;
	   			}
	   		}
	   		if(i == LENGTH-1){
	   			printf("forbidden substring: %s, start position: %d\n", ch, index);
	   			str_count++;
	   			}
   			}
   			printf("None\n");
   		} 

   	}
   	else{ // value not equal, check next(collision)
   		while(hash_table[hash_est] != 0){
   			hash_est = (hash_est + 1) % prime;
   			int i=0;
	   		for(i=0; i<LENGTH; i++){
	   			if(forbidden_str[hash_est][i] != ch[i]){
	   				break;
	   			}
	   		}
	   		if(i == LENGTH-1){
	   			printf("forbidden substring: %s, start position: %d\n", ch, index);
	   			str_count++;
	   		}
	   		printf("None\n");
   		}
   	}

	while(!feof(sample)){
		//printf("%c", c);
		hash_est = hash_next;
		int diff = ch[0];
		for(int j=0; j<LENGTH; j++){
			diff = diff * 89 % prime;
		}
		//printf("diff is %d\n", diff);
		c = fgetc(sample);
		index++;
		hash_est = ((hash_est + prime + int(c)) % prime + diff ) % prime;
		hash_next = hash_est;
		//printf("%d\n", hash_est);
		
		/* update ch[LENGTH] */
		for(int j=0; j<LENGTH; j++){
			ch[0] = ch[1];
			ch[1] = ch[2];
			ch[2] = ch[3];
			ch[3] = ch[4];
			ch[4] = ch[5];
			ch[5] = ch[6];
			ch[6] = c;
		}

		// compare procedure
	   	if(hash_table[hash_est] == 0){ // value not exist
	   		printf("None\n");
	   	}
	   	else if(hash_table[hash_est] == hash_est){ // value equal
	   		int i=0;
	   		for(i=0; i<LENGTH; i++){
	   			if(forbidden_str[hash_est][i] != ch[i]){
	   				break;
	   			}
	   		}
	   		if(i == LENGTH-1){
	   			printf("forbidden substring: %s\n", ch);
	   			str_count++;
	   		}
	   		else{ // need to check next(collision)
	   			while(hash_table[hash_est] != 0){
	   			hash_est = (hash_est + 1) % prime;
	   			int i=0;
		   		for(i=0; i<LENGTH; i++){
		   			if(forbidden_str[hash_est][i] != ch[i]){
		   				break;
		   			}
		   		}
		   		if(i == LENGTH-1){
		   			printf("forbidden substring: %s, start position: %d\n", ch, index);
		   			str_count++;
		   			}
	   			}
	   			printf("None\n");
	   		} 

	   	}
	   	else{ // value not equal, check next(collision)
	   		while(hash_table[hash_est] != 0){
	   			hash_est = (hash_est + 1) % prime;
	   			int i=0;
		   		for(i=0; i<LENGTH; i++){
		   			if(forbidden_str[hash_est][i] != ch[i]){
		   				break;
		   			}
		   		}
		   		if(i == LENGTH-1){
		   			printf("forbidden substring: %s, start position: %d\n", ch, index);
		   			str_count++;
		   		}
		   		printf("None\n");
	   		}
	   	}

	}
	printf("Total number of forbidden substring is: %d\n", str_count);
}