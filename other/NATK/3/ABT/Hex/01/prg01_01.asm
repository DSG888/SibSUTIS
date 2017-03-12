;---------Prg01_01.asm----------------------------------------------------------------------------
; Пример выделения значений 
; Исходная строка: 0abcdh 
; Результат	 : 0bdh
;-----------------------------------------------------------------------------------------------------
masm
model small
extrn	creg:far
.data
var1	db	'xy' 	
var2	db	'00'
asci	db	4 dup(0),13,10,'$'	

.code
start:
	mov	ax,@data
	mov	ds,ax
;----------------------------         
	mov	bl,byte ptr var1+0	; bh  bl

; Вставка                               
	mov	bh,byte ptr var1+2		 	; ab  cd
	
	mov	ax,bx                   ; исходные данные
	lea	si,asci                 ; адрес результата
	call	creg

	mov	ah,09h                  ; вывод результата
	lea	dx,asci
	int	21h

	shl	bl,4                    ; b0  cd
	and	bh,0fh                  ; b0  0d
	or	bl,ah                   ; bd  0d
	mov	var2,bl                 ; bd

	mov	ax,bx                   ; исходные данные
	lea	si,asci                 ; адрес результата
	call	creg

	mov	ah,09h                  ; вывод результата
	lea	dx,asci
	int	21h


;----------------------------
	mov	ax,4c00h
	int	21h
end	start

