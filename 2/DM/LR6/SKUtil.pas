unit SKUtil;

interface

uses Objects;


type
  {Структура для хранения списка пройденных вершин}
  PTops = ^TTops;
  TTops = record
    Co : Integer;
    NextItem: PTops;
  end;


  {Очередь}
  PQueue = ^TQueue;
  TQueue = object(TObject)
    Head: PTops;  {Указатель на начало очереди}
    Tail: PTops;  {Указатель на конец очереди}
    constructor Init; {Конструктор}
    destructor Done; virtual;  {Деструктор}
    procedure Clear;  {Очистка очереди}
    procedure PutItem(Data: Integer); {Добавление элемента в очередь}
    function GetItem: Integer; {Извлечение элемента из очереди}
  end;


   MatrRec = record
     RowValue   : byte;
     ColValue   : byte;
     PDim : pointer;
   end;

   MatrPtr = ^MatrRec;


{ Создание прямоугольной матрицы }
function  CreateMatr(RValue,CValue : byte) : MatrPtr;

{ Заполнение матрицы указанным числом }
function  FillMatr(Mp: MatrPtr; El : Integer) : boolean;

{ Отображение матрицы на консоль }
function PrintMatr(Mp : MatrPtr; Im: byte) : boolean;

{ Освобождение памяти выделенное под матрицу, в случае успеха возвращает True }
function  ClearMemMatrix(var Mp : MatrPtr) : boolean;

{ Присвоение значения определённого элемента матрицы }
procedure SetElement(Mp : MatrPtr;RValue,CValue : byte; Me : Integer);

{ Возвращает значение заданного элемента матрицы }
function  GetElement(Mp : MatrPtr;RValue,CValue : byte) : Integer;

{ Умножает соответствующие элементы матриц одинакового размера без сложения элементов}
function MultMatrixNotAdd(Mp1,Mp2 : MatrPtr) : MatrPtr;

{  Умножение матрицы на матрицу алгебраически }
function MultipleMatr(Mp1,Mp2 : MatrPtr) : MatrPtr;

{  Транспонирует матрицу }
function TranspMatr(Mp : MatrPtr) : MatrPtr;

{  Умножает элементы матриц одинакового размера алгебраически с логическим сложением}
function MultMatrixLogical(Mp1,Mp2 : MatrPtr) : MatrPtr;


implementation

constructor TQueue.Init;
begin
  Head := nil;
  Tail := nil;
end;

destructor TQueue.Done;
begin
  Clear;
end;

procedure TQueue.Clear;
var
  p, p1: PTops;
begin
  p := Head;
  while (p <> nil) do begin
    p1 := p;
    p := p1^.nextItem;
    Dispose(p1); {Освобождаем память, занимаемую эелементом очереди}
  end;
end;


{Процедура добавления эелемента в очередь}    
procedure TQueue.PutItem(Data: Integer);
var
  p: PTops;
begin
  New(P);
  P^.Co := Data;
  P^.NextItem := nil;

  if Head <> nil then
    Tail^.NextItem := P
  else
    Head := P;
  Tail := P;
end;

{Извлечение элемента из очереди}
function TQueue.GetItem: Integer;
var
  p: PTops;
begin
  GetItem := 0;  {Значение, если очередь пуста}
  p := Head;
  if p <> nil then begin
    Head := p^.NextItem;
    GetItem := p^.Co;
    Dispose(p);
  end;
end;


{ Создание прямоугольной матрицы }
function  CreateMatr(RValue,CValue : byte) : MatrPtr;
var
  TmpPtr : MatrPtr;
begin
  TmpPtr:= nil;
  GetMem(TmpPtr,SizeOf(MatrRec));
  if TmpPtr = nil then begin
    CreateMatr:= nil;
    Exit;
  end;
  with TmpPtr^ do begin
    RowValue:= RValue;
    ColValue:= CValue;
    PDim:= nil;
    GetMem(PDim,RValue*CValue*SizeOf(Integer));
    if PDim = nil then begin
      FreeMem(TmpPtr,SizeOf(MatrRec));
      CreateMatr:= nil;
      Exit;
    end;
  end;
  FillMatr(TmpPtr,0);
  CreateMatr:= TmpPtr;
end;


{  Освобождение памяти выделенное под матрицу, в случае успеха возвращает True }
function ClearMemMatrix(var Mp : MatrPtr) : boolean;
begin
  if Mp = nil then ClearMemMatrix:= False
  else with Mp^ do begin
    if PDim <> nil then
      FreeMem(PDim,RowValue*ColValue*SizeOf(Integer));
    FreeMem(Mp,SizeOf(MatrRec));
    Mp:= nil;
    ClearMemMatrix:= True;
  end;
end;


{ Отображение матрицы на консоль }
function PrintMatr(Mp : MatrPtr; Im: byte) : boolean;
var
  i,j : byte;
begin
  if Mp = nil then PrintMatr:= False
  else with Mp^ do begin
    for i:= 1 to RowValue do begin
      for j:= 1 to ColValue do
        write(GetElement(Mp,i,j) : Im);
      writeln;
    end;
    PrintMatr:= True;
  end;
end;


{ Заполнение матрицы указанным числом }
function  FillMatr(Mp: MatrPtr; El : Integer) : boolean;
var
  i,j : byte;
begin
  if Mp = nil then FillMatr:= False
  else with Mp^ do begin
    for i:= 1 to RowValue do
      for j:= 1 to ColValue do
        SetElement(Mp,i,j,El);
    FillMatr:= True;
  end;
end;


{ Присвоение значения определённого элемента матрицы }
procedure SetElement(Mp : MatrPtr;RValue,CValue : byte; Me : Integer);
var
  TmpPtr : ^Integer;
begin
  if Mp <> nil then
    if (RValue <> 0) or (CValue <> 0) then with Mp^ do begin
      pointer(TmpPtr):= pointer(PDim);
      Inc(TmpPtr,RowValue*(CValue-1)+RValue-1);
      TmpPtr^:= Me;
    end;
end;


{  Возвращает значение заданного элемента матрицы }
function  GetElement(Mp : MatrPtr;RValue,CValue : byte) : Integer;
var
  TmpPtr : ^Integer;
begin
  if Mp <> nil then begin
    if (RValue <> 0) and (CValue <> 0) then with Mp^ do begin
      pointer(TmpPtr):= pointer(PDim);
      Inc(TmpPtr,RowValue*(CValue-1)+RValue-1);
      GetElement:= TmpPtr^;
    end else GetElement:= 0;
  end else GetElement:= 0;
end;


{  Транспонирует матрицу }
function TranspMatr(Mp : MatrPtr) : MatrPtr;
var
  i,j     : byte;
  TmpPtr : MatrPtr;
begin
  if (Mp <> nil) or (Mp^.PDim <> nil) then
   with Mp^ do begin
    TmpPtr:= CreateMatr(ColValue,RowValue);
    for i:= 1 to RowValue do
      for j:= 1 to ColValue do
        SetElement(TmpPtr,j,i,GetElement(Mp,i,j));
    TranspMatr:= TmpPtr;
  end else TranspMatr:= nil;
end;


{  умножает соответствующие элементы матриц одинакового размера без сложения элементов}
function MultMatrixNotAdd(Mp1,Mp2 : MatrPtr) : MatrPtr;
var
  TmpPtr : MatrPtr;
  i,j,k   : byte;
begin
  if (Mp1 <>  nil) and (Mp2 <> nil) then begin
    TmpPtr:= CreateMatr(Mp1^.RowValue,Mp1^.ColValue);
    if TmpPtr = nil then begin
      MultMatrixNotAdd:= nil;
      Exit;
    end;
    for i:= 1 to TmpPtr^.RowValue do
      for j:= 1 to TmpPtr^.ColValue do
          SetElement(TmpPtr,i,j,
            GetElement(Mp1,i,j)*GetElement(Mp2,i,j));
    MultMatrixNotAdd:= TmpPtr;
  end else MultMatrixNotAdd :=nil;
end;




{  умножает матрицу на матрицу алгебраически }
function MultipleMatr(Mp1,Mp2 : MatrPtr) : MatrPtr;
var
  i,j,k   : byte;
  TmpPtr : MatrPtr;
begin
  if (Mp1 <>  nil) and (Mp2 <> nil) then begin
    TmpPtr:= CreateMatr(Mp1^.RowValue,Mp2^.ColValue);
    if TmpPtr = nil then begin
      MultipleMatr:= nil;
      Exit;
    end;
    for i:= 1 to TmpPtr^.RowValue do
      for j:= 1 to TmpPtr^.ColValue do
        for k:= 1 to Mp1^.ColValue do
          SetElement(TmpPtr,i,j,GetElement(TmpPtr,i,j)+
            GetElement(Mp1,i,k)*GetElement(Mp2,k,j));
    MultipleMatr:= TmpPtr;
  end else MultipleMatr:= nil;
end;

function LogicSumm(I1, I2: Integer): Integer;
begin
  if (I1 = 0) and (I2 = 0) then
    LogicSumm := 0
  else
    LogicSumm := 1;
end;

{  Умножает элементы матриц одинакового размера алгебраически с логическим сложением}
function MultMatrixLogical(Mp1,Mp2 : MatrPtr) : MatrPtr;
var
  i,j,k   : byte;
  TmpPtr : MatrPtr;
begin
  if (Mp1 <>  nil) and (Mp2 <> nil) then begin
    TmpPtr:= CreateMatr(Mp1^.RowValue,Mp1^.ColValue);
    if TmpPtr = nil then begin
      MultMatrixLogical:= nil;
      Exit;
    end;
    for i:= 1 to TmpPtr^.RowValue do
      for j:= 1 to TmpPtr^.ColValue do
        for k:= 1 to Mp1^.ColValue do
          SetElement(TmpPtr,i,j, LogicSumm(GetElement(TmpPtr,i,j),
            GetElement(Mp1,i,k)*GetElement(Mp2,k,j)));
    MultMatrixLogical:= TmpPtr;
  end else MultMatrixLogical:= nil;
end;

end.
