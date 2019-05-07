object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'SQLite Viewer'
  ClientHeight = 441
  ClientWidth = 802
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object LabelStatus: TLabel
    Left = 8
    Top = 365
    Width = 226
    Height = 13
    Caption = #1044#1083#1103' '#1085#1072#1095#1072#1083#1072' '#1088#1072#1073#1086#1090#1099', '#1079#1072#1075#1088#1091#1079#1080#1090#1077' '#1073#1072#1079#1091' '#1076#1072#1085#1085#1099#1093
  end
  object ButtonLoad: TButton
    Left = 8
    Top = 392
    Width = 145
    Height = 41
    Caption = #1047#1072#1075#1088#1091#1079#1080#1090#1100' '#1073#1072#1079#1091' '#1076#1072#1085#1085#1099#1093
    TabOrder = 0
    OnClick = ButtonLoadClick
  end
  object ButtonSelect: TButton
    Left = 168
    Top = 392
    Width = 145
    Height = 41
    Caption = #1054#1090#1086#1073#1088#1072#1079#1080#1090#1100' '#1076#1072#1085#1085#1099#1077
    Enabled = False
    TabOrder = 1
    OnClick = ButtonSelectClick
  end
  object ButtonDelete: TButton
    Left = 327
    Top = 392
    Width = 146
    Height = 41
    Caption = #1059#1076#1072#1083#1080#1090#1100' '#1089#1090#1088#1086#1082#1091
    Enabled = False
    TabOrder = 2
    OnClick = ButtonDeleteClick
  end
  object ButtonDeleteAll: TButton
    Left = 487
    Top = 392
    Width = 146
    Height = 41
    Caption = #1059#1076#1072#1083#1080#1090#1100' '#1074#1089#1077' '#1076#1072#1085#1085#1099#1077
    Enabled = False
    TabOrder = 3
    OnClick = ButtonDeleteAllClick
  end
  object ButtonClose: TButton
    Left = 647
    Top = 392
    Width = 146
    Height = 41
    Caption = #1047#1072#1082#1088#1099#1090#1100' '#1087#1088#1080#1083#1086#1078#1077#1085#1080#1077
    TabOrder = 4
    OnClick = ButtonCloseClick
  end
  object VirtualStringTree1: TVirtualStringTree
    Left = 8
    Top = 8
    Width = 786
    Height = 345
    Header.AutoSizeIndex = 0
    Header.Height = 20
    Header.Options = [hoColumnResize, hoDrag, hoShowSortGlyphs, hoVisible]
    TabOrder = 5
    TreeOptions.PaintOptions = [toShowButtons, toShowDropmark, toShowRoot, toShowTreeLines, toShowVertGridLines, toThemeAware, toUseBlendedImages]
    TreeOptions.SelectionOptions = [toFullRowSelect]
    Visible = False
    OnGetText = VirtualStringTree1GetText
    Columns = <
      item
        Position = 0
        Text = 'Id'
        Width = 89
      end
      item
        Position = 1
        Text = 'URL'
        Width = 361
      end
      item
        Position = 2
        Text = #1053#1072#1079#1074#1072#1085#1080#1077
        Width = 116
      end
      item
        Position = 3
        Text = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1074#1080#1079#1080#1090#1086#1074
        Width = 122
      end>
  end
  object OpenDialog1: TOpenDialog
    Left = 768
    Top = 8
  end
end
