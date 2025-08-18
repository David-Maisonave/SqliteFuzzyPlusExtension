##### This page was added starting on version 0.1.1 to keep track of newly added features between versions.
### 0.1.0
- Initial Upload.
### 0.1.1
- Fixed MaxValue, and added MaxLength, MinValue, and MinLength.
- Removed SameRSound alias.
- Changed SameSound so it's no longer an alias for soundex, and it's now a generic function similar to Distance and HowSimilar.
- Added C# Caverphone2 and Soundex. The C# Soundex is the default method for SameSound.
- Added default DefaultSameSoundMethod variable, and associated functions.
  - SetDefaultSameSoundMethod
  - GetSameSoundMethod
### 0.1.2
- Added BlockDistance, ChapmanLengthDeviation, ChapmanMeanLength, EuclideanDistance, MatchingCoefficient, MongeElkan, QGramsDistance, SmithWaterman, SmithWatermanGotoh, and SmithWatermanGotohWindowedAffine.
- Added Soundex2 and changed Caverphone2 so it can take 1 or 2 arguments.
- Added function EnPhoneticDistance which is functional when downloading SqliteFuzzyPlusExtensionWithMsPhoneticMatching.
### 0.1.3
- Added NGramsDistance
- Resorted enum's in order of types (Edit Distance, Sequence Alignment, Token Based, and Hybrid Algorithms)
- Made SqliteFuzzyPlusExtension C language compatible. Changed the main header file and added extern "C" to all the C compatible functions.
- Added C language project (UnitTestConsole_C_Runner) for test purposes.
- Updated enum's in SqliteFuzzyPlusExtension.h with the enum's in Fuzzy.cs.
- Added phonetic methods MatchRatingApproach, Metaphone, CaverPhonePhonix, and DoubleMetaphone from Phonix project.
- Added phonetic method ColognePhonetics.
- Created the following export functions so that the fuzzy code can be used outside of SQLite:
  - fuzzy_script, SameName, HasCharInSameOrder, DamerauLevenshteinDistance, DamerauLevenshtein, LevenshteinDistance, Levenshtein, HammingDistance, Hamming, JaccardDistance, JaroDistance,
  - JaroWinklerDistance, Levenshtein2Distance, LongestCommonSubsequenceDistance, LongestCommonSubstringDistance, NormalizedLevenshteinDistance, OverlapCoefficientDistance, RatcliffObershelpSimilarityDistance,
  - SorensenDiceDistance, TanimotoCoefficientDistance, BlockDistance, NeedlemanWunsch, JaccardIndex, ChapmanLengthDeviation, ChapmanMeanLength, EuclideanDistance, MatchingCoefficient, MongeElkan, QGramsDistance,
  - SmithWaterman, SmithWatermanGotoh, SmithWatermanGotohWindowedAffine, CosineSimilarity, JaccardSimilarity, LongestCommonSequence, DiceSimilarity, PhraseTokenize, SimplePhraseTokenize
### 0.1.4
- Added IExactMatch class.
- Added additional phonetic functions to GetSoundCode.
- Removed PhoneticMethods.CaverPhone because it was almost identical to Phonix.CaverPhone.
- Made SoundexPhonix (Phonix.Soundex) the default phonetic function instead of PhoneticMethods.Soundex.
- Renamed PhoneticMethods.Soundex to PhoneticMethods.SoundexVer2. 
  - Note: SoundexVer2 might be removed in future updates if testing shows no difference from Phonix.Soundex.
- Created separate solution for testing and example code, and moved all testing and example code out of the primary SqliteFuzzyPlusExtension solution. The SqliteFuzzyPlusExtension solution will now only build the two binaries that get uploaded when creating a new version of SqliteFuzzyPlusExtension.
- Removed Microsoft.PhoneticMatching out of SqliteFuzzyPlusExtension.PhoneticMatching solution.
- Changed enum SameSoundMethod so that the first enum function ID starts at 8192. This is to prepare the code for future development in which functions taking enum ID StringMatchingAlgorithm_ID can possibly also take the SameSoundMethod ID's without clashing with existing StringMatchingAlgorithm_ID.
- Change to upper case letters for phonetic SQLean enum's to make them consistent with the SQLean StringMatchingAlgorithm_ID enum's.
- Removed iEdlibDistance function for the purpose of consistency, since none of the other case insensitive enum's had an associated function.
- 