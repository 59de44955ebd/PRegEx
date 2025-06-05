on Test_PRegEx_GetSlice                      -- List, Keys, [InitList]) ==> SliceList
  if (not(ListEQ(re_slice       ([#a       ,#b     ,#c     ], [3,  2]), [#c,#b]))) then Blech "Test_PRegEx_GetSlice 101"
  if (not(ListEQ(PRegEx_GetSlice([#a   ,#b     ,#c     ], [3,  2]), [#c,#b]))) then Blech "Test_PRegEx_GetSlice 101"
  if (not(ListEQ(PRegEx_GetSlice([#a:10,#b:11,#c:12], [#b,#a]), [11,10]))) then Blech "Test_PRegEx_GetSlice 102"
  if (not(ListEQ(PRegEx_GetSlice([#a:10,#b:11,#c:12], [#b,#a], ["foo", "bar"]), ["foo", "bar", 11,10]))) then Blech "Test_PRegEx_GetSlice 103"
  if (not(ListEQ(PRegEx_GetSlice([#a:10,#b:"é",#c:12], [#b,#a]), ["é",10]))) then Blech "Test_PRegEx_GetSlice 104"
    
  set myList = []
  if (not(ListEQ(PRegEx_GetSlice([#a:10,#b:11,#c:12], [#b,#a], myList), [11,10]))) then Blech "Test_PRegEx_GetSlice 104a"
  if (not(ListEQ(myList, [11,10]))) then Blech "Test_PRegEx_GetSlice 104b"
  
  -- leak test
  if (LeakTestingSelected()) then
    set fBytes = void
    repeat with iterNum = 1 to 10000
      
      if (not(ListEQ(PRegEx_GetSlice([#a   ,#b     ,#c     ], [3,  2]), [#c,#b]))) then Blech "Test_PRegEx_GetSlice 101"
      if (not(ListEQ(PRegEx_GetSlice([#a:10,#b:11,#c:12], [#b,#a]), [11,10]))) then Blech "Test_PRegEx_GetSlice 102"
      if (not(ListEQ(PRegEx_GetSlice([#a:10,#b:11,#c:12], [#b,#a], ["foo", "bar"]), ["foo", "bar", 11,10]))) then Blech "Test_PRegEx_GetSlice 103"
      
      if iterNum mod 200 = 0 then -- measure memory after 1/50th of the iterations
        if fBytes = void then set fBytes = the freeBytes
        -- put iterNum && the freeBytes -- remember: uncommenting this uses up memory in the Message window's buffer!
      end if
    end repeat
    -- Measure memory again after all 100% of iterations have happened.  There should be no change.
    if abs(fBytes - the freeBytes)>100 then Blech "PRegEx_GetSlice Leak" && (the freeBytes - fBytes)
  end if
  
end Test_PRegEx_GetSlice