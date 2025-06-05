on Test_PRegEx_Grep
  
  -- Callback / #FilterFunction mode
  if (not(ListEQ(re_grep    ([1, "b", 3, "c", -2, 1.2], #IsLessThan, 2), [1, -2, 1.2000]))) then Blech("Test_PRegEx_Grep 101")
  if (not(ListEQ(PRegEx_Grep([1, "b", 3, "c", -2, 1.2], #IsLessThan, 2), [1, -2, 1.2000]))) then Blech("Test_PRegEx_Grep 101")
  if (not(ListEQ(PRegEx_Grep([1, "b", 3, "c", -2, 1.2], #IsLessThan, [2]), [1, -2, 1.2000]))) then Blech("Test_PRegEx_Grep 102")
  if (not(ListEQ(PRegEx_Grep([1, "b", 3, "c", -2, 1.2], #IsLessThan, [2, 3]), [1, -2, 1.2000]))) then Blech("Test_PRegEx_Grep 103")
  if (not(ListEQ(PRegEx_Grep([1, "b", 3, "c", -2, 1.2], #IsLessThan, [2.5, 4]), [1, -2, 1.2000]))) then Blech("Test_PRegEx_Grep 1041")
  if (not(ListEQ(PRegEx_Grep([1, "b", 3, "c", -2, 1.2], #IsLessThan, 1), [-2]))) then Blech("Test_PRegEx_Grep 105")
  if (not(ListEQ(PRegEx_Grep([1, "b", 3, "c", -2, 1.2, "ü"], #IsString, 1), ["b", "c", "ü"]))) then Blech("Test_PRegEx_Grep 106")
  if (not(ListEQ(PRegEx_Grep([1, "b", 3, "c", -2, 1.2], #stringP), ["b", "c"]))) then Blech("Test_PRegEx_Grep 107")
  if (not(ListEQ(PRegEx_Grep([1, "b", 3, "c", -2, 1.2], #IsPositive, 1), [1,3,1.2]))) then Blech("Test_PRegEx_Grep 108")
  if (not(ListEQ(PRegEx_Grep([1, "b", 3, "c", -2, 1.2], #IsPositive, 1), [1,3,1.2]))) then Blech("Test_PRegEx_Grep 109")
  if (not(ListEQ(PRegEx_Grep([1, "b", 3, "c", -2, 1.2], #integerP), [1,3,-2]))) then Blech("Test_PRegEx_Grep 110")
  if (not(ListEQ(PRegEx_Grep([1], #undef), []) and PRegEx_LastErrCode() = PRegEx_ErrCode_CallbackFunctionFailed())) then Blech("Test_PRegEx_Grep 111")
  if (not(ListEQ(PRegEx_Grep([:], #FooBang), []) and PRegEx_LastErrCode() = PRegEx_ErrCode_ExpectedListArgument())) then Blech("Test_PRegEx_Grep 112")
  
  -- PRegEx matching mode
  if (not(ListEQ(re_grep    ([["a"], ["b"], ["c"]], "[a-b]"), [["a"], ["b"]]))) then Blech("Test_PRegEx_Grep 201")
  if (not(ListEQ(PRegEx_Grep([["a"], ["b"], ["c"]], "[a-b]"), [["a"], ["b"]]))) then Blech("Test_PRegEx_Grep 201")
  if (not(ListEQ(PRegEx_Grep([["a"], ["b"], ["c"]], "[A-B]", "i"), [["a"], ["b"]]))) then Blech("Test_PRegEx_Grep 202")
  if (not(ListEQ(PRegEx_Grep([["a"], ["b"], ["c"]], "[A-B]", ""), []))) then Blech("Test_PRegEx_Grep 203")
  if (not(ListEQ(PRegEx_Grep([["a"], ["b"], ["c"]], "[A-B]"), []))) then Blech("Test_PRegEx_Grep 204")
  
  if (not(ListEQ(PRegEx_Grep(["a", "b", "c"], "[a-b]"), ["a", "b"]))) then Blech("Test_PRegEx_Grep 206")
  if (not(ListEQ(PRegEx_Grep(["a", "b", "c"], "[A-B]", "i"), ["a", "b"]))) then Blech("Test_PRegEx_Grep 206")
  if (not(ListEQ(PRegEx_Grep(["a", "b", "c"], "[A-B]", ""), []))) then Blech("Test_PRegEx_Grep 207")
  if (not(ListEQ(PRegEx_Grep(["a", "b", "c"], "[A-B]"), []))) then Blech("Test_PRegEx_Grep 208")
  
  if (not(ListEQ(PRegEx_Grep([2, "a", #foo, ["abc"], [1:2]], "\w"), ["a", ["abc"]]))) then Blech("Test_PRegEx_Grep 209")
  
  -- leak test
  if (LeakTestingSelected()) then
    set fBytes = void
    repeat with iterNum = 1 to 10000
      if (not(ListEQ(PRegEx_Grep([1, "b", 3, "c", -2, 1.2], #IsLessThan, 2), [1, -2, 1.2000]))) then Blech("Test_PRegEx_Grep 301")
      if (not(ListEQ(PRegEx_Grep([2, "a", #foo, ["abc"], [1:2]], "\w"), ["a", ["abc"]]))) then Blech("Test_PRegEx_Grep 302")
      
      if iterNum mod 200 = 0 then -- measure memory after 1/50th of the iterations
        if fBytes = void then set fBytes = the freeBytes
        -- put the freeBytes -- remember: uncommenting this uses up memory in the Message window's buffer!
      end if
    end repeat
    -- Measure memory again after all 100% of iterations have happened.  There should be no change.
    if abs(fBytes - the freeBytes)>100 then Blech "Test_PRegEx_Grep Leak" && (the freeBytes - fBytes)
  end if
  
end Test_PRegEx_Grep

