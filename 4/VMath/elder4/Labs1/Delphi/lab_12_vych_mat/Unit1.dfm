object Form1: TForm1
  Left = 211
  Top = 146
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
    Width = 300
    Height = 300
  end
  object Button1: TButton
    Left = 344
    Top = 16
    Width = 75
    Height = 25
    Caption = #1042#1099#1095#1080#1089#1083#1080#1090#1100
    TabOrder = 0
    OnClick = Button1Click
  end
  object SG: TStringGrid
    Left = 528
    Top = 8
    Width = 153
    Height = 57
    ColCount = 6
    DefaultColWidth = 24
    RowCount = 2
    TabOrder = 1
    OnClick = SGClick
    ColWidths = (
      24
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
    Left = 432
    Top = 200
    Width = 121
    Height = 21
    TabOrder = 3
    Text = 'Edit1'
  end
end
