#include <thread>
#include <chrono>
#include <cstdio>
#include <iostream>
int main(int argc, char *argv[]) {
uint16_t vec1[]={1,2,3,4,5,6,7,8};
uint16_t vec2[]={1,2,3,4,5,6,7,8};
uint16_t result[8];
srand((unsigned)time(0));
auto time_t1=std::chrono::high_resolution_clock::now();
for (int i=0;i<100000;i++){
vec1[i%4]=rand()%1000;
vec2[i%4]=rand()%1000;

asm(
"VLDM %0,{Q0}\n"
"VLDM %1,{Q1}\n"
"VADD.I16 Q2,Q0,Q1\n"
"VSTMIA %2,{Q2}\n"
:
:"r" (vec1),"r"(vec2),"r"(result)
:
);

}
auto time_t2=std::chrono::high_resolution_clock::now();
auto duration=std::chrono::duration_cast<std::chrono::milliseconds>(time_t2 - time_t1);
std::cout<<"Temps en ms : "<<duration.count()<<std::endl;
for (int i=0;i<8;i++) {
printf("%d\n",result[i]);
}
return 0;
}
