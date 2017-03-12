; ===== CONTROL THE TRAFFIC LIGHTS =============================

	CLO		; Close unwanted windows.
Start:
			; Turn off all the traffic lights.
	MOV AL,0	; Copy 00000000 into the AL register.
	OUT 01		; Send AL to Port One (The traffic lights).
			; Turn on all the traffic lights.
	MOV AL,FC	; Copy 11111100 into the AL register.
	OUT 01		; Send AL to Port One (The traffic lights).
	JMP Start	; Jump back to the start.
	END		; Program ends.
	
; ===== Program Ends ==========================================

	YOUR TASK
	=========
	Use the help page on Hexadecimal and ASCII codes.
	Work out what hexadecimal numbers will activate the
	correct traffic lights. Modify the program to step
	the lights through a realistic sequence.

	«адание 01
	==========
	»спользуйте один из свободных регистров(например BL)
	дл€ задани€ количества повторений цикла, а другой(CL)
	дл€ подсчЄта повторений, начина€ с 0. ѕосле того, как
	значени€ в регистах совпадут, т.е BL=Cl, программа должна
	закончить работу.

	«адание 11
	==========
	»спользуйте два адреса в пам€ти, один дл€ задани€ количества
	повторений цикла, а другой дл€ подсчЄта текущих повторений,
	начина€ с нул€. ѕосле того, как значени€ по этим адресам 
	совпадут, программа должна закончить работу.
