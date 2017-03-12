# файл, с отладочной информацией
# make -DDEBUG > p
NAME = add
OBJS = $(NAME).obj
!ifdef DEBUG
TASMDEBUG=/zi/m2
LINKDEBUG=/v
!else
TASMDEBUG=
LINKDEBUG=
!endif
$(NAME).EXE: $(OBJS)
	p:\Assembler\tasm\bin\tlink $(LINKDEBUG) $(OBJS)
.asm.obj:
 	p:\Assembler\tasm\bin\tasm $(TASMDEBUG) $.,,,

