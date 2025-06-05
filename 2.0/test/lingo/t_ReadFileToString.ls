on  r2stest n, inPath, textFormat, expectedCharLength, expectNulls  
  set myFile = PRegEx_ReadFileToString(inPath, textFormat)
  if (not listP(myFile)) then Blech("Test_PRegEx_ReadFileToString" && inPath && n & "01")
  if (PRegEx_LastErrCode() <> 0) then Blech("Test_PRegEx_ReadFileToString" && inPath && n & "02")
  if (myFile[2] <> expectedCharLength) then Blech("Test_PRegEx_ReadFileToString"  && inPath && n & "03")
  if (myFile[2] <> myFile[1].length) then Blech("Test_PRegEx_ReadFileToString" && inPath && n & "04")
  if (myFile[3] <> expectNulls) then Blech("Test_PRegEx_ReadFileToString" && inPath && n & "05")
  return myFile[1]
end r2stest

on Test_PRegEx_ReadFileToString
  set oldDebugSetting = PRegEx_ErrorsToMessageWindow()
  PRegEx_ErrorsToMessageWindow(0)
  
  set myFile = PRegEx_ReadFileToString("@:testdata:test_toronto.html", "MACROMAN")
  if (not listP(myFile)) then Blech("Test_PRegEx_ReadFileToString 101")
  if (PRegEx_LastErrCode() <> 0) then Blech("Test_PRegEx_ReadFileToString 102")
  if (myFile[2] <> 23955) then Blech("Test_PRegEx_ReadFileToString 103")
  if (myFile[3] <> 0) then Blech("Test_PRegEx_ReadFileToString 104")
  if (PRegEx_Search(myFile, "<", "g") <> 617) then Blech("Test_PRegEx_ReadFileToString 105a")
  
  -- test full 8 bit text
  r2stest(2, "@:testdata:test_256v1.txt", "MACROMANFULL", 256, 1)
  r2stest(3, "@:testdata:test_256v2.txt", "MACROMANFULL", 256, 1)
  r2stest(4, "@:testdata:test_256v1.txt", "CP1252FULL",   256, 1)
  r2stest(5, "@:testdata:test_256v2.txt", "CP1252FULL",   256, 1)
  
  -- test a-z in various formats
  a1 = r2stest(6, "@:testdata:test_abc_utf32.txt" , "UTF-32", 27, 0 )
  a2 = r2stest(7, "@:testdata:test_abc_utf16.txt",  "UTF-16", 27, 0)
  a3 = r2stest(8, "@:testdata:test_abc_ascii.txt",  "ASCII",  27, 0 )
  if (a1 <> a2) then Blech("Test_PRegEx_ReadFileToString 901")
  if (a2 <> a3) then Blech("Test_PRegEx_ReadFileToString 902")
  if (a3 <> a1) then Blech("Test_PRegEx_ReadFileToString 903")
  
  -- test char in arabic, chinese, russian, japanese and korean
  b1 = r2stest(10, "@:testdata:test_more_utf8.txt",  "UTF-8",  147, 0)
  b2 = r2stest(11, "@:testdata:test_more_utf16.txt", "UTF-16", 147, 0)
  b3 = r2stest(12, "@:testdata:test_more_utf32.txt", "UTF-32", 147, 0)
  if (b1 <> b2) then Blech("Test_PRegEx_ReadFileToString 1301")
  if (b2 <> b3) then Blech("Test_PRegEx_ReadFileToString 1302")
  if (b3 <> b1) then Blech("Test_PRegEx_ReadFileToString 1303")

  -- test raw mode
  -- test_more_utf8.txt = 147 chars = 209 bytes
  r1 = PRegEx_ReadFileToString("@:testdata:test_more_utf8.txt",  "raw")
  if (r1[2] <> 209) then Blech("Test_PRegEx_ReadFileToString 1401")

  set myFile = PRegEx_ReadFileToString("@:testdata:test_toronto.html.bogus", "MACROMAN")
  if (listP(myFile)) then Blech("Test_PRegEx_ReadFileToString 2001")
  if (myFile <> PRegEx_ErrCode_FileNotFound()) then Blech("Test_PRegEx_ReadFileToString 2002")
  
  PRegEx_ErrorsToMessageWindow(oldDebugSetting)
end Test_PRegEx_ReadFileToString

