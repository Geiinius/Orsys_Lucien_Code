.data
tab: .fill 4 ,4, 0
buff: .word 0
test: .asciz "%d"
format: .asciz "element: %d\n"
size: .word 4
chaine: .asciz "Position: %d\n"
.text
.global main

main:
LDR r8, =size
LDR r8, [r8]
LDR r7, =tab

tantque:
CMP r8, #0
BEQ fin_tantque
STMFD sp!,{r7}
LDR r0, =test
LDR r1, =buff
BL scanf
LDR r1, =buff
LDR r1, [r1]
LDMFD sp!,{r7}
STR r1, [r7], #4
SUB r8, r8, #1
B tantque
fin_tantque:
LDR R8,=size
LDR R8,[R8]
LDR r7,=tab

ldr r0,=tab
ldr r1,=size
ldr r1,[r1]
ldr r2,=format
bl AFFICHER

ldr r0,=tab
ldr r1,=size
ldr r1,[r1]
bl CALCULMAX
ldr r0,=chaine
mov r1,r2
bl printf

ldr r7,=tab
ldr r8,=size
ldr r8,[r8]
boucledecroiss:

@ Condition de boucle (taille_liste-1 tours)
cmp r8,#1
beq finboucledecroiss

@R0: addresse du tableau
@R1: 
mov r0,r7
mov r1,r8
bl CALCULMAX
ldr r5,[r7]
mov r2,r2, lsl #2
ldr r6,[r7,r2]@pour avoir l'adresse du plus grand élément
str r6,[r7]
str r5,[r7,r2]
add r7,r7,#4
sub r8,r8,#1

b boucledecroiss

finboucledecroiss:
ldr r0,=tab
ldr r1,=size
ldr r1,[r1]
ldr r2,=format
bl AFFICHER

fin:
MOV r0, #0
MOV r7, #1
SVC 0


@param: r0:add tab
@param: r1:size
@param: r2:chaine de format
AFFICHER:
stmfd sp!,{r6,r7,r8,r14}
mov r8,r1
mov r7,r2
mov r6,r0
boucle:
CMP r8,#0
BEQ finAfficher
LDR r1,[r6],#4 @val du tableau pour le print
mov r0,r7 @copie la chaine de formatage pour le print
bl printf
SUB r8,r8,#1
b boucle

finAfficher:
ldmfd sp!,{r6,r7,r8,r15}

CALCULMAX:
@param: r0: adresse du tab
@param: r1:taille du tableau
@param r2: le résultat; la position de la plus grande valeur

STMFD sp!, {r3,r5,r6,r14}
LDR r5,[r0]
MOV r3, #0
MOV r2,#0

boucle1:
CMP r1,#0
BEQ fin1
LDR r6,[r0],#4
CMP r6,r5
BHS else
B finif

else:
MOV r5,r6
MOV r2, r3

finif:
ADD r3,r3,#1
SUB r1,r1,#1
B boucle1

fin1:

LDMFD sp!,{r3,r5,r6,r15}
