#include <iostream>
#include <memory>
#define MAXVALUE 1023
#define ERR_NULL -1
#define ERR_TOOBIG -2
struct Task
{
int mId;
Task(int id ) :mId(id)
{
std::cout<<"Task::Constructor"<<std::endl;
}
~Task()
{
std::cout<<"Task::Destructor"<<std::endl;
}
};

std::unique_ptr<char[]> func(const char *s) {
int c=0,i,err_val=0;
auto sl = std::make_unique<char[]>(MAXVALUE);
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
if(err_val == -1)
throw std::runtime_error("pointeur null");
else
throw std::runtime_error("trop grand");
return NULL;
}
int main()
{
const char* s = "bonjour mewan";
auto copie = func(s);
std::cout<<copie[0]<<std::endl; //probleme d'affichage, cela affiche que le premier caractere
return 0;
}
