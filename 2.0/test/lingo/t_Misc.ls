-- misc tests

on Test_PRegEx_Clear
end Test_PRegEx_Clear

--Status functions:

on Test_PRegEx_CompiledOK
end Test_PRegEx_CompiledOK

on Test_PRegEx_MemError
end Test_PRegEx_MemError

on Test_PRegEx_MemErrorSticky
end Test_PRegEx_MemErrorSticky

on Test_PRegEx_MemErrorStickyReset
end Test_PRegEx_MemErrorStickyReset

on Test_PRegEx_GetMatchStart
end Test_PRegEx_GetMatchStart

on Test_PRegEx_GetMatchLen
end Test_PRegEx_GetMatchLen

on Test_PRegEx_GetMatchBRCount
end Test_PRegEx_GetMatchBRCount

on Test_PRegEx_FoundCount
end Test_PRegEx_FoundCount

on Test_PRegEx_GetPos
  -- tested in many other places as well...
  
  -- Unicode test:
  re_m(["doggy dug döggy dug blahblah"], "(\S+) (\S+)", "g")
  
  if (PRegEx_GetPos() <> 19) then Blech "PRegEx_GetPos 101" -- would return 20 if GetPos was not working right.
  
end Test_PRegEx_GetPos

on Test_PRegEx_SetPos
  if (PRegEx_SetSearchString(["dög çât tøåd"]) <> true) then Blech "PRegEx_SetPos 1" && PRegEx_CompiledOK()
  
  if (PRegEx_SetMatchPattern("(\s*\S+)", "i" ) <> true) then Blech "PRegEx_SetPos 2" && PRegEx_MemError()
  
  -- Match #1
  if (PRegEx_GetNextMatch()        <> true            ) then Blech "PRegEx_SetPos 210" && PRegEx_MemError()
  
  if (PRegEx_GetMatchString()  <> "dög"               ) then Blech "PRegEx_SetPos 211" && PRegEx_GetMatchString()
  if (PRegEx_GetMatchString(0) <> "dög"               ) then Blech "PRegEx_SetPos 212" && PRegEx_GetMatchString(0)
  if (PRegEx_GetMatchString(1) <> "dög"               ) then Blech "PRegEx_SetPos 213" && PRegEx_GetMatchString(1)
  if (PRegEx_GetMatchString(2) <> void                ) then Blech "PRegEx_SetPos 214" && PRegEx_GetMatchString(2)
  if (PRegEx_GetPos()             <> 3                ) then Blech "PRegEx_SetPos 215" && PRegEx_GetPos()
  
  -- Change Pos and match (again)
  
  if (PRegEx_SetPos(8)            <> void             ) then Blech "PRegEx_SetPos 220" && PRegEx_SetPos()
  if (PRegEx_GetPos()             <> 8                ) then Blech "PRegEx_SetPos 221" && PRegEx_GetPos()
  
  if (PRegEx_GetNextMatch()       <> true             ) then Blech "PRegEx_SetPos 222" && PRegEx_MemError()
  
  if (PRegEx_GetMatchString()  <> "tøåd"              ) then Blech "PRegEx_SetPos 223" && PRegEx_GetMatchString()
  if (PRegEx_GetPos()             <> 12               ) then Blech "PRegEx_SetPos 224" && PRegEx_GetPos()
  
  -- Change Pos and match (again)
  
  if (PRegEx_SetPos(3)            <> void             ) then Blech "PRegEx_SetPos 230" && PRegEx_SetPos()
  if (PRegEx_GetPos()             <> 3                ) then Blech "PRegEx_SetPos 231" && PRegEx_GetPos()
  
  if (PRegEx_GetNextMatch()       <> true             ) then Blech "PRegEx_SetPos 232" && PRegEx_MemError()
  
  if (PRegEx_GetMatchString()  <> " çât"              ) then Blech "PRegEx_SetPos 233" && PRegEx_GetMatchString()
  if (PRegEx_GetPos()             <> 7                ) then Blech "PRegEx_SetPos 234" && PRegEx_GetPos()
  
end Test_PRegEx_SetPos



on Test_PRegEx_GetICONVVersion
  PRegEx_GetICONVVersion()
end Test_PRegEx_GetICONVVersion

on Test_PRegEx_GetPCREVersion
  PRegEx_GetPCREVersion()
end Test_PRegEx_GetPCREVersion

on Test_PRegEx_GetPRegExVersion
  PRegEx_GetPRegExVersion()
end Test_PRegEx_GetPRegExVersion


on Test_PRegEx_CallbackLast    -- Tested above.
end Test_PRegEx_CallbackLast

on Test_PRegEx_CallbackStop    -- Tested above.
end Test_PRegEx_CallbackStop

on Test_PRegEx_CallbackSkip    -- Tested above.
end Test_PRegEx_CallbackSkip

on Test_PRegEx_CallbackAbort   -- Tested above.
end Test_PRegEx_CallbackAbort
