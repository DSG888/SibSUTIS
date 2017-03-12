; --------------------------------------------------
; вычитание ASCII-чисел
; --------------------------------------------------
		.MODEL SMALL
		.DATA
; --------------------------------------------------
ASCVALUE1	DB	  '548'			;ASCII-числа	
ASCVALUE2	DB	  '724'
message         DB	  'результат вычитания ','$'
ASCTOTAL	DB	  '0000','$'
.386  ; ---------------------------------------------
		.CODE
BEGIN:
ADDASCII	PROC   NEAR
		MOV	AX,@DATA                ;инициализация DS
		MOV	DS,AX			;	через AX

		CLC				;очистка CF
		LEA	  SI,ASCVALUE1+2	;инициализация адресов
		LEA	  DI,ASCVALUE2+2	;   ASCII-чисел
		LEA	  BX,ASCTOTAL+3
		MOV	  CX,03			;кол-во повторений цикла
A20:
		MOVZX  AX,[DI]			;загрузить ASCII-байт в AX
		ADC	  AL,[SI]		;сложить с возможным переносом
		AAA				;скоректировать сложение
		MOV	  [BX],AL		;сохранить сумму
		DEC	  SI
		DEC	  DI
		DEC	  BX
		LOOP   A20			;повторить 3 раза
		MOV	  [BX],AH		;в конце сохранить возможный
						;	 перенос
		LEA	  BX,ASCTOTAL+3		;инициализация преобразования
		MOV	  CX,04			;  суммы в ASCII формат
A30:
		OR	  BYTE PTR[BX],30H      ;формирование ASCII-числа
		DEC	  BX
		LOOP   A30			;повторить 4 раза
		mov	ah,09h
	        mov	dx,offset message
		int 	21h
		mov	ah,09h
		mov	dx,offset ASCTOTAL 
		int	21h
		MOV	  AX,4C00H		;стандартное окнчание программы
		INT	  21H
		
ADDASCII	ENDP
		END	  BEGIN
