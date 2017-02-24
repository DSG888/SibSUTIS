object Form1: TForm1
  Left = 195
  Top = 154
  Width = 928
  Height = 510
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object PaintBox1: TPaintBox
    Left = 8
    Top = 32
    Width = 897
    Height = 409
    Color = clBtnFace
    ParentColor = False
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 50
    OnTimer = Timer1Timer
    Left = 872
  end
  object MainMenu1: TMainMenu
    Left = 16
    object Add1: TMenuItem
      Caption = 'Add'
      object Point1: TMenuItem
        Caption = 'Point'
        OnClick = Point1Click
      end
      object Line1: TMenuItem
        Caption = 'Line'
        OnClick = Line1Click
      end
      object Circle1: TMenuItem
        Caption = 'Circle'
        OnClick = Circle1Click
      end
      object Rectangle1: TMenuItem
        Caption = 'Rectangle'
        OnClick = Rectangle1Click
      end
      object Triangle1: TMenuItem
        Caption = 'Triangle'
        OnClick = Triangle1Click
      end
      object Ellipse1: TMenuItem
        Caption = 'Ellipse'
        OnClick = Ellipse1Click
      end
      object Romb1: TMenuItem
        Caption = 'Romb'
        OnClick = Romb1Click
      end
    end
    object Move1: TMenuItem
      Caption = 'Move'
      object Linear1: TMenuItem
        Caption = 'Linear'
        OnClick = Linear1Click
      end
      object Chaotic1: TMenuItem
        Caption = 'Chaotic'
        OnClick = Chaotic1Click
      end
    end
  end
end
