#include <Array.au3>
#include <String.au3>
#include <WinAPIShPath.au3>
#include <WinAPI.au3>

Local $CmdLine = _WinAPI_CommandLineToArgv($CmdLineRaw)
local $KodProduktu = $CmdLine[1];35379075
;local $KodProduktu = 35379075

local $AnalizowanyPlik = 1
local $czyStop = False

; --------------------------------------------------------------------------------------------

local $ZnacznikDaneProduktuStart = 'window["dataLayer"]'
local $ZnacznikDaneProduktuKoniec = '</script>'

local $ZnacznikDaneProduktu2Start = 'keys : ['
local $ZnacznikDaneProduktu2Koniec = '"]'

local $ZnacznikLinkMorele =  'data-shop="379"'
local $ZnacznikLinkMoreleKoniec = 'alt="morele.net"'

local $ZnacznikPoczatekOp = '<li class="product-review js_product-review">'
local $ZnacznikKoniecOp = '<div class="review-icons">'
local $ZnacznikStart = '<START>'
local $ZnacznikEnd = '<KONIEC>'
local $jestBlad = False

; --------------------------------------------------------------------------------------------

Local $arr[1] ; zawiera wyciête opinie z danej strony
Local $liczbaOpini = 0
Local $DaneProduktu1
Local $Opinie

local $adres = "http://www.ceneo.pl/" & $KodProduktu & "/opinie-"
$oHTTP = ObjCreate("winhttp.winhttprequest.5.1")


While $czyStop <> True
   $oHTTP.Open("GET", $adres & String($AnalizowanyPlik), False)
   $oHTTP.Send()
   $oReceived = $oHTTP.ResponseText
   $oStatusCode = $oHTTP.Status

   $czyBlad = "";
   $czyBlad = _StringBetween($oReceived, '<abbr title="B³¹d 404">', '</abbr>')

   ;If $czyBlad[0] == '//404' Then
   If UBound($czyBlad) > 0 Then

	  ConsoleWrite($czyBlad)
	  $czyStop = True
	  $jestBlad = True
	  ExitLoop
   EndIf

   If $oStatusCode == 200 then
	  ReDim $arr[UBound($arr) + 1]
	  $array = _StringBetween($oReceived, $ZnacznikPoczatekOp, $ZnacznikKoniecOp)   ; wektor pojedynczych opini

	  For $i = 0 To UBound($array) - 1
		 $array[$i] = @CRLF & $ZnacznikStart & @CRLF & $array[$i] & $ZnacznikEnd
		 $arr[$AnalizowanyPlik] = $arr[$AnalizowanyPlik] & $array[$i]
	  Next

	  If $AnalizowanyPlik >= 2 Then
		 If $arr[$AnalizowanyPlik - 1] == $arr[$AnalizowanyPlik] Then
			$czyStop = True
		 EndIf
	  EndIf

	  If $czyStop <> True Then
		 If $AnalizowanyPlik == 1 Then
			$DaneProduktu1 = _StringBetween($oReceived, $ZnacznikDaneProduktuStart, $ZnacznikDaneProduktuKoniec)
			$DaneProduktu2 = _StringBetween($oReceived, $ZnacznikDaneProduktu2Start, $ZnacznikDaneProduktu2Koniec)
			$DaneProduktuLinkMorele = _StringBetween($oReceived, $ZnacznikLinkMorele, $ZnacznikLinkMoreleKoniec)
			if $DaneProduktuLinkMorele <> 0 Then
			   $DaneProduktuLinkMorele = _StringBetween($DaneProduktuLinkMorele[0], "href='", "'")
			EndIf
		 EndIf
		 $liczbaOpini = $liczbaOpini + UBound($array)
		 $Opinie = $Opinie & @CRLF & $arr[$AnalizowanyPlik]
		 ConsoleWrite($AnalizowanyPlik & @CRLF)
	  EndIf
   EndIf
   $AnalizowanyPlik = $AnalizowanyPlik + 1
WEnd

If $jestBlad <> True Then
   if $DaneProduktuLinkMorele <> 0 Then
	  $Morele = $DaneProduktuLinkMorele[0]
   Else
	  $Morele = 0;
   EndIf

   $Opinie = $DaneProduktu1[0] & @CRLF & 'keys : [' & $DaneProduktu2[0] & '"]' & @CRLF & '<MORELE>' & $Morele & '</MORELE>' & @CRLF & $Opinie
   $Opinie = $Opinie & @CRLF & '<OPINI:>' & $liczbaOpini & '</OPN>'
EndIf


$file = FileOpen("Opinie" & ".txt", 2) ; 2 nadpisanie danych


If $jestBlad == True Then
   $Opinie = ""
EndIf

FileWrite($file, $Opinie)
FileClose($file)

ConsoleWrite('Opini:  ' & String($liczbaOpini) & @CRLF)

;MsgBox(0, "UWAGA!", "Zakoñczono ekstrakcje, liczba opini: " & $liczbaOpini)