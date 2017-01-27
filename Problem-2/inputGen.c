#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

int main (int argc, char *argv[])
{

	if(argc != 2){
		printf("Missing command line arguments\n");
		return 0 ; 
	}

  FILE * fout = fopen(argv[1], "wb"); 
  if(!fout){
  	printf("Cannot open output file %s\n",argv[1]);
  	return 0 ; 
  }
  

  int iSecret, iGuess;

  /* initialize random seed: */
  srand (time(NULL));
  
  int len = rand() % 500 + 50;
  fwrite(&len, sizeof len, 1, fout) ; 
  printf("Found length: %d\n",len); 
  int i ; 
  for(i=0;i<len;++i){
  	int bin_len = rand() % 100 + 10;
  	printf("Generated len: %d\n",bin_len);
  	fwrite(&bin_len, sizeof bin_len, 1, fout) ; 
  	int j ; 
  	for(j=0;j<bin_len;++j)
  	{
  		unsigned char c = (unsigned char) (rand()%256) ; 
  		fwrite(&c, sizeof c, 1, fout) ; 
  	}
  
  }
  
  fclose(fout); 
  return 0;
}
