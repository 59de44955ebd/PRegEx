-- list related functions

-- ListEQ

-- Recursive list comparison functions needed by our testing routines
-- Call ListEQ with any two objects, including lists and/or property lists.
-- It will tell you whether the objects are equivalent, when compared recursively.

on ListEQ aList, bList
  
  if (ilk(aList) = #propList) then return (PListEQ(aList, bList))
  if not listP(aList) or not listP(bList) then return(false)
  if count(aList) <> count(bList) then return(false)
  repeat with itemNum = 1 to count(aList)
    aVal = aList[itemNum]
    bVal = bList[itemNum]
    if          ((ilk(aVal) = #list      ) and (ilk(bVal) = #list        )) then -- recursive processing of list elements.
      if (not(ListEQ(aVal, bVal))) then
        return(false)
      end if
    else if ((ilk(aVal) = #propList) and (ilk(bVal) = #propList)) then -- recursive processing of list elements.
      if (not(PListEQ(aVal, bVal))) then
        return(false)
      end if
    else
      if (aVal <> bVal) then return(false)
    end if
  end repeat
  return(true)
end ListEQ

on PListEQ aList, bList
  if (ilk(aList) = #list) then return (ListEQ(aList, bList))
  if not listP(aList) or not listP(bList) then return(false)
  if count(aList) <> count(bList) then return(false)
  repeat with itemNum = 1 to count(aList)
    aKey = getPropAt(aList, itemNum)
    bKey = getPropAt(bList, itemNum)
    aVal = getAProp(aList, aKey)
    bVal = getAProp(bList, bKey)
    if aKey <> bKey then return(false)
    if          ((ilk(aVal) = #list      ) and (ilk(bVal) = #list        )) then -- recursive processing of list elements.
      if (not(ListEQ(aVal, bVal))) then
        return(false)
      end if
    else if ((ilk(aVal) = #propList) and (ilk(bVal) = #propList)) then -- recursive processing of list elements.
      if (not(PListEQ(aVal, bVal))) then
        return(false)
      end if
    else
      if (aVal <> bVal) then return(false)
    end if
  end repeat
  return(true)
end PListEQ

on ListAdder myList
  append myList, PRegEx_GetMatchString(0)
  -- put myList
end ListAdder

on ListElemGetter myArgList
  set myList          = myArgList[1]
  set myWhichElem = myArgList[2]
  return(myList[myWhichElem])
end ListElemGetter