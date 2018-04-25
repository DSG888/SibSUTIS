%Запишите в новый файл все строки исходного файла, содержащие в качестве
%фрагмента заданную строку, которая вводится с клавиатуры.

goal:-
	read(STR),
	open('in.txt', read, INTEXT),
	set_input(INTEXT),
	walk(INTEXT, L),
	close(INTEXT),
	findall(X, (member(X, L), sub_string(X, _, _, _, STR)), OUT),
	(exists_file('out.txt'), delete_file('out.txt'), ! ; true),
	open('out.txt', write, OUTFILE),
	set_output(OUTFILE),
	out(OUTFILE, OUT),
	close(OUTFILE).

walk(_, []):-
	at_end_of_stream,
	!.

walk(F, [H|T]):-
	read_line_to_codes(F, COD),
	string_codes(H, COD),
	walk(F, T).

out(_, []):-
	!.

out(R,[H|T]):-
	writeln(H),
	out(R, T).


