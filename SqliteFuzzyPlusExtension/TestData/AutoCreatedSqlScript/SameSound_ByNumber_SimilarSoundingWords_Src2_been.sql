select Words as src1, 'been' as src2 
, SameSound(Words, 'been', 16384) as a16384 -- UseDefaultSameSoundMethod (ID# 16384)
, SameSound(Words, 'been', 16385) as a16385 -- SoundexPhonix (ID# 16385)
, SameSound(Words, 'been', 16386) as a16386 -- CaverPhonePhonix (ID# 16386)
, SameSound(Words, 'been', 16387) as a16387 -- MatchRatingApproach (ID# 16387)
, SameSound(Words, 'been', 16388) as a16388 -- Metaphone (ID# 16388)
, SameSound(Words, 'been', 16389) as a16389 -- DoubleMetaphone (ID# 16389)
, SameSound(Words, 'been', 16390) as a16390 -- ColognePhonetics (ID# 16390)
, SameSound(Words, 'been', 16391) as a16391 -- SoundexVer2 (ID# 16391)
, SameSound(Words, 'been', 16448) as a16448 -- EnPhoneticDistance (ID# 16448)
, SameSound(Words, 'been', 16512) as a16512 -- Fuzzy_Soundex (ID# 16512)
, SameSound(Words, 'been', 16513) as a16513 -- Fuzzy_Caver (ID# 16513)
, SameSound(Words, 'been', 16514) as a16514 -- Fuzzy_Rsoundex (ID# 16514)
, SameSound(Words, 'been', 16515) as a16515 -- Fuzzy_Phonetic (ID# 16515)
FROM SimilarSoundingWords;
-- Note: EnPhoneticDistance only works with SqliteFuzzyPlusExtensionWithMsPhoneticMatching.dll
