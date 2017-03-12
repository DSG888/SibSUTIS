;----------------------------------------------------------
;prg05_11.asm - программа ввода-вывода в консоль c изменеием
; атрибутов выводимого текста
;----------------------------------------------------------
.486
.model flat,STDCALL	;модель памяти flat,
;STDCALL - передача параметров в стиле С (справа налево), 
;	вызываемая процедура чистит за собой стек
;%NOINCL	;запретить вывод текста включаемых файлов
;include	WindowConA.inc

STD_INPUT_HANDLE	equ	-10	;winbase.h
STD_OUTPUT_HANDLE	equ	-11

include lib.inc

;Объявление внешними используемых в данной программе функций Win32 (ASCII):
;extrn	AllocConsole:PROC
;extrn	SetConsoleTitleA:PROC
;extrn	GetStdHandle:PROC
;extrn	SetConsoleCursorPosition:PROC
;extrn	SetConsoleTextAttribute:PROC
;extrn	ReadConsoleA:PROC
;extrn	WriteConsoleA:PROC
;extrn	ExitProcess:PROC

;макроопределения типов
SSHORT	equ	<dw	0>
;структура для установки положения курсора в консоли:
Coord	struc
xx	SSHORT
yy	SSHORT
Coord	ends
.data
con	Coord	<>
dIn	dd	0	;дескриптор ввода консоли
dOut	dd	0	;дескриптор вывода консоли
NumWri	dd	0	;количество действительно введенных-выведенных символов
TitleText	db	80 dup (0),0
;-------------------------------------------------------
msg	db	"Введите любую строку: ",0
len=$-msg
;-------------------------------------------------------

.code
start	proc	near	;точка входа в программу:
;запрос консоли
;	call	AllocConsole
	invoke	AllocConsole
;проверить успех запроса консоли
	test	eax,eax
	jz	exit	;неудача
;-------------------------------------------------------
;работаем … … …
;получим стандартные дескрипторы ввода-вывода
;	push	STD_OUTPUT_HANDLE
;	call	GetStdHandle
	invoke	GetStdHandle, STD_OUTPUT_HANDLE
	mov	dOut,eax	;dOut-дескриптор вывода консоли

;	push	STD_INPUT_HANDLE
;	call	GetStdHandle
	invoke	GetStdHandle, STD_INPUT_HANDLE
	mov	dIn,eax	;dIn-дескриптор ввода консоли
;-------------------------------------------------------
;-------------------------------------------------------
;перекодируем строку
	invoke	CharToOemA, ADDR msg, ADDR msg
;	push	offset msg
;	push	offset msg
;	call	CharToOemA
;-------------------------------------------------------

;установим курсор в позицию (2,6)
	mov	con.yy,6
cycle:

	mov	con.xx,2
	inc	con.yy
;	push	con
;	push	dOut
;	call	SetConsoleCursorPosition
	mov	eax, con
	invoke	SetConsoleCursorPosition, dOut, eax
	cmp	eax, 0
	jz	exit	;если неуспех
;-------------------------------------------------------
;-------------------------------------------------------
;выведем строку
	invoke	WriteConsoleA, dOut, ADDR msg, len, ADDR NumWri, 0
;-------------------------------------------------------

;введем строку
;	push	0
;	push	offset NumWri	;количество действительно введенных символов
;	push	80	;размер буфера TitleText для ввода
;	push	offset TitleText
;	push	dIn
;	call	ReadConsoleA	;читаем имя входного файла
	invoke	ReadConsoleA, dIn, ADDR TitleText, 80, ADDR NumWri, 0 
	cmp	eax, 0
	jz	exit	;если неуспех
;-------------------------------------------------------
;проверка окончания бесконечного цикла
	cmp	NumWri,2
	je	exit
;-------------------------------------------------------

;-------------------------------------------------------
;выведем введенную строку в заголовок окна консоли:
;	push	offset TitleText
;	call	SetConsoleTitleA
	invoke	SetConsoleTitleA, ADDR TitleText
;проверить успех вывода заголовка
	test	eax,eax
	jz	exit	;неудача
;-------------------------------------------------------
;выведем строку в окно консоли с различных позиций и с разными цветами
;установим курсор в позицию (2,5)
	mov	ecx,10	;строку выведем 10 раз
	mov	bl,10000001b	;начальные атрибуты
m1:
push	ecx
	inc	con.xx
	inc	con.yy
;	push	con
;	push	dOut
;	call	SetConsoleCursorPosition
	mov	eax, con
	invoke	SetConsoleCursorPosition, dOut, eax
	cmp	eax,0
	jz	exit	;если неуспех
;определим атрибуты выводимых символов - будем получать их циклически сдвигом - регистр bl
	xor	eax,eax
	rol	bl,1
	mov	al,bl
;	push	eax
;	push	dOut
;	call	SetConsoleTextAttribute
	invoke	SetConsoleTextAttribute, dOut, eax
	cmp	eax,0
	jz	exit	;если неуспех
;вывести строку
;	push	0
;	push	offset NumWri	;действительное количество выведенных на экран
;	push	NumWri	;длина строки для вывода на экран
;	push	offset TitleText	;адрес строки для вывода на экран
;	push	dOut
;	call	WriteConsoleA
	invoke	WriteConsoleA, dOut, ADDR TitleText, NumWri, ADDR NumWri, 0
	cmp	eax,0
	jz	exit	;если неуспех
pop	ecx
	loop	m1
	jmp	cycle

;-------------------------------------------------------
exit:	;выход из приложения
;готовим вызов VOID ExitProcess(UINT uExitCode)
;	push	0
;	call	ExitProcess
	invoke	ExitProcess, 0
start	endp
end	start
