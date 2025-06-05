on Test_Regressions
  -- We put tests here for anything that used to be a bug and has been
  -- fixed.
  
  -- Ensure \n maps to char(13) on both platforms
  -- Searching side (interpolations done by PCRE).
  if (PRegEx_Search([return               ], "\n") <> 1) then Blech("Test_Regressions 101")
  if (PRegEx_Search([numtochar(13)], "\n") <> 1) then Blech("Test_Regressions 102")
  
  -- Replacing side (interpolations done by PRegEx).
  set myTest = ["a_b"]
  if (PRegEx_Search (myTest, "\n") <> 0) then Blech("Test_Regressions 103a")
  if (PRegEx_Replace(myTest, "_", "g", "\n") <> 1) then Blech("Test_Regressions 103b")
  if (PRegEx_Search (myTest, "\n") <> 1) then Blech("Test_Regressions 103c")
  
end Test_Regressions