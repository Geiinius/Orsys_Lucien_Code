.data
tab1: .word 12,50,20,11,7
N1: .word 5
tab2: .word 8,11,13,-9,-11,10
N2: .word 6
Somme: .word 0

.text
.global main
main:
@ partie 1

ldr r0,=tab1
ldr r1,=N1
ldr r1,[r1]
bl ROUTINE
@ à ce stade, r2 contient la somme des valeurs de tab1
mov r4,r2

@ partie 2

ldr r0,=tab2
ldr r1,=N2
ldr r1,[r1]
bl ROUTINE
@ à ce stade, r2 contient la somme des valeurs de tab2
add r4,r4,r2
ldr r3,=Somme
str r4,[r3]

@ fin

mov r0,#0
mov r7,#1
svc 0


ROUTINE:
stmfd sp!,{r0,r1,r3,r14}
mov r2,#0

ROUTINE_WHILE:
cmp r1,#0
beq ROUTINE_END

ldr r3,[r0],#4
add r2,r2,r3
sub r1,r1,#1

b ROUTINE_WHILE

ROUTINE_END:
ldmfd sp!,{r0,r1,r3,r15}
