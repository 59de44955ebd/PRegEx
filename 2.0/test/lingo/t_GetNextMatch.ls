on Test_PRegEx_GetNextMatch
  
  PRegEx_Clear()
  if PRegEx_GetNextMatch() <> PRegEx_ErrCode_TriedToMatchWithoutSearchStrL() then Blech "PRegEx_GetNextMatch 001" && PRegEx_MemError()
  PRegEx_SetSearchString(["foo"])
  if PRegEx_GetNextMatch() <> PRegEx_ErrCode_TriedToMatchWithoutSearchPattern() then Blech "PRegEx_GetNextMatch 002" && PRegEx_MemError()
  
  -- Tests of GetMatchString and GetMatchLen (including Unicode characters)
  
  re_m(["doggy dug döggy dug"], "(\S+) (\S+)", "") -- match first pair of words
  
  if (pregex_getmatchstring() <> "doggy dug") then Blech "Pregex_GetMatchString 301"
  if (pregex_getmatchstring(1) <> "doggy") then Blech "Pregex_GetMatchString 302"
  if (pregex_getmatchstring(2) <> "dug") then Blech "Pregex_GetMatchString 303"
  
  if (pregex_getmatchlen() <> 9) then Blech "Pregex_GetMatchLen 304"
  if (pregex_getmatchlen(1) <> 5) then Blech "Pregex_GetMatchLen 305"
  if (pregex_getmatchlen(2) <> 3) then Blech "Pregex_GetMatchLen 306"
  
  re_m(["doggy dug döggy dug"], "(\S+) (\S+)", "g") -- match second pair of words
  
  if (pregex_getmatchstring() <> "döggy dug") then Blech "Pregex_GetMatchString 401"
  if (pregex_getmatchstring(1) <> "döggy") then Blech "Pregex_GetMatchString 402"
  if (pregex_getmatchstring(2) <> "dug") then Blech "Pregex_GetMatchString 403"
  
  if (pregex_getmatchlen() <> 9) then Blech "Pregex_GetMatchLen 404"
  if (pregex_getmatchlen(1) <> 5) then Blech "Pregex_GetMatchLen 405"
  if (pregex_getmatchlen(2) <> 3) then Blech "Pregex_GetMatchLen 406"
  
  -- SUITE #1: Multiple matches in a regular string.
  
  if      (PRegEx_SetSearchString(["a big pig sat on" &                    "_" & "a priggish fig figgy figg fig"]) <> true) then Blech "PRegEx_GetNextMatch 1" && PRegEx_CompiledOK()
  --                                                       0000000000111111                            1       111222222222233333333334444444
  --                                                       0123456789012345                            6       789012345678901234567890123456
  --                                                          ^^^^^                                                                                ^^^^^       ^^^^^^
  
  if (PRegEx_SetMatchPattern(" ([a-z]ig+) ", "i"          ) <> true) then Blech "PRegEx_GetNextMatch 2" && PRegEx_MemError()
  
  -- Match #1
  if (PRegEx_GetNextMatch()        <> true            ) then Blech "PRegEx_GetNextMatch 10" && PRegEx_MemError()
  
  if (re_get                          ()  <> " big "   ) then Blech "PRegEx_GetNextMatch 11" && PRegEx_GetMatchString()
  if (PRegEx_GetMatchString()  <> " big "     ) then Blech "PRegEx_GetNextMatch 11" && PRegEx_GetMatchString()
  if (PRegEx_GetMatchString(0) <> " big "     ) then Blech "PRegEx_GetNextMatch 12" && PRegEx_GetMatchString(0)
  if (PRegEx_GetMatchString(1) <> "big"           ) then Blech "PRegEx_GetNextMatch 13" && PRegEx_GetMatchString(1)
  if (PRegEx_GetMatchString(2) <> void            ) then Blech "PRegEx_GetNextMatch 13b" && PRegEx_GetMatchString(2)
  
  if (PRegEx_GetMatchStart()  <> 1                    ) then Blech "PRegEx_GetNextMatch 14" && PRegEx_GetMatchStart()
  if (PRegEx_GetMatchStart(0) <> 1                    ) then Blech "PRegEx_GetNextMatch 15" && PRegEx_GetMatchStart(0) -- FAILING 4/21/2001
  if (PRegEx_GetMatchStart(1) <> 2                    ) then Blech "PRegEx_GetNextMatch 16" && PRegEx_GetMatchStart(1) -- FAILING 4/21/2001
  if (PRegEx_GetMatchStart(2) <> void             ) then Blech "PRegEx_GetNextMatch 16b" && PRegEx_GetMatchStart(2)
  
  if (PRegEx_GetMatchLen()    <> 5                        ) then Blech "PRegEx_GetNextMatch 17" && PRegEx_GetMatchLen()
  if (PRegEx_GetMatchLen(0) <> 5                      ) then Blech "PRegEx_GetNextMatch 18" && PRegEx_GetMatchLen(0)
  if (PRegEx_GetMatchLen(1) <> 3                      ) then Blech "PRegEx_GetNextMatch 19" && PRegEx_GetMatchLen(1)
  if (PRegEx_GetMatchLen(2) <> void                   ) then Blech "PRegEx_GetNextMatch 19b" && PRegEx_GetMatchLen(2)
  
  if (PRegEx_GetPos()             <> 6                        ) then Blech "PRegEx_GetNextMatch 19c" && PRegEx_GetPos()
  
  -- Match #2
  if (PRegEx_GetNextMatch()        <> true            ) then Blech "PRegEx_GetNextMatch 20" && PRegEx_MemError()
  
  if (PRegEx_GetMatchString()  <> " fig "     ) then Blech "PRegEx_GetNextMatch 21" && PRegEx_GetMatchString()
  if (PRegEx_GetMatchString(0) <> " fig "     ) then Blech "PRegEx_GetNextMatch 22" && PRegEx_GetMatchString(0)
  if (PRegEx_GetMatchString(1) <> "fig"           ) then Blech "PRegEx_GetNextMatch 23" && PRegEx_GetMatchString(1)
  if (PRegEx_GetMatchString(2) <> void            ) then Blech "PRegEx_GetNextMatch 23b" && PRegEx_GetMatchString(2)
  
  if (PRegEx_GetMatchStart()  <> 27                   ) then Blech "PRegEx_GetNextMatch 24" && PRegEx_GetMatchStart()
  if (PRegEx_GetMatchStart(0) <> 27                   ) then Blech "PRegEx_GetNextMatch 25" && PRegEx_GetMatchStart(0) -- FAILING 4/21/2001
  if (PRegEx_GetMatchStart(1) <> 28                   ) then Blech "PRegEx_GetNextMatch 26" && PRegEx_GetMatchStart(1) -- FAILING 4/21/2001
  if (PRegEx_GetMatchStart(2) <> void             ) then Blech "PRegEx_GetNextMatch 26b" && PRegEx_GetMatchStart(2)
  
  if (PRegEx_GetMatchLen()    <> 5                        ) then Blech "PRegEx_GetNextMatch 27" && PRegEx_GetMatchLen()
  if (PRegEx_GetMatchLen(0) <> 5                      ) then Blech "PRegEx_GetNextMatch 28" && PRegEx_GetMatchLen(0)
  if (PRegEx_GetMatchLen(1) <> 3                      ) then Blech "PRegEx_GetNextMatch 29" && PRegEx_GetMatchLen(1)
  if (PRegEx_GetMatchLen(2) <> void                   ) then Blech "PRegEx_GetNextMatch 29b" && PRegEx_GetMatchLen(2)
  
  if (PRegEx_GetPos()             <> 32                       ) then Blech "PRegEx_GetNextMatch 29c" && PRegEx_GetPos()
  
  -- Match #3
  if (PRegEx_GetNextMatch()        <> true            ) then Blech "PRegEx_GetNextMatch 30" && PRegEx_MemError()
  
  if (PRegEx_GetMatchString()  <> " figg "    ) then Blech "PRegEx_GetNextMatch 31" && PRegEx_GetMatchString()
  if (PRegEx_GetMatchString(0) <> " figg "    ) then Blech "PRegEx_GetNextMatch 32" && PRegEx_GetMatchString(0)
  if (PRegEx_GetMatchString(1) <> "figg"      ) then Blech "PRegEx_GetNextMatch 33" && PRegEx_GetMatchString(1)
  if (PRegEx_GetMatchString(2) <> void            ) then Blech "PRegEx_GetNextMatch 33b" && PRegEx_GetMatchString(2)
  
  if (PRegEx_GetMatchStart()  <> 37                   ) then Blech "PRegEx_GetNextMatch 34" && PRegEx_GetMatchStart()
  if (PRegEx_GetMatchStart(0) <> 37                   ) then Blech "PRegEx_GetNextMatch 35" && PRegEx_GetMatchStart(0) -- FAILING 4/21/2001
  if (PRegEx_GetMatchStart(1) <> 38                   ) then Blech "PRegEx_GetNextMatch 36" && PRegEx_GetMatchStart(1) -- FAILING 4/21/2001
  if (PRegEx_GetMatchStart(2) <> void             ) then Blech "PRegEx_GetNextMatch 36b" && PRegEx_GetMatchStart(2)
  
  if (PRegEx_GetMatchLen()    <> 6                        ) then Blech "PRegEx_GetNextMatch 37" && PRegEx_GetMatchLen()
  if (PRegEx_GetMatchLen(0) <> 6                      ) then Blech "PRegEx_GetNextMatch 38" && PRegEx_GetMatchLen(0)
  if (PRegEx_GetMatchLen(1) <> 4                      ) then Blech "PRegEx_GetNextMatch 39" && PRegEx_GetMatchLen(1)
  if (PRegEx_GetMatchLen(2) <> void                   ) then Blech "PRegEx_GetNextMatch 39b" && PRegEx_GetMatchLen(2)
  
  if (PRegEx_GetPos()             <> 43                       ) then Blech "PRegEx_GetNextMatch 39c" && PRegEx_GetPos()
  
  -- Match #4 (supposed to NOT match because there are no more matches available.)
  if (PRegEx_GetNextMatch()        <> false            ) then Blech "PRegEx_GetNextMatch 40" && PRegEx_MemError() -- FAILING 4/21/2001
  
  -- SUITE #2: Redo same suite of tests, but now with a null character in the search string in position 16
  
  set origString = ["a big pig sat on" & numtochar(0) & "a priggish fig figgy figg fig"]
  --                               0000000000111111                            1       111222222222233333333334444444
  --                               0123456789012345                            6       789012345678901234567890123456
  --                               ^^^^^                                                                              ^^^^^           ^^^^^^
  set aString = [origString[1], length(origString[1])]
  
  if (PRegEx_SetSearchString(aString) <> true)                                     then Blech "PRegEx_GetNextMatch 1" && PRegEx_CompiledOK()
  if (PRegEx_SetMatchPattern(" ([a-z]ig+) ", "i"          ) <> true) then Blech "PRegEx_GetNextMatch 2" && PRegEx_MemError()
  
  -- Match #1
  if (PRegEx_GetNextMatch()        <> true            ) then Blech "PRegEx_GetNextMatch 110" && PRegEx_MemError()
  
  if (PRegEx_GetMatchString()  <> " big "     ) then Blech "PRegEx_GetNextMatch 111" && PRegEx_GetMatchString()
  if (PRegEx_GetMatchString(0) <> " big "     ) then Blech "PRegEx_GetNextMatch 112" && PRegEx_GetMatchString(0)
  if (PRegEx_GetMatchString(1) <> "big"           ) then Blech "PRegEx_GetNextMatch 113" && PRegEx_GetMatchString(1)
  if (PRegEx_GetMatchString(2) <> void            ) then Blech "PRegEx_GetNextMatch 113b" && PRegEx_GetMatchString(2)
  
  if (PRegEx_GetPos()             <> 6                        ) then Blech "PRegEx_GetNextMatch 119c" && PRegEx_GetPos()
  
  -- Match #2 -- FAILING 4/21/2001 (ENTIRE GROUP) -- seems to be re-starting match at beginning,
  -- OR maybe GetNextMatch() is failing to match when it should (BUG), and then failng to return false (another BUG)
  
  if (PRegEx_GetNextMatch()        <> true            ) then Blech "PRegEx_GetNextMatch 120" && PRegEx_MemError()
  
  if (PRegEx_GetMatchString()  <> " fig "     ) then Blech "PRegEx_GetNextMatch 121" && PRegEx_GetMatchString()
  if (PRegEx_GetMatchString(0) <> " fig "     ) then Blech "PRegEx_GetNextMatch 122" && PRegEx_GetMatchString(0)
  if (PRegEx_GetMatchString(1) <> "fig"           ) then Blech "PRegEx_GetNextMatch 123" && PRegEx_GetMatchString(1)
  if (PRegEx_GetMatchString(2) <> void            ) then Blech "PRegEx_GetNextMatch 123b" && PRegEx_GetMatchString(2)
  
  if (PRegEx_GetPos()             <> 32                       ) then Blech "PRegEx_GetNextMatch 129c" && PRegEx_GetPos()
  
  -- Match #3 -- FAILING 4/21/2001 (ENTIRE GROUP) -- seems to be re-starting match at beginning.
  -- OR maybe GetNextMatch() is failing to match when it should (BUG), and then failng to return false (another BUG)
  if (PRegEx_GetNextMatch()        <> true            ) then Blech "PRegEx_GetNextMatch 130" && PRegEx_MemError()
  
  if (PRegEx_GetMatchString()  <> " figg "    ) then Blech "PRegEx_GetNextMatch 131" && PRegEx_GetMatchString()
  if (PRegEx_GetMatchString(0) <> " figg "    ) then Blech "PRegEx_GetNextMatch 132" && PRegEx_GetMatchString(0)
  if (PRegEx_GetMatchString(1) <> "figg"      ) then Blech "PRegEx_GetNextMatch 133" && PRegEx_GetMatchString(1)
  if (PRegEx_GetMatchString(2) <> void            ) then Blech "PRegEx_GetNextMatch 133b" && PRegEx_GetMatchString(2)
  
  if (PRegEx_GetPos()             <> 43                       ) then Blech "PRegEx_GetNextMatch 139c" && PRegEx_GetPos()
  
  -- Match #4 (supposed to NOT match because there are no more matches available.)
  if (PRegEx_GetNextMatch()        <> false            ) then Blech "PRegEx_GetNextMatch 140" && PRegEx_MemError() -- FAILING 4/21/2001
  
  -- SUITE #3: Matching twice with a SetPos in between.
  
  if      (PRegEx_SetSearchString(["a big pig sat on" &                    "_" & "a priggish fig figgy figg fig"]) <> true) then Blech "PRegEx_GetNextMatch 1" && PRegEx_CompiledOK()
  --                                                       0000000000111111                            1       111222222222233333333334444444
  --                                                       0123456789012345                            6       789012345678901234567890123456
  --                                                          ^^^^^                                                                                ^^^^^       ^^^^^^
  
  if (PRegEx_SetMatchPattern(" ([a-z]ig+) ", "i"          ) <> true) then Blech "PRegEx_GetNextMatch 2" && PRegEx_MemError()
  
  -- Match #1
  if (PRegEx_GetNextMatch()        <> true            ) then Blech "PRegEx_GetNextMatch 210" && PRegEx_MemError()
  
  if (PRegEx_GetMatchString()  <> " big "     ) then Blech "PRegEx_GetNextMatch 211" && PRegEx_GetMatchString()
  if (PRegEx_GetMatchString(0) <> " big "     ) then Blech "PRegEx_GetNextMatch 212" && PRegEx_GetMatchString(0)
  if (PRegEx_GetMatchString(1) <> "big"           ) then Blech "PRegEx_GetNextMatch 213" && PRegEx_GetMatchString(1)
  if (PRegEx_GetMatchString(2) <> void            ) then Blech "PRegEx_GetNextMatch 213b" && PRegEx_GetMatchString(2)
  
  -- Match #1 (again)
  
  if (PRegEx_GetPos()             <> 6                        ) then Blech "PRegEx_GetNextMatch 219c" && PRegEx_GetPos()
  if (PRegEx_SetPos(1)             <> void                ) then Blech "PRegEx_GetNextMatch 219c" && PRegEx_SetPos()
  if (PRegEx_GetPos()             <> 1                        ) then Blech "PRegEx_GetNextMatch 219c" && PRegEx_GetPos()
  
  if (PRegEx_GetNextMatch()        <> true            ) then Blech "PRegEx_GetNextMatch 220" && PRegEx_MemError()
  
  if (PRegEx_GetMatchString()  <> " big "     ) then Blech "PRegEx_GetNextMatch 221" && PRegEx_GetMatchString()
  if (PRegEx_GetMatchString(0) <> " big "     ) then Blech "PRegEx_GetNextMatch 222" && PRegEx_GetMatchString(0)
  if (PRegEx_GetMatchString(1) <> "big"           ) then Blech "PRegEx_GetNextMatch 223" && PRegEx_GetMatchString(1)
  if (PRegEx_GetMatchString(2) <> void            ) then Blech "PRegEx_GetNextMatch 223b" && PRegEx_GetMatchString(2)
  
  -- Match #1 (again)
  if (PRegEx_GetPos()             <> 6                        ) then Blech "PRegEx_GetNextMatch 229c" && PRegEx_GetPos()
  if (PRegEx_SetPos(0)             <> void                ) then Blech "PRegEx_GetNextMatch 229c" && PRegEx_SetPos() -- FAILING 4/21/2001 (see 3 below)
  if (PRegEx_GetPos()             <> 0                        ) then Blech "PRegEx_GetNextMatch 229c" && PRegEx_GetPos()
  
  if (PRegEx_GetNextMatch()        <> true            ) then Blech "PRegEx_GetNextMatch 230" && PRegEx_MemError()
  
  if (PRegEx_GetMatchString()  <> " big "     ) then Blech "PRegEx_GetNextMatch 231" && PRegEx_GetMatchString()    -- FAILING 4/21/2001 (SetPos(0))
  if (PRegEx_GetMatchString(0) <> " big "     ) then Blech "PRegEx_GetNextMatch 232" && PRegEx_GetMatchString(0) -- FAILING 4/21/2001 (SetPos(0))
  if (PRegEx_GetMatchString(1) <> "big"           ) then Blech "PRegEx_GetNextMatch 233" && PRegEx_GetMatchString(1) -- FAILING 4/21/2001 (SetPos(0))
  if (PRegEx_GetMatchString(2) <> void            ) then Blech "PRegEx_GetNextMatch 233b" && PRegEx_GetMatchString(2)
  
  -- Match #1 (again) -- SetMatchPattern should re-set pos, just like calling SetPos(0) does.
  
  if (PRegEx_SetMatchPattern(" ([a-z]ig+) ", "i"          ) <> true) then Blech "PRegEx_GetNextMatch 3" && PRegEx_MemError()
  
  if (PRegEx_GetNextMatch()        <> true            ) then Blech "PRegEx_GetNextMatch 240" && PRegEx_MemError()
  
  if (PRegEx_GetMatchString()  <> " big "     ) then Blech "PRegEx_GetNextMatch 241" && PRegEx_GetMatchString()
  if (PRegEx_GetMatchString(0) <> " big "     ) then Blech "PRegEx_GetNextMatch 242" && PRegEx_GetMatchString(0)
  if (PRegEx_GetMatchString(1) <> "big"           ) then Blech "PRegEx_GetNextMatch 243" && PRegEx_GetMatchString(1)
  if (PRegEx_GetMatchString(2) <> void            ) then Blech "PRegEx_GetNextMatch 243b" && PRegEx_GetMatchString(2)
  
  -- Match #1 (again) -- PRegEx_SetSearchString should re-set pos, just like calling SetPos(0) does.
  
  if (PRegEx_SetSearchString(["a big pig sat on"]          ) <> true) then Blech "PRegEx_GetNextMatch 4" && PRegEx_MemError()
  
  if (PRegEx_GetNextMatch()        <> true            ) then Blech "PRegEx_GetNextMatch 250" && PRegEx_MemError()
  
  if (PRegEx_GetMatchString()  <> " big "     ) then Blech "PRegEx_GetNextMatch 251" && PRegEx_GetMatchString()
  if (PRegEx_GetMatchString(0) <> " big "     ) then Blech "PRegEx_GetNextMatch 252" && PRegEx_GetMatchString(0)
  if (PRegEx_GetMatchString(1) <> "big"           ) then Blech "PRegEx_GetNextMatch 253" && PRegEx_GetMatchString(1)
  if (PRegEx_GetMatchString(2) <> void            ) then Blech "PRegEx_GetNextMatch 253b" && PRegEx_GetMatchString(2)
  
  -- leak test -- picks up from same search string as above
  if (LeakTestingSelected()) then
    set fBytes = void
    repeat with iterNum = 1 to 10000
      if (PRegEx_SetPos(1)             <> void                ) then Blech "PRegEx_GetNextMatch 260" && PRegEx_SetPos()
      if (PRegEx_GetPos()             <> 1                        ) then Blech "PRegEx_GetNextMatch 261" && PRegEx_GetPos()
      if (PRegEx_GetNextMatch()        <> true            ) then Blech "PRegEx_GetNextMatch 262" && PRegEx_MemError()
      if (PRegEx_GetMatchString()  <> " big "     ) then Blech "PRegEx_GetNextMatch 263" && PRegEx_GetMatchString()
      if (PRegEx_GetMatchString(0) <> " big "     ) then Blech "PRegEx_GetNextMatch 264" && PRegEx_GetMatchString(0)
      if (PRegEx_GetMatchString(1) <> "big"           ) then Blech "PRegEx_GetNextMatch 265" && PRegEx_GetMatchString(1)
      
      if iterNum mod 200 = 0 then
        if fBytes = void then set fBytes = the freeBytes
      end if
    end repeat
    if abs(fBytes - the freeBytes)>100 then Blech "PRegEx_GetNextMatch Leak" && (the freeBytes - fBytes)
  end if
  
end Test_PRegEx_GetNextMatch
