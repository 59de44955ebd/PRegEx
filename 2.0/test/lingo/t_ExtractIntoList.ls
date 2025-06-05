on Test_PRegEx_ExtractIntoList
  if not(ListEQ(re_extract            (["a b c d e"], "(\w) (\w) (\w) (\w)", ""), ["a", "b", "c", "d"])) then Blech "PRegEx_ExtractIntoList 101" && PRegEx_CompiledOK()
  if not(ListEQ(PRegEx_ExtractIntoList(["a b ç d e"], "(\w) (\w) (\pL) (\w)", ""), ["a", "b", "ç", "d"])) then Blech "PRegEx_ExtractIntoList 101" && PRegEx_CompiledOK()

  -- global
  if not(ListEQ(PRegEx_ExtractIntoList(["a b c d e"], "(\w) (\w) (\w) (\w)", "g"), ["a", "b", "c", "d"])) then Blech "PRegEx_ExtractIntoList 201" && PRegEx_CompiledOK()
  if not(ListEQ(PRegEx_ExtractIntoList(["a b c d e "], "(\w) ", "g"),  ["a", "b", "c", "d", "e"])) then Blech "PRegEx_ExtractIntoList 202" && PRegEx_CompiledOK()
  if not(ListEQ(PRegEx_ExtractIntoList(["a b c d e  "], "(\w) ", "g"), ["a", "b", "c", "d", "e"])) then Blech "PRegEx_ExtractIntoList 203" && PRegEx_CompiledOK()
  
  if not(ListEQ(PRegEx_ExtractIntoList(["a b c d e     "], "(\w) ", "g"), ["a", "b", "c", "d", "e"])) then Blech "PRegEx_ExtractIntoList 204" && PRegEx_CompiledOK()
  
  -- Testing matching and extraction of strings with null characters in them.
  set aString      = ["Hi" & numtochar(0) & "Mom"]
  set aString[2] = length(aString[1])
  if not(ListEQ(PRegEx_ExtractIntoList(aString, "(\w+)\W+(\w+)", ""), ["Hi", "Mom"])) then Blech "PRegEx_ExtractIntoList 301" && PRegEx_CompiledOK()
  if not(ListEQ(PRegEx_ExtractIntoList(aString, "(.+)", ""),                      [aString[1]                             ])) then Blech "PRegEx_ExtractIntoList 302" && PRegEx_CompiledOK()
  if not(ListEQ(PRegEx_ExtractIntoList(aString, "(\0)", ""),                      [numtochar(0)                           ])) then Blech "PRegEx_ExtractIntoList 303" && PRegEx_CompiledOK()
  
  -- Testing REs that match a zero-width string (ensure Pos advances 1 char each time when in global mode).
  if not ListEQ(PRegEx_ExtractIntoList(["foo"], "(.*?)", "g"), ["", "", "", ""]) then Blech "PRegEx_ExtractIntoList 304"
  if not ListEQ(PRegEx_ExtractIntoList(["foo"], ".?", "g"), []) then Blech "PRegEx_ExtractIntoList 305"
  
  -- leak test
  if (LeakTestingSelected()) then
    set fBytes = void
    repeat with iterNum = 1 to 10000
      
      set xList = []
      if not(ListEQ(PRegEx_ExtractIntoList(["a"], "(\w)", "g", xList), ["a"])) then Blech "PRegEx_ExtractIntoList 400a" && PRegEx_CompiledOK()
      if not(ListEQ(PRegEx_ExtractIntoList(["a"], "(\w)", "g", xList), ["a", "a"])) then Blech "PRegEx_ExtractIntoList 400b" && PRegEx_CompiledOK()
      if not(ListEQ(PRegEx_ExtractIntoList(["a b c d e  "], "(\w) ", "g"), ["a", "b", "c", "d", "e"])) then Blech "PRegEx_ExtractIntoList 403" && PRegEx_CompiledOK()
      
      if iterNum mod 200 = 0 then -- measure memory after 1/50th of the iterations
        if fBytes = void then set fBytes = the freeBytes
        -- put the freeBytes -- remember: uncommenting this uses up memory in the Message window's buffer!
      end if
    end repeat
    -- Measure memory again after all 100% of iterations have happened.  There should be no change.
    if abs(fBytes - the freeBytes)>100 then Blech "PRegEx_ExtractIntoList Leak" && (the freeBytes - fBytes)
  end if
  
end Test_PRegEx_ExtractIntoList