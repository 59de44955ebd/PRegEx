on Test_PRegEx_SetSearchString
  if (PRegEx_SetSearchString([]) <> PRegEx_ErrCode_SearchStrLMustContainString()) then Blech "PRegEx_SetSearchString 1" && PRegEx_MemError()
  if (PRegEx_SetSearchString([1]) <> PRegEx_ErrCode_SearchStrLMustContainString()) then Blech "PRegEx_SetSearchString 2" && PRegEx_MemError()
  if (PRegEx_SetSearchString([1.0]) <> PRegEx_ErrCode_SearchStrLMustContainString()) then Blech "PRegEx_SetSearchString 3" && PRegEx_MemError()
  if (PRegEx_SetSearchString([#a]) <> PRegEx_ErrCode_SearchStrLMustContainString()) then Blech "PRegEx_SetSearchString 4" && PRegEx_MemError()
  if (PRegEx_SetSearchString([void]) <> PRegEx_ErrCode_SearchStrLMustContainString()) then Blech "PRegEx_SetSearchString 5" && PRegEx_MemError()
  if (PRegEx_SetSearchString([[]]) <> PRegEx_ErrCode_SearchStrLMustContainString()) then Blech "PRegEx_SetSearchString 6" && PRegEx_MemError()
  --if (PRegEx_SetSearchString([[:]]) <> false) then Blech "PRegEx_SetSearchString 7" && PRegEx_MemError() -- Lingo bug
  if (PRegEx_SetSearchString([:]) <> PRegEx_ErrCode_SearchStrLMustBeList()) then Blech "PRegEx_SetSearchString 8" && PRegEx_MemError()
  if (PRegEx_SetSearchString(["foo":1]) <> PRegEx_ErrCode_SearchStrLMustBeList()) then Blech "PRegEx_SetSearchString 9" && PRegEx_MemError()
  if (PRegEx_SetSearchString(["foo":"bar"]) <> PRegEx_ErrCode_SearchStrLMustBeList()) then Blech "PRegEx_SetSearchString 9b" && PRegEx_MemError()
  
  if (PRegEx_SetSearchString(["foo"]) <> true) then Blech "PRegEx_SetSearchString 10" && PRegEx_MemError()
  if (PRegEx_SetSearchString(["föo", 0]) <> true) then Blech "PRegEx_SetSearchString 11" && PRegEx_MemError()
  
  -- leak test
  if (LeakTestingSelected()) then
    set fBytes = void
    repeat with iterNum = 1 to 10000
      if (PRegEx_SetSearchString(["Supercalifragilisticexpialidocious"]) <> true) then Blech "PRegEx_SetSearchString 12" && PRegEx_MemError()
      
      if iterNum mod 200 = 0 then
        if fBytes = void then set fBytes = the freeBytes
      end if
    end repeat
    if abs(fBytes - the freeBytes)>100 then Blech "PRegEx_SetSearchString Leak 1" && (the freeBytes - fBytes)
  end if
  
  -- leak test
  if (LeakTestingSelected()) then
    set fBytes = void
    repeat with iterNum = 1 to 10000
      set a = ["Supercalifragilisticexpialidocious"]
      if (PRegEx_SetSearchString(a) <> true) then Blech "PRegEx_SetSearchString 12" && PRegEx_MemError()
      set a = void
      
      if iterNum mod 200 = 0 then
        if fBytes = void then set fBytes = the freeBytes
      end if
    end repeat
    if abs(fBytes - the freeBytes)>100 then Blech "PRegEx_SetSearchString Leak 2" && (the freeBytes - fBytes)
  end if
  
end Test_PRegEx_SetSearchString