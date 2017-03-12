unit Unit2;

interface
function conv(s:string):string;
implementation
 function conv(s:string):string;
 const
tabb='ABCDEFGHIJKLMNOPQRSTUVWXYZÉÖÓÊÅÍÃØÙÇÕÚÔÛÂÀÏĞÎËÄÆİß×ÑÌÈÒÜÁŞ';
tabm='abcdefghijklmnopqrstuvwxyzéöóêåíãøùçõúôûâàïğîëäæıÿ÷ñìèòüáş';
var i:integer;
begin
for i := 1 to length(s) do
  if pos(s[i],tabm)>0 then
  s[i]:=tabb[pos(s[i], tabm)];
  result:=s;
end;
end.
