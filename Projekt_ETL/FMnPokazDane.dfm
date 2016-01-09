object FMainPokazDane: TFMainPokazDane
  Left = 0
  Top = 0
  Caption = 'Dane prduktu i opini'
  ClientHeight = 618
  ClientWidth = 1017
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 24
    Top = 8
    Width = 92
    Height = 18
    Caption = 'Kod produktu:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Label2: TLabel
    Left = 24
    Top = 33
    Width = 45
    Height = 18
    Caption = 'Marka:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Label3: TLabel
    Left = 24
    Top = 83
    Width = 123
    Height = 18
    Caption = 'Rodzaj urz'#261'dzenia:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Label4: TLabel
    Left = 24
    Top = 58
    Width = 43
    Height = 18
    Caption = 'Model:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Label5: TLabel
    Left = 24
    Top = 108
    Width = 118
    Height = 18
    Caption = 'Dodatkowe uwagi:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object LblKodProduktu: TLabel
    Left = 168
    Top = 8
    Width = 5
    Height = 18
    Caption = '-'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object LblMarka: TLabel
    Left = 168
    Top = 33
    Width = 5
    Height = 18
    Caption = '-'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object LblModel: TLabel
    Left = 168
    Top = 58
    Width = 5
    Height = 18
    Caption = '-'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object LblRodzUrz: TLabel
    Left = 168
    Top = 83
    Width = 5
    Height = 18
    Caption = '-'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object LblDodUwagi: TLabel
    Left = 168
    Top = 108
    Width = 825
    Height = 61
    AutoSize = False
    Caption = '-'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    WordWrap = True
  end
  object Label6: TLabel
    Left = 24
    Top = 144
    Width = 28
    Height = 13
    Caption = 'Opini:'
  end
  object LblIlOpini: TLabel
    Left = 64
    Top = 144
    Width = 4
    Height = 13
    Caption = '-'
  end
  object Label7: TLabel
    Left = 482
    Top = 11
    Width = 41
    Height = 13
    Caption = 'Produkt:'
  end
  object Label8: TLabel
    Left = 484
    Top = 40
    Width = 39
    Height = 13
    Caption = 'Id opini:'
  end
  object Label9: TLabel
    Left = 350
    Top = 368
    Width = 290
    Height = 23
    Caption = 'Brak opini dla wybranego prouktu!'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object StringGrid1: TStringGrid
    Left = 8
    Top = 181
    Width = 1001
    Height = 429
    ColCount = 6
    RowCount = 1
    FixedRows = 0
    TabOrder = 0
    OnDrawCell = StringGrid1DrawCell
  end
  object Cbx: TComboBox
    Left = 529
    Top = 8
    Width = 145
    Height = 21
    TabOrder = 1
    OnClick = CbxClick
  end
  object BtnZapisz: TButton
    Left = 680
    Top = 8
    Width = 97
    Height = 28
    Caption = 'Zapis do pliku CSV'
    TabOrder = 2
    OnClick = BtnZapiszClick
  end
  object EdIdOpini: TEdit
    Left = 529
    Top = 37
    Width = 113
    Height = 21
    TabOrder = 3
  end
  object BtnZapisTxt: TButton
    Left = 648
    Top = 35
    Width = 129
    Height = 25
    Caption = 'Zapis opini do pliku txt'
    TabOrder = 4
    OnClick = BtnZapisTxtClick
  end
  object SDialog: TSaveDialog
    Filter = '*.cvs|*.csv'
    Left = 808
    Top = 8
  end
  object SDialog2: TSaveDialog
    Filter = '*.txt|*.txt'
    Left = 808
    Top = 56
  end
end
