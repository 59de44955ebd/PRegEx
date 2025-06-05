on startMovie
  _player.debugPlaybackEnabled = 1
  
  InitPRegEx
  -- DebugPGX
  
  set the keyboardFocusSprite = 0
end startMovie

on InitPRegEx
  -- Always reload the Xtra when the movie starts
  -- This is very helpful for debugging.
  
  -- We can optionally load the debug version based on a check box setting in the score.
  DebugMode = the hilite of member("Use Debug Build")
  if DebugMode then 
    XtrasDir = "@::xtras:Debug:"
  else
    XtrasDir = "@::xtras:Release:"
  end if
  
  ForceReloadXtra "PRegEx", XtrasDir
  
  PRegEx_ErrorsToMessageWindow(1) -- Optional but helpful when playing around with PRegEx
end InitPRegEx
