;
; Преобразование значения региста ах в ASCI-код
; Исходные данные: значение в ах
; Результат      : ASCI-код(из 4-х символов) по адресу регистра si
;
; Например; ax=0acdfh Результат='ACDF'
;
model small
.code
creg	proc 	far
	public	creg
push	cx                      ;сохранить
push	dx
push	bx
                                                                ;Часть
                                                                ;примера 
	mov	cx,4            ;кол-во повторений              
.loop:                                                          
	mov	dh,ah           ;очередной байт начиная слева	; ac
	and	dh,0f0h		;выделение левого полубайта     ; a0
	shr	dh,4            ;выравнивание                   ; 0a
	cmp	dh,9            ;значение > 9
	jg	.big            ;да
	or	dh,30h          ;ASCI-код для значений 0..9
.cont:
	mov	[si],dh         ;сохранение результата          ;'A'
	shl	ax,4            ;следующий полубайт             ; cd
	inc	si              ;следующий адрес для результата
	loop	.loop
pop	bx
pop	dx
pop	cx                      ;восстановить
	retf
.big:                           ;значение > 9, т.е. 10..15
	and	dh,07h          ;значение - 10                  ;  2 
	dec	dh              ;уменьшение на 1                ;  1
	or	dh,40h          ;ASCI-код для значений 10..15   ; 41='A'
	jmp	.cont
creg	endp
end