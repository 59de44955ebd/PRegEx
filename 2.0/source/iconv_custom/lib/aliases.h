/* ANSI-C code produced by gperf version 3.0.3 */
/* Command-line: gperf -m 10 lib/aliases.gperf  */
/* Computed positions: -k'1,3-11,$' */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
#error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gnu-gperf@gnu.org>."
#endif

#line 1 "lib/aliases.gperf"
struct alias { int name; unsigned int encoding_index; };

#define TOTAL_KEYWORDS 351
#define MIN_WORD_LENGTH 2
#define MAX_WORD_LENGTH 45
#define MIN_HASH_VALUE 18
#define MAX_HASH_VALUE 978
/* maximum key range = 961, duplicates = 0 */

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
static unsigned int
aliases_hash (register const char *str, register unsigned int len)
{
  static const unsigned short asso_values[] =
    {
      979, 979, 979, 979, 979, 979, 979, 979, 979, 979,
      979, 979, 979, 979, 979, 979, 979, 979, 979, 979,
      979, 979, 979, 979, 979, 979, 979, 979, 979, 979,
      979, 979, 979, 979, 979, 979, 979, 979, 979, 979,
      979, 979, 979, 979, 979,   5,  43, 979,  89,   7,
       33, 106,  15,  17,   5, 157,  23,  25, 344, 979,
      979, 979, 979, 979, 979, 154, 197,  11,  39,  15,
      157,  12, 117,   6, 268, 128,  14, 156,   5,   6,
       59, 979,   5,   6,  26, 219,  21, 164, 152,  20,
       42, 979, 979, 979, 979,   6, 979, 979, 979, 979,
      979, 979, 979, 979, 979, 979, 979, 979, 979, 979,
      979, 979, 979, 979, 979, 979, 979, 979, 979, 979,
      979, 979, 979, 979, 979, 979, 979, 979
    };
  register int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[(unsigned char)str[10]];
      /*FALLTHROUGH*/
      case 10:
        hval += asso_values[(unsigned char)str[9]];
      /*FALLTHROUGH*/
      case 9:
        hval += asso_values[(unsigned char)str[8]];
      /*FALLTHROUGH*/
      case 8:
        hval += asso_values[(unsigned char)str[7]];
      /*FALLTHROUGH*/
      case 7:
        hval += asso_values[(unsigned char)str[6]];
      /*FALLTHROUGH*/
      case 6:
        hval += asso_values[(unsigned char)str[5]];
      /*FALLTHROUGH*/
      case 5:
        hval += asso_values[(unsigned char)str[4]];
      /*FALLTHROUGH*/
      case 4:
        hval += asso_values[(unsigned char)str[3]];
      /*FALLTHROUGH*/
      case 3:
        hval += asso_values[(unsigned char)str[2]];
      /*FALLTHROUGH*/
      case 2:
      case 1:
        hval += asso_values[(unsigned char)str[0]];
        break;
    }
  return hval + asso_values[(unsigned char)str[len - 1]];
}

struct stringpool_t
  {
    char stringpool_str18[sizeof("CN")];
    char stringpool_str21[sizeof("L6")];
    char stringpool_str23[sizeof("L1")];
    char stringpool_str28[sizeof("SJIS")];
    char stringpool_str30[sizeof("R8")];
    char stringpool_str31[sizeof("L4")];
    char stringpool_str33[sizeof("L5")];
    char stringpool_str36[sizeof("866")];
    char stringpool_str39[sizeof("L8")];
    char stringpool_str49[sizeof("L2")];
    char stringpool_str51[sizeof("ISO-IR-6")];
    char stringpool_str52[sizeof("EUCCN")];
    char stringpool_str54[sizeof("CP866")];
    char stringpool_str58[sizeof("EUC-CN")];
    char stringpool_str61[sizeof("TCVN")];
    char stringpool_str62[sizeof("VISCII")];
    char stringpool_str64[sizeof("C99")];
    char stringpool_str65[sizeof("ISO-IR-166")];
    char stringpool_str67[sizeof("LATIN6")];
    char stringpool_str70[sizeof("CP154")];
    char stringpool_str71[sizeof("LATIN1")];
    char stringpool_str72[sizeof("ISO646-CN")];
    char stringpool_str79[sizeof("ISO-IR-14")];
    char stringpool_str80[sizeof("CHINESE")];
    char stringpool_str81[sizeof("CSVISCII")];
    char stringpool_str84[sizeof("CP1256")];
    char stringpool_str86[sizeof("CYRILLIC")];
    char stringpool_str87[sizeof("LATIN4")];
    char stringpool_str88[sizeof("CP1251")];
    char stringpool_str89[sizeof("ISO-IR-165")];
    char stringpool_str91[sizeof("LATIN5")];
    char stringpool_str92[sizeof("862")];
    char stringpool_str93[sizeof("ISO-IR-126")];
    char stringpool_str95[sizeof("ISO-IR-144")];
    char stringpool_str96[sizeof("CP819")];
    char stringpool_str103[sizeof("LATIN8")];
    char stringpool_str104[sizeof("CP1254")];
    char stringpool_str105[sizeof("ISO-IR-58")];
    char stringpool_str106[sizeof("CP949")];
    char stringpool_str108[sizeof("CP1255")];
    char stringpool_str110[sizeof("CP862")];
    char stringpool_str111[sizeof("ISO-IR-148")];
    char stringpool_str113[sizeof("LATIN-9")];
    char stringpool_str115[sizeof("ISO-IR-149")];
    char stringpool_str117[sizeof("ISO-IR-159")];
    char stringpool_str118[sizeof("PT154")];
    char stringpool_str119[sizeof("ISO-IR-226")];
    char stringpool_str120[sizeof("CP1258")];
    char stringpool_str121[sizeof("ISO-CELTIC")];
    char stringpool_str122[sizeof("L3")];
    char stringpool_str123[sizeof("LATIN2")];
    char stringpool_str124[sizeof("ISO8859-6")];
    char stringpool_str125[sizeof("ISO-IR-199")];
    char stringpool_str128[sizeof("ISO8859-1")];
    char stringpool_str130[sizeof("ISO-8859-6")];
    char stringpool_str131[sizeof("ISO_8859-6")];
    char stringpool_str132[sizeof("ISO8859-16")];
    char stringpool_str134[sizeof("ISO-8859-1")];
    char stringpool_str135[sizeof("ISO_8859-1")];
    char stringpool_str136[sizeof("ISO8859-11")];
    char stringpool_str137[sizeof("VISCII1.1-1")];
    char stringpool_str138[sizeof("ISO-8859-16")];
    char stringpool_str139[sizeof("ISO_8859-16")];
    char stringpool_str140[sizeof("CP1252")];
    char stringpool_str141[sizeof("ISO_646.IRV:1991")];
    char stringpool_str142[sizeof("ISO-8859-11")];
    char stringpool_str143[sizeof("ISO_8859-11")];
    char stringpool_str144[sizeof("ISO8859-4")];
    char stringpool_str146[sizeof("ISO_8859-16:2001")];
    char stringpool_str148[sizeof("ISO8859-5")];
    char stringpool_str149[sizeof("CP1361")];
    char stringpool_str150[sizeof("ISO-8859-4")];
    char stringpool_str151[sizeof("ISO_8859-4")];
    char stringpool_str152[sizeof("ISO8859-14")];
    char stringpool_str153[sizeof("ISO-IR-101")];
    char stringpool_str154[sizeof("ISO-8859-5")];
    char stringpool_str155[sizeof("ISO_8859-5")];
    char stringpool_str156[sizeof("ISO8859-15")];
    char stringpool_str157[sizeof("CP936")];
    char stringpool_str158[sizeof("ISO-8859-14")];
    char stringpool_str159[sizeof("ISO_8859-14")];
    char stringpool_str160[sizeof("ISO8859-8")];
    char stringpool_str161[sizeof("HZ")];
    char stringpool_str162[sizeof("ISO-8859-15")];
    char stringpool_str163[sizeof("ISO_8859-15")];
    char stringpool_str164[sizeof("ISO8859-9")];
    char stringpool_str165[sizeof("ELOT_928")];
    char stringpool_str166[sizeof("ISO-8859-8")];
    char stringpool_str167[sizeof("ISO_8859-8")];
    char stringpool_str168[sizeof("RK1048")];
    char stringpool_str169[sizeof("EUCKR")];
    char stringpool_str170[sizeof("ISO-8859-9")];
    char stringpool_str171[sizeof("ISO_8859-9")];
    char stringpool_str172[sizeof("ISO_8859-14:1998")];
    char stringpool_str173[sizeof("L7")];
    char stringpool_str174[sizeof("ISO_8859-15:1998")];
    char stringpool_str175[sizeof("EUC-KR")];
    char stringpool_str178[sizeof("KOI8-R")];
    char stringpool_str179[sizeof("CHAR")];
    char stringpool_str180[sizeof("ISO8859-2")];
    char stringpool_str181[sizeof("MAC")];
    char stringpool_str186[sizeof("ISO-8859-2")];
    char stringpool_str187[sizeof("ISO_8859-2")];
    char stringpool_str188[sizeof("ASCII")];
    char stringpool_str189[sizeof("ISO-IR-109")];
    char stringpool_str190[sizeof("PTCP154")];
    char stringpool_str191[sizeof("CSKOI8R")];
    char stringpool_str195[sizeof("L10")];
    char stringpool_str202[sizeof("ISO-IR-138")];
    char stringpool_str204[sizeof("850")];
    char stringpool_str206[sizeof("IBM866")];
    char stringpool_str207[sizeof("CSASCII")];
    char stringpool_str211[sizeof("MS-EE")];
    char stringpool_str213[sizeof("CP932")];
    char stringpool_str220[sizeof("KOI8-T")];
    char stringpool_str222[sizeof("GREEK8")];
    char stringpool_str226[sizeof("CP874")];
    char stringpool_str227[sizeof("US")];
    char stringpool_str229[sizeof("CSPTCP154")];
    char stringpool_str230[sizeof("GB2312")];
    char stringpool_str232[sizeof("MS-CYRL")];
    char stringpool_str234[sizeof("CP850")];
    char stringpool_str235[sizeof("ISO-IR-110")];
    char stringpool_str236[sizeof("CP950")];
    char stringpool_str242[sizeof("ISO-2022-CN")];
    char stringpool_str243[sizeof("LATIN10")];
    char stringpool_str244[sizeof("UHC")];
    char stringpool_str247[sizeof("BIG5")];
    char stringpool_str248[sizeof("IBM819")];
    char stringpool_str249[sizeof("CSISO2022CN")];
    char stringpool_str251[sizeof("CYRILLIC-ASIAN")];
    char stringpool_str252[sizeof("CP1250")];
    char stringpool_str253[sizeof("BIG-5")];
    char stringpool_str254[sizeof("TIS620")];
    char stringpool_str255[sizeof("CSISOLATIN6")];
    char stringpool_str256[sizeof("ISO_8859-10:1992")];
    char stringpool_str257[sizeof("ISO-IR-179")];
    char stringpool_str259[sizeof("CSISOLATIN1")];
    char stringpool_str260[sizeof("TIS-620")];
    char stringpool_str262[sizeof("IBM862")];
    char stringpool_str263[sizeof("X0212")];
    char stringpool_str265[sizeof("UCS-4")];
    char stringpool_str266[sizeof("CSBIG5")];
    char stringpool_str267[sizeof("ISO-2022-CN-EXT")];
    char stringpool_str269[sizeof("LATIN3")];
    char stringpool_str271[sizeof("GBK")];
    char stringpool_str272[sizeof("CN-BIG5")];
    char stringpool_str274[sizeof("CSISOLATINCYRILLIC")];
    char stringpool_str275[sizeof("CSISOLATIN4")];
    char stringpool_str276[sizeof("MACCYRILLIC")];
    char stringpool_str278[sizeof("KSC_5601")];
    char stringpool_str279[sizeof("CSISOLATIN5")];
    char stringpool_str282[sizeof("ISO646-US")];
    char stringpool_str283[sizeof("CSUCS4")];
    char stringpool_str286[sizeof("CP1253")];
    char stringpool_str287[sizeof("GEORGIAN-PS")];
    char stringpool_str290[sizeof("CN-GB-ISOIR165")];
    char stringpool_str293[sizeof("X0201")];
    char stringpool_str295[sizeof("TCVN5712-1")];
    char stringpool_str296[sizeof("UCS-4LE")];
    char stringpool_str297[sizeof("KZ-1048")];
    char stringpool_str300[sizeof("ISO8859-10")];
    char stringpool_str301[sizeof("UCS-2")];
    char stringpool_str302[sizeof("MS936")];
    char stringpool_str303[sizeof("GREEK")];
    char stringpool_str306[sizeof("ISO-8859-10")];
    char stringpool_str307[sizeof("ISO_8859-10")];
    char stringpool_str311[sizeof("CSISOLATIN2")];
    char stringpool_str312[sizeof("GB_1988-80")];
    char stringpool_str313[sizeof("TCVN-5712")];
    char stringpool_str314[sizeof("UCS-2LE")];
    char stringpool_str317[sizeof("ISO-IR-100")];
    char stringpool_str318[sizeof("KOREAN")];
    char stringpool_str320[sizeof("KS_C_5601-1989")];
    char stringpool_str325[sizeof("X0208")];
    char stringpool_str326[sizeof("ISO8859-3")];
    char stringpool_str329[sizeof("JP")];
    char stringpool_str330[sizeof("TIS620.2529-1")];
    char stringpool_str332[sizeof("ISO-8859-3")];
    char stringpool_str333[sizeof("ISO_8859-3")];
    char stringpool_str334[sizeof("ISO8859-13")];
    char stringpool_str335[sizeof("UCS-4-INTERNAL")];
    char stringpool_str336[sizeof("CSUNICODE")];
    char stringpool_str338[sizeof("UNICODE-1-1")];
    char stringpool_str340[sizeof("ISO-8859-13")];
    char stringpool_str341[sizeof("ISO_8859-13")];
    char stringpool_str344[sizeof("CSUNICODE11")];
    char stringpool_str345[sizeof("MS-ANSI")];
    char stringpool_str346[sizeof("CSKZ1048")];
    char stringpool_str349[sizeof("CP1133")];
    char stringpool_str350[sizeof("TIS620-0")];
    char stringpool_str353[sizeof("UCS-2-INTERNAL")];
    char stringpool_str356[sizeof("NEXTSTEP")];
    char stringpool_str359[sizeof("ISO-2022-KR")];
    char stringpool_str365[sizeof("CSISO14JISC6220RO")];
    char stringpool_str366[sizeof("CSISO2022KR")];
    char stringpool_str371[sizeof("LATIN7")];
    char stringpool_str372[sizeof("ROMAN8")];
    char stringpool_str373[sizeof("ISO-IR-57")];
    char stringpool_str377[sizeof("ISO-IR-203")];
    char stringpool_str379[sizeof("ISO-IR-87")];
    char stringpool_str381[sizeof("ISO-IR-157")];
    char stringpool_str382[sizeof("ECMA-114")];
    char stringpool_str385[sizeof("EUCTW")];
    char stringpool_str386[sizeof("IBM850")];
    char stringpool_str387[sizeof("MULELAO-1")];
    char stringpool_str388[sizeof("CP1257")];
    char stringpool_str389[sizeof("CSISOLATINGREEK")];
    char stringpool_str391[sizeof("EUC-TW")];
    char stringpool_str392[sizeof("ISO-10646-UCS-4")];
    char stringpool_str396[sizeof("UNICODELITTLE")];
    char stringpool_str397[sizeof("ISO-IR-127")];
    char stringpool_str398[sizeof("ECMA-118")];
    char stringpool_str399[sizeof("ARMSCII-8")];
    char stringpool_str401[sizeof("CSEUCKR")];
    char stringpool_str404[sizeof("UTF-16")];
    char stringpool_str406[sizeof("GEORGIAN-ACADEMY")];
    char stringpool_str410[sizeof("ISO-10646-UCS-2")];
    char stringpool_str413[sizeof("GB_2312-80")];
    char stringpool_str415[sizeof("CSISOLATINARABIC")];
    char stringpool_str416[sizeof("CSIBM866")];
    char stringpool_str417[sizeof("EUCJP")];
    char stringpool_str421[sizeof("US-ASCII")];
    char stringpool_str422[sizeof("GB18030")];
    char stringpool_str423[sizeof("EUC-JP")];
    char stringpool_str427[sizeof("CN-GB")];
    char stringpool_str428[sizeof("ISO8859-7")];
    char stringpool_str430[sizeof("BIGFIVE")];
    char stringpool_str432[sizeof("UTF-8")];
    char stringpool_str434[sizeof("ISO-8859-7")];
    char stringpool_str435[sizeof("ISO_8859-7")];
    char stringpool_str436[sizeof("BIG-FIVE")];
    char stringpool_str437[sizeof("ISO646-JP")];
    char stringpool_str440[sizeof("CSGB2312")];
    char stringpool_str441[sizeof("CP367")];
    char stringpool_str443[sizeof("MACCENTRALEUROPE")];
    char stringpool_str444[sizeof("EXTENDED_UNIX_CODE_PACKED_FORMAT_FOR_JAPANESE")];
    char stringpool_str445[sizeof("UTF-16LE")];
    char stringpool_str446[sizeof("STRK1048-2002")];
    char stringpool_str452[sizeof("KS_C_5601-1987")];
    char stringpool_str457[sizeof("CSISOLATIN3")];
    char stringpool_str459[sizeof("MACINTOSH")];
    char stringpool_str460[sizeof("MACICELAND")];
    char stringpool_str463[sizeof("WINDOWS-1256")];
    char stringpool_str465[sizeof("WINDOWS-1251")];
    char stringpool_str467[sizeof("CSISO159JISX02121990")];
    char stringpool_str472[sizeof("MS-GREEK")];
    char stringpool_str473[sizeof("WINDOWS-1254")];
    char stringpool_str475[sizeof("WINDOWS-1255")];
    char stringpool_str476[sizeof("CSKSC56011987")];
    char stringpool_str477[sizeof("WINDOWS-1252-FULL")];
    char stringpool_str478[sizeof("MACGREEK")];
    char stringpool_str479[sizeof("UCS-4BE")];
    char stringpool_str480[sizeof("CSISO57GB1988")];
    char stringpool_str481[sizeof("WINDOWS-1258")];
    char stringpool_str483[sizeof("MACTHAI")];
    char stringpool_str484[sizeof("TIS620.2533-1")];
    char stringpool_str486[sizeof("JIS_C6220-1969-RO")];
    char stringpool_str491[sizeof("WINDOWS-1252")];
    char stringpool_str494[sizeof("UNICODE-1-1-UTF-7")];
    char stringpool_str495[sizeof("SHIFT-JIS")];
    char stringpool_str496[sizeof("SHIFT_JIS")];
    char stringpool_str497[sizeof("UCS-2BE")];
    char stringpool_str498[sizeof("CSUNICODE11UTF7")];
    char stringpool_str499[sizeof("JIS_C6226-1983")];
    char stringpool_str503[sizeof("HP-ROMAN8")];
    char stringpool_str505[sizeof("WCHAR_T")];
    char stringpool_str506[sizeof("MACROMAN")];
    char stringpool_str507[sizeof("MS-HEBR")];
    char stringpool_str508[sizeof("ISO_8859-4:1988")];
    char stringpool_str509[sizeof("BIG5HKSCS")];
    char stringpool_str510[sizeof("ISO_8859-5:1988")];
    char stringpool_str515[sizeof("BIG5-HKSCS")];
    char stringpool_str516[sizeof("ISO_8859-8:1988")];
    char stringpool_str519[sizeof("ANSI_X3.4-1986")];
    char stringpool_str520[sizeof("ISO_8859-9:1989")];
    char stringpool_str521[sizeof("CSISO58GB231280")];
    char stringpool_str524[sizeof("CSPC862LATINHEBREW")];
    char stringpool_str529[sizeof("CP1252FULL")];
    char stringpool_str531[sizeof("CSISOLATINHEBREW")];
    char stringpool_str533[sizeof("UNICODEBIG")];
    char stringpool_str537[sizeof("ANSI_X3.4-1968")];
    char stringpool_str538[sizeof("JIS0208")];
    char stringpool_str539[sizeof("ARABIC")];
    char stringpool_str541[sizeof("WINDOWS-936")];
    char stringpool_str547[sizeof("WINDOWS-1250")];
    char stringpool_str550[sizeof("MACCROATIAN")];
    char stringpool_str557[sizeof("ISO-2022-JP-1")];
    char stringpool_str558[sizeof("HZ-GB-2312")];
    char stringpool_str559[sizeof("UTF-32")];
    char stringpool_str564[sizeof("WINDOWS-1253")];
    char stringpool_str566[sizeof("TIS620.2533-0")];
    char stringpool_str569[sizeof("CSHPROMAN8")];
    char stringpool_str572[sizeof("UTF-32LE")];
    char stringpool_str579[sizeof("IBM-CP1133")];
    char stringpool_str583[sizeof("ISO-2022-JP-2")];
    char stringpool_str589[sizeof("CSISO2022JP2")];
    char stringpool_str592[sizeof("MACFULL")];
    char stringpool_str593[sizeof("IBM367")];
    char stringpool_str599[sizeof("ISO_8859-3:1988")];
    char stringpool_str601[sizeof("JAVA")];
    char stringpool_str606[sizeof("KOI8-U")];
    char stringpool_str607[sizeof("ISO-2022-JP")];
    char stringpool_str610[sizeof("WINDOWS-874")];
    char stringpool_str612[sizeof("KOI8-RU")];
    char stringpool_str614[sizeof("CSISO2022JP")];
    char stringpool_str615[sizeof("WINDOWS-1257")];
    char stringpool_str617[sizeof("CSEUCTW")];
    char stringpool_str619[sizeof("CSSHIFTJIS")];
    char stringpool_str621[sizeof("ASMO-708")];
    char stringpool_str626[sizeof("CSMACINTOSH")];
    char stringpool_str628[sizeof("UTF-16BE")];
    char stringpool_str632[sizeof("ISO_8859-6:1987")];
    char stringpool_str634[sizeof("ISO_8859-1:1987")];
    char stringpool_str636[sizeof("JIS_X0212")];
    char stringpool_str658[sizeof("CSPC850MULTILINGUAL")];
    char stringpool_str660[sizeof("ISO_8859-2:1987")];
    char stringpool_str666[sizeof("JIS_X0201")];
    char stringpool_str668[sizeof("HEBREW")];
    char stringpool_str674[sizeof("MS-TURK")];
    char stringpool_str679[sizeof("CSISO87JISX0208")];
    char stringpool_str698[sizeof("JIS_X0208")];
    char stringpool_str699[sizeof("JISX0201-1976")];
    char stringpool_str700[sizeof("UTF-7")];
    char stringpool_str709[sizeof("JIS_X0212-1990")];
    char stringpool_str714[sizeof("MACARABIC")];
    char stringpool_str724[sizeof("MACUKRAINE")];
    char stringpool_str733[sizeof("ISO_8859-7:2003")];
    char stringpool_str736[sizeof("MACINTOSHFULL")];
    char stringpool_str737[sizeof("MS_KANJI")];
    char stringpool_str743[sizeof("TCVN5712-1:1993")];
    char stringpool_str744[sizeof("UCS-4-SWAPPED")];
    char stringpool_str749[sizeof("JIS_X0212.1990-0")];
    char stringpool_str753[sizeof("MS-ANSI-FULL")];
    char stringpool_str755[sizeof("UTF-32BE")];
    char stringpool_str762[sizeof("UCS-2-SWAPPED")];
    char stringpool_str781[sizeof("JIS_X0208-1990")];
    char stringpool_str784[sizeof("ISO_8859-7:1987")];
    char stringpool_str798[sizeof("JIS_X0208-1983")];
    char stringpool_str801[sizeof("MACTURKISH")];
    char stringpool_str817[sizeof("MACROMANIA")];
    char stringpool_str853[sizeof("MACHEBREW")];
    char stringpool_str855[sizeof("CSEUCPKDFMTJAPANESE")];
    char stringpool_str865[sizeof("BIG5-HKSCS:2001")];
    char stringpool_str873[sizeof("BIG5-HKSCS:2004")];
    char stringpool_str875[sizeof("MS-ARAB")];
    char stringpool_str883[sizeof("BIG5-HKSCS:1999")];
    char stringpool_str893[sizeof("WINBALTRIM")];
    char stringpool_str909[sizeof("MACROMANFULL")];
    char stringpool_str938[sizeof("JOHAB")];
    char stringpool_str978[sizeof("CSHALFWIDTHKATAKANA")];
  };
static const struct stringpool_t stringpool_contents =
  {
    "CN",
    "L6",
    "L1",
    "SJIS",
    "R8",
    "L4",
    "L5",
    "866",
    "L8",
    "L2",
    "ISO-IR-6",
    "EUCCN",
    "CP866",
    "EUC-CN",
    "TCVN",
    "VISCII",
    "C99",
    "ISO-IR-166",
    "LATIN6",
    "CP154",
    "LATIN1",
    "ISO646-CN",
    "ISO-IR-14",
    "CHINESE",
    "CSVISCII",
    "CP1256",
    "CYRILLIC",
    "LATIN4",
    "CP1251",
    "ISO-IR-165",
    "LATIN5",
    "862",
    "ISO-IR-126",
    "ISO-IR-144",
    "CP819",
    "LATIN8",
    "CP1254",
    "ISO-IR-58",
    "CP949",
    "CP1255",
    "CP862",
    "ISO-IR-148",
    "LATIN-9",
    "ISO-IR-149",
    "ISO-IR-159",
    "PT154",
    "ISO-IR-226",
    "CP1258",
    "ISO-CELTIC",
    "L3",
    "LATIN2",
    "ISO8859-6",
    "ISO-IR-199",
    "ISO8859-1",
    "ISO-8859-6",
    "ISO_8859-6",
    "ISO8859-16",
    "ISO-8859-1",
    "ISO_8859-1",
    "ISO8859-11",
    "VISCII1.1-1",
    "ISO-8859-16",
    "ISO_8859-16",
    "CP1252",
    "ISO_646.IRV:1991",
    "ISO-8859-11",
    "ISO_8859-11",
    "ISO8859-4",
    "ISO_8859-16:2001",
    "ISO8859-5",
    "CP1361",
    "ISO-8859-4",
    "ISO_8859-4",
    "ISO8859-14",
    "ISO-IR-101",
    "ISO-8859-5",
    "ISO_8859-5",
    "ISO8859-15",
    "CP936",
    "ISO-8859-14",
    "ISO_8859-14",
    "ISO8859-8",
    "HZ",
    "ISO-8859-15",
    "ISO_8859-15",
    "ISO8859-9",
    "ELOT_928",
    "ISO-8859-8",
    "ISO_8859-8",
    "RK1048",
    "EUCKR",
    "ISO-8859-9",
    "ISO_8859-9",
    "ISO_8859-14:1998",
    "L7",
    "ISO_8859-15:1998",
    "EUC-KR",
    "KOI8-R",
    "CHAR",
    "ISO8859-2",
    "MAC",
    "ISO-8859-2",
    "ISO_8859-2",
    "ASCII",
    "ISO-IR-109",
    "PTCP154",
    "CSKOI8R",
    "L10",
    "ISO-IR-138",
    "850",
    "IBM866",
    "CSASCII",
    "MS-EE",
    "CP932",
    "KOI8-T",
    "GREEK8",
    "CP874",
    "US",
    "CSPTCP154",
    "GB2312",
    "MS-CYRL",
    "CP850",
    "ISO-IR-110",
    "CP950",
    "ISO-2022-CN",
    "LATIN10",
    "UHC",
    "BIG5",
    "IBM819",
    "CSISO2022CN",
    "CYRILLIC-ASIAN",
    "CP1250",
    "BIG-5",
    "TIS620",
    "CSISOLATIN6",
    "ISO_8859-10:1992",
    "ISO-IR-179",
    "CSISOLATIN1",
    "TIS-620",
    "IBM862",
    "X0212",
    "UCS-4",
    "CSBIG5",
    "ISO-2022-CN-EXT",
    "LATIN3",
    "GBK",
    "CN-BIG5",
    "CSISOLATINCYRILLIC",
    "CSISOLATIN4",
    "MACCYRILLIC",
    "KSC_5601",
    "CSISOLATIN5",
    "ISO646-US",
    "CSUCS4",
    "CP1253",
    "GEORGIAN-PS",
    "CN-GB-ISOIR165",
    "X0201",
    "TCVN5712-1",
    "UCS-4LE",
    "KZ-1048",
    "ISO8859-10",
    "UCS-2",
    "MS936",
    "GREEK",
    "ISO-8859-10",
    "ISO_8859-10",
    "CSISOLATIN2",
    "GB_1988-80",
    "TCVN-5712",
    "UCS-2LE",
    "ISO-IR-100",
    "KOREAN",
    "KS_C_5601-1989",
    "X0208",
    "ISO8859-3",
    "JP",
    "TIS620.2529-1",
    "ISO-8859-3",
    "ISO_8859-3",
    "ISO8859-13",
    "UCS-4-INTERNAL",
    "CSUNICODE",
    "UNICODE-1-1",
    "ISO-8859-13",
    "ISO_8859-13",
    "CSUNICODE11",
    "MS-ANSI",
    "CSKZ1048",
    "CP1133",
    "TIS620-0",
    "UCS-2-INTERNAL",
    "NEXTSTEP",
    "ISO-2022-KR",
    "CSISO14JISC6220RO",
    "CSISO2022KR",
    "LATIN7",
    "ROMAN8",
    "ISO-IR-57",
    "ISO-IR-203",
    "ISO-IR-87",
    "ISO-IR-157",
    "ECMA-114",
    "EUCTW",
    "IBM850",
    "MULELAO-1",
    "CP1257",
    "CSISOLATINGREEK",
    "EUC-TW",
    "ISO-10646-UCS-4",
    "UNICODELITTLE",
    "ISO-IR-127",
    "ECMA-118",
    "ARMSCII-8",
    "CSEUCKR",
    "UTF-16",
    "GEORGIAN-ACADEMY",
    "ISO-10646-UCS-2",
    "GB_2312-80",
    "CSISOLATINARABIC",
    "CSIBM866",
    "EUCJP",
    "US-ASCII",
    "GB18030",
    "EUC-JP",
    "CN-GB",
    "ISO8859-7",
    "BIGFIVE",
    "UTF-8",
    "ISO-8859-7",
    "ISO_8859-7",
    "BIG-FIVE",
    "ISO646-JP",
    "CSGB2312",
    "CP367",
    "MACCENTRALEUROPE",
    "EXTENDED_UNIX_CODE_PACKED_FORMAT_FOR_JAPANESE",
    "UTF-16LE",
    "STRK1048-2002",
    "KS_C_5601-1987",
    "CSISOLATIN3",
    "MACINTOSH",
    "MACICELAND",
    "WINDOWS-1256",
    "WINDOWS-1251",
    "CSISO159JISX02121990",
    "MS-GREEK",
    "WINDOWS-1254",
    "WINDOWS-1255",
    "CSKSC56011987",
    "WINDOWS-1252-FULL",
    "MACGREEK",
    "UCS-4BE",
    "CSISO57GB1988",
    "WINDOWS-1258",
    "MACTHAI",
    "TIS620.2533-1",
    "JIS_C6220-1969-RO",
    "WINDOWS-1252",
    "UNICODE-1-1-UTF-7",
    "SHIFT-JIS",
    "SHIFT_JIS",
    "UCS-2BE",
    "CSUNICODE11UTF7",
    "JIS_C6226-1983",
    "HP-ROMAN8",
    "WCHAR_T",
    "MACROMAN",
    "MS-HEBR",
    "ISO_8859-4:1988",
    "BIG5HKSCS",
    "ISO_8859-5:1988",
    "BIG5-HKSCS",
    "ISO_8859-8:1988",
    "ANSI_X3.4-1986",
    "ISO_8859-9:1989",
    "CSISO58GB231280",
    "CSPC862LATINHEBREW",
    "CP1252FULL",
    "CSISOLATINHEBREW",
    "UNICODEBIG",
    "ANSI_X3.4-1968",
    "JIS0208",
    "ARABIC",
    "WINDOWS-936",
    "WINDOWS-1250",
    "MACCROATIAN",
    "ISO-2022-JP-1",
    "HZ-GB-2312",
    "UTF-32",
    "WINDOWS-1253",
    "TIS620.2533-0",
    "CSHPROMAN8",
    "UTF-32LE",
    "IBM-CP1133",
    "ISO-2022-JP-2",
    "CSISO2022JP2",
    "MACFULL",
    "IBM367",
    "ISO_8859-3:1988",
    "JAVA",
    "KOI8-U",
    "ISO-2022-JP",
    "WINDOWS-874",
    "KOI8-RU",
    "CSISO2022JP",
    "WINDOWS-1257",
    "CSEUCTW",
    "CSSHIFTJIS",
    "ASMO-708",
    "CSMACINTOSH",
    "UTF-16BE",
    "ISO_8859-6:1987",
    "ISO_8859-1:1987",
    "JIS_X0212",
    "CSPC850MULTILINGUAL",
    "ISO_8859-2:1987",
    "JIS_X0201",
    "HEBREW",
    "MS-TURK",
    "CSISO87JISX0208",
    "JIS_X0208",
    "JISX0201-1976",
    "UTF-7",
    "JIS_X0212-1990",
    "MACARABIC",
    "MACUKRAINE",
    "ISO_8859-7:2003",
    "MACINTOSHFULL",
    "MS_KANJI",
    "TCVN5712-1:1993",
    "UCS-4-SWAPPED",
    "JIS_X0212.1990-0",
    "MS-ANSI-FULL",
    "UTF-32BE",
    "UCS-2-SWAPPED",
    "JIS_X0208-1990",
    "ISO_8859-7:1987",
    "JIS_X0208-1983",
    "MACTURKISH",
    "MACROMANIA",
    "MACHEBREW",
    "CSEUCPKDFMTJAPANESE",
    "BIG5-HKSCS:2001",
    "BIG5-HKSCS:2004",
    "MS-ARAB",
    "BIG5-HKSCS:1999",
    "WINBALTRIM",
    "MACROMANFULL",
    "JOHAB",
    "CSHALFWIDTHKATAKANA"
  };
#define stringpool ((const char *) &stringpool_contents)

static const struct alias aliases[] =
  {
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 293 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str18, ei_iso646_cn},
    {-1}, {-1},
#line 134 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str21, ei_iso8859_10},
    {-1},
#line 60 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str23, ei_iso8859_1},
    {-1}, {-1}, {-1}, {-1},
#line 313 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str28, ei_sjis},
    {-1},
#line 232 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str30, ei_hp_roman8},
#line 84 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str31, ei_iso8859_4},
    {-1},
#line 126 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str33, ei_iso8859_9},
    {-1}, {-1},
#line 210 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str36, ei_cp866},
    {-1}, {-1},
#line 151 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str39, ei_iso8859_14},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 68 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str49, ei_iso8859_2},
    {-1},
#line 16 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str51, ei_ascii},
#line 323 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str52, ei_euc_cn},
    {-1},
#line 208 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str54, ei_cp866},
    {-1}, {-1}, {-1},
#line 322 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str58, ei_euc_cn},
    {-1}, {-1},
#line 263 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str61, ei_tcvn},
#line 260 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str62, ei_viscii},
    {-1},
#line 51 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str64, ei_c99},
#line 257 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str65, ei_tis620},
    {-1},
#line 133 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str67, ei_iso8859_10},
    {-1}, {-1},
#line 241 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str70, ei_pt154},
#line 59 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str71, ei_iso8859_1},
#line 291 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str72, ei_iso646_cn},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 269 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str79, ei_iso646_jp},
#line 298 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str80, ei_gb2312},
#line 262 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str81, ei_viscii},
    {-1}, {-1},
#line 192 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str84, ei_cp1256},
    {-1},
#line 91 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str86, ei_iso8859_5},
#line 83 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str87, ei_iso8859_4},
#line 174 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str88, ei_cp1251},
#line 299 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str89, ei_isoir165},
    {-1},
#line 125 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str91, ei_iso8859_9},
#line 206 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str92, ei_cp862},
#line 107 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str93, ei_iso8859_7},
    {-1},
#line 90 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str95, ei_iso8859_5},
#line 57 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str96, ei_iso8859_1},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 150 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str103, ei_iso8859_14},
#line 186 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str104, ei_cp1254},
#line 296 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str105, ei_gb2312},
#line 355 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str106, ei_cp949},
    {-1},
#line 189 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str108, ei_cp1255},
    {-1},
#line 204 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str110, ei_cp862},
#line 124 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str111, ei_iso8859_9},
    {-1},
#line 158 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str113, ei_iso8859_15},
    {-1},
#line 304 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str115, ei_ksc5601},
    {-1},
#line 288 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str117, ei_jisx0212},
#line 239 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str118, ei_pt154},
#line 163 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str119, ei_iso8859_16},
#line 198 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str120, ei_cp1258},
#line 152 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str121, ei_iso8859_14},
#line 76 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str122, ei_iso8859_3},
#line 67 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str123, ei_iso8859_2},
#line 102 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str124, ei_iso8859_6},
#line 149 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str125, ei_iso8859_14},
    {-1}, {-1},
#line 62 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str128, ei_iso8859_1},
    {-1},
#line 94 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str130, ei_iso8859_6},
#line 95 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str131, ei_iso8859_6},
#line 166 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str132, ei_iso8859_16},
    {-1},
#line 53 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str134, ei_iso8859_1},
#line 54 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str135, ei_iso8859_1},
#line 139 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str136, ei_iso8859_11},
#line 261 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str137, ei_viscii},
#line 160 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str138, ei_iso8859_16},
#line 161 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str139, ei_iso8859_16},
#line 177 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str140, ei_cp1252},
#line 15 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str141, ei_ascii},
#line 137 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str142, ei_iso8859_11},
#line 138 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str143, ei_iso8859_11},
#line 86 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str144, ei_iso8859_4},
    {-1},
#line 162 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str146, ei_iso8859_16},
    {-1},
#line 93 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str148, ei_iso8859_5},
#line 358 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str149, ei_johab},
#line 79 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str150, ei_iso8859_4},
#line 80 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str151, ei_iso8859_4},
#line 153 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str152, ei_iso8859_14},
#line 66 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str153, ei_iso8859_2},
#line 87 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str154, ei_iso8859_5},
#line 88 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str155, ei_iso8859_5},
#line 159 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str156, ei_iso8859_15},
#line 328 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str157, ei_cp936},
#line 146 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str158, ei_iso8859_14},
#line 147 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str159, ei_iso8859_14},
#line 120 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str160, ei_iso8859_8},
#line 335 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str161, ei_hz},
#line 154 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str162, ei_iso8859_15},
#line 155 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str163, ei_iso8859_15},
#line 128 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str164, ei_iso8859_9},
#line 109 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str165, ei_iso8859_7},
#line 114 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str166, ei_iso8859_8},
#line 115 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str167, ei_iso8859_8},
#line 244 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str168, ei_rk1048},
#line 353 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str169, ei_euc_kr},
#line 121 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str170, ei_iso8859_9},
#line 122 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str171, ei_iso8859_9},
#line 148 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str172, ei_iso8859_14},
#line 144 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str173, ei_iso8859_13},
#line 156 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str174, ei_iso8859_15},
#line 352 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str175, ei_euc_kr},
    {-1}, {-1},
#line 167 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str178, ei_koi8_r},
#line 361 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str179, ei_local_char},
#line 70 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str180, ei_iso8859_2},
#line 214 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str181, ei_mac_roman},
    {-1}, {-1}, {-1}, {-1},
#line 63 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str186, ei_iso8859_2},
#line 64 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str187, ei_iso8859_2},
#line 13 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str188, ei_ascii},
#line 74 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str189, ei_iso8859_3},
#line 240 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str190, ei_pt154},
#line 168 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str191, ei_koi8_r},
    {-1}, {-1}, {-1},
#line 165 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str195, ei_iso8859_16},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 117 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str202, ei_iso8859_8},
    {-1},
#line 202 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str204, ei_cp850},
    {-1},
#line 209 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str206, ei_cp866},
#line 22 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str207, ei_ascii},
    {-1}, {-1}, {-1},
#line 173 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str211, ei_cp1250},
    {-1},
#line 316 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str213, ei_cp932},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 238 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str220, ei_koi8_t},
    {-1},
#line 110 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str222, ei_iso8859_7},
    {-1}, {-1}, {-1},
#line 258 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str226, ei_cp874},
#line 21 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str227, ei_ascii},
    {-1},
#line 243 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str229, ei_pt154},
#line 324 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str230, ei_euc_cn},
    {-1},
#line 176 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str232, ei_cp1251},
    {-1},
#line 200 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str234, ei_cp850},
#line 82 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str235, ei_iso8859_4},
#line 346 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str236, ei_cp950},
    {-1}, {-1}, {-1}, {-1}, {-1},
#line 332 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str242, ei_iso2022_cn},
#line 164 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str243, ei_iso8859_16},
#line 356 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str244, ei_cp949},
    {-1}, {-1},
#line 340 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str247, ei_ces_big5},
#line 58 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str248, ei_iso8859_1},
#line 333 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str249, ei_iso2022_cn},
    {-1},
#line 242 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str251, ei_pt154},
#line 171 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str252, ei_cp1250},
#line 341 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str253, ei_ces_big5},
#line 252 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str254, ei_tis620},
#line 135 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str255, ei_iso8859_10},
#line 131 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str256, ei_iso8859_10},
#line 142 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str257, ei_iso8859_13},
    {-1},
#line 61 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str259, ei_iso8859_1},
#line 251 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str260, ei_tis620},
    {-1},
#line 205 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str262, ei_cp862},
#line 287 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str263, ei_jisx0212},
    {-1},
#line 33 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str265, ei_ucs4},
#line 345 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str266, ei_ces_big5},
#line 334 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str267, ei_iso2022_cn_ext},
    {-1},
#line 75 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str269, ei_iso8859_3},
    {-1},
#line 327 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str271, ei_ces_gbk},
#line 344 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str272, ei_ces_big5},
    {-1},
#line 92 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str274, ei_iso8859_5},
#line 85 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str275, ei_iso8859_4},
#line 223 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str276, ei_mac_cyrillic},
    {-1},
#line 301 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str278, ei_ksc5601},
#line 127 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str279, ei_iso8859_9},
    {-1}, {-1},
#line 14 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str282, ei_ascii},
#line 35 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str283, ei_ucs4},
    {-1}, {-1},
#line 183 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str286, ei_cp1253},
#line 237 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str287, ei_georgian_ps},
    {-1}, {-1},
#line 300 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str290, ei_isoir165},
    {-1}, {-1},
#line 274 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str293, ei_jisx0201},
    {-1},
#line 265 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str295, ei_tcvn},
#line 37 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str296, ei_ucs4le},
#line 246 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str297, ei_rk1048},
    {-1}, {-1},
#line 136 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str300, ei_iso8859_10},
#line 24 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str301, ei_ucs2},
#line 329 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str302, ei_cp936},
#line 111 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str303, ei_iso8859_7},
    {-1}, {-1},
#line 129 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str306, ei_iso8859_10},
#line 130 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str307, ei_iso8859_10},
    {-1}, {-1}, {-1},
#line 69 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str311, ei_iso8859_2},
#line 290 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str312, ei_iso646_cn},
#line 264 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str313, ei_tcvn},
#line 31 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str314, ei_ucs2le},
    {-1}, {-1},
#line 56 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str317, ei_iso8859_1},
#line 306 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str318, ei_ksc5601},
    {-1},
#line 303 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str320, ei_ksc5601},
    {-1}, {-1}, {-1}, {-1},
#line 280 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str325, ei_jisx0208},
#line 78 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str326, ei_iso8859_3},
    {-1}, {-1},
#line 270 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str329, ei_iso646_jp},
#line 254 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str330, ei_tis620},
    {-1},
#line 71 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str332, ei_iso8859_3},
#line 72 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str333, ei_iso8859_3},
#line 145 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str334, ei_iso8859_13},
#line 49 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str335, ei_ucs4internal},
#line 26 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str336, ei_ucs2},
    {-1},
#line 29 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str338, ei_ucs2be},
    {-1},
#line 140 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str340, ei_iso8859_13},
#line 141 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str341, ei_iso8859_13},
    {-1}, {-1},
#line 30 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str344, ei_ucs2be},
#line 179 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str345, ei_cp1252},
#line 247 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str346, ei_rk1048},
    {-1}, {-1},
#line 249 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str349, ei_cp1133},
#line 253 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str350, ei_tis620},
    {-1}, {-1},
#line 47 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str353, ei_ucs2internal},
    {-1}, {-1},
#line 234 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str356, ei_nextstep},
    {-1}, {-1},
#line 359 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str359, ei_iso2022_kr},
    {-1}, {-1}, {-1}, {-1}, {-1},
#line 271 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str365, ei_iso646_jp},
#line 360 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str366, ei_iso2022_kr},
    {-1}, {-1}, {-1}, {-1},
#line 143 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str371, ei_iso8859_13},
#line 231 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str372, ei_hp_roman8},
#line 292 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str373, ei_iso646_cn},
    {-1}, {-1}, {-1},
#line 157 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str377, ei_iso8859_15},
    {-1},
#line 281 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str379, ei_jisx0208},
    {-1},
#line 132 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str381, ei_iso8859_10},
#line 98 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str382, ei_iso8859_6},
    {-1}, {-1},
#line 338 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str385, ei_euc_tw},
#line 201 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str386, ei_cp850},
#line 248 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str387, ei_mulelao},
#line 195 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str388, ei_cp1257},
#line 112 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str389, ei_iso8859_7},
    {-1},
#line 337 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str391, ei_euc_tw},
#line 34 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str392, ei_ucs4},
    {-1}, {-1}, {-1},
#line 32 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str396, ei_ucs2le},
#line 97 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str397, ei_iso8859_6},
#line 108 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str398, ei_iso8859_7},
#line 235 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str399, ei_armscii_8},
    {-1},
#line 354 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str401, ei_euc_kr},
    {-1}, {-1},
#line 38 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str404, ei_utf16},
    {-1},
#line 236 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str406, ei_georgian_academy},
    {-1}, {-1}, {-1},
#line 25 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str410, ei_ucs2},
    {-1}, {-1},
#line 295 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str413, ei_gb2312},
    {-1},
#line 101 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str415, ei_iso8859_6},
#line 211 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str416, ei_cp866},
#line 308 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str417, ei_euc_jp},
    {-1}, {-1}, {-1},
#line 12 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str421, ei_ascii},
#line 331 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str422, ei_gb18030},
#line 307 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str423, ei_euc_jp},
    {-1}, {-1}, {-1},
#line 325 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str427, ei_euc_cn},
#line 113 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str428, ei_iso8859_7},
    {-1},
#line 343 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str430, ei_ces_big5},
    {-1},
#line 23 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str432, ei_utf8},
    {-1},
#line 103 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str434, ei_iso8859_7},
#line 104 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str435, ei_iso8859_7},
#line 342 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str436, ei_ces_big5},
#line 268 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str437, ei_iso646_jp},
    {-1}, {-1},
#line 326 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str440, ei_euc_cn},
#line 19 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str441, ei_ascii},
    {-1},
#line 219 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str443, ei_mac_centraleurope},
#line 309 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str444, ei_euc_jp},
#line 40 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str445, ei_utf16le},
#line 245 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str446, ei_rk1048},
    {-1}, {-1}, {-1}, {-1}, {-1},
#line 302 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str452, ei_ksc5601},
    {-1}, {-1}, {-1}, {-1},
#line 77 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str457, ei_iso8859_3},
    {-1},
#line 213 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str459, ei_mac_roman},
#line 220 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str460, ei_mac_iceland},
    {-1}, {-1},
#line 193 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str463, ei_cp1256},
    {-1},
#line 175 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str465, ei_cp1251},
    {-1},
#line 289 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str467, ei_jisx0212},
    {-1}, {-1}, {-1}, {-1},
#line 185 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str472, ei_cp1253},
#line 187 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str473, ei_cp1254},
    {-1},
#line 190 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str475, ei_cp1255},
#line 305 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str476, ei_ksc5601},
#line 181 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str477, ei_cp1252full},
#line 225 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str478, ei_mac_greek},
#line 36 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str479, ei_ucs4be},
#line 294 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str480, ei_iso646_cn},
#line 199 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str481, ei_cp1258},
    {-1},
#line 229 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str483, ei_mac_thai},
#line 256 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str484, ei_tis620},
    {-1},
#line 267 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str486, ei_iso646_jp},
    {-1}, {-1}, {-1}, {-1},
#line 178 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str491, ei_cp1252},
    {-1}, {-1},
#line 45 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str494, ei_utf7},
#line 312 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str495, ei_sjis},
#line 311 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str496, ei_sjis},
#line 27 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str497, ei_ucs2be},
#line 46 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str498, ei_utf7},
#line 282 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str499, ei_jisx0208},
    {-1}, {-1}, {-1},
#line 230 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str503, ei_hp_roman8},
    {-1},
#line 362 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str505, ei_local_wchar_t},
#line 212 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str506, ei_mac_roman},
#line 191 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str507, ei_cp1255},
#line 81 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str508, ei_iso8859_4},
#line 350 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str509, ei_big5hkscs2004},
#line 89 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str510, ei_iso8859_5},
    {-1}, {-1}, {-1}, {-1},
#line 349 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str515, ei_big5hkscs2004},
#line 116 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str516, ei_iso8859_8},
    {-1}, {-1},
#line 18 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str519, ei_ascii},
#line 123 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str520, ei_iso8859_9},
#line 297 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str521, ei_gb2312},
    {-1}, {-1},
#line 207 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str524, ei_cp862},
    {-1}, {-1}, {-1}, {-1},
#line 180 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str529, ei_cp1252full},
    {-1},
#line 119 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str531, ei_iso8859_8},
    {-1},
#line 28 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str533, ei_ucs2be},
    {-1}, {-1}, {-1},
#line 17 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str537, ei_ascii},
#line 279 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str538, ei_jisx0208},
#line 100 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str539, ei_iso8859_6},
    {-1},
#line 330 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str541, ei_cp936},
    {-1}, {-1}, {-1}, {-1}, {-1},
#line 172 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str547, ei_cp1250},
    {-1}, {-1},
#line 221 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str550, ei_mac_croatian},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 319 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str557, ei_iso2022_jp1},
#line 336 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str558, ei_hz},
#line 41 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str559, ei_utf32},
    {-1}, {-1}, {-1}, {-1},
#line 184 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str564, ei_cp1253},
    {-1},
#line 255 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str566, ei_tis620},
    {-1}, {-1},
#line 233 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str569, ei_hp_roman8},
    {-1}, {-1},
#line 43 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str572, ei_utf32le},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 250 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str579, ei_cp1133},
    {-1}, {-1}, {-1},
#line 320 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str583, ei_iso2022_jp2},
    {-1}, {-1}, {-1}, {-1}, {-1},
#line 321 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str589, ei_iso2022_jp2},
    {-1}, {-1},
#line 218 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str592, ei_macromanfull},
#line 20 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str593, ei_ascii},
    {-1}, {-1}, {-1}, {-1}, {-1},
#line 73 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str599, ei_iso8859_3},
    {-1},
#line 52 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str601, ei_java},
    {-1}, {-1}, {-1}, {-1},
#line 169 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str606, ei_koi8_u},
#line 317 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str607, ei_iso2022_jp},
    {-1}, {-1},
#line 259 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str610, ei_cp874},
    {-1},
#line 170 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str612, ei_koi8_ru},
    {-1},
#line 318 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str614, ei_iso2022_jp},
#line 196 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str615, ei_cp1257},
    {-1},
#line 339 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str617, ei_euc_tw},
    {-1},
#line 315 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str619, ei_sjis},
    {-1},
#line 99 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str621, ei_iso8859_6},
    {-1}, {-1}, {-1}, {-1},
#line 215 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str626, ei_mac_roman},
    {-1},
#line 39 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str628, ei_utf16be},
    {-1}, {-1}, {-1},
#line 96 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str632, ei_iso8859_6},
    {-1},
#line 55 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str634, ei_iso8859_1},
    {-1},
#line 284 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str636, ei_jisx0212},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1},
#line 203 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str658, ei_cp850},
    {-1},
#line 65 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str660, ei_iso8859_2},
    {-1}, {-1}, {-1}, {-1}, {-1},
#line 272 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str666, ei_jisx0201},
    {-1},
#line 118 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str668, ei_iso8859_8},
    {-1}, {-1}, {-1}, {-1}, {-1},
#line 188 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str674, ei_cp1254},
    {-1}, {-1}, {-1}, {-1},
#line 283 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str679, ei_jisx0208},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 276 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str698, ei_jisx0208},
#line 273 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str699, ei_jisx0201},
#line 44 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str700, ei_utf7},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 286 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str709, ei_jisx0212},
    {-1}, {-1}, {-1}, {-1},
#line 228 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str714, ei_mac_arabic},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 224 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str724, ei_mac_ukraine},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 106 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str733, ei_iso8859_7},
    {-1}, {-1},
#line 217 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str736, ei_macromanfull},
#line 314 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str737, ei_sjis},
    {-1}, {-1}, {-1}, {-1}, {-1},
#line 266 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str743, ei_tcvn},
#line 50 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str744, ei_ucs4swapped},
    {-1}, {-1}, {-1}, {-1},
#line 285 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str749, ei_jisx0212},
    {-1}, {-1}, {-1},
#line 182 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str753, ei_cp1252full},
    {-1},
#line 42 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str755, ei_utf32be},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 48 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str762, ei_ucs2swapped},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 278 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str781, ei_jisx0208},
    {-1}, {-1},
#line 105 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str784, ei_iso8859_7},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1}, {-1},
#line 277 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str798, ei_jisx0208},
    {-1}, {-1},
#line 226 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str801, ei_mac_turkish},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 222 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str817, ei_mac_romania},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 227 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str853, ei_mac_hebrew},
    {-1},
#line 310 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str855, ei_euc_jp},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 348 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str865, ei_big5hkscs2001},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 351 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str873, ei_big5hkscs2004},
    {-1},
#line 194 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str875, ei_cp1256},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 347 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str883, ei_big5hkscs1999},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 197 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str893, ei_cp1257},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
#line 216 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str909, ei_macromanfull},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1},
#line 357 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str938, ei_johab},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1},
#line 275 "lib/aliases.gperf"
    {(int)(long)&((struct stringpool_t *)0)->stringpool_str978, ei_jisx0201}
  };

#ifdef __GNUC__
__inline
#ifdef __GNUC_STDC_INLINE__
__attribute__ ((__gnu_inline__))
#endif
#endif
const struct alias *
aliases_lookup (register const char *str, register unsigned int len)
{
  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = aliases_hash (str, len);

      if (key <= MAX_HASH_VALUE && key >= 0)
        {
          register int o = aliases[key].name;
          if (o >= 0)
            {
              register const char *s = o + stringpool;

              if (*str == *s && !strcmp (str + 1, s + 1))
                return &aliases[key];
            }
        }
    }
  return 0;
}
