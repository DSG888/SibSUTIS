@echo off 			
if  -%1 == -  goto no_param1	
if  -%2 == -  goto no_param2	
if not exist %1 goto not_exist
if exist %2 goto yes_exist
echo === Переименование каталога %1 ===	
ren %1 %2
goto exit			
: no_param1			
echo Должен быть задан переименуемый каталог
goto exit			
: no_param2			
echo Должено быть задано имя нового каталога
goto exit			
: not_exist		
echo Каталог %1 не найден		
goto exit			
: yes_exist		
echo Каталог с именем %2 уже существует
: exit				
