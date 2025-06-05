on Test_PRegEx_ErrorCodes
  
  if(PRegEx_ErrCode_OutOfMemory()<>                               -1)  then Blech("Test_PRegEx_ErrorCodes 1")
  
  -- leak test
  if (LeakTestingSelected()) then
    set fBytes = void
    repeat with iterNum = 1 to 10000
      if not(PRegEx_DescribeError(PRegEx_ErrCode_OutOfMemory()) contains("!")) then Blech "Test_PRegEx_ErrorCodes 101" && PRegEx_CompiledOK()
      if (PRegEx_ErrorsToMessageWindow(1) <> 1) then Blech "Test_PRegEx_ErrorCodes 102" && PRegEx_CompiledOK()
      if (PRegEx_ErrorsToMessageWindow(0) <> 0) then Blech "Test_PRegEx_ErrorCodes 103" && PRegEx_CompiledOK()
      if iterNum mod 200 = 0 then -- measure memory after 1/50th of the iterations
        if fBytes = void then set fBytes = the freeBytes
        -- put the freeBytes -- remember: uncommenting this uses up memory in the Message window's buffer!
      end if
    end repeat
    -- Measure memory again after all 100% of iterations have happened.  There should be no change.
    if abs(fBytes - the freeBytes)>100 then Blech "PRegEx_Search Leak" && (the freeBytes - fBytes)
  end if
  
end Test_PRegEx_ErrorCodes