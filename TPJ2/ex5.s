.data
tab: .fill 4 ,4, 0
buff: .word 0
test: .asciz "%d"
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

LDR r0, =test
LDR r1, =buff
BL scanf
LDR r1, =buff
LDR r1, [r1]
STR r1, [r7], #4
SUB r8, r8, #1
B tantque
fin_tantque:

MOV r0, #0
MOV r7, #1
SVC 0
