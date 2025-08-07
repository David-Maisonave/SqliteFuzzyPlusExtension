select Source1, Source2
, SameSound(Source1, Source2, "EnPhoneticDistance") as ed -- Microsoft.PhoneticMatching
, SameSound(Source1, Source2, "fuzzy_soundex") as sx -- compare using soundex, and soundex results must be equal
, SameSound(Source1, Source2, "Caverphone2") as cp2 -- compare using Caverphone2, and Caverphone2 results must be equal
, SameSound(Source1, Source2, "Soundex") as sx2 -- compare using Soundex(C#), and Soundex(C#) results must be equal
, SameSound(Source1, Source2, "fuzzy_phonetic") as fp -- compare using phonetic, and phonetic results must be equal
, SameSound(Source1, Source2, "fuzzy_rsoundex") as sr -- compare using rsoundex, and rsoundex results must be equal
, SameSound(Source1, Source2, "fuzzy_caver") as fc -- compare using caver, and caver results must be equal
, SameSound(Source1, Source2, "fuzzy_translit") as ft -- compare using transliteration, and transliteration results must be equal
, SameSound(Source1, Source2, "fuzzy_soundex", "Levenshtein") as sx_L_VS -- compare using soundex, and soundex results must be VERY similar using Levenshtein distance
, SameSound(Source1, Source2, "fuzzy_phonetic", "Levenshtein") as fp_L_VS -- compare using phonetic, and phonetic results must be VERY similar using Levenshtein distance
, SameSound(Source1, Source2, "fuzzy_rsoundex", "Levenshtein", TRUE) as sr_L_VS -- compare using rsoundex, and rsoundex results must be VERY similar using Levenshtein distance
, SameSound(Source1, Source2, "fuzzy_soundex", "DamerauLevenshtein", TRUE) as sx_DL_VS -- compare using soundex, and soundex results must be VERY similar using DamerauLevenshtein distance
, SameSound(Source1, Source2, "fuzzy_phonetic", "JaroWinkler", TRUE) as fp_JW_VS -- compare using soundex, and soundex results must be VERY similar using JaroWinkler distance
, SameSound(Source1, Source2, "EnPhoneticDistance", "SameSound_StrCmp", 0) as ed_L_S -- Microsoft.PhoneticMatching similar
, SameSound(Source1, Source2, "fuzzy_soundex", "Levenshtein", 0) as sx_S -- compare using soundex, and soundex results must be only similar using Levenshtein distance
, SameSound(Source1, Source2, "fuzzy_phonetic", "Levenshtein", FALSE) as fp_S -- compare using phonetic, and phonetic results must be only similar using Levenshtein distance
, SameSound(Source1, Source2, "fuzzy_rsoundex", "Levenshtein", FALSE) as sr_S -- compare using rsoundex, and rsoundex results must be only similar using Levenshtein distance
, SameSound(Source1, Source2, "fuzzy_soundex", "DamerauLevenshtein", 0) as sx_DL_S -- compare using soundex, and soundex results must be only similar using DamerauLevenshtein distance
, SameSound(Source1, Source2, "fuzzy_phonetic", "JaroWinkler", 0) as fp_JW_S -- compare using soundex, and soundex results must be VERY similar using JaroWinkler distance
, soundex(Source1) as s0, soundex(Source1) as s1, rsoundex(Source1) as r0, rsoundex(Source2) as r1, fuzzy_phonetic(Source1) as p0, fuzzy_phonetic(Source2) as p1, fuzzy_caver(Source1) as c0, fuzzy_caver(Source2) as c1
, fuzzy_translit(Source1) as t0, fuzzy_translit(Source2) as t1, Caverphone2(Source1) as c02, Caverphone2(Source2) as c12, Soundex2(Source1) as s02, Soundex2(Source2) as s12
FROM SimilarSoundingWords1To1_AllMatch

--SELECT load_extension('E:\_\David-Maisonave\GameLauncher\SqliteFuzzyPlusExtension\SqliteFuzzyPlusExtension.PhoneticMatching\Debug\SqliteFuzzyPlusExtensionWithMsPhoneticMatching.dll');
--SELECT load_extension('E:\_\David-Maisonave\GameLauncher\SqliteFuzzyPlusExtension\SqliteFuzzyPlusExtension\Debug\SqliteFuzzyPlusExtension.dll');
