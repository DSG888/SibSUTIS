{
Лабораторная работа № 6  Поиск компонент связности 
Граф задан его матрицей смежности. Требуется определить количество компонент связности этого графа. При этом должны быть конкретно перечислены вершины, входящие в каждую компоненту связности.
Пользователю должна быть предоставлена возможность редактировать исходную матрицу, т.е. изменять исходный граф без выхода из программы. Предусмотреть также возможность изменения количества вершин.
При выполнении работы разрешается (даже рекомендуется!) использовать матрицу бинарных отношений из лабораторной работы №2.
Вход  программы: число вершин графа и матрица смежности.
Выход: разбиение множества вершин на подмножества, соответствующие компонентам связности.
Дополнительно: 
Заданный граф – ориентированный. Выполнять поиск компонент сильной связности.
}

program laba5;

uses  Crt, SKUtil, Objects;

var
  TopsCol: Integer;  {Число вершин графа} 
  PMatr: MatrPtr;  {Матрица смежности графа}
  Queue: PQueue;     {Очередь для обхода}
  PList: PTops;  {Список для хранения пройденных вершин}


{Функция вывода главного меню программы}
function CreateMenu: Char;
begin
  clrscr;
  Writeln('***** Поиск компонент связности неориентированного графа *****');
  WriteLn('1 Ввод матрицы смежности графа');
  WriteLn('2 Генерация матрицы смежности графа');
  WriteLn('3 Просмотр матрицы смежности графа');
  WriteLn('4 Поиск компонент связности графа');
  Writeln('ESC - Выход');
  CreateMenu := ReadKey;
end ;

{Процедура ожидания нажатие клавиши ESC либо ENTER}
procedure StopKey;
begin
  WriteLn('Для продолжения нажмте клавишу ESC или ENTER...');
  WriteLn;
  while not (ReadKey in [#27, #13]) do;
end;


{Функция определения симметричности матрицы.}
function Is_Simmetr(TmpMatr: MatrPtr): Boolean;
var
  i, j: Integer;
begin
  Is_Simmetr := True;
  With TmpMatr^ do begin
    for i := 1 to RowValue do
      for j := 1 to Colvalue do
        if GetElement(TmpMatr, i, j) <> GetElement(TmpMatr, j, i) then begin
          Is_Simmetr := False;
          Break;
        end;
    end;
end;

procedure PrintMatr;
var
  i, j: Integer;
  s: string;
begin
  if PMatr = nil then Exit;
  with PMatr^ do begin
    Write('    ');
    for i := 1 to TopsCol do begin
       Str(i, s);
       Write('A' + s);
       Write(' ');
    end;
    WriteLn;

    for i := 0 to RowValue - 1 do begin
      for j := 0 to ColValue do begin
        Str(i + 1, s);
        if (j = 0) and (i < TopsCol) then begin
          Write('A' + s);
          Write(' ');
        end;
        if (j > 0) then begin
          Write('  ');
          Write(GetElement(PMatr, i + 1, j));
        end;
      end;
      WriteLn;
    end;
  end;
end;


procedure CreateMatrix;
var
  i, j, k: Integer;
  s1, s2: string;
begin
  clrscr;
  ClearMemMatrix(PMatr);
  Write('Введите количество вершин графа: ');
  Read(TopsCol);
  WriteLn;
  PMatr := CreateMatr(TopsCol, TopsCol);
  
  with PMatr^ do begin
    PrintMatr;
    WriteLn;
    for i := 1 to RowValue do begin
      for j := 1 to ColValue do begin
        Str(i, s1);
        Str(j, s2); 
        repeat       
          Write('Введите элемент A(' + s1 + ',' + s2 + ') (Количество рёбер): ');
          Read(k);
          if (k < 0) then begin
            WriteLn;
            WriteLn;
            WriteLn('Некорректный ввод! В матрице смежности должны быть элементов больее 0');
            WriteLn;
            WriteLn;
          end;
        Until (k >= 0);
        SetElement(PMatr, i, j, k);
      end;
    end;

    WriteLn;
    WriteLn('Матрица смежности:');
    PrintMatr;

    WriteLn;
    WriteLn;

    if not is_simmetr(PMatr) then begin
       ClearMemMatrix(PMatr); TopsCol := 0;
       WriteLn('Матрица смежности неориентированного графа должна быть симметричной!');
       WriteLn('Матрица смежности очищена.Необходимо повторить ввод матрицы.');
       WriteLn;
       WriteLn;
    end ;
  end;
  StopKey;
end;


procedure GenerateMatr;
var
  i, j: Integer;
begin
  clrscr;
  ClearMemMatrix(PMatr);
  TopsCol := 7;
  PMatr := CreateMatr(TopsCol, TopsCol);
  with PMatr^ do begin
    for i := 1 to RowValue do begin
      for j := 1 to ColValue do begin
         if ((i = 1) and (j = 3)) or
            ((i = 2) and (j = 5)) or
            ((i = 3) and (j = 1)) or
            ((i = 3) and (j = 4)) or
            ((i = 4) and (j = 3)) or
            ((i = 4) and (j = 7)) or
            ((i = 5) and (j = 2)) or
            ((i = 5) and (j = 6)) or
            ((i = 7) and (j = 4)) 
         then
           SetElement(PMatr, i, j, 1);
      end;
    end;
  end;
  WriteLn;
  WriteLn('Матрица смежности');
  PrintMatr;
  StopKey;
end;

procedure ViewMatr;
begin
  clrscr;
  WriteLn('***** Матрица смежности графа *****');
  WriteLn;
  PrintMatr;
  StopKey;
end;


procedure ClearList;
var
  ps, ps1: PTops;
begin
  ps := PList;
  while ps <> nil do begin
    ps1 := ps;
    ps := ps1^.NextItem;
    Dispose(ps1);
  end;
  PList := nil;
end;


procedure PutList(var TmpList: PTops; Co: Integer);
var
  ps, ps1: PTops;
begin
  ps := TmpList;
  {Устанавливаем указатель в конец списка}
  if ps <> nil then begin
    while ps^.NextItem <> nil do
      ps := ps^.NextItem;
  end;

  {Выделение память под элемент}
  New(ps1);
  ps1^.Co := Co;
  ps1^.NextItem := nil;

  if ps <> nil then
    ps^.NextItem := ps1
  else
    TmpList := ps1;
end;


{Функция проверки наличия вершины в списке}
function RecExists(Co: Integer): Boolean;
var
  Pt: PTops;
begin
  RecExists := False;
  Pt := PList;
  while (pt <> nil) do begin
    if (pt^.Co = Co) then begin
      RecExists := True;
      Break;
    end;
    pt := pt^.nextItem;
  end;
end;

{Функция вывода компоненты связности на экран}
function GetTopsLink(TmpList: PTops): string;
var
  s, s1: string;
  pt: PTops;
begin
  s1 := '';
  pt := TmpList;
  while pt <> nil do begin
    if s1 <> '' then s1 := s1 + ' - ';
    Str(pt^.Co, s);
    s1 := s1 + 'A' + s;
    pt := pt^.NextItem;
  end;
  GetTopsLink := s1;
end;


procedure isFindLink(StartNode: Integer);
var
  i, j, x, k: Integer;
  ps: PTops; {Список вершин в компоненте связности}
begin
  Queue^.Clear;  {Очищаем очередь}
  i := StartNode;  {Вершина, с которой начинаем обход}
  Queue^.PutItem(i); {Заносим вершину в очередь}
  PutList(PList, i); {Помечаем вершину}

  ps := nil; 

  PutList(ps, i); {Заносим стартовую вершину в начало списка}

  repeat
    x := Queue^.GetItem;
    with PMatr^ do begin
      for j := 1 to ColValue do begin
        k := GetElement(PMatr, x, j); {Проверим связь вершин по матрице смежности}
        if (k > 0) then begin
           if not RecExists(j) then begin 
	            {Вершины с номерами X и J связаны, и вершина J еще не в очереди}
              Queue^.PutItem(j); {Заносим вершину в очередь}
              PutList(PList, j); {Помечаем вершину, как пройденную}
              PutList(ps, j); {Заносим следующую вершину в  список текущей компоненты связности}
           end;
        end;
      end;
    end;
  until Queue^.Head = nil; {Выполняем обход, пока очередь не станет пустой}

  {Вывод компоненты связности на экран}
  WriteLn(GetTopsLink(ps));
end;


procedure SearchAllLinks;
var
  i: Integer;
  s, sl: string;
begin
  clrscr;  
  WriteLn('***** Поиск компонент связности графа *****');
  if TopsCol = 0 then begin
    WriteLn('Не задан граф! Для поиска компонент связности необходимо задайть граф !');
    StopKey;
    Exit;
  end;

  
  ClearList; {Очиска списка}
  WriteLn;
  WriteLn('** Матрица смежности **');
  PrintMatr;
  WriteLn;
  
  WriteLn('** Компоненты связности **');
  WriteLn;
  {Производим перебор по всем вершинам, и пытаемся от каждой найти маршруты}
  for i := 1 to TopsCol do begin
    if not RecExists(i) then
      isFindLink(i);
  end;

  StopKey;
end;


var
  ch: Char;
begin
  PMatr := nil;
  PList := nil;
  Queue := nil ;
  TopsCol := 0;
  Queue := New(PQueue, Init);
  repeat
    ch := createMenu;
    case ch of
      '1': CreateMatrix;
      '2': GenerateMatr;
      '3': ViewMatr;
      '4': SearchAllLinks;
   end;
  until ch = #27;
  if PMatr <> nil then ClearMemMatrix(PMatr);
  if PList <> nil then ClearList;
  if Queue <> nil then Dispose(Queue);
end.
