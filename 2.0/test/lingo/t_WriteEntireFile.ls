on Test_PRegEx_WriteEntireFile
  set oldDebugSetting = PRegEx_ErrorsToMessageWindow()
  PRegEx_ErrorsToMessageWindow(0)
  
  -- See Test_PRegEx_ReadEntireFile for some round-trip reading/writing tests.
  set myFile = re_read2("@:testdata:test_256v1.txt", "MACROMANFULL")
  
  -- Test writing with various length restrictions.
  myFile[2] = 200 -- this limit should now be ignored in PRegEx 2.0
  if (re_write2("@:testdata:output:test_256v1.200chars.txt", myFile, "MACROMANFULL") <> 256) then Blech("Test_PRegEx_WriteEntireFile 201")
  
  myFile[2] = 400 -- more chars than actually in file: should be 256
  if (re_write2("@:testdata:output:test_256v1.400chars.txt", myFile, "MACROMANFULL") <> 256) then Blech("Test_PRegEx_WriteEntireFile 202")
  
  myFile[2] = 0 -- this limit should now be ignored in PRegEx 2.0
  if (re_write2("@:testdata:output:test_256v1.0chars.txt"  , myFile, "MACROMANFULL") <> 256) then Blech("Test_PRegEx_WriteEntireFile 203")
  
  myFile[2] = 10 -- this limit should now be ignored in PRegEx 2.0
  if (re_write2("@:testdata:output:test_256v1.10chars.txt" , myFile, "MACROMANFULL") <> 256) then Blech("Test_PRegEx_WriteEntireFile 204")
  
  if the machineType = 256 then    
    myFile[2] = 10 -- empty file name test -- MOA gives different error on Win vs. Mac
    if (re_write2("@:testdata:output:"                       , myFile, "MACROMANFULL") <> PRegEx_ErrCode_ErrorWritingFile()) then Blech("Test_PRegEx_WriteEntireFile 204a")
    
  else
    myFile[2] = 10 -- empty file name test
    if (re_write2("@:testdata:output:"                       , myFile, "MACROMANFULL") <> PRegEx_ErrCode_ErrorOpeningFile()) then Blech("Test_PRegEx_WriteEntireFile 204a")
  end if
  
  myFile[2] = 10
  if (re_write2("@:BOGUSDIRECTORY:test_256v1.10chars.html" , myFile, "MACROMANFULL") <> PRegEx_ErrCode_DirNotFound()) then Blech("Test_PRegEx_WriteEntireFile 204b")
  
  -- leak test
  if (LeakTestingSelected()) then
    set fBytes = void
    repeat with iterNum = 1 to 50
      if (re_write2("@:testdata:output:test_toronto.200chars.html", myFile, "MACROMANFULL") <> 256) then Blech("Test_PRegEx_WriteEntireFile 205")
      
      if iterNum mod 3 = 0 then -- measure memory after 1/8th of the iterations
        if fBytes = void then set fBytes = the freeBytes
        -- put iterNum && the freeBytes -- remember: uncommenting this uses up memory in the Message window's buffer!
      end if
    end repeat
    -- Measure memory again after all 100% of iterations have happened.  There should be no change.
    if abs(fBytes - the freeBytes)>100 then Blech "Test_PRegEx_WriteEntireFile Leak" && (the freeBytes - fBytes)
  end if
  
  PRegEx_ErrorsToMessageWindow(oldDebugSetting)
end Test_PRegEx_WriteEntireFile
