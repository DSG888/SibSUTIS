@echo off 			
rem shift			
if  -%1 == -  goto no_param1	
if  -%2 == -  goto no_param2	
if  -%3 == -  goto no_param3	
if not exist %1 goto not_exist1
if not exist %2 goto not_exist2
if not exist %1\%3 goto not_exist3
if exist %2\%3 goto yes_exist3
echo === Копирование файла %3 из каталога %1 в каталог %2 ===	
copy %1\%3 %2\
goto exit			
: no_param1			
echo Должен быть задан каталог, откуда копируется файл 
goto exit			
: no_param2			
echo Должен быть задан каталог, куда копируется файл 
goto exit			
: no_param3			
echo Должен быть задан копируемый файл из каталога %1
goto exit			
: not_exist1			
echo Каталог %1 не найден		
goto exit			
: not_exist2			
echo Каталог %2 не найден		
goto exit			
: not_exist3			
echo Файл %3 в каталоге %1 не найден		
goto exit			
: yes_exist3
echo Файл %3 в каталоге %2 уже существует		
: exit				
