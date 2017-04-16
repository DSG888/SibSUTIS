object Form1: TForm1
  Left = 237
  Top = 198
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
  object Image1: TImage
    Left = 16
    Top = 16
    Width = 353
    Height = 329
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
  object SG: TStringGrid
    Left = 552
    Top = 8
    Width = 129
    Height = 57
    DefaultColWidth = 24
    RowCount = 2
    TabOrder = 1
    OnClick = SGClick
    ColWidths = (
      24
      24
      24
      24
      24)
  end
  object Edit5: TEdit
    Left = 552
    Top = 72
    Width = 129
    Height = 21
    TabOrder = 2
    Text = '1'
  end
  object Edit1: TEdit
    Left = 552
    Top = 96
    Width = 129
    Height = 21
    TabOrder = 3
    Text = '1'
  end
  object Edit2: TEdit
    Left = 424
    Top = 48
    Width = 121
    Height = 21
    TabOrder = 4
    Text = '1'
  end
  object Edit3: TEdit
    Left = 392
    Top = 96
    Width = 121
    Height = 21
    TabOrder = 5
    Text = '2'
  end
  object Memo1: TMemo
    Left = 392
    Top = 160
    Width = 265
    Height = 177
    Lines.Strings = (
      'Memo1')
    TabOrder = 6
    Visible = False
  end
end
