global gLoadedXtras
on DebugPGX  
  put " --------------------------- start debugging --------------------------- "
  --  if the machineType =  256 then ForceReloadXtra "PRegEx", "@:::build_win:Debug:"  
  --  if the machineType <> 256 then ForceReloadXtra "PRegEx", "@:::build_mac:Debug:"
  
  ForceReloadXtra "PRegEx", "@::xtras:"
  if not voidP(gLoadedXtras) then put gLoadedXtras 
  put _system.time()  && " pcre=" && PRegEx_GetPCREVersion() && " iconv=" && PRegEx_GetICONVVersion() && " PRegEx=" && PRegEx_GetPRegExVersion()
  
  -- trace _player.scriptingXtraList
  -- Test_PRegEx_ReadEntireFile
  -- Test_PRegEx_WriteEntireFile
  -- Test_PRegEx_ReadFileToString
  ---Test_PRegEx_WriteStringToFile
  
  -- Test_PRegEx_Translate
  -- Test_PRegEx_CopyList
  -- ProfileFunc #Test_PRegEx_ReadFileToString
  -- RunTestSuite
  
  LeaveEarly
  
end DebugPGX


on LeaveEarly
  put "exiting..."
  -- put _player.scriptingXtraList
  -- closexlib "@:::build_mac:Debug:PRegEx.xtra"
  _movie.halt()
end LeavEarly

on ProfileFunc function
  set start = _system.milliseconds
  PRegEx_CallHandler(function)
  put (_system.milliseconds - start) && " ms " && " ->" && function
  
end ProfileFunc

