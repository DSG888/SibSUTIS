# файл, с отладочной информацией
# make -DDEBUG > p
NAME = prg01_01
OBJ = $(NAME).obj
NAME1 = creg
OBJ1 = $(NAME1).obj
!ifdef DEBUG
TASMDEBUG=/zi/m2
LINKDEBUG=/v
!else
TASMDEBUG=
LINKDEBUG=/v
!endif
$(NAME).EXE: $(OBJ) $(OBJ1) 
	P:\Assembler\tasm\bin\tlink $(LINKDEBUG) $(OBJ) $(OBJ1)
#	tlink $(LINKDEBUG) $(OBJ1)
.asm.obj:
# 	tasm $(TASMDEBUG) $.,,,
 	P:\Assembler\tasm\bin\tasm $(TASMDEBUG) $.,,
 	P:\Assembler\tasm\bin\tasm $(TASMDEBUG) $(NAME1).asm  ,,


