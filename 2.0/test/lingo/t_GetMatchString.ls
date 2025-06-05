on Test_PRegEx_GetMatchString
  
  if (PRegEx_SetSearchString(["bîg"]                  ) <> true) then Blech "Test_PRegEx_GetMatchString 100b" && PRegEx_MemError()
  if (PRegEx_SetSearchString(["big"]                  ) <> true) then Blech "Test_PRegEx_GetMatchString 100a" && PRegEx_MemError()
  
  -- leak test
  if (LeakTestingSelected()) then
    set fBytes = void
    repeat with iterNum = 1 to 10000
      if (PRegEx_SetMatchPattern("(b(i(g)))", "i"     ) <> true) then Blech "Test_PRegEx_GetMatchString 101" && PRegEx_MemError()
      if (PRegEx_GetNextMatch()        <> true                 ) then Blech "Test_PRegEx_GetMatchString 102" && PRegEx_MemError()
      if (re_get(0) <> "big"                                   ) then Blech "Test_PRegEx_GetMatchString 103" && PRegEx_GetMatchString(0)
      if (PRegEx_GetMatchString(0) <> "big"                    ) then Blech "Test_PRegEx_GetMatchString 103" && PRegEx_GetMatchString(0)
      
      if iterNum mod 200 = 0 then
        if fBytes = void then set fBytes = the freeBytes
      end if
    end repeat
    if abs(fBytes - the freeBytes)>100 then Blech "PRegEx_ReplaceString Leak" && (the freeBytes - fBytes)
  end if
  
end Test_PRegEx_GetMatchString