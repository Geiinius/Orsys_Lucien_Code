.data
tab1: .word 5,60,8,10
tab2: .fill 4,4,0
taille: .word 4

.bss
.text

.global main
main:

LDR r8, =taille
LDR r0, [r8]

LDR r1, =tab1
LDR r2, =tab2

tantque:
CMP r0, #0
BEQ quitter

LDR r3, [r1]
STR r3, [r2]

ADD r1, r1, #4
ADD r2, r2, #4
SUb r0, r0, #1

B tantque

quitter:
MOV r0, #0
MOV r7, #1 @ quitter

SVC 0
