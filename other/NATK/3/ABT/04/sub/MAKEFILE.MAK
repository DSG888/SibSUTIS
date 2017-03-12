# файл, с отладочной информацией
# make -DDEBUG > p
NAME = sub
OBJS = $(NAME).obj
!ifdef DEBUG
TASMDEBUG=/zi/m2
LINKDEBUG=/v
!else
TASMDEBUG=
LINKDEBUG=
!endif
$(NAME).EXE: $(OBJS)
	P:\Assembler\tlink $(LINKDEBUG) $(OBJS)
.asm.obj:
 	tasm $(TASMDEBUG) $.,,,

