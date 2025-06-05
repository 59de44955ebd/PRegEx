on Test_PRegEx_Translate
  -- test 101 demonstrates an apparent lingo compiler optimization bug, existing both in Director 11 and Director MX 2004
  -- the second set myList = ["foo"] is NOT executed
  -- this however doesn't happen when
  -- 1 - executed in the interpretor Message window vs. from a compiled handler call
  -- 2 - when there are no PRegEx xtra calls sandwiched between set statements.
  -- 3- if the constant "foo" is replaced by a function call or expression which yields a string (e.g. "foo"&"")
  set myList = ["foo"]
  PRegEx_Translate    (myList, "fo", "bp")
  set myList = ["foo"]
  if (PRegEx_Translate(myList, "fo", "bp") <> 3 or myList[1] <> "bpp") then Blech "Test_PRegEx_Translate 101 (known Director bug)"
  
  -- The remaining tests work around the bug by using the &"" trick or by calling re_i.
  
  set myList = ["foo"&""]
  if (PRegEx_Translate(myList, "", "") <> 0 or myList[1] <> "foo") then Blech "Test_PRegEx_Translate 102"
  
  set myList = [re_i("foo\n")]
  if (PRegEx_Translate(myList, "\n", "\t") <> 1 or myList[1] <> re_i("foo\t")) then Blech "Test_PRegEx_Translate 103"
  set myList = [re_i("foo\0bar")]
  if (PRegEx_Translate(myList, "a-z", "_") <> 6 or myList[1] <> "___" & numtochar(0) & "___") then Blech "Test_PRegEx_Translate 103"
  
  -- test rot13 encryption and back again
  set myList = ["abcdwxyz"&""]
  if (PRegEx_Translate(myList, "a-z", "n-za-m") <> 8 or myList[1] <> "nopqjklm") then Blech "Test_PRegEx_Translate 104a"
  if (PRegEx_Translate(myList, "a-z", "n-za-m") <> 8 or myList[1] <> "abcdwxyz") then Blech "Test_PRegEx_Translate 104b"
  
  -- test rot128 encryption and back again, with rotation expressed one way in octal, the other in hex.
  set myList1 = ["ABCDEFGH"&""]
  if (PRegEx_Translate(myList1, "\0-\0377"  , "\0377-\0"   ) <> 0                            ) then Blech "Test_PRegEx_Translate 105a"
  set myList2 = ["ABCDEFGH"&""]
  if (PRegEx_Translate(myList2, "\0-\0377"  , "\0377-\0"   ) <> 0 or myList2[1] <> "ABCDEFGH" ) then Blech "Test_PRegEx_Translate 105b"
  set myList3 = ["ABCDEFGH"&""]
  if (PRegEx_Translate(myList3, "\x00-\xFF", "\xFF-\x00") <> 0                             ) then Blech "Test_PRegEx_Translate 105c"
  set myList4 = ["ABCDEFGH"&""]
  if (PRegEx_Translate(myList4, "\x00-\x7F", "\x7F-\x00") <> 8 or myList4[1] <> ">=<;:987") then Blech "Test_PRegEx_Translate 105d"
  
  set myList = ["-0123"&""]
  if (PRegEx_Translate(myList, "-012"   , "ABC"  ) <> 4 or myList[1] <> "ABCC3") then Blech "Test_PRegEx_Translate 106"
  
  set myList = ["abc"&""]
  if (PRegEx_Translate(myList, "•abéc••••••••••", "•••••••••••••céba") <> 2 or myList[1] <> "cba") then Blech "Test_PRegEx_Translate 107"
  if (PRegEx_Translate(myList, "•abéc••••••••••", "•••••••••••••céba") <> 2 or myList[1] <> "abc") then Blech "Test_PRegEx_Translate 108"
  if (PRegEx_Translate(myList, "•abéc••••••••••", "•••••••••••••céba") <> 2 or myList[1] <> "cba") then Blech "Test_PRegEx_Translate 109"
  
  -- Currently, "-" and "\" are considered special in _Translate() EVEN when they are specified 
  -- via the escape sequences \-, \\, \x2D, or \x5C. In these cases, they should be treated as 
  -- literal characters in the translation tables. (Thanks to Arno Oesterheld.)
  --
  -- ==> Workaround 1: to map a dash, make it the first character in the input mapping. 
  -- To map a slash, make it the last character in the input mapping. For example:
  -- re_tr(foo, "-a-z", "!z-a") -- dashes to bangs; invert alphabet
  -- re_tr(foo, "a-z\", "z-a!") -- backslash to bang; invert alphabet
  --
  -- ==> Workaround 2: use "-" as a range operator to include dash and slash in a range with the 
  -- surrounding characters. For example:
  -- re_tr(foo, ",-.", ",!.") -- convert dashes (only) to bangs
  -- re_tr(foo, "[-]", "[!]") -- convert backslashes (only) to bangs

  -- test workaround 1 
  -- dashes to bangs; backslash to pound; invert alphabet
  set myText1 = ["-a-b-c\d-\é-f-" & ""]
  set myText2 = ["\a-b-c\d-e\" & ""]
  -- put "before" && myText1 && myText2
  if (re_tr(myText1, "-a-z\", "!z-a#") <> 13) then Blech "Test_PRegEx_Translate 201a"
  if (myText1 <> ["!z!y!x#w!#é!u!"]) then Blech "Test_PRegEx_Translate 201b"
  if (re_tr(myText2, "-a-z\", "!z-a#") <> 11) then Blech "Test_PRegEx_Translate 202a"
  if (myText2 <> ["#z!y!x#w!v#"]) then Blech "Test_PRegEx_Translate 202b"
  -- put "after" && myText1 && myText2
  
  -- test workaround 2
  -- dashes to bangs; backslash to pound; invert alphabet
  set myText3 = ["-x-b-c\d-\e-y-" & ""]
  set myText4 = ["\z-b-c\d-a\" & ""]
  if (re_tr(myText3, ",-.[-]a-z", ",!.[#]z-a") <> 14) then Blech "Test_PRegEx_Translate 203a"
  if (myText3 <> ["!c!y!x#w!#v!b!"]) then Blech "Test_PRegEx_Translate 203b"
  if (re_tr(myText4, ",-.[-]a-z", ",!.[#]z-a") <> 11) then Blech "Test_PRegEx_Translate 204a"
  if (myText4 <> ["#a!y!x#w!z#"]) then Blech "Test_PRegEx_Translate 204b"

  -- leak test
  if (LeakTestingSelected()) then
    set fBytes = void
    repeat with iterNum = 1 to 10000
      set myList = ["foo"]
      if (PRegEx_Translate(myList, "", "") <> 0 or myList[1] <> "foo") then Blech "Test_PRegEx_Translate L101"
      set myList = [re_i("abcdwxyz")] -- test rot13 encryption and back again
      if (PRegEx_Translate(myList, "a-z", "n-za-m") <> 8 or myList[1] <> "nopqjklm") then Blech "Test_PRegEx_Translate L104a"
      if (PRegEx_Translate(myList, "a-z", "n-za-m") <> 8 or myList[1] <> "abcdwxyz") then Blech "Test_PRegEx_Translate L104b"
      
      if iterNum mod 200 = 0 then -- measure memory after 1/50th of the iterations
        if fBytes = void then set fBytes = the freeBytes
        -- put iterNum && the freeBytes -- remember: uncommenting this uses up memory in the Message window's buffer!
      end if
    end repeat
    -- Measure memory again after all 100% of iterations have happened.   There should be no change.
    if abs(fBytes - the freeBytes)>100 then Blech "PRegEx_Translate Leak" && (the freeBytes - fBytes)
  end if
  
end Test_PRegEx_Translate
