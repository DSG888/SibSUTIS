object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 216
  ClientWidth = 167
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  PopupMenu = PopupMenu1
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 31
    Top = 192
    Width = 32
    Height = 13
    Caption = #1054#1090#1074#1077#1090
  end
  object Label2: TLabel
    Left = 8
    Top = 23
    Width = 69
    Height = 13
    Caption = #1055#1077#1088#1074#1086#1077' '#1095#1080#1089#1083#1086
  end
  object Label3: TLabel
    Left = 8
    Top = 55
    Width = 68
    Height = 13
    Caption = #1042#1090#1086#1088#1086#1077' '#1095#1080#1089#1083#1086
  end
  object Button1: TButton
    Left = 23
    Top = 74
    Width = 33
    Height = 25
    Caption = '+'
    TabOrder = 0
    OnClick = Button1Click
  end
  object Edit1: TEdit
    Left = 83
    Top = 20
    Width = 57
    Height = 21
    TabOrder = 1
  end
  object Button2: TButton
    Left = 82
    Top = 74
    Width = 33
    Height = 25
    Caption = '-'
    TabOrder = 2
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 24
    Top = 105
    Width = 33
    Height = 25
    Caption = '/'
    TabOrder = 3
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 82
    Top = 105
    Width = 33
    Height = 25
    Caption = '*'
    TabOrder = 4
    OnClick = Button4Click
  end
  object Edit2: TEdit
    Left = 83
    Top = 47
    Width = 58
    Height = 21
    TabOrder = 5
  end
  object RadioButton1: TRadioButton
    Left = 31
    Top = 136
    Width = 32
    Height = 17
    Caption = '+'
    TabOrder = 6
    OnClick = RadioButton1Click
  end
  object RadioButton2: TRadioButton
    Left = 87
    Top = 136
    Width = 25
    Height = 17
    Caption = '-'
    TabOrder = 7
    OnClick = RadioButton2Click
  end
  object RadioButton3: TRadioButton
    Left = 31
    Top = 159
    Width = 33
    Height = 17
    Caption = '/'
    TabOrder = 8
    OnClick = RadioButton3Click
  end
  object RadioButton4: TRadioButton
    Left = 87
    Top = 159
    Width = 25
    Height = 17
    Caption = '*'
    TabOrder = 9
    OnClick = RadioButton4Click
  end
  object MainMenu1: TMainMenu
    Left = 128
    Top = 184
    object N1: TMenuItem
      Caption = #1086#1087#1077#1088#1072#1094#1080#1080
      object N2: TMenuItem
        Caption = '+'
        OnClick = N2Click
      end
      object N3: TMenuItem
        Caption = ' - '
        OnClick = N3Click
      end
      object N4: TMenuItem
        Caption = '/'
        OnClick = N4Click
      end
      object N5: TMenuItem
        Caption = '*'
        OnClick = N5Click
      end
    end
  end
  object PopupMenu1: TPopupMenu
    Left = 88
    Top = 184
    object N6: TMenuItem
      Caption = #1057#1083#1086#1078#1080#1090#1100
      OnClick = N6Click
    end
    object N7: TMenuItem
      Caption = #1042#1099#1095#1077#1089#1090#1100
      OnClick = N7Click
    end
    object N8: TMenuItem
      Caption = #1056#1072#1079#1076#1077#1083#1080#1090#1100
      OnClick = N8Click
    end
    object N9: TMenuItem
      Caption = #1059#1084#1085#1086#1078#1080#1090#1100
      OnClick = N9Click
    end
  end
end
