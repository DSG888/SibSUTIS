; ###########################################################################
;
;                         Support macros for MASM32
;
; ###########################################################################

    ; ----------------------------------------------------------
    ; load a library and get the procedure address in one macro
    ; return value for the proc address in in EAX
    ; ----------------------------------------------------------
      LoadProcAddress MACRO quoted_text1,quoted_text2
        LOCAL library_name
        LOCAL proc_name
          .data
            library_name db quoted_text1,0
            proc_name db quoted_text2,0
          .code
        invoke LoadLibrary,ADDR library_name
        invoke GetProcAddress,eax,ADDR proc_name
      ENDM

    ; -------------------------
    ; initialised GLOBAL value
    ; -------------------------
;      GLOBAL MACRO variable:VARARG
;      .data
;        variable
;      .code
;      ENDM

    ; --------------------------------
    ; initialised GLOBAL string value
    ; --------------------------------
      STRING MACRO variable:REQ,args:VARARG
      .data
        variable db args,0
      .code
      ENDM

    ; ---------------------
    ; literal string MACRO
    ; ---------------------
      literal MACRO quoted_text:VARARG
        LOCAL local_text
        .data
          local_text db quoted_text,0
        .code
        EXITM <local_text>
      ENDM
    ; --------------------------------
    ; string address in INVOKE format
    ; --------------------------------
      SADD MACRO quoted_text:VARARG
        EXITM <ADDR literal(quoted_text)>
      ENDM
    ; --------------------------------
    ; string OFFSET for manual coding
    ; --------------------------------
      CTXT MACRO quoted_text:VARARG
        EXITM <offset literal(quoted_text)>
      ENDM

    ; --------------------------------------------------
    ; Two macros for allocating and freeing OLE memory.
    ; stralloc returns the handle/address of the string
    ; memory in eax. strfree uses the handle to free
    ; memory after use.
    ; NOTE that you must use the following INCLUDE &
    ; LIB files with these two macros.
    ;
    ;       include \MASM32\include\oleaut32.inc
    ;       includelib \MASM32\LIB\oleaut32.lib
    ;
    ; --------------------------------------------------
      stralloc MACRO ln
        invoke SysAllocStringByteLen,0,ln
      ENDM

      strfree MACRO strhandle
        invoke SysFreeString,strhandle
      ENDM

    ; -------------------------------------------------------------------
    ; The following 2 macros are for limiting the size of a window while
    ; it is being resized. They are to be used in the WM_SIZING message.
    ; -------------------------------------------------------------------
    LimitWindowWidth MACRO wdth
        LOCAL label
        mov eax, lParam
        mov ecx, (RECT PTR [eax]).right
        sub ecx, (RECT PTR [eax]).left
        cmp ecx, wdth
        jg label
      .if wParam == WMSZ_RIGHT || wParam == WMSZ_BOTTOMRIGHT || wParam == WMSZ_TOPRIGHT
        mov ecx, (RECT PTR [eax]).left
        add ecx, wdth
        mov (RECT PTR [eax]).right, ecx
      .elseif wParam == WMSZ_LEFT || wParam == WMSZ_BOTTOMLEFT || wParam == WMSZ_TOPLEFT
        mov ecx, (RECT PTR [eax]).right
        sub ecx, wdth
        mov (RECT PTR [eax]).left, ecx
      .endif
      label:
    ENDM

    LimitWindowHeight MACRO whgt
        LOCAL label
        mov eax, lParam
        mov ecx, (RECT PTR [eax]).bottom
        sub ecx, (RECT PTR [eax]).top
        cmp ecx, whgt
        jg label
      .if wParam == WMSZ_TOP || wParam == WMSZ_TOPLEFT || wParam == WMSZ_TOPRIGHT
        mov ecx, (RECT PTR [eax]).bottom
        sub ecx, whgt
        mov (RECT PTR [eax]).top, ecx
      .elseif wParam == WMSZ_BOTTOM || wParam == WMSZ_BOTTOMLEFT || wParam == WMSZ_BOTTOMRIGHT
        mov ecx, (RECT PTR [eax]).top
        add ecx, whgt
        mov (RECT PTR [eax]).bottom, ecx
      .endif
      label:
    ENDM

    ; ---------------------------------------
    ; Append literal string to end of buffer
    ; ---------------------------------------
      Append MACRO buffer,text
        LOCAL szTxt
        .data
          szTxt db text,0
        .code
        invoke szCatStr,ADDR buffer,ADDR szTxt
      ENDM

    ; ---------------------------
    ; Put ascii zero at 1st byte
    ; ---------------------------
      zero1 MACRO membuf
        mov membuf[0], 0
      ENDM

    ; -------------------------
    ; Application startup code
    ; -------------------------
      AppStart MACRO
        .code
        start:
        invoke GetModuleHandle, NULL
        mov hInstance, eax

        invoke GetCommandLine
        mov CommandLine, eax

        invoke InitCommonControls

        invoke WinMain,hInstance,NULL,CommandLine,SW_SHOWDEFAULT
        invoke ExitProcess,eax
      ENDM

      ShellAboutBox MACRO handle,IconHandle,quoted_Text_1,quoted_Text_2:VARARG
        LOCAL AboutTitle,AboutMsg,buffer

        .data
          AboutTitle db quoted_Text_1,0
          AboutMsg   db quoted_Text_2,0
          buffer db 128 dup (0)
        .code

        mov esi, offset AboutTitle
        mov edi, offset buffer
        mov ecx, lengthof AboutTitle
        rep movsb
        
        invoke ShellAbout,handle,ADDR buffer,ADDR AboutMsg,IconHandle
      ENDM

    ; --------------------------------------------------------------
    ; Specifies processor, memory model & case sensitive option.
    ; The parameter "Processor" should be in the form ".386" etc..
    ; EXAMPLE : AppModel .586
    ; --------------------------------------------------------------
      AppModel MACRO Processor
        Processor             ;; Processor type
        .model flat, stdcall  ;; 32 bit memory model
        option casemap :none  ;; case sensitive
      ENDM

    ; --------------------------------------------
    ; The following two macros must be used as a
    ; pair and can only be used once in a module.
    ; Additional code for processing within the
    ; message loop can be placed between them.
    ;
    ; The single parameter passed to both macros
    ; is the name of the MSG structure and must be
    ; the same in both macros.
    ; --------------------------------------------

      BeginMessageLoop MACRO mStruct
        MessageLoopStart:
          invoke GetMessage,ADDR mStruct,NULL,0,0
          cmp eax, 0
          je MessageLoopExit
      ENDM

      EndMessageLoop MACRO mStruct
          invoke TranslateMessage, ADDR mStruct
          invoke DispatchMessage,  ADDR mStruct
          jmp MessageLoopStart
        MessageLoopExit:
      ENDM

    ; --------------------------------------------------------
    ; MsgBox macro takes 2 parameters, both can be either
    ; literal text in quotes or addresses of zero terminated
    ; strings passed with "ADDR szString" where szString is
    ; a zero terminated string. Note that ADDR is uppercase.
    ;
    ; example : MsgBox "Greetings all",ADDR szTitle
    ;           MsgBox ADDR szMessage,"Result"
    ;
    ; --------------------------------------------------------

      MsgBox MACRO handl, TxtMsg, TxtTitle, styl

        LOCAL Msg1
        LOCAL Titl

        If @InStr(1,<TxtMsg>,<ADDR>) eq 0
          If @InStr(1,<TxtTitle>,<ADDR>) eq 0
          .data
            Msg1 db TxtMsg,0
            Titl db TxtTitle,0
          .code
            invoke MessageBox,handl,ADDR Msg1,ADDR Titl,styl
            EXITM
          EndIf
        EndIf

        If @InStr(1,<TxtMsg>,<ADDR>) gt 0
          If @InStr(1,<TxtTitle>,<ADDR>) eq 0
          .data
            Titl db TxtTitle,0
          .code
            invoke MessageBox,handl,TxtMsg,ADDR Titl,styl
            EXITM
          EndIf
        EndIf

        If @InStr(1,<TxtMsg>,<ADDR>) eq 0
          If @InStr(1,<TxtTitle>,<ADDR>) gt 0
          .data
            Msg1 db TxtMsg,0
          .code
            invoke MessageBox,handl,ADDR Msg1,TxtTitle,styl
            EXITM
          EndIf
        EndIf

        If @InStr(1,<TxtMsg>,<ADDR>) gt 0
          If @InStr(1,<TxtTitle>,<ADDR>) gt 0
            invoke MessageBox,handl,TxtMsg,TxtTitle,styl
            EXITM
          EndIf
        EndIf

      ENDM

    ; -------------------------------------------
    ; put zero terminated string in .data section
    ; alternative to the szText MACRO
    ; -------------------------------------------
      dsText MACRO Name, Text:VARARG
      .data
        Name db Text,0
      .code
      ENDM

    ; -------------------------------
    ; make 2 WORD values into a DWORD
    ; result in eax
    ; -------------------------------
      MAKEDWORD MACRO LoWord,HiWord
        mov ax, HiWord
        ror eax, 16
        mov ax, LoWord
      ENDM

    ; -----------------------------
    ; return IMMEDIATE value in eax
    ; -----------------------------
      retval MACRO var
        IF var EQ 0
          xor eax, eax  ;; slightly more efficient for zero
        ELSE
          mov eax, var  ;; place value in eax
        ENDIF
      ENDM

    ; ------------------------
    ; inline memory copy macro
    ; ------------------------
      Mcopy MACRO lpSource,lpDest,len
        mov esi, lpSource
        mov edi, lpDest
        mov ecx, len
        rep movsb
      ENDM

    ;; -----------------------------------
    ;; INPUT red, green & blue BYTE values
    ;; OUTPUT DWORD COLORREF value in eax
    ;; -----------------------------------
      RGB MACRO red, green, blue
        xor eax, eax
        mov al, blue    ; blue
        rol eax, 8
        mov al, green   ; green
        rol eax, 8
        mov al, red     ; red
      ENDM

    ; ------------------------------------------------
    ; The following macro were written by Ron Thomas
    ; ------------------------------------------------
    ; Retrieves the low word from double word argument
    ; ------------------------------------------------
      LOWORD MACRO bigword  
        mov  eax,bigword
        and  eax,0FFFFh     ;; Set to low word 
      ENDM

    ; ----------------------
    ; fast lodsb replacement
    ; ----------------------
      lob MACRO
        mov al, [esi]
        inc esi
      ENDM

    ; ----------------------
    ; fast stosb replacement
    ; ----------------------
      stb MACRO
        mov [edi], al
        inc edi
      ENDM

    ; -------------------------------
    ; pascal calling convention macro
    ; left to right push
    ; -------------------------------
      Pcall MACRO name:REQ,items:VARARG
        LOCAL arg
        FOR arg,<items>
          push arg
        ENDM
          call name
      ENDM

; ------------------------------------------------------------------
; macro for making STDCALL procedure and API calls.
; ------------------------------------------------------------------

Scall MACRO name:REQ,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12, \
                     p13,p14,p15,p16,p17,p18,p19,p20,p21,p22

    ;; ---------------------------------------
    ;; loop through arguments backwards, push
    ;; NON blank ones and call the function.
    ;; ---------------------------------------

    FOR arg,<p22,p21,p20,p19,p18,p17,p16,p15,p14,p13,\
             p12,p11,p10,p9,p8,p7,p6,p5,p4,p3,p2,p1>
      IFNB <arg>    ;; If not blank
        push arg    ;; push parameter
      ENDIF
    ENDM

    call name       ;; call the procedure

ENDM

; ---------------------------------------------------------------------
;
; The GLOBALS macro is for allocating uninitialised data in the .DATA?
; section. It is designed to take multiple definitions to make
; allocating uninitialised data more intuitive while coding.
;
; EXAMPLE: GLOBALS item1 dd ?,\
;                  item2 dd ?,\
;                  item3 dw ?,\
;                  item4 db 128 dup (?)
;
; ---------------------------------------------------------------------

      GLOBALS MACRO var1,var2,var3,var4,var5,var6,var7,var8,var9,var0,
                    varA,varB,varC,varD,varE,varF,varG,varH,varI,varJ
        .data?
          var1
          var2
          var3
          var4
          var5
          var6
          var7
          var8
          var9
          var0
          varA
          varB
          varC
          varD
          varE
          varF
          varG
          varH
          varI
          varJ
        .code
      ENDM
