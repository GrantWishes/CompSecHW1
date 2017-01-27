#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

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

	fread(&amount, sizeof(int), 1, inFile);

	printf("Buffer test: %d\n", amount);
	fprintf(outFile, "%d\n", amount);

//	for(int i = 0; i < amount; i++) {
		fread(&size, sizeof(int), 1, inFile);
		printf("Length in bytes is %d\n", size);
		fprintf(outFile, "%d", (2 * size) + 2);
		//buffer = malloc();
		for(int j = 0; j < (size / 4); j++) {
			fread(&buffer, 1, 1, inFile);
			printf("Buffer value: %u\n", buffer);
		}
//	}
	
	
	

	return 0;
}
