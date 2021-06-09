#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdint.h>
#define GPIO_BASE 0x3F200000

static volatile uint32_t *gpio;

extern "C" void SORTIE(uint32_t*);
extern "C" void ALLUMER(uint32_t*);
extern "C" void ETEINDRE(uint32_t*);

int main() {
int fd, x;

if(getuid()!=0) {
printf("You must run this program as root\n");
return -1;
}

if ((fd=open("/dev/mem", O_RDWR | O_SYNC)) < 0) {
printf("Unable to open /dev/mem\n");
return -1;
}

// Le pointeur gpio pointe indirectement sur les registres GPIO

gpio=(uint32_t *)mmap(0, getpagesize(), PROT_READ|PROT_WRITE,
MAP_SHARED, fd, GPIO_BASE);
if ((int32_t) gpio < 0) {
printf("Memory mapping failed\n");
return -1;
}

SORTIE((uint32_t *)gpio);
while(1) {
ALLUMER((uint32_t*)gpio);
sleep(1);
ETEINDRE((uint32_t*)gpio);
sleep(1);
}
}
