on AddNumbers Arg1, Arg2
  if not(integerP(Arg1) and integerP(Arg2)) then PRegEx_CallbackSkip(true)
  return(Arg1+Arg2)
end AddNumbers

on FooBang
  return("Foo!")
end FooBang

on NullFunc
end NullFunc

on VoidReturner
end VoidReturner

-- argument related utils

on ArgDoubler myString
  return(myString&myString)
end ArgDoubler

-- isA utils
on IsPositive Arg1
  return(integer(Arg1)>0)
  
end IsPositive

on IsString Arg1
  return(stringP(Arg1))
  
end IsString

on IsLessThan Arg1, Arg2
  return(Arg1<Arg2)
end IsLessThan

-- constant
on ReturnsInt
  return(3)
end ReturnsInt

-- Sample ReplFunctions for the above test routines.
on Bracketize
  return("[[" & PRegEx_GetMatchString() & "]]")
end Bracketize

on BracketizeAbort
  PRegEx_CallbackAbort(1)
  return("[[" & PRegEx_GetMatchString() & "]]")
end BracketizeAbort

on Underscore_LONG_SYMBOL_NAME_FOR_LEAK_TESTING
  return("_")
end Underscore_LONG_SYMBOL_NAME_FOR_LEAK_TESTING

on Underscore
  return("_")
end Underscore

on UnderscoreAbortOn2
  if PRegEx_FoundCount() = 2 then re_abort(1)
  return("_")
end UnderscoreAbortOn2

on UnderscoreStopOn2
  if PRegEx_FoundCount() = 2 then re_stop(1)
  return("_")
end UnderscoreStopOn2

on UnderscoreSkipOn2
  if PRegEx_FoundCount() = 2 then re_skip(1)
  return("_")
end UnderscoreSkipOn2

on UnderscoreLastOn2
  if PRegEx_FoundCount() = 2 then re_last(1)
  return("_")
end UnderscoreLastOn2
