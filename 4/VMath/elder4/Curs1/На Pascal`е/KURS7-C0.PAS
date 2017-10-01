unit  kurs7;


interface

const m=3;n=4;k=2;
type  m1=array[1..m,1..n] of integer;
      m2=array[1..m,1..k] of integer;
      m3=array[1..k,1..n] of integer;
procedure zapoln(l,m:integer);

implementation

 procedure zapoln1(x:m1);
  var i,j:integer;
  begin
    randomize;
    for i:=1 to m do
      for j:=1 to k do
        x[i,j]:=random(10)-5;
  end;

 procedure zapoln2(x:m2);
  var i,j:integer;
  begin
    randomize;
    for i:=1 to k do
      for j:=1 to n do
        x[i,j]:=random(10)-5;
  end;

 procedure multiply;
  var i,j,h:integer;
  d:m1; b:m2; e:m3;
  begin
    zapoln1(b);
    zapoln2(e);
    for i:=1 to m do
      for j:=1 to n do begin
        s:=0;
        for h:=1 to k do
          s:=s+b[i,h]*e[h,j];
        d[i,j]:=s;
      end;

end.