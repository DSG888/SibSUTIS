@echo off 			
rem shift			
if  -%1 == -  goto no_param1	
if  -%2 == -  goto no_param2	
if not exist %1 goto not_exist1
if not exist %1\%2 goto not_exist2
if exist %2 goto yes_exist3
echo === Копирование файла %2 из каталога %1 в текущий каталог ===	
copy %1\%2
goto exit			
: no_param1			
echo Должен быть задан каталог, откуда копируется файл 
goto exit			
: no_param2			
echo Должен быть задан копируемый файл из каталога %1
goto exit			
: not_exist1			
echo Каталог %1 не найден		
goto exit			
: not_exist2			
echo Файл %2 в каталоге %1 не найден		
goto exit			
: yes_exist3
echo Файл %2 в текущем каталоге уже существует		
: exit				
