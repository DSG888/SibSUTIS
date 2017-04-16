object Form1: TForm1
  Left = 67
  Top = 243
  Width = 1242
  Height = 280
  Caption = #1040#1083#1075#1086#1088#1080#1090#1084' '#1044#1077#1081#1082#1077#1089#1090#1088#1099
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
    Width = 177
    Height = 222
    Align = alLeft
    TabOrder = 0
    object Panel2: TPanel
      Left = 1
      Top = 1
      Width = 176
      Height = 16
      Align = alCustom
      Caption = 'G(V,E)'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
    end
    object RichEdit1: TRichEdit
      Left = 1
      Top = 17
      Width = 168
      Height = 204
      TabStop = False
      Align = alCustom
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
    end
  end
  object Panel3: TPanel
    Left = 177
    Top = 0
    Width = 1049
    Height = 222
    Align = alClient
    TabOrder = 1
    object Panel5: TPanel
      Left = 1
      Top = 1
      Width = 112
      Height = 220
      Align = alLeft
      Alignment = taLeftJustify
      TabOrder = 0
      object Panel6: TPanel
        Left = -15
        Top = 17
        Width = 126
        Height = 16
        Align = alCustom
        Caption = 'S'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -19
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
      end
      object RichEdit2: TRichEdit
        Left = 0
        Top = 32
        Width = 113
        Height = 201
        Align = alCustom
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clNavy
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 1
      end
    end
    object Panel7: TPanel
      Left = 113
      Top = 1
      Width = 53
      Height = 220
      Align = alLeft
      TabOrder = 1
      object Panel8: TPanel
        Left = 1
        Top = 17
        Width = 51
        Height = 16
        Align = alCustom
        Caption = 'w'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -19
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
      end
      object RichEdit3: TRichEdit
        Left = 1
        Top = 32
        Width = 51
        Height = 187
        Align = alCustom
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGreen
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 1
      end
    end
    object Panel9: TPanel
      Left = 166
      Top = 1
      Width = 77
      Height = 220
      Align = alLeft
      TabOrder = 2
      object Panel10: TPanel
        Left = 1
        Top = 17
        Width = 75
        Height = 16
        Align = alCustom
        Caption = 'D(w)'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -19
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
      end
      object RichEdit4: TRichEdit
        Left = 1
        Top = 32
        Width = 75
        Height = 187
        Align = alCustom
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGreen
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 1
      end
    end
    object Panel11: TPanel
      Left = 243
      Top = 1
      Width = 805
      Height = 220
      Align = alClient
      TabOrder = 3
      object Panel12: TPanel
        Left = 1
        Top = 1
        Width = 803
        Height = 16
        Align = alTop
        Caption = #1058#1072#1073#1083#1080#1094#1072
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -19
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
      end
      object RichEdit5: TRichEdit
        Left = 1
        Top = 17
        Width = 803
        Height = 202
        Align = alClient
        Color = clMenu
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        HideScrollBars = False
        ParentFont = False
        ScrollBars = ssHorizontal
        TabOrder = 1
      end
    end
  end
  object MainMenu1: TMainMenu
    Left = 800
    Top = 176
    object N1: TMenuItem
      Caption = #1060#1072#1080#1083
      object N2: TMenuItem
        Caption = #1054#1090#1082#1088#1099#1090#1100
        OnClick = N2Click
      end
      object N3: TMenuItem
        Caption = #1042#1099#1093#1086#1076
        OnClick = N3Click
      end
    end
    object N4: TMenuItem
      Caption = #1042#1099#1087#1086#1083#1085#1080#1090#1100
      OnClick = N4Click
    end
  end
  object OpenDialog1: TOpenDialog
    Left = 832
    Top = 176
  end
end
