select Words as src1, 'being' as src2 
, SameSound(Words, 'being', 16384) as a16384 -- UseDefaultSameSoundMethod (ID# 16384)
, SameSound(Words, 'being', 16385) as a16385 -- SoundexPhonix (ID# 16385)
, SameSound(Words, 'being', 16386) as a16386 -- CaverPhonePhonix (ID# 16386)
, SameSound(Words, 'being', 16387) as a16387 -- MatchRatingApproach (ID# 16387)
, SameSound(Words, 'being', 16388) as a16388 -- Metaphone (ID# 16388)
, SameSound(Words, 'being', 16389) as a16389 -- DoubleMetaphone (ID# 16389)
, SameSound(Words, 'being', 16390) as a16390 -- ColognePhonetics (ID# 16390)
, SameSound(Words, 'being', 16391) as a16391 -- SoundexVer2 (ID# 16391)
, SameSound(Words, 'being', 16448) as a16448 -- EnPhoneticDistance (ID# 16448)
, SameSound(Words, 'being', 16832) as a16832 -- Fuzzy_Soundex (ID# 16832)
, SameSound(Words, 'being', 16833) as a16833 -- Fuzzy_Caver (ID# 16833)
, SameSound(Words, 'being', 16834) as a16834 -- Fuzzy_Rsoundex (ID# 16834)
, SameSound(Words, 'being', 16835) as a16835 -- Fuzzy_Phonetic (ID# 16835)
FROM SimilarSoundingWords;
-- Note: EnPhoneticDistance only works with SqliteFuzzyPlusExtensionWithMsPhoneticMatching.dll
