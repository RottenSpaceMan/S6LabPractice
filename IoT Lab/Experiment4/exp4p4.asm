ORG 0000H
	MOV DPTR, #4200H
	MOVX A, @DPTR
	MOV B, A
	INC DPTR
	MOVX A, @DPTR
	MUL AB
	INC DPTR
	MOVX @DPTR, A
	INC DPTR
	MOV A, B
	MOVX @DPTR, A
HERE: SJMP HERE
END