#include <stdio.h>

void itoa(int val, int base, char* input, size_t at, size_t input_size){
    int i = 30;

    for(; val && i ; --i, val /= base)

        buf[i] = "0123456789abcdef"[val % base];

    return &buf[i+1];

}


int main()
{
	
	getchar();
	return 0;
}
