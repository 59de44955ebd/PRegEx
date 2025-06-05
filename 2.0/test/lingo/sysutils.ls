-- Xtra loading / reloading

-- This can be used to force an Xtra to always reload every time something happens,
-- like startMovie.  So if you're programming an Xtra, each time you re-build, you
-- can just come back to Director and hit the Enter (not Return) key twice.  That starts
-- and stops the movie and in the process forces the Xtra to be re-loaded.  Saves hours
-- of time.

global gLoadedXtras

on ForceReloadXtra XtraName, XtrasDir
  if voidP(gLoadedXtras) then set gLoadedXtras = [:]
  if voidP(XtrasDir) then set XtrasDir = "@::xtras:"
  set XtraLoc = XtrasDir & XtraName
  if the machineType =  256 then set XtraLoc = XtraLoc & ".x32"
  if the machineType <> 256 then set XtraLoc = XtraLoc & ".xtra"
  if (string(the xtralist) contains XtraName) then
    put "Unloading" && gLoadedXtras[XtraName]
    do("closexlib(" & quote & gLoadedXtras[XtraName] & quote & ")")
    if (string(the xtralist) contains XtraName) then
      put "ERROR: Failed to unload" && gLoadedXtras[XtraName]
    end if
  end if
  openxlib(XtraLoc)
  if (string(the xtralist) contains XtraName) then
    -- Remember where we loaded this one from, for the unload later.
    put "Loaded" && XtraName && "from" && XtraLoc
    set gLoadedXtras[XtraName] = XtraLoc
  else
    put "ERROR: Failed to load" && XtraName && "from" && XtraLoc
  end if
end ForceReloadXtra

on Blech Message
  put " ==> " & Message
end Blech
