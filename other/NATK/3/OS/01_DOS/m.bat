cls
copy con www.sss
rem
md tmp                	
rem
copy *.txt tmp\*.ttt 
rem  
move tmp\*.ttt	
pause
rem	
del *.ttt, *.sss      		
rem
rd tmp			
