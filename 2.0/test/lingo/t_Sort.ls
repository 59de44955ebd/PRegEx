on Test_PRegEx_Sort
  
  if not ListEQ(re_sort    ([1,3,2], 0, #PlainSort), [1,2,3]) then Blech("Test_PRegEx_Sort 101a")
  if not ListEQ(PRegEx_Sort([1,3,2], 0, #PlainSort), [1,2,3]) then Blech("Test_PRegEx_Sort 101b")
  if not ListEQ(PRegEx_Sort([3,2,1], 1, #PlainSort), [1,2,3]) then Blech("Test_PRegEx_Sort 102")
  if not ListEQ(PRegEx_Sort([#a, #c, #b], 1, #InListSort, [#c:1, #d:1]), [#c, #a, #b]) then Blech("Test_PRegEx_Sort 103")
  if not ListEQ(PRegEx_Sort([#a, #c, #b], 1, #InListSort, [#c:1, #b:1]), [#c, #b, #a]) then Blech("Test_PRegEx_Sort 104a")
  if not ListEQ(PRegEx_Sort([#a, #c, #b], 1, #SymbolSort, [#c:1, #b:1]), [#a, #b, #c]) then Blech("Test_PRegEx_Sort 104b")
  if not ListEQ(PRegEx_Sort([3,"Ω",2,1], 1, #PlainSort), [1,2,3,"Ω"]) then Blech("Test_PRegEx_Sort 105")
  
  -- leak test
  if (LeakTestingSelected()) then
    set fBytes = void
    repeat with iterNum = 1 to 10000
      if not ListEQ(PRegEx_Sort([3,2,1], 1, #PlainSort), [1,2,3]) then Blech("Test_PRegEx_Sort 102")
      --if not ListEQ(PRegEx_Sort([#a, #c, #b], 1, #SymbolSort, [#c:1, #b:1]), [#a, #b, #c]) then Blech("Test_PRegEx_Sort 104")
      
      if iterNum mod 200 = 0 then -- measure memory after 1/50th of the iterations
        if fBytes = void then set fBytes = the freeBytes
        -- put the freeBytes -- remember: uncommenting this uses up memory in the Message window's buffer!
      end if
    end repeat
    -- Measure memory again after all 100% of iterations have happened.  There should be no change.
    if abs(fBytes - the freeBytes)>100 then Blech "Test_PRegEx_Sort Leak" && (the freeBytes - fBytes)
  end if
  
end Test_PRegEx_Sort
