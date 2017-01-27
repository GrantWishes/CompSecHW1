#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

	/* Checking arguments and the such */
	if(argc != 3) {
		fprintf(stderr, "Incorrect amount of arguments\n");
		exit(1);
	}

	FILE* inFile;
	FILE* outFile;
	
	inFile = fopen(argv[1],"rb");
	outFile = fopen(argv[2],"w");
	
	if(inFile == NULL || outFile == NULL) {
		fprintf(stderr, "Error opening file");
		exit(1);
	}

	unsigned char buffer;
	int amount;
	int size;
	/* Why didn't I think of this when I was doing part one??? */
	char hexchars[] = "0123456789ABCDEF";
	
	fread(&amount, sizeof(int), 1, inFile); // read in how many numbers

	//printf("Buffer test: %d\n", amount);
	fprintf(outFile, "%d\n", amount);

	
	for(int i = 0; i < amount; i++) {
		// How many bytes it will be
		fread(&size, sizeof(int), 1, inFile);
		//printf("Length in bytes is %d\n", size);
		fprintf(outFile, "%d 0X", (2 * size) + 2);
		for(int j = 0; j < size ; j++) {
			// Read in a byte
			fread(&buffer, 1, 1, inFile);
			// Convert to hex
			fprintf(outFile, "%c", hexchars[buffer/16]);
			fprintf(outFile, "%c", hexchars[buffer%16]);			
		}
		fprintf(outFile, "\n");
	}
	
	return 0;
}
