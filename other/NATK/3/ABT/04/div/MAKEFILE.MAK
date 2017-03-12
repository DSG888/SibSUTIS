# файл, с отладочной информацией
# make -DDEBUG > p
NAME = div
OBJS = $(NAME).obj
!ifdef DEBUG
TASMDEBUG=/zi/m2
LINKDEBUG=/v
!else
TASMDEBUG=
LINKDEBUG=
!endif
$(NAME).EXE: $(OBJS)
	tlink $(LINKDEBUG) $(OBJS)
.asm.obj:
 	tasm $(TASMDEBUG) $.,,,

