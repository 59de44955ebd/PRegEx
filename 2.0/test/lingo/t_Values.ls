on Test_PRegEx_Values                        -- PList, [InitList]) ==> ValueList
  if (not(ListEQ(re_values    ([#a:10,#b:11,#c:12]                                ), [                            10, 11, 12]))) then Blech "Test_PRegEx_Values 101"
  if (not(ListEQ(PRegEx_Values([#a:10,#b:11,#c:12]                                ), [                            10, 11, 12]))) then Blech "Test_PRegEx_Values 101"
  if (not(ListEQ(PRegEx_Values([#a:10,#b:11,#c:12], ["dog", "cøw"]), ["dog", "cøw", 10, 11, 12]))) then Blech "Test_PRegEx_Values 102"
  if (not(ListEQ(PRegEx_Values([#a:10,#b:11,#c:12], []), [10, 11, 12]))) then Blech "PRegEx_Values 102b"
  if (not(ListEQ(PRegEx_Values([:]                                ), []))) then Blech "PRegEx_Values 103"
  if (not(ListEQ(PRegEx_Values([:]        ,[]), []))) then Blech "PRegEx_Values 104"
  if (not(ListEQ(PRegEx_Values([:]        ,[1,2,4]), [1,2,4]))) then Blech "PRegEx_Values 105"
  
  set myList = []
  if (not(ListEQ(PRegEx_Values([#a:10,#b:11,#c:12], myList), [10, 11, 12]))) then Blech "PRegEx_Values 106a"
  if (not(ListEQ(myList, [10, 11, 12]))) then Blech "PRegEx_Values 106b"
  
  -- leak test
  if (LeakTestingSelected()) then
    set fBytes = void
    repeat with iterNum = 1 to 10000
      
      if (not(ListEQ(PRegEx_Values([#a:10,#b:11,#c:12], ["dog", "cow"]), ["dog", "cow", 10, 11, 12]))) then Blech "Test_PRegEx_Values 102"
      if (not(ListEQ(PRegEx_Values([:]                                ), []))) then Blech "PRegEx_Values 103"
      
      if iterNum mod 200 = 0 then -- measure memory after 1/50th of the iterations
        if fBytes = void then set fBytes = the freeBytes
        -- put iterNum && the freeBytes -- remember: uncommenting this uses up memory in the Message window's buffer!
      end if
    end repeat
    -- Measure memory again after all 100% of iterations have happened.  There should be no change.
    if abs(fBytes - the freeBytes)>100 then Blech "PRegEx_Values Leak" && (the freeBytes - fBytes)
  end if
end Test_PRegEx_Values