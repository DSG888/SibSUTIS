object Form1: TForm1
  Left = 84
  Top = 148
  Width = 928
  Height = 480
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindow
  Font.Height = -24
  Font.Name = 'Comic Sans MS'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 33
  object Label1: TLabel
    Left = 32
    Top = 136
    Width = 268
    Height = 33
    Caption = 'Num of elements in a row'
    Font.Charset = GB2312_CHARSET
    Font.Color = clMenuText
    Font.Height = -24
    Font.Name = 'Comic Sans MS'
    Font.Style = []
    ParentFont = False
  end
  object StringGrid1: TStringGrid
    Left = 24
    Top = 16
    Width = 753
    Height = 97
    Color = clBlue
    ColCount = 1
    FixedCols = 0
    RowCount = 1
    FixedRows = 0
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindow
    Font.Height = -16
    Font.Name = 'Comic Sans MS'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
  end
  object Edit1: TEdit
    Left = 344
    Top = 128
    Width = 121
    Height = 37
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clRed
    Font.Height = -24
    Font.Name = 'Verdana'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    OnChange = Edit1Change
  end
  object Button2: TButton
    Left = 32
    Top = 248
    Width = 137
    Height = 33
    Caption = 'Select Sort'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindow
    Font.Height = -13
    Font.Name = 'Comic Sans MS'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 224
    Top = 248
    Width = 137
    Height = 33
    Caption = 'Bubble Sort'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindow
    Font.Height = -13
    Font.Name = 'Comic Sans MS'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 416
    Top = 248
    Width = 137
    Height = 33
    Caption = 'Merge Sort'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindow
    Font.Height = -13
    Font.Name = 'Comic Sans MS'
    Font.Style = []
    ParentFont = False
    TabOrder = 4
    OnClick = Button4Click
  end
  object StringGrid2: TStringGrid
    Left = 40
    Top = 312
    Width = 320
    Height = 73
    Color = clYellow
    FixedCols = 0
    RowCount = 1
    FixedRows = 0
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindow
    Font.Height = -16
    Font.Name = 'Comic Sans MS'
    Font.Style = []
    ParentFont = False
    TabOrder = 5
    Visible = False
  end
  object StringGrid3: TStringGrid
    Left = 200
    Top = 360
    Width = 1
    Height = 73
    TabOrder = 6
  end
  object StringGrid4: TStringGrid
    Left = 416
    Top = 312
    Width = 320
    Height = 73
    Color = clYellow
    FixedCols = 0
    RowCount = 1
    FixedRows = 0
    TabOrder = 7
    Visible = False
  end
end
