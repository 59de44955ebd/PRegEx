on Test_PRegEx_SetSlice                     -- List, Keys, Values) ==> List
  if (not(ListEQ(re_slice_set   ([#a:1], [#d, #c, #b], [2, 3, 4]), [#a:1, #b:4, #c:3, #d:2]))) then Blech "Test_PRegEx_SetSlice 101"
  if (not(ListEQ(PRegEx_SetSlice([#a:1], [#d, #c, #b], [2, 3, 4]), [#a:1, #b:4, #c:3, #d:2]))) then Blech "Test_PRegEx_SetSlice 101"
  if (not(ListEQ(PRegEx_SetSlice([#a, #b], [2, 4, 3], ["dog", "c™t", "cow"]), [#a, "dog", "cow", "c™t"]))) then Blech "Test_PRegEx_SetSlice 102"
  
  set myList = [#a:1]
  if (not(ListEQ(PRegEx_SetSlice(myList, [#d, #c, #b], [2, 3, 4]), [#a:1, #b:4, #c:3, #d:2]))) then Blech "Test_PRegEx_SetSlice 105a"
  if (not(ListEQ(myList, [#a:1, #b:4, #c:3, #d:2]))) then Blech "Test_PRegEx_SetSlice 105b"
  
  -- leak test
  if (LeakTestingSelected()) then
    set fBytes = void
    repeat with iterNum = 1 to 10000
      if (not(ListEQ(PRegEx_SetSlice([#a:1], [#d, #c, #b], [2, 3, 4]), [#a:1, #b:4, #c:3, #d:2]))) then Blech "Test_PRegEx_SetSlice 101"
      if (not(ListEQ(PRegEx_SetSlice([#a, #b], [2, 4, 3], ["dog", "cat", "cow"]), [#a, "dog", "cow", "cat"]))) then Blech "Test_PRegEx_SetSlice 102"
      
      if iterNum mod 200 = 0 then -- measure memory after 1/50th of the iterations
        if fBytes = void then set fBytes = the freeBytes
        -- put iterNum && the freeBytes -- remember: uncommenting this uses up memory in the Message window's buffer!
      end if
    end repeat
    -- Measure memory again after all 100% of iterations have happened.  There should be no change.
    if abs(fBytes - the freeBytes)>100 then Blech "PRegEx_SetSlice Leak" && (the freeBytes - fBytes)
  end if
  
end Test_PRegEx_SetSlice
