; ===== Counting ===================================


	MOV	BL,40	; Initial value stored in BL

Rep:			; Jump back to this label
	INC	BL	; Add ONE to BL
	JMP	Rep	; Jump back to Rep

	END		; Program Ends

; ===== Program Ends ===============================

	TASK
	=====
	
	Rewrite the program to count backwards using DEC BL.
	
	Rewrite the program to count in threes using ADD BL,3.
	
	Rewrite the program to count 1 2 4 8 16 using MUL BL,2
	
	Here is a more difficult task.  
	Count 0 1 1 2 3 5 8 13 21 34 55 98 overflow.  
	Here each number is the sum of the previous two.  
	You will need to use registers or RAM locations 
	for temporary storage of the numbers.  
	If you have never programmed before, this is a real brain teaser. 
	Remember that the result will overflow when it goes above 127.
	
	This number sequence was first described by 
	Leonardo Fibonacci of Pisa (1170_1230)
	
	Задание 04
	==========
	Используйте внутри цикла команду DEC для последовательного
	уменьшения содержимого регистра BL. Когда содержимое регистра
	BL станет равным 0, программа должна закончить работу.


	Задание 05
	==========
	Используйте один из свободных регистров(например CL)
	для подсчёта повторений, начиная с 0 с шагом 1. После того, как
	значения в регистах совпадут, т.е BL=Cl, программа должна
	закончить работу.	

	Задание 06
	==========
	Используйте один из свободных регистров(например CL)
	для подсчёта повторений, начиная с 0 с шагом 4. После того, как
	значения в регистах совпадут, т.е BL=Cl, программа должна
	закончить работу.	
	
	Задание 07
	==========
	Используйте один из свободных регистров(например CL)
	для подсчёта повторений, начиная с 1 с шагом 1, а другой
	(DL) для накапливания промежуточной суммы произведения 
	значения CL умноженного на 2. После того, как DL > CL
	программа должна закончить работу(DL = 1x2 + 2x2 + 3x2 ...).

	Задание 12
	==========
	Используйте команду вычитания SUB для последовательного 
	уменьшения значения в регистре BL на 2. После того, как 
	значение в регистре BL станет равным нулю программа должна 
	закончить работу.

	Задание 13
	==========
	Используйте команду деления DIV для последовательного 
	уменьшения значения в регистре BL в два раза. После того, как 
	значение в регистре BL станет равным нулю программа должна 
	закончить работу. Начальное значение в регистре BL=64.
