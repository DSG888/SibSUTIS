library Project1;

{ Important note about DLL memory management: ShareMem must be the
  first unit in your library's USES clause AND your project's (select
  Project-View Source) USES clause if your DLL exports any procedures or
  functions that pass strings as parameters or function results. This
  applies to all strings passed to and from your DLL--even those that
  are nested in records and classes. ShareMem is the interface unit to
  the BORLNDMM.DLL shared memory manager, which must be deployed along
  with your DLL. To avoid using BORLNDMM.DLL, pass string information
  using PChar or ShortString parameters. }

uses
  SysUtils,
  Classes;

{$R *.res}

function f (s:string):string ;
var
i,g:integer;
begin
i:=length(s);
for g:=1 to length(s) do
begin
 while (s[1]=' ') do
  begin
   delete (s,1,1);
   i:=i-1;
  end;
 while (s[g]=' ') and (s[g+1]=' ') do
  begin
   delete (s,g,1);
   i:=i-1;
  end;
 while (s[i]=' ') do
  begin
   delete (s,i,1);
   i:=i-1;
  end;
result:=s;
end;
end;
exports f;
end.