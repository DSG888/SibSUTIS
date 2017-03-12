@echo off 			
if  -%1 == -  goto no_param	
if not exist %1 goto not_exist
rem echo === Удаление файлов из каталога %1 ===	
rem del %1\*.*
echo === Удаление каталога %1 ===	
rd /S /Q %1
goto exit			
: no_param			
echo Должен быть задан удаляемый каталог
goto exit			
: not_exist		
echo Каталог %1 не найден		
: exit				
