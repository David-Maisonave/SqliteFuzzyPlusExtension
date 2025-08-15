using FuzzyPlusCSharp.DistanceMethods;

using Phonix;

using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics.Contracts;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

using static System.Net.Mime.MediaTypeNames;

namespace FuzzyPlusCSharp
{
    #region Non-Static version
    public class FuzzyInst
    {
        private readonly Fuzzy.DistanceMethod distanceMethod = Fuzzy.DistanceMethod.iDamerauLevenshtein;
        public FuzzyInst(Fuzzy.DistanceMethod distanceMethod)
        {
            this.distanceMethod = distanceMethod;
        }
        public bool IsVerySimilar(string source1, string source2) => Fuzzy.IsMatch(source1, source2, Fuzzy.ISVERYSIMILAR, distanceMethod); // Is 90% similar
        public bool IsSimilar(string source1, string source2) => Fuzzy.IsMatch(source1, source2, Fuzzy.ISSIMILAR, distanceMethod); // Is 75% similar
        public bool IsSomeWhatSimilar(string source1, string source2) => Fuzzy.IsMatch(source1, source2, Fuzzy.ISSOMEWHATSIMILAR, distanceMethod); // Is 50% similar
        public bool IsSlightlySimilar(string source1, string source2) => Fuzzy.IsMatch(source1, source2, Fuzzy.ISSLIGHTLYSIMILAR, distanceMethod); // Is 30% similar
        public bool IsHardlySimilar(string source1, string source2) => Fuzzy.IsMatch(source1, source2, Fuzzy.ISHARDLYSIMILAR, distanceMethod); // Is 10% similar
        public bool IsMatch(string source1, string source2, double desiredSimilarity) => Fuzzy.HowSimilar(source1, source2, distanceMethod) >= desiredSimilarity;
        public double HowSimilar(string source1, string source2) => Fuzzy.HowSimilar(source1, source2, distanceMethod);
        public bool IsNotSimilar(string source1, string source2) => Fuzzy.IsNotSimilar(source1, source2, distanceMethod);
    }
    #endregion Non-Static version
    //////////////////////////////////////////////////////////////////////
    /// Static version 
    public static class Fuzzy
    {
        #region Constants
        public const double ISVERYSIMILAR = 0.9f;
        public const double ISSIMILAR = 0.75f;
        public const double ISSOMEWHATSIMILAR = 0.5f;
        public const double ISSLIGHTLYSIMILAR = 0.3f;
        public const double ISHARDLYSIMILAR = 0.1f;
        public const int CASE_INSENSITIVE = 256;
        public const int CPP_ONLY_FUZZY = 128;
        public const int TOKEN_METHODS = 64;
        public const int MICROSOFT_PHONETIC_METHODS = 64;
        public const int PHRASE_METHODS = TOKEN_METHODS + 32;
        public const int METHODS_UP_FOR_DELETION = PHRASE_METHODS + 16;
        #endregion Constants
        #region Distance and Phonetic class members
        // Distance classes
        public static DistanceMethods.BlockDistance blockDistance = new DistanceMethods.BlockDistance();
        public static DistanceMethods.ChapmanLengthDeviation chapmanLengthDeviation = new DistanceMethods.ChapmanLengthDeviation();
        public static DistanceMethods.ChapmanMeanLength chapmanMeanLength = new DistanceMethods.ChapmanMeanLength();
        public static DistanceMethods.EuclideanDistance euclideanDistance = new DistanceMethods.EuclideanDistance();
        public static DistanceMethods.MatchingCoefficient matchingCoefficient = new DistanceMethods.MatchingCoefficient();
        public static DistanceMethods.MongeElkan mongeElkan = new DistanceMethods.MongeElkan();
        public static DistanceMethods.QGramsDistance qGramsDistance = new DistanceMethods.QGramsDistance();
        public static DistanceMethods.SmithWaterman smithWaterman = new DistanceMethods.SmithWaterman();
        public static DistanceMethods.SmithWatermanGotoh smithWatermanGotoh = new DistanceMethods.SmithWatermanGotoh();
        public static DistanceMethods.SmithWatermanGotohWindowedAffine smithWatermanGotohWindowedAffine = new DistanceMethods.SmithWatermanGotohWindowedAffine();
        public static DistanceMethods.DiceSimilarity diceSimilarity = new DistanceMethods.DiceSimilarity();
        // Phonetic classes
        public static MatchRatingApproach matchRatingApproach = new MatchRatingApproach();
        public static Metaphone metaphone = new Metaphone();
        public static CaverPhone caverPhonePhonix = new CaverPhone();
        public static DoubleMetaphone doubleMetaphone = new DoubleMetaphone();
        #endregion Distance classes members
        #region DistanceMethod definitions
        public enum DistanceMethod
        {
            UseDefaultDistanceMethod = 0,
            Levenshtein,
            DamerauLevenshtein,
            JaroWinkler,
            LongestCommonSequence,
            JaccardIndex,
            OverlapCoefficient,
            NeedlemanWunsch,
            SorensenDiceDistance,
            RatcliffObershelpSimilarityDistance,
            HammingDistance,
            LongestCommonSubstringDistance,
            LongestCommonSubsequenceDistance,
            JaroDistance,
            NormalizedLevenshteinDistance,
            Levenshtein2Distance,
            TanimotoCoefficientDistance,
            // Distance method from SimMetricsCore
            BlockDistance,
            ChapmanLengthDeviation,
            ChapmanMeanLength,
            EuclideanDistance,
            MatchingCoefficient,
            MongeElkan,
            QGramsDistance,
            SmithWaterman,
            SmithWatermanGotoh,
            SmithWatermanGotohWindowedAffine,
            DiceSimilarity,

            //Token methods
            CosineSimilarity = TOKEN_METHODS,
            JaccardSimilarity,
            
            // Phrase token methods which are all case insensitive only
            PhraseTokenize = PHRASE_METHODS,
            SimplePhraseTokenize,

            // EditDistance may get removed, replaced, or logic change 
            EditDistance = METHODS_UP_FOR_DELETION,

            // ------------------------------------------------------------
            // These functions are NOT supported by CSharp Fuzzy class code, and are only here for C++ SqliteFuzzyPlusExtension usage.
            // Sqlean Fuzzy external functions. 
            Fuzzy_Damlev = CPP_ONLY_FUZZY,
            Fuzzy_Hamming,
            Fuzzy_Jarowin,
            Fuzzy_Leven,
            Fuzzy_Osadist,
            Fuzzy_Editdist,
            Fuzzy_Jaro,
            ExactMatch,
            // Other C++ (external) only functions. (NOT part of Sqlean)
            EdlibDistance,
            // ------------------------------------------------------------

            // Case INSENSITIVE versions
            iLevenshtein = CASE_INSENSITIVE + Levenshtein,
            iDamerauLevenshtein,
            iJaroWinkler,
            iLongestCommonSequence,
            iJaccardIndex,
            iOverlapCoefficient,
            iNeedlemanWunsch,
            iSorensenDiceDistance,
            iRatcliffObershelpSimilarityDistance,
            iHammingDistance,
            iLongestCommonSubstringDistance,
            iLongestCommonSubsequenceDistance,
            iJaroDistance,
            iNormalizedLevenshteinDistance,
            iLevenshtein2Distance,
            iTanimotoCoefficientDistance,
            iEditDistance,

            //Token methods
            iCosineSimilarity,
            iJaccardSimilarity,

            // Distance method from SimMetricsCore
            iBlockDistance,
            iChapmanLengthDeviation,
            iChapmanMeanLength,
            iEuclideanDistance,
            iMatchingCoefficient,
            iMongeElkan,
            iQGramsDistance,
            iSmithWaterman,
            iSmithWatermanGotoh,
            iSmithWatermanGotohWindowedAffine,
            iDiceSimilarity,

            // ------------------------------------------------------------
            // These functions are NOT supported by CSharp Fuzzy class code, and are only here for C++ SqliteFuzzyPlusExtension usage.
            iEdlibDistance = CASE_INSENSITIVE + EdlibDistance,
            // ------------------------------------------------------------
        }
        public static DistanceMethod DefaultDistanceMethod { get; private set; } = DistanceMethod.iDamerauLevenshtein;

        public static void SetDefaultDistanceMethod(DistanceMethod distanceMethod) => DefaultDistanceMethod = distanceMethod;
        public static DistanceMethod GetDistanceMethod(int distanceMethod_ID) => (DistanceMethod)distanceMethod_ID;
        public static DistanceMethod GetDistanceMethod(string distanceMethod_Name)
        { // This function is for SQLite extension purposes, and should only be called once!!!
            DistanceMethod distanceMethod = DefaultDistanceMethod;
            if (distanceMethod_Name != null && !distanceMethod_Name.Equals("UseDefaultDistanceMethod", StringComparison.OrdinalIgnoreCase))
            {
                try
                {
                    distanceMethod = (DistanceMethod)Enum.Parse(typeof(DistanceMethod), distanceMethod_Name, true);
                }
                catch
                {
                    // ToDo: add error console logging here.
                }
            }
            return distanceMethod;
        }
        public static bool SetDefaultDistanceMethod(int distanceMethod_ID) // This function is to let SQL access setting default method
        {
            DefaultDistanceMethod = (DistanceMethod)distanceMethod_ID;
            return true;
        }
        public static bool SetDefaultDistanceMethod(string distanceMethod_Name)
        { // This function is to let SQL access setting default method by using the distance method name explicitly.
            //But this should only be called once. If repetitive calls are required, use ID method instead.
            DefaultDistanceMethod = GetDistanceMethod(distanceMethod_Name);
            return true;
        }
        public static string GetDistanceMethodName(int distanceMethod_ID)
        {
            DistanceMethod distanceMethod = GetDistanceMethod(distanceMethod_ID);
            return distanceMethod.ToString();
        }
        #endregion DistanceMethod definitions
        #region SameSoundMethod
        public enum SameSoundMethod
        {
            UseDefaultSameSoundMethod = 0,
            Soundex2,    // Default SameSound method
            Caverphone2,
            MatchRatingApproach,
            Metaphone,
            CaverPhonePhonix,
            DoubleMetaphone,
            ColognePhonetics,
            EnPhoneticDistance = MICROSOFT_PHONETIC_METHODS,
            // ------------------------------------------------------------
            // These functions are NOT supported by CSharp Fuzzy class code, and are only here for C++ SqliteFuzzyPlusExtension usage.
            // SQLean phonetic external functions. 
            fuzzy_caver = CPP_ONLY_FUZZY,
            fuzzy_phonetic,
            fuzzy_soundex,
            fuzzy_rsoundex,  //Refined Soundex
            fuzzy_translit, //Transliteration
        }
        public static SameSoundMethod DefaultSameSoundMethod { get; private set; } = SameSoundMethod.Soundex2;
        public static void SetDefaultSameSoundMethod(SameSoundMethod sameSoundMethod) => DefaultSameSoundMethod = sameSoundMethod;
        public static SameSoundMethod GetSameSoundMethod(int sameSoundMethod_ID) => (SameSoundMethod)sameSoundMethod_ID;
        public static SameSoundMethod GetSameSoundMethod(string sameSoundMethod_Name)
        { // This function is for SQLite extension purposes, and should only be called once!!!
            SameSoundMethod sameSoundMethod = DefaultSameSoundMethod;
            if (sameSoundMethod_Name != null && !sameSoundMethod_Name.Equals("UseDefaultSameSoundMethod", StringComparison.OrdinalIgnoreCase))
            {
                try
                {
                    sameSoundMethod = (SameSoundMethod)Enum.Parse(typeof(SameSoundMethod), sameSoundMethod_Name, true);
                }
                catch
                {
                    // ToDo: add error console logging here.
                }
            }
            return sameSoundMethod;
        }
        public static bool SetDefaultSameSoundMethod(int sameSoundMethod_ID) // This function is to let SQL access setting default method
        {
            DefaultSameSoundMethod = (SameSoundMethod)sameSoundMethod_ID;
            return true;
        }
        public static bool SetDefaultSameSoundMethod(string sameSoundMethod_Name)
        { // This function is to let SQL access setting default method by using the distance method name explicitly.
            //But this should only be called once. If repetitive calls are required, use ID method instead.
            DefaultSameSoundMethod = GetSameSoundMethod(sameSoundMethod_Name);
            return true;
        }
        public static string GetSameSoundMethodName(int sameSoundMethod_ID)
        {
            SameSoundMethod sameSoundMethod = GetSameSoundMethod(sameSoundMethod_ID);
            return sameSoundMethod.ToString();
        }
        #endregion SameSoundMethod
        #region Similarity functions
        public static bool IsMatch(string source1, string source2, double desiredSimilarity, DistanceMethod distanceMethod = DistanceMethod.UseDefaultDistanceMethod) => HowSimilar(source1, source2, distanceMethod) >= desiredSimilarity;
        // The following HowSimilar method is to let SQLite access to HowSimilar
        public static bool IsCaseSensitive(DistanceMethod distanceMethod) => (int)distanceMethod < CASE_INSENSITIVE;
        public static void FixIfIsCaseSensitive(ref string source1, ref string source2, bool isCaseSensitive)
        {
            if (!isCaseSensitive)
            {
                source1 = source1.ToLower();
                source2 = source2.ToLower();
            }
        }
        public static double HowSimilar(string source1, string source2, int distanceMethod) => HowSimilar(source1, source2, GetDistanceMethod(distanceMethod));
        public static double HowSimilar(string source1, string source2, string distanceMethod) => HowSimilar(source1, source2, GetDistanceMethod(distanceMethod));
        public static double HowSimilar(string source1, string source2, DistanceMethod distanceMethod = DistanceMethod.UseDefaultDistanceMethod)
        {
            if (distanceMethod == DistanceMethod.UseDefaultDistanceMethod)
                distanceMethod = DefaultDistanceMethod;
            bool isCaseSensitive = IsCaseSensitive(distanceMethod);
            double sourceLength = Math.Max(source1.Length, source2.Length);
            double diff;
            switch (distanceMethod) 
            {
                case DistanceMethod.Levenshtein:
                case DistanceMethod.iLevenshtein:
                    diff = DistanceMethods.Levenshtein.Distance(source1, source2, isCaseSensitive);
                    break;
                case DistanceMethod.JaroWinkler:
                case DistanceMethod.iJaroWinkler:
                    diff = DistanceMethods.JaroWinkler.Percentage(source1, source2, isCaseSensitive);
                    break;
                case DistanceMethod.CosineSimilarity:
                case DistanceMethod.iCosineSimilarity:
                    return DistanceMethods.CosineSimilarity.Percentage(source1, source2, isCaseSensitive);
                case DistanceMethod.LongestCommonSequence:
                case DistanceMethod.iLongestCommonSequence:
                    return DistanceMethods.LongestCommonSequence.Percentage(source1, source2, isCaseSensitive);
                case DistanceMethod.JaccardSimilarity:
                case DistanceMethod.iJaccardSimilarity:
                    return DistanceMethods.JaccardSimilarity.Percentage(source1, source2, isCaseSensitive);
                case DistanceMethod.JaccardIndex:
                case DistanceMethod.iJaccardIndex:
                    return DistanceMethods.JaccardIndex.Percentage(source1, source2, isCaseSensitive);
                case DistanceMethod.OverlapCoefficient:
                case DistanceMethod.iOverlapCoefficient:
                    diff = DistanceMethods.OverlapCoefficient.Distance(source1, source2, isCaseSensitive);
                    break;
                case DistanceMethod.NeedlemanWunsch:
                case DistanceMethod.iNeedlemanWunsch:
                    return DistanceMethods.NeedlemanWunsch.Percentage(source1, source2, isCaseSensitive);
                case DistanceMethod.SorensenDiceDistance:
                case DistanceMethod.iSorensenDiceDistance:
                    return DistanceMethods.SorensenDice.Percentage(source1, source2, isCaseSensitive);
                case DistanceMethod.RatcliffObershelpSimilarityDistance:
                case DistanceMethod.iRatcliffObershelpSimilarityDistance:
                    return DistanceMethods.RatcliffObershelpSimilarity.Percentage(source1, source2, isCaseSensitive);
                case DistanceMethod.HammingDistance:
                case DistanceMethod.iHammingDistance:
                    return DistanceMethods.Hamming.Percentage(source1, source2, isCaseSensitive);
                case DistanceMethod.LongestCommonSubstringDistance:
                case DistanceMethod.iLongestCommonSubstringDistance:
                    diff = DistanceMethods.LongestCommonSubstring.Distance(source1, source2, isCaseSensitive);
                    sourceLength = Math.Min(source1.Length, source2.Length);
                    break;
                case DistanceMethod.LongestCommonSubsequenceDistance:
                case DistanceMethod.iLongestCommonSubsequenceDistance:
                    diff = DistanceMethods.LongestCommonSubsequence.Distance(source1, source2, isCaseSensitive);
                    sourceLength = Math.Min(source1.Length, source2.Length);
                    break;
                case DistanceMethod.JaroDistance:
                case DistanceMethod.iJaroDistance:
                    diff = DistanceMethods.Jaro.Distance(source1, source2, isCaseSensitive);
                    break;
                case DistanceMethod.NormalizedLevenshteinDistance:
                case DistanceMethod.iNormalizedLevenshteinDistance:
                    return DistanceMethods.NormalizedLevenshtein.Percentage(source1, source2, isCaseSensitive);
                case DistanceMethod.Levenshtein2Distance:
                case DistanceMethod.iLevenshtein2Distance:
                    return DistanceMethods.Levenshtein2.Percentage(source1, source2, isCaseSensitive);
                case DistanceMethod.TanimotoCoefficientDistance:
                case DistanceMethod.iTanimotoCoefficientDistance:
                    return DistanceMethods.TanimotoCoefficient.Percentage(source1, source2, isCaseSensitive);
                case DistanceMethod.EditDistance:
                case DistanceMethod.iEditDistance:
                    return DistanceMethods.EditDistanceWithWildCard.Percentage(source1, source2, isCaseSensitive);
                case DistanceMethod.BlockDistance:
                case DistanceMethod.iBlockDistance:
                    FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
                    diff = blockDistance.GetSimilarity(source1, source2);
                    break;
                case DistanceMethod.ChapmanLengthDeviation:
                case DistanceMethod.iChapmanLengthDeviation:
                    FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
                    diff = chapmanLengthDeviation.GetSimilarity(source1, source2);
                    break;
                case DistanceMethod.ChapmanMeanLength:
                case DistanceMethod.iChapmanMeanLength:
                    FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
                    diff = chapmanMeanLength.GetSimilarity(source1, source2);
                    break;
                case DistanceMethod.EuclideanDistance:
                case DistanceMethod.iEuclideanDistance:
                    FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
                    diff = euclideanDistance.GetSimilarity(source1, source2);
                    break;
                case DistanceMethod.MatchingCoefficient:
                case DistanceMethod.iMatchingCoefficient:
                    FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
                    diff = matchingCoefficient.GetSimilarity(source1, source2);
                    break;
                case DistanceMethod.MongeElkan:
                case DistanceMethod.iMongeElkan:
                    FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
                    diff = mongeElkan.GetSimilarity(source1, source2);
                    break;
                case DistanceMethod.QGramsDistance:
                case DistanceMethod.iQGramsDistance:
                    FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
                    diff = qGramsDistance.GetSimilarity(source1, source2);
                    break;
                case DistanceMethod.SmithWaterman:
                case DistanceMethod.iSmithWaterman:
                    FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
                    diff = smithWaterman.GetSimilarity(source1, source2);
                    break;
                case DistanceMethod.SmithWatermanGotoh:
                case DistanceMethod.iSmithWatermanGotoh:
                    FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
                    diff = smithWatermanGotoh.GetSimilarity(source1, source2);
                    break;
                case DistanceMethod.SmithWatermanGotohWindowedAffine:
                case DistanceMethod.iSmithWatermanGotohWindowedAffine:
                    FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
                    diff = smithWatermanGotohWindowedAffine.GetSimilarity(source1, source2);
                    break;
                case DistanceMethod.DiceSimilarity:
                case DistanceMethod.iDiceSimilarity:
                    diff = DiceSimilarity(source1, source2, isCaseSensitive);
                    break;
                case DistanceMethod.PhraseTokenize:
                    diff = DistanceMethods.PhraseTokenize.Distance(source1, source2);
                    sourceLength = Math.Max(GetKeywordList(ref source1).Length, GetKeywordList(ref source2).Length);
                    break;
                case DistanceMethod.SimplePhraseTokenize:
                    diff = DistanceMethods.SimplePhraseTokenize.Distance(source1, source2);
                    sourceLength = Math.Max(GetKeywordList(ref source1).Length, GetKeywordList(ref source2).Length);
                    break;
                case DistanceMethod.DamerauLevenshtein:
                case DistanceMethod.iDamerauLevenshtein:
                default:
                    diff = DistanceMethods.DamerauLevenshtein.Distance(source1, source2, isCaseSensitive);
                    break;
            }
            return diff == 0 ? 1.0f : (sourceLength - diff) / sourceLength;
        }
        public static double Distance(string source1, string source2, DistanceMethod distanceMethod = DistanceMethod.UseDefaultDistanceMethod)
        {
            if (distanceMethod == DistanceMethod.UseDefaultDistanceMethod)
                distanceMethod = DefaultDistanceMethod;
            bool isCaseSensitive = IsCaseSensitive(distanceMethod);
            IDistance i = GetIDistance(distanceMethod);
            if (i != null)
                return i.Distance(source1, source2, isCaseSensitive);
            switch (distanceMethod) 
            {
                case DistanceMethod.Levenshtein:
                case DistanceMethod.iLevenshtein:
                    return DistanceMethods.Levenshtein.Distance(source1, source2, isCaseSensitive);
                case DistanceMethod.JaroWinkler:
                case DistanceMethod.iJaroWinkler:
                    return DistanceMethods.JaroWinkler.Distance(source1, source2, isCaseSensitive);
                case DistanceMethod.CosineSimilarity:
                case DistanceMethod.iCosineSimilarity:
                    return DistanceMethods.CosineSimilarity.Distance(source1, source2, isCaseSensitive);
                case DistanceMethod.LongestCommonSequence:
                case DistanceMethod.iLongestCommonSequence:
                    return DistanceMethods.LongestCommonSequence.Distance(source1, source2, isCaseSensitive);
                case DistanceMethod.JaccardSimilarity:
                case DistanceMethod.iJaccardSimilarity:
                    return DistanceMethods.JaccardSimilarity.Distance(source1, source2, isCaseSensitive);
                case DistanceMethod.JaccardIndex:
                case DistanceMethod.iJaccardIndex:
                    return DistanceMethods.JaccardIndex.Distance(source1, source2, isCaseSensitive);
                case DistanceMethod.OverlapCoefficient:
                case DistanceMethod.iOverlapCoefficient:
                    return DistanceMethods.OverlapCoefficient.Distance(source1, source2, isCaseSensitive);
                case DistanceMethod.NeedlemanWunsch:
                case DistanceMethod.iNeedlemanWunsch:
                    return DistanceMethods.NeedlemanWunsch.Distance(source1, source2, isCaseSensitive);
                case DistanceMethod.SorensenDiceDistance:
                case DistanceMethod.iSorensenDiceDistance:
                    return DistanceMethods.SorensenDice.Distance(source1, source2, isCaseSensitive);
                case DistanceMethod.RatcliffObershelpSimilarityDistance:
                case DistanceMethod.iRatcliffObershelpSimilarityDistance:
                    return DistanceMethods.RatcliffObershelpSimilarity.Distance(source1, source2, isCaseSensitive);
                case DistanceMethod.HammingDistance:
                case DistanceMethod.iHammingDistance:
                    return (double)DistanceMethods.Hamming.Distance(source1, source2, isCaseSensitive);
                case DistanceMethod.LongestCommonSubstringDistance:
                case DistanceMethod.iLongestCommonSubstringDistance:
                    return DistanceMethods.LongestCommonSubstring.Distance(source1, source2, isCaseSensitive);
                case DistanceMethod.LongestCommonSubsequenceDistance:
                case DistanceMethod.iLongestCommonSubsequenceDistance:
                    return DistanceMethods.LongestCommonSubsequence.Distance(source1, source2, isCaseSensitive);
                case DistanceMethod.JaroDistance:
                case DistanceMethod.iJaroDistance:
                    return DistanceMethods.Jaro.Distance(source1, source2, isCaseSensitive);
                case DistanceMethod.NormalizedLevenshteinDistance:
                case DistanceMethod.iNormalizedLevenshteinDistance:
                    return DistanceMethods.NormalizedLevenshtein.Distance(source1, source2, isCaseSensitive);
                case DistanceMethod.Levenshtein2Distance:
                case DistanceMethod.iLevenshtein2Distance:
                    return DistanceMethods.Levenshtein2.Distance(source1, source2, isCaseSensitive);
                case DistanceMethod.TanimotoCoefficientDistance:
                case DistanceMethod.iTanimotoCoefficientDistance:
                    return DistanceMethods.TanimotoCoefficient.Distance(source1, source2, isCaseSensitive);
                case DistanceMethod.EditDistance:
                case DistanceMethod.iEditDistance:
                    return DistanceMethods.EditDistanceWithWildCard.Distance(source1, source2, isCaseSensitive);
                case DistanceMethod.BlockDistance:
                case DistanceMethod.iBlockDistance:
                    FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
                    return blockDistance.GetSimilarity(source1, source2);
                case DistanceMethod.ChapmanLengthDeviation:
                case DistanceMethod.iChapmanLengthDeviation:
                    FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
                    return chapmanLengthDeviation.GetSimilarity(source1, source2);
                case DistanceMethod.ChapmanMeanLength:
                case DistanceMethod.iChapmanMeanLength:
                    FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
                    return chapmanMeanLength.GetSimilarity(source1, source2);
                case DistanceMethod.EuclideanDistance:
                case DistanceMethod.iEuclideanDistance:
                    FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
                    return euclideanDistance.GetSimilarity(source1, source2);
                case DistanceMethod.MatchingCoefficient:
                case DistanceMethod.iMatchingCoefficient:
                    FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
                    return matchingCoefficient.GetSimilarity(source1, source2);
                case DistanceMethod.MongeElkan:
                case DistanceMethod.iMongeElkan:
                    FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
                    return mongeElkan.GetSimilarity(source1, source2);
                case DistanceMethod.QGramsDistance:
                case DistanceMethod.iQGramsDistance:
                    FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
                    return qGramsDistance.GetSimilarity(source1, source2);
                case DistanceMethod.SmithWaterman:
                case DistanceMethod.iSmithWaterman:
                    FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
                    return smithWaterman.GetSimilarity(source1, source2);
                case DistanceMethod.SmithWatermanGotoh:
                case DistanceMethod.iSmithWatermanGotoh:
                    FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
                    return smithWatermanGotoh.GetSimilarity(source1, source2);
                case DistanceMethod.SmithWatermanGotohWindowedAffine:
                case DistanceMethod.iSmithWatermanGotohWindowedAffine:
                    return smithWatermanGotohWindowedAffine.Distance(source1, source2, isCaseSensitive);
                case DistanceMethod.DiceSimilarity:
                case DistanceMethod.iDiceSimilarity:
                    return DiceSimilarity(source1, source2, isCaseSensitive);
                case DistanceMethod.PhraseTokenize:
                    return DistanceMethods.PhraseTokenize.Distance(source1, source2);
                case DistanceMethod.SimplePhraseTokenize:
                    return DistanceMethods.SimplePhraseTokenize.Distance(source1, source2);
                case DistanceMethod.DamerauLevenshtein:
                case DistanceMethod.iDamerauLevenshtein:
                default:
                    return DistanceMethods.DamerauLevenshtein.Distance(source1, source2, isCaseSensitive);
            }
        }
        public static double Distance(string source1, string source2, int distanceMethod) => Distance(source1, source2, GetDistanceMethod(distanceMethod));
        public static double Distance(string source1, string source2, string distanceMethod) => Distance(source1, source2, GetDistanceMethod(distanceMethod));
        public static bool IsNotSimilar(string source1, string source2) => IsNotSimilar(source1, source2, DistanceMethod.UseDefaultDistanceMethod);
        public static bool IsNotSimilar(string source1, string source2, DistanceMethod distanceMethod)
        {
            if (distanceMethod == DistanceMethod.UseDefaultDistanceMethod)
                distanceMethod = DefaultDistanceMethod;
            bool isCaseSensitive = IsCaseSensitive(distanceMethod);
            switch (distanceMethod)
            {
                case DistanceMethod.Levenshtein:
                case DistanceMethod.iLevenshtein:
                    return DistanceMethods.Levenshtein.Distance(source1, source2, isCaseSensitive) == Math.Max(source1.Length, source2.Length);
                case DistanceMethod.JaroWinkler:
                case DistanceMethod.iJaroWinkler:
                    return DistanceMethods.JaroWinkler.Percentage(source1, source2, isCaseSensitive) == Math.Max(source1.Length, source2.Length);
                case DistanceMethod.CosineSimilarity:
                case DistanceMethod.iCosineSimilarity:
                    return DistanceMethods.CosineSimilarity.Percentage(source1, source2, isCaseSensitive) == 0;
                case DistanceMethod.JaccardSimilarity:
                case DistanceMethod.iJaccardSimilarity:
                    return DistanceMethods.JaccardSimilarity.Percentage(source1, source2, isCaseSensitive) == 0;
                case DistanceMethod.JaccardIndex:
                case DistanceMethod.iJaccardIndex:
                    return DistanceMethods.JaccardIndex.Distance(source1, source2, isCaseSensitive) == Math.Max(source1.Length, source2.Length);
                case DistanceMethod.OverlapCoefficient:
                case DistanceMethod.iOverlapCoefficient:
                    return DistanceMethods.OverlapCoefficient.Distance(source1, source2, isCaseSensitive) == Math.Max(source1.Length, source2.Length);
                case DistanceMethod.NeedlemanWunsch:
                case DistanceMethod.iNeedlemanWunsch:
                    return DistanceMethods.NeedlemanWunsch.Percentage(source1, source2, isCaseSensitive) == 0;
                case DistanceMethod.LongestCommonSequence:
                case DistanceMethod.iLongestCommonSequence:
                    return DistanceMethods.LongestCommonSequence.Difference(source1, source2, isCaseSensitive) == Math.Max(source1.Length, source2.Length);
                case DistanceMethod.SorensenDiceDistance:
                case DistanceMethod.iSorensenDiceDistance:
                    return DistanceMethods.SorensenDice.Distance(source1, source2, isCaseSensitive) == Math.Max(source1.Length, source2.Length);
                case DistanceMethod.RatcliffObershelpSimilarityDistance:
                case DistanceMethod.iRatcliffObershelpSimilarityDistance:
                    return DistanceMethods.RatcliffObershelpSimilarity.Distance(source1, source2, isCaseSensitive) == Math.Max(source1.Length, source2.Length);
                case DistanceMethod.HammingDistance:
                case DistanceMethod.iHammingDistance:
                    return DistanceMethods.Hamming.Distance(source1, source2, isCaseSensitive) == Math.Max(source1.Length, source2.Length);
                case DistanceMethod.LongestCommonSubstringDistance:
                case DistanceMethod.iLongestCommonSubstringDistance:
                    return DistanceMethods.LongestCommonSubstring.Distance(source1, source2, isCaseSensitive) == Math.Min(source1.Length, source2.Length);
                case DistanceMethod.LongestCommonSubsequenceDistance:
                case DistanceMethod.iLongestCommonSubsequenceDistance:
                    return DistanceMethods.LongestCommonSubsequence.Distance(source1, source2, isCaseSensitive) == Math.Min(source1.Length, source2.Length);
                case DistanceMethod.JaroDistance:
                case DistanceMethod.iJaroDistance:
                    return DistanceMethods.Jaro.Distance(source1, source2, isCaseSensitive) == Math.Max(source1.Length, source2.Length);
                case DistanceMethod.NormalizedLevenshteinDistance:
                case DistanceMethod.iNormalizedLevenshteinDistance:
                    return DistanceMethods.NormalizedLevenshtein.Distance(source1, source2, isCaseSensitive) == Math.Max(source1.Length, source2.Length);
                case DistanceMethod.Levenshtein2Distance:
                case DistanceMethod.iLevenshtein2Distance:
                    return DistanceMethods.Levenshtein2.Distance(source1, source2, isCaseSensitive) == Math.Max(source1.Length, source2.Length);
                case DistanceMethod.TanimotoCoefficientDistance:
                case DistanceMethod.iTanimotoCoefficientDistance:
                    return DistanceMethods.TanimotoCoefficient.Distance(source1, source2, isCaseSensitive) == Math.Max(source1.Length, source2.Length);
                case DistanceMethod.PhraseTokenize:
                    return DistanceMethods.PhraseTokenize.Distance(source1, source2) == Math.Max(GetKeywordList(ref source1).Length, GetKeywordList(ref source2).Length);
                case DistanceMethod.SimplePhraseTokenize:
                    return DistanceMethods.SimplePhraseTokenize.Distance(source1, source2) == Math.Max(GetKeywordList(ref source1).Length, GetKeywordList(ref source2).Length);
                case DistanceMethod.DamerauLevenshtein:
                case DistanceMethod.iDamerauLevenshtein:
                default:
                    return DistanceMethods.DamerauLevenshtein.Distance(source1, source2, isCaseSensitive) == Math.Max(source1.Length, source2.Length);
            }
        }
        public static bool IsVerySimilar(string source1, string source2) => IsVerySimilar(source1, source2, DistanceMethod.UseDefaultDistanceMethod);
        public static bool IsVerySimilar(string source1, string source2, DistanceMethod distanceMethod) => IsMatch(source1, source2, Fuzzy.ISVERYSIMILAR, distanceMethod); // Is 90% similar
        public static bool IsSimilar(string source1, string source2) => IsSimilar(source1, source2, DistanceMethod.UseDefaultDistanceMethod);
        public static bool IsSimilar(string source1, string source2, DistanceMethod distanceMethod) => IsMatch(source1, source2, Fuzzy.ISSIMILAR, distanceMethod); // Is 75% similar
        public static bool IsSomeWhatSimilar(string source1, string source2) => IsSomeWhatSimilar(source1, source2, DistanceMethod.UseDefaultDistanceMethod);
        public static bool IsSomeWhatSimilar(string source1, string source2, DistanceMethod distanceMethod) => IsMatch(source1, source2, Fuzzy.ISSOMEWHATSIMILAR, distanceMethod); // Is 50% similar
        public static bool IsSlightlySimilar(string source1, string source2) => IsSlightlySimilar(source1, source2, DistanceMethod.UseDefaultDistanceMethod);
        public static bool IsSlightlySimilar(string source1, string source2, DistanceMethod distanceMethod) => IsMatch(source1, source2, Fuzzy.ISSLIGHTLYSIMILAR, distanceMethod); // Is 30% similar
        public static bool IsHardlySimilar(string source1, string source2) => IsHardlySimilar(source1, source2, DistanceMethod.UseDefaultDistanceMethod);
        public static bool IsHardlySimilar(string source1, string source2, DistanceMethod distanceMethod) => IsMatch(source1, source2, Fuzzy.ISHARDLYSIMILAR, distanceMethod); // Is 10% similar
        // GetIDistance should NOT be used until all associated classes have implementation for Percentage and Distance methods.
        // Classes that do NOT begin with an I, are classes which need work on these methods.
        public static IDistance GetIDistance(DistanceMethod distanceMethod)
        {
            if (distanceMethod == DistanceMethod.UseDefaultDistanceMethod)
                distanceMethod = DefaultDistanceMethod;
            switch (distanceMethod)
            {
                case DistanceMethod.Levenshtein:
                case DistanceMethod.iLevenshtein:
                    return new DistanceMethods.ILevenshtein();
                case DistanceMethod.JaroWinkler:
                case DistanceMethod.iJaroWinkler:
                    return new DistanceMethods.IJaroWinkler();
                case DistanceMethod.CosineSimilarity:
                case DistanceMethod.iCosineSimilarity:
                    return new DistanceMethods.ICosineSimilarity();
                case DistanceMethod.LongestCommonSequence:
                case DistanceMethod.iLongestCommonSequence:
                    return new DistanceMethods.ILongestCommonSequence();
                case DistanceMethod.JaccardSimilarity:
                case DistanceMethod.iJaccardSimilarity:
                    return new DistanceMethods.IJaccardSimilarity();
                case DistanceMethod.JaccardIndex:
                case DistanceMethod.iJaccardIndex:
                    return new DistanceMethods.IJaccardIndex();
                case DistanceMethod.OverlapCoefficient:
                case DistanceMethod.iOverlapCoefficient:
                    return new DistanceMethods.IOverlapCoefficient();
                case DistanceMethod.NeedlemanWunsch:
                case DistanceMethod.iNeedlemanWunsch:
                    return new DistanceMethods.INeedlemanWunsch();
                case DistanceMethod.SorensenDiceDistance:
                case DistanceMethod.iSorensenDiceDistance:
                    return new DistanceMethods.ISorensenDice();
                case DistanceMethod.RatcliffObershelpSimilarityDistance:
                case DistanceMethod.iRatcliffObershelpSimilarityDistance:
                    return new DistanceMethods.IRatcliffObershelpSimilarity();
                case DistanceMethod.HammingDistance:
                case DistanceMethod.iHammingDistance:
                    return new DistanceMethods.IHamming();
                case DistanceMethod.LongestCommonSubstringDistance:
                case DistanceMethod.iLongestCommonSubstringDistance:
                    return new DistanceMethods.ILongestCommonSubstring();
                case DistanceMethod.LongestCommonSubsequenceDistance:
                case DistanceMethod.iLongestCommonSubsequenceDistance:
                    return new DistanceMethods.ILongestCommonSubsequence();
                case DistanceMethod.JaroDistance:
                case DistanceMethod.iJaroDistance:
                    return new DistanceMethods.IJaro();
                case DistanceMethod.NormalizedLevenshteinDistance:
                case DistanceMethod.iNormalizedLevenshteinDistance:
                    return new DistanceMethods.INormalizedLevenshtein();
                case DistanceMethod.Levenshtein2Distance:
                case DistanceMethod.iLevenshtein2Distance:
                    return new DistanceMethods.ILevenshtein2();
                case DistanceMethod.TanimotoCoefficientDistance:
                case DistanceMethod.iTanimotoCoefficientDistance:
                    return new DistanceMethods.ITanimotoCoefficient();
                case DistanceMethod.EditDistance:
                case DistanceMethod.iEditDistance:
                    return new DistanceMethods.IEditDistanceWithWildCard();
                case DistanceMethod.BlockDistance:
                case DistanceMethod.iBlockDistance:
                    return new DistanceMethods.BlockDistance();
                case DistanceMethod.ChapmanLengthDeviation:
                case DistanceMethod.iChapmanLengthDeviation:
                    return new DistanceMethods.ChapmanLengthDeviation();
                case DistanceMethod.ChapmanMeanLength:
                case DistanceMethod.iChapmanMeanLength:
                    return new DistanceMethods.ChapmanMeanLength();
                case DistanceMethod.EuclideanDistance:
                case DistanceMethod.iEuclideanDistance:
                    return new DistanceMethods.EuclideanDistance();
                case DistanceMethod.MatchingCoefficient:
                case DistanceMethod.iMatchingCoefficient:
                    return new DistanceMethods.MatchingCoefficient();
                case DistanceMethod.MongeElkan:
                case DistanceMethod.iMongeElkan:
                    return new DistanceMethods.MongeElkan();
                case DistanceMethod.QGramsDistance:
                case DistanceMethod.iQGramsDistance:
                    return new DistanceMethods.QGramsDistance();
                case DistanceMethod.SmithWaterman:
                case DistanceMethod.iSmithWaterman:
                    return new DistanceMethods.SmithWaterman();
                case DistanceMethod.SmithWatermanGotoh:
                case DistanceMethod.iSmithWatermanGotoh:
                    return new DistanceMethods.SmithWatermanGotoh();
                case DistanceMethod.SmithWatermanGotohWindowedAffine:
                case DistanceMethod.iSmithWatermanGotohWindowedAffine:
                    return new DistanceMethods.SmithWatermanGotohWindowedAffine();
                case DistanceMethod.DiceSimilarity:
                case DistanceMethod.iDiceSimilarity:
                    return new DistanceMethods.DiceSimilarity();
                case DistanceMethod.PhraseTokenize:
                    return new DistanceMethods.IPhraseTokenize();
                case DistanceMethod.SimplePhraseTokenize:
                    return new DistanceMethods.ISimplePhraseTokenize();
                case DistanceMethod.DamerauLevenshtein:
                case DistanceMethod.iDamerauLevenshtein:
                    return new DistanceMethods.IDamerauLevenshtein();
                default:
                    return null;
            }
        }

        #endregion Similarity functions
        #region Distance functions
        public static double EditDistance(string source1, string source2, bool isCaseSensitive = true) => DistanceMethods.EditDistanceWithWildCard.Distance(source1, source2, isCaseSensitive);
        public static double BlockDistance(this string source1, string source2, bool isCaseSensitive = true)
        {
            FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            return blockDistance.GetSimilarity(source1, source2);
        }
        public static double ChapmanLengthDeviation(this string source1, string source2, bool isCaseSensitive = true)
        {
            FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            return chapmanLengthDeviation.GetSimilarity(source1, source2);
        }
        public static double ChapmanMeanLength(this string source1, string source2, bool isCaseSensitive = true)
        {
            FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            return chapmanMeanLength.GetSimilarity(source1, source2);
        }
        public static double EuclideanDistance(this string source1, string source2, bool isCaseSensitive = true)
        {
            FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            return euclideanDistance.GetSimilarity(source1, source2);
        }
        public static double MatchingCoefficient(this string source1, string source2, bool isCaseSensitive = true)
        {
            FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            return matchingCoefficient.GetSimilarity(source1, source2);
        }
        public static double MongeElkan(this string source1, string source2, bool isCaseSensitive = true)
        {
            FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            return mongeElkan.GetSimilarity(source1, source2);
        }
        public static double QGramsDistance(this string source1, string source2, bool isCaseSensitive = true)
        {
            FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            return qGramsDistance.GetSimilarity(source1, source2);
        }
        public static double SmithWaterman(this string source1, string source2, bool isCaseSensitive = true)
        {
            FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            return smithWaterman.GetSimilarity(source1, source2);
        }
        public static double SmithWatermanGotoh(this string source1, string source2, bool isCaseSensitive = true)
        {
            FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            return smithWatermanGotoh.GetSimilarity(source1, source2);
        }
        public static double SmithWatermanGotohWindowedAffine(this string source1, string source2, bool isCaseSensitive = true)
        {
            FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            return smithWatermanGotohWindowedAffine.GetSimilarity(source1, source2);
        }
        public static double DiceSimilarity(this string source1, string source2, bool isCaseSensitive = true)
        {
            FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            return diceSimilarity.GetSimilarity(source1, source2);
        }
        public static double NeedlemanWunsch(this string source1, string source2, bool isCaseSensitive = true) => DistanceMethods.NeedlemanWunsch.Percentage(source1, source2, isCaseSensitive);
        public static double CosineSimilarity(this string source1, string source2, bool isCaseSensitive = true) => DistanceMethods.CosineSimilarity.Percentage(source1, source2, isCaseSensitive);
        public static double JaccardSimilarity(this string source1, string source2, bool isCaseSensitive = true) => DistanceMethods.JaccardSimilarity.Percentage(source1, source2, isCaseSensitive);
        public static double LongestCommonSequence(this string source1, string source2, bool isCaseSensitive = true) => DistanceMethods.LongestCommonSequence.Percentage(source1, source2, isCaseSensitive);
        public static double PhraseTokenize(this string source1, string source2, bool isCaseSensitive = true) => DistanceMethods.PhraseTokenize.Distance(source1, source2, isCaseSensitive);
        public static double SimplePhraseTokenize(this string source1, string source2, bool isCaseSensitive = true) => DistanceMethods.SimplePhraseTokenize.Distance(source1, source2, isCaseSensitive);
        public static double LevenshteinDistance(this string source1, string source2, bool isCaseSensitive = true) => DistanceMethods.Levenshtein.Distance(source1, source2, isCaseSensitive);
        public static double DamerauLevenshteinDistance(this string source1, string source2, bool isCaseSensitive = true) => DistanceMethods.DamerauLevenshtein.Distance(source1, source2, isCaseSensitive);
        public static double JaroWinklerDistance(this string source1, string source2, bool isCaseSensitive = true) => DistanceMethods.JaroWinkler.Distance(source1, source2, isCaseSensitive);
        public static double OverlapCoefficientDistance(this string source1, string source2, bool isCaseSensitive = true) => DistanceMethods.OverlapCoefficient.Distance(source1, source2, isCaseSensitive);
        public static double JaccardDistance(this string source1, string source2, bool isCaseSensitive = true) => DistanceMethods.JaccardIndex.Distance(source1, source2, isCaseSensitive);
        public static double JaccardIndex(this string source1, string source2, bool isCaseSensitive = true) => DistanceMethods.JaccardIndex.Distance(source1, source2, isCaseSensitive);
        public static double SorensenDiceDistance(this string source1, string source2, bool isCaseSensitive = true) => DistanceMethods.SorensenDice.Distance(source1, source2, isCaseSensitive);
        public static double RatcliffObershelpSimilarityDistance(this string source1, string source2, bool isCaseSensitive = true) => DistanceMethods.RatcliffObershelpSimilarity.Distance(source1, source2, isCaseSensitive);
        public static double HammingDistance(this string source1, string source2, bool isCaseSensitive = true) => DistanceMethods.Hamming.Distance(source1, source2, isCaseSensitive);
        public static double LongestCommonSubstringDistance(this string source1, string source2, bool isCaseSensitive = true) => DistanceMethods.LongestCommonSubstring.Distance(source1, source2, isCaseSensitive);
        public static double LongestCommonSubsequenceDistance(this string source1, string source2, bool isCaseSensitive = true) => DistanceMethods.LongestCommonSubsequence.Distance(source1, source2, isCaseSensitive);
        public static double JaroDistance(this string source1, string source2, bool isCaseSensitive = true) => DistanceMethods.Jaro.Distance(source1, source2, isCaseSensitive);
        public static double NormalizedLevenshteinDistance(this string source1, string source2, bool isCaseSensitive = true) => DistanceMethods.NormalizedLevenshtein.Distance(source1, source2, isCaseSensitive);
        public static double Levenshtein2Distance(this string source1, string source2, bool isCaseSensitive = true) => DistanceMethods.Levenshtein2.Distance(source1, source2, isCaseSensitive);
        public static double TanimotoCoefficientDistance(this string source1, string source2, bool isCaseSensitive = true) => DistanceMethods.TanimotoCoefficient.Distance(source1, source2, isCaseSensitive);
        public static double PhraseSimplifiedDiff(this string source1, string source2) => DistanceMethods.SimplePhraseTokenize.Distance(source1, source2, false);
        #endregion Distance functions
        #region SameFunc functions
        public static bool SameFirstLastName(string source1, string source2, bool isCaseSensitive = false) => Misc.Sameness.SameFirstLastName(source1, source2, isCaseSensitive);
        public static bool SamePhone(string source1, string source2, bool isCaseSensitive = false) => Misc.Sameness.SamePhone(source1, source2, isCaseSensitive);
        public static bool SameSocial(string source1, string source2, bool isCaseSensitive = false) => Misc.Sameness.SameSocial(source1, source2, isCaseSensitive);
        public static bool SameZip(string source1, string source2, bool isCaseSensitive = false) => Misc.Sameness.SameZip(source1, source2, isCaseSensitive);
        public static bool SameAddress(string source1, string source2, bool isCaseSensitive = false) => Misc.Sameness.SameAddress(source1, source2, isCaseSensitive);
        public static bool SameDate(string source1, string source2, bool isCaseSensitive = false) => Misc.Sameness.SameDate(source1, source2, isCaseSensitive);
        public static bool SameFileName(string source1, string source2, bool isCaseSensitive = false) => Misc.Sameness.SameFileName(source1, source2, isCaseSensitive);
        public static bool SameNumber(string source1, string source2, bool isCaseSensitive = false) => Misc.Sameness.SameNumber(source1, source2, isCaseSensitive);
        #endregion SameFunc functions
        #region Phonetic (sound) functions
        public static bool MatchRatingApproach(this string source1, string source2, bool isVerySimilar = true)
        {
            return isVerySimilar ? matchRatingApproach.IsVerySimilar(source1, source2) : matchRatingApproach.IsSimilar(source1, source2);
        }
        public static bool Metaphone(this string source1, string source2)
        {
            string[] sources = { source1,  source2 };
            return metaphone.IsSimilar(sources);
        }
        public static bool CaverPhonePhonix(this string source1, string source2)
        {
            string[] sources = { source1,  source2 };
            return caverPhonePhonix.IsSimilar(sources);
        }
        public static bool DoubleMetaphone(this string source1, string source2)
        {
            string[] sources = { source1,  source2 };
            return doubleMetaphone.IsSimilar(sources);
        }
        public static bool ColognePhonetics(this string source1, string source2)
        {
            string s1 = ColognePhoneticsSharp.ColognePhonetics.GetPhonetics(source1);
            string s2 = ColognePhoneticsSharp.ColognePhonetics.GetPhonetics(source2);
            return s1 == s2;
        }
        public static bool Caverphone2(this string source1, string source2,
            DistanceMethod distanceMethod,
            bool isVerySimilar = true)
        {
            string s1 = PhoneticMethods.Caverphone.BuildKey(source1);
            string s2 = PhoneticMethods.Caverphone.BuildKey(source2);
            return Compare(s1, s2, distanceMethod, isVerySimilar);
        }
        public static bool Caverphone2(this string source1, string source2) => Caverphone2(source1, source2, DistanceMethod.ExactMatch);
        public static string Caverphone2(string source1)
        {
            return PhoneticMethods.Caverphone.BuildKey(source1);
        }
        public static bool Soundex2(this string source1, string source2,
            DistanceMethod distanceMethod,
            bool isVerySimilar)
        {
            string s1 = PhoneticMethods.Soundex.Generate(source1);
            string s2 = PhoneticMethods.Soundex.Generate(source2);
            return Compare(s1, s2, distanceMethod, isVerySimilar);
        }
        public static bool Soundex2(this string source1, string source2) => Soundex2(source1, source2, DistanceMethod.ExactMatch, true);
        public static string Soundex2(string source1)
        {
            return PhoneticMethods.Soundex.Generate(source1);
        }
        public static bool EnPhoneticDistance_IsSupported() => FuzzyPhoneticMatching.EnPhoneticDistance_Supported;
        public static bool EnPhoneticDistance(this string source1, string source2, bool isVerySimilar = true)
        {
            return FuzzyPhoneticMatching.EnPhoneticDistance_Supported ? FuzzyPhoneticMatching.EnPhoneticDistance(source1, source2, isVerySimilar) : Soundex2(source1, source2, DistanceMethod.ExactMatch, isVerySimilar);
        }
        public static string GetSoundCode(string source1, SameSoundMethod sameSoundMethod = SameSoundMethod.UseDefaultSameSoundMethod)
        {
            if (sameSoundMethod == SameSoundMethod.UseDefaultSameSoundMethod)
                sameSoundMethod = DefaultSameSoundMethod;
            switch (sameSoundMethod)
            {
                case SameSoundMethod.Caverphone2:
                    return Caverphone2(source1);
                case SameSoundMethod.Soundex2:
                default:
                    return Soundex2(source1);
            }
        }
        public static bool SameSound(this string source1, string source2,
            SameSoundMethod sameSoundMethod = SameSoundMethod.UseDefaultSameSoundMethod,
            DistanceMethod distanceMethod = DistanceMethod.ExactMatch,
            bool isVerySimilar = true)
        {
            if (sameSoundMethod == SameSoundMethod.UseDefaultSameSoundMethod)
                sameSoundMethod = DefaultSameSoundMethod;
            switch (sameSoundMethod)
            {
                case SameSoundMethod.EnPhoneticDistance:
                    return EnPhoneticDistance(source1, source2, isVerySimilar);
                case SameSoundMethod.Caverphone2:
                    return Caverphone2(source1, source2, distanceMethod, isVerySimilar);
                case SameSoundMethod.MatchRatingApproach:
                    return MatchRatingApproach(source1, source2);
                case SameSoundMethod.Metaphone:
                    return Metaphone(source1, source2);
                case SameSoundMethod.CaverPhonePhonix:
                    return CaverPhonePhonix(source1, source2);
                case SameSoundMethod.DoubleMetaphone:
                    return DoubleMetaphone(source1, source2);
                case SameSoundMethod.ColognePhonetics:
                    return ColognePhonetics(source1, source2);
                case SameSoundMethod.Soundex2:
                default:
                    return Soundex2(source1, source2, distanceMethod, isVerySimilar);
            }
        }
        public static bool Compare(string source1, string source2, DistanceMethod CompareMethod, bool isVerySimilar)
        {
            switch (CompareMethod)
            {
                case DistanceMethod.ExactMatch:
                    return source1 == source2;
                default:
                    return isVerySimilar ? IsVerySimilar(source1, source2, CompareMethod) : IsSimilar(source1, source2, CompareMethod);
            }
        }
        #endregion Phonetic (sound) functions
        #region Miscellaneous functions
        // ToDo: Consider adding the following fuzzy_score, vector search, MD5, UUID, sha256, date parser, JSON, path handler, URL handler, undo-redo
        //      math -> https://github.com/uzbekdev1/SqliteExtension
        //      see following for good FuzzyInst names (https://github.com/schiffma/distlib)
        //      MD5 -> https://github.com/thechampion/sqlite3_extensions (md5, sha1, sha224, sha256, sha384, and sha512)
        public static string HasCharInSameOrder(this string word) => Misc.HasInSameOrder.HasCharInSameOrder(word, "%"); // Needed for CPP code access
        public static string HasCharInSameOrder(this string word, string sep) => Misc.HasInSameOrder.HasCharInSameOrder(word, sep); // SQL function extension
        public static string HasWordsInSameOrder(string words, string fieldToCompare) => Misc.HasInSameOrder.HasWordsInSameOrder(words, fieldToCompare, false); // Needed for CPP code access
        public static string HasWordsInSameOrder(string words, string fieldToCompare, bool doNearWordSearch, int minimumWordLenForWordInWordMatch = 1, bool simplify = false) =>
           Misc.HasInSameOrder.HasWordsInSameOrder(words, fieldToCompare, doNearWordSearch, minimumWordLenForWordInWordMatch, simplify); // SQL function extension
        public static string RegexReplace(this string source, string pattern, string replacement)
        {
            return Regex.Replace(source, pattern, replacement);
        }
        public static string RegexSearch(this string source, string pattern)
        {
            Regex r = new Regex(pattern, RegexOptions.IgnoreCase);
            Match m = r.Match(source);
            return m.Success ? m.Value : "";
        }
        public static bool RegexMatch(this string source, string pattern)
        {
            Regex r = new Regex(pattern, RegexOptions.IgnoreCase);
            Match m = r.Match(source);
            return m.Success;
        }
        public static string StringReverse(this string source)
        {
            char[] charArray = source.ToCharArray();
            Array.Reverse(charArray);
            return new string(charArray);
        }
        public static int MaxValue(int x, int y) => Math.Max(x, y);
        public static int MinValue(int x, int y) => Math.Min(x, y);
        public static int MaxLength(string source1, string source2) => Math.Max(source1.Length, source2.Length);
        public static int MinLength(string source1, string source2) => Math.Min(source1.Length, source2.Length);
        public static bool IsFileExist(string path) => File.Exists(path);
        public static bool IsDirExist(string path) => Directory.Exists(path);
        public static string GetFileName(string path) => Path.GetFileName(path);
        public static string GetExtension(string path) => Path.GetExtension(path);
        public static string GetDirectoryName(string path) => System.IO.Path.GetDirectoryName(path);
        public static string GetFileNameWithoutExtension(string path) => System.IO.Path.GetFileNameWithoutExtension(path);
        #endregion Miscellaneous functions
        #region Case INSENSITIVE phrase comparison associated functions (token ratio)
        public static double PhraseHowSimilar(string source1, string source2)
        {
            string[] list1 = GetKeywordList(ref source1, false, true);
            string[] list2 = GetKeywordList(ref source2, false, true);
            double sourceLength = Math.Max(list1.Length, list2.Length);
            double diff = DistanceMethods.PhraseTokenize.Distance(source1, source2,false, true);
            return diff == 0 ? 1.0f : (sourceLength - diff) / sourceLength;
        }
        public static bool IsPhraseSimilar(string source1, string source2, double desiredSimilarity) => PhraseHowSimilar(source1, source2) >= desiredSimilarity;
        public static bool PhraseVerySimilar(string source1, string source2) => IsPhraseSimilar(source1, source2, Fuzzy.ISVERYSIMILAR); // Is 90% similar
        public static bool PhraseSimilar(string source1, string source2) => IsPhraseSimilar(source1, source2, Fuzzy.ISSIMILAR); // Is 75% similar
        public static bool PhraseSomeWhatSimilar(string source1, string source2) => IsPhraseSimilar(source1, source2, Fuzzy.ISSOMEWHATSIMILAR); // Is 50% similar
        public static bool PhraseSlightlySimilar(string source1, string source2) => IsPhraseSimilar(source1, source2, Fuzzy.ISSLIGHTLYSIMILAR); // Is 30% similar
        public static bool PhraseHardlySimilar(string source1, string source2) => IsPhraseSimilar(source1, source2, Fuzzy.ISHARDLYSIMILAR); // Is 10% similar
        public static string GetKeywordStr(string name, bool removeSpace = false, bool simplify = false, bool insertSpacesBetweenCapitalLetters = true)
        {
            if (insertSpacesBetweenCapitalLetters)
            {
                name = Regex.Replace(name, "([a-z])([A-Z])", "$1 $2"); // Put spaces between words like FooDigitHere
                name = Regex.Replace(name, "([A-Z][a-z]*)([A-Z][a-z]*)", "$1 $2"); // Put spaces between words like FooDigitHere
            }
            if (simplify)
            {
                name = Regex.Replace(name, @"([A-Z]\.){2,}", ""); // Remove abbreviated letters
                name = Regex.Replace(name, "[^a-zA-Z]", " "); // Remove non-alpha
                name = Regex.Replace(name, @"(?i)^A\s", " ");
                name = Regex.Replace(name, @"(?i)^The\s", " ");
                name = Regex.Replace(name, @"(?i)\sA\s", " ");
                name = Regex.Replace(name, @"(?i)\sThe\s", " ");
                // name = Regex.Replace(name, @"(?i)\sand\s", "");
            }
            name = removeSpace ? name.Replace(" ", "") : name.Replace("  ", " ");
            name = name.Trim();
            return name;
        }
        public static string[] GetKeywordList(ref string name, bool simplify = false, bool insertSpacesBetweenCapitalLetters = true)
        {
            name = GetKeywordStr(name, false, simplify, insertSpacesBetweenCapitalLetters);
            name = name.Replace(" ", ",");
            string[] keywords = name.Split(new char[] { ',' }, StringSplitOptions.RemoveEmptyEntries).Select(x => x.Trim().ToLower()).Distinct().ToArray();
            return keywords;
        }
        public static string[] KeywordList(string name, bool simplify = false, bool insertSpacesBetweenCapitalLetters = true)
        {
            name = GetKeywordStr(name, false, simplify, insertSpacesBetweenCapitalLetters);
            name = name.Replace(" ", ",");
            string[] keywords = name.Split(new char[] { ',' }, StringSplitOptions.RemoveEmptyEntries).Select(x => x.Trim().ToLower()).Distinct().ToArray();
            return keywords;
        }
        public static int GetWordCount(string words, bool simplify = false, bool insertSpacesBetweenCapitalLetters = true)
        {
            string[] list1 = GetKeywordList(ref words, simplify, insertSpacesBetweenCapitalLetters);
            return list1.Length;
        }
        public static int GetMatchCount(string phrase1, string phrase2, ref int qtyNotMatching, bool simplify = true, bool insertSpacesBetweenCapitalLetters = true, bool isCaseSensitive = false)
        {
            phrase1 = GetKeywordStr(phrase1, true, simplify, insertSpacesBetweenCapitalLetters);
            phrase2 = GetKeywordStr(phrase2, true, simplify, insertSpacesBetweenCapitalLetters);
            if (String.IsNullOrEmpty(phrase1) || String.IsNullOrEmpty(phrase2))
                return 0;
            FixIfIsCaseSensitive(ref phrase1, ref phrase2, isCaseSensitive);
            qtyNotMatching = 0;
            int matchCount = 0;
            string matchingLetters = "";
            foreach (char c in phrase1)
            {
                if (phrase2.Contains(c))
                {
                    if (!matchingLetters.Contains(c))
                    {
                        ++matchCount;
                        matchingLetters += $"{c}";
                    }
                    else
                    {
                        matchingLetters += $"{c}";
                        int count1 = matchingLetters.Count(x => x == c);
                        int count2 = phrase2.Count(x => x == c);
                        if (count2 >= count1)
                            ++matchCount;
                        else
                            ++qtyNotMatching;
                    }
                }
                else
                    ++qtyNotMatching;
            }
            return matchCount;
        }
        #endregion Phrase comparison associated functions
    }
}
