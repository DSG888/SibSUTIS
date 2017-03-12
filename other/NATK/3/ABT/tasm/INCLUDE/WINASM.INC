;WindowsConA.inc - включаемый файл для консольных приложений 
;		(аналог windows.h в С) содержащий 
;		описание необходимых в программе на ассемблере 
;		структур и констант Windows
;-----------------------------------------------------------------

; #########################################################################

NULL	equ	0
TCHAR	equ	<db>
UCHAR	equ	<db>
LPTSTR	equ	<dd>
USHORT	equ	<dw>
LPBYTE	equ	<dd>
HANDLE	equ	<dd>
UINT	equ	<dd>	;32-битное целое
ULONG	equ	<dd>	;32-битный указатель на объект
WNDPROC	equ	<dd>
HWiND	equ	<dd>

ADDR	equ	<offset>

; #########################################################################

FALSE	equ	0
TRUE	equ	1

NULL	equ	0
ULONG	equ	<dd>
POINT	struc
x	ULONG	0
y	ULONG	0
	ends
GENERIC_READ	equ	80000000h
GENERIC_WRITE	equ	40000000h

OPEN_EXISTING	equ	3
OPEN_ALWAYS	equ	4

FILE_ATTRIBUTE_NORMAL	equ	00000080h
FILE_ATTRIBUTE_READONLY	equ	00000001h

FILE_SHARE_READ	equ	00000001h

FILETIME	struc
dwLowDateTime	dd	0  
dwHighDateTime	dd	0
	ends
; #########################################################################

POINT	struc
x	ULONG	0
y	ULONG	0
POINT	ends


MSG	struc
meshwnd	HWiND	0
mes	UINT	?
lParam 	UINT	?
wParam 	UINT	?
time	dd	0
POINT	struc	{}
MSG	ends

WNDCLASSEX	struc
cbSize	UINT	0
style	UINT	?
lpfnWndProc	WNDPROC	?
cbClsExtra	UINT	?
cbWndExtra 	UINT	?
hInstance	HANDLE	?
hIcon	UINT	?
hCursor	UINT	?
hbrBackground	UINT	?
lpszMenuName	ULONG	0	;по умолчанию без меню
lpszClassName	ULONG	?
hIconSm	UINT	0
WNDCLASSEX	ends

; #########################################################################


_BY_HANDLE_FILE_INFORMATION struc
dwFileAttributes	dd	0
ftCreationTime	FILETIME	<>
;FILETIME	struc	{}
ftLastAccessTime	FILETIME	<>
;FILETIME ftLastAccessTime; 
;FILETIME	struc	{}
ftLastWriteTime	FILETIME	<>
;FILETIME ftLastWriteTime; 
dwVolumeSerialNumber	dd	0     
nFileSizeHigh	dd	0 
nFileSizeLow	dd	0 
nNumberOfLinks	dd	0     
nFileIndexHigh	dd	0 
nFileIndexLow	dd	0     
ends

PAGE_WRITECOPY	equ	08h	;winnt.h
PAGE_READWRITE	equ	04h


SECTION_QUERY	equ	0001h	;winbase.h
SECTION_MAP_WRITE	equ	0002h

FILE_MAP_COPY	equ	SECTION_QUERY

FILE_MAP_WRITE	equ	SECTION_MAP_WRITE


;winnt.h
SECTION_QUERY	equ	0001h
SECTION_MAP_WRITE	equ	0002h
SECTION_MAP_READ	equ	0004h
SECTION_MAP_EXECUTE	equ	0008h
SECTION_EXTEND_SIZE	equ	0010h


STANDARD_RIGHTS_REQUIRED	equ	000F0000h
SECTION_QUERY	equ	0001h
SECTION_ALL_ACCESS	equ	STANDARD_RIGHTS_REQUIRED+SECTION_QUERY+SECTION_MAP_WRITE+SECTION_MAP_READ+SECTION_MAP_EXECUTE+SECTION_EXTEND_SIZE

FileMapAllAccess	equ	 SECTION_ALL_ACCESS


STD_INPUT_HANDLE	equ	-10	;winbase.h
STD_OUTPUT_HANDLE	equ	-11
STD_ERROR_HANDLE      equ	-12
;Режимы и флаги доступа к файлам (из winnt.h, winbase.h)

GENERIC_READ	=80000000h
GENERIC_WRITE	=40000000h

FILE_SHARE_READ	=00000001h
FILE_SHARE_WRITE	=00000002h

CREATE_NEW=1
CREATE_ALWAYS=2
OPEN_EXISTING=3
OPEN_ALWAYS=4
TRUNCATE_EXISTING=5

FILE_ATTRIBUTE_READONLY=00000001h
FILE_ATTRIBUTE_HIDDEN=00000002h
FILE_ATTRIBUTE_SYSTEM=00000004h
FILE_ATTRIBUTE_DIRECTORY=00000010h
FILE_ATTRIBUTE_ARCHIVE=00000020h
FILE_ATTRIBUTE_NORMAL=00000080h  
FILE_ATTRIBUTE_TEMPORARY=00000100h  
FILE_ATTRIBUTE_COMPRESSED=00000800h  

FILE_FLAG_WRITE_THROUGH=80000000h
FILE_FLAG_OVERLAPPED=40000000h
FILE_FLAG_NO_BUFFERING=20000000h
FILE_FLAG_RANDOM_ACCESS=10000000h
FILE_FLAG_SEQUENTIAL_SCAN=08000000h
FILE_FLAG_DELETE_ON_CLOSE=04000000h
FILE_FLAG_BACKUP_SEMANTICS=02000000h
FILE_FLAG_POSIX_SEMANTICS=01000000h

MOVEFILE_REPLACE_EXISTING=00000001h
MOVEFILE_COPY_ALLOWED=00000002h
MOVEFILE_DELAY_UNTIL_REBOOT=00000004h
MOVEFILE_WRITE_THROUGH=00000008h

FILE_BEGIN=0
FILE_CURRENT=1
FILE_END=2

FILE_CASE_SENSITIVE_SEARCH=00000001h  
FILE_CASE_PRESERVED_NAMES=00000002h  
FILE_UNICODE_ON_DISK=00000004h  
FILE_PERSISTENT_ACLS=00000008h  
FILE_FILE_COMPRESSION=00000010h  
FILE_VOLUME_IS_COMPRESSED=00008000h 

FS_CASE_IS_PRESERVED=FILE_CASE_PRESERVED_NAMES
FS_CASE_SENSITIVE=FILE_CASE_SENSITIVE_SEARCH
FS_UNICODE_STORED_ON_DISK=FILE_UNICODE_ON_DISK
FS_PERSISTENT_ACLS=FILE_PERSISTENT_ACLS
FS_VOL_IS_COMPRESSED=FILE_VOLUME_IS_COMPRESSED
FS_FILE_COMPRESSION=FILE_FILE_COMPRESSION

SECURITY_ATTRIBUTES struc
nLength dd	0
lpSecurityDescriptor	dd	0
bInheritHandle	dd	0
	ends

PAGE_READONLY=02     
PAGE_READWRITE=04     
PAGE_WRITECOPY=08     

STANDARD_RIGHTS_REQUIRED=000F0000h
SECTION_MAP_EXECUTE=0008h
SECTION_EXTEND_SIZE=0010h


SECTION_QUERY=01
SECTION_MAP_WRITE=02
SECTION_MAP_READ=04
SECTION_ALL_ACCESS=STANDARD_RIGHTS_REQUIRED+SECTION_QUERY+SECTION_MAP_WRITE+SECTION_MAP_READ+SECTION_MAP_EXECUTE+SECTION_EXTEND_SIZE



;FILE_MAP_COPY=SECTION_QUERY
;FILE_MAP_WRITE=SECTION_MAP_WRITE
FILE_MAP_READ=SECTION_MAP_READ
FILE_MAP_ALL_ACCESS=SECTION_ALL_ACCESS


;из wincon.h
CTRL_C_EVENT=0
CTRL_BREAK_EVENT=1
CTRL_CLOSE_EVENT=2
;// 3 is reserved!
;// 4 is reserved!
CTRL_LOGOFF_EVENT=5
CTRL_SHUTDOWN_EVENT=6

;из wincon.h
FOREGROUND_BLUE=0001h	;text color contains blue.
FOREGROUND_GREEN=0002h	;text color contains green.
FOREGROUND_RED=0004h	;text color contains red.
FOREGROUND_INTENSITY=0008h	;text color is intensified.
BACKGROUND_BLUE=0010h	;background color contains blue.
BACKGROUND_GREEN=0020h	;background color contains green.
BACKGROUND_RED=0040h	;background color contains red.
BACKGROUND_INTENSITY=0080h	;background color is intensified.

;из wincon.h
KEY_EVENT=0001h	;// Event contains key event record
MOUSE_EVENT=0002h	;// Event contains mouse event record
WINDOW_BUFFER_SIZE_EVENT=0004h	;// Event contains window change event record
MENU_EVENT=0008h	;// Event contains menu event record
FOCUS_EVENT=0010h	;// event contains focus change

;из wincon.h
RIGHT_ALT_PRESSED=0001h	;// the right alt key is pressed.
LEFT_ALT_PRESSED=0002h	;// the left alt key is pressed.
RIGHT_CTRL_PRESSED=0004h	;// the right ctrl key is pressed.
LEFT_CTRL_PRESSED=0008h	;// the left ctrl key is pressed.
SHIFT_PRESSED=0010h	;// the shift key is pressed.
NUMLOCK_ON=0020h	;// the numlock light is on.
SCROLLLOCK_ON=0040h	;// the scrolllock light is on.
CAPSLOCK_ON=0080h	;// the capslock light is on.
ENHANCED_KEY=0100h	;// the key is enhanced.

;из wincon.h
MOUSE_MOVED=0001h
DOUBLE_CLICK=0002h

;из winnt.h
DLL_PROCESS_ATTACH=1    
DLL_THREAD_ATTACH =2    
DLL_THREAD_DETACH =3    
DLL_PROCESS_DETACH=0    

; #########################################################################

;
; Class styles
;
CS_VREDRAW         = 0001h
CS_HREDRAW         = 0002h
CS_KEYCVTWINDOW    = 0004H
CS_DBLCLKS         = 0008h
;                    0010h reserved
CS_OWNDC           = 0020h
CS_CLASSDC         = 0040h
CS_PARENTDC        = 0080h
CS_NOKEYCVT        = 0100h
CS_SAVEBITS        = 0800h
CS_NOCLOSE         = 0200h
CS_BYTEALIGNCLIENT = 1000h
CS_BYTEALIGNWINDOW = 2000h
CS_GLOBALCLASS     = 4000h    ; Global window class

;
;  Predefined cursor & icon IDs
;
IDC_ARROW       = 32512
IDC_IBEAM       = 32513
IDC_WAIT        = 32514
IDC_CROSS       = 32515
IDC_UPARROW     = 32516
IDC_SIZE        = 32640
IDC_ICON        = 32641
IDC_SIZENWSE    = 32642
IDC_SIZENESW    = 32643
IDC_SIZEWE      = 32644
IDC_SIZENS      = 32645

IDI_APPLICATION = 32512
IDI_HAND        = 32513
IDI_QUESTION    = 32514
IDI_EXCLAMATION = 32515
IDI_ASTERISK    = 32516

IFNDEF  NOCOLOR

COLOR_SCROLLBAR           = 0
COLOR_BACKGROUND          = 1
COLOR_ACTIVECAPTION       = 2
COLOR_INACTIVECAPTION     = 3
COLOR_MENU                = 4
COLOR_WINDOW              = 5
COLOR_WINDOWFRAME         = 6
COLOR_MENUTEXT            = 7
COLOR_WINDOWTEXT          = 8
COLOR_CAPTIONTEXT         = 9
COLOR_ACTIVEBORDER        = 10
COLOR_INACTIVEBORDER      = 11
COLOR_APPWORKSPACE        = 12
COLOR_HIGHLIGHT           = 13
COLOR_HIGHLIGHTTEXT       = 14
COLOR_BTNFACE             = 15
COLOR_BTNSHADOW           = 16
COLOR_GRAYTEXT            = 17
COLOR_BTNTEXT             = 18

IFNDEF NOWIN31
COLOR_INACTIVECAPTIONTEXT = 19
COLOR_BTNHILIGHT          = 20
ENDIF

ENDIF   ;NOCOLOR

IFNDEF                  NOMB
MB_OK                   = 0000H
MB_OKCANCEL             = 0001H
MB_ABORTRETRYIGNORE     = 0002H
MB_YESNOCANCEL          = 0003H
MB_YESNO                = 0004H
MB_RETRYCANCEL          = 0005H

MB_ICONHAND             = 0010H
MB_ICONQUESTION         = 0020H
MB_ICONEXCLAMATION      = 0030H
MB_ICONASTERISK         = 0040H

MB_DEFBUTTON1           = 0000H
MB_DEFBUTTON2           = 0100H
MB_DEFBUTTON3           = 0200H

MB_APPLMODAL            = 0000H
MB_SYSTEMMODAL          = 1000H
MB_TASKMODAL            = 2000H

MB_NOFOCUS              = 8000H

;
;  Conventional dialog box and message box command IDs
;
IDOK     =   1
IDCANCEL =   2
IDABORT  =   3
IDRETRY  =   4
IDIGNORE =   5
IDYES    =   6
IDNO     =   7
;
;  Flags for OpenFile
;
OF_READ             = 0000H
OF_WRITE            = 0001H
OF_READWRITE        = 0002H
OF_SHARE_COMPAT     = 0000H
OF_SHARE_EXCLUSIVE  = 0010H
OF_SHARE_DENY_WRITE = 0020H
OF_SHARE_DENY_READ  = 0030H
OF_SHARE_DENY_NONE  = 0040H
OF_PARSE            = 0100H
OF_DELETE           = 0200H
OF_VERIFY           = 0400H     ; Used with OF_REOPEN
OF_SEARCH           = 0400H     ; Used without OF_REOPEN
OF_CANCEL           = 0800H
OF_CREATE           = 1000H
OF_PROMPT           = 2000H
OF_EXIST            = 4000H
OF_REOPEN           = 8000H

TF_FORCEDRIVE   = 80H

OPENSTRUC       STRUC
opLen   db      ?
opDisk  db      ?
opXtra  dw      ?
opDate  dw      ?
opTime  dw      ?
opFile  db      120 dup (?)
OPENSTRUC       ENDS
;
;  DrawText format flags
;
DT_LEFT         = 00H
DT_CENTER       = 01H
DT_RIGHT        = 02H
DT_TOP          = 00H
DT_VCENTER      = 04H
DT_BOTTOM       = 08H
DT_WORDBREAK    = 10H
DT_SINGLELINE   = 20H
DT_EXPANDTABS   = 40H
DT_TABSTOP      = 80H
DT_NOCLIP       =    0100H
DT_EXTERNALLEADING = 0200H
DT_CALCRECT     =    0400H
DT_NOPREFIX     =    0800H
DT_INTERNAL     =    1000H
ENDIF


;
;  System Menu Command Values
;
SC_SIZE        = 0F000h
SC_MOVE        = 0F010h
SC_MINIMIZE    = 0F020h
SC_MAXIMIZE    = 0F030h
SC_NEXTWINDOW  = 0F040h
SC_PREVWINDOW  = 0F050h
SC_CLOSE       = 0F060h
SC_VSCROLL     = 0F070h
SC_HSCROLL     = 0F080h
SC_MOUSEMENU   = 0F090h
SC_KEYMENU     = 0F100h
SC_ARRANGE     = 0F110h
SC_RESTORE     = 0F120h
SC_TASKLIST    = 0F130h
SC_SCREENSAVE  = 0F140h
SC_HOTKEY      = 0F150h

SC_ICON        = SC_MINIMIZE
SC_ZOOM        = SC_MAXIMIZE


IFNDEF NOSYSMETRICS

; GetSystemMetrics() codes
SM_CXSCREEN           =  0
SM_CYSCREEN           =  1
SM_CXVSCROLL          =  2
SM_CYHSCROLL          =  3
SM_CYCAPTION          =  4
SM_CXBORDER           =  5
SM_CYBORDER           =  6
SM_CXDLGFRAME         =  7
SM_CYDLGFRAME         =  8
SM_CYVTHUMB           =  9
SM_CXHTHUMB           =  10
SM_CXICON             =  11
SM_CYICON             =  12
SM_CXCURSOR           =  13
SM_CYCURSOR           =  14
SM_CYMENU             =  15
SM_CXFULLSCREEN       =  16
SM_CYFULLSCREEN       =  17
SM_CYKANJIWINDOW      =  18
SM_MOUSEPRESENT       =  19
SM_CYVSCROLL          =  20
SM_CXHSCROLL          =  21
SM_DEBUG              =  22
SM_SWAPBUTTON         =  23
SM_RESERVED1          =  24
SM_RESERVED2          =  25
SM_RESERVED3          =  26
SM_RESERVED4          =  27
SM_CXMIN              =  28
SM_CYMIN              =  29
SM_CXSIZE             =  30
SM_CYSIZE             =  31
SM_CXFRAME            =  32
SM_CYFRAME            =  33
SM_CXMINTRACK         =  34
SM_CYMINTRACK         =  35
IFNDEF NOWIN31
SM_CXDOUBLECLK        =  36
SM_CYDOUBLECLK        =  37
SM_CXICONSPACING      =  38
SM_CYICONSPACING      =  39
SM_MENUDROPALIGNMENT  =  40
SM_PENWINDOWS         =  41
SM_DBCSENABLED        =  42
ENDIF
SM_CMETRICSMAX        =  43

ENDIF   ;NOSYSMETRICS

; ShowWindow() Commands
SW_HIDE            = 0
SW_SHOWNORMAL      = 1
SW_NORMAL          = 1
SW_SHOWMINIMIZED   = 2
SW_SHOWMAXIMIZED   = 3
SW_MAXIMIZE        = 3
SW_SHOWNOACTIVATE  = 4
SW_SHOW            = 5
SW_MINIMIZE        = 6
SW_SHOWMINNOACTIVE = 7
SW_SHOWNA          = 8
SW_RESTORE         = 9


;
; Special CreateWindow position value
;
CW_USEDEFAULT   EQU    8000h

;
; Windows styles (the high words)
;
WS_EX_DLGMODALFRAME                  equ 1h
WS_EX_NOPARENTNOTIFY                 equ 4h
WS_EX_TOPMOST                        equ 8h
WS_EX_ACCEPTFILES                    equ 10h
WS_EX_TRANSPARENT                    equ 20h
WS_EX_MDICHILD                       equ 00000040h
WS_EX_TOOLWINDOW                     equ 00000080h
WS_EX_WINDOWEDGE                     equ 00000100h
WS_EX_CLIENTEDGE                     equ 00000200h
WS_EX_CONTEXTHELP                    equ 00000400h
WS_EX_RIGHT                          equ 00001000h
WS_EX_LEFT                           equ 00000000h
WS_EX_RTLREADING                     equ 00002000h
WS_EX_LTRREADING                     equ 00000000h
WS_EX_LEFTSCROLLBAR                  equ 00004000h
WS_EX_RIGHTSCROLLBAR                 equ 00000000h
WS_EX_CONTROLPARENT                  equ 00010000h
WS_EX_STATICEDGE                     equ 00020000h
WS_EX_APPWINDOW                      equ 00040000h
WS_EX_OVERLAPPEDWINDOW               equ WS_EX_WINDOWEDGE OR WS_EX_CLIENTEDGE
WS_EX_PALETTEWINDOW                  equ WS_EX_WINDOWEDGE OR WS_EX_TOOLWINDOW OR WS_EX_TOPMOST
WS_OVERLAPPED   = 00000h
WS_ICONICPOPUP  = 0C000h
WS_POPUP        = 08000h
WS_CHILD        = 04000h
WS_MINIMIZE     = 02000h
WS_VISIBLE      = 01000h
WS_DISABLED     = 00800h
WS_CLIPSIBLINGS = 00400h
WS_CLIPCHILDREN = 00200h
WS_MAXIMIZE     = 00100h
WS_CAPTION      = 000C0h     ; WS_BORDER | WS_DLGFRAME
WS_BORDER       = 00080h
WS_DLGFRAME     = 00040h
WS_VSCROLL      = 00020h
WS_HSCROLL      = 00010h
WS_SYSMENU      = 00008h
WS_THICKFRAME   = 00004h
WS_HREDRAW      = 00002h
WS_VREDRAW      = 00001h
WS_GROUP        = 00002h
WS_TABSTOP      = 00001h
WS_MINIMIZEBOX  = 00002h
WS_MAXIMIZEBOX  = 00001h

; Common Window Styles

WS_OVERLAPPEDWINDOW = WS_OVERLAPPED + WS_CAPTION + WS_SYSMENU + WS_THICKFRAME + WS_MINIMIZEBOX + WS_MAXIMIZEBOX
WS_POPUPWINDOW  = WS_POPUP + WS_BORDER + WS_SYSMENU
WS_CHILDWINDOW  = WS_CHILD
WS_TILEDWINDOW  = WS_OVERLAPPEDWINDOW

WS_TILED        = WS_OVERLAPPED
WS_ICONIC       = WS_MINIMIZE
WS_SIZEBOX      = WS_THICKFRAME

; Extended Window Styles (low words)
WS_EX_DLGMODALFRAME  = 0001
WS_EX_DRAGOBJECT     = 0002
WS_EX_NOPARENTNOTIFY = 0004
WS_EX_TOPMOST        = 0008

;
;  Window State Messages
;
IFNDEF  NOWM
WM_STATE            = 0000H

WM_NULL             = 0000h
WM_CREATE           = 0001h
WM_DESTROY          = 0002h
WM_MOVE             = 0003h
WM_SIZE             = 0005h
WM_ACTIVATE         = 0006h
WM_SETFOCUS         = 0007h
WM_KILLFOCUS        = 0008h
WM_ENABLE           = 000Ah
WM_SETREDRAW        = 000Bh
WM_SETTEXT          = 000Ch
WM_GETTEXT          = 000Dh
WM_GETTEXTLENGTH    = 000Eh
WM_PAINT            = 000Fh
WM_CLOSE            = 0010h
WM_QUERYENDSESSION  = 0011h
WM_QUIT             = 0012h
WM_QUERYOPEN        = 0013h
WM_ERASEBKGND       = 0014h
WM_SYSCOLORCHANGE   = 0015h
WM_ENDSESSION       = 0016h
WM_SYSTEMERROR      = 0017h
WM_SHOWWINDOW       = 0018h
WM_CTLCOLOR         = 0019h
WM_WININICHANGE     = 001Ah
WM_DEVMODECHANGE    = 001Bh
WM_ACTIVATEAPP      = 001Ch
WM_FONTCHANGE       = 001Dh
WM_TIMECHANGE       = 001Eh
WM_CANCELMODE       = 001Fh
WM_SETCURSOR        = 0020h
WM_MOUSEACTIVATE    = 0021h
WM_CHILDACTIVATE    = 0022h
WM_QUEUESYNC        = 0023h
WM_GETMINMAXINFO    = 0024h
WM_PAINTICON        = 0026h
WM_ICONERASEBKGND   = 0027h
WM_NEXTDLGCTL       = 0028h
WM_SPOOLERSTATUS    = 002Ah
WM_DRAWITEM         = 002Bh
WM_MEASUREITEM      = 002Ch
WM_DELETEITEM       = 002Dh
WM_VKEYTOITEM       = 002Eh
WM_CHARTOITEM       = 002Fh
WM_SETFONT          = 0030h
WM_GETFONT          = 0031h
WM_QUERYDRAGICON    = 0037h
WM_COMPAREITEM      = 0039h
WM_COMPACTING       = 0041h
IFNDEF NOWIN31
WM_COMMNOTIFY       = 0044h
WM_WINDOWPOSCHANGING= 0046h
WM_WINDOWPOSCHANGED = 0047h
WM_POWER            = 0048h
ENDIF


WM_NCCREATE         = 0081h
WM_NCDESTROY        = 0082h
WM_NCCALCSIZE       = 0083h
WM_NCHITTEST        = 0084h
WM_NCPAINT          = 0085h
WM_NCACTIVATE       = 0086h
WM_GETDLGCODE       = 0087h
WM_NCMOUSEMOVE      = 00A0h
WM_NCLBUTTONDOWN    = 00A1h
WM_NCLBUTTONUP      = 00A2h
WM_NCLBUTTONDBLCLK  = 00A3h
WM_NCRBUTTONDOWN    = 00A4h
WM_NCRBUTTONUP      = 00A5h
WM_NCRBUTTONDBLCLK  = 00A6h
WM_NCMBUTTONDOWN    = 00A7h
WM_NCMBUTTONUP      = 00A8h
WM_NCMBUTTONDBLCLK  = 00A9h

WM_KEYFIRST         = 0100h
WM_KEYDOWN          = 0100h
WM_KEYUP            = 0101h
WM_CHAR             = 0102h
WM_DEADCHAR         = 0103h
WM_SYSKEYDOWN       = 0104h
WM_SYSKEYUP         = 0105h
WM_SYSCHAR          = 0106h
WM_SYSDEADCHAR      = 0107h
WM_KEYLAST          = 0108h

WM_INITDIALOG       = 0110h
WM_COMMAND          = 0111h
WM_SYSCOMMAND       = 0112h
WM_TIMER            = 0113h
WM_HSCROLL          = 0114h
WM_VSCROLL          = 0115h
WM_INITMENU         = 0116h
WM_INITMENUPOPUP    = 0117h
WM_MENUSELECT       = 011Fh
WM_MENUCHAR         = 0120h
WM_ENTERIDLE        = 0121h


WM_MOUSEFIRST       = 0200h
WM_MOUSEMOVE        = 0200h
WM_LBUTTONDOWN      = 0201h
WM_LBUTTONUP        = 0202h
WM_LBUTTONDBLCLK    = 0203h
WM_RBUTTONDOWN      = 0204h
WM_RBUTTONUP        = 0205h
WM_RBUTTONDBLCLK    = 0206h
WM_MBUTTONDOWN      = 0207h
WM_MBUTTONUP        = 0208h
WM_MBUTTONDBLCLK    = 0209h
WM_MOUSELAST        = 0209h

WM_PARENTNOTIFY     = 0210h
WM_MDICREATE        = 0220h
WM_MDIDESTROY       = 0221h
WM_MDIACTIVATE      = 0222h
WM_MDIRESTORE       = 0223h
WM_MDINEXT          = 0224h
WM_MDIMAXIMIZE      = 0225h
WM_MDITILE          = 0226h
WM_MDICASCADE       = 0227h
WM_MDIICONARRANGE   = 0228h
WM_MDIGETACTIVE     = 0229h
WM_MDISETMENU       = 0230h
WM_DROPFILES        = 0233h


WM_CUT              = 0300h
WM_COPY             = 0301h
WM_PASTE            = 0302h
WM_CLEAR            = 0303h
WM_UNDO             = 0304h
WM_RENDERFORMAT     = 0305h
WM_RENDERALLFORMATS = 0306h
WM_DESTROYCLIPBOARD = 0307h
WM_DRAWCLIPBOARD    = 0308h
WM_PAINTCLIPBOARD   = 0309h
WM_VSCROLLCLIPBOARD = 030Ah
WM_SIZECLIPBOARD    = 030Bh
WM_ASKCBFORMATNAME  = 030Ch
WM_CHANGECBCHAIN    = 030Dh
WM_HSCROLLCLIPBOARD = 030Eh
WM_QUERYNEWPALETTE  = 030Fh
WM_PALETTEISCHANGING = 0310h
WM_PALETTECHANGED   = 0311h

IFNDEF NOWIN31

WM_PENWINFIRST      equ 0380h
WM_PENWINLAST       equ 038Fh

WM_COALESCE_FIRST  equ 0390h
WM_COALESCE_LAST   equ 039Fh

ENDIF

; #########################################################################
