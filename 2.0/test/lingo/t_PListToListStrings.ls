on Test_PRegEx_PListToListStrings                        -- PList, [InitList]) ==> List
  
  if (not(ListEQ(re_list_strs             ([#a: 2, #b: 4]), ["a", 2, "b", 4]))) then Blech "Test_PRegEx_PListToListStrings 101"
  if (not(ListEQ(PRegEx_PListToListStrings([#a: 2, #b: 4]), ["a", 2, "b", 4]))) then Blech "Test_PRegEx_PListToListStrings 101"
  if (not(ListEQ(PRegEx_PListToListStrings([#a: 2, #b: 4], ["dög", "cat"]), ["dög", "cat", "a", 2, "b", 4]))) then Blech "Test_PRegEx_PListToListStrings 102"
  
  set myList = ["dog", "cat"]
  if (not(ListEQ(PRegEx_PListToListStrings([#a: 2, #b: 4], myList), ["dog", "cat", "a", 2, "b", 4]))) then Blech "Test_PRegEx_PListToListStrings 103a"
  if (not(ListEQ(myList, ["dog", "cat", "a", 2, "b", 4]))) then Blech "Test_PRegEx_PListToListStrings 103b"
  
  -- leak test
  if (LeakTestingSelected()) then
    set fBytes = void
    repeat with iterNum = 1 to 10000
      if (not(ListEQ(PRegEx_PListToListStrings([#a: 2, #b: 4]), ["a", 2, "b", 4]))) then Blech "Test_PRegEx_PListToListStrings 101"
      if (not(ListEQ(PRegEx_PListToListStrings([#a: 2, #b: 4], ["dog", "cat"]), ["dog", "cat", "a", 2, "b", 4]))) then Blech "Test_PRegEx_PListToListStrings 102"
      
      if iterNum mod 200 = 0 then -- measure memory after 1/50th of the iterations
        if fBytes = void then set fBytes = the freeBytes
        -- put iterNum && the freeBytes -- remember: uncommenting this uses up memory in the Message window's buffer!
      end if
    end repeat
    -- Measure memory again after all 100% of iterations have happened.  There should be no change.
    if abs(fBytes - the freeBytes)>100 then Blech "PRegEx_PListToListStrings Leak" && (the freeBytes - fBytes)
  end if
end Test_PRegEx_PListToListStrings