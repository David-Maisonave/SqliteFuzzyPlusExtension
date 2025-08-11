--SELECT load_extension('E:\_\David-Maisonave\GameLauncher\SqliteFuzzyPlusExtension\SqliteFuzzyPlusExtension.PhoneticMatching\Debug\SqliteFuzzyPlusExtensionWithMsPhoneticMatching.dll');
--SELECT load_extension('E:\_\David-Maisonave\GameLauncher\SqliteFuzzyPlusExtension\SqliteFuzzyPlusExtension\Debug\SqliteFuzzyPlusExtension.dll');

-- The goal in this test is to find "being" as a match for "been", but only EnPhoneticDistance pass this test with no false positives
-- fp_JW_VS (fuzzy_phonetic, JaroWinkler, TRUE) comes close, but it gives false matches for ban and bone
select Words
--, soundex(Words) as s, rsoundex(Words) as r, fuzzy_phonetic(Words) as p, fuzzy_caver(Words) as c, fuzzy_translit(Words) as t, Caverphone2(Words) as c2, Soundex2(Words) as s2
, SameSound(Words, "been", "EnPhoneticDistance") as ed -- 
, SameSound(Words, "been", "fuzzy_soundex") as sx -- compare using soundex, and soundex results must be equal
, SameSound(Words, "been", "Caverphone2") as sx2 -- compare using Caverphone2, and Caverphone2 results must be equal
, SameSound(Words, "been", "Soundex") as sx2 -- compare using Soundex(C#), and Soundex(C#) results must be equal
, SameSound(Words, "been", "fuzzy_phonetic") as fp -- compare using phonetic, and phonetic results must be equal
, SameSound(Words, "been", "fuzzy_rsoundex") as sr -- compare using rsoundex, and rsoundex results must be equal
, SameSound(Words, "been", "fuzzy_caver") as fc -- compare using caver, and caver results must be equal
, SameSound(Words, "been", "fuzzy_translit") as ft -- compare using transliteration, and transliteration results must be equal
, SameSound(Words, "been", "fuzzy_soundex", "Levenshtein") as sx_L_VS -- compare using soundex, and soundex results must be VERY similar using Levenshtein distance
, SameSound(Words, "been", "fuzzy_phonetic", "Levenshtein") as fp_L_VS -- compare using phonetic, and phonetic results must be VERY similar using Levenshtein distance
, SameSound(Words, "been", "fuzzy_rsoundex", "Levenshtein", TRUE) as sr_L_VS -- compare using rsoundex, and rsoundex results must be VERY similar using Levenshtein distance
, SameSound(Words, "been", "fuzzy_soundex", "DamerauLevenshtein", TRUE) as sx_DL_VS -- compare using soundex, and soundex results must be VERY similar using DamerauLevenshtein distance
, SameSound(Words, "been", "fuzzy_phonetic", "JaroWinkler", TRUE) as fp_JW_VS -- compare using soundex, and soundex results must be VERY similar using JaroWinkler distance
, SameSound(Words, "been", "fuzzy_soundex", "Levenshtein", 0) as sx_S -- compare using soundex, and soundex results must be only similar using Levenshtein distance
, SameSound(Words, "been", "fuzzy_phonetic", "Levenshtein", FALSE) as fp_S -- compare using phonetic, and phonetic results must be only similar using Levenshtein distance
, SameSound(Words, "been", "fuzzy_rsoundex", "Levenshtein", FALSE) as sr_S -- compare using rsoundex, and rsoundex results must be only similar using Levenshtein distance
, SameSound(Words, "been", "fuzzy_soundex", "DamerauLevenshtein", 0) as sx_DL_S -- compare using soundex, and soundex results must be only similar using DamerauLevenshtein distance
, SameSound(Words, "been", "fuzzy_phonetic", "JaroWinkler", 0) as fp_JW_S -- compare using soundex, and soundex results must be VERY similar using JaroWinkler distance
FROM SimilarSoundingWords --where fp_JW_S = 1
