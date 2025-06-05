on Test_PRegEx_ExtractIntoSPList
  if not(PListEQ(re_extractp             (["a b c d e"], "(\w) (\w) (\w) (\w)"           , ""), ["a":"b", "c":"d"                    ])) then Blech "PRegEx_ExtractIntoSPList 101" && PRegEx_CompiledOK()
  if not(PListEQ(PRegEx_ExtractIntoSPList(["a b c d e"], "(\w) (\w) (\w) (\w)"         , ""), ["a":"b", "c":"d"                    ])) then Blech "PRegEx_ExtractIntoSPList 101" && PRegEx_CompiledOK()
  if not(PListEQ(PRegEx_ExtractIntoSPList(["a b c d e"], "(\w) (\w) (\w) (\w) (\w)", ""), ["a":"b", "c":"d", "e":void  ])) then Blech "PRegEx_ExtractIntoSPList 102" && PRegEx_CompiledOK()
  
  -- global
  if not(PListEQ(PRegEx_ExtractIntoSPList(["a b c d e"], "(\w) (\w) (\w) (\w)"         , "g"), ["a":"b", "c":"d"                  ])) then Blech "PRegEx_ExtractIntoSPList 201" && PRegEx_CompiledOK()
  if not(PListEQ(PRegEx_ExtractIntoSPList(["a b c d e"], "(\w) ", "g"), ["a":"b", "c":"d"])) then Blech "PRegEx_ExtractIntoSPList 202" && PRegEx_CompiledOK()
  if not(PListEQ(PRegEx_ExtractIntoSPList(["a ß c d e "], "(\pL) ", "g"), ["a":"ß", "c":"d", "e":void ])) then Blech "PRegEx_ExtractIntoSPList 203" && PRegEx_CompiledOK()
  
  if not(PListEQ(PRegEx_ExtractIntoSPList(["a b c d e f g h i "], "(\w) (\w) (\w) ", "g"), ["a":"b", "c":"d", "e":"f", "g":"h", "i":void  ])) then Blech "PRegEx_ExtractIntoSPList 204" && PRegEx_CompiledOK()
  if not(PListEQ(PRegEx_ExtractIntoSPList(["a b c d e f g h i "], "(\w) (\w) ", "g"), ["a":"b", "c":"d", "e":"f", "g":"h"                 ])) then Blech "PRegEx_ExtractIntoSPList 205" && PRegEx_CompiledOK()
  
  if not(PListEQ(PRegEx_ExtractIntoSPList(["a b c d e f g h i "], "\w(\W)", "g"), [" ":void                                            ])) then Blech "PRegEx_ExtractIntoSPList 206" && PRegEx_CompiledOK()
  if not(PListEQ(PRegEx_ExtractIntoSPList(["a b c d e f g h   "], "\w(\W)", "g"), [" ":" "])) then Blech "PRegEx_ExtractIntoSPList 207" && PRegEx_CompiledOK()
  
  -- leak test
  if (LeakTestingSelected()) then
    set fBytes = void
    repeat with iterNum = 1 to 10000
      
      set xList = [:]
      if not(PListEQ(PRegEx_ExtractIntoSPList(["a b "], "(\w) "                                   , "g", xList), ["a":"b"                                     ])) then Blech "PRegEx_ExtractIntoSPList 400a" && PRegEx_CompiledOK()
      if not(PListEQ(PRegEx_ExtractIntoSPList(["c d e"], "(\w) "                                  , "g", xList), ["a":"b", "c":"d"                    ])) then Blech "PRegEx_ExtractIntoSPList 400b" && PRegEx_CompiledOK()
      if not(PListEQ(PRegEx_ExtractIntoSPList(["a b c d e"], "(\w) (\w) (\w) (\w) (\w)", "" ),     ["a":"b", "c":"d", "e":void    ])) then Blech "PRegEx_ExtractIntoSPList 401" && PRegEx_CompiledOK()
      
      if iterNum mod 200 = 0 then -- measure memory after 1/50th of the iterations
        if fBytes = void then set fBytes = the freeBytes
        -- put the freeBytes -- remember: uncommenting this uses up memory in the Message window's buffer!
      end if
    end repeat
    -- Measure memory again after all 100% of iterations have happened.  There should be no change.
    if abs(fBytes - the freeBytes)>100 then Blech "PRegEx_ExtractIntoSPList Leak" && (the freeBytes - fBytes)
  end if
  
end Test_PRegEx_ExtractIntoSPList