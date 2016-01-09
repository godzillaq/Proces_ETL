object FMainExtractor: TFMainExtractor
  Left = 0
  Top = 0
  Caption = 'ExTraktor'
  ClientHeight = 355
  ClientWidth = 544
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label3: TLabel
    Left = 119
    Top = 27
    Width = 100
    Height = 13
    Caption = 'Kod produktu ceneo:'
  end
  object BtnETL: TButton
    Left = 8
    Top = 8
    Width = 89
    Height = 57
    Caption = 'ETL'
    TabOrder = 0
    OnClick = BtnETLClick
  end
  object EdKodProduktu: TEdit
    Left = 225
    Top = 24
    Width = 88
    Height = 21
    TabOrder = 1
    Text = '28513296'
  end
  object BtnCzyscBaze: TButton
    Left = 8
    Top = 316
    Width = 89
    Height = 27
    Caption = 'Wyczy'#347#263' baz'#281
    TabOrder = 2
    OnClick = BtnCzyscBazeClick
  end
  object GbBazaDane: TGroupBox
    Left = 328
    Top = 8
    Width = 201
    Height = 89
    Caption = 'Dane w bazie'
    TabOrder = 3
    object Label1: TLabel
      Left = 16
      Top = 24
      Width = 80
      Height = 13
      Caption = 'Ilo'#347#263' produkt'#243'w:'
    end
    object Label2: TLabel
      Left = 16
      Top = 43
      Width = 51
      Height = 13
      Caption = 'Ilo'#347#263' opini:'
    end
    object LblIlProduktow: TLabel
      Left = 120
      Top = 24
      Width = 70
      Height = 13
      Caption = 'LblIlProduktow'
    end
    object LblIlOpini: TLabel
      Left = 120
      Top = 43
      Width = 31
      Height = 13
      Caption = 'Label3'
    end
  end
  object MDane: TMemo
    Left = 136
    Top = 112
    Width = 393
    Height = 217
    TabOrder = 4
  end
  object BtnDane: TButton
    Left = 8
    Top = 269
    Width = 89
    Height = 41
    Caption = 'Przegl'#261'daj dane'
    TabOrder = 5
    OnClick = BtnDaneClick
  end
  object Button2: TButton
    Left = 456
    Top = 335
    Width = 25
    Height = 13
    Caption = 'Button2'
    TabOrder = 6
    Visible = False
    OnClick = Button2Click
  end
  object BtnE: TButton
    Left = 8
    Top = 80
    Width = 83
    Height = 25
    Caption = 'E'
    TabOrder = 7
    OnClick = BtnEClick
  end
  object BtnT: TButton
    Left = 8
    Top = 120
    Width = 83
    Height = 25
    Caption = 'T'
    TabOrder = 8
    OnClick = BtnTClick
  end
  object BtnL: TButton
    Left = 8
    Top = 159
    Width = 83
    Height = 25
    Caption = 'L'
    TabOrder = 9
    OnClick = BtnLClick
  end
  object BtnInfo: TButton
    Left = 487
    Top = 335
    Width = 49
    Height = 17
    Caption = 'Info'
    TabOrder = 10
    OnClick = BtnInfoClick
  end
end
