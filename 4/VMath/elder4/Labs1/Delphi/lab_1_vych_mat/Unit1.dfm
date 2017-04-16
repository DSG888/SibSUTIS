object Form1: TForm1
  Left = 229
  Top = 225
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
  object Label1: TLabel
    Left = 8
    Top = 152
    Width = 30
    Height = 13
    Caption = #1054#1090#1074#1077#1090
  end
  object Label2: TLabel
    Left = 192
    Top = 56
    Width = 189
    Height = 13
    Caption = #1063#1080#1089#1083#1086' '#1080#1079#1084#1077#1085#1077#1085#1080#1103' '#1079#1085#1072#1095#1077#1085#1080#1081' '#1084#1072#1090#1088#1080#1094#1099
  end
  object Label3: TLabel
    Left = 16
    Top = 264
    Width = 29
    Height = 13
    Caption = #1064#1072#1075' 1'
  end
  object Label4: TLabel
    Left = 216
    Top = 264
    Width = 29
    Height = 13
    Caption = #1064#1072#1075' 2'
  end
  object Label5: TLabel
    Left = 456
    Top = 264
    Width = 29
    Height = 13
    Caption = #1064#1072#1075' 3'
  end
  object Label6: TLabel
    Left = 472
    Top = 32
    Width = 125
    Height = 13
    Caption = #1059#1087#1086#1088#1103#1076#1086#1095#1077#1085#1085#1072#1103' '#1084#1072#1090#1088#1080#1094#1072
    Visible = False
  end
  object Label7: TLabel
    Left = 296
    Top = 195
    Width = 29
    Height = 13
    Caption = #1064#1072#1075' 1'
  end
  object Label8: TLabel
    Left = 296
    Top = 221
    Width = 29
    Height = 13
    Caption = #1064#1072#1075' 2'
  end
  object Button1: TButton
    Left = 192
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
    Width = 177
    Height = 137
    DefaultColWidth = 24
    RowCount = 4
    TabOrder = 1
    OnClick = StringGrid1Click
  end
  object StringGrid2: TStringGrid
    Left = 448
    Top = 288
    Width = 177
    Height = 137
    DefaultColWidth = 24
    RowCount = 4
    TabOrder = 2
    RowHeights = (
      24
      24
      24
      24)
  end
  object Button2: TButton
    Left = 192
    Top = 104
    Width = 193
    Height = 25
    Caption = #1048#1079#1084#1077#1085#1080#1090#1100' '#1088#1072#1079#1084#1077#1088' '#1084#1072#1090#1088#1080#1094#1099
    TabOrder = 3
    Visible = False
    OnClick = Button2Click
  end
  object Edit1: TEdit
    Left = 192
    Top = 80
    Width = 121
    Height = 21
    TabOrder = 4
    Text = '1'
  end
  object Memo1: TMemo
    Left = 8
    Top = 168
    Width = 177
    Height = 89
    TabOrder = 5
  end
  object Edit2: TEdit
    Left = 192
    Top = 136
    Width = 121
    Height = 21
    TabOrder = 6
    Text = '3'
    Visible = False
  end
  object CheckBox1: TCheckBox
    Left = 472
    Top = 8
    Width = 193
    Height = 17
    Caption = #1088#1077#1096#1077#1085#1080#1077' '#1091#1087#1086#1088#1103#1076#1086#1095#1077#1085#1085#1086#1081' '#1084#1072#1090#1088#1080#1094#1099
    TabOrder = 7
  end
  object StringGrid3: TStringGrid
    Left = 8
    Top = 288
    Width = 177
    Height = 137
    DefaultColWidth = 24
    RowCount = 4
    TabOrder = 8
  end
  object StringGrid4: TStringGrid
    Left = 208
    Top = 288
    Width = 177
    Height = 137
    DefaultColWidth = 24
    RowCount = 4
    TabOrder = 9
    RowHeights = (
      24
      24
      24
      22)
  end
  object StringGrid5: TStringGrid
    Left = 472
    Top = 48
    Width = 177
    Height = 137
    DefaultColWidth = 24
    RowCount = 4
    TabOrder = 10
    Visible = False
    OnClick = StringGrid1Click
  end
  object Button3: TButton
    Left = 192
    Top = 168
    Width = 81
    Height = 25
    Caption = #1054#1090#1082#1088#1099#1090#1100' '#1092#1072#1081#1083
    TabOrder = 11
    OnClick = Button3Click
  end
  object Memo2: TMemo
    Left = 328
    Top = 192
    Width = 305
    Height = 65
    TabOrder = 12
  end
  object OpenDialog1: TOpenDialog
    FilterIndex = 0
    Left = 192
    Top = 200
  end
end
