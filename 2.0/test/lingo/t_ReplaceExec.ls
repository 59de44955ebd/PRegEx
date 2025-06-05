on Test_PRegEx_ReplaceExec
  set aStringOrig = ["Hi Chris"]
  
  set aString         = [aStringOrig[1]]
  if ((PRegEx_ReplaceExec(aString, "chris", "",    #Bracketize         ) <> 0) or (aString[1] <> "Hi Chris"                )) then Blech "Test_PRegEx_ReplaceExec 101" && PRegEx_CompiledOK()
  
  set aString         = [aStringOrig[1]]
  if ((re_s                           (aString, "chris", "ie", #Bracketize         ) <> 1) or (aString[1] <> "Hi [[Chris]]"    )) then Blech "Test_PRegEx_ReplaceExec 102" && PRegEx_CompiledOK()
  
  set aString         = [aStringOrig[1]]
  if ((re_replace             (aString, "chris", "ie", #Bracketize         ) <> 1) or (aString[1] <> "Hi [[Chris]]"    )) then Blech "Test_PRegEx_ReplaceExec 102" && PRegEx_CompiledOK()
  
  set aString         = [aStringOrig[1]]
  if ((PRegEx_ReplaceExec(aString, "chris", "i",  #Bracketize         ) <> 1) or (aString[1] <> "Hi [[Chris]]"    )) then Blech "Test_PRegEx_ReplaceExec 102" && PRegEx_CompiledOK()
  
  set aString         = [aStringOrig[1]]
  if ((PRegEx_ReplaceExec(aString, "chris", "i", #BracketizeAbort) <> PRegEx_ErrCode_CallbackRequestedAbort()) or (aString[1] <> "Hi Chris"                )) then Blech "Test_PRegEx_ReplaceExec 103" && PRegEx_CompiledOK()
  
  -- exec mode with argument to callback function
  set aString         = [aStringOrig[1]]
  if ((PRegEx_ReplaceExec(aString, "chris", "i", #ListElemGetter, [[["a", "b", "c"], 2]]) <> 1) or (aString[1] <> "Hi b"              )) then Blech "Test_PRegEx_ReplaceExec 103b" && PRegEx_CompiledOK()
  
  set aString         = [aStringOrig[1]]
  if ((PRegEx_ReplaceExec(aString, "chris", "i", #ArgDoubler, "wot") <> 1) or (aString[1] <> "Hi wotwot"              )) then Blech "Test_PRegEx_ReplaceExec 103c" && PRegEx_CompiledOK()
  
  set aString         = ["Hi Chrîs"]
  if ((PRegEx_ReplaceExec(aString, "chrîs", "i", #ArgDoubler, "wot") <> 1) or (aString[1] <> "Hi wotwot"              )) then Blech "Test_PRegEx_ReplaceExec 103d" && PRegEx_CompiledOK()
  
  -- global
  
  set aString         = [aStringOrig[1]]
  if ((PRegEx_ReplaceExec(aString, "\w+", "g", #Bracketize) <> 2) or (aString[1] <> "[[Hi]] [[Chris]]"            )) then Blech "Test_PRegEx_ReplaceExec 201" && PRegEx_CompiledOK()
  
  set aString         = [aStringOrig[1]]
  if ((PRegEx_ReplaceExec(aString, "\w+", "g", #Underscore) <> 2) or (aString[1] <> "_ _"                                     )) then Blech "Test_PRegEx_ReplaceExec 202" && PRegEx_CompiledOK()
  
  -- global, with abort/stop/last
  
  set aStringOrig = ["Hi Chris T", 10]
  
  set aString         = [aStringOrig[1]]
  if ((PRegEx_ReplaceExec(aString, "\w+", "g", #Underscore) <> 3) or (aString[1] <> "_ _ _"                                       )) then Blech "Test_PRegEx_ReplaceExec 301" && PRegEx_CompiledOK()
  
  set aString         = [aStringOrig[1]]
  if ((PRegEx_ReplaceExec(aString, "\w+", "g", #UnderscoreAbortOn2) <> PRegEx_ErrCode_CallbackRequestedAbort()) or (aString[1] <> "Hi Chris T"     )) then Blech "Test_PRegEx_ReplaceExec 302" && PRegEx_CompiledOK()
  
  set aString         = [aStringOrig[1]]
  if ((PRegEx_ReplaceExec(aString, "\w+", "g", #UnderscoreStopOn2 ) <> 2) or (aString[1] <> "_ Chris T"               )) then Blech "Test_PRegEx_ReplaceExec 303" && PRegEx_CompiledOK()
  
  set aString         = [aStringOrig[1]]
  if ((PRegEx_ReplaceExec(aString, "\w+", "g", #UnderscoreSkipOn2 ) <> 3) or (aString[1] <> "_ Chris _"               )) then Blech "Test_PRegEx_ReplaceExec 303a" && PRegEx_CompiledOK()
  
  set aString         = [aStringOrig[1]]
  if ((PRegEx_ReplaceExec(aString, "\w+", "g", #UnderscoreLastOn2 ) <> 2) or (aString[1] <> "_ _ T"                       )) then Blech "Test_PRegEx_ReplaceExec 304" && PRegEx_CompiledOK()
  
  -- "e" option to Replace makes it do the same as ReplaceExec.
  set aString         = [aStringOrig[1]]
  if ((PRegEx_Replace(aString, "\w+", "ge", #UnderscoreStopOn2 ) <> 2) or (aString[1] <> "_ Chris T"           )) then Blech "Test_PRegEx_ReplaceExec 305" && PRegEx_CompiledOK()
  
  RecursionTest
  
  -- leak test
  if (LeakTestingSelected()) then
    set fBytes = void
    repeat with iterNum = 1 to 10000
      
      set aStringOrig = ["Hi Chris"]
      
      set aString         = [aStringOrig[1]]
      if ((PRegEx_ReplaceExec(aString, "chris", "i", #Bracketize       ) <> 1) or (aString[1] <> "Hi [[Chris]]"    )) then Blech "Test_PRegEx_ReplaceExec 400" && PRegEx_CompiledOK()
      
      set aStringOrig = ["Hi Chris T", 10]
      
      set aString         = [aStringOrig[1]]
      if ((PRegEx_ReplaceExec(aString, "\w+", "g", #Underscore_LONG_SYMBOL_NAME_FOR_LEAK_TESTING) <> 3) or (aString[1] <> "_ _ _")) then Blech "Test_PRegEx_ReplaceExec 401" && PRegEx_CompiledOK()
      
      set aString         = [aStringOrig[1]]
      if ((PRegEx_ReplaceExec(aString, "\w+", "g", #UnderscoreAbortOn2) <> PRegEx_ErrCode_CallbackRequestedAbort()) or (aString[1] <> "Hi Chris T"     )) then Blech "Test_PRegEx_ReplaceExec 402" && PRegEx_CompiledOK()
      
      set aString         = [aStringOrig[1]]
      if ((PRegEx_ReplaceExec(aString, "\w+", "g", #UnderscoreStopOn2 ) <> 2) or (aString[1] <> "_ Chris T"               )) then Blech "Test_PRegEx_ReplaceExec 403" && PRegEx_CompiledOK()
      
      set aString         = [aStringOrig[1]]
      if ((PRegEx_ReplaceExec(aString, "\w+", "g", #UnderscoreLastOn2 ) <> 2) or (aString[1] <> "_ _ T"                       )) then Blech "Test_PRegEx_ReplaceExec 404" && PRegEx_CompiledOK()
      
      if iterNum mod 200 = 0 then -- measure memory after 1/50th of the iterations
        if fBytes = void then set fBytes = the freeBytes
        -- put the freeBytes -- remember: uncommenting this uses up memory in the Message window's buffer!
      end if
    end repeat
    -- Measure memory again after all 100% of iterations have happened.  There should be no change.
    if abs(fBytes - the freeBytes)>100 then Blech "Test_PRegEx_ReplaceExec Leak 400" && (the freeBytes - fBytes)
  end if
  
  -- leak test with recursion
  if (LeakTestingSelected()) then
    set fBytes = void
    repeat with iterNum = 1 to 4000
      
      -- recursion test
      RecursionTest()
      
      if iterNum mod 200 = 0 then -- measure memory after 1/50th of the iterations
        if fBytes = void then set fBytes = the freeBytes
        -- put the freeBytes -- remember: uncommenting this uses up memory in the Message window's buffer!
      end if
    end repeat
    -- Measure memory again after all 100% of iterations have happened.  There should be no change.
    if abs(fBytes - the freeBytes)>100 then Blech "Test_PRegEx_ReplaceExec Leak 500" && (the freeBytes - fBytes)
  end if
  
end Test_PRegEx_ReplaceExec

on RecursionTest
  set aStringOrig = ["Hi Joe Jones"]
  set aString         = [aStringOrig[1]]
  if ((PRegEx_ReplaceExec(aString, "(\w+)", "g", #CapUnderScorer) <> 3) or (aString[1] <> "_H_i _J_oe _J_ones"        )) then Blech "Test_PRegEx_ReplaceExec 305" && PRegEx_CompiledOK()
  if PRegEx_GetMatchString(1) <> "Jones" then Blech "Test_PRegEx_ReplaceExec 501"
end RecursionTest