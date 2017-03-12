@echo off 			
rem shift			
if  -%1 == -  goto no_param1	
if  -%2 == -  goto no_param2	
if not exist %1 goto not_exist1
if exist %2 goto yes_exist2
echo === Копирование каталога %1 в каталог %2 ===	
xcopy %1 %2 /E
goto exit			
: no_param1			
echo Должен быть задан копируемый каталог
goto exit			
: no_param2			
echo Должен быть задан каталог, куда выполнмть копирование
goto exit			
: not_exist1			
echo Каталог %1 не найден		
goto exit			
: yes_exist2			
echo Каталог %2 уже существует
: exit				
