% 1.3. Сформируйте новый список из общих элементов двух списков (пересечение множеств). Например, [1,2,3,5], [6,4,1,8,3] -> [1,3].
%      Вариант 3

/*принадлежность элемента к множеству*/
member(X,[X|_]).
member(X,[_|L]) :- member(X,L).
    
/*удаление элемента из множества */
del(X,[X|L],L).
del(X,[Y|L],[Y|L1]) :- del(X,L,L1). 
    
/*удаление из второго множества, всех элементов первого множества*/
except([],L,L).
except([X|L1],L2,Result) :- member(X,L2),!, del(X,L2,L), except(L1,L,Result); except(L1,L2,Result).

cross(L1,L2) :- except(L1,L2,L3), except(L3,L2,Result), write('cross ='),write(Result). 
