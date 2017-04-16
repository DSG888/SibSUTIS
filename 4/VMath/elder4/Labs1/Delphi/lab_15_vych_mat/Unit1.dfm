object Form1: TForm1
  Left = 221
  Top = 382
  Width = 695
  Height = 480
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 16
    Top = 96
    Width = 8
    Height = 13
    Caption = 'H'
  end
  object Label2: TLabel
    Left = 8
    Top = 128
    Width = 21
    Height = 13
    Caption = 'EPS'
  end
  object Label3: TLabel
    Left = 16
    Top = 24
    Width = 6
    Height = 13
    Caption = 'a'
  end
  object Label4: TLabel
    Left = 16
    Top = 64
    Width = 6
    Height = 13
    Caption = 'b'
  end
  object Button1: TButton
    Left = 424
    Top = 16
    Width = 75
    Height = 25
    Caption = #1042#1099#1095#1080#1089#1083#1080#1090#1100
    TabOrder = 0
    OnClick = Button1Click
  end
  object Memo1: TMemo
    Left = 24
    Top = 168
    Width = 449
    Height = 89
    TabOrder = 1
  end
  object Edit1: TEdit
    Left = 40
    Top = 24
    Width = 121
    Height = 21
    TabOrder = 2
    Text = '1'
  end
  object Edit2: TEdit
    Left = 40
    Top = 64
    Width = 121
    Height = 21
    TabOrder = 3
    Text = '12'
  end
  object Edit3: TEdit
    Left = 40
    Top = 96
    Width = 121
    Height = 21
    TabOrder = 4
    Text = '0,1'
  end
  object Edit4: TEdit
    Left = 40
    Top = 128
    Width = 121
    Height = 21
    TabOrder = 5
    Text = '0,0000001'
  end
  object RadioButton1: TRadioButton
    Left = 448
    Top = 80
    Width = 113
    Height = 17
    Caption = 'sqrt'
    TabOrder = 6
  end
  object RadioButton2: TRadioButton
    Left = 448
    Top = 104
    Width = 113
    Height = 17
    Caption = '1/c'
    TabOrder = 7
  end
end
