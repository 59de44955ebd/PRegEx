on Test_PRegEx_Interpolate
  if (PRegEx_Interpolate("") <> "" )then Blech "Test_PRegEx_Interpolate 101"
  if (PRegEx_Interpolate("abc") <> "abc") then Blech "Test_PRegEx_Interpolate 102"
  if (PRegEx_Interpolate("123\t") <> "123" & tab) then Blech "Test_PRegEx_Interpolate 103"
  
  if (PRegEx_Interpolate("123\n") <> "123" & return) then Blech "Test_PRegEx_Interpolate 104"
  if (PRegEx_Interpolate("12ü3\n") <> "12ü3" & return)         then Blech "Test_PRegEx_Interpolate 104a"
  if (PRegEx_Interpolate("123\n")  = "123" & enter)          then Blech "Test_PRegEx_Interpolate 104b"
  if (PRegEx_Interpolate("123\n")  = "123" & numToChar(10))  then Blech "Test_PRegEx_Interpolate 104c"
  
  if (PRegEx_Interpolate("123\x20") <> "123" & " ") then Blech "Test_PRegEx_Interpolate 105"
  if (PRegEx_Interpolate("123\x40") <> "123" & numtochar(64)) then Blech "Test_PRegEx_Interpolate 106"
  if (PRegEx_Interpolate("123\100") <> "123" & numtochar(64)) then Blech "Test_PRegEx_Interpolate 107"
  if (PRegEx_Interpolate("123\0") <> "123" & numtochar(0)) then Blech "Test_PRegEx_Interpolate 108"
  if (PRegEx_Search(["house"], "(\w+)") <> 1) then Blech "Test_PRegEx_Interpolate 109"
  if (PRegEx_Interpolate("123\1\2\0") <> "123house" & numtochar(0)) then Blech "Test_PRegEx_Interpolate 110a"
  if (PRegEx_Interpolate("123\1\2\x00") <> "123house" & numtochar(0)) then Blech "Test_PRegEx_Interpolate 110b"
  if (PRegEx_Interpolate("123\1\2\000") <> "123house" & numtochar(0)) then Blech "Test_PRegEx_Interpolate 110c"
  if (PRegEx_Interpolate("123\1\2\x{00}") <> "123house" & numtochar(0)) then Blech "Test_PRegEx_Interpolate 110d"
  
  if (PRegEx_Interpolate("${a}xxx${b}yyy${c}") <> "${a}xxx${b}yyy${c}") then Blech "Test_PRegEx_Interpolate 201"
  set myProps = ["a": "BOO", "c":"WAH", "b":1234, "d":"____"]
  if (PRegEx_Interpolate("${a}xxx${b}yyy${c}", myProps) <> "BOOxxxyyyWAH") then Blech "Test_PRegEx_Interpolate 202"
  set myProps = [#a: "BOO", #c:"WAH", #b:1234, #d:"____"]
  if (PRegEx_Interpolate("${#a}xxx${#b}yyy${#c}", myProps) <> "BOOxxxyyyWAH") then Blech "Test_PRegEx_Interpolate 203"
  
  -- Test high-numbered backrefs (26 of them in this case)
  if (PRegEx_Search(["ABCDEFGHIJKLMNOPQRSTUVWXYZ"], "(\w)(\w)(\w)(\w)(\w)(\w)(\w)(\w)(\w)(\w)(\w)(\w)(\w)(\w)(\w)(\w)(\w)(\w)(\w)(\w)(\w)(\w)(\w)(\w)(\w)(\w)") <> 1) then Blech "Test_PRegEx_Interpolate 204"
  if (PRegEx_Interpolate("1:\1 2:\2 10:\10 26:\26") <> "1:A 2:B 10:J 26:Z") then Blech "Test_PRegEx_Interpolate 205"
  
  -- Confirm that lower-case hex escapes work the same as upper-case ones.
if ( \
re_i("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2A\x2B\x2C\x2D\x2E\x2F\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x3A\x3B\x3C\x3D\x3E\x3F\x40\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4A\x4B\x4C\x4D\x4E\x4F\x50\x51\x52\x53\x54\x55\x56\x57\x58\x59\x5A\x5B\x5C\x5D\x5E\x5F\x60\x61\x62\x63\x64\x65\x66\x67\x68\x69\x6A\x6B\x6C\x6D\x6E\x6F\x70\x71\x72\x73\x74\x75\x76\x77\x78\x79\x7A\x7B\x7C\x7D\x7E\x7F\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8A\x8B\x8C\x8D\x8E\x8F\x90\x91\x92\x93\x94\x95\x96\x97\x98\x99\x9A\x9B\x9C\x9D\x9E\x9F\xA0\xA1\xA2\xA3\xA4\xA5\xA6\xA7\xA8\xA9\xAA\xAB\xAC\xAD\xAE\xAF\xB0\xB1\xB2\xB3\xB4\xB5\xB6\xB7\xB8\xB9\xBA\xBB\xBC\xBD\xBE\xBF\xC0\xC1\xC2\xC3\xC4\xC5\xC6\xC7\xC8\xC9\xCA\xCB\xCC\xCD\xCE\xCF\xD0\xD1\xD2\xD3\xD4\xD5\xD6\xD7\xD8\xD9\xDA\xDB\xDC\xDD\xDE\xDF\xE0\xE1\xE2\xE3\xE4\xE5\xE6\xE7\xE8\xE9\xEA\xEB\xEC\xED\xEE\xEF\xF0\xF1\xF2\xF3\xF4\xF5\xF6\xF7\xF8\xF9\xFA\xFB\xFC\xFD\xFE\xFF") \
<> \
re_i("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2a\x2b\x2c\x2d\x2e\x2f\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x3a\x3b\x3c\x3d\x3e\x3f\x40\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4a\x4b\x4c\x4d\x4e\x4f\x50\x51\x52\x53\x54\x55\x56\x57\x58\x59\x5a\x5b\x5c\x5d\x5e\x5f\x60\x61\x62\x63\x64\x65\x66\x67\x68\x69\x6a\x6b\x6c\x6d\x6e\x6f\x70\x71\x72\x73\x74\x75\x76\x77\x78\x79\x7a\x7b\x7c\x7d\x7e\x7f\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8a\x8b\x8c\x8d\x8e\x8f\x90\x91\x92\x93\x94\x95\x96\x97\x98\x99\x9a\x9b\x9c\x9d\x9e\x9f\xa0\xa1\xa2\xa3\xa4\xa5\xa6\xa7\xa8\xa9\xaa\xab\xac\xad\xae\xaf\xb0\xb1\xb2\xb3\xb4\xb5\xb6\xb7\xb8\xb9\xba\xbb\xbc\xbd\xbe\xbf\xc0\xc1\xc2\xc3\xc4\xc5\xc6\xc7\xc8\xc9\xca\xcb\xcc\xcd\xce\xcf\xd0\xd1\xd2\xd3\xd4\xd5\xd6\xd7\xd8\xd9\xda\xdb\xdc\xdd\xde\xdf\xe0\xe1\xe2\xe3\xe4\xe5\xe6\xe7\xe8\xe9\xea\xeb\xec\xed\xee\xef\xf0\xf1\xf2\xf3\xf4\xf5\xf6\xf7\xf8\xf9\xfa\xfb\xfc\xfd\xfe\xff") \
) then Blech "Test_PRegEx_Interpolate 301"

-- Confirm that hex escapes produce same results as (first 256) octal escapes.
if ( \
re_i("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2A\x2B\x2C\x2D\x2E\x2F\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x3A\x3B\x3C\x3D\x3E\x3F\x40\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4A\x4B\x4C\x4D\x4E\x4F\x50\x51\x52\x53\x54\x55\x56\x57\x58\x59\x5A\x5B\x5C\x5D\x5E\x5F\x60\x61\x62\x63\x64\x65\x66\x67\x68\x69\x6A\x6B\x6C\x6D\x6E\x6F\x70\x71\x72\x73\x74\x75\x76\x77\x78\x79\x7A\x7B\x7C\x7D\x7E\x7F\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8A\x8B\x8C\x8D\x8E\x8F\x90\x91\x92\x93\x94\x95\x96\x97\x98\x99\x9A\x9B\x9C\x9D\x9E\x9F\xA0\xA1\xA2\xA3\xA4\xA5\xA6\xA7\xA8\xA9\xAA\xAB\xAC\xAD\xAE\xAF\xB0\xB1\xB2\xB3\xB4\xB5\xB6\xB7\xB8\xB9\xBA\xBB\xBC\xBD\xBE\xBF\xC0\xC1\xC2\xC3\xC4\xC5\xC6\xC7\xC8\xC9\xCA\xCB\xCC\xCD\xCE\xCF\xD0\xD1\xD2\xD3\xD4\xD5\xD6\xD7\xD8\xD9\xDA\xDB\xDC\xDD\xDE\xDF\xE0\xE1\xE2\xE3\xE4\xE5\xE6\xE7\xE8\xE9\xEA\xEB\xEC\xED\xEE\xEF\xF0\xF1\xF2\xF3\xF4\xF5\xF6\xF7\xF8\xF9\xFA\xFB\xFC\xFD\xFE\xFF") \
<> \
re_i("\001\002\003\004\005\006\007\010\011\012\013\014\015\016\017\020\021\022\023\024\025\026\027\030\031\032\033\034\035\036\037\040\041\042\043\044\045\046\047\050\051\052\053\054\055\056\057\060\061\062\063\064\065\066\067\070\071\072\073\074\075\076\077\100\101\102\103\104\105\106\107\110\111\112\113\114\115\116\117\120\121\122\123\124\125\126\127\130\131\132\133\134\135\136\137\140\141\142\143\144\145\146\147\150\151\152\153\154\155\156\157\160\161\162\163\164\165\166\167\170\171\172\173\174\175\176\177\200\201\202\203\204\205\206\207\210\211\212\213\214\215\216\217\220\221\222\223\224\225\226\227\230\231\232\233\234\235\236\237\240\241\242\243\244\245\246\247\250\251\252\253\254\255\256\257\260\261\262\263\264\265\266\267\270\271\272\273\274\275\276\277\300\301\302\303\304\305\306\307\310\311\312\313\314\315\316\317\320\321\322\323\324\325\326\327\330\331\332\333\334\335\336\337\340\341\342\343\344\345\346\347\350\351\352\353\354\355\356\357\360\361\362\363\364\365\366\367\370\371\372\373\374\375\376\377") \
) then Blech "Test_PRegEx_Interpolate 302"

-- Confirm that \x{...} hex escapes produce the same results as (first 512) octal escapes
if ( \
re_i("\001\002\003\004\005\006\007\010\011\012\013\014\015\016\017\020\021\022\023\024\025\026\027\030\031\032\033\034\035\036\037\040\041\042\043\044\045\046\047\050\051\052\053\054\055\056\057\060\061\062\063\064\065\066\067\070\071\072\073\074\075\076\077\100\101\102\103\104\105\106\107\110\111\112\113\114\115\116\117\120\121\122\123\124\125\126\127\130\131\132\133\134\135\136\137\140\141\142\143\144\145\146\147\150\151\152\153\154\155\156\157\160\161\162\163\164\165\166\167\170\171\172\173\174\175\176\177\200\201\202\203\204\205\206\207\210\211\212\213\214\215\216\217\220\221\222\223\224\225\226\227\230\231\232\233\234\235\236\237\240\241\242\243\244\245\246\247\250\251\252\253\254\255\256\257\260\261\262\263\264\265\266\267\270\271\272\273\274\275\276\277\300\301\302\303\304\305\306\307\310\311\312\313\314\315\316\317\320\321\322\323\324\325\326\327\330\331\332\333\334\335\336\337\340\341\342\343\344\345\346\347\350\351\352\353\354\355\356\357\360\361\362\363\364\365\366\367\370\371\372\373\374\375\376\377\400\401\402\403\404\405\406\407\410\411\412\413\414\415\416\417\420\421\422\423\424\425\426\427\430\431\432\433\434\435\436\437\440\441\442\443\444\445\446\447\450\451\452\453\454\455\456\457\460\461\462\463\464\465\466\467\470\471\472\473\474\475\476\477\500\501\502\503\504\505\506\507\510\511\512\513\514\515\516\517\520\521\522\523\524\525\526\527\530\531\532\533\534\535\536\537\540\541\542\543\544\545\546\547\550\551\552\553\554\555\556\557\560\561\562\563\564\565\566\567\570\571\572\573\574\575\576\577\600\601\602\603\604\605\606\607\610\611\612\613\614\615\616\617\620\621\622\623\624\625\626\627\630\631\632\633\634\635\636\637\640\641\642\643\644\645\646\647\650\651\652\653\654\655\656\657\660\661\662\663\664\665\666\667\670\671\672\673\674\675\676\677\700\701\702\703\704\705\706\707\710\711\712\713\714\715\716\717\720\721\722\723\724\725\726\727\730\731\732\733\734\735\736\737\740\741\742\743\744\745\746\747\750\751\752\753\754\755\756\757\760\761\762\763\764\765\766\767\770\771\772\773\774\775\776\777") \
<> \
re_i("\x{1}\x{2}\x{3}\x{4}\x{5}\x{6}\x{7}\x{8}\x{9}\x{a}\x{b}\x{c}\x{d}\x{e}\x{f}\x{10}\x{11}\x{12}\x{13}\x{14}\x{15}\x{16}\x{17}\x{18}\x{19}\x{1a}\x{1b}\x{1c}\x{1d}\x{1e}\x{1f}\x{20}\x{21}\x{22}\x{23}\x{24}\x{25}\x{26}\x{27}\x{28}\x{29}\x{2a}\x{2b}\x{2c}\x{2d}\x{2e}\x{2f}\x{30}\x{31}\x{32}\x{33}\x{34}\x{35}\x{36}\x{37}\x{38}\x{39}\x{3a}\x{3b}\x{3c}\x{3d}\x{3e}\x{3f}\x{40}\x{41}\x{42}\x{43}\x{44}\x{45}\x{46}\x{47}\x{48}\x{49}\x{4a}\x{4b}\x{4c}\x{4d}\x{4e}\x{4f}\x{50}\x{51}\x{52}\x{53}\x{54}\x{55}\x{56}\x{57}\x{58}\x{59}\x{5a}\x{5b}\x{5c}\x{5d}\x{5e}\x{5f}\x{60}\x{61}\x{62}\x{63}\x{64}\x{65}\x{66}\x{67}\x{68}\x{69}\x{6a}\x{6b}\x{6c}\x{6d}\x{6e}\x{6f}\x{70}\x{71}\x{72}\x{73}\x{74}\x{75}\x{76}\x{77}\x{78}\x{79}\x{7a}\x{7b}\x{7c}\x{7d}\x{7e}\x{7f}\x{80}\x{81}\x{82}\x{83}\x{84}\x{85}\x{86}\x{87}\x{88}\x{89}\x{8a}\x{8b}\x{8c}\x{8d}\x{8e}\x{8f}\x{90}\x{91}\x{92}\x{93}\x{94}\x{95}\x{96}\x{97}\x{98}\x{99}\x{9a}\x{9b}\x{9c}\x{9d}\x{9e}\x{9f}\x{a0}\x{a1}\x{a2}\x{a3}\x{a4}\x{a5}\x{a6}\x{a7}\x{a8}\x{a9}\x{aa}\x{ab}\x{ac}\x{ad}\x{ae}\x{af}\x{b0}\x{b1}\x{b2}\x{b3}\x{b4}\x{b5}\x{b6}\x{b7}\x{b8}\x{b9}\x{ba}\x{bb}\x{bc}\x{bd}\x{be}\x{bf}\x{c0}\x{c1}\x{c2}\x{c3}\x{c4}\x{c5}\x{c6}\x{c7}\x{c8}\x{c9}\x{ca}\x{cb}\x{cc}\x{cd}\x{ce}\x{cf}\x{d0}\x{d1}\x{d2}\x{d3}\x{d4}\x{d5}\x{d6}\x{d7}\x{d8}\x{d9}\x{da}\x{db}\x{dc}\x{dd}\x{de}\x{df}\x{e0}\x{e1}\x{e2}\x{e3}\x{e4}\x{e5}\x{e6}\x{e7}\x{e8}\x{e9}\x{ea}\x{eb}\x{ec}\x{ed}\x{ee}\x{ef}\x{f0}\x{f1}\x{f2}\x{f3}\x{f4}\x{f5}\x{f6}\x{f7}\x{f8}\x{f9}\x{fa}\x{fb}\x{fc}\x{fd}\x{fe}\x{ff}\x{100}\x{101}\x{102}\x{103}\x{104}\x{105}\x{106}\x{107}\x{108}\x{109}\x{10a}\x{10b}\x{10c}\x{10d}\x{10e}\x{10f}\x{110}\x{111}\x{112}\x{113}\x{114}\x{115}\x{116}\x{117}\x{118}\x{119}\x{11a}\x{11b}\x{11c}\x{11d}\x{11e}\x{11f}\x{120}\x{121}\x{122}\x{123}\x{124}\x{125}\x{126}\x{127}\x{128}\x{129}\x{12a}\x{12b}\x{12c}\x{12d}\x{12e}\x{12f}\x{130}\x{131}\x{132}\x{133}\x{134}\x{135}\x{136}\x{137}\x{138}\x{139}\x{13a}\x{13b}\x{13c}\x{13d}\x{13e}\x{13f}\x{140}\x{141}\x{142}\x{143}\x{144}\x{145}\x{146}\x{147}\x{148}\x{149}\x{14a}\x{14b}\x{14c}\x{14d}\x{14e}\x{14f}\x{150}\x{151}\x{152}\x{153}\x{154}\x{155}\x{156}\x{157}\x{158}\x{159}\x{15a}\x{15b}\x{15c}\x{15d}\x{15e}\x{15f}\x{160}\x{161}\x{162}\x{163}\x{164}\x{165}\x{166}\x{167}\x{168}\x{169}\x{16a}\x{16b}\x{16c}\x{16d}\x{16e}\x{16f}\x{170}\x{171}\x{172}\x{173}\x{174}\x{175}\x{176}\x{177}\x{178}\x{179}\x{17a}\x{17b}\x{17c}\x{17d}\x{17e}\x{17f}\x{180}\x{181}\x{182}\x{183}\x{184}\x{185}\x{186}\x{187}\x{188}\x{189}\x{18a}\x{18b}\x{18c}\x{18d}\x{18e}\x{18f}\x{190}\x{191}\x{192}\x{193}\x{194}\x{195}\x{196}\x{197}\x{198}\x{199}\x{19a}\x{19b}\x{19c}\x{19d}\x{19e}\x{19f}\x{1a0}\x{1a1}\x{1a2}\x{1a3}\x{1a4}\x{1a5}\x{1a6}\x{1a7}\x{1a8}\x{1a9}\x{1aa}\x{1ab}\x{1ac}\x{1ad}\x{1ae}\x{1af}\x{1b0}\x{1b1}\x{1b2}\x{1b3}\x{1b4}\x{1b5}\x{1b6}\x{1b7}\x{1b8}\x{1b9}\x{1ba}\x{1bb}\x{1bc}\x{1bd}\x{1be}\x{1bf}\x{1c0}\x{1c1}\x{1c2}\x{1c3}\x{1c4}\x{1c5}\x{1c6}\x{1c7}\x{1c8}\x{1c9}\x{1ca}\x{1cb}\x{1cc}\x{1cd}\x{1ce}\x{1cf}\x{1d0}\x{1d1}\x{1d2}\x{1d3}\x{1d4}\x{1d5}\x{1d6}\x{1d7}\x{1d8}\x{1d9}\x{1da}\x{1db}\x{1dc}\x{1dd}\x{1de}\x{1df}\x{1e0}\x{1e1}\x{1e2}\x{1e3}\x{1e4}\x{1e5}\x{1e6}\x{1e7}\x{1e8}\x{1e9}\x{1ea}\x{1eb}\x{1ec}\x{1ed}\x{1ee}\x{1ef}\x{1f0}\x{1f1}\x{1f2}\x{1f3}\x{1f4}\x{1f5}\x{1f6}\x{1f7}\x{1f8}\x{1f9}\x{1fa}\x{1fb}\x{1fc}\x{1fd}\x{1fe}\x{1ff}") \
) then Blech "Test_PRegEx_Interpolate 303"

  -- leak test
  if (LeakTestingSelected()) then
    set fBytes = void
    repeat with iterNum = 1 to 10000
      if (PRegEx_Search(["house"], "(\w+)") <> 1) then Blech "Test_PRegEx_Interpolate 109"
      if (PRegEx_Interpolate("123\1\2\0") <> "123house" & numtochar(0)) then Blech "Test_PRegEx_Interpolate 110"
      
      if (PRegEx_Interpolate("${a}xxx${b}yyy${c}") <> "${a}xxx${b}yyy${c}") then Blech "Test_PRegEx_Interpolate 201"
      set myProps = ["a": "BOO", "c":"WAH", "b":1234, "d":"____"]
      if (PRegEx_Interpolate("${a}xxx${b}yyy${c}", myProps) <> "BOOxxxyyyWAH") then Blech "Test_PRegEx_Interpolate 202"
      
      if iterNum mod 200 = 0 then -- measure memory after 1/50th of the iterations
      if fBytes = void then set fBytes = the freeBytes
      -- put iterNum && the freeBytes -- remember: uncommenting this uses up memory in the Message window's buffer!
      end if
    end repeat
    -- Measure memory again after all 100% of iterations have happened.  There should be no change.
    if abs(fBytes - the freeBytes)>100 then Blech "Test_PRegEx_Interpolate Leak" && (the freeBytes - fBytes)
  end if

end Test_PRegEx_Interpolate