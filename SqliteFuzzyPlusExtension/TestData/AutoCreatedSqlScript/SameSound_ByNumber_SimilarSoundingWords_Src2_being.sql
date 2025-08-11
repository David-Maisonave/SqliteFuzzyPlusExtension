select Words as src1, 'being' as src2 
, SameSound(Words, 'being', 0) as a0 -- UseDefaultSameSoundMethod (ID# 0)
, SameSound(Words, 'being', 1) as a1 -- Soundex2 (ID# 1)
, SameSound(Words, 'being', 2) as a2 -- Caverphone2 (ID# 2)
, SameSound(Words, 'being', 3) as a3 -- MatchRatingApproach (ID# 3)
, SameSound(Words, 'being', 4) as a4 -- Metaphone (ID# 4)
, SameSound(Words, 'being', 5) as a5 -- CaverPhonePhonix (ID# 5)
, SameSound(Words, 'being', 6) as a6 -- DoubleMetaphone (ID# 6)
, SameSound(Words, 'being', 7) as a7 -- ColognePhonetics (ID# 7)
, SameSound(Words, 'being', 64) as a64 -- EnPhoneticDistance (ID# 64)
, SameSound(Words, 'being', 128) as a128 -- fuzzy_caver (ID# 128)
, SameSound(Words, 'being', 129) as a129 -- fuzzy_phonetic (ID# 129)
, SameSound(Words, 'being', 130) as a130 -- fuzzy_soundex (ID# 130)
, SameSound(Words, 'being', 131) as a131 -- fuzzy_rsoundex (ID# 131)
FROM SimilarSoundingWords;
-- Note: EnPhoneticDistance only works with SqliteFuzzyPlusExtensionWithMsPhoneticMatching.dll
