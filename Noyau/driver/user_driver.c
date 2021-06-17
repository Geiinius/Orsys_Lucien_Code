#include <stdio.h>
#include <fcntl.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>

int main(){

    char buf[100] = "parcour embarqué \n";
    char rbuf[100];
    
    int fd =open ("/dev/alten", O_RDWR);
    write (fd, buf, strlen(buf));
    printf ("écriture dans le périphérique\n");
    read(fd, rbuf,100);
    printf("Voilà : %s\n", rbuf);

    return 0;

}
