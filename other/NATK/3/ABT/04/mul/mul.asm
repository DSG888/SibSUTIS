;--------------------------------------------
; Умножение ASCII-чисел
;--------------------------------------------
		.MODEL SMALL
		.DATA
;--------------------------------------------
MULTCAND	DB	  '3783'		;ASCII-числа	
MULTPLER	DB	  '5'
ASCPROD	DB	  5 DUP(0)
;--------------------------------------------
		.CODE
BEGIN:	
MULASCII	PROC   NEAR			
		MOV	AX,@DATA                ;инициализация DS
		MOV	DS,AX			;	через AX

		MOV	  CX,04			;кол-во повторений цикла
		LEA	  SI,MULTCAND+3         ;инициализация адресов
		LEA	  DI,ASCPROD+4          ;	ASCII-чисел
		AND	  MULTPLER,0FH		;очистка 3 в ASCII-числе
A20:
		MOV	  AL,[SI]		;загрузить ASCII-байт в AL
		AND	  AL,0FH		;очистка 3 в ASCII-числе
		MUL	  MULTPLER		;умножить
		AAM				;   скорректировать умножение
		ADD	  AL,[DI]		;сложить с ранее полученным
						;   результатом
		AAA				;   скорректировать сложение
		MOV	  [DI],AL		;сохранить результат
		DEC	  DI                    
		MOV	  [DI],AH		;сохранить результат переноса
		DEC	  SI
		LOOP	  A20			;повторить 4 раза

		LEA	  BX,ASCPROD+4		;преобразовать результат в
		                                ;	ASCII-формат	
		MOV	  CX,05			;справа - налево 5 байт	
A30:
		OR	  BYTE PTR[BX],30H      ;формирование ASCII-числа
		DEC	  BX
		LOOP   A30			;повторить 5 раз

		MOV	  AX,4C00H		;стандартное окнчание программы
		INT	  21H
MULASCII	ENDP
		END	  BEGIN

