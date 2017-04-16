object Form1: TForm1
  Left = 251
  Top = 208
  Width = 613
  Height = 429
  Caption = #1047#1072#1076#1072#1095#1072' '#1086' '#1075#1088#1072#1073#1080#1090#1077#1083#1077
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
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 241
    Height = 371
    Align = alLeft
    TabOrder = 0
    object Panel3: TPanel
      Left = 1
      Top = 1
      Width = 239
      Height = 48
      Align = alTop
      Color = clYellow
      TabOrder = 0
      object Edit1: TEdit
        Left = 24
        Top = 8
        Width = 89
        Height = 32
        Color = clMenuHighlight
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -21
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        Text = '3'
      end
      object Edit2: TEdit
        Left = 136
        Top = 8
        Width = 81
        Height = 32
        Color = clYellow
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -21
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 1
        Text = '13'
      end
    end
    object RichEdit1: TRichEdit
      Left = 1
      Top = 49
      Width = 239
      Height = 321
      Align = alClient
      Color = clGradientInactiveCaption
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -21
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      Lines.Strings = (
        '3 5 8'
        '8 14 23')
      ParentFont = False
      TabOrder = 1
    end
  end
  object Panel4: TPanel
    Left = 241
    Top = 0
    Width = 356
    Height = 371
    Align = alClient
    TabOrder = 1
    object RichEdit2: TRichEdit
      Left = 1
      Top = 1
      Width = 354
      Height = 369
      Align = alClient
      Color = clPurple
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clMenuHighlight
      Font.Height = -21
      Font.Name = 'MS Sans Serif'
      Font.Pitch = fpFixed
      Font.Style = []
      ParentFont = False
      ScrollBars = ssVertical
      TabOrder = 0
    end
  end
  object MainMenu1: TMainMenu
    Left = 480
    Top = 216
    object N1: TMenuItem
      Caption = '>> start'
      ShortCut = 16467
      OnClick = N1Click
    end
  end
end
