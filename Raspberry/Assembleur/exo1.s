.data

va: .word 5
vb: .word 10
resu: .word 0

.text
.global main

main:

LDR R8, =va
LDR R0, [R8]

LDR R8, =vb
LDR R1, [R8]

@Condition if
CMP R0,R1
BNE else

@If egale
LDR R8, =resu
STR R0, [R8]

B fin

@Else
else:

MOV R5, #8
MUL R3, R1, R5
LDR R8, =resu
STR R3, [R8]

fin:
MOV R0, #0
MOV R7, #1
svc 0
