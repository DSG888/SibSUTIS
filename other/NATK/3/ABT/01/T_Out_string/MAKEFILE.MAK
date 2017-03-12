# файл, с отладочной информацией
# make -DDEBUG > p
NAME = string
OBJS = $(NAME).obj
!ifdef DEBUG
TASMDEBUG=/zi/m2
LINKDEBUG=/v
!else
TASMDEBUG=
LINKDEBUG=/v
!endif
$(NAME).EXE: $(OBJS)
	tlink $(LINKDEBUG) $(OBJS)
.asm.obj:
 	tasm $(TASMDEBUG) $.,,,


