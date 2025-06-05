on Test_PRegEx_CallHandler interactive
  set mySampleArgList = ["a", 2, #foo, ["aé"], [1:2]]
  if (interactive) then
    -- These all put output into the message window.    Best when doing manual testing.
    if (PRegEx_CallHandler(#MaybeArgPutter, 1, "a")) <> "Whoah!" then Blech("Test_PRegEx_CallHandler 101")
    if (PRegEx_CallHandler(#MaybeArgPutter, 2, ["a"])) <> "Whoah!" then Blech("Test_PRegEx_CallHandler 102")
    if (PRegEx_CallHandler(#MaybeArgPutter, 1, ["a", 2])) <> "Whoah!" then Blech("Test_PRegEx_CallHandler 103")
    if (PRegEx_CallHandler(#MaybeArgPutter, 1, mySampleArgList)) <> "Whoah!" then Blech("Test_PRegEx_CallHandler 104")
    if (PRegEx_CallHandler(#AllArgPutter,       1, mySampleArgList)) <> "Whoah!" then Blech("Test_PRegEx_CallHandler 105")
    if (PRegEx_CallHandler(#AllArgPutter,       mySampleArgList, mySampleArgList)) <> "Whoah!" then Blech("Test_PRegEx_CallHandler 106")
    if (PRegEx_CallHandler(#AllArgPutter,       mySampleArgList, 1)) <> "Whoah!" then Blech("Test_PRegEx_CallHandler 107")
  end if
  
  if (re_call                  (#MaybeArgPutter, 0, "a")) <> "Whoah!" then Blech("Test_PRegEx_CallHandler 201a")
  if (PRegEx_CallHandler(#MaybeArgPutter, 0, "á")) <> "Whoah!" then Blech("Test_PRegEx_CallHandler 201b")
  if (PRegEx_CallHandler(#MaybeArgPutter, 0, ["a"])) <> "Whoah!" then Blech("Test_PRegEx_CallHandler 202")
  if (PRegEx_CallHandler(#MaybeArgPutter, 0, ["a", 2])) <> "Whoah!" then Blech("Test_PRegEx_CallHandler 203")
  if (PRegEx_CallHandler(#MaybeArgPutter, 0, mySampleArgList)) <> "Whoah!" then Blech("Test_PRegEx_CallHandler 204")
  
  -- leak test
  if (0) then -- (LeakTestingSelected()) then
    set fBytes = void
    repeat with iterNum = 1 to 10000
      if (PRegEx_CallHandler(#MaybeArgPutter)) <> "Whoah!" then Blech("Test_PRegEx_CallHandler 301")
      
      if iterNum mod 200 = 0 then -- measure memory after 1/50th of the iterations
        if fBytes = void then set fBytes = the freeBytes
        -- put the freeBytes -- remember: uncommenting this uses up memory in the Message window's buffer!
      end if
    end repeat
    -- Measure memory again after all 100% of iterations have happened.  There should be no change.
    if abs(fBytes - the freeBytes)>100 then Blech "Test_PRegEx_CallHandler Leak" && (the freeBytes - fBytes)
  end if
  
end Test_PRegEx_CallHandler

on MaybeArgPutter printArgs, a,b,c,d,e,f,g,h,i,j,k,l
  if (printArgs) then
    put "--------"
    put a
    put b
    put c
    put d
    put e
    put f
    put g
    put h
    put i
    put j
    put k
    put l
  end if
  return("Whoah!")
end MaybeArgPutter

on AllArgPutter a,b,c,d,e,f,g,h,i,j,k,l
  put "--------"
  put a
  put b
  put c
  put d
  put e
  put f
  put g
  put h
  put i
  put j
  put k
  put l
  return("Whoah!")
end AllArgPutter
