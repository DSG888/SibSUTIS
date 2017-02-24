object Form1: TForm1
  Left = 152
  Top = 57
  Width = 802
  Height = 454
  Caption = 'Form1'
  Color = clSilver
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Image1: TImage
    Left = 0
    Top = 0
    Width = 729
    Height = 385
  end
  object Memo1: TMemo
    Left = 736
    Top = 24
    Width = 41
    Height = 273
    Lines.Strings = (
      'Memo1')
    TabOrder = 0
  end
  object Timer1: TTimer
    Interval = 1
    OnTimer = Timer1Timer
    Left = 248
    Top = 368
  end
end
