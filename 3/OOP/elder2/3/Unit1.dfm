object Form1: TForm1
  Left = 373
  Top = 118
  Width = 928
  Height = 480
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object PaintBox1: TPaintBox
    Left = 16
    Top = 8
    Width = 889
    Height = 361
  end
  object Button1: TButton
    Left = 16
    Top = 400
    Width = 185
    Height = 33
    Caption = 'Draw'
    TabOrder = 0
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 632
    Top = 400
    Width = 185
    Height = 33
    Caption = 'Exit'
    TabOrder = 1
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 328
    Top = 400
    Width = 185
    Height = 33
    Caption = 'Move'
    TabOrder = 2
    OnClick = Button3Click
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 50
    OnTimer = Timer1Timer
    Left = 48
    Top = 24
  end
end
