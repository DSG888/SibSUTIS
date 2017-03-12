@echo off 			
if  -%1 == -  goto no_param	
if not exist %1 goto not_exist
echo === Атрибуты файлов в каталоге %1 ===	
attrib %1\*.*
goto exit			
: no_param			
echo Должен быть задан каталог
goto exit			
: not_exist		
echo Каталог %1 не найден		
: exit				
