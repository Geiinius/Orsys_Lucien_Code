.data
liste: .word 10,5,17,3
.text
.global main
main:
mov r0,#4 @ taille de 'liste'
ldr r1,=liste
@stmfd sp!,{r1,r0}
while_emptying: @ empiller les éléments de 'liste'
cmp r0,#0
beq before_filling

ldr r3,[r1],#4
stmfd sp!,{r3}
sub r0,r0,#1

b while_emptying
before_filling:
@ldmfd sp!,{r1,r0}
mov r0,#4
ldr r1,=liste
while_filling:
cmp r0,#0
beq end

ldmfd sp!,{r4}
str r4,[r1],#4
sub r0,r0,#1

b while_filling
end:
mov r0,#0
mov r7,#1
svc 0

