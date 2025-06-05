-- ui actions to manipulate the spec file

on ImportSpec
  -- Read the spec file into memory.
  set SpecFile = re_read2("@::docs:PRegEx_Spec.txt", "MACROMAN")
  if not listP(SpecFile)      then return(void)
  if not stringP(SpecFile[1]) then return(void)
  
  -- Convert line endings from DOS or Mac or Unix to Director's format (Mac)
  -- Add some feedback showing what time it was reimported (for entertainment only).
  -- Also "Detab" the entire text so it only has spaces in it.
  -- Note that the Detab functions below are GREAT examples of the use of
  -- PRegEx features to make an otherwise hard task simple.
  
  linecount = PRegEx_Replace(SpecFile, "(?:\x0D\x0A)|[\x0D\x0A]", "g", "\n")
  -- put "linecount:" && linecount
  inserted = PRegEx_Replace(SpecFile, "(\n=)", "", re_i("\n\n\tThis spec was last re-imported at ${#d}\\1", [#d:the date && the long time]))
  -- put "inserted:" && inserted
  Detab(SpecFile)
  
  -- Put the modified text from the buffer into a text cast member.
  set the text of member("Copy of PRegEx_Spec.txt -- not original") = SpecFile[1]
  
  -- Fun hack!    Use PRegEx to modify the RTF!    Automated control of styles!
  set RtfBuf = [the rtf of member("Copy of PRegEx_Spec.txt -- not original")]
  PRegEx_Replace(RtfBuf, "(re-imported at )(.*?)(\\par ?\n)", "", "\1{\\b\\ul \2}\3", "\n")
  set the rtf of member("Copy of PRegEx_Spec.txt -- not original") = RtfBuf[1]
end ImportSpec

on Rot13Spec
  set SpecFile = [the text of member("Copy of PRegEx_Spec.txt -- not original")]
  re_tr(SpecFile, "a-zA-Z", "n-za-mN-ZA-M") -- rot13 the entire document.
  set the text of member("Copy of PRegEx_Spec.txt -- not original") = SpecFile[1]
end Rot13Spec

on InvertcaseSpec
  set SpecFile = [the text of member("Copy of PRegEx_Spec.txt -- not original")]
  re_tr(SpecFile, "A-Za-z", "a-zA-Z") -- upcase the entire document.
  set the text of member("Copy of PRegEx_Spec.txt -- not original") = SpecFile[1]
end DowncaseSpec

on DowncaseSpec
  set SpecFile = [the text of member("Copy of PRegEx_Spec.txt -- not original")]
  re_tr(SpecFile, "A-Z", "a-z") -- upcase the entire document.
  set the text of member("Copy of PRegEx_Spec.txt -- not original") = SpecFile[1]
end DowncaseSpec

on UpcaseSpec
  set SpecFile = [the text of member("Copy of PRegEx_Spec.txt -- not original")]
  re_tr(SpecFile, "a-z", "A-Z") -- upcase the entire document.
  set the text of member("Copy of PRegEx_Spec.txt -- not original") = SpecFile[1]
end UpcaseSpec
