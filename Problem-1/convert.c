#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BIN2HEX (1)
#define HEX2BIN (2)
#define DEC2BIN (3)
#define DEC2HEX (4)

/* A simple power function to use for decimal conversion */
long power(int base, int exponent) {
	long start = 1;
	for(int i = 0; i < exponent; i++) {
		start = start * base;
	}
	return start;
}

/* I don't know why I chose to write this in C, I still barely know
 * the language. As you can see, my conversion from binary to hex was
 * "interesting", to say the least. */
char dontJudge(char* digit) {

	long sorry = strtol(digit, 0, 10);
	
	//oh god here it goes i just want to use %x or something
	switch(sorry) {
		case 0:		return '0';
		case 1:		return '1'; 
		case 10:  	return '2';
		case 11: 	return '3';
		case 100: 	return '4';
		case 101:	return '5';
		case 110:	return '6';
		case 111:	return '7';
		case 1000:	return '8';
		case 1001: 	return '9';
		case 1010: 	return 'A';
		case 1011:	return 'B';
		case 1100: 	return 'C';
		case 1101: 	return 'D';
		case 1110: 	return 'E';
		case 1111:	return 'F';
		default: return '?';
	}	
}

int main (int argc, char * argv[]) {

	/* Need exactly 4 arguments */
	if(argc != 4) {
		fprintf(stderr,"arguments\n");
		exit(1);
	}

	int conversionType; // made it a number so I could switch on it

	// look at this wonderful logic!
	if(strcmp(argv[1],"bin2hex")==0) {
		conversionType = BIN2HEX;
	} else if (strcmp(argv[1],"hex2bin")==0) {
		conversionType = HEX2BIN;
	} else if (strcmp(argv[1],"dec2hex")==0) {
		conversionType = DEC2HEX;
	} else if (strcmp(argv[1],"dec2bin")==0) {
		conversionType = DEC2BIN;
	} else {
		fprintf(stderr,"Must choose hex2bin, dec2hex, dec2bin, or bin2hex!\n");
		exit(1);
	}

	FILE *inFile;
	FILE *outFile;

	inFile = fopen(argv[2],"r");
	outFile = fopen(argv[3], "w");	

	if(inFile == NULL || outFile == NULL) {
		fprintf(stderr, "Error opening file");
	}

	int numberCount; // bad variable name, but how many numbers are there?

	fscanf(inFile, "%u", &numberCount);
	fprintf(outFile, "%u\n", numberCount);

	//printf("There are %u numbers to be converted\n", numberCount);

	int numLength;	// used for the length of hex/binary numbers
	long number;	// used for story decimal numbers
	char string[1001]; // picked an arbitrary max size, really like 32	
	char *substring = malloc(5); // for binary to hex
	substring[5] = '\0'; 
	char character;

	// Handles all the conversion in here
	switch (conversionType) {

	case BIN2HEX:
		//printf("Bin2Hex branch!\n");
		for(int i = 0; i < numberCount; i++) {
			fscanf(inFile, "%d", &numLength );
			//printf("This number is %d long!\n", numLength);
			fscanf(inFile, "%s", string);
			//printf("The binary number is %s\n", string);
			
			/* Prints the length of the number coming out */
			fprintf(outFile,"%d 0X", (numLength / 4) + 2);

			/* Converts from binary to hex using dontJudge() */
			for(int j = 0; j < numLength / 4; j++) {
				strncpy(substring, string + (4*j), 4);
				//printf("Substring is %s\n", substring);
				fprintf(outFile, "%c", dontJudge(substring));
			}
			fprintf(outFile, "\n");
		}
		break;

	case HEX2BIN:
		//printf("Hex2Bin branch!\n");
		for(int i = 0; i < numberCount; i++) {
			fscanf(inFile, "%d", &numLength );
			//printf("This number is %d long!\n", numLength);
			fscanf(inFile, "%s", string);
			//printf("The hex number is %s\n", string);
			
			fprintf(outFile,"%d ", (numLength-2)*4);

			/* Don't ask... me avoiding writing a function that
 			 * returns a chararcter array/pointer */
			for(int j = 2; j < numLength; j++) { // 2 because ignore 0X
				strncpy(substring, string + j, 1);
				//printf("Substring is %s\n", substring);
				character = substring[0];
				// I'm so sorry
				switch(character) {
					case '0': fprintf(outFile, "%s","0000"); break;
					case '1': fprintf(outFile, "%s","0001"); break;
					case '2': fprintf(outFile, "%s","0010"); break;
					case '3': fprintf(outFile, "%s","0011"); break;
					case '4': fprintf(outFile, "%s","0100"); break;
					case '5': fprintf(outFile, "%s","0101"); break;
					case '6': fprintf(outFile, "%s","0110"); break;
					case '7': fprintf(outFile, "%s","0111"); break;
					case '8': fprintf(outFile, "%s","1000"); break;
					case '9': fprintf(outFile, "%s","1001"); break;
					case 'A': fprintf(outFile, "%s","1010"); break;
					case 'B': fprintf(outFile, "%s","1011"); break;
					case 'C': fprintf(outFile, "%s","1100"); break;
					case 'D': fprintf(outFile, "%s","1101"); break;
					case 'E': fprintf(outFile, "%s","1110"); break;
					case 'F': fprintf(outFile, "%s","1111"); break;

				}
			}
			fprintf(outFile, "\n");
		}
		break;

	case DEC2BIN:
		//printf("Dec2Bin branch!\n");
		for(int i = 0; i < numberCount; i++) {
			fprintf(outFile, "32 ");
			fscanf(inFile, "%ld", &number);
			//printf("The dec number is %ld\n", number);
			if(number == 0) {
				fprintf(outFile, "%032d", 0);
			}
			/* Finds the biggest binary digit we can use
 			 * and works downwards */
			for(int j = 31; j >= 0; j--) {			
				if(number - power(2,j) >= 0) {
					fprintf(outFile, "1");
					number = number - power(2,j);
				} else {
					fprintf(outFile, "0");
				}
			}
			fprintf(outFile, "\n");
		}
		break;

	case DEC2HEX:
		//printf("Dec2Hex branch!\n");
		for(int i = 0; i < numberCount; i++) {
			fprintf(outFile, "10 0X");
			fscanf(inFile, "%ld", &number);
			/* Finds biggest hex digit that can be used */
			for(int j = 7; j >= 0; j--) {
				if(number - power(16,j) >= 0) {
					int quotient;
					quotient = number / power(16,j);
					if(quotient < 10) {
						fprintf(outFile, "%d", quotient);
					} else {
						// For numbers > 9
						switch(quotient) {
							case 10: fprintf(outFile, "A"); break;
							case 11: fprintf(outFile, "B"); break;
							case 12: fprintf(outFile, "C"); break;
							case 13: fprintf(outFile, "D"); break;
							case 14: fprintf(outFile, "E"); break;
							case 15: fprintf(outFile, "F"); break;
							default: printf("Something is super broken"); break;
						}
					}
					number = number % power(16, j);
				} else {
					fprintf(outFile, "0");
				}
			} 
			fprintf(outFile, "\n");
		}
		break;
	
	default:
		printf("Something's gone wrong!");
		exit(1);

	}

	free(substring);
	fclose(inFile);
	fclose(outFile);
	return 0;
}


