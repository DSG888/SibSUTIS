@echo off 			
rem shift			
if  -%1 == -  goto no_param1	
if  -%2 == -  goto no_param2	
if  -%3 == -  goto no_param3	
if not exist %2 goto not_exist2
if exist %3 goto not_exist3
echo === Копирование файла %2 из текущего каталога в подкаталог %1 ===	
md %1
copy %2 %1\
echo === Перемещение файла %3 из подкаталога в текущий каталог ===
move %1\%2 %3	
echo === Удаление файла %3 и подкаталога %1 ===	
del %3
rd %1
goto exit			
: no_param1			
echo Должен быть задан подкаталог
goto exit			
: no_param2			
echo Должен быть задан копируемый файл из текущего каталога 
goto exit			
: no_param3			
echo Должен быть задан перемещаемый файл из подкаталога %2 в каталог
goto exit			
: not_exist2			
echo Файл %2 в текущем каталоге не найден		
goto exit			
: yes_exist3
echo Файл %3 в текущем каталоге уже существует		
: exit				
