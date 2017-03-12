# файл, с отладочной информацией
# make -DDEBUG > p
NAME = prg01_01
OBJ = $(NAME).obj
NAME1 = prg01_02
OBJ1 = $(NAME1).obj
NAME2 = BinToAsc
OBJ2 = $(NAME2).obj
!ifdef DEBUG
TASMDEBUG=/zi/m2
LINKDEBUG=/v
!else
TASMDEBUG=
LINKDEBUG=/v
!endif
$(NAME).EXE: $(OBJ) 
	P:\Assembler\tasm\BIN\tlink $(LINKDEBUG) $(OBJ)
#	tlink $(LINKDEBUG) $(OBJ1) $(OBJ2)
.asm.obj:
# 	tasm $(TASMDEBUG) $.,,,
 	P:\Assembler\tasm\BIN\tasm $(TASMDEBUG) $.,,
# 	P:\Assembler\tasm\BIN\tasm $(TASMDEBUG) $(NAME1).asm  ,,
# 	tasm $(TASMDEBUG) $(NAME2).asm  ,,


