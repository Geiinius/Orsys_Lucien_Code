#include <cstdlib>
#include <cstdio>
#include <cstring>

//si sstr est trop grand, la copie continuera apres buffer
//et ira apres ecraser les donnees (notemment le retour a la fonction main
//a la fin de la fonction foo)
int foo(char *sstr)
{
 char buffer[100];
 printf("%p\n",&buffer[0]);
 strcpy(buffer, sstr); //ecrasement des donnee stack si len(str)>len(buffer)
 return 0;
}

int main(int argc, char **argv)
{
 char str[400];
 FILE *badfile;
 badfile = fopen("badfile", "r");
 fread(str, sizeof(char), 300, badfile);//fichier contenant le code bin asm
 fclose(badfile);
 foo(str);//enregistrement de @printf dans la stack puis execution de foo
 printf("Returned properly!\n");//fonction bypassed si la faille est exploite
 return 0;//la fonction n'est donc plus exectué mais le SP suis les nouvelles
²	  //instructions
}
