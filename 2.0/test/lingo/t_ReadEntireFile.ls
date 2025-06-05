on readwrite_compatibility_mode_roundtrip_test inPath, expectedCharLength, expectNulls
  set outPath = [inPath]
  re_s(outPath, "(.*?testdata:)(.*?)(\..*)", "", "\1output:\2.out.roundtrip\3")
  -- put outPath[1]
  
  set myFile = re_read2(inPath, "MACROMANFULL")
  if (not listP(myFile)) then Blech("readwrite_compatibility_mode_roundtrip_test" && inPath && "101")
  if (PRegEx_LastErrCode() <> 0) then Blech("readwrite_compatibility_mode_roundtrip_test" && inPath && "102")
  if (myFile[2] <> expectedCharLength) then Blech("readwrite_compatibility_mode_roundtrip_test" && inPath && "103")
  if (myFile[2] <> myFile[1].length) then Blech("readwrite_compatibility_mode_roundtrip_test" && inPath && "104")
  if (myFile[3] <> expectNulls) then Blech("readwrite_compatibility_mode_roundtrip_test" && inPath && "105")
  byteCount = re_write2(outPath[1], myFile, "MACROMANFULL")
  if (byteCount <> expectedCharLength) then Blech("readwrite_compatibility_mode_roundtrip_test" && inPath && "106" && byteCount)
  
end readwrite_compatibility_mode_roundtrip_test

on Test_PRegEx_ReadEntireFile
  oldDebugSetting = PRegEx_ErrorsToMessageWindow()
  PRegEx_ErrorsToMessageWindow(0)
  
  -- Take 4 files and make sure we can read/write them.
  readwrite_compatibility_mode_roundtrip_test("@:testdata:test_toronto.html", 23955, 0)
  readwrite_compatibility_mode_roundtrip_test("@:testdata:test_256v1.txt", 256, 1)
  readwrite_compatibility_mode_roundtrip_test("@:testdata:test_256v2.txt", 256, 1)
  readwrite_compatibility_mode_roundtrip_test("@:testdata:test_single_nbsp_macroman.txt", 1, 0)
  
  -- Read a file and test searching within it
  set myFile = re_read2("@:testdata:test_toronto.html", "MACROMANFULL")
  
  -- We expect 617 < characters in this file.
  if (PRegEx_Search(myFile, "<", "g") <> 617) then Blech("Test_PRegEx_ReadEntireFile 101")
  -- We expect 12 nbsp characters in this file (and we have 4 ways of expressing that code point)
  if (PRegEx_Search(myFile, " ", "g") <> 12) then Blech("Test_PRegEx_ReadEntireFile 102")
  if (PRegEx_Search(myFile, "\xA0", "g") <> 12) then Blech("Test_PRegEx_ReadEntireFile 102")
  if (PRegEx_Search(myFile, "\x{A0}", "g") <> 12) then Blech("Test_PRegEx_ReadEntireFile 102")
  if (PRegEx_Search(myFile, "\240", "g") <> 12) then Blech("Test_PRegEx_ReadEntireFile 102")
  
  -- Check for correct error message if file not found
  set myFile = PRegEx_ReadEntireFile("@:testdata:test_toronto.html.non-existant-file")
  if (listP(myFile)) then Blech("Test_PRegEx_ReadEntireFile 201")
  if (myFile <> PRegEx_ErrCode_FileNotFound()) then Blech("Test_PRegEx_ReadEntireFile 202")
  
  -- leak test
  if (LeakTestingSelected()) then
    set fBytes = void
    repeat with iterNum = 1 to 50
      readwrite_compatibility_mode_roundtrip_test("@:testdata:test_toronto.html", 23955, 0)
      
      if iterNum mod 3 = 0 then -- measure memory after 1/8th of the iterations
        if fBytes = void then set fBytes = the freeBytes
        --  put iterNum && the freeBytes -- remember: uncommenting this uses up memory in the Message window's buffer!
      end if
    end repeat
    -- Measure memory again after all 100% of iterations have happened.  There should be no change.
    if abs(fBytes - the freeBytes)>100 then Blech "Test_PRegEx_ReadEntireFile Leak" && (the freeBytes - fBytes)
  end if
  
  PRegEx_ErrorsToMessageWindow(oldDebugSetting)
end Test_PRegEx_ReadEntireFile