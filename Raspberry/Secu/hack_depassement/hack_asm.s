.text
.global main
.arm

main:
add r6, pc, #1
bx r6

.thumb
mov r7, #0x04
mov r0, #1
mov r1, pc
add r1,#10
mov r2,#11
svc 1
mov r7, #1
mov r0, #1
svc 1

.asciz "programme 1"
