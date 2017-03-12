
; #########################################################################

;
; Define the external functions we will be linking to
;
extrn		 EnumWindows:PROC
extrn		 CallWindowProcA:PROC
extrn		 GetClassNameA:PROC
extrn		 GetClientRect:PROC
extrn            GetModuleHandleA:PROC
extrn		 GetDlgItemTextA:PROC
extrn		 SetDlgItemTextA:PROC
extrn		 GetDlgItem:PROC
extrn		 SetFocus:PROC
extrn            DialogBoxParamA:PROC
extrn            ExitProcess:PROC
extrn            SendMessageA:PROC
extrn            EndDialog:PROC
extrn            BeginPaint:PROC
extrn            CreateWindowExA:PROC
extrn            DefWindowProcA:PROC
extrn            DispatchMessageA:PROC
extrn            EndPaint:PROC
extrn            ExitProcess:PROC
extrn            FindWindowA:PROC
extrn            GetMessageA:PROC
extrn            GetModuleHandleA:PROC
extrn            GetStockObject:PROC
extrn            InvalidateRect:PROC
extrn            LoadCursorA:PROC
extrn            LoadIconA:PROC
extrn            MessageBeep:PROC
extrn            MessageBoxA:PROC
extrn            PostQuitMessage:PROC
extrn            RegisterClassExA:PROC
extrn            ShowWindow:PROC
extrn            SetWindowPos:PROC
extrn            TextOutA:PROC
extrn            TranslateMessage:PROC
extrn            UpdateWindow:PROC
extrn            GetCommandLineA:PROC
extrn            LoadMenuA:PROC
extrn            SetMenu:PROC
extrn            MessageBoxA:PROC
extrn            PostMessageA:PROC
extrn            SendMessageA:PROC
extrn		 GetSystemMetrics:PROC
extrn		 SetWindowLongA:PROC
extrn		 MoveWindow:PROC
extrn		 _wsprintfA:PROC

; #########################################################################

