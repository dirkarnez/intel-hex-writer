#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void decimalToHexChar(unsigned char zero_to_255, char* input, size_t at, size_t input_size){
	char hexChars[] = "0123456789ABCDEF";
	if (at < input_size) {
		input[at] = hexChars[(zero_to_255 >> 4) % 16];
		at++;
	}

	if (at < input_size - 1) { // left last char for '\0' inserted by memset
		input[at] = hexChars[(zero_to_255 & 0b00001111) % 16];
	}
}

unsigned char checksum(unsigned char* code_without_ending_checksum, input_size){
	 //= { 0x04,0x02,0x0E,0x00, 0x48, 0x64, 0x00, 0x00 };
	int sum = 0;
	for (int i = 0; i < input_size; i++) {
		sum += code_without_ending_checksum[i];
	}

	return ((~sum + 1) & 0xFF)
}

int main()
{
	const size_t size = 51; // 1 for the invisible \0
	char s[size];
	


	FILE *file;
	
    file = fopen("random.txt", "w");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

	for (int i = 0; i < 10; i++) {
		memset( s, '\0', size * sizeof(char));

		size_t random_length = i + 20; //as long as this length does not overrride '\0' inserted by memset at the end of the string
		for (int j = 0; j < random_length; j += 2) {// overflowed character will not be printed
			decimalToHexChar(i + j, s, j, size); // just some random unsigned char value
			printf("%s", s);
				// 2 because unsigned char takes 2 charactor in hex 0x00 - 0xFF
		}
    	fprintf(file, ":%s\n", s);
	}

	fclose(file);


	/*
	:020000020000FC
	:1000000000E21FEF259A2D9A2FEF2A95F1F72D98F0
	:080010002FEF2A95F1F7F7CF5D
	:00000001FF
	*/
    file = fopen("real.txt", "w");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

	memset( s, '\0', size * sizeof(char)); //clean

	decimalToHexChar(0x02, s, 0, size); // just some random unsigned char value
	decimalToHexChar(0x00, s, 2, size); // just some random unsigned char value
	decimalToHexChar(0x00, s, 4, size); // just some random unsigned char value
	decimalToHexChar(0x02, s, 6, size); // just some random unsigned char value
	decimalToHexChar(0x00, s, 8, size); // just some random unsigned char value
	decimalToHexChar(0x00, s, 10, size); // just some random unsigned char value
	decimalToHexChar(0xfc, s, 12, size); // just some random unsigned char value
	fprintf(file, ":%s\n", s);

	fclose(file);
	return 0;
}
