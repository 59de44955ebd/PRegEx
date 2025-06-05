on Test_PRegEx_Map
  set oldDebugSetting = PRegEx_ErrorsToMessageWindow()
  PRegEx_ErrorsToMessageWindow(0)
  set mySampleArgList = [2, "a", #foo, ["abc"], [1:2]]
  
  if (not(ListEQ(re_map       ([1,2,3], #AddNumbers, mySampleArgList), [3,4,5]))) then Blech("Test_PRegEx_Map 101")
  if (not(ListEQ(PRegEx_Map([1,2,3], #AddNumbers, mySampleArgList), [3,4,5]))) then Blech("Test_PRegEx_Map 101")
  if (not(ListEQ(PRegEx_Map(["å",1,"b",2,3, void], #AddNumbers, mySampleArgList), [3,4,5]))) then Blech("Test_PRegEx_Map 101b") -- tests Skip flag
  if (not(ListEQ(PRegEx_Map([1,2,3], #FooBang, mySampleArgList), ["Foo!","Foo!","Foo!"]))) then Blech("Test_PRegEx_Map 102")
  if (not(ListEQ(PRegEx_Map([1,2,3], #VoidReturner, mySampleArgList), [void,void,void]))) then Blech("Test_PRegEx_Map 103")
  if (not(ListEQ(PRegEx_Map([], #FooBang, mySampleArgList), []))) then Blech("Test_PRegEx_Map 104")
  if (not(ListEQ(PRegEx_Map([], #FooBang), []))) then Blech("Test_PRegEx_Map 105")
  if (not(ListEQ(PRegEx_Map([1], #undef), []) and PRegEx_LastErrCode() = PRegEx_ErrCode_CallbackFunctionFailed())) then Blech("Test_PRegEx_Map 106")
  if (not(ListEQ(PRegEx_Map([:], #FooBang), []) and PRegEx_LastErrCode() = PRegEx_ErrCode_ExpectedListArgument())) then Blech("Test_PRegEx_Map 107")
  
  -- leak test
  if (LeakTestingSelected()) then
    set fBytes = void
    repeat with iterNum = 1 to 10000
      if (not(ListEQ(PRegEx_Map([1,2,3], #AddNumbers, mySampleArgList), [3,4,5]))) then Blech("Test_PRegEx_Map 201")
      
      if iterNum mod 200 = 0 then -- measure memory after 1/50th of the iterations
        if fBytes = void then set fBytes = the freeBytes
        -- put the freeBytes -- remember: uncommenting this uses up memory in the Message window's buffer!
      end if
    end repeat
    -- Measure memory again after all 100% of iterations have happened.  There should be no change.
    if abs(fBytes - the freeBytes)>100 then Blech "Test_PRegEx_Map Leak" && (the freeBytes - fBytes)
  end if
  PRegEx_ErrorsToMessageWindow(oldDebugSetting)
end Test_PRegEx_Map