on Test_PRegEx_QuoteMeta
  if (PRegEx_QuoteMeta("") <> "")                                                         then Blech "PRegEx_QuoteMeta 101" && PRegEx_MemError()
  if (re_quotemeta     ("+abc*-()") <> "\+abc\*\-\(\)")                                   then Blech "PRegEx_QuoteMeta 102" && PRegEx_MemError()
  if (re_quotemeta     (numtochar(0) & "+abc*-()" & numtochar(0)) <> "\0\+abc\*\-\(\)\0") then Blech "PRegEx_QuoteMeta 102b" && PRegEx_MemError()
  
  if (PRegEx_QuoteMeta("abc") <> "abc")                                                   then Blech "PRegEx_QuoteMeta 103" && PRegEx_MemError()
  if (PRegEx_QuoteMeta("a") <> "a")                                                       then Blech "PRegEx_QuoteMeta 104" && PRegEx_MemError()
  if (PRegEx_QuoteMeta("\\") <> "\\\\")                                                   then Blech "PRegEx_QuoteMeta 105" && PRegEx_MemError()
  if (PRegEx_QuoteMeta("*") <> "\*")                                                      then Blech "PRegEx_QuoteMeta 106" && PRegEx_MemError()
  
  -- Testing round-trip interpolate --> quotemeta, with null chars, both ways.
  if (re_quotemeta(re_i(numtochar(0) & "åßç\0")) <> "\0åßç\0")                            then Blech "PRegEx_QuoteMeta 107" && PRegEx_MemError()
  
  if (re_quotemeta("(日本語)") <> "\(日本語\)") then Blech "PRegEx_QuoteMeta 108" && PRegEx_MemError()
  
  -- leak test
  if (LeakTestingSelected()) then
    set fBytes = void
    repeat with iterNum = 1 to 10000
      -- test removed : director 11 now represents non-ASCII code differently than the previous version, this test should be
      -- rewritten in the future
      --          if (re_quotemeta(re_i(numtochar(0) & "åßç\0")) <> "\0\å\ß\ç\0")                                       then Blech "PRegEx_QuoteMeta 107" && PRegEx_MemError()
      if (PRegEx_QuoteMeta("") <> "")                                          then Blech "PRegEx_QuoteMeta 101" && PRegEx_MemError()
      if (re_quotemeta     ("+abc*-()") <> "\+abc\*\-\(\)") then Blech "PRegEx_QuoteMeta 102" && PRegEx_MemError()
      
      if iterNum mod 200 = 0 then
        if fBytes = void then set fBytes = the freeBytes
      end if
    end repeat
    if abs(fBytes - the freeBytes)>100 then Blech "PRegEx_ReplaceString Leak" && (the freeBytes - fBytes)
  end if
  
end Test_PRegEx_QuoteMeta