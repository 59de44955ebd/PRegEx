on Test_PRegEx_Replace
  set aStringOrig = ["Chris"]
  
  set aString         = [aStringOrig[1]]
  if ((re_s                   (aString, "chris", "",  "foo") <> 0) or (aString[1] <> "Chris" )) then Blech "PRegEx_Replace 101" && PRegEx_CompiledOK()
  
  set aString         = [aStringOrig[1]]
  if ((re_replace     (aString, "chris", "",  "foo") <> 0) or (aString[1] <> "Chris" )) then Blech "PRegEx_Replace 101" && PRegEx_CompiledOK()
  
  set aString         = [aStringOrig[1]]
  if ((PRegEx_Replace(aString, "chris", "",    "foo") <> 0) or (aString[1] <> "Chris" )) then Blech "PRegEx_Replace 101" && PRegEx_CompiledOK()
  
  set aString         = [aStringOrig[1]]
  if ((PRegEx_Replace(aString, "chr", "i", "foo") <> 1) or (aString[1] <> "foois"     )) then Blech "PRegEx_Replace 102" && PRegEx_CompiledOK()
  
  -- global
  
  set aString         = [aStringOrig[1]]
  if ((PRegEx_Replace(aString, "chris", "g",  "foo") <> 0) or (aString[1] <> "Chris" )) then Blech "PRegEx_Replace 200" && PRegEx_CompiledOK()
  
  set aString         = [aStringOrig[1]]
  if ((PRegEx_Replace(aString, "\w", "g", "Xx") <> 5) or (aString[1] <> "XxXxXxXxXx")) then Blech "PRegEx_Replace 201" && PRegEx_CompiledOK()
  
  set aString         = [aStringOrig[1]]
  if ((PRegEx_Replace(aString, "\w\w", "g", "Xx") <> 2) or (aString[1] <> "XxXxs"     )) then Blech "PRegEx_Replace 202" && PRegEx_CompiledOK()
  
  set aString         = [aStringOrig[1]]
  if ((PRegEx_Replace(aString, "[hi]", "g", "Xxî") <> 2) or (aString[1] <> "CXxîrXxîs"       )) then Blech "PRegEx_Replace 203" && PRegEx_CompiledOK()
  
  set aString         = [aStringOrig[1]]
  if ((PRegEx_Replace(aString, "[hi]", "g", "") <> 2) or (aString[1] <> "Crs"              )) then Blech "PRegEx_Replace 204" && PRegEx_CompiledOK()
  
  -- leak test
  if (LeakTestingSelected()) then
    set fBytes = void
    repeat with iterNum = 1 to 10000
      
      set aString         = [aStringOrig[1]]
      if ((PRegEx_Replace(aString, "\w", "g", "Xx") <> 5) or (aString[1] <> "XxXxXxXxXx")) then Blech "PRegEx_Replace 401" && PRegEx_CompiledOK()
      set aString         = [aStringOrig[1]]
      if ((PRegEx_Replace(aString, "[hi]", "g", "") <> 2) or (aString[1] <> "Crs"             )) then Blech "PRegEx_Replace 402" && PRegEx_CompiledOK()
      
      if iterNum mod 200 = 0 then -- measure memory after 1/50th of the iterations
        if fBytes = void then set fBytes = the freeBytes
        -- put the freeBytes -- remember: uncommenting this uses up memory in the Message window's buffer!
      end if
    end repeat
    -- Measure memory again after all 100% of iterations have happened.  There should be no change.
    if abs(fBytes - the freeBytes)>100 then Blech "PRegEx_Replace Leak" && (the freeBytes - fBytes)
  end if
  
end Test_PRegEx_Replace