object Form1: TForm1
  Left = 272
  Top = 234
  Width = 696
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
  object Label2: TLabel
    Left = 144
    Top = 40
    Width = 189
    Height = 13
    Caption = #1063#1080#1089#1083#1086' '#1080#1079#1084#1077#1085#1077#1085#1080#1103' '#1079#1085#1072#1095#1077#1085#1080#1081' '#1084#1072#1090#1088#1080#1094#1099
  end
  object Label5: TLabel
    Left = 16
    Top = 272
    Width = 30
    Height = 13
    Caption = #1054#1090#1074#1077#1090
  end
  object Button1: TButton
    Left = 144
    Top = 8
    Width = 161
    Height = 25
    Caption = #1056#1077#1096#1080#1090#1100' '#1084#1072#1090#1088#1080#1094#1091
    TabOrder = 0
    OnClick = Button1Click
  end
  object StringGrid1: TStringGrid
    Left = 8
    Top = 8
    Width = 129
    Height = 105
    DefaultColWidth = 24
    RowCount = 4
    TabOrder = 1
    OnClick = StringGrid1Click
    ColWidths = (
      24
      24
      24
      24
      24)
    RowHeights = (
      24
      24
      24
      24)
  end
  object Edit1: TEdit
    Left = 144
    Top = 56
    Width = 121
    Height = 21
    TabOrder = 2
    Text = '1'
  end
  object Button3: TButton
    Left = 312
    Top = 8
    Width = 97
    Height = 25
    Caption = #1054#1090#1082#1088#1099#1090#1100' '#1092#1072#1081#1083
    TabOrder = 3
    OnClick = Button3Click
  end
  object StringGrid3: TStringGrid
    Left = 8
    Top = 120
    Width = 105
    Height = 105
    ColCount = 4
    DefaultColWidth = 24
    RowCount = 4
    TabOrder = 4
    ColWidths = (
      24
      24
      24
      24)
    RowHeights = (
      24
      24
      24
      24)
  end
  object StringGrid4: TStringGrid
    Left = 120
    Top = 120
    Width = 57
    Height = 105
    ColCount = 2
    DefaultColWidth = 24
    RowCount = 4
    TabOrder = 5
    RowHeights = (
      24
      24
      24
      24)
  end
  object Memo1: TMemo
    Left = 216
    Top = 144
    Width = 185
    Height = 89
    Lines.Strings = (
      'Memo1')
    TabOrder = 6
    Visible = False
  end
  object Memo2: TMemo
    Left = 16
    Top = 288
    Width = 633
    Height = 89
    Lines.Strings = (
      'Memo2')
    ScrollBars = ssVertical
    TabOrder = 7
  end
  object Edit2: TEdit
    Left = 368
    Top = 88
    Width = 121
    Height = 21
    TabOrder = 8
    Text = '0,0001'
  end
  object OpenDialog1: TOpenDialog
    Left = 424
    Top = 216
  end
end
