on PlainSort a, b
  -- put a && b
  if (a < b) then return(-1)
  if (a = b) then return(0)
  if (a > b) then return(1)
end PlainSort

on InListSort a, b, aList
  -- put a && b
  if (aList[a] <> void and aList[b]    = void) then return(-1)
  if (aList[a]    = void and aList[b] <> void) then return(1)
  return(0)
end InListSort

on SymbolSort a, b
  return(PlainSort(string(a), string(b)))
end SymbolSort
