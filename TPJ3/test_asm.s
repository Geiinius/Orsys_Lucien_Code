@ R1 address of output string
@ R0 address of input string
@ R4 original output string for length calc.
@ R5 current character being processed
@
.global mytoupper
mytoupper:
	PUSH {R4-R5,R14} @ STMFD sp!,{R4,R5,R14}
	MOV R4, R1
	@ The loop is until byte pointed to by R1 is non-zero
	loop:
		LDRB R5, [R0], #1 @load character and increment
		CMP R5,#0
		BEQ fin
		CMP R5, #'z' @ is letter > 'z'?
		BGT cont @ If R5 > 'z' then goto cont
		CMP R5, #'a' @ Else if R5 'a' then goto cont
		BLT cont @ goto to end if
	SUB R5, #('a'-'A')
	cont: @ end if
		STRB R5, [R1], #1 @ store character to output str
		B loop
	fin:
	SUB R0, R1, R4 @get the length by subtracting the pointers
	POP {R4-R5,R15} @Restore the register we use.
