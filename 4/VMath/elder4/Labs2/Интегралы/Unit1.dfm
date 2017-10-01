object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 389
  ClientWidth = 628
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label2: TLabel
    Left = 8
    Top = 81
    Width = 21
    Height = 19
    Caption = 'n='
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    OnClick = Label2Click
  end
  object Label3: TLabel
    Left = 7
    Top = 106
    Width = 20
    Height = 19
    Caption = 'a='
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Label4: TLabel
    Left = 8
    Top = 133
    Width = 21
    Height = 19
    Caption = 'b='
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Label1: TLabel
    Left = 8
    Top = 167
    Width = 39
    Height = 19
    Caption = 'E=10'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Label5: TLabel
    Left = 53
    Top = 160
    Width = 6
    Height = 19
    Caption = '-'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Button1: TButton
    Left = 8
    Top = 8
    Width = 89
    Height = 25
    Caption = #1058#1088#1072#1087#1077#1094#1080#1080
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 8
    Top = 39
    Width = 89
    Height = 25
    Caption = #1057#1080#1084#1089#1086#1085#1072
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    OnClick = Button2Click
  end
  object Memo1: TMemo
    Left = 107
    Top = 8
    Width = 254
    Height = 373
    TabOrder = 2
  end
  object numN: TMaskEdit
    Left = 33
    Top = 79
    Width = 66
    Height = 21
    EditMask = '!99999;0;_'
    MaxLength = 5
    TabOrder = 3
    Text = '10   '
  end
  object numA: TMaskEdit
    Left = 33
    Top = 106
    Width = 67
    Height = 21
    EditMask = '!99999;0;_'
    MaxLength = 5
    TabOrder = 4
    Text = '1    '
  end
  object numB: TMaskEdit
    Left = 34
    Top = 133
    Width = 66
    Height = 21
    EditMask = '!99999;0;_'
    MaxLength = 5
    TabOrder = 5
    Text = '3    '
  end
  object Memo2: TMemo
    Left = 367
    Top = 8
    Width = 257
    Height = 377
    TabOrder = 6
  end
  object Edit1: TEdit
    Left = 65
    Top = 160
    Width = 36
    Height = 21
    TabOrder = 7
    Text = '7'
  end
end
