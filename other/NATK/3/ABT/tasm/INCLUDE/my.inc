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

WNDCLASSEX STRUCT
  cbSize            DWORD      ?
  style             DWORD      ?
  lpfnWndProc       DWORD      ?
  cbClsExtra        DWORD      ?
  cbWndExtra        DWORD      ?
  hInstance         DWORD      ?
  hIcon             DWORD      ?
  hCursor           DWORD      ?
  hbrBackground     DWORD      ?
  lpszMenuName      DWORD      ?
  lpszClassName     DWORD      ?
  hIconSm           DWORD      ?
WNDCLASSEX ENDS

POINT STRUCT
  x  DWORD ?
  y  DWORD ?
POINT ENDS

MSG STRUCT
  hwnd      DWORD      ?
  message   DWORD      ?
  wParam    DWORD      ?
  lParam    DWORD      ?
  time      DWORD      ?
  pt        POINT      <>
MSG ENDS

IFNDEF NOWINMESSAGES

; Listbox messages
LB_ADDSTRING           = (WM_USER+1)
LB_INSERTSTRING        = (WM_USER+2)
LB_DELETESTRING        = (WM_USER+3)
LB_RESETCONTENT        = (WM_USER+5)
LB_SETSEL              = (WM_USER+6)
LB_SETCURSEL           = (WM_USER+7)
LB_GETSEL              = (WM_USER+8)
LB_GETCURSEL           = (WM_USER+9)
LB_GETTEXT             = (WM_USER+10)
LB_GETTEXTLEN          = (WM_USER+11)
LB_GETCOUNT            = (WM_USER+12)
LB_SELECTSTRING        = (WM_USER+13)
LB_DIR                 = (WM_USER+14)
LB_GETTOPINDEX         = (WM_USER+15)
LB_FINDSTRING          = (WM_USER+16)
LB_GETSELCOUNT         = (WM_USER+17)
LB_GETSELITEMS         = (WM_USER+18)
LB_SETTABSTOPS         = (WM_USER+19)
LB_GETHORIZONTALEXTENT = (WM_USER+20)
LB_SETHORIZONTALEXTENT = (WM_USER+21)
LB_SETTOPINDEX         = (WM_USER+24)
LB_GETITEMRECT         = (WM_USER+25)
LB_GETITEMDATA         = (WM_USER+26)
LB_SETITEMDATA         = (WM_USER+27)
LB_SELITEMRANGE        = (WM_USER+28)
LB_SETCARETINDEX       = (WM_USER+31)
LB_GETCARETINDEX       = (WM_USER+32)

IFNDEF NOWIN31

LB_SETITEMHEIGHT       = (WM_USER+33)
LB_GETITEMHEIGHT       = (WM_USER+34)
LB_FINDSTRINGEXACT     = (WM_USER+35)

ENDIF

ENDIF 
;NOWINMESSAGES

; Window field offsets for GetWindowLong() and GetWindowWord()
GWL_WNDPROC       =  (-4)
GWW_HINSTANCE     =  (-6)
GWW_HWNDPARENT    =  (-8)
GWW_ID            =  (-12)
GWL_STYLE         =  (-16)
GWL_EXSTYLE       =  (-20)

; GetWindow() Constants
GW_HWNDFIRST      =  0
GW_HWNDLAST       =  1
GW_HWNDNEXT       =  2
GW_HWNDPREV       =  3
GW_OWNER          =  4
GW_CHILD          =  5

; Static Control styles (low word)
SS_LEFT            = 00h
SS_CENTER          = 01h
SS_RIGHT           = 02h
SS_ICON            = 03h
SS_BLACKRECT       = 04h
SS_GRAYRECT        = 05h
SS_WHITERECT       = 06h
SS_BLACKFRAME      = 07h
SS_GRAYFRAME       = 08h
SS_WHITEFRAME      = 09h
SS_SIMPLE          = 0Bh
SS_LEFTNOWORDWRAP  = 0Ch
SS_NOPREFIX        = 80h    ; Don't do "&" character translation

; Listbox Styles
LBS_NOTIFY            = 0001h
LBS_SORT              = 0002h
LBS_NOREDRAW          = 0004h
LBS_MULTIPLESEL       = 0008h
LBS_OWNERDRAWFIXED    = 0010h
LBS_OWNERDRAWVARIABLE = 0020h
LBS_HASSTRINGS        = 0040h
LBS_USETABSTOPS       = 0080h
LBS_NOINTEGRALHEIGHT  = 0100h
LBS_MULTICOLUMN       = 0200h
LBS_WANTKEYBOARDINPUT = 0400h
LBS_EXTENDEDSEL       = 0800h
LBS_STANDARD          = LBS_NOTIFY + LBS_SORT + WS_VSCROLL + WS_BORDER
LBS_DISABLENOSCROLL   = 1000h

; Listbox Notification Codes
LBN_ERRSPACE      =  (-2)
LBN_SELCHANGE     =  1
LBN_DBLCLK        =  2
LBN_SELCANCEL     =  3
LBN_SETFOCUS      =  4
LBN_KILLFOCUS     =  5

DDL_READWRITE                        equ 0h
DDL_READONLY                         equ 1h
DDL_HIDDEN                           equ 2h
DDL_SYSTEM                           equ 4h
DDL_DIRECTORY                        equ 10h
DDL_ARCHIVE                          equ 20h
DDL_POSTMSGS                         equ 2000h
DDL_DRIVES                           equ 4000h
DDL_EXCLUSIVE                        equ 8000h

