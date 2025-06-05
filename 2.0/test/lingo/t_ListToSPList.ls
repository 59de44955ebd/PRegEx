on Test_PRegEx_ListToSPList                  -- List, [InitPList]) ==> SPList
  if (not(ListEQ(re_hash            ([#a, 2, #b, 4]), [#a: 2, #b: 4]))) then Blech "Test_PRegEx_ListToSPList 101"
  if (not(ListEQ(PRegEx_ListToSPList([#a, 2, #b, 4]), [#a: 2, #b: 4]))) then Blech "Test_PRegEx_ListToSPList 101"
  if (not(ListEQ(PRegEx_ListToSPList([#b, "√", #a, 2]), [#a: 2, #b: "√"]))) then Blech "Test_PRegEx_ListToSPList 101b"
  
  set myList = [#coo: 2, #aardvark: 4]
  if (not(ListEQ(PRegEx_ListToSPList([#a, 2, #b, 4], myList), [#a: 2, #aardvark: 4, #b: 4, #coo: 2]))) then Blech "PRegEx_ListToSPList 103a"
  if (not(ListEQ(myList, [#a: 2, #aardvark: 4, #b: 4, #coo: 2]))) then Blech "PRegEx_ListToSPList 103b"
  
  -- leak test
  if (LeakTestingSelected()) then
    set fBytes = void
    repeat with iterNum = 1 to 10000
      if (not(ListEQ(PRegEx_ListToSPList([#a, 2, #b, 4]), [#a: 2, #b: 4]))) then Blech "Test_PRegEx_ListToSPList 101"
      if (not(ListEQ(PRegEx_ListToSPList([#b, 4, #a, 2]), [#a: 2, #b: 4]))) then Blech "Test_PRegEx_ListToSPList 101b"
      
      if iterNum mod 200 = 0 then -- measure memory after 1/50th of the iterations
        if fBytes = void then set fBytes = the freeBytes
        -- put iterNum && the freeBytes -- remember: uncommenting this uses up memory in the Message window's buffer!
      end if
    end repeat
    -- Measure memory again after all 100% of iterations have happened.  There should be no change.
    if abs(fBytes - the freeBytes)>100 then Blech "PRegEx_ListToSPList Leak" && (the freeBytes - fBytes)
  end if
end Test_PRegEx_ListToSPList
