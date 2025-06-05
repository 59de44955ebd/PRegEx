on Test_PRegEx_SearchBegin
  -- Always implicitly "global" whether or not "g" option is used.
  
  PRegEx_SearchBegin(["Hi ch Chh"], "ch+",        "ig"         )
  set totalRuns = 0
  repeat while (PRegEx_SearchContinue()>0)
    if PRegEx_FoundCount() = 1 and PRegEx_GetMatchString(0) <> "ch"  then Blech "PRegEx_SearchBegin 101" && PRegEx_CompiledOK()
    if PRegEx_FoundCount() = 2 and PRegEx_GetMatchString(0) <> "Chh" then Blech "PRegEx_SearchBegin 102" && PRegEx_CompiledOK()
    set totalRuns = totalRuns + 1
  end repeat
  if totalRuns <> 2 or PRegEx_FoundCount() <> 2                                           then Blech "PRegEx_SearchBegin 103" && PRegEx_CompiledOK()
  
  PRegEx_SearchBegin(["Hi ch Chh"], "ch+",        "i"         )
  set totalRuns = 0
  repeat while (PRegEx_SearchContinue()>0)
    if PRegEx_FoundCount() = 1 and PRegEx_GetMatchString(0) <> "ch"  then Blech "PRegEx_SearchBegin 201" && PRegEx_CompiledOK()
    if PRegEx_FoundCount() = 2 and PRegEx_GetMatchString(0) <> "Chh" then Blech "PRegEx_SearchBegin 202" && PRegEx_CompiledOK()
    set totalRuns = totalRuns + 1
  end repeat
  if totalRuns <> 2 or PRegEx_FoundCount() <> 2                                           then Blech "PRegEx_SearchBegin 203" && PRegEx_CompiledOK()
  
  -- Ensure it continues to return false.
  if PRegEx_SearchContinue() <> false                                                                 then Blech "PRegEx_SearchBegin 301" && PRegEx_CompiledOK()
  if PRegEx_SearchContinue() <> false                                                                 then Blech "PRegEx_SearchBegin 302" && PRegEx_CompiledOK()
  
  -- Ensure found count remains stable.
  if totalRuns <> 2 or PRegEx_FoundCount() <> 2                                           then Blech "PRegEx_SearchBegin 303" && PRegEx_CompiledOK()
  
  -- leak test
  if (LeakTestingSelected()) then
    set fBytes = void
    repeat with iterNum = 1 to 10000
      
      PRegEx_SearchBegin(["Hi ch Chh"], "ch+",        "ig"         )
      set totalRuns = 0
      repeat while (PRegEx_SearchContinue()>0)
        if PRegEx_FoundCount() = 1 and PRegEx_GetMatchString(0) <> "ch"  then Blech "PRegEx_SearchBegin 401" && PRegEx_CompiledOK()
        if PRegEx_FoundCount() = 2 and PRegEx_GetMatchString(0) <> "Chh" then Blech "PRegEx_SearchBegin 402" && PRegEx_CompiledOK()
        set totalRuns = totalRuns + 1
      end repeat
      if totalRuns <> 2 or PRegEx_FoundCount() <> 2                                           then Blech "PRegEx_SearchBegin 403" && PRegEx_CompiledOK()
      
      if iterNum mod 200 = 0 then -- measure memory after 1/50th of the iterations
        if fBytes = void then set fBytes = the freeBytes
        -- put the freeBytes -- remember: uncommenting this uses up memory in the Message window's buffer!
      end if
    end repeat
    -- Measure memory again after all 100% of iterations have happened.  There should be no change.
    if abs(fBytes - the freeBytes)>100 then Blech "PRegEx_SearchBegin Leak" && (the freeBytes - fBytes)
  end if
  
end Test_PRegEx_SearchBegin
