-- Test suite

on LeakTestingSelected
  set doLeakTesting = the hilite of member "DoLeakTesting"
  return(doLeakTesting)
end LeakTestingSelected

on RunTestSuite
  
  PRegEx_ErrorsToMessageWindow(0)
  
  if (LeakTestingSelected()) then
    put "Note: for best results when leak testing on Windows, "
    put "You should run with no other apps running."
    put "If you do, you may see both 'positive' and 'negative' leaks reported."
    put "Of course, a 'positive' leak means memory being gained back."
    put "... and does not reflect actual leaking in PRegEx."
  end if
  
  put the freeBytes && "Running tests.    Messages preceded by an arrow are test failures."
  
  put the freeBytes && "Test_PRegEx_SetMatchPattern"
  Test_PRegEx_SetMatchPattern         -- (RE, Opts)     ==> True if compiled OK
  
  put the freeBytes && "Test_PRegEx_SetSearchString"
  Test_PRegEx_SetSearchString         -- (SrchStrL)     ==> True unless mem err or bad params
  
  put the freeBytes && "Test_PRegEx_GetNextMatch"
  Test_PRegEx_GetNextMatch                -- ()         ==> True unless mem err or no match
  
  put the freeBytes && "Test_PRegEx_ReplaceString"
  Test_PRegEx_ReplaceString               -- (ReplPat)  ==> True unless mem err or bad params
  
  put the freeBytes && "Test_PRegEx_Clear"
  Test_PRegEx_Clear                               -- ()                    ==> void
  
  --Status functions:
  
  put the freeBytes && "Test_PRegEx_CompiledOK"
  Test_PRegEx_CompiledOK                  -- () ==> True if last expression compiled
  
  put the freeBytes && "Test_PRegEx_MemError"
  Test_PRegEx_MemError                        -- () ==> True if last operation failed due to memory
  
  put the freeBytes && "Test_PRegEx_MemErrorSticky"
  Test_PRegEx_MemErrorSticky          -- () ==> True if any op has failed due to memory
  
  put the freeBytes && "Test_PRegEx_MemErrorStickyReset"
  Test_PRegEx_MemErrorStickyReset -- () ==> Resets the sticky error; returns previous val
  
  put the freeBytes && "Test_PRegEx_GetMatchString"
  Test_PRegEx_GetMatchString          -- ([num]) ==> Cur (or last) match, (entire OR back #)
  
  put the freeBytes && "Test_PRegEx_GetMatchStart"
  Test_PRegEx_GetMatchStart               -- ([num]) ==> Char start pos of "" (entire OR back #)
  
  put the freeBytes && "Test_PRegEx_GetMatchLen"
  Test_PRegEx_GetMatchLen                 -- ([num]) ==> Length of "" (entire OR back #)
  
  put the freeBytes && "Test_PRegEx_GetMatchBRCount"
  Test_PRegEx_GetMatchBRCount         -- () ==> Number of back ref strings available
  
  put the freeBytes && "Test_PRegEx_FoundCount"
  Test_PRegEx_FoundCount                  -- () ==> Running or final ct. of total match events
  
  put the freeBytes && "Test_PRegEx_GetPos"
  Test_PRegEx_GetPos                          -- () ==> Char pos where last left off / next will begin
  
  put the freeBytes && "Test_PRegEx_SetPos"
  Test_PRegEx_SetPos                          -- (num) ==> Change pos (within bounds of string length)
  
  put the freeBytes && "Test_PRegEx_GetICONVVersion"
  Test_PRegEx_GetICONVVersion          -- () ==> String-format version number of libiconv ("1.12p1")
  
  put the freeBytes && "Test_PRegEx_GetPCREVersion"
  Test_PRegEx_GetPCREVersion          -- () ==> String-format version number of PCRE ("7.7p1")
  
  put the freeBytes && "Test_PRegEx_GetPRegExVersion"
  Test_PRegEx_GetPRegExVersion         -- () ==> String-format version number of PRegEx ("2.0")
  
  -- Utility Functions:
  
  put the freeBytes && "Test_PRegEx_QuoteMeta"
  Test_PRegEx_QuoteMeta               -- (String)      ==> String with special chars quoted
  
  -- High-level interface:
  
  put the freeBytes && "Test_PRegEx_Search"
  Test_PRegEx_Search                           -- (SrchStrL, RE, Opts) ==> FoundCount
  
  put the freeBytes && "Test_PRegEx_SearchExec"
  Test_PRegEx_SearchExec                           -- (SrchStrL, RE, Opts) ==> FoundCount  
  
  put the freeBytes && "Test_PRegEx_ExtractIntoList"
  Test_PRegEx_ExtractIntoList          -- (SrchStrL, RE, Opts, OrigList) ==> List
  
  put the freeBytes && "Test_PRegEx_ExtractIntoSPList"
  Test_PRegEx_ExtractIntoSPList        -- (SrchStrL, RE, Opts, OrigList) ==> sorted Property List
  
  put the freeBytes && "Test_PRegEx_ExtractIntoSPListSym"
  Test_PRegEx_ExtractIntoSPListSym -- (SrchStrL, RE, Opts, OrigList) ==> sorted Property List
  
  put the freeBytes && "Test_PRegEx_Replace"
  Test_PRegEx_Replace                 -- (SrchStrL, RE, Opts, ReplPat         ) ==> FoundCount
  
  put the freeBytes && "Test_PRegEx_ReplaceExec"
  Test_PRegEx_ReplaceExec         -- (SrchStrL, RE, Opts, ReplFunction) ==> FoundCount
  
  put the freeBytes && "Test_PRegEx_CallHandler"
  Test_PRegEx_CallHandler
  
  put the freeBytes && "Test_PRegEx_ReadFileToString"
  Test_PRegEx_ReadFileToString
  
  put the freeBytes && "Test_PRegEx_WriteStringToFile"
  Test_PRegEx_WriteStringToFile
  
  put the freeBytes && "Test_PRegEx_ReadEntireFile"
  Test_PRegEx_ReadEntireFile
  
  put the freeBytes && "Test_PRegEx_WriteEntireFile"
  Test_PRegEx_WriteEntireFile
  
  put the freeBytes && "Test_PRegEx_Unicode"
  Test_PRegEx_Unicode
  
  put the freeBytes && "Test_PRegEx_Map"
  Test_PRegEx_Map
  
  put the freeBytes && "Test_PRegEx_Split"
  Test_PRegEx_Split
  
  put the freeBytes && "Test_PRegEx_Join"
  Test_PRegEx_Join
  
  put the freeBytes && "Test_PRegEx_Sort"
  Test_PRegEx_Sort
  
  put the freeBytes && "Test_PRegEx_Reverse"
  Test_PRegEx_Reverse
  
  put the freeBytes && "Test_PRegEx_CopyList"
  Test_PRegEx_CopyList
  
  put the freeBytes &&    "Test_PRegEx_Keys"
  Test_PRegEx_Keys                        -- PList, [InitList] ==> KeyList
  
  put the freeBytes &&    "Test_PRegEx_Values"
  Test_PRegEx_Values                      -- PList, [InitList] ==> ValueList
  
  put the freeBytes &&    "Test_PRegEx_GetSlice"
  Test_PRegEx_GetSlice                        -- List, Keys, [InitList] ==> SliceList
  
  put the freeBytes &&    "Test_PRegEx_SetSlice"
  Test_PRegEx_SetSlice                        -- List, Keys, Values ==> List
  
  put the freeBytes &&    "Test_PRegEx_PListToList"
  Test_PRegEx_PListToList                     -- PList, [InitList] ==> List
  
  put the freeBytes &&    "Test_PRegEx_PListToListStrings"
  Test_PRegEx_PListToListStrings          -- PList, [InitList] ==> List
  
  put the freeBytes &&    "Test_PRegEx_ListToSPList"
  Test_PRegEx_ListToSPList                    -- List, [InitPList] ==> SPList
  
  put the freeBytes &&    "Test_PRegEx_ListToSPListSym"
  Test_PRegEx_ListToSPListSym             -- List, [InitPList] ==> SPList
  
  put the freeBytes && "Test_PRegEx_Grep"
  Test_PRegEx_Grep
  
  put the freeBytes && "Test_PRegEx_CallbackAbort"
  Test_PRegEx_CallbackAbort           -- () ==> Called by ReplFunction to stop and fail replace
  
  put the freeBytes && "Test_PRegEx_CallbackStop"
  Test_PRegEx_CallbackStop            -- () ==> Called by ReplFunction to stop replacing
  
  put the freeBytes && "Test_PRegEx_CallbackSkip"
  Test_PRegEx_CallbackSkip            -- () ==> Called by ReplFunction to stop and fail replace
  
  put the freeBytes && "Test_PRegEx_CallbackLast"
  Test_PRegEx_CallbackLast            -- () ==> Called by ReplFunction to signal last replace
  
  put the freeBytes && "Test_PRegEx_ErrorCodes"
  Test_PRegEx_ErrorCodes          -- () ==> Called by ReplFunction to stop and fail replace
  
  put the freeBytes && "Test_PRegEx_Translate"
  Test_PRegEx_Translate
  
  put the freeBytes && "Test_PRegEx_Interpolate"
  Test_PRegEx_Interpolate
  
  put the freeBytes && "Done"
  
  PRegEx_ErrorsToMessageWindow(1)
  
end RunTestSuite

