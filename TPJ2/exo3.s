.data 
val: .word 5
ham: .word 0
.text
.global main
main:
ldr r0,=val
ldr r1,[r0]



mov r2,#0  @hamming

tantque: 
cmp r1,#0
beq quitter
tst r1,#1
beq finboucle
add r2,r2,#1

finboucle:
mov r1,r1,lsr #1

b tantque
quitter:
ldr r4,=ham
str r2,[r4]

mov r0,#0
mov r7,#1
svc 0
