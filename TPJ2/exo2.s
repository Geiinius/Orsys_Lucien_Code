.data
VN: .word 3
som: .word 0
.text
.global main
main:
ldr r0,=VN
ldr r1,[r0] @R1=VN
mov R2,#0 @R2=i
mov R3,#0 @ R3=Somme

tantque: cmp R2,R1
BHI fin
add r3,r3,r2
add r2,r2,#1
B tantque

fin:
ldr r5,=som
str r3,[r5]

mov r0,#0
mov r7,#1
svc 0
