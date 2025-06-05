on Test_PRegEx_ListToSPListSym               -- List, [InitPList]) ==> SPList
  if (not(ListEQ(re_hash_syms          (["a", "dog", "b", "bo≈", #c, 2]), [#a: "dog", #b: "bo≈", #c: 2]))) then Blech "Test_PRegEx_ListToSPListSym 101"
  if (not(ListEQ(PRegEx_ListToSPListSym(["a", "dog", "b", "box", #c, 2]), [#a: "dog", #b: "box", #c: 2]))) then Blech "Test_PRegEx_ListToSPListSym 101"
  if (not(ListEQ(PRegEx_ListToSPListSym([#b, 4, #a, 2]), [#a: 2, #b: 4]))) then Blech "Test_PRegEx_ListToSPListSym 101b"
  
  set myList = [#coo: 2, #aardvark: 4]
  if (not(ListEQ(PRegEx_ListToSPListSym(["a", 2, "b", 4], myList), [#a: 2, #aardvark: 4, #b: 4, #coo: 2]))) then Blech "PRegEx_ListToSPListSym 103a"
  if (not(ListEQ(myList, [#a: 2, #aardvark: 4, #b: 4, #coo: 2]))) then Blech "PRegEx_ListToSPListSym 103b"
  
  -- leak test
  if (LeakTestingSelected()) then
    set fBytes = void
    repeat with iterNum = 1 to 10000
      if (not(ListEQ(PRegEx_ListToSPListSym(["a", "dog", "b", "box", #c, 2]), [#a: "dog", #b: "box", #c: 2]))) then Blech "Test_PRegEx_ListToSPListSym 101"
      if (not(ListEQ(PRegEx_ListToSPListSym([#b, 4, #a, 2]), [#a: 2, #b: 4]))) then Blech "Test_PRegEx_ListToSPListSym 101b"
      
      if iterNum mod 200 = 0 then -- measure memory after 1/50th of the iterations
        if fBytes = void then set fBytes = the freeBytes
        -- put iterNum && the freeBytes -- remember: uncommenting this uses up memory in the Message window's buffer!
      end if
    end repeat
    -- Measure memory again after all 100% of iterations have happened.  There should be no change.
    if abs(fBytes - the freeBytes)>100 then Blech "PRegEx_ListToSPListSym Leak" && (the freeBytes - fBytes)
  end if
end Test_PRegEx_ListToSPListSym
