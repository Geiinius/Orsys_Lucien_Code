.data
va: .word 5
vb: .word 10
vc: .word 0

.text
.global main
main:

LDR R8,=va @ dans r8 on met l'adresse de a
LDR R0,[R8] @ ensuite on charge dans r0 le mot memoire compris dans r8

LDR R8,=vb
LDR R1,[R8]

LDR R8, =vc

CMP R0,R1

STREQ R0,[R8] @bloc then


MOVNE R5,#8
MULNE R3,R1,R5 @on met dans le registre R3 la multiplication de r1 par 8
STRNE R3,[R8]

MOV R0,#0
MOV R7,#1
svc 0
