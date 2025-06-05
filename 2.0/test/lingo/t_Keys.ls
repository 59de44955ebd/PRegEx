on Test_PRegEx_Keys                      -- PList, [InitList]) ==> KeyList
  if (not(ListEQ(re_keys    ([#a:10,#b:11,#c:12]                              ), [                            #a, #b, #c]))) then Blech "Test_PRegEx_Keys 101"
  if (not(ListEQ(PRegEx_Keys([#a:10,#b:11,#c:12]                              ), [                            #a, #b, #c]))) then Blech "Test_PRegEx_Keys 101"
  if (not(ListEQ(PRegEx_Keys([#a:10,#b:11,#c:12], ["dög", "cow"]), ["dög", "cow", #a, #b, #c]))) then Blech "Test_PRegEx_Keys 102"
  if (not(ListEQ(PRegEx_Keys([#a:10,#b:11,#c:12], []), [#a, #b, #c]))) then Blech "Test_PRegEx_Keys 102b"
  if (not(ListEQ(PRegEx_Keys([:]                              ), []))) then Blech "Test_PRegEx_Keys 103"
  if (not(ListEQ(PRegEx_Keys([:]      ,[]), []))) then Blech "Test_PRegEx_Keys 104"
  if (not(ListEQ(PRegEx_Keys([:]      ,[1,2,4]), [1,2,4]))) then Blech "Test_PRegEx_Keys 105"
  
  set myList = []
  if (not(ListEQ(PRegEx_Keys([#a:10,#b:11,#c:12], myList), [#a, #b, #c]))) then Blech "PRegEx_Keys 106a"
  if (not(ListEQ(myList, [#a, #b, #c]))) then Blech "PRegEx_Keys 106b"
  
  -- leak test
  if (LeakTestingSelected()) then
    set fBytes = void
    repeat with iterNum = 1 to 10000
      
      if (not(ListEQ(PRegEx_Keys([#a:10,#b:11,#c:12], ["dog", "cow"]), ["dog", "cow", #a, #b, #c]))) then Blech "Test_PRegEx_Keys 102"
      if (not(ListEQ(PRegEx_Keys([:]                              ), []))) then Blech "Test_PRegEx_Keys 103"
      
      if iterNum mod 200 = 0 then -- measure memory after 1/50th of the iterations
        if fBytes = void then set fBytes = the freeBytes
        -- put iterNum && the freeBytes -- remember: uncommenting this uses up memory in the Message window's buffer!
      end if
    end repeat
    -- Measure memory again after all 100% of iterations have happened.  There should be no change.
    if abs(fBytes - the freeBytes)>100 then Blech "PRegEx_Keys Leak" && (the freeBytes - fBytes)
  end if
end Test_PRegEx_Keys
