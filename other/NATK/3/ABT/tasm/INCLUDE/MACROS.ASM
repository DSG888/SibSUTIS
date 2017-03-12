comment © -----------------------------------------------------------------
                          Support macros for MASM32

                          Updated 4th December 2003
         ---------------------------------------------------------------- ©

comment * -----------------------------------------------------------------

   NOTES on DDPROTO macro

   This macro is for producing prototypes for functions where the start
   address is known and the parameter count is known. It requires a named
   DWORD sized entry in the .DATA or .DATA? section which has the start
   address written to it before the function is called.

        EXAMPLE:
        .data?
          user32_msgbox dd ?            ; << The named variable

        msgbox DDPROTO(user32_msgbox,4) ; create prototype

        This is expanded to the following. The TYPEDEF refers to
        the macro "pr4" in the WINDOWS.INC file.

        pt4 TYPEDEF PTR pr4
        msgbox equ <(TYPE pt4) PTR user32_msgbox>

        The address must be written to the DWORD variable before it can
        be called. This can be LoadLibrary/GetProcAddress or it can be
        an address recovered from a virtual table in a DLL or any other
        viable means of obtaining the start address of a function to call.

        invoke msgbox,hWnd,ADDR message_text, ADDR title_text,MB_OK

        ----------------------------------------------------------------- *

      DDPROTO MACRO lpFunction,pcount
        LOCAL txt1,txt2
        txt1 equ <pr>
        txt1 CATSTR txt1,%pcount
        txt2 equ <pt>
        txt2 CATSTR txt2,%pcount
        txt2 TYPEDEF PTR txt1
        EXITM <equ <(TYPE txt2) PTR lpFunction>>
      ENDM

  ; -----------------------------------------------------------
  ; This macro replaces quoted text with a DATA section OFFSET
  ; and returns it in ADDR "name" format. It is used by other
  ; macros that handle optional quoted text as a parameter.
  ; -----------------------------------------------------------
    reparg MACRO arg
      LOCAL nustr
        quot SUBSTR <arg>,1,1
      IFIDN quot,<">            ;; if 1st char = "
        .data
          nustr db arg,0        ;; write arg to .DATA section
        .code
        EXITM <ADDR nustr>      ;; append name to ADDR operator
      ELSE
        EXITM <arg>             ;; else return arg
      ENDIF
    ENDM

  ; -------------------------------------------------------
  ; This is a parameter checking macro. It is used to test
  ; if a parameter in a macro is a quoted string when a
  ; quoted string should not be used as a parameter. If it
  ; is a user defined error message is displayed at
  ; assembly time so that the error can be fixed.
  ; -------------------------------------------------------
    tstarg MACRO arg
      quot SUBSTR <arg>,1,1
      IFIDN quot,<">            ;; if 1st char = "
        % echo arg ** QUOTED TEXT ERROR ** memory address expected
        .ERR
      ELSE
        EXITM <arg>             ;; else return arg
      ENDIF
    ENDM

  ; ----------------------------------------------------------------
  ; invoke enhancement. Add quoted text support to any procedure
  ; or API call by using this macro instead of the standard invoke.
  ; LIMITATION : quoted text must be plain text only, no ascii 
  ; values or macro reserved characters IE <>!() etc ..
  ; use SADD() for requirements of this type.
  ; ----------------------------------------------------------------
    fn MACRO args:VARARG
      LOCAL cnt
      cnt = 0
      arg equ <>
      FOR var,<args>
        arg CATSTR arg,<var> ;; get the proc name as 1st arg
        EXITM
      ENDM
      FOR var,<args>
        IF cnt gt 0
        arg CATSTR arg,<,reparg(var)> ;; replace quotes and append arg
        ENDIF
        cnt = cnt + 1
      ENDM
      invoke arg
    ENDM

    ; *******************
    ; DATA DECLARATIONS *
    ; *******************

    ; -------------------------------------
    ; initialised GLOBAL value of any type
    ; -------------------------------------
      GLOBAL MACRO variable:VARARG
      .data
      align 4
        variable
      .code
      ENDM

    ; --------------------------------
    ; initialised GLOBAL string value
    ; --------------------------------
      STRING MACRO variable:REQ,args:VARARG
      .data
        variable db args,0
        align 4
      .code
      ENDM

    ; --------------------------------
    ; initialise floating point vaues
    ; --------------------------------

      FLOAT4 MACRO name,value
        .data
        align 4
          name REAL4 value
        .code
      ENDM

      FLOAT8 MACRO name,value
        .data
        align 4
          name REAL8 value
        .code
      ENDM

      FLOAT10 MACRO name,value
        .data
        align 4
          name REAL10 value
        .code
      ENDM

    ; **********************************************************
    ; function style macros for direct insertion of data types *
    ; **********************************************************

      FP4 MACRO value
        LOCAL vname
        .data
        align 4
          vname REAL4 value
        .code
        EXITM <vname>
      ENDM

      FP8 MACRO value
        LOCAL vname
        .data
        align 4
          vname REAL8 value
        .code
        EXITM <vname>
      ENDM

      FP10 MACRO value
        LOCAL vname
        .data
        align 4
          vname REAL10 value
        .code
        EXITM <vname>
      ENDM

    ; **********************************************
    ; The original concept for the following macro *
    ; was designed by "huh" from New Zealand.      *
    ; **********************************************

    ; ---------------------
    ; literal string MACRO
    ; ---------------------
      literal MACRO quoted_text:VARARG
        LOCAL local_text
        .data
          local_text db quoted_text,0
        align 4
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

    ; -----------------------------------------------------
    ; string address embedded directly in the code section
    ; -----------------------------------------------------
      CADD MACRO quoted_text:VARARG
        LOCAL vname,lbl
          jmp lbl
            vname db quoted_text,0
          align 4
          lbl:
        EXITM <ADDR vname>
      ENDM

    ; --------------------------------------------------
    ; Macro for placing an assembler instruction either
    ; within another or within a procedure call
    ; --------------------------------------------------

    ASM MACRO parameter1,source
      LOCAL mnemonic
      LOCAL dest
      LOCAL poz

      % poz INSTR 1,<parameter1>,< >             ;; get the space position
      mnemonic SUBSTR <parameter1>, 1, poz-1     ;; get the mnemonic
      dest SUBSTR <parameter1>, poz+1            ;; get the first argument

      mnemonic dest, source

      EXITM <dest>
    ENDM

    ; ------------------------------------------------------------
    ; Macro for nesting function calls in other invoke statements
    ; ------------------------------------------------------------
      FUNC MACRO parameters:VARARG
        invoke parameters
        EXITM <eax>
      ENDM

    ; -------------------------------------------
    ;             Pseudo mnemonics.
    ; These macros emulate assembler mnemonics
    ; but perform higher level operations not
    ; directly supported by the instruction set
    ; NOTE: The parameter order is the normal
    ; assembler order of,
    ; instruction/destination/source
    ; -------------------------------------------

    ; --------------------------
    ; szstring to szstring copy
    ; --------------------------
      cst MACRO arg1,arg2
        invoke szCopy,reparg(arg2),tstarg(arg1)
      ENDM

    ; ----------------------------
    ; memory to memory assignment
    ; ----------------------------
      m2m MACRO M1, M2
        push M2
        pop  M1
      ENDM

    ; **********************************
    ;         String assign.           *
    ; Assign quoted text and assembler *
    ; notation to a DWORD variable     *
    ; sas var,"text",13,10,"more",0    *
    ; NOTE: zero is always appended    *
    ; **********************************

      sas MACRO var,quoted_text:VARARG
        LOCAL txtname
        .data
          txtname db quoted_text,0
          align 4
        .code
        mov var, OFFSET txtname
      ENDM

    ; --------------------------------------------
    ; emulation of the floating point mnemonic FLD
    ; to load real4/8/10 values
    ; EXAMPLE : fld8 1234.56789
    ; --------------------------------------------
      fld4 MACRO fpvalue
        LOCAL name
        .data
          name REAL4 fpvalue
          align 4
        .code
        fld name
      ENDM

      fld8 MACRO fpvalue
        LOCAL name
        .data
          name REAL8 fpvalue
          align 4
        .code
        fld name
      ENDM

      fld10 MACRO fpvalue
        LOCAL name
        .data
          name REAL10 fpvalue
          align 4
        .code
        fld name
      ENDM
    ; --------------------------------------------

  ; ----------------------------------------------------------
  ; function position macros that takes a DWORD parameter and
  ; returns the address of the buffer that holds the result.
  ; The return format is for use within the INVOKE syntax.
  ; ----------------------------------------------------------
    str$ MACRO DDvalue
      LOCAL rvstring
      .data
        rvstring db 20 dup (0)
        align 4
      .code
      invoke dwtoa,DDvalue,ADDR rvstring
      EXITM <ADDR rvstring>
    ENDM

    hex$ MACRO DDvalue
      LOCAL rvstring
      .data
        rvstring db 12 dup (0)
        align 4
      .code
      invoke dw2hex,DDvalue,ADDR rvstring
      EXITM <ADDR rvstring>
    ENDM

    ; ******************************************************
    ; BASIC style conversions from string to 32 bit integer
    ; ******************************************************
      sval MACRO lpstring       ; string to signed 32 bit integer
        invoke atol, reparg(lpstring)
        EXITM <eax>
      ENDM

      uval MACRO lpstring       ; string to unsigned 32 bit integer
        invoke atodw, reparg(lpstring)
        EXITM <eax>
      ENDM

      val equ <uval>

      hval MACRO lpstring       ; hex string to unsigned 32 bit integer
        invoke htodw, reparg(lpstring)
        EXITM <eax>
      ENDM

    ; ********************************
    ; BASIC string function emulation
    ; ********************************
      add$ MACRO lpSource,lpAppend
        invoke szCatStr,tstarg(lpSource),reparg(lpAppend)
        EXITM <eax>
      ENDM

      append$ MACRO string,buffer,location
        invoke szappend,reparg(string),buffer,location
        EXITM <eax>
      ENDM

      chr$ MACRO any_text:VARARG
        LOCAL txtname
        .data
          txtname db any_text,0
        .code
        EXITM <OFFSET txtname>
      ENDM

      ptr$ MACRO buffer
        lea eax, buffer
        mov BYTE PTR [eax], 0
        EXITM <eax>
      ENDM

      len MACRO lpString
        invoke szLen,reparg(lpString)
        EXITM <eax>
      ENDM

      istring MACRO spos,lpMainString,lpSubString
        invoke InString,spos,reparg(lpMainString),reparg(lpSubString)
        EXITM <eax>
      ENDM

      ucase$ MACRO lpString
        invoke szUpper,reparg(lpString)
        EXITM <eax>
      ENDM

      lcase$ MACRO lpString
        invoke szLower,reparg(lpString)
        EXITM <eax>
      ENDM

      left$ MACRO lpString,slen
        invoke szLeft,reparg(lpString),reparg(lpString),slen
        EXITM <eax>
      ENDM

      right$ MACRO lpString,slen
        invoke szRight,reparg(lpString),reparg(lpString),slen
        EXITM <eax>
      ENDM

      rev$ MACRO lpString
        invoke szRev,reparg(lpString),reparg(lpString)
        EXITM <eax>
      ENDM

      ltrim$ MACRO lpString
        invoke szLtrim,reparg(lpString),reparg(lpString)
        mov eax, ecx
        EXITM <eax>
      ENDM

      rtrim$ MACRO lpString
        invoke szRtrim,reparg(lpString),reparg(lpString)
        mov eax, ecx
        EXITM <eax>
      ENDM

      trim$ MACRO lpString
        invoke szTrim,reparg(lpString)
        mov eax, ecx
        EXITM <eax>
      ENDM

      remove$ MACRO src,substr
        invoke szRemove,reparg(src),reparg(src),reparg(substr)
        EXITM <eax>
      ENDM

      ustr$ MACRO DDvalue   ;; unsigned integer from string
        LOCAL rvstring
        .data
          rvstring db 20 dup (0)
        align 4
        .code
        invoke dwtoa,DDvalue,ADDR rvstring
        EXITM <OFFSET rvstring>
      ENDM

      sstr$ MACRO DDvalue   ;; signed integer from string
        LOCAL rvstring
        .data
          rvstring db 20 dup (0)
        align 4
        .code
        invoke ltoa,DDvalue,ADDR rvstring
        EXITM <OFFSET rvstring>
      ENDM

      uhex$ MACRO DDvalue   ;; unsigned DWORD to hex string
        LOCAL rvstring
        .data
          rvstring db 12 dup (0)
        align 4
        .code
        invoke dw2hex,DDvalue,ADDR rvstring
        EXITM <OFFSET rvstring>
      ENDM

comment * -------------------------------------------------------
        Each of the following macros has its own dedicated 260
        BYTE buffer. The OFFSET returned by each macro can be
        used directly in code but if the macro is called again
        the data in the dedicated buffer will be overwritten
        with the new result.

        mov str1, ptr$(buffer)
        mov str2, pth$()
        invoke szCopy str2,str1

        Empty brackets should be used with these macros as they
        take no parameters. pth$() CurDir$() etc ...
        ------------------------------------------------------- *

      pth$ MACRO            ;; application path OFFSET returned
        IFNDEF pth__equate__flag
        .data?
          pth__260_BYTE__buffer db MAX_PATH dup (?)
        .code
        pth__equate__flag equ <1>
        ENDIF
        invoke GetAppPath,ADDR pth__260_BYTE__buffer
        EXITM <eax>
      ENDM

      CurDir$ MACRO
        IFNDEF cdir__equate__flag
        .data?
          cdir__260_BYTE__buffer db MAX_PATH dup (?)
        .code
        cdir__equate__flag equ <1>
        ENDIF
        invoke GetCurrentDirectory,MAX_PATH,ADDR cdir__260_BYTE__buffer
        mov eax, OFFSET cdir__260_BYTE__buffer
        EXITM <eax>
      ENDM

      SysDir$ MACRO
        IFNDEF sys__equate__flag
        .data?
          sysdir__260_BYTE__buffer db MAX_PATH dup (?)
        .code
        sys__equate__flag equ <1>
        ENDIF
        invoke GetSystemDirectory,ADDR sysdir__260_BYTE__buffer,MAX_PATH
        mov eax, OFFSET sysdir__260_BYTE__buffer
        EXITM <eax>
      ENDM

      WinDir$ MACRO
        IFNDEF wdir__equate__flag
        .data?
          windir__260_BYTE__buffer db MAX_PATH dup (?)
        .code
        wdir__equate__flag equ <1>
        ENDIF
        invoke GetWindowsDirectory,ADDR windir__260_BYTE__buffer,MAX_PATH
        mov eax, OFFSET windir__260_BYTE__buffer
        EXITM <eax>
      ENDM

    ; ---------------------------------------------------------------
    ; Get command line arg specified by "argnum" starting at arg 1
    ; Test the return values with the following to determine results
    ; 1 = successful operation
    ; 2 = no argument exists at specified arg number
    ; 3 = non matching quotation marks
    ; 4 = empty quotation marks
    ; test the return value in ECX
    ; ---------------------------------------------------------------
      cmd$ MACRO argnum
        LOCAL argbuffer
        IFNDEF cmdflag
        .data?
          argbuffer db MAX_PATH dup (?)
        .code
        cmdflag equ 1
        ENDIF
        invoke GetCL,argnum, ADDR argbuffer
        mov ecx, eax
        mov eax, OFFSET argbuffer
        EXITM <eax>
      ENDM

  ; ******************************************
  ; DOS style directory manipulation macros  *
  ; The parameters passed to these directory *
  ; macros should be zero terminated string  *
  ; addresses.                               *
  ; ******************************************
      chdir MACRO pathname
        invoke SetCurrentDirectory,reparg(pathname)
      ENDM
      CHDIR equ <chdir>

      mkdir MACRO dirname
        invoke CreateDirectory,reparg(dirname),NULL
      ENDM
      MKDIR equ <mkdir>

      rndir MACRO oldname,newname
        invoke MoveFile,reparg(oldname),reparg(newname)
      ENDM
      RNDIR equ <rndir>

      rmdir MACRO dirname
        invoke RemoveDirectory,reparg(dirname)
      ENDM
      RMDIR equ <rmdir>

    ; **************************
    ; memory allocation macros *
    ; **************************

    comment * --------------------------------------------------    
            Two macros for allocating and freeing OLE memory.
            stralloc returns the handle/address of the string
            memory in eax. alloc$ acts in the same way but is
            used in the function position. strfree uses the
            handle to free memory after use.
    
            NOTE that you must use the following INCLUDE &
            LIB files with these two macros.
    
            include \MASM32\include\oleaut32.inc
            includelib \MASM32\LIB\oleaut32.lib
            -------------------------------------------------- *

      alloc$ MACRO ln
        invoke SysAllocStringByteLen,0,ln
        mov BYTE PTR [eax], 0
        EXITM <eax>
      ENDM

      free$ MACRO strhandle
        invoke SysFreeString,strhandle
      ENDM

      stralloc MACRO ln
        invoke SysAllocStringByteLen,0,ln
      ENDM

      strfree MACRO strhandle
        invoke SysFreeString,strhandle
      ENDM

comment * ------------------------------------------------
    The following 2 macros are for general purpose memory
    allocation where fine granularity in memory is required
    or where the memory attribute "execute" is useful.
    ------------------------------------------------------ *

      alloc MACRO bytecount
        invoke GlobalAlloc,GMEM_FIXED or GMEM_ZEROINIT,bytecount
        EXITM <eax>
      ENDM

      free MACRO hmemory
        invoke GlobalFree,hmemory
      ENDM

    ; ************************************************************
    ;                       File IO macros                       *
    ; NOTE: With the address returned by InputFile that contains *
    ; the data in the file, it must be deallocated using the API *
    ; function GlobalFree().                                     *
    ; EXAMPLE: invoke GlobalFree,pMem                            *
    ; ************************************************************

      InputFile MACRO lpFile
      ;; ----------------------------------------------------------
      ;; The untidy data? names are to avoid duplication in normal
      ;; code. The two values are reused by each call to the macro
      ;; ----------------------------------------------------------
        IFNDEF ipf@@flag            ;; if the flag is not defined
          .data?
            ipf@__@mem@__@Ptr dd ?  ;; write 2 DWORD variables to
            ipf@__file__@len dd ?   ;; the uninitialised data section
          .code
          ipf@@flag equ <1>         ;; define the flag
        ENDIF
        invoke read_disk_file,reparg(lpFile),
               ADDR ipf@__@mem@__@Ptr,
               ADDR ipf@__file__@len
        mov ecx, ipf@__file__@len   ;; file length returned in ECX
        mov eax, ipf@__@mem@__@Ptr  ;; address of memory returned in EAX
        EXITM <eax>
      ENDM

      OutputFile MACRO lpFile,lpMem,lof
        invoke write_disk_file,reparg(lpFile),lpMem,lof
        EXITM <eax>
      ENDM

    ; -----------------------------------------
    ; common dialog file open and close macros.
    ; Return value in both is the OFFSET of a
    ; 260 byte dedicated buffer in the .DATA?
    ; section in EAX.
    ; -----------------------------------------
      OpenFileDlg MACRO hWin,hInstance,lpTitle,lpPattern
        invoke OpenFileDialog,hWin,hInstance,reparg(lpTitle),reparg(lpPattern)
        EXITM <eax>
      ENDM

      SaveFileDlg MACRO hWin,hInstance,lpTitle,lpPattern
        invoke SaveFileDialog,hWin,hInstance,reparg(lpTitle),reparg(lpPattern)
        EXITM <eax>
      ENDM

    ; ----------------------------------------------------------
    ; load a library and get the procedure address in one macro
    ; return value for the proc address in in EAX. Both DLL and
    ; procedure name are enclosed in quotation marks.
    ;
    ; EXAMPLE : LoadProcAddress "mydll.dll","myproc"
    ;           proc address in EAX
    ;           library handle in ECX
    ;
    ; EXAMPLE : mov lpProc, GetDllProc("mydll.dll","myproc")
    ;           library handle in ECX
    ;
    ; ----------------------------------------------------------

      LoadProcAddress MACRO libname_text1,procname_text2
        LOCAL library_name
        LOCAL proc_name
          .data
            library_name db libname_text1,0
            proc_name db procname_text2,0
          align 4
          .code
        invoke LoadLibrary,ADDR library_name
        mov ecx, eax
        invoke GetProcAddress,eax,ADDR proc_name
      ENDM

      GetDllProc MACRO libname_text1,procname_text2
        LOCAL library_name
        LOCAL proc_name
          .data
            library_name db libname_text1,0
            proc_name db procname_text2,0
          align 4
          .code
        invoke LoadLibrary,ADDR library_name
        mov ecx, eax
        invoke GetProcAddress,eax,ADDR proc_name
        EXITM <eax>
      ENDM

    ; **********************************
    ; control flow macro by Greg Falen *
    ; **********************************

    ; ----------------------
    ; Switch/Case emulation
    ; ----------------------
    $casflg equ <>
    $casvar equ <>
    $casstk equ <>
    
    switch macro _var:req, _reg:=<eax>
        mov _reg, _var
        $casstk catstr <_reg>, <#>, $casflg, <#>, $casstk
        $casvar equ _reg
        $casflg equ <0>         ;; 0 = emit an .if, 1 an .elseif
    endm
    
    case macro _args:vararg     ;; like Pascal: case id1. id4 .. id8, lparam, ...
                                ;; does an or (case1 || case2 || case3...)
      $cas textequ <>
      irp $v, <_args>         ;; for each case
          t@ instr <$v>, <..> ;; range ?
          if t@               ;; yes
              $LB substr <$v>, 1, t@-1                  ;; lbound = left portion
              $LB catstr <(>, $casvar, <!>=>, $LB, <)>  ;; ($casvar >= lbound)
              $UB substr <$v>, t@+2                     ;; ubound = right portion
              $UB catstr <(>, $casvar, <!<=>, $UB, <)>  ;; ($casvar <= ubound)
              $t catstr <(>, $LB, <&&> , $UB,<)>        ;; (($casvar >= $lb) && ($casvar <= $ub))
          else    ;; no, it's a value (var/const)
              $t catstr <(>, $casvar, <==>, <$v>, <)>   ;; ($casvar == value)
          endif
          $cas catstr <|| >, $t, $cas                   ;; or this case w/ others
      endm
      $cas substr $cas, 3 ;; lose the extra "|| " in front
        ifidn $casflg, <0> ;; 0 = 1'st case
            % .if $cas ;; emit ".if"
        else ;; all others
            % .elseif $cas ;; emit ".elseif"
        endif
        $casflg equ <1> ;; NOT 1'st
    endm
    
    default macro _default:vararg
        .else
        _default
    endm
    
    endsw macro _cmd:vararg
        ifidn $casstk, <>
            .err <Endsw w/o Switch>
        else
            t@ instr $casstk, <#>
            $casvar substr $casstk, 1, t@-1
            $casstk substr $casstk, t@+1
            t@ instr $casstk, <#>
            $casflg substr $casstk, 1, t@-1
            ifidn $casstk, <#>
                $casstk equ <>
            else
                $casstk substr $casstk, t@+1
            endif
            .endif
        endif
    endm

  ; --------------------------------------------------
  ; equates for name and case variation in macro names
  ; --------------------------------------------------
    Case equ <case>
    CASE equ <case>
    Switch equ <switch>
    SWITCH equ <switch>

    Endsw equ <endsw>
    EndSw equ <endsw>
    ENDSW equ <endsw>

    Select equ <switch>
    select equ <switch>
    SELECT equ <switch>

    Endsel equ <endsw>
    endsel equ <endsw>
    ENDSEL equ <endsw>

    Default equ <default>
    DEFAULT equ <default>

    CaseElse equ <default>
    Caseelse equ <default>
    CASEELSE equ <default>
    caseelse equ <default>

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

    MsgBox MACRO hndl,txtmsg,titlemsg,styl
      invoke MessageBox,hndl,reparg(txtmsg),reparg(titlemsg),styl
    ENDM

  ; ------------------------------------------------------
  ; macro for concantenating strings using the szMultiCat
  ; procedure written by Alexander Yackubtchik.
  ;
  ; USAGE strcat buffer,str1,str2,str3 etc ...
  ; 
  ; buffer must be large enough to contain all of the
  ; strings to append. Limit is set by maximum line
  ; length in MASM.
  ; ------------------------------------------------------
    strcat MACRO arguments:VARARG
    LOCAL txt
    LOCAL pcount
        txt equ <invoke szMultiCat,>        ;; lead string
        pcount = 0
          FOR arg, <arguments>
            pcount = pcount + 1             ;; count arguments
          ENDM
        % pcount = pcount - 1               ;; dec 1 for 1st arg
        txt CATSTR txt,%pcount              ;; append number to lead string
          FOR arg, <arguments>
            txt CATSTR txt,<,>,reparg(arg)
          ENDM
        txt                                 ;; put result in code
    ENDM

  ; ----------------------------------------------
  ; this version is used in the function position
  ; ----------------------------------------------
    cat$ MACRO arguments:VARARG
      LOCAL txt
      LOCAL spare
      LOCAL pcount
        spare equ <>
          FOR arg, <arguments>
            spare CATSTR spare,tstarg(arg)  ;; test if 1st arg is quoted text
            EXITM                           ;; and produce error if it is
          ENDM
        txt equ <invoke szMultiCat,>        ;; lead string
        pcount = 0
          FOR arg, <arguments>
            pcount = pcount + 1             ;; count arguments
          ENDM
        % pcount = pcount - 1               ;; dec 1 for 1st arg
        txt CATSTR txt,%pcount              ;; append number to lead string
          FOR arg, <arguments>
            txt CATSTR txt,<,>,reparg(arg)
          ENDM
        txt                                 ;; put result in code
      EXITM <eax>
    ENDM

    ; ************************************
    ; console mode text input and output *
    ; ************************************

    cls MACRO                       ;; clear screen
      invoke ClearScreen
    ENDM

    print MACRO varname:VARARG      ;; display zero terminated string
      invoke StdOut,reparg(varname)
    ENDM

    write MACRO quoted_text:VARARG  ;; display quoted text
      LOCAL txt
      .data
        txt db quoted_text,0
        align 4
      .code
      invoke StdOut,ADDR txt
    ENDM

    loc MACRO xc,yc                 ;; set cursor position
      invoke locate,xc,yc
    ENDM

comment * -------------------------------------

    use the "input" macro as follows,

    If you want a prompt use this version
    mov lpstring, input("Type text here : ")

    If you don't need a prompt use the following
    mov lpstring, input()

    NOTE : The "lpstring" is a preallocated
           DWORD variable that is either LOCAL
           or declared in the .DATA or .DATA?
           section. Any legal name is OK.

    LIMITATION : MASM uses < > internally in its
    macros so if you wish to use these symbols
    in a prompt, you must use the ascii value
    and not use the symbol literally.

    EXAMPLE mov var, input("Enter number here ",62," ")

    ------------------------------------------- *

    input MACRO prompt:VARARG
        LOCAL txt
        LOCAL buffer
      IFNB <prompt>
        .data
          txt db prompt
          buffer db 128 dup (0)
          align 4
        .code
        invoke StdOut,ADDR txt
        invoke StdIn,ADDR buffer,LENGTHOF buffer
        invoke StripLF,ADDR buffer
        mov eax, offset buffer
        EXITM <eax>
      ELSE
        .data
          buffer db 128 dup (0)
          align 4
        .code
        invoke StdIn,ADDR buffer,LENGTHOF buffer
        invoke StripLF,ADDR buffer
        mov eax, offset buffer
        EXITM <eax>
      ENDIF
    ENDM

    exit MACRO 
      invoke ExitProcess, 0
    ENDM

    ; **************************
    ; Application startup code *
    ; **************************

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

    ; ********************************************
    ; align memory                               *
    ; reg has the address of the memory to align *
    ; number is the required alignment           *
    ; EXAMPLE : memalign esi, 16                 *
    ; ********************************************

      memalign MACRO reg, number
        add reg, number - 1
        and reg, -number
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
          align 4
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

    ; **********************
    ; miscellaneous macros *
    ; **********************

      ShellAboutBox MACRO handle,IconHandle,quoted_Text_1,quoted_Text_2:VARARG
        LOCAL AboutTitle,AboutMsg,buffer

        .data
          align 4
          buffer db 128 dup (0)
          AboutTitle db quoted_Text_1,0
          AboutMsg   db quoted_Text_2,0
          align 4
        .code

        mov esi, offset AboutTitle
        mov edi, offset buffer
        mov ecx, lengthof AboutTitle
        rep movsb
        
        invoke ShellAbout,handle,ADDR buffer,ADDR AboutMsg,IconHandle
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

    ; ---------------------------------------
    ; Append literal string to end of buffer
    ; ---------------------------------------
      Append MACRO buffer,text
        LOCAL szTxt
        .data
          szTxt db text,0
          align 4
        .code
        invoke szCatStr,ADDR buffer,ADDR szTxt
      ENDM

    ; ---------------------------
    ; Put ascii zero at 1st byte
    ; ---------------------------
      zero1 MACRO membuf
        mov membuf[0], 0
      ENDM

    ; -------------------------------------------
    ; put zero terminated string in .data section
    ; alternative to the szText MACRO
    ; -------------------------------------------
      dsText MACRO Name, Text:VARARG
      .data
        Name db Text,0
        align 4
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
        ret
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

    ; -----------------------------------
    ; INPUT red, green & blue BYTE values
    ; OUTPUT DWORD COLORREF value in eax
    ; -----------------------------------
      RGB MACRO red, green, blue
        xor eax, eax
        mov ah, blue    ; blue
        mov al, green   ; green
        rol eax, 16
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

    ; ----------------------------
    ; code section text insertion
    ; ----------------------------
      szText MACRO Name, Text:VARARG
        LOCAL lbl
          jmp lbl
            Name db Text,0
          lbl:
        ENDM

      return MACRO arg
        mov eax, arg
        ret
      ENDM

      SingleInstanceOnly MACRO lpClassName
        invoke FindWindow,lpClassName,NULL
        cmp eax, 0
        je @F
          push eax
          invoke ShowWindow,eax,SW_RESTORE
          pop eax
          invoke SetForegroundWindow,eax
          mov eax, 0
          ret
        @@:
      ENDM

    ; macro encapsulates the MAX_PATH size buffer and returns its OFFSET

      DropFileName MACRO wordparam
        IFNDEF df@@name
          .data?
            dfname db MAX_PATH dup (?)
          .code
        df@@name equ 1
        ENDIF
        invoke DragQueryFile,wordparam,0,ADDR dfname,SIZEOF dfname
        EXITM <OFFSET dfname>
      ENDM

; ¤=÷=¤=÷=¤=÷=¤=÷=¤=÷=¤=÷=¤=÷=¤=÷=¤=÷=¤=÷=¤=÷=¤=÷=¤=÷=¤=÷=¤=÷=¤=÷=¤=÷=¤=÷=¤

comment © ------------------------------------------------------------------

    *************************************************************
    * NOTE:                                                     *
    * This macro system is not supported in MASM32 and is still *
    * in the development stage where it is subject to change.   *
    *************************************************************

                      Function declaration macros

    This macro system is designed for simplifying procedure calls
    by removing the "invoke" syntax so that it can be called
    directly by its name. It works by prepending "FN_" to
    the procedure name and then using an equate to match the
    required procedure name to the modified name.

    MyFunc equ <invoke FN_MyFunc,>

    Writing the FUNCTION is done with the FUNCTION macro and
    terminated with the ENDFN macro.

    FUNCTION MyFunc,parameters
      ; write code here
      ret
    ENDFN

    When you use the procedure, the equate is expanded up to its
    full name with the leading FN_ prepended by INVOKE. This allows,

        MyFunc Parameters

        rather than

        invoke MyFunc,parameters

    When you need to use the original procedure name there is another
    macro called FPTR which handles the leading FN_ so that if you have
    to specify the OFFSET of the procedure or use CALL, you get the
    correct address by way of the correct label name being substituted
    in the body of the code that uses it.

    Instead of using code like,

        "mov wc.lpfnWndProc, offset WndProc"

        you use

        "mov wc.lpfnWndProc, offset FPTR(WndProc)"

    --------------------------------------------------------------------- ©

  ; -------------------------------------
  ; function prototype declaration macro
  ; -------------------------------------

    DECLARE MACRO cname,parameters:VARARG
      LOCAL txt,fname
      fname equ <FN_>
      fname CATSTR fname,<cname>
      txt CATSTR fname
      fname CATSTR fname,< PROTO parameters>
      fname
      cname equ <invoke txt,>
    ENDM

  ; ---------------------
  ; begin function macro
  ; ---------------------
    FUNCTION MACRO procname,parameters:VARARG
      LOCAL txt
      fn@@name@?? equ <FN_>
      fn@@name@?? CATSTR fn@@name@??,<procname>     ;; write name for ENDFN
      txt equ <FN_>
      txt CATSTR txt,<procname proc parameters>
      align 4
      txt
    ENDM

  ; -------------------
  ; end function macro
  ; -------------------
    ENDFN MACRO
      fn@@name@?? endp
    ENDM

    ENDF equ <ENDFN>

  ; -----------------------
  ; function pointer macro
  ; -----------------------
    FPTR MACRO parameter
      LOCAL txt
      txt equ <FN_>
      txt CATSTR txt,<parameter>
      EXITM <txt>
    ENDM

  ; ----------------------------
  ; function return value macro
  ; ----------------------------
    RV MACRO args:VARARG
      args
      EXITM <eax>
    ENDM

; ¤=÷=¤=÷=¤=÷=¤=÷=¤=÷=¤=÷=¤=÷=¤=÷=¤=÷=¤=÷=¤=÷=¤=÷=¤=÷=¤=÷=¤=÷=¤=÷=¤=÷=¤=÷=¤
