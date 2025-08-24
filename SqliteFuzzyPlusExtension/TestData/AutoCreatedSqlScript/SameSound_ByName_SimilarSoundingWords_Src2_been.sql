select Words as src1, 'been' as src2 
, SameSound(Words, 'been', 'UseDefaultSameSoundMethod') as a16384 -- UseDefaultSameSoundMethod (ID# 16384)
, SameSound(Words, 'been', 'SoundexPhonix') as a16385 -- SoundexPhonix (ID# 16385)
, SameSound(Words, 'been', 'CaverPhonePhonix') as a16386 -- CaverPhonePhonix (ID# 16386)
, SameSound(Words, 'been', 'MatchRatingApproach') as a16387 -- MatchRatingApproach (ID# 16387)
, SameSound(Words, 'been', 'Metaphone') as a16388 -- Metaphone (ID# 16388)
, SameSound(Words, 'been', 'DoubleMetaphone') as a16389 -- DoubleMetaphone (ID# 16389)
, SameSound(Words, 'been', 'ColognePhonetics') as a16390 -- ColognePhonetics (ID# 16390)
, SameSound(Words, 'been', 'SoundexVer2') as a16391 -- SoundexVer2 (ID# 16391)
, SameSound(Words, 'been', 'EnPhoneticDistance') as a16448 -- EnPhoneticDistance (ID# 16448)
, SameSound(Words, 'been', 'Fuzzy_Soundex') as a16832 -- Fuzzy_Soundex (ID# 16832)
, SameSound(Words, 'been', 'Fuzzy_Caver') as a16833 -- Fuzzy_Caver (ID# 16833)
, SameSound(Words, 'been', 'Fuzzy_Rsoundex') as a16834 -- Fuzzy_Rsoundex (ID# 16834)
, SameSound(Words, 'been', 'Fuzzy_Phonetic') as a16835 -- Fuzzy_Phonetic (ID# 16835)
FROM SimilarSoundingWords;
-- Note: EnPhoneticDistance only works with SqliteFuzzyPlusExtensionWithMsPhoneticMatching.dll
