# файл, с отладочной информацией
# make -DDEBUG > p
NAME = prg05_02
PATH = p:\Assembler\tasm\BIN
OBJS = $(NAME).obj
!ifdef DEBUG
TASMDEBUG=/zi/m2
LINKDEBUG=/v
!else
TASMDEBUG=
LINKDEBUG=
!endif
$(NAME).EXE: $(OBJS)
	$(PATH)\tlink $(LINKDEBUG) $(OBJS)
.asm.obj:
 	$(PATH)\tasm $(TASMDEBUG) $.,,,


