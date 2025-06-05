on  w2ftest n, inPath, textFormat, expectedCharLength, expectNulls  

  set outPath = [inPath]
  re_s(outPath, "(.*?testdata:)(.*?)(\..*)", "", "\1output:\2.out.wstf\3")
  -- put outPath[1]
  
  set myFile = PRegEx_ReadFileToString(inPath, textFormat)
  if (not listP(myFile)) then Blech("Test_PRegEx_WriteStringToFile" && inPath && n & "01")
  if (PRegEx_LastErrCode() <> 0) then Blech("Test_PRegEx_WriteStringToFile" && inPath && n & "02")
  if (myFile[2] <> expectedCharLength) then Blech("Test_PRegEx_WriteStringToFile"  && inPath && n & "03")
  if (myFile[2] <> myFile[1].length) then Blech("Test_PRegEx_WriteStringToFile" && inPath && n & "04")
  if (myFile[3] <> expectNulls) then Blech("Test_PRegEx_WriteStringToFile" && inPath && n & "05")

  re_write2(outPath[1], myFile, textFormat)
  
  set myFileback = PRegEx_ReadFileToString(outPath[1], textFormat)
  if (not listP(myFileback)) then Blech("Test_PRegEx_WriteStringToFile" && inPath && n & "07")
  if (PRegEx_LastErrCode() <> 0) then Blech("Test_PRegEx_WriteStringToFile" && inPath && n & "08")
  if (myFileback[2] <> expectedCharLength) then Blech("Test_PRegEx_WriteStringToFile"  && inPath && n & "09")
  if (myFileback[2] <> myFile[2]) then Blech("Test_PRegEx_WriteStringToFile" && inPath && n & "10")
  if (myFileback[3] <> myFile[3]) then Blech("Test_PRegEx_WriteStringToFile" && inPath && n & "11")
  if (myFileback[1] <> myFile[1]) then Blech("Test_PRegEx_WriteStringToFile" && inPath && n & "12")

  return myFile
end w2ftest

on Test_PRegEx_WriteStringToFile
  set oldDebugSetting = PRegEx_ErrorsToMessageWindow()
  PRegEx_ErrorsToMessageWindow(0)
  
  set myFile = PRegEx_ReadFileToString("@:testdata:test_toronto.html", "MACROMAN")
  if (not listP(myFile)) then Blech("Test_PRegEx_WriteStringToFile 101")
  if (PRegEx_LastErrCode() <> 0) then Blech("Test_PRegEx_WriteStringToFile 102")
  if (myFile[2] <> 23955) then Blech("Test_PRegEx_WriteStringToFile 103")
  if (myFile[3] <> 0) then Blech("Test_PRegEx_WriteStringToFile 104")
  if (PRegEx_Search(myFile, "<", "g") <> 617) then Blech("Test_PRegEx_WriteStringToFile 105")
  
  if (PRegEx_WriteStringToFile("@:testdata:output:test_toronto.out.wstf.html", myFile, "MACROMAN") <> myFile[2]) then Blech("Test_PRegEx_WriteStringToFile 106")
  -- read in the new written file to verify
  set myFile2 = PRegEx_ReadFileToString("@:testdata:output:test_toronto.out.wstf.html", "MACROMAN")
  if (not listP(myFile2)) then Blech("Test_PRegEx_WriteStringToFile 107")
  if (PRegEx_LastErrCode() <> 0) then Blech("Test_PRegEx_WriteStringToFile 108")
  if (myFile2[1] <> myFile[1]) then Blech("Test_PRegEx_WriteStringToFile 109a")
  if (myFile2[2] <> myFile[2]) then Blech("Test_PRegEx_WriteStringToFile 109b")
  if (myFile2[3] <> myFile[3]) then Blech("Test_PRegEx_WriteStringToFile 119c")
  if (PRegEx_Search(myFile2, "<", "g") <> 617) then Blech("Test_PRegEx_WriteStringToFile 110")
  
  -- test partial writeouts
  myFile[2] = 200  -- this limit should now be ignored in PRegEx 2.0
  if (re_write2("@:testdata:output:test_toronto.out.wstf.200chars.html", myFile, "MACROMAN") <> 23955) then Blech("Test_PRegEx_WriteStringToFile 201")
  myFile[2] = 400  -- this limit should now be ignored in PRegEx 2.0
  if (PRegEx_WriteStringToFile("@:testdata:output:test_toronto.out.wstf.400chars.html", myFile, "MACROMAN")  <> 23955) then Blech("Test_PRegEx_WriteStringToFile 202")
  myFile[2] = 0  -- this limit should now be ignored in PRegEx 2.0
  if (PRegEx_WriteStringToFile("@:testdata:output:test_toronto.out.wstf.0char.html", myFile, "MACROMAN") <> 23955) then Blech("Test_PRegEx_WriteStringToFile 203")
  myFile[2] = 10  -- this limit should now be ignored in PRegEx 2.0
  if (re_write2("@:testdata:output:test_toronto.out.wstf.10chars.html", myFile, "MACROMAN") <> 23955) then Blech("Test_PRegEx_WriteStringToFile 204")
  
  
  -- test file system errors, mac/win MOA implementations differ
  
  -- empty filename test
  if (the machineType = 256) then --windows
    if (PRegEx_WriteStringToFile("@:testdata:output:", myFile2, "CP1252") <> PRegEx_ErrCode_ErrorWritingFile()) then 
      Blech("Test_PRegEx_WriteStringToFile 301")
    end if
  else  -- mac
    if (PRegEx_WriteStringToFile("@:testdata:output:", myFile2, "MACROMAN") <> PRegEx_ErrCode_ErrorOpeningFile()) then 
      Blech("Test_PRegEx_WriteStringToFile 301")
    end if
  end if 

  -- long filename test, 305 char filename, 
  if (PRegEx_WriteStringToFile("@:testdata:output:test_toronto.wstf.htmlx_TOOO_LONG_FILE_NAME________AVERYVERYVERYVERYVERYVERYVERYVERYVERYVERYVERYVERYVERYVERYVERYVERYVERYVERYVERYVERYVERYVERYVERYVERYVERYVERYVERYVERYVERYVERYVERYVERYVERYVERYVERYVERYVERYVERYVERYVERYVERYVERYVERYVERYVERYVERYVERYVERYVERYVERYVERYVERYVERYVERYVERYVERYVERYVERYVERYVERYLONGFILENAME", myFile2, "MACROMAN" ) <> PRegEx_ErrCode_ErrorOpeningFile()) then 
    Blech("Test_PRegEx_WriteStringToFile 302")
  end if
  
  if (PRegEx_WriteStringToFile("@:BOGUSDIRECTORY:test_toronto.wstf.html", myFile2, "MACROMAN") <> PRegEx_ErrCode_DirNotFound()) then Blech("Test_PRegEx_WriteStringToFile 303")
  
  -- test full 8 bit text
  bin1 = w2ftest(4, "@:testdata:test_256v1.txt", "MACROMANFULL", 256, 1)
  bin2 = w2ftest(5, "@:testdata:test_256v1.txt", "CP1252FULL",   256, 1)
  bin3 = w2ftest(6, "@:testdata:test_256v2.txt", "CP1252FULL",   256, 1)
  bin4 = w2ftest(7, "@:testdata:test_256v2.txt", "MACROMANFULL", 256, 1)
  -- test binary conversion 
  bin5 = PRegEx_ReadFileToString("@:testdata:output:test_256v1.out.wstf.txt", "MACROMANFULL")
  bin6 = PRegEx_ReadFileToString("@:testdata:output:test_256v2.out.wstf.txt", "CP1252FULL")
  if (bin1[1] <> bin5[1]) then Blech("Test_PRegEx_WriteStringToFile 701c")
  if (bin3[1] <> bin6[1]) then Blech("Test_PRegEx_WriteStringToFile 702c")

  -- test a-z in various formats
  a1 = w2ftest(8,  "@:testdata:test_abc_utf32.txt" , "UTF-32", 27, 0)
  a2 = w2ftest(9,  "@:testdata:test_abc_utf16.txt",  "UTF-16", 27, 0)
  a3 = w2ftest(10, "@:testdata:test_abc_ascii.txt",  "ASCII",  27, 0)
  
  if (a1[1] <> a2[1]) then Blech("Test_PRegEx_WriteStringToFile 1101")
  if (a2[1] <> a3[1]) then Blech("Test_PRegEx_WriteStringToFile 1102")
  if (a3[1] <> a1[1]) then Blech("Test_PRegEx_WriteStringToFile 1103")

  -- test format conversion for alphabet
  re_write2("@:testdata:output:test_abc_utf16.wstf.fromascii.txt", a3, "UTF-16")
  re_write2("@:testdata:output:test_abc_utf16.wstf.fromutf32.txt", a1, "UTF-16")
  r1 = PRegEx_ReadFileToString("@:testdata:output:test_abc_utf16.wstf.fromascii.txt", "UTF-16")
  r2 = PRegEx_ReadFileToString("@:testdata:output:test_abc_utf16.wstf.fromutf32.txt", "UTF-16")
  if (r1[1] <> r2[1]) then Blech("Test_PRegEx_WriteStringToFile 1104" )
  
--   
  -- test char in arabic, chinese, russian, japanese and korean
  b1 = w2ftest(12, "@:testdata:test_more_utf8.txt",  "UTF-8",  147, 0)
  b2 = w2ftest(13, "@:testdata:test_more_utf16.txt", "UTF-16", 147, 0)
  b3 = w2ftest(14, "@:testdata:test_more_utf32.txt", "UTF-32", 147, 0)
  if (b1[1] <> b2[1]) then Blech("Test_PRegEx_WriteStringToFile 1401")
  if (b2[1] <> b3[1]) then Blech("Test_PRegEx_WriteStringToFile 1402")
  if (b3[1] <> b1[1]) then Blech("Test_PRegEx_WriteStringToFile 1403")
  
  -- test format conversion for 8bit chars
  re_write2("@:testdata:output:test_more_utf16.wstf.fromutf8.txt",    b1, "UTF-16")
  re_write2("@:testdata:output:test_more_utf32.wstf.fromutf16.txt",   b2, "UTF-32")
  re_write2("@:testdata:output:test_more_utf8.wstf.fromutf32.txt",    b3, "UTF-8")
  m1 = PRegEx_ReadFileToString("@:testdata:output:test_more_utf16.wstf.fromutf8.txt",   "UTF-16")
  m2 = PRegEx_ReadFileToString("@:testdata:output:test_more_utf32.wstf.fromutf16.txt",  "UTF-32")
  m3 = PRegEx_ReadFileToString("@:testdata:output:test_more_utf8.wstf.fromutf32.txt",   "UTF-8")
  if (m1[1] <> m2[1]) then Blech("Test_PRegEx_WriteStringToFile 1501" )
  if (m2[1] <> m3[1]) then Blech("Test_PRegEx_WriteStringToFile 1502" )
  if (m3[1] <> m1[1]) then Blech("Test_PRegEx_WriteStringToFile 1503" )
--   
  -- test raw mode
  -- test_more_utf8.txt = 147 chars = 209 bytes
  r1 = PRegEx_ReadFileToString("@:testdata:test_more_utf8.txt",  "raw")
  if (PRegEx_WriteStringToFile("@:testdata:output:test_more_utf8.wstf.rawout.txt", r1, "raw") <> 209) then
    then Blech("Test_PRegEx_WriteStringToFile 1801" )
  end if
  r2 = PRegEx_ReadFileToString("@:testdata:output:test_more_utf8.wstf.rawout.txt",  "raw")
  if (r1[1] <> r2[1]) then Blech("Test_PRegEx_WriteStringToFile 1802" )

  r3 = PRegEx_ReadFileToString("@:testdata:output:test_more_utf8.wstf.rawout.txt",  "UTF-8")
  r4 = PRegEx_ReadFileToString("@:testdata:test_more_utf8.txt", "UTF-8")
  r5 = PRegEx_ReadFileToString("@:testdata:test_more_utf16.txt", "UTF-16")

  if (r3[1] <> r4[1]) then Blech("Test_PRegEx_WriteStringToFile 1803" )
  if (r3[1] <> r5[1]) then Blech("Test_PRegEx_WriteStringToFile 1804" )
  
  PRegEx_ErrorsToMessageWindow(oldDebugSetting)
end Test_PRegEx_WriteStringToFile






























