.data
tab2: .fill 4,4,0
tab3: .fill 4,4,0
tab1: .word 15,8,90,23
taille: .word 4

.text
.global main

main:
ldr r8,=taille
ldr r0,[r8]

ldr r1,=tab1
ldr r2,=tab2
ldr r3,=tab3

tantque:
cmp r0,#0
beq end1

ldr r4,[r1],#4
tst r4,#0b1
bne else
str r4,[r2],#4
b end
else:
str r4,[r3],#4

end:
sub r0,r0,#1

b tantque

end1:
mov r0,#0
mov r7,#1
svc 0
