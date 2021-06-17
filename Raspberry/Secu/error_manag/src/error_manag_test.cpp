#include <iostream>
#include <vector>
#include <string>

#define MAXVALUE 1023
#define ERR_NULL -1
#define ERR_TOOBIG -2

char* func(const char *s) {
int c=0,i,err_val=0;
char* sl=NULL;
sl = (char*) malloc(sizeof(char)*MAXVALUE);
if (s == NULL || sl == NULL) {
err_val = ERR_NULL;
goto ERR_HANDLER;
}
for (i = 0; i < MAXVALUE; i++) {
sl[i] = s[i];
if (s[i] == '\0')
return sl;
}
err_val = ERR_TOOBIG;
ERR_HANDLER:
if (sl != NULL)
free(sl);
if(err_val == -1)
throw std::runtime_error("pointeur null");
else
throw std::runtime_error("trop grand");
return NULL;
}

int main(){

const char* s1 = "taupe";
try{
char* s2 = func(s1);
}catch(int a){

}
}
