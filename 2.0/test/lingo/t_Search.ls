on Test_PRegEx_Search
  if (PRegEx_Search(["Hi Chris"], "chris", ""                 ) <> 0) then Blech "PRegEx_Search 101" && PRegEx_CompiledOK()
  if (PRegEx_Search(["Hi Chris"], "chris", "i"                ) <> 1) then Blech "PRegEx_Search 102" && PRegEx_CompiledOK()
  if (re_search       (["Hi Chris"], "chris", "i"             ) <> 1) then Blech "PRegEx_Search 102" && PRegEx_CompiledOK()
  if (re_m                (["Hi Chris"], "chris", "i"         ) <> 1) then Blech "PRegEx_Search 103" && PRegEx_CompiledOK()
  
  -- Regression test: make sure "s" and "m" flags work correctly.
  -- \n should be a newline for puposes of "." and signaling line beginnings for "m"
  if (re_m                ([re_i("a\nb")], "...", "g"         ) <> 0) then Blech "PRegEx_Search 104" && PRegEx_CompiledOK()
  if (re_m                ([re_i("a\nb")], "...", "gs"        ) <> 1) then Blech "PRegEx_Search 105" && PRegEx_CompiledOK()
  if (re_m                ([re_i("a\nb\n\n\n")], "...", "gs"  ) <> 2) then Blech "PRegEx_Search 105" && PRegEx_CompiledOK()
  
  if (re_m                ([re_i("a\nb")], "^b", "g"          ) <> 0) then Blech "PRegEx_Search 106" && PRegEx_CompiledOK()
  if (re_m                ([re_i("a\nb")], "^b", "gm"         ) <> 1) then Blech "PRegEx_Search 107" && PRegEx_CompiledOK()
  if (re_m                ([re_i("a\nbsdf\nb \n")], "^b", "gm") <> 2) then Blech "PRegEx_Search 108" && PRegEx_CompiledOK()
  
  -- \x0d (CR aka return) should be the same as \n
  if (re_m                ([re_i("a\x0db")], "...", "g"         ) <> 0) then Blech "PRegEx_Search 109" && PRegEx_CompiledOK()
  if (re_m                ([re_i("a\x0db")], "...", "gs"        ) <> 1) then Blech "PRegEx_Search 110" && PRegEx_CompiledOK()
  if (re_m                ([re_i("a\x0db\x0d\x0d\x0d")], "...", "gs"  ) <> 2) then Blech "PRegEx_Search 111" && PRegEx_CompiledOK()
  
  if (re_m                ([re_i("a\x0db")], "^b", "g"          ) <> 0) then Blech "PRegEx_Search 112" && PRegEx_CompiledOK()
  if (re_m                ([re_i("a\x0db")], "^b", "gm"         ) <> 1) then Blech "PRegEx_Search 113" && PRegEx_CompiledOK()
  if (re_m                ([re_i("a\x0dbsdf\x0db \x0d")], "^b", "gm") <> 2) then Blech "PRegEx_Search 114" && PRegEx_CompiledOK()
  
  -- \x0a (LF aka line feed aka not an official Director line ending char) should NOT be same as \n
  if (re_m                ([re_i("a\x0ab")], "...", "g"         ) <> 1) then Blech "PRegEx_Search 115" && PRegEx_CompiledOK()
  if (re_m                ([re_i("a\x0ab")], "...", "gs"        ) <> 1) then Blech "PRegEx_Search 116" && PRegEx_CompiledOK()
  if (re_m                ([re_i("a\x0ab\x0a\x0a\x0a")], "...", "gs"  ) <> 2) then Blech "PRegEx_Search 117" && PRegEx_CompiledOK()
  
  if (re_m                ([re_i("a\x0ab")], "^b", "g"          ) <> 0) then Blech "PRegEx_Search 118" && PRegEx_CompiledOK()
  if (re_m                ([re_i("a\x0ab")], "^b", "gm"         ) <> 0) then Blech "PRegEx_Search 119" && PRegEx_CompiledOK()
  if (re_m                ([re_i("a\x0absdf\x0ab \x0a")], "^b", "gm") <> 0) then Blech "PRegEx_Search 120" && PRegEx_CompiledOK()
  
  -- testing global mode
  
  if (PRegEx_Search(["Hi Chris"], "chris", "g"            ) <> 0) then Blech "PRegEx_Search 201" && PRegEx_CompiledOK()
  if (PRegEx_Search(["Hi Chrîs"], "chrîs", "ig"           ) <> 1) then Blech "PRegEx_Search 202" && PRegEx_CompiledOK()
  if (PRegEx_Search(["Hi ch Ch"], "ch",        "ig"           ) <> 2) then Blech "PRegEx_Search 203" && PRegEx_CompiledOK()
  if (PRegEx_Search(["Hi ch Ch"], "ch",        "g"            ) <> 1) then Blech "PRegEx_Search 204" && PRegEx_CompiledOK()
  
  -- testing bad params
  
  if (PRegEx_Search([""],                 "ch",        "g"            ) <> 0) then Blech "PRegEx_Search 301" && PRegEx_CompiledOK()
  if (PRegEx_Search([],                   "ch",        "g"                ) <> PRegEx_ErrCode_SearchStrLMustContainString()) then Blech "PRegEx_Search 302" && PRegEx_CompiledOK()
  if (PRegEx_Search(["", ""],                 "ch",        "g"    ) <> PRegEx_ErrCode_SearchStrLLengthArgMustBeInteger()) then Blech "PRegEx_Search 302b" && PRegEx_CompiledOK()
  if (PRegEx_Search([""],                 "",      "g"    ) <> PRegEx_ErrCode_REMustNotBeEmpty()) then Blech "PRegEx_Search 302c" && PRegEx_CompiledOK()
  if (PRegEx_Search([""],                 "((",        "g"    ) <> PRegEx_ErrCode_REDidNotCompile()) then Blech "PRegEx_Search 302d" && PRegEx_CompiledOK()
  if (PRegEx_Replace([""],                 "a",        "g", 0  ) <> PRegEx_ErrCode_ReplPatMustBeString()) then Blech "PRegEx_Search 302e" && PRegEx_CompiledOK()
  if (PRegEx_Replace([""],                 "a",        "ge", "foo"    ) <> PRegEx_ErrCode_CallbackFuncMustBeSymbol()) then Blech "PRegEx_Search 302f" && PRegEx_CompiledOK()
  if (PRegEx_Replace(["aaa"],          "a",        "ge", #undef    ) <> PRegEx_ErrCode_CallbackFunctionFailed()) then Blech "PRegEx_Search 302g" && PRegEx_CompiledOK()
  if (PRegEx_Replace(["aaa"],          "a",        "ge", #ReturnsInt  ) <> PRegEx_ErrCode_CallbackFuncDidNotReturnString()) then Blech "PRegEx_Search 302h" && PRegEx_CompiledOK()
  
  -- leak test
  if (LeakTestingSelected()) then
    set fBytes = void
    repeat with iterNum = 1 to 10000
      if (PRegEx_Search(["Hi Chris"], "chris", "g"            ) <> 0) then Blech "PRegEx_Search 401" && PRegEx_CompiledOK()
      if (PRegEx_Search(["Hi Chris"], "chris", "ig"           ) <> 1) then Blech "PRegEx_Search 402" && PRegEx_CompiledOK()
      if (PRegEx_Search(["Hi ch Ch"], "ch",        "ig"           ) <> 2) then Blech "PRegEx_Search 403" && PRegEx_CompiledOK()
      
      if iterNum mod 200 = 0 then -- measure memory after 1/50th of the iterations
        if fBytes = void then set fBytes = the freeBytes
        -- put the freeBytes -- remember: uncommenting this uses up memory in the Message window's buffer!
      end if
    end repeat
    -- Measure memory again after all 100% of iterations have happened.  There should be no change.
    if abs(fBytes - the freeBytes)>100 then Blech "PRegEx_Search Leak" && (the freeBytes - fBytes)
  end if
  
end Test_PRegEx_Search