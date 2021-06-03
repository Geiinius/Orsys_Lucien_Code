.data
tab: .fill 6 ,4, 0
buff: .word 0
test: .asciz "%c"
format: .asciz "element: %c\n"

size: .word 6
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
Boucle:
CMP r8,#0
BEQ fin
LDR r1,[r7],#4
LDR r0,=format
bl printf
SUB r8,r8,#1
b Boucle


fin:

MOV r0, #0
MOV r7, #1
SVC 0
