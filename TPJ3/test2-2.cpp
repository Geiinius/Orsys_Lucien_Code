#include <cstdio>
int main()
{
int x=15;
int y=10;
printf("avant : val x %d val y %d\n",x,y);
asm (
"MOV R4, %0\n"
"MOV R5, %1\n"
"MOV %3, R4\n"
"MOV %2, R5\n"

: "=r"(x), "=r"(y)
: "r"(x), "r"(y)
: "r4", "r5");

printf("val x %d val y %d\n",x,y);
return(0);
}
