@echo off 			
rem shift			
if  -%1 == -  goto no_param	
if not exist %1 goto not_exist
echo === Удаление файла %1 ===	
del %1
goto exit			
: no_param			
echo Должен быть задан файл для удаления 
goto exit			
: not_exist			
echo Удаляемый файл %1 не найден		
: exit				
