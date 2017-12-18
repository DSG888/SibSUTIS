%Запишите в новый файл все строки исходного файла, содержащие в качестве
%фрагмента заданную строку, которая вводится с клавиатуры.

goal :-
	read_file_to_string('in.txt', InputData, []),
	split_string(InputData, "\n", "", InputList),
	(exists_file('out.txt'), delete_file('out.txt'), ! ; true),
	append('out.txt'),
	foo(InputList, 'REDISKA').

foo([],_).

foo([H|[]], _).

foo([_|T],Str) :-
	append('out.txt'),
	write(Str),
	nl,
	foo(T,Str).

finds([H|T],Str):-
	
