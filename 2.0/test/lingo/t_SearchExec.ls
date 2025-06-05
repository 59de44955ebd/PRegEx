on Test_PRegEx_SearchExec
  set myList = ["a"]
  if (PRegEx_SearchExec(["Hi chî Chî"], "chî",        "ig",      #ListAdder,  [myList]) <> 2) then Blech "PRegEx_SearchExec 101" && PRegEx_CompiledOK()
  if (not(ListEQ(myList, ["a", "chî", "Chî"])))                                              then Blech "PRegEx_SearchExec 102" && PRegEx_CompiledOK()
  set myList = ["a"]
  if (re_search               (["Hi ch Ch"], "ch",        "ige",   #ListAdder,    [myList]) <> 2) then Blech "PRegEx_SearchExec 101" && PRegEx_CompiledOK()
  if (not(ListEQ(myList, ["a", "ch", "Ch"])))                                                     then Blech "PRegEx_SearchExec 102" && PRegEx_CompiledOK()
  set myList = ["a"]
  if (re_m                        (["Hi ch Ch"], "ch",        "ige",   #ListAdder,    [myList]) <> 2) then Blech "PRegEx_SearchExec 101" && PRegEx_CompiledOK()
  if (not(ListEQ(myList, ["a", "ch", "Ch"])))                                                         then Blech "PRegEx_SearchExec 102" && PRegEx_CompiledOK()
  
  -- leak test
  if (LeakTestingSelected()) then
    set fBytes = void
    repeat with iterNum = 1 to 10000
      set myList = ["a"]
      if (PRegEx_SearchExec(["Hi ch Ch"], "ch",        "ig",      #ListAdder,  [myList]) <> 2) then Blech "PRegEx_SearchExec 403" && PRegEx_CompiledOK()
      
      if iterNum mod 200 = 0 then -- measure memory after 1/50th of the iterations
        if fBytes = void then set fBytes = the freeBytes
        -- put the freeBytes -- remember: uncommenting this uses up memory in the Message window's buffer!
      end if
    end repeat
    -- Measure memory again after all 100% of iterations have happened.  There should be no change.
    if abs(fBytes - the freeBytes)>100 then Blech "PRegEx_SearchExec Leak" && (the freeBytes - fBytes)
  end if
  
end Test_PRegEx_SearchExec