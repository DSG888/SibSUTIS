@echo off 			
rem shift			
if  -%1 == -  goto no_param1	
if  -%2 == -  goto no_param2	
if not exist %2 goto not_exist2
if not exist %2\%1 goto not_exist1
echo === Удаление файла %1 из каталога %2 ===	
del %2\%1
goto exit			
: no_param1			
echo Должен быть задан файл для удаления 
goto exit			
: no_param2			
echo Должен быть задан каталог, откуда удаляется файл %1
goto exit			
: not_exist1			
echo Файл %1 в каталоге %2 не найден		
goto exit			
: not_exist2			
echo Каталог %2 не найден		
: exit				
