ORG 0000H
	MAIN:
		MOV DPTR, #4200H
		MOVX A, @DPTR
		ANL A, #01H
		JNZ ODD
		MOV A, #0FFH
		SJMP HERE
		ODD:
			MOV A, #00H
	HERE: SJMP HERE
END