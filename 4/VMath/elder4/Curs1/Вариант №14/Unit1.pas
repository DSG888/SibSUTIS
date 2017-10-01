unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;

type
  TForm1 = class(TForm)
    procedure FormCreate(Sender: TObject);
    procedure FormPaint(Sender: TObject);
    procedure FormResize(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

const
  epsr = 0.0001;
  epsmh = 0.01;
  epskr = 0.001;
  n = 20;
  
type
  vect = record
    a, b: real;
  end;
  rect = record
    X, Y: real;
  end;  
var
  Form1: TForm1;
  j0: vect;
  x0, h, k: real;
  a: array[0..120] of rect;
  C: array[0..20, 0..20] of real;
  D: array[0..20] of real;
  M: array[0..20] of real;

implementation

//Функция выдает значение функции при заданных параметрах
function F(ytt: real; y, yt, x: real): real;
begin
  Result := ytt + cos(ytt) - cos(yt + x*x) + 2.9*y;
end;

//Вычисление корня уравнения методом хорд
function MH(y, yt, xy: real): real;
 var
  a, b, c, x, eps: real;
begin
  a := -10;
  b := 10;
  c := (a*F(b, y, yt, xy) - b*F(a, y, yt, xy)) / (F(b, y, yt, xy) - F(a, y, yt, xy));
  if f(c, y, yt, xy) = 0 then
  begin
    Result := x;
    exit;
  end
  else
  begin
    while (Abs(b - a) > epsmh) do
    begin
      if ((F(c, y, yt, xy) + epsmh) > 0)and((F(c, y, yt, xy) - epsmh) < 0) then
      begin
        Result := c;
        exit;
      end;
      if F(c, y, yt, xy)*F(a, y, yt, xy) < 0 then
        b := c else a := c;
      c := (a*F(b, y, yt, xy) - b*F(a, y, yt, xy)) / (F(b, y, yt, xy) - F(a, y, yt, xy));
    end;
    x := (a*F(b, y, yt, xy) - b*F(a, y, yt, xy)) / (F(b, y, yt, xy) - F(a, y, yt, xy));;
  end;
  Result := x;
end;

//Задание начальных значений
procedure FlashNew;
begin
  j0.a := 1;         // y(0)=1
  j0.b := 2;         // y"(1)=0.2
  x0 := 0;
  h := 0.1;
end;

//Вычисление следующего значения функций
function J_X(input: vect; x: real): vect;
 var
  o: vect;
begin
  o.a := input.b;
  o.b := MH(input.a, input.b, x);
  Result := o;
end;

{function J_X(input: vect; x: real): vect;
 var
  o: vect;
begin
  o.a := input.b;
  o.b := 1 - input.a + 2 * input.b * x;
  Result := o;
end;}

//Функция вычисления суммы вектора и вектора умноженого на коэффицент
function SummJ(a1: vect; a2: vect; k: real): vect;
begin
  Result.a := a1.a + a2.a * k;
  Result.b := a1.b + a2.b * k;
end;

//Функция вычисления значения вектора методом Рунге-Кутта 4 порядка 
function EvalJ(new: vect; x, ht: real): vect;
 var
  j1, j2, j3, j4: vect;
begin
    j1.a := J_X(new, x).a;
    j1.b := J_X(new, x).b;
    j2.a := J_X(SummJ(new, j1, ht / 2), x + ht / 2).a;
    j2.b := J_X(SummJ(new, j1, ht / 2), x + ht / 2).b;
    j3.a := J_X(SummJ(new, j2, ht / 2), x + ht / 2).a;
    j3.b := J_X(SummJ(new, j2, ht / 2), x + ht / 2).b;
    j4.a := J_X(SummJ(new, j3, ht), x + ht).a;
    j4.b := J_X(SummJ(new, j3, ht), x + ht).b;
    Result.a := new.a + (ht / 6)*(j1.a + 2*j2.a + 2*j3.a + j4.a);
    Result.b := new.b + (ht / 6)*(j1.b + 2*j2.b + 2*j3.b + j4.b);
end;

//Функция вычисления всех значений от x0 с шагом h
function Runge(n: integer; flag: boolean): vect;
 var
  j, j1, j2: vect;
  x, ht: real;
  i: integer;
begin
  j := j0;
  x := x0;
  i := 0;
  while(true)do
  begin
    j1 := EvalJ(j, x, h);
{    ht := ht / 2;
    j2 := EvalJ(j, x, ht);
    if abs(j1.b - j2.b) < (15 * epsr) then
    begin
      ht := h;
      ShowMessage('Y(x) = ' + FloatToStr(j2.a) + '; Y^(x) = ' + FloatToStr(j2.b) +  '; x = ' + FloatToStr(x) + ';');
      x := x + ht;
      j := j2;
      inc(i);
      if (i >= n) then break;
    end;}
    if flag then
    begin
      a[i].X := x;
      a[i].Y := j1.a;
    end;
    j := j1;
    x := x + h;
    inc(i);
    if (i >= n) then break;
  end;
  Result := j;
end;

//Сплайны
//Функция вычисления значения h в определенном месте
function hp(i: integer): real;
begin
  Result := a[i].X - a[i - 1].X;
end;

//Функция нахождения коэффицента домножения строки(метод Гаусса, модифицированный)
function SearchKoeff(q, w: integer): real;
begin
  Result := -c[q, w] / c[w, w];
end;

//Процедура домножения строки на коэффицент(метод Гаусса, модифицированный)
procedure MultyKoeff(q, w, r: integer);
 var
  i: integer;
begin
  for i := w to n - 2 do
    c[q, i] := c[q, i] + k * c[r, i];
end;

//Процедура перестановки строк(метод Гаусса, модифицированный)
procedure RevertString(i1, i2: integer);
 var
  t: real;
  i: integer;
begin
  for i := 0 to n - 2 do
  begin
    t := c[i1, i];
    c[i1, i] := c[i2, i];
    c[i2, i] := t;
  end;
end;

//Процедура включения модернизации в метод Гаусса(метод Гаусса, модифицированный)
procedure EnableModer(r: integer);
 var
  i, p: integer;
  max: real;
begin
  if r < n then
  begin
    max := Abs(c[r, r]);
    p := r;
    for i := r to n - 2 do
      if Abs(c[i, r]) > max then
      begin
        max := Abs(c[i, r]);
        p := i;
      end;
    if (p <> r) then RevertString(p, r);
  end;
end;


//Процедура первого прохода(метод Гаусса, модифицированный)
procedure GoToForward;
 var
  i, j: integer;
begin
  j := 0;
//  t := 0;
  while j <= (n - 2) do
  begin
    EnableModer(j);
    for i := j + 1 to n - 2 do
    begin
      if c[j, j] <> 0 then
      begin
        k := SearchKoeff(i, j);
        MultyKoeff(i, 0, j);
      end;
    end;
    inc(j);
  end;
end;


//Процедура обратного прохода и вычисления конкретных значений(метод Гаусса, модифицированный)
procedure GoToBack;
 var
  i, j: integer;
  te: real;
begin
  for i := n - 3 downto 0 do
  begin
    te := c[i, n - 2];
    for j := (i) to n - 3 do
    begin
      te := te - c[i, j] * m[j];
    end;
    if c[i, i] <> 0 then m[i] := te / c[i, i];
  end;
  for i := n - 1 downto 1 do
    m[i] := m[i - 1];
  m[n - 1] := 0;
  m[0] := 0;
end;

//Вычисление моментов, столбца d, подсчет матрицы С.
procedure EvaluateMoment;
 var
  i, j, k: integer;
  t: real;
begin
  //Вычисляем матрицу С
  for i := 1 to n - 2 do
    for j := 1 to n - 2 do
    begin
      if (i = j) then C[i - 1, j - 1] := (hp(i) + hp(i + 1)) / 3;
      if (j = i + 1) then C[i - 1, j - 1] := hp(i + 1) / 6;
      if (j = i - 1) then C[i - 1, j - 1] := hp(i) / 6;
      if (abs(i - j)>=2) then C[i - 1, j - 1] := 0;
    end;
  //Вычисляем столбец d
  for i := 1 to n - 2 do
  begin
    d[i - 1] := ((a[i + 1].y - a[i].y)/ hp(i + 1)) - ((a[i].y - a[i - 1].y) / hp(i));
  end;
  //Дополняем матрицу С столбцом d
  for i := 0 to n - 3 do
    C[i, n - 2] := d[i];
  //Считаем моменты с помощью метода Гаусса
  GoToForward;
  GoToBack;
end;

//Вычисление номера нужного аргумента
function Inter(x: real): integer;
 var
  i: integer;
begin
  for i := 0 to n - 2 do
    if (x >= a[i].x)and(x < a[i + 1].x) then
    begin
      Result := i + 1;
      exit;
    end;
end;

//Непосредственно интерполяция кубическими сплайнами(итоговая формула)
function Spline(x: real): real;
 var
  i: integer;
begin
  i := Inter(x);
  Result := m[i - 1]*(a[i].x - x)*(a[i].x - x)*(a[i].x - x)/(6*hp(i))+
            m[i]*(x - a[i - 1].x)*(x - a[i - 1].x)*(x - a[i - 1].x)/(6*hp(i))+
            (a[i - 1].y - m[i - 1]*hp(i)*hp(i)/6)*((a[i].x - x)/hp(i))+
            (a[i].y - m[i]*hp(i)*hp(i)/6)*((x - a[i - 1].x)/hp(i));
end;

//Конец

{$R *.dfm}

//Вывод элементов массива
procedure DrawSqrt;
 var
  s: string;
  i, j: integer;
begin
  s := '';
  for i := 0 to n do
      s := s + FloatToStr(a[i].X) + ' ';
  ShowMessage(s);
end;

//Процедура вывода результата интерполяции в виде графика.
procedure DrawGraph;
 var
  coeffx, coeffy, cell: real;
  pt: array of TPoint;
  iter, i, xk, yk: integer;
  o: real;
  func: vect;
begin
  coeffx := 154;
  coeffy := 24;
  xk := 00;
  yk := 00;
  iter := 1100 * Round(abs(a[0].x - a[n - 1].x));
  cell := 1;
  SetLength(pt, iter);
  Form1.Canvas.Pen.Color := clWhite;
  i := 0;
  o := a[0].x;
  while(o < a[n - 4].x)do
  begin
    pt[i].X := Round((o) * coeffx) + Form1.ClientWidth div 2;
    pt[i].Y := Form1.ClientHeight div 2 - Round(Spline(o)*coeffy);
    o := o + 0.01;
    inc(i);
  end;
  x0 := 0;
  h := 0.05;
  func := Runge(101, true);
  with Form1.Canvas do
  begin
    for i := 0 to i - 2 do
    begin
      Pen.Color := clLime;
      MoveTo(pt[i].x - xk, pt[i].y - yk);
      LineTo(pt[i + 1].x - xk, pt[i + 1].y - yk);
    end;
    for i := 16 to 100 - 1 do
    begin
      Pen.Color := clGray;
      MoveTo(Round(a[i].X * coeffx) + Form1.ClientWidth div 2,
       Form1.ClientHeight div 2 - Round(a[i].Y*coeffy));
      LineTo(Round(a[i + 1].X * coeffx) + Form1.ClientWidth div 2,
       Form1.ClientHeight div 2 - Round(a[i + 1].Y*coeffy));
    end;
    Pen.Color := clWhite;
    MoveTo(Form1.ClientWidth div 2 - xk, 0);
    LineTo(Form1.ClientWidth div 2 - xk, Form1.ClientHeight);
    MoveTo(0, Form1.ClientHeight div 2 - yk);
    LineTo(Form1.ClientWidth, Form1.ClientHeight div 2 - yk);
    Pen.Color := clRed;
    for i := 0 to n - 1 do
    begin
      if (i mod 4 = 0) then
      begin
        pt[i].X := Round(a[i].x * coeffx) + Form1.ClientWidth div 2 - xk;
        pt[i].Y := Form1.ClientHeight div 2 - Round(a[i].y * coeffy) - yk;
        Ellipse(pt[i].x - 3, pt[i].y - 3, pt[i].x + 3, pt[i].y + 3);
      end;  
    end;
  end;
end;


procedure TForm1.FormCreate(Sender: TObject);
 var
  a: vect;
  i: real;
begin
  FlashNew;
  i := -10;
  while(true)do
  begin
    j0.b := i;
    a := Runge(10, false);
    if (a.b > 0.2) then i := i + 0.01 else i := i - 0.01;
    if ((a.b + 0.01) > 0.2)and((a.b - 0.01) < 0.2) then break;
  end;
  j0.b := i;
  h := 0.05;
  x0 := 0;
  a := Runge(22, true);
end;

procedure TForm1.FormPaint(Sender: TObject);
begin
  DrawGraph;
end;

procedure TForm1.FormResize(Sender: TObject);
begin
  Form1.Repaint;
end;

end.
