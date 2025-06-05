on Test_PRegEx_CopyList
  -- Non-Deep Copy
  set aListOrig   = ["a", "b", "ç", [1:2, #c: ["a":"b"]]]
  set aList       = ["a", "b", "ç", [1:2, #c: ["a":"b"]]]
  set aListMod    = ["a", "x", "ç", [1:2, #c: ["a":"b"]]]
  set bList       = PRegEx_CopyList([1,2, aList])
  set aList[2]    = "x"
  
  if (not(ListEQ(bList, [1,2,aListMod]))) then Blech("Test_PRegEx_CopyList 101")
  
  -- Deep Copy
  set aListOrig   = ["a", "b", "ç", [1:2, #c: ["a":"b"]]]
  set aList       = ["a", "b", "ç", [1:2, #c: ["a":"b"]]]
  set aListMod    = ["a", "x", "ç", [1:2, #c: ["a":"b"]]]
  set bList       = PRegEx_CopyList([1,2, aList], 1)
  set aList[2]    = "x"
  
  if (not(ListEQ(bList, [1,2,aListOrig]))) then Blech("Test_PRegEx_CopyList 102")
  
  -- Copying several kinds of lists.
  
  if (not(ListEQ(re_copy        ([:], 1), [:]))) then Blech("Test_PRegEx_CopyList 201")
  if (not(ListEQ(PRegEx_CopyList([:], 1), [:]))) then Blech("Test_PRegEx_CopyList 201")
  if (not(ListEQ(PRegEx_CopyList([], 1), []))) then Blech("Test_PRegEx_CopyList 202")
  if (not(ListEQ(PRegEx_CopyList(["a":[]], 1), ["a":[]]))) then Blech("Test_PRegEx_CopyList 203")
  if (not(ListEQ(PRegEx_CopyList([#c,2,[1],[1:"f"]], 1), [#c,2,[1],[1:"f"]]))) then Blech("Test_PRegEx_CopyList 204")
  
  -- leak test
  if (LeakTestingSelected()) then
    set fBytes = void
    repeat with iterNum = 1 to 10000
      if (not(ListEQ(PRegEx_CopyList(["a":[]], 1), ["a":[]]))) then Blech("Test_PRegEx_CopyList 203")
      if (not(ListEQ(PRegEx_CopyList([#c,2,[1],[1:"f"]], 1), [#c,2,[1],[1:"f"]]))) then Blech("Test_PRegEx_CopyList 204")
      
      if iterNum mod 200 = 0 then -- measure memory after 1/50th of the iterations
        if fBytes = void then set fBytes = the freeBytes
        -- put the freeBytes -- remember: uncommenting this uses up memory in the Message window's buffer!
      end if
    end repeat
    -- Measure memory again after all 100% of iterations have happened.  There should be no change.
    if abs(fBytes - the freeBytes)>100 then Blech "Test_PRegEx_CopyList Leak" && (the freeBytes - fBytes)
  end if
  
end Test_PRegEx_CopyList
