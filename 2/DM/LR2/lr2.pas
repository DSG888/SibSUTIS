{
Лабораторная работа № 2  Отношения и их свойства
Бинарное отношение R на конечном множестве A2 задано списком упорядоченных пар вида (a,b), где a,bA. Программа должна определять свойства данного отношения: рефлексивность, симметричность, антисимметричность, транзитивность (по материалам лекции 2).
Работа программы должна происходить следующим образом:
1.	На вход подается множество A из n элементов, список упорядоченных пар, задающий отношение R (ввод с клавиатуры). 
2.	Результаты  выводятся на экран (с необходимыми пояснениями) в следующем виде: 		
а)	матрица бинарного отношения размера nn;	
б)	список свойств данного отношения.
Дополнительно: после вывода результатов предусмотреть возможность изменения списка пар, определяющих отношение. Например, вывести на экран список пар (с номерами) и по команде пользователя изменить что-либо в этом списке (удалить какую-то пару, добавить новую, изменить имеющуюся), после чего повторить вычисления.
}

program lab2;

uses
  Crt;

const
  Nmax = 15; { Макс. количество элементов множества A }

type
  T = Char; { Тип элементов множества A }
  TPair = Record
    a, b: T;
  end;
  TSet = Array[1..Nmax] of T;
  TMatrix = Array[1..Nmax, 1..Nmax] of Byte;

{ Сортировка выбором по неубыванию }
procedure Sort(var A: TSet; const N: Integer);
var
  i, j, k: Integer;
  tmp: T;
begin
  for i := 1 to N - 1 do begin
    k := i;
    for j := i + 1 to N do
      if A[j] < A[k] then k := j;
    tmp := A[i];
    A[i] := A[k];
    A[k] := tmp;
  end;
end;

{ Возвращает индекс элемента x в A. Если такого элемента нет, то возвращает -1 }
function Search(const x: T; const A: TSet; const N: Integer): Integer;
var
  i: Integer;
begin
  for i := 1 to N do
    if x = A[i] then begin
      Search := i;
      Exit;
    end;
  Search := -1;
end;

{ Проверка на рефлексивность }
function Reflex(const M: TMatrix; const N: Integer): Boolean;
var
  i: Integer;
begin
  Reflex := False;
  for i := 1 to N do
    if M[i, i] = 0 then Exit;
  Reflex := True;
end;

{ Проверка на симметричность }
function Symmetry(const M: TMatrix; const N: Integer): Boolean;
var
  i, j: Integer;
begin
  Symmetry := False;
  for i := 1 to N - 1 do
    for j := i + 1 to N do
      if M[i, j] <> M[j, i] then Exit;
  Symmetry := True;
end;

{ Проверка на антисимметричность }
function Antisymmetry(const M: TMatrix; const N: Integer): Boolean;
var
  i, j: Integer;
begin
  Antisymmetry := False;
  for i := 1 to N do
    for j := 1 to N do
      if (i <> j) and (M[i, j] * M[j, i] <> 0) then Exit;
  Antisymmetry := True;
end;

{ Проверка на транзитивность }
function Transit(const M: TMatrix; const N: Integer): Boolean;
var
  i, j, k: Integer;
  S: TMatrix;
begin
  Transit := False;
  for i := 1 to N do
    for j := 1 to N do begin
      S[i, j] := 0;
      for k := 1 to N do
        S[i, j] := S[i, j] or M[i, k] and M[k, j];
    end;
  for i := 1 to N do
    for j := 1 to N do
       if M[i, j] < S[i, j] then Exit;
  Transit := True;
end;

{ Вывод списка клавиш управления }
procedure Keys;
begin
  ClrScr;
  WriteLn('Выберите действие.');
  WriteLn;
  WriteLn('1 - показать список элементов множества A');
  WriteLn('2 - показать список пар бинарного отношения');
  WriteLn('3 - показать матрицу бинарного отношения');
  WriteLn('4 - показать свойства бинарного отношения');
  WriteLn('5 - измененть одну пару бинарного отношения');
  WriteLn('6 - удалить одну пару бинарного отношения');
  WriteLn('7 - добавить новую пару бинарного отношения');
  WriteLn('0 - очистить экран');
  WriteLn('Esc - завершить работу');
  WriteLn
end;

var
  i, j, N, k, z: Integer;
  x, y: T;  
  A: TSet;  
  M: TMatrix;
  P: Array[1..Nmax] of TPair;
  F: Boolean;
  v: Char;
begin
  ClrScr;
  WriteLn('Введите множество A (набор элементов через пробел)');
  N := 0;
  while not SeekEoLn do begin
    Inc(N);
    Read(A[N]);
  end;
  Sort(A, N);
  F := False;
  i := 1;
  while i < N do begin
    if A[i] = A[i + 1] then begin
      F := True;
      Dec(N);
      for j := i to N do
        A[j] := A[j + 1];
    end
    else
      Inc(i);
  end;
  if F then WriteLn('Повторяющиеся элементы были удалены.');
  for i := 1 to Nmax do
    for j := 1 to Nmax do
       M[i, j] := 0;
  WriteLn;
  WriteLn('Введите список пар. Каждую пару в новой строке, элементы пары - через пробел.');
  WriteLn('Для завершения ввода, вместо ввода пары нажмите Enter.');
  Reset(Input);
  k := 0;
  while not SeekEoLn do begin
    Read(x);
    if SeekEoLn then Reset(Input);
    ReadLn(y);
    if (Search(x, A, N) = -1) or (Search(y, A, N) = -1) then begin
       WriteLn('Элементы должны быть из множества A. Эта пара будет пропущена.');
       Continue;
    end;
    F := False;
    for i := 1 to k do
      if (P[i].a = x) and (P[i].b = y) then begin
         WriteLn('Эта пара уже была. Пропущено.');
         F := True;
         Break;
      end;
    if F then Continue;
    M[Search(x, A, N), Search(y, A, N)] := 1;
    Inc(k);
    P[k].a := x;
    P[k].b := y;
  end;
  Keys;
  repeat
    v := ReadKey;
    case v of
    '1':
      begin
        WriteLn('Элементы множества A:');
        for i := 1 to N do
          Write(A[i], ' ');
        WriteLn;
      end;
    '2':
      begin
        WriteLn('Список пар бинарного отношения:');
        for i := 1 to k do
          WriteLn(i, '. (', P[i].a, ', ', P[i].b, ')');
      end;
    '3':
      begin
        WriteLn('Матрица бинарного отношения:');
        Write('    ');
        for i := 1 to N do
          Write(A[i]:3, ' ');
        WriteLn;
        for i := 1 to N do
        begin
          Write(A[i]:3, ' ');
          for j := 1 to N do
            Write(M[i, j]:3, ' ');
          WriteLn;
        end;
      end;
    '4':
      begin
        WriteLn('Введённое отношение');
        if Symmetry(M, N)     then  WriteLn('- симметрично')     else WriteLn('- не симметрично ');
        if Antisymmetry(M, N) then  WriteLn('- антисимметрично') else WriteLn('- не антисимметрично');
        if Reflex(M, N)       then  WriteLn('- рефлексивно')     else WriteLn('- не рефлексивно');
        if Transit(M, N)      then  WriteLn('- транзитивно')     else WriteLn('- не транзитивно');
      end;
    '5':
      begin
        WriteLn('Введите номер пары, которую хотите изменить.');
        {$I-}
        ReadLn(z);
        {$I+}
        while IOResult <> 0 do begin
          WriteLn('Введено неверно. Введите заново.');
          {$I-}
          ReadLn(z);
          {$I+}
        end;
        if (z > k) or (z < 1) then
          WriteLn('Нет такой пары.')
        else begin
          WriteLn('Введите новое значение пары (два элемента через пробел).');
          Reset(Input);
          Read(x);
          if SeekEoLn then Reset(Input);
          ReadLn(y);
          if (Search(x, A, N) = -1) or (Search(y, A, N) = -1) then
            WriteLn('Значения должны быть из множества A. Изменение не произведено.')
          else begin
            F := False;
            for i := 1 to k do
              if (P[i].a = x) and (P[i].b = y) then begin
                WriteLn('Эта пара уже была. Пропущено.');
                F := True;
                Break;
              end;
            if not F then begin
              M[Search(P[z].a, A, N), Search(P[z].b, A, N)] := 0;
              P[z].a := x;
              P[z].b := y;
              M[Search(x, A, N), Search(y, A, N)] := 1;
              WriteLn('Изменено.');
            end;
          end;
        end;
      end;
    '6':
      begin
        WriteLn('Введите номер пары для удаления');
        {$I-}
        ReadLn(z);
        {$I+}
        while IOResult <> 0 do begin
          WriteLn('Введено неверно. Введите заново.');
          {$I-}
          ReadLn(z);
          {$I+}
        end;
        if (z > k) or (z < 1) then
          WriteLn('Нет такой пары')
        else begin
          M[Search(P[z].a, A, N), Search(P[z].b, A, N)] := 0; { Удаляем пару из матрицы }
          Dec(k);
          for i := z to k do  { Удаляем пару из списка P }
            P[i] := P[i + 1];
          WriteLn('Удалено.');
        end;
      end;
    '7':
      begin
        WriteLn('Введите пару (два элемента через пробел)');
        Reset(Input);
        Read(x);
        if SeekEoLn then Reset(Input);
        ReadLn(y);
        if (Search(x, A, N) = -1) or (Search(y, A, N) = -1) then
          WriteLn('Значения должны быть из множества A. Добавление не произведено.')
        else begin
          F := False;
          for i := 1 to k do
            if (P[i].a = x) and (P[i].b = y) then begin
              WriteLn('Эта пара уже есть. Пропущено.');
              F := True;
              Break;
            end;
          if not F then begin
            Inc(k);
            P[k].a := x;
            P[k].b := y;;
            M[Search(P[k].a, A, N), Search(P[k].b, A, N)] := 1;
          end;
        end;
        if not F then WriteLn('Добавлено.');
      end;
      '0': Keys;
    end;
  until v = #27;
end.
