@echo off 			
rem shift			
if  -%1 == -  goto no_param	
if not exist %1 goto not_exist	
type %1				
goto exit			
: no_param			
echo Должен быть задан параметр	
goto exit			
: not_exist			
echo Файл %1 не найден		
: exit				
