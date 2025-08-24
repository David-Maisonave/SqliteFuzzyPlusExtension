select Words as src1, 'bean' as src2 
, SameSound(Words, 'bean', 'UseDefaultSameSoundMethod') as a16384 -- UseDefaultSameSoundMethod (ID# 16384)
, SameSound(Words, 'bean', 'SoundexPhonix') as a16385 -- SoundexPhonix (ID# 16385)
, SameSound(Words, 'bean', 'CaverPhonePhonix') as a16386 -- CaverPhonePhonix (ID# 16386)
, SameSound(Words, 'bean', 'MatchRatingApproach') as a16387 -- MatchRatingApproach (ID# 16387)
, SameSound(Words, 'bean', 'Metaphone') as a16388 -- Metaphone (ID# 16388)
, SameSound(Words, 'bean', 'DoubleMetaphone') as a16389 -- DoubleMetaphone (ID# 16389)
, SameSound(Words, 'bean', 'ColognePhonetics') as a16390 -- ColognePhonetics (ID# 16390)
, SameSound(Words, 'bean', 'SoundexVer2') as a16391 -- SoundexVer2 (ID# 16391)
, SameSound(Words, 'bean', 'EnPhoneticDistance') as a16448 -- EnPhoneticDistance (ID# 16448)
, SameSound(Words, 'bean', 'Fuzzy_Soundex') as a16832 -- Fuzzy_Soundex (ID# 16832)
, SameSound(Words, 'bean', 'Fuzzy_Caver') as a16833 -- Fuzzy_Caver (ID# 16833)
, SameSound(Words, 'bean', 'Fuzzy_Rsoundex') as a16834 -- Fuzzy_Rsoundex (ID# 16834)
, SameSound(Words, 'bean', 'Fuzzy_Phonetic') as a16835 -- Fuzzy_Phonetic (ID# 16835)
FROM SimilarSoundingWords;
-- Note: EnPhoneticDistance only works with SqliteFuzzyPlusExtensionWithMsPhoneticMatching.dll
