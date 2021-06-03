.data
A: .short 1, 4, 7, 0
.short 2, 5, 8, 0
.short 3, 6, 9, 0

B: .short 9, 6, 3, 0
.short 8, 5, 2, 0
.short 7, 4, 1, 0

C: .fill 12, 2, 0
prtstr: .asciz "%3d %3d %3d\n"

.text
.global main

.MACRO mulcol ccol bcol
VMUL.I16 \ccol, D0, \bcol[0]
VMLA.I16 \ccol, D1, \bcol[1]
VMLA.I16 \ccol, D2, \bcol[2]
.ENDM
main:
LDR R0, =A @ Address of A
VLDM R0, {D0-D2} @ bulk load the three columns

LDR R0, =B @ Address of B
VLDM R0, {D3-D5} @ bulk load the three columns

mulcol D6,D3
mulcol D7,D4
mulcol D8,D5

@Enregistrement
LDR R1, =C
VSTM R1, {D6-D8}


@Affichage
MOV R5, #3 @ Print 3 rows
LDR R11, =C @ Addr of results matrix
printloop:
LDR R0, =prtstr @ printf format string
LDRH R1, [R11], #2 @ first element in current row
LDRH R2, [R11,#6] @ second element in current row
LDRH R3, [R11,#14] @ third element in current row
BL printf @ Call printf
SUBS R5, #1 @ Dec loop counter
BNE printloop

Mov r0,#0
Mov r7,#1
svc 0
