CLR C
MOV R4, #00H
MOV DPTR, #4200H
MOVX A, @DPTR
MOV R0, A
INC DPTR
MOVX A, @DPTR
MOV R1, A
INC DPTR
MOVX A, @DPTR
MOV R2, A
INC DPTR
MOVX A, @DPTR
MOV R3, A
MOV A, R0
ADD A, R2
MOV DPTR, #4204H
MOVX @DPTR, A
MOV A, R1
ADDC A, R3
JNC HERE
INC R4
HERE:
	INC DPTR
	MOVX @DPTR, A
	INC DPTR
	MOV A, R4
	MOVX @DPTR, A
NOW: SJMP NOW
END