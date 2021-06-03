.data
tab: .fill 4 ,4, 0
buff: .word 0
test: .asciz "%d"
format: .asciz "element: %d\n"
size: .word 4
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
BEQ fin
LDR r1,[r6],#4 @val du tableau pour le print
mov r0,r7 @copie la chaine de formatage pour le print
bl printf
SUB r8,r8,#1
b boucle
ldmfd sp!,{r6,r7,r8,r15}

