@echo off 			
rem shift			
if  -%1 == -  goto no_param1	
if  -%2 == -  goto no_param2	
if not exist %1 goto not_exist1
if not exist %2 goto not_exist2
if exist %2\%1 goto yes_exist3
echo === Перемещение файла %1 в каталог %2 ===	
move %1 %2\ 
goto exit			
: no_param1			
echo Должен быть задан файл для перемещения
goto exit			
: no_param2			
echo Должен быть задан каталог, куда перемещается файл %1
goto exit			
: not_exist1			
echo Файл %1 не найден		
goto exit			
: not_exist2			
echo Каталог %2 не найден
goto exit			
: yes_exist3			
echo Файл %1 в каталоге %2 уже существует
: exit				
