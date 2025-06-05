-- Detab
-- DetabString

-- Detab Converts tabs to spaces in a String Buffer (List with a string in it)
-- DetabString does the same, but on a bare string.

-- These are good examples of what you can do with PRegEx

global LotsOfSpaces

on Detab StringBuf, TabWidth
  LotsOfSpaces = re_i("\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20")
  if voidP(TabWidth) then TabWidth = 4
  PRegEx_Replace(StringBuf, "((?:\t)|(?:\n)|([^\t\n]+))", "ge", #DetabHelper, [TabWidth, [0]])
  return(StringBuf)
end Detab

on DetabHelper TabWidth, LinePosList
  Text = PRegEx_GetMatchString(1)
  if (Text = return) then
    set LinePosList[1] = 0
  else if (Text = tab) then
    set NumSpaces =  TabWidth - (LinePosList[1] mod TabWidth)
    set LinePosList[1] = LinePosList[1] + NumSpaces
    set Text = char 1 to NumSpaces of LotsOfSpaces
  else
    set LinePosList[1] = LinePosList[1] + length(Text)
  end if
  return(Text)
end Detab

on DetabString Text
  return((Detab([Text]))[1])
end DetabString

on testDetab
  myVal=[re_i("\ta\tab\tabc\tabcd\t")]
  if (Detab(myVal)[1] <> "    a   ab  abc abcd    ") then put "failed:"
  else put "Succeeded: "
  put "'" && Detab(myVal)[1] && "'"
end

-- CapUnderScorer

-- A PRegEx callback function that
-- munges the entire matched string by surrounding
-- each capital letter with an underscore.
-- Used to test recursive calls to PRegEx functions
-- because it calls PRegEx_Replace, but yet can be called
-- from within a PRegEx_Replace.

on CapUnderScorer
  set myString = [string(PRegEx_GetMatchString(0))]
  PRegEx_Replace(myString, "([A-Z])", "g", "_\1_")
  -- put PRegEx_GetMatchString(1)
  return (myString[1])
end CapUnderScorer