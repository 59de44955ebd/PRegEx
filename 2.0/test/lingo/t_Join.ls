on Test_PRegEx_Join
  
  if (re_join    (["a", "", "b", ""], "3") <> "a33b3") then Blech("Test_PRegEx_Join 101")
  
  if (PRegEx_Join(["a", "", "b", "", "é"], "3") <> "a33b33é") then Blech("Test_PRegEx_Join 101")
  if (PRegEx_Join(["", "a", "", "b", ""], "3") <> "3a33b3") then Blech("Test_PRegEx_Join 102")
  if (PRegEx_Join([[], "a", #c, "b", 3], "3") <> "3a33b3") then Blech("Test_PRegEx_Join 103")
  if (PRegEx_Join(PRegEx_Split(["1    2    3  5        3"], "\s+", "g"), " ") <> "1 2 3 5 3") then Blech("Test_PRegEx_Join 104")
  
  -- regression: join of [] was crashing on mac
  if (re_join([], "abc") <> "") then Blech("Test_PRegEx_Join 105")
  
  -- leak test
  if (LeakTestingSelected()) then
    set fBytes = void
    repeat with iterNum = 1 to 10000
      if (PRegEx_Join(["a", "", "b", ""], "3") <> "a33b3") then Blech("Test_PRegEx_Join 101")
      if (PRegEx_Join(["", "a", "", "b", ""], "3") <> "3a33b3") then Blech("Test_PRegEx_Join 102")
      if (PRegEx_Join([[], "a", #c, "b", 3], "3") <> "3a33b3") then Blech("Test_PRegEx_Join 103")
      if (PRegEx_Join(PRegEx_Split(["1    2    3  5        3"], "\s+", "g"), " ") <> "1 2 3 5 3") then Blech("Test_PRegEx_Join 104")
      if (re_join([], "abc") <> "") then Blech("Test_PRegEx_Join 105")
      
      if iterNum mod 200 = 0 then -- measure memory after 1/50th of the iterations
        if fBytes = void then set fBytes = the freeBytes
        -- put the freeBytes -- remember: uncommenting this uses up memory in the Message window's buffer!
      end if
    end repeat
    -- Measure memory again after all 100% of iterations have happened.  There should be no change.
    if abs(fBytes - the freeBytes)>100 then Blech "Test_PRegEx_Join Leak" && (the freeBytes - fBytes)
  end if
  
end Test_PRegEx_Join

