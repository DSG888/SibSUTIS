@echo off 			
if  -%1 == -  goto no_param1	
if not exist %1 goto not_exist1
if  -%2 == -  goto no_param2	
if not exist %1\%2 goto not_exist2
if  -%3 == -  goto no_param3
if exist %1\%3 goto yes_exist
echo === Переименование файла %2 в каталоге %1 на %3 ===	
ren %1\%2 %3
goto exit			
: no_param1			
echo Должен быть задан каталог
goto exit			
: no_param2			
echo Должен быть задан файл в каталоге %1
goto exit			
: no_param3			
echo Должено быть задано новое имя для переименования файла %2
goto exit			
: not_exist1		
echo Каталог %1 не найден		
goto exit			
: not_exist2		
echo Файл с именем %2 не существует
goto exit			
: yes_exist		
echo Файл с новым именем %3 уже существует в каталоге %1
: exit				
