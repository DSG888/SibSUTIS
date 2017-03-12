@echo off 			
if  -%1 == -  goto no_param1	
if not exist %1 goto not_exist1
if  -%2 == -  goto no_param2	
if not exist %1\%2 goto not_exist2
echo === Атрибуты файла %2 в каталоге %1 ===	
attrib %1\%2
goto exit			
: no_param1			
echo Должен быть задан каталог
goto exit			
: no_param2			
echo Должено быть задано имя файла в каталоге %1
goto exit			
: not_exist1		
echo Каталог %1 не найден		
goto exit			
: not_exist2
echo Имя файла %1\%2 не найдено
: exit				
