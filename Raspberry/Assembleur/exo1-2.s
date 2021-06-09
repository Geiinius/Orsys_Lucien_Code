.text
.global main
main:
MOV r0, #1
MOV r1, #8
MOV r2, #3

CMP r0, r1
BHS else @ Si r0 > r1
c
CMP r1, r2
BHS else2 @R1 > R2

MOV r3, r2
B finif

else2:
MOV r3, r1
B finif

@R0 > R1
else:
CMP r0, r2
BHS else3 @ Si r0 > r2
MOV r3, r2

B finif
else3:
MOV r3, r0


finif:
MOV r0, #0
MOV r7, #1 @ quitter

SVC 0
