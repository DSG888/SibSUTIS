;---------------------------------------------------
; Деление ASCII-чисел
;---------------------------------------------------
		.MODEL SMALL
		.DATA
;---------------------------------------------------
DIVIDEND	DB	  '3698'		;ASCII-числа
DIVISOR	DB	  '4'                           
ASCQUOT	DB	  4 DUP(0)
;---------------------------------------------------
		.CODE
BEGIN:	
DIVASCII	PROC   NEAR
		MOV	AX,@DATA                ;инициализация DS
		MOV	DS,AX			;	через AX
		MOV	ES,AX
							
		MOV	  CX,04			;кол-во повторений цикла
		SUB	  AH,AH			;очистка левого байта делимого
		AND	  DIVISOR,0FH		;очистка в делителе 3 в ASCII
		LEA	  SI,DIVIDEND           ;инициализация адресов
		LEA	  DI,ASCQUOT            ;	ASCII-чисел
A20:
		LODSB	  			;загрузить ASCII-байт в AL
		AND	  AL,0FH		;очистить 3 в ASCII
		AAD				;скорректировать перед
						;	делением	
		DIV	  DIVISOR		деление
		STOSB	  			;сохранить результат
		LOOP   A20			;повторить 4 раза
						;преобразовать результат в
		LEA	  BX,ASCQUOT		;	ASCII-формат начиная
						;	с левого байта	
		MOV	  CX,04			;	4 раза  
A30:
		OR	  BYTE PTR[BX],30H	;формирование ASCII-числа
		INC	  BX			;следующий байт
		LOOP   A30			;повторить 4 раза

		MOV	  AX,4C00H		;стандартное окнчание программы
		INT	  21H
DIVASCII	ENDP
		END	  BEGIN
