object Form1: TForm1
  Left = 299
  Top = 247
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
    Left = 120
    Top = 40
    Width = 189
    Height = 13
    Caption = #1063#1080#1089#1083#1086' '#1080#1079#1084#1077#1085#1077#1085#1080#1103' '#1079#1085#1072#1095#1077#1085#1080#1081' '#1084#1072#1090#1088#1080#1094#1099
  end
  object Label5: TLabel
    Left = 456
    Top = 264
    Width = 30
    Height = 13
    Caption = #1054#1090#1074#1077#1090
  end
  object Label1: TLabel
    Left = 120
    Top = 88
    Width = 102
    Height = 13
    Caption = #1084#1072#1090#1088#1080#1094#1072' '#1074' '#1082#1074#1072#1076#1088#1072#1090#1077
    OnClick = Label1Click
  end
  object Button1: TButton
    Left = 120
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
    Width = 105
    Height = 105
    ColCount = 4
    DefaultColWidth = 24
    RowCount = 4
    TabOrder = 1
    OnClick = StringGrid1Click
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
  object StringGrid2: TStringGrid
    Left = 16
    Top = 288
    Width = 633
    Height = 105
    ColCount = 4
    DefaultColWidth = 155
    RowCount = 4
    TabOrder = 2
    RowHeights = (
      24
      24
      24
      24)
  end
  object Button2: TButton
    Left = 120
    Top = 120
    Width = 153
    Height = 25
    Caption = #1048#1079#1084#1077#1085#1080#1090#1100' '#1088#1072#1079#1084#1077#1088' '#1084#1072#1090#1088#1080#1094#1099
    TabOrder = 3
    OnClick = Button2Click
  end
  object Edit1: TEdit
    Left = 120
    Top = 56
    Width = 121
    Height = 21
    TabOrder = 4
    Text = '1'
  end
  object Edit2: TEdit
    Left = 120
    Top = 152
    Width = 153
    Height = 21
    TabOrder = 5
    Text = '3'
  end
  object CheckBox1: TCheckBox
    Left = 192
    Top = 256
    Width = 201
    Height = 17
    Caption = #1084#1072#1090#1088#1080#1094#1072' '#1074' '#1082#1074#1072#1076#1088#1072#1090#1077
    TabOrder = 6
    Visible = False
    OnClick = CheckBox1Click
  end
  object Button3: TButton
    Left = 288
    Top = 8
    Width = 97
    Height = 25
    Caption = #1054#1090#1082#1088#1099#1090#1100' '#1092#1072#1081#1083
    TabOrder = 7
    OnClick = Button3Click
  end
  object Memo1: TMemo
    Left = 32
    Top = 408
    Width = 185
    Height = 89
    Lines.Strings = (
      'Memo1')
    TabOrder = 8
    Visible = False
  end
  object Edit3: TEdit
    Left = 120
    Top = 176
    Width = 153
    Height = 21
    TabOrder = 9
    Text = '3'
    Visible = False
  end
  object Edit4: TEdit
    Left = 280
    Top = 152
    Width = 153
    Height = 21
    TabOrder = 10
    Text = '3'
    Visible = False
  end
  object Edit5: TEdit
    Left = 280
    Top = 176
    Width = 153
    Height = 21
    TabOrder = 11
    Text = '3'
    Visible = False
  end
  object StringGrid3: TStringGrid
    Left = 8
    Top = 120
    Width = 105
    Height = 105
    ColCount = 4
    DefaultColWidth = 24
    RowCount = 4
    TabOrder = 12
    Visible = False
    OnClick = StringGrid3Click
    RowHeights = (
      24
      24
      24
      24)
  end
  object Button4: TButton
    Left = 280
    Top = 120
    Width = 153
    Height = 25
    Caption = #1048#1079#1084#1077#1085#1080#1090#1100' '#1088#1072#1079#1084#1077#1088' '#1084#1072#1090#1088#1080#1094#1099
    TabOrder = 13
    Visible = False
    OnClick = Button4Click
  end
  object Button5: TButton
    Left = 288
    Top = 80
    Width = 97
    Height = 25
    Caption = #1054#1090#1082#1088#1099#1090#1100' '#1092#1072#1081#1083' 2'
    TabOrder = 14
    Visible = False
    OnClick = Button5Click
  end
  object Button6: TButton
    Left = 432
    Top = 56
    Width = 75
    Height = 25
    Caption = 'Button6'
    TabOrder = 15
    OnKeyPress = Button6KeyPress
  end
  object Button7: TButton
    Left = 536
    Top = 192
    Width = 75
    Height = 25
    Caption = 'Button7'
    TabOrder = 16
  end
  object OpenDialog1: TOpenDialog
    Left = 424
    Top = 216
  end
end
