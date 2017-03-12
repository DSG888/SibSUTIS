# файл, с отладочной информацией
# make -DDEBUG > p
NAME = PROGRAMM
OBJS = $(NAME).obj
!ifdef DEBUG
TASMDEBUG=/zi/m2
LINKDEBUG=/v
!else
TASMDEBUG=
LINKDEBUG=
!endif
$(NAME).EXE: $(OBJS)
	P:\Assembler\tasm\bin\tlink $(LINKDEBUG) $(OBJS)
.asm.obj:
 	P:\Assembler\tasm\bin\tasm $(TASMDEBUG) $.,,,

