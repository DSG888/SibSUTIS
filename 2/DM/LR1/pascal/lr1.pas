{
Лабораторная работа № 1  Множества и операции над ними
Написать программу, в которой для конечных упорядоченных множеств реализовать все основные операции (, , , \) с помощью алгоритма типа слияния (по материалам лекции 1). Допустима организация множеств в виде списка или в виде массива.
Работа программы должна происходить следующим образом:
1.	На вход подаются два упорядоченных множества A и B (вводятся с клавиатуры, элементы множеств – буквы латинского алфавита). 
2. После ввода множеств выбирается требуемая операция (посредством текстового меню, вводом определенного символа в ответ на запрос – выбор по желанию автора). Операции: вхождение AB, AB, AB (дополнительно: A\B, B\A, AB). 
3. Программа посредством алгоритма типа слияния определяет результат выбранной операции и выдает его на экран с необходимыми пояснениями.
4. Возврат  на п.2 (выбор операции).
5. Завершение работы программы – из п.2 (например, по ESC).
Дополнительно: возможность возврата (по выбору пользователя) на п.2 или п.1. Выход в таком случае должен быть предусмотрен из любого пункта (1 или 2).
}

program lab1;

uses
  Crt;

const
  Nmax = 50;  { Макс. кол-во элементов множества }

type
  T = Char; { Тип элементов множества }
  TSet = Array[1..Nmax] of T; { Само множество }

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

{ Ввод множества }
procedure Set_Input(var A: TSet; var N: Integer);
var
  i, j: Integer;
  tmp: T;
  F: Boolean;
begin
  Reset(Input);
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
      for j := i + 1 to N do
        A[j] := A[j + 1];
    end
    else
      Inc(i);
  end;
  if F then WriteLn('Повторяющиеся элементы удалены.');
end;

{ Печать множества }
procedure Print(const A: TSet; const N: Integer);
var
  i: Integer;
begin
  for i := 1 to N do
    Write(A[i], ' ');
  if N = 0 then Write('Пустое множество.');
  WriteLn;
end;

{ Печать множеств A, B }
procedure Print_Sets(const A, B: TSet; const N, M: Integer);
var
  i: Integer;
begin
  WriteLn;
  Write('Множество A:  ');
  for i := 1 to N do
    Write(A[i], ' ');
  WriteLn;
  Write('Множество B:  ');
  for i := 1 to M do
    Write(B[i], ' ');
  WriteLn;
end;

{ Объединение множеств A и B методом слияния }
procedure Union(var U: TSet; var k: Integer; const A, B: TSet; const N, M: Integer);
var
  i, j: Integer;
begin
  i := 1;
  j := 1;
  k := 0;
  while (i <= N) or (j <= M) do
    if (j <= M) and (i <= N) and (A[i] = B[j]) then begin
      Inc(k);
      U[k] := A[i];
      Inc(i);
      Inc(j);
    end
    else if (j > M) or (i <= N) and (A[i] < B[j]) then begin
      Inc(k);
      U[k] := A[i];
      Inc(i);
    end
    else begin
      Inc(k);
      U[k] := B[j];
      Inc(j);
    end;
end;

{ Пересечение множеств A, B методом слияния }
procedure Product(var P: TSet; var k: Integer; const A, B: TSet; const N, M: Integer);
var
  i, j, W: Integer;
begin
  i := 1;
  j := 1;
  k := 0;
  while (i <= N) and (j <= M) do
    if (A[i] = B[j]) then begin
      Inc(k);
      P[k] := A[i];
      Inc(i);
      Inc(j);
    end
    else if A[i] < B[j] then
      Inc(i)
    else
      Inc(j);
end;

{ Разность множеств A, B методом слияния }
procedure Diff(var D: TSet; var k: Integer; const A, B: TSet; const N, M: Integer);
var
  i, j: Integer;
begin
  i := 1;
  j := 1;
  k := 0;
  while (i <= N) and (j <= M) do
    if A[i] = B[j] then begin
      Inc(i);
      Inc(j);
    end
    else if A[i] < B[j] then begin
      Inc(k);
      D[k] := A[i];
      Inc(i);
    end
    else if A[i] > B[j] then
      Inc(j);
  while (i <= N) and (j > M) do begin
    Inc(k);
    D[k] := A[i];
    Inc(i);
  end;
end;

{ Проверка на вхождение A в B }
function Incl(const A, B: TSet; const N, M: Integer): Boolean;
var
  i, j: Integer;
begin
  Incl := False;
  if N > M then Exit;
  i := 1;
  j := 1;
  while (i <= N) and (j <= M) and (A[i] >= B[j]) do
    if A[i] > B[j] then
      Inc(j)
    else if A[i] = B[j] then begin
      Inc(i);
      Inc(j);
    end;
  Incl := i - 1 = N;
end;

{ Вывод на экран клавиш управления }
procedure Keys;
begin
  ClrScr;
  WriteLn('Выберите действие:');
  WriteLn;
  WriteLn('1 - ввод множества A');
  WriteLn('2 - ввод множества B');
  WriteLn('3 - проверка вхождения A в B');
  WriteLn('4 - вывести объеденение множеств A и B');
  WriteLn('5 - вывести пересечение множеств A и B');
  WriteLn('6 - вывести разность A \ B');
  WriteLn('0 - очистка экрана');
  WriteLn('Esc - выход');
  WriteLn;
end;

var
  N, M, K: Integer;
  A, B, C: TSet;
  v: Char;
begin
  Keys;
  N := 0;
  M := 0;
  repeat
    v := ReadKey; { Получаем номер действия }
    if v in ['3'..'6'] then Print_Sets(A, B, N, M);
    case v of
      '1':
        begin
          WriteLn('Введите множество A:');
          Set_Input(A, N);
          WriteLn('Готово.');
          WriteLn;
        end;
      '2':
        begin
          WriteLn('Введите множество B:');
          Set_Input(B, M);
          WriteLn('Готово.');
          WriteLn;
        end;
      '3': if Incl(A, B, N, M) then WriteLn('A входит в B') else WriteLn('A не входит в B');
      '4':
        begin
          WriteLn('Объединение A и B:');
          Union(C, K, A, B, N, M);
          Print(C, K);
        end;
      '5':
        begin
          WriteLn('Пересечение A и B:');
          Product(C, K, A, B, N, M);
          Print(C, K);
        end;
      '6':
        begin
          WriteLn('Разность A \ B:');
          Diff(C, K, A, B, N, M);
          Print(C, K);
        end;
      '0': Keys;
    end;
  until v = #27;
end.
