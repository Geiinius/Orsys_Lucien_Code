#include <cstdio>

int main()
{
	char *str =(char*) "Ceci est un test.";
	char outBuf[255];
	int len;
	asm (
		"MOV R4, %2\n"
		"loop: LDRB R5, [%1], #1\n"
		"CMP R5, #'z'\n"
		"BGT cont\n"
		"CMP R5, #'a'\n"
		"BLT cont\n"
		"SUB R5, #('a'-'A')\n"
		"cont: STRB R5, [%2], #1\n"
		"CMP R5, #0\n"
		"BNE loop\n"
		"SUB %0, %2, R4\n"
		: "=r" (len)
		: "r" (str), "r" (outBuf)
		: "r4", "r5"
	);
	printf("Chaine str: %s\n", str);
	printf("Chaine de sortie : %s\n", outBuf);
	printf("Longueur de la chaine de sortie len = %d\n", len);
		return(0);
}
