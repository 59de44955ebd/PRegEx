on Test_PRegEx_ReplaceString
  
  set aStringOrig =                        ["a big pig sat on" &                  "_" & "a priggish fig figgy figg fig"]
  --                                         0000000000111111                      1     111222222222233333333334444444
  --                                         0123456789012345                      6     789012345678901234567890123456
  --                                         ^^^^^                                       ^^^^^       ^^^^^^
  
  -- Suite #1: Shortening
  set aString =                                [aStringOrig[1]]
  if (PRegEx_SetSearchString(aString                           ) <> 1) then Blech "PRegEx_ReplaceString 01" && PRegEx_MemError()
  if (PRegEx_SetMatchPattern(" ([a-z]IG+) ", "i"   ) <> 1) then Blech "PRegEx_ReplaceString 02" && PRegEx_MemError()
  
  --Replacing without calling PRegEx_GetNextMatch should give error
  if (PRegEx_ReplaceString("XYZ"                                   ) <> PRegEx_ErrCode_TriedToReplaceWithoutMatching()) then Blech "PRegEx_ReplaceString 03" && PRegEx_MemError()
  if ((aString[1]) <> (aStringOrig[1])                                         ) then Blech "PRegEx_ReplaceString 04" && PRegEx_MemError()
  if (aString[1] <> "a big pig sat on_a priggish fig figgy figg fig") then Blech "PRegEx_ReplaceString 04c" && PRegEx_MemError()
  
  if (PRegEx_GetNextMatch()        <> true                                            ) then Blech "PRegEx_ReplaceString 05" && PRegEx_MemError()
  if (PRegEx_ReplaceString("XYZ"                                   ) <> true) then Blech "PRegEx_ReplaceString 06" && PRegEx_MemError()
  if (aString[1] <> "aXYZpig sat on_a priggish fig figgy figg fig") then Blech "PRegEx_ReplaceString 07" && PRegEx_MemError()
  
  if (PRegEx_GetNextMatch()        <> true                                            ) then Blech "PRegEx_ReplaceString 08" && PRegEx_MemError()
  if (PRegEx_ReplaceString("XYZ"                                   ) <> true) then Blech "PRegEx_ReplaceString 09" && PRegEx_MemError()
  if (aString[1] <> "aXYZpig sat on_a priggishXYZfiggy figg fig") then Blech "PRegEx_ReplaceString 10" && PRegEx_MemError()
  
  if (PRegEx_GetNextMatch()        <> true                                            ) then Blech "PRegEx_ReplaceString 11" && PRegEx_MemError()
  if (PRegEx_ReplaceString("XYZü"                                   ) <> true) then Blech "PRegEx_ReplaceString 12" && PRegEx_MemError()
  if (aString[1] <> "aXYZpig sat on_a priggishXYZfiggyXYZüfig") then Blech "PRegEx_ReplaceString 13" && PRegEx_MemError()
  
  
  -- Suite #2: Lengthening
  set aString =                                [aStringOrig[1]]
  if (PRegEx_SetSearchString(aString                           ) <> true) then Blech "PRegEx_ReplaceString 101" && PRegEx_MemError()
  if (PRegEx_SetMatchPattern(" ([a-z]IG+) ", "i"   ) <> true) then Blech "PRegEx_ReplaceString 102" && PRegEx_MemError()
  
  if (PRegEx_GetNextMatch()        <> true                                            ) then Blech "PRegEx_ReplaceString 105" && PRegEx_MemError()
  if (PRegEx_ReplaceString("_XYZZY_"                           ) <> true) then Blech "PRegEx_ReplaceString 106" && PRegEx_MemError()
  if (aString[1] <> "a_XYZZY_pig sat on_a priggish fig figgy figg fig") then Blech "PRegEx_ReplaceString 107" && PRegEx_MemError()
  
  if (PRegEx_GetNextMatch()        <> true                                            ) then Blech "PRegEx_ReplaceString 108" && PRegEx_MemError()
  if (PRegEx_ReplaceString("_XYZZY_"                           ) <> true) then Blech "PRegEx_ReplaceString 109" && PRegEx_MemError()
  if (aString[1] <> "a_XYZZY_pig sat on_a priggish_XYZZY_figgy figg fig") then Blech "PRegEx_ReplaceString 110" && PRegEx_MemError()
  
  if (PRegEx_GetNextMatch()        <> true                                            ) then Blech "PRegEx_ReplaceString 111" && PRegEx_MemError()
  if (PRegEx_ReplaceString("_XYZZY_"                           ) <> true) then Blech "PRegEx_ReplaceString 112" && PRegEx_MemError()
  if (aString[1] <> "a_XYZZY_pig sat on_a priggish_XYZZY_figgy_XYZZY_fig") then Blech "PRegEx_ReplaceString 113" && PRegEx_MemError()
  
  -- Suite #3: Checking back refs after replacement is done.
  set aString =                                [aStringOrig[1]]
  if (PRegEx_SetSearchString(aString                           ) <> true) then Blech "PRegEx_ReplaceString 201" && PRegEx_MemError()
  if (PRegEx_SetMatchPattern(" ([a-z]IG+) ", "i"   ) <> true) then Blech "PRegEx_ReplaceString 202" && PRegEx_MemError()
  
  if (PRegEx_GetNextMatch()        <> true                                            ) then Blech "PRegEx_ReplaceString 205" && PRegEx_MemError()
  if (PRegEx_ReplaceString("_XYZZY_"                           ) <> true) then Blech "PRegEx_ReplaceString 206" && PRegEx_MemError()
  if (aString[1] <> "a_XYZZY_pig sat on_a priggish fig figgy figg fig") then Blech "PRegEx_ReplaceString 207" && PRegEx_MemError()
  
  if (PRegEx_GetMatchString(0) <> " big "                                     ) then Blech "PRegEx_ReplaceString 207b" && PRegEx_GetMatchString(0)
  if (PRegEx_GetMatchString(1) <> "big"                                           ) then Blech "PRegEx_ReplaceString 207c" && PRegEx_GetMatchString(1)
  
  if (PRegEx_GetNextMatch()        <> true                                            ) then Blech "PRegEx_ReplaceString 208" && PRegEx_MemError()
  if (PRegEx_ReplaceString("_XYZZY_"                           ) <> true) then Blech "PRegEx_ReplaceString 209" && PRegEx_MemError()
  if (aString[1] <> "a_XYZZY_pig sat on_a priggish_XYZZY_figgy figg fig") then Blech "PRegEx_ReplaceString 210" && PRegEx_MemError()
  
  if (PRegEx_GetMatchString(0) <> " fig "                                     ) then Blech "PRegEx_ReplaceString 207b" && PRegEx_GetMatchString(0)
  if (PRegEx_GetMatchString(1) <> "fig"                                           ) then Blech "PRegEx_ReplaceString 207c" && PRegEx_GetMatchString(1)
  
  if (PRegEx_GetNextMatch()        <> true                                            ) then Blech "PRegEx_ReplaceString 211" && PRegEx_MemError()
  if (PRegEx_ReplaceString("_XYZZY_"                           ) <> true) then Blech "PRegEx_ReplaceString 212" && PRegEx_MemError()
  if (aString[1] <> "a_XYZZY_pig sat on_a priggish_XYZZY_figgy_XYZZY_fig") then Blech "PRegEx_ReplaceString 213" && PRegEx_MemError()
  
  if (PRegEx_GetMatchString(0) <> " figg "                                 ) then Blech "PRegEx_ReplaceString 207b" && PRegEx_GetMatchString(0)
  if (PRegEx_GetMatchString(1) <> "figg"                                      ) then Blech "PRegEx_ReplaceString 207c" && PRegEx_GetMatchString(1)
  
  -- Calling Replace after a replace has already been done; should give error.
  if (PRegEx_ReplaceString("_XYZZY_"                           ) <> PRegEx_ErrCode_TriedToReplaceWithoutMatching()) then Blech "PRegEx_ReplaceString 301" && PRegEx_MemError()
  if (aString[1] <> "a_XYZZY_pig sat on_a priggish_XYZZY_figgy_XYZZY_fig") then Blech "PRegEx_ReplaceString 302" && PRegEx_MemError()
  
  -- leak test
  
  if (LeakTestingSelected()) then
    set aString =                                [aStringOrig[1]]
    if (PRegEx_SetSearchString(aString                           ) <> true) then Blech "PRegEx_ReplaceString 401" && PRegEx_MemError()
    
    set fBytes = void
    repeat with iterNum = 1 to 10000
      if (PRegEx_SetMatchPattern("(p(i(g)))", "i"                      ) <> true) then Blech "PRegEx_ReplaceString 402" && PRegEx_MemError()
      if (PRegEx_GetNextMatch()        <> true                                            ) then Blech "PRegEx_ReplaceString 403" && PRegEx_MemError()
      if (PRegEx_ReplaceString("PIGPIG"                                ) <> true) then Blech "PRegEx_ReplaceString 404" && PRegEx_MemError()
      if (aString[1] <> "a big PIGPIG sat on_a priggish fig figgy figg fig") then Blech "PRegEx_ReplaceString 405" && PRegEx_MemError()
      
      if (PRegEx_SetMatchPattern("((pig)(pig))", "i"               ) <> true) then Blech "PRegEx_ReplaceString 406" && PRegEx_MemError()
      if (PRegEx_GetNextMatch()        <> true                                            ) then Blech "PRegEx_ReplaceString 407" && PRegEx_MemError()
      if (PRegEx_ReplaceString("PIG"                                   ) <> true) then Blech "PRegEx_ReplaceString 408" && PRegEx_MemError()
      if (aString[1] <> "a big PIG sat on_a priggish fig figgy figg fig") then Blech "PRegEx_ReplaceString 409" && PRegEx_MemError()
      
      if iterNum mod 200 = 0 then
        if fBytes = void then set fBytes = the freeBytes
      end if
    end repeat
    if abs(fBytes - the freeBytes)>100 then Blech "PRegEx_ReplaceString Leak" && (the freeBytes - fBytes)
  end if
  
end Test_PRegEx_ReplaceString
