% 1. Написать предикат, который разбивает числоваой список по двум числам, вводимым 
%    с клавиатуры на три списка: меньше введенного числа, от меньшего введенного 
%    числа до большего введенного числа, больше большего введенного числа.
%    Список и два числа вводятся с клавиатуры в процессе работы предиката.

	splite :-
		read(List),read(A),read(B),splite_prepare(A, B, Min, Max),
		splite_rec(List, Min, Max, List1, List2, List3),
		write(List1), write(List2), writeln(List3).

	splite_prepare(A, B, Min, Max) :- A > B, !, Max = A, Min = B; Max = B, Min = A.

	splite_rec([], _A, _B, [], [], []).
       
	splite_rec([Head|Tail], A, B, [Head|List1], List2, List3) :-
		Head < A, !,splite_rec(Tail, A, B, List1, List2, List3).
	splite_rec([Head|Tail], A, B, List1, [Head|List2], List3) :-
		Head =< B, !, splite_rec(Tail, A, B, List1, List2, List3).
	splite_rec([Head|Tail], A, B, List1, List2, [Head|List3]) :-
		!, splite_rec(Tail, A, B, List1, List2, List3).

% 2. Написать предикат, фкоторый формирует список из номеров максимальных элементов 
%    числового списка. Список вводится с клавиатуры в процессе работы предиката.

	max :-
		read(A), max_list(A, M), max_rec(A, B, M, 1),writeln(B).

	max_rec([], [], _, _).
	max_rec([Head|Tail], [N|B], M, N) :-
		Head =:= M, !, N1 is N + 1, max_rec(Tail, B, M, N1).
	max_rec([Head|Tail], B, M, N) :-
		Head =\= M, !, N1 is N + 1, max_rec(Tail, B, M, N1).

% 3. Написать предикат, который формирует список из наиболее часто встречающихся 
%    элементов списка. Список вводится с клавиатуры в процессе работы предиката.

	f :-
		read(List), msort(List, SList), cou(SList, _, ResList), write(ResList).

	cou([], 0, []).
	cou([H|B], K, [H]) :-
		foo([H|B], H, K, List), cou(List, MX, _), K > MX, !.
	cou([H|B], MX, List1) :-
		foo([H|B], H, K, List), cou(List, MX, List1), K < MX, !.
	cou([H|B], MX, [H|List1]) :-
		foo([H|B], H, K, List), cou(List, MX, List1), K =:= MX, !.

	foo([], _, 0, []) :- !.
	foo([H|B], X, 0, [H|B]) :- H =\= X, !.
	foo([H|B], X, K, B1) :-  H =:= X,  foo(B, X, K1, B1), K is K1 + 1.

