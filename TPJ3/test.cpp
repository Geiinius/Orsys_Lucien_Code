#include <iostream>
extern "C" void mytoupper(char*, char*);

int main(){

char s1[]= "Bonjour";
char s2[8];


mytoupper(s1, s2);

std::cout << s2 << std::endl;
return 0;
}
