on Test_PRegEx_Split
  set mySampleArgList = [2, "a", #foo, ["abc"], [1:2]]
  
  if (not(ListEQ(re_split    (["1b2c3d4e5"], "[a-z]", "g"), ["1", "2", "3", "4", "5"]))) then Blech("Test_PRegEx_Split 101")
  if (not(ListEQ(PRegEx_Split(["1b2c3d4e5"], "[a-z]", "g"), ["1", "2", "3", "4", "5"]))) then Blech("Test_PRegEx_Split 101")
  if (not(ListEQ(PRegEx_Split(["1b2c3d4e5"], "\d", "g"), ["", "b", "c", "d", "e"]))) then Blech("Test_PRegEx_Split 102")
  if (not(ListEQ(PRegEx_Split(["1b2c3∂4é5"], "(\d)", "g"), ["", "1", "b", "2", "c", "3", "∂", "4", "é", "5"]))) then Blech("Test_PRegEx_Split 103")
  if (not(ListEQ(PRegEx_Split(["1b2c3d4e5"], "(\d)", ""), ["", "1", "b2c3d4e5"]))) then Blech("Test_PRegEx_Split 104")
  if (not(ListEQ(PRegEx_Split(["1b2c3d4e5"], "(\d)", "g", [], -1), ["", "1", "b", "2", "c", "3", "d", "4", "e", "5", ""]))) then Blech("Test_PRegEx_Split 105")
  
  -- leak test
  if (LeakTestingSelected()) then
    set fBytes = void
    repeat with iterNum = 1 to 10000
      if (not(ListEQ(PRegEx_Split(["1b2c3d4e5"], "[a-z]", "g"), ["1", "2", "3", "4", "5"]))) then Blech("Test_PRegEx_Split 201")
      if (not(ListEQ(PRegEx_Split(["1b2c3d4e5"], "(\d)", "g", [], -1), ["", "1", "b", "2", "c", "3", "d", "4", "e", "5", ""]))) then Blech("Test_PRegEx_Split 203")
      
      if iterNum mod 200 = 0 then -- measure memory after 1/50th of the iterations
        if fBytes = void then set fBytes = the freeBytes
        -- put the freeBytes -- remember: uncommenting this uses up memory in the Message window's buffer!
      end if
    end repeat
    -- Measure memory again after all 100% of iterations have happened.  There should be no change.
    if abs(fBytes - the freeBytes)>100 then Blech "Test_PRegEx_Split Leak" && (the freeBytes - fBytes)
  end if
  
end Test_PRegEx_Split
