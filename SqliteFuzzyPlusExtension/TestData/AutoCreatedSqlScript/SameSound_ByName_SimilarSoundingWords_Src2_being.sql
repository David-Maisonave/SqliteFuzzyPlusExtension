select Words as src1, 'being' as src2 
, SameSound(Words, 'being', 'UseDefaultSameSoundMethod') as a16384 -- UseDefaultSameSoundMethod (ID# 16384)
, SameSound(Words, 'being', 'SoundexPhonix') as a16385 -- SoundexPhonix (ID# 16385)
, SameSound(Words, 'being', 'CaverPhonePhonix') as a16386 -- CaverPhonePhonix (ID# 16386)
, SameSound(Words, 'being', 'MatchRatingApproach') as a16387 -- MatchRatingApproach (ID# 16387)
, SameSound(Words, 'being', 'Metaphone') as a16388 -- Metaphone (ID# 16388)
, SameSound(Words, 'being', 'DoubleMetaphone') as a16389 -- DoubleMetaphone (ID# 16389)
, SameSound(Words, 'being', 'ColognePhonetics') as a16390 -- ColognePhonetics (ID# 16390)
, SameSound(Words, 'being', 'SoundexVer2') as a16391 -- SoundexVer2 (ID# 16391)
, SameSound(Words, 'being', 'EnPhoneticDistance') as a16448 -- EnPhoneticDistance (ID# 16448)
, SameSound(Words, 'being', 'Fuzzy_Soundex') as a16512 -- Fuzzy_Soundex (ID# 16512)
, SameSound(Words, 'being', 'Fuzzy_Caver') as a16513 -- Fuzzy_Caver (ID# 16513)
, SameSound(Words, 'being', 'Fuzzy_Rsoundex') as a16514 -- Fuzzy_Rsoundex (ID# 16514)
, SameSound(Words, 'being', 'Fuzzy_Phonetic') as a16515 -- Fuzzy_Phonetic (ID# 16515)
FROM SimilarSoundingWords;
-- Note: EnPhoneticDistance only works with SqliteFuzzyPlusExtensionWithMsPhoneticMatching.dll
