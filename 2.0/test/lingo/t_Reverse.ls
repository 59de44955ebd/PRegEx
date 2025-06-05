on Test_PRegEx_Reverse
  if not ListEQ(re_reverse    ([[1:2],[],#c,#w,4,"a"]), ["a", 4, #w, #c, [], [1: 2]]) then Blech("Test_PRegEx_Reverse 101")
  if not ListEQ(PRegEx_Reverse([[1:2],[],#c,#w,4,"a"]), ["a", 4, #w, #c, [], [1: 2]]) then Blech("Test_PRegEx_Reverse 101")
  if not ListEQ(PRegEx_Reverse([1]), [1]) then Blech("Test_PRegEx_Reverse 102")
  if not ListEQ(PRegEx_Reverse([2,1]), [1,2]) then Blech("Test_PRegEx_Reverse 103")
  if not ListEQ(PRegEx_Reverse([3,2,1]), [1,2,3]) then Blech("Test_PRegEx_Reverse 104")
  if not ListEQ(PRegEx_Reverse([4,3,2,1]), [1,2,3,4]) then Blech("Test_PRegEx_Reverse 105")
  if not ListEQ(PRegEx_Reverse([5,4,3,2,1]), [1,2,3,4,5]) then Blech("Test_PRegEx_Reverse 106")
  if not ListEQ(PRegEx_Reverse([5,4,3,2,1,"ü"]), ["ü",1,2,3,4,5]) then Blech("Test_PRegEx_Reverse 106")
  
  -- leak test
  if (LeakTestingSelected()) then
    set fBytes = void
    repeat with iterNum = 1 to 10000
      if not ListEQ(PRegEx_Reverse([[1:2],[],#c,#w,4,"a"]), ["a", 4, #w, #c, [], [1: 2]]) then Blech("Test_PRegEx_Reverse 101")
      
      if iterNum mod 200 = 0 then -- measure memory after 1/50th of the iterations
        if fBytes = void then set fBytes = the freeBytes
        -- put the freeBytes -- remember: uncommenting this uses up memory in the Message window's buffer!
      end if
    end repeat
    -- Measure memory again after all 100% of iterations have happened.  There should be no change.
    if abs(fBytes - the freeBytes)>100 then Blech "Test_PRegEx_Reverse Leak" && (the freeBytes - fBytes)
  end if
  
end Test_PRegEx_Reverse
