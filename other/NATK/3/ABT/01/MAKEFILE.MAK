# файл, с отладочной информацией
# make -DDEBUG > p
NAME = prg05_01
PATH = P:\Assembler\TASM\BIN
OBJS = $(NAME).obj
!ifdef DEBUG
TASMDEBUG=/zi/m2
LINKDEBUG=/v
!else
TASMDEBUG=
LINKDEBUG=/v
!endif
$(NAME).EXE: $(OBJS)
	$(PATH)\tlink $(LINKDEBUG) $(OBJS)
.asm.obj:
 	$(PATH)\tasm $(TASMDEBUG) $.,,,


