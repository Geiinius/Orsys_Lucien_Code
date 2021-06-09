.global SORTIE
.global ALLUMER
.global ETEINDRE

SORTIE:
PUSH {r5-r8,r14}
ADD r0, r0, #4
LDR r6, [r0]
MOV r8, #0b111
MOV r7, r8, LSL #21
MOV r8, #0b001
MOV r5, r8, LSL #21

BIC r6, r6, r7
ORR r6, r6, r5

STR r6, [r0]

POP {r5-r8,r15}

ALLUMER:
PUSH {r6-r8, r14}
ADD r0, r0, #0x1c
LDR r6, [r0]
MOV r8, #0b1
MOV r7, r8, LSL #17

ORR r6, r6, r7

STR r6, [r0]

POP {r6-r8, r15}

ETEINDRE:
PUSH {r6-r8, r14}
ADD r0, r0, #0x28
LDR r6, [r0]
MOV r8, #0b1
MOV r7, r8, LSL #17

ORR r6, r6, r7

STR r6, [r0]

POP {r6-r8, r15}
