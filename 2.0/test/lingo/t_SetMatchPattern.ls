on Test_PRegEx_SetMatchPattern
  
  if (PRegEx_SetMatchPattern("", ""               ) <> PRegEx_ErrCode_REMustNotBeEmpty()) then Blech "PRegEx_SetMatchPattern 1" && PRegEx_CompiledOK()
  if (PRegEx_SetMatchPattern("a", ""          ) <> true) then Blech "PRegEx_SetMatchPattern 2" && PRegEx_CompiledOK()
  if (PRegEx_SetMatchPattern("a", "g"         ) <> true) then Blech "PRegEx_SetMatchPattern 3" && PRegEx_CompiledOK()
  if (PRegEx_SetMatchPattern("a", "i"         ) <> true) then Blech "PRegEx_SetMatchPattern 4" && PRegEx_CompiledOK()
  if (PRegEx_SetMatchPattern("a", "s"         ) <> true) then Blech "PRegEx_SetMatchPattern 5" && PRegEx_CompiledOK()
  if (PRegEx_SetMatchPattern("a", "m"         ) <> true) then Blech "PRegEx_SetMatchPattern 6" && PRegEx_CompiledOK()
  if (PRegEx_SetMatchPattern("a", "x"         ) <> true) then Blech "PRegEx_SetMatchPattern 7" && PRegEx_CompiledOK()
  if (PRegEx_SetMatchPattern("a", "t"         ) <> true) then Blech "PRegEx_SetMatchPattern 8" && PRegEx_CompiledOK()
  if (PRegEx_SetMatchPattern("a", "gismxt") <> true) then Blech "PRegEx_SetMatchPattern 9" && PRegEx_CompiledOK()
  if (PRegEx_SetMatchPattern("a", "qaxfffffff") <> PRegEx_ErrCode_InvalidOptionsSpecified()) then Blech "PRegEx_SetMatchPattern 10" && PRegEx_CompiledOK()
  if (PRegEx_SetMatchPattern("å", "g"         ) <> true) then Blech "PRegEx_SetMatchPattern 3" && PRegEx_CompiledOK()
  
  -- Patterns that match the empty string (OK but risky)
  if (PRegEx_SetMatchPattern(".*", "gismxt") <> true) then Blech "PRegEx_SetMatchPattern 11" && PRegEx_CompiledOK()
  if (PRegEx_SetMatchPattern(".+", "gismxt") <> true) then Blech "PRegEx_SetMatchPattern 12" && PRegEx_CompiledOK()
  if (PRegEx_SetMatchPattern(".*?", "gismxt") <> true) then Blech "PRegEx_SetMatchPattern 13" && PRegEx_CompiledOK()
  if (PRegEx_SetMatchPattern(".+?", "gismxt") <> true) then Blech "PRegEx_SetMatchPattern 14" && PRegEx_CompiledOK()
  
  -- FAILING
  -- ALL of the following patterns (15-24) should NOT compile OK, but right now they are.  This is VERY troubling.
  -- Need to report this to creator of PCRE, (if the mistake is not on our side, that is!)
  
  -- meaningless quantifiers
  if (PRegEx_SetMatchPattern("+", "gismxt") <> PRegEx_ErrCode_REDidNotCompile()) then Blech "PRegEx_SetMatchPattern 15" && PRegEx_CompiledOK()
  if (PRegEx_SetMatchPattern("*", "gismxt") <> PRegEx_ErrCode_REDidNotCompile()) then Blech "PRegEx_SetMatchPattern 16" && PRegEx_CompiledOK()
  if (PRegEx_SetMatchPattern("?", "gismxt") <> PRegEx_ErrCode_REDidNotCompile()) then Blech "PRegEx_SetMatchPattern 17" && PRegEx_CompiledOK()
  if (PRegEx_SetMatchPattern("{1}", "gismxt") <> PRegEx_ErrCode_REDidNotCompile()) then Blech "PRegEx_SetMatchPattern 17b" && PRegEx_CompiledOK()
  
  -- unmatched parens
  if (PRegEx_SetMatchPattern("(", "gismxt") <> PRegEx_ErrCode_REDidNotCompile()) then Blech "PRegEx_SetMatchPattern 18" && PRegEx_CompiledOK()
  if (PRegEx_SetMatchPattern("(abc", "gismxt") <> PRegEx_ErrCode_REDidNotCompile()) then Blech "PRegEx_SetMatchPattern 19" && PRegEx_CompiledOK()
  if (PRegEx_SetMatchPattern(")", "gismxt") <> PRegEx_ErrCode_REDidNotCompile()) then Blech "PRegEx_SetMatchPattern 20" && PRegEx_CompiledOK()
  if (PRegEx_SetMatchPattern("(((((", "gismxt") <> PRegEx_ErrCode_REDidNotCompile()) then Blech "PRegEx_SetMatchPattern 21" && PRegEx_CompiledOK()
  if (PRegEx_SetMatchPattern("((((()))))))))", "gismxt") <> PRegEx_ErrCode_REDidNotCompile()) then Blech "PRegEx_SetMatchPattern 22" && PRegEx_CompiledOK()
  
  -- test removed : the new pcre-7.6 no longer has this limitation and compiles the expression without error
  -- too many back refs (120)
  --  if (PRegEx_SetMatchPattern("()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()", "gismxt") <> PRegEx_ErrCode_REDidNotCompile()) then Blech "PRegEx_SetMatchPattern 23" && PRegEx_CompiledOK()
  --  if (PRegEx_SetMatchPattern("(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)", "gismxt") <> PRegEx_ErrCode_REDidNotCompile()) then Blech "PRegEx_SetMatchPattern 24" && PRegEx_CompiledOK()
  
  -- leak test
  if (LeakTestingSelected()) then
    set fBytes = void
    repeat with iterNum = 1 to 10000
      if (PRegEx_SetMatchPattern("", ""               ) <> PRegEx_ErrCode_REMustNotBeEmpty()) then Blech "PRegEx_SetMatchPattern 1" && PRegEx_CompiledOK()
      if (PRegEx_SetMatchPattern("a", ""          ) <> true) then Blech "PRegEx_SetMatchPattern 2" && PRegEx_CompiledOK()
      if (PRegEx_SetMatchPattern("chris(.*?)t(a+[0-9]+)", ""          ) <> true) then Blech "PRegEx_SetMatchPattern 3" && PRegEx_CompiledOK()
      
      if iterNum mod 200 = 0 then -- measure memory after 1/50th of the iterations
        if fBytes = void then set fBytes = the freeBytes
        -- put the freeBytes -- remember: uncommenting this uses up memory in the Message window's buffer!
      end if
    end repeat
    -- Measure memory again after all 100% of iterations have happened.  There should be no change.
    if abs(fBytes - the freeBytes)>100 then Blech "PRegEx_SetMatchPattern Leak" && (the freeBytes - fBytes)
  end if
  
end Test_PRegEx_SetMatchPattern