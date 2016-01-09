object DMBaza: TDMBaza
  OldCreateOrder = False
  Height = 333
  Width = 533
  object ACPolaczenie: TADOConnection
    Connected = True
    ConnectionString = 
      'Provider=MSDASQL.1;Password=qazxsw123;Persist Security Info=True' +
      ';User ID=postgres;Data Source=Opinie'
    LoginPrompt = False
    Left = 48
    Top = 48
  end
  object Query: TADOQuery
    Connection = ACPolaczenie
    CursorType = ctStatic
    Parameters = <>
    Left = 48
    Top = 104
  end
end
