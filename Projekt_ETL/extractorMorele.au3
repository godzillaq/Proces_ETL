#include <Array.au3>
#include <String.au3>
#include <WinAPIShPath.au3>
#include <WinAPI.au3>

Local $CmdLine = _WinAPI_CommandLineToArgv($CmdLineRaw)
local $KodProduktu = $CmdLine[1]
;local $KodProduktu = "/Click/Offer/?e=DEaz-Fy8BkJo4kUUuzcMCJQ1E8PXX9fqYJIMOBirmygrqcMfUomfMk19WYEW_4VMHoRYPb2lypxfnFXDuP5nJ6UUZS7vMTnlLUbS2KCJLBG_AhOlU5MaC4zKhwJC6Pgeo8eJB_UXT2EZIG3M-B6huBzRZ4htRZlZjsvWWUEUaw9jp11vS4UfbemeOhaqa1TQ3wJoKIBCx0hbmISgUv4jL0Wk0WAKReLmit-e1wzcGoulUEzCWQUN3eavcoNGqqi4_8XlaH9_qSOlUEzCWQUN3aVQTMJZBQ3dP8fhmNswdm0%3d"

$ZnakPoczatek = '<ul class="left-comment review">'
$ZnakKoniec = "<hr/>"

local $adres = "http://www.ceneo.pl" & $KodProduktu
$oHTTP = ObjCreate("winhttp.winhttprequest.5.1")

$oHTTP.Open("GET", $adres, False)
$oHTTP.Send()
$oReceived = $oHTTP.ResponseText
$oStatusCode = $oHTTP.Status

$KodProduktu = _StringBetween($oReceived, 'item: ', '}')

$adres = "http://www.morele.net/catalog/ajaxGetReviews/" & $KodProduktu[0]
$oHTTP = ObjCreate("winhttp.winhttprequest.5.1")
$oHTTP.Open("GET", $adres, False)
$oHTTP.Send()
$opinieMorele = $oHTTP.ResponseText
$oStatusCode = $oHTTP.Status

$array = _StringBetween($opinieMorele, $ZnakPoczatek, $ZnakKoniec)   ; wektor pojedynczych opini
$opinie = ""
For $i = 0 To UBound($array) - 1
   $opinie = $opinie & @CRLF & "<STARTMORELE>" & @CRLF & $array[$i] & "<KONIECMORELE>"
Next


$file = FileOpen("Opinie2" & ".txt", 2) ;
FileWrite($file, $opinie)
FileClose($file)
