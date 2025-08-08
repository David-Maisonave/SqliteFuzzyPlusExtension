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

using static FuzzyPlusCSharp.SmithWatermanGotohWindowedAffine;
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
        public bool IsVerySimilar(string source1, string source2) => Fuzzy.IsMatch(source1, source2, 0.9f, distanceMethod); // Is 90% similar
        public bool IsSimilar(string source1, string source2) => Fuzzy.IsMatch(source1, source2, 0.75f, distanceMethod); // Is 75% similar
        public bool IsSomeWhatSimilar(string source1, string source2) => Fuzzy.IsMatch(source1, source2, 0.5f, distanceMethod); // Is 50% similar
        public bool IsSlightlySimilar(string source1, string source2) => Fuzzy.IsMatch(source1, source2, 0.3f, distanceMethod); // Is 30% similar
        public bool IsHardlySimilar(string source1, string source2) => Fuzzy.IsMatch(source1, source2, 0.1f, distanceMethod); // Is 10% similar
        public bool IsMatch(string source1, string source2, double desiredSimilarity) => Fuzzy.HowSimilar(source1, source2, distanceMethod) >= desiredSimilarity;
        public double HowSimilar(string source1, string source2) => Fuzzy.HowSimilar(source1, source2, distanceMethod);
        public bool IsNotSimilar(string source1, string source2) => Fuzzy.IsNotSimilar(source1, source2, distanceMethod);
    }
    #endregion Non-Static version
    //////////////////////////////////////////////////////////////////////
    /// Static version 
    public static class Fuzzy
    {
        #region DistanceMethod definitions
        public const int CASE_INSENSITIVE = 256;
        public const int CPP_ONLY_FUZZY = 128;
        public const int TOKEN_METHODS = 64;
        public const int PHRASE_METHODS = TOKEN_METHODS + 32;
        public const int METHODS_UP_FOR_DELETION = PHRASE_METHODS + 16;
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
            SameSound_StrCmp,
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
            EnPhoneticDistance,
            // ------------------------------------------------------------
            // These functions are NOT supported by CSharp Fuzzy class code, and are only here for C++ SqliteFuzzyPlusExtension usage.
            // SQLean phonetic external functions. 
            fuzzy_caver,
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
                    diff = LevenshteinDistance(source1, source2, isCaseSensitive);
                    break;
                case DistanceMethod.JaroWinkler:
                case DistanceMethod.iJaroWinkler:
                    diff = JaroWinklerPercentage(source1, source2, isCaseSensitive);
                    break;
                case DistanceMethod.CosineSimilarity:
                case DistanceMethod.iCosineSimilarity:
                    return CosineSimilarityClass.Percentage(source1, source2, isCaseSensitive);
                case DistanceMethod.LongestCommonSequence:
                case DistanceMethod.iLongestCommonSequence:
                    return LongestCommonSequenceClass.Percentage(source1, source2, isCaseSensitive);
                case DistanceMethod.JaccardSimilarity:
                case DistanceMethod.iJaccardSimilarity:
                    return JaccardSimilarityClass.Percentage(source1, source2, isCaseSensitive);
                case DistanceMethod.JaccardIndex:
                case DistanceMethod.iJaccardIndex:
                    diff = JaccardDistance(source1, source2, isCaseSensitive);
                    break;
                case DistanceMethod.OverlapCoefficient:
                case DistanceMethod.iOverlapCoefficient:
                    diff = OverlapCoefficientDistance(source1, source2, isCaseSensitive);
                    break;
                case DistanceMethod.NeedlemanWunsch:
                case DistanceMethod.iNeedlemanWunsch:
                    return NeedlemanWunschClass.Percentage(source1, source2, isCaseSensitive);
                case DistanceMethod.SorensenDiceDistance:
                case DistanceMethod.iSorensenDiceDistance:
                    diff = SorensenDiceDistance(source1, source2, isCaseSensitive);
                    break;
                case DistanceMethod.RatcliffObershelpSimilarityDistance:
                case DistanceMethod.iRatcliffObershelpSimilarityDistance:
                    diff = RatcliffObershelpSimilarityDistance(source1, source2, isCaseSensitive);
                    break;
                case DistanceMethod.HammingDistance:
                case DistanceMethod.iHammingDistance:
                    diff = HammingDistance(source1, source2, isCaseSensitive);
                    break;
                case DistanceMethod.LongestCommonSubstringDistance:
                case DistanceMethod.iLongestCommonSubstringDistance:
                    diff = LongestCommonSubstringDistance(source1, source2, isCaseSensitive);
                    sourceLength = Math.Min(source1.Length, source2.Length);
                    break;
                case DistanceMethod.LongestCommonSubsequenceDistance:
                case DistanceMethod.iLongestCommonSubsequenceDistance:
                    diff = LongestCommonSubsequenceDistance(source1, source2, isCaseSensitive);
                    sourceLength = Math.Min(source1.Length, source2.Length);
                    break;
                case DistanceMethod.JaroDistance:
                case DistanceMethod.iJaroDistance:
                    diff = JaroDistance(source1, source2, isCaseSensitive);
                    break;
                case DistanceMethod.NormalizedLevenshteinDistance:
                case DistanceMethod.iNormalizedLevenshteinDistance:
                    diff = NormalizedLevenshteinDistance(source1, source2, isCaseSensitive);
                    break;
                case DistanceMethod.Levenshtein2Distance:
                case DistanceMethod.iLevenshtein2Distance:
                    return Levenshtein2Distance(source1, source2, isCaseSensitive);
                case DistanceMethod.TanimotoCoefficientDistance:
                case DistanceMethod.iTanimotoCoefficientDistance:
                    diff = TanimotoCoefficientDistance(source1, source2, isCaseSensitive);
                    break;
                case DistanceMethod.EditDistance:
                case DistanceMethod.iEditDistance:
                    diff = EditDistance(source1, source2, isCaseSensitive);
                    break;
                case DistanceMethod.BlockDistance:
                case DistanceMethod.iBlockDistance:
                    FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
                    BlockDistance sim2 = new BlockDistance();
                    diff = sim2.GetSimilarity(source1, source2);
                    break;
                case DistanceMethod.ChapmanLengthDeviation:
                case DistanceMethod.iChapmanLengthDeviation:
                    FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
                    ChapmanLengthDeviation sim3 = new ChapmanLengthDeviation();
                    diff = sim3.GetSimilarity(source1, source2);
                    break;
                case DistanceMethod.ChapmanMeanLength:
                case DistanceMethod.iChapmanMeanLength:
                    FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
                    ChapmanMeanLength sim0 = new ChapmanMeanLength();
                    diff = sim0.GetSimilarity(source1, source2);
                    break;
                case DistanceMethod.EuclideanDistance:
                case DistanceMethod.iEuclideanDistance:
                    FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
                    EuclideanDistance sim4 = new EuclideanDistance();
                    diff = sim4.GetSimilarity(source1, source2);
                    break;
                case DistanceMethod.MatchingCoefficient:
                case DistanceMethod.iMatchingCoefficient:
                    FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
                    MatchingCoefficient sim5 = new MatchingCoefficient();
                    diff = sim5.GetSimilarity(source1, source2);
                    break;
                case DistanceMethod.MongeElkan:
                case DistanceMethod.iMongeElkan:
                    FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
                    MongeElkan sim6 = new MongeElkan();
                    diff = sim6.GetSimilarity(source1, source2);
                    break;
                case DistanceMethod.QGramsDistance:
                case DistanceMethod.iQGramsDistance:
                    FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
                    QGramsDistance sim7 = new QGramsDistance();
                    diff = sim7.GetSimilarity(source1, source2);
                    break;
                case DistanceMethod.SmithWaterman:
                case DistanceMethod.iSmithWaterman:
                    FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
                    SmithWaterman sim8 = new SmithWaterman();
                    diff = sim8.GetSimilarity(source1, source2);
                    break;
                case DistanceMethod.SmithWatermanGotoh:
                case DistanceMethod.iSmithWatermanGotoh:
                    FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
                    SmithWatermanGotoh sim9 = new SmithWatermanGotoh();
                    diff = sim9.GetSimilarity(source1, source2);
                    break;
                case DistanceMethod.SmithWatermanGotohWindowedAffine:
                case DistanceMethod.iSmithWatermanGotohWindowedAffine:
                    FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
                    SmithWatermanGotohWindowedAffine sim1 = new SmithWatermanGotohWindowedAffine();
                    diff = sim1.GetSimilarity(source1, source2);
                    break;
                case DistanceMethod.DiceSimilarity:
                case DistanceMethod.iDiceSimilarity:
                    diff = DiceSimilarity(source1, source2, isCaseSensitive);
                    break;
                case DistanceMethod.PhraseTokenize:
                    diff = GetPhraseDifference(source1, source2);
                    sourceLength = Math.Max(GetKeywordList(ref source1).Length, GetKeywordList(ref source2).Length);
                    break;
                case DistanceMethod.SimplePhraseTokenize:
                    diff = PhraseSimplifiedDiff(source1, source2);
                    sourceLength = Math.Max(GetKeywordList(ref source1).Length, GetKeywordList(ref source2).Length);
                    break;
                case DistanceMethod.DamerauLevenshtein:
                case DistanceMethod.iDamerauLevenshtein:
                default:
                    diff = DamerauLevenshteinDistance(source1, source2, isCaseSensitive);
                    break;
            }
            return diff == 0 ? 1.0f : (sourceLength - diff) / sourceLength;
        }
        public static double Distance(string source1, string source2, DistanceMethod distanceMethod = DistanceMethod.UseDefaultDistanceMethod)
        {
            if (distanceMethod == DistanceMethod.UseDefaultDistanceMethod)
                distanceMethod = DefaultDistanceMethod;
            bool isCaseSensitive = IsCaseSensitive(distanceMethod);
            switch (distanceMethod) 
            {
                case DistanceMethod.Levenshtein:
                case DistanceMethod.iLevenshtein:
                    return LevenshteinDistance(source1, source2, isCaseSensitive);
                case DistanceMethod.JaroWinkler:
                case DistanceMethod.iJaroWinkler:
                    return JaroWinklerPercentage(source1, source2, isCaseSensitive);
                case DistanceMethod.CosineSimilarity:
                case DistanceMethod.iCosineSimilarity:
                    return CosineSimilarityClass.Percentage(source1, source2, isCaseSensitive);
                case DistanceMethod.LongestCommonSequence:
                case DistanceMethod.iLongestCommonSequence:
                    return LongestCommonSequenceClass.Percentage(source1, source2, isCaseSensitive);
                case DistanceMethod.JaccardSimilarity:
                case DistanceMethod.iJaccardSimilarity:
                    return JaccardSimilarityClass.Percentage(source1, source2, isCaseSensitive);
                case DistanceMethod.JaccardIndex:
                case DistanceMethod.iJaccardIndex:
                    return JaccardDistance(source1, source2, isCaseSensitive);
                case DistanceMethod.OverlapCoefficient:
                case DistanceMethod.iOverlapCoefficient:
                    return OverlapCoefficientDistance(source1, source2, isCaseSensitive);
                case DistanceMethod.NeedlemanWunsch:
                case DistanceMethod.iNeedlemanWunsch:
                    return NeedlemanWunschClass.Percentage(source1, source2, isCaseSensitive);
                case DistanceMethod.SorensenDiceDistance:
                case DistanceMethod.iSorensenDiceDistance:
                    return SorensenDiceDistance(source1, source2, isCaseSensitive);
                case DistanceMethod.RatcliffObershelpSimilarityDistance:
                case DistanceMethod.iRatcliffObershelpSimilarityDistance:
                    return RatcliffObershelpSimilarityDistance(source1, source2, isCaseSensitive);
                case DistanceMethod.HammingDistance:
                case DistanceMethod.iHammingDistance:
                    return HammingDistance(source1, source2, isCaseSensitive);
                case DistanceMethod.LongestCommonSubstringDistance:
                case DistanceMethod.iLongestCommonSubstringDistance:
                    return LongestCommonSubstringDistance(source1, source2, isCaseSensitive);
                case DistanceMethod.LongestCommonSubsequenceDistance:
                case DistanceMethod.iLongestCommonSubsequenceDistance:
                    return LongestCommonSubsequenceDistance(source1, source2, isCaseSensitive);
                case DistanceMethod.JaroDistance:
                case DistanceMethod.iJaroDistance:
                    return JaroDistance(source1, source2, isCaseSensitive);
                case DistanceMethod.NormalizedLevenshteinDistance:
                case DistanceMethod.iNormalizedLevenshteinDistance:
                    return NormalizedLevenshteinDistance(source1, source2, isCaseSensitive);
                case DistanceMethod.Levenshtein2Distance:
                case DistanceMethod.iLevenshtein2Distance:
                    return Levenshtein2Distance(source1, source2, isCaseSensitive);
                case DistanceMethod.TanimotoCoefficientDistance:
                case DistanceMethod.iTanimotoCoefficientDistance:
                    return TanimotoCoefficientDistance(source1, source2, isCaseSensitive);
                case DistanceMethod.EditDistance:
                case DistanceMethod.iEditDistance:
                    return EditDistance(source1, source2, isCaseSensitive);
                case DistanceMethod.BlockDistance:
                case DistanceMethod.iBlockDistance:
                    FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
                    BlockDistance sim2 = new BlockDistance();
                    return sim2.GetSimilarity(source1, source2);
                case DistanceMethod.ChapmanLengthDeviation:
                case DistanceMethod.iChapmanLengthDeviation:
                    FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
                    ChapmanLengthDeviation sim3 = new ChapmanLengthDeviation();
                    return sim3.GetSimilarity(source1, source2);
                case DistanceMethod.ChapmanMeanLength:
                case DistanceMethod.iChapmanMeanLength:
                    FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
                    ChapmanMeanLength sim0 = new ChapmanMeanLength();
                    return sim0.GetSimilarity(source1, source2);
                case DistanceMethod.EuclideanDistance:
                case DistanceMethod.iEuclideanDistance:
                    FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
                    EuclideanDistance sim4 = new EuclideanDistance();
                    return sim4.GetSimilarity(source1, source2);
                case DistanceMethod.MatchingCoefficient:
                case DistanceMethod.iMatchingCoefficient:
                    FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
                    MatchingCoefficient sim5 = new MatchingCoefficient();
                    return sim5.GetSimilarity(source1, source2);
                case DistanceMethod.MongeElkan:
                case DistanceMethod.iMongeElkan:
                    FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
                    MongeElkan sim6 = new MongeElkan();
                    return sim6.GetSimilarity(source1, source2);
                case DistanceMethod.QGramsDistance:
                case DistanceMethod.iQGramsDistance:
                    FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
                    QGramsDistance sim7 = new QGramsDistance();
                    return sim7.GetSimilarity(source1, source2);
                case DistanceMethod.SmithWaterman:
                case DistanceMethod.iSmithWaterman:
                    FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
                    SmithWaterman sim8 = new SmithWaterman();
                    return sim8.GetSimilarity(source1, source2);
                case DistanceMethod.SmithWatermanGotoh:
                case DistanceMethod.iSmithWatermanGotoh:
                    FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
                    SmithWatermanGotoh sim9 = new SmithWatermanGotoh();
                    return sim9.GetSimilarity(source1, source2);
                case DistanceMethod.SmithWatermanGotohWindowedAffine:
                case DistanceMethod.iSmithWatermanGotohWindowedAffine:
                    FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
                    SmithWatermanGotohWindowedAffine sim1 = new SmithWatermanGotohWindowedAffine();
                    return sim1.GetSimilarity(source1, source2);
                case DistanceMethod.DiceSimilarity:
                case DistanceMethod.iDiceSimilarity:
                    return DiceSimilarity(source1, source2, isCaseSensitive);
                case DistanceMethod.PhraseTokenize:
                    return GetPhraseDifference(source1, source2);
                case DistanceMethod.SimplePhraseTokenize:
                    return PhraseSimplifiedDiff(source1, source2);
                case DistanceMethod.DamerauLevenshtein:
                case DistanceMethod.iDamerauLevenshtein:
                default:
                    return DamerauLevenshteinDistance(source1, source2, isCaseSensitive);
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
                    return LevenshteinDistance(source1, source2, isCaseSensitive) == Math.Max(source1.Length, source2.Length);
                case DistanceMethod.JaroWinkler:
                case DistanceMethod.iJaroWinkler:
                    return JaroWinklerPercentage(source1, source2, isCaseSensitive) == Math.Max(source1.Length, source2.Length);
                case DistanceMethod.CosineSimilarity:
                case DistanceMethod.iCosineSimilarity:
                    return CosineSimilarityClass.Percentage(source1, source2, isCaseSensitive) == 0;
                case DistanceMethod.JaccardSimilarity:
                case DistanceMethod.iJaccardSimilarity:
                    return JaccardSimilarityClass.Percentage(source1, source2, isCaseSensitive) == 0;
                case DistanceMethod.JaccardIndex:
                case DistanceMethod.iJaccardIndex:
                    return JaccardDistance(source1, source2, isCaseSensitive) == Math.Max(source1.Length, source2.Length);
                case DistanceMethod.OverlapCoefficient:
                case DistanceMethod.iOverlapCoefficient:
                    return OverlapCoefficientDistance(source1, source2, isCaseSensitive) == Math.Max(source1.Length, source2.Length);
                case DistanceMethod.NeedlemanWunsch:
                case DistanceMethod.iNeedlemanWunsch:
                    return NeedlemanWunschClass.Percentage(source1, source2, isCaseSensitive) == 0;
                case DistanceMethod.LongestCommonSequence:
                case DistanceMethod.iLongestCommonSequence:
                    return LongestCommonSequenceClass.Difference(source1, source2, isCaseSensitive) == Math.Max(source1.Length, source2.Length);
                case DistanceMethod.SorensenDiceDistance:
                case DistanceMethod.iSorensenDiceDistance:
                    return SorensenDiceDistance(source1, source2, isCaseSensitive) == Math.Max(source1.Length, source2.Length);
                case DistanceMethod.RatcliffObershelpSimilarityDistance:
                case DistanceMethod.iRatcliffObershelpSimilarityDistance:
                    return RatcliffObershelpSimilarityDistance(source1, source2, isCaseSensitive) == Math.Max(source1.Length, source2.Length);
                case DistanceMethod.HammingDistance:
                case DistanceMethod.iHammingDistance:
                    return HammingDistance(source1, source2, isCaseSensitive) == Math.Max(source1.Length, source2.Length);
                case DistanceMethod.LongestCommonSubstringDistance:
                case DistanceMethod.iLongestCommonSubstringDistance:
                    return LongestCommonSubstringDistance(source1, source2, isCaseSensitive) == Math.Min(source1.Length, source2.Length);
                case DistanceMethod.LongestCommonSubsequenceDistance:
                case DistanceMethod.iLongestCommonSubsequenceDistance:
                    return LongestCommonSubsequenceDistance(source1, source2, isCaseSensitive) == Math.Min(source1.Length, source2.Length);
                case DistanceMethod.JaroDistance:
                case DistanceMethod.iJaroDistance:
                    return JaroDistance(source1, source2, isCaseSensitive) == Math.Max(source1.Length, source2.Length);
                case DistanceMethod.NormalizedLevenshteinDistance:
                case DistanceMethod.iNormalizedLevenshteinDistance:
                    return NormalizedLevenshteinDistance(source1, source2, isCaseSensitive) == Math.Max(source1.Length, source2.Length);
                case DistanceMethod.Levenshtein2Distance:
                case DistanceMethod.iLevenshtein2Distance:
                    return Levenshtein2Distance(source1, source2, isCaseSensitive) == Math.Max(source1.Length, source2.Length);
                case DistanceMethod.TanimotoCoefficientDistance:
                case DistanceMethod.iTanimotoCoefficientDistance:
                    return TanimotoCoefficientDistance(source1, source2, isCaseSensitive) == Math.Max(source1.Length, source2.Length);
                case DistanceMethod.PhraseTokenize:
                    return GetPhraseDifference(source1, source2) == Math.Max(GetKeywordList(ref source1).Length, GetKeywordList(ref source2).Length);
                case DistanceMethod.SimplePhraseTokenize:
                    return PhraseSimplifiedDiff(source1, source2) == Math.Max(GetKeywordList(ref source1).Length, GetKeywordList(ref source2).Length);
                case DistanceMethod.DamerauLevenshtein:
                case DistanceMethod.iDamerauLevenshtein:
                default:
                    return DamerauLevenshteinDistance(source1, source2, isCaseSensitive) == Math.Max(source1.Length, source2.Length);
            }
        }
        public static bool IsVerySimilar(string source1, string source2) => IsVerySimilar(source1, source2, DistanceMethod.UseDefaultDistanceMethod);
        public static bool IsVerySimilar(string source1, string source2, DistanceMethod distanceMethod) => IsMatch(source1, source2, 0.9f, distanceMethod); // Is 90% similar
        public static bool IsSimilar(string source1, string source2) => IsSimilar(source1, source2, DistanceMethod.UseDefaultDistanceMethod);
        public static bool IsSimilar(string source1, string source2, DistanceMethod distanceMethod) => IsMatch(source1, source2, 0.75f, distanceMethod); // Is 75% similar
        public static bool IsSomeWhatSimilar(string source1, string source2) => IsSomeWhatSimilar(source1, source2, DistanceMethod.UseDefaultDistanceMethod);
        public static bool IsSomeWhatSimilar(string source1, string source2, DistanceMethod distanceMethod) => IsMatch(source1, source2, 0.5f, distanceMethod); // Is 50% similar
        public static bool IsSlightlySimilar(string source1, string source2) => IsSlightlySimilar(source1, source2, DistanceMethod.UseDefaultDistanceMethod);
        public static bool IsSlightlySimilar(string source1, string source2, DistanceMethod distanceMethod) => IsMatch(source1, source2, 0.3f, distanceMethod); // Is 30% similar
        public static bool IsHardlySimilar(string source1, string source2) => IsHardlySimilar(source1, source2, DistanceMethod.UseDefaultDistanceMethod);
        public static bool IsHardlySimilar(string source1, string source2, DistanceMethod distanceMethod) => IsMatch(source1, source2, 0.1f, distanceMethod); // Is 10% similar
        #endregion Similarity functions
        #region Distance functions
        /// <summary>
        ///     Calculate the difference between 2 strings using the LevenshteinDistance distance algorithm.
        ///     Calculate how str#1 can be equal to str#2 by doing insertions, deletions, or substitutions
        /// </summary>
        /// <param name="source1">First string</param>
        /// <param name="source2">Second string</param>
        /// <returns>
        ///     Returns the number of characters difference.
        ///     If all characters are different, it returns the length of the longest string between source1 and source2 {Math.Max(source1.Length, source2.Length)}
        ///     It returns a zero if strings are exactly the same.
        /// </returns>
        public static int LevenshteinDistance(this string source1, string source2, bool isCaseSensitive = true)
        {
            // If any entry empty return full length of other
            if (source1.Length == 0 || source2.Length == 0)
                return Math.Max(source1.Length, source2.Length);
            FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            int source1Length = source1.Length;
            int source2Length = source2.Length;
            // Initialization of matrix with row size source1Length and columns size source2Length
            int[,] matrix = new int[source1Length + 1, source2Length + 1];
            for (int i = 0; i <= source1Length; i++)
                matrix[i, 0] = i;
            for (int j = 0; j <= source2Length; j++)
                matrix[0, j] = j;
            // Calculate rows and columns distances
            for (int i = 1; i <= source1Length; i++)
            {
                for (int j = 1; j <= source2Length; j++)
                {
                    int cost = (source2[j - 1] == source1[i - 1]) ? 0 : 1;
                    matrix[i, j] = Math.Min(
                        Math.Min(matrix[i - 1, j] + 1, matrix[i, j - 1] + 1),
                        matrix[i - 1, j - 1] + cost);
                }
            }
            return matrix[source1Length, source2Length];
        }
        /// <summary>
        ///     Calculate the difference between 2 strings using the Damerau-LevenshteinDistance distance algorithm
        ///     Calculate how str#1 can be equal to str#2 by doing insertions, deletions, substitutions, or adjacent character swap
        /// </summary>
        /// <param name="source1">First string</param>
        /// <param name="source2">Second string</param>
        /// <returns>
        ///     Returns the number of characters difference.
        ///     If all characters are different, it returns the length of the longest string between source1 and source2 {Math.Max(source1.Length, source2.Length)}
        ///     It returns a zero if strings are exactly the same.
        /// </returns>
        public static int DamerauLevenshteinDistance(string source1, string source2, bool isCaseSensitive = true)
        {
            if (source1 == source2)
                return 0;
            // If any entry empty return full length of other
            if (source1.Length == 0 || source2.Length == 0)
                return Math.Max(source1.Length, source2.Length);
            FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            int source1Length = source1.Length;
            int source2Length = source2.Length;
            int[,] matrix = new int[source1Length + 1, source2Length + 1];
            for (int i = 1; i <= source1Length; i++)
            {
                matrix[i, 0] = i;
                for (int j = 1; j <= source2Length; j++)
                {
                    int cost = source2[j - 1] == source1[i - 1] ? 0 : 1;
                    if (i == 1)
                        matrix[0, j] = j;
                    int[] vals = new int[] {
                            matrix[i - 1, j] + 1,
                            matrix[i, j - 1] + 1,
                            matrix[i - 1, j - 1] + cost
                    };
                    matrix[i, j] = vals.Min();
                    if (i > 1 && j > 1 && source1[i - 1] == source2[j - 2] && source1[i - 2] == source2[j - 1])
                        matrix[i, j] = Math.Min(matrix[i, j], matrix[i - 2, j - 2] + cost);
                }
            }
            return matrix[source1Length, source2Length];
        }
        /// <summary>
        ///     Jaro-Winkler distance between the specified strings.
        ///     Similar to Damerau-LevenshteinDistance, but it has a character edit-once restriction to make equal.
        /// </summary>
        /// <param name="source1">First String</param>
        /// <param name="source2">Second String</param>
        /// <returns>
        ///     Returns the Jaro-Winkler distance between the specified strings. The distance is symmetric and will fall in the range 0 (perfect match) to 1 (no match). 
        /// </returns>
        public static double JaroWinklerPercentage(string source1, string source2, bool isCaseSensitive = true)
        {
            return 1.0f - JaroWinklerDistance(source1, source2, isCaseSensitive);
        }
        /// The Winkler modification will not be applied unless the percent match was at or above the JaroWinklerWeightThreshold percent without the modification. Winkler's paper used a default value of 0.7
        private static readonly double JaroWinklerWeightThreshold = 0.7f;
        /// Size of the prefix to be considered by the Winkler modification. Winkler's paper used a default value of 4
        private static readonly int JaroWinklerNumChars = 4;
        /// <summary>
        /// Jaro-Winkler distance between the specified strings.
        /// </summary>
        /// <param name="source1">First String</param>
        /// <param name="source2">Second String</param>
        /// <returns>
        /// Returns the Jaro-Winkler distance between the specified strings. The distance is symmetric and will fall in the range 0 (no match) to 1 (perfect match). 
        /// </returns>
        public static double JaroWinklerDistance(string source1, string source2, bool isCaseSensitive = true)
        {
            int source1Length = source1.Length;
            int source2Length = source2.Length;
            if (source1Length == 0)
                return source2Length == 0 ? 1.0f : 0.0f;
            FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            int lSearchRange = Math.Max(0, (Math.Max(source1Length, source2Length) / 2) - 1);
            bool[] lMatched1 = new bool[source1Length];
            bool[] lMatched2 = new bool[source2Length];
            int lNumCommon = 0;
            for (int i = 0; i < source1Length; ++i)
            {
                int lStart = Math.Max(0, i - lSearchRange);
                int lEnd = Math.Min(i + lSearchRange + 1, source2Length);
                for (int j = lStart; j < lEnd; ++j)
                {
                    if (lMatched2[j]) 
                        continue;
                    if (source1[i] != source2[j])
                        continue;
                    lMatched1[i] = true;
                    lMatched2[j] = true;
                    ++lNumCommon;
                    break;
                }
            }
            if (lNumCommon == 0) 
                return 0.0f;
            int lNumHalfTransposed = 0;
            int k = 0;
            for (int i = 0; i < source1Length; ++i)
            {
                if (!lMatched1[i]) 
                    continue;
                while (!lMatched2[k]) 
                    ++k;
                if (source1[i] != source2[k])
                    ++lNumHalfTransposed;
                ++k;
            }
            int lNumTransposed = lNumHalfTransposed / 2;
            double lNumCommonD = lNumCommon;
            double lWeight = ((lNumCommonD / source1Length) + (lNumCommonD / source2Length) + ((lNumCommon - lNumTransposed) / lNumCommonD)) / 3.0f;
            if (lWeight <= JaroWinklerWeightThreshold) 
                return lWeight;
            int lMax = Math.Min(JaroWinklerNumChars, Math.Min(source1.Length, source2.Length));
            int lPos = 0;
            while (lPos < lMax && source1[lPos] == source2[lPos])
                ++lPos;
            return lPos == 0 ? lWeight : lWeight + (0.1f * lPos * (1.0f - lWeight));
        }
        public static string HasCharInSameOrder(this string word) => HasCharInSameOrder(word, "%"); // Needed for CPP code access
        public static string HasCharInSameOrder(this string word, string sep) // SQL function extension
        {
            string returnWord = "";
            foreach (char c in word)
                returnWord += $"{c}{sep}";
            return $"{sep}{returnWord}";
        }
        public static string HasWordsInSameOrder(string words, string fieldToCompare) => HasWordsInSameOrder(words, fieldToCompare, false); // Needed for CPP code access
        public static string HasWordsInSameOrder(string words, string fieldToCompare, bool doNearWordSearch, int minimumWordLenForWordInWordMatch = 1, bool simplify = false) // SQL function extension
        {
            string[] keywords = KeywordList(words, simplify);
            string returnStr = "";
            for (int i = 0; i < keywords.Length; ++i)
            {
                if (keywords[i].Length >= minimumWordLenForWordInWordMatch)
                {
                    string nearWordSearch = doNearWordSearch ? $" OR {fieldToCompare} LIKE '%{Fuzzy.HasCharInSameOrder(keywords[i])}%' " : "";
                    returnStr += $"({fieldToCompare} LIKE '%{keywords[i]}%'  {nearWordSearch}) ";
                }
                else
                    returnStr += $"(' '||{fieldToCompare}||' ' LIKE '% {keywords[i]} %') ";
                if (i + 1 < keywords.Length)
                    returnStr += " + ";
            }
            return returnStr;
        }
        public static double OverlapCoefficientDistance(this string source1, string source2, bool isCaseSensitive = true)
        {
            FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            return 1.0f - (double)source1.OverlapCoefficient(source2);
        }
        public static double OverlapCoefficient(this string source1, string source2) => Convert.ToDouble(source1.Intersect(source2).Count()) / Convert.ToDouble(Math.Min(source1.Length, source2.Length));
        public static double JaccardDistance(this string source1, string source2, bool isCaseSensitive = true)
        {
            FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            return 1.0f - (double)source1.JaccardIndex(source2);
        }

        public static double JaccardIndex(this string source1, string source2) => Convert.ToDouble(source1.Intersect(source2).Count()) / Convert.ToDouble(source1.Union(source2).Count());
        // ToDo: Add the following distance functions to the enum list of DistanceMethods
        public static double SorensenDiceDistance(this string source1, string source2, bool isCaseSensitive = true)
        {
            FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            return 1.0f - (double)source1.SorensenDiceIndex(source2);
        }
        public static double SorensenDiceIndex(this string source1, string source2) => 2 * Convert.ToDouble(source1.Intersect(source2).Count()) / Convert.ToDouble(source1.Length + source2.Length);
        public static double RatcliffObershelpSimilarityDistance(this string source1, string source2, bool isCaseSensitive = true)
        {
            FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            return 1.0f - (double)source1.RatcliffObershelpSimilarity(source2);
        }
        public static double RatcliffObershelpSimilarity(this string source1, string source2) => 2 * Convert.ToDouble(source1.Intersect(source2).Count()) / Convert.ToDouble(source1.Length + source2.Length);
        public static double HammingDistance(this string source1, string source2, bool isCaseSensitive = true)
        {
            if (source1.Length != source2.Length) // Can only use HammingDiceDistance on string of equal length
                return -1.0f;
            FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            return 1.0f - ((double)source1.Hamming(source2) / (double)source2.Length);
        }
        public static int Hamming(this string source1, string source2)
        {
            int distance = 0;
            for (int i = 0; i < source1.Length; i++)
                if (!source1[i].Equals(source2[i]))
                    distance++;
            return distance;
        }
        public static double LongestCommonSubstringDistance(this string source1, string source2, bool isCaseSensitive = true)
        {
            FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            return 1.0f - ((double)source1.GetLongestCommonSubstring(source2).Length / (double)Math.Min(source1.Length, source2.Length));
        }
        public static string GetLongestCommonSubstring(this string source1, string source2)
        {
            if (String.IsNullOrEmpty(source1) || String.IsNullOrEmpty(source2)) 
                return null;
            int[,] L = new int[source1.Length, source2.Length];
            int maximumLength = 0;
            int lastSubsBegin = 0;
            StringBuilder stringBuilder = new StringBuilder();
            for (int i = 0; i < source1.Length; i++)
            {
                for (int j = 0; j < source2.Length; j++)
                {
                    if (source1[i] != source2[j])
                        L[i, j] = 0;
                    else
                    {
                        L[i, j] = (i == 0) || (j == 0) ? 1 : 1 + L[i - 1, j - 1];
                        if (L[i, j] > maximumLength)
                        {
                            maximumLength = L[i, j];
                            int thisSubsBegin = i - L[i, j] + 1;
                            if (lastSubsBegin == thisSubsBegin)//if the current LCS is the same as the last time this block ran
                                stringBuilder.Append(source1[i]);
                            else //this block resets the string builder if a different LCS is found
                            {
                                lastSubsBegin = thisSubsBegin;
                                stringBuilder.Length = 0; //clear it
                                stringBuilder.Append(source1.Substring(lastSubsBegin, i + 1 - lastSubsBegin));
                            }
                        }
                    }
                }
            }
            return stringBuilder.ToString();
        }
        public static double LongestCommonSubsequenceDistance(this string source1, string source2, bool isCaseSensitive = true)
        {
            FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            return 1.0f - ((double)source1.LongestCommonSubsequence(source2).Length / (double)Math.Min(source1.Length, source2.Length));
        }
        public static string LongestCommonSubsequence(this string source1, string source2)
        {
            int[,] C = LongestCommonSubsequenceLengthTable(source1, source2);
            return LongestCommonSubsequenceBacktrack(C, source1, source2, source1.Length, source2.Length);
        }
        private static int[,] LongestCommonSubsequenceLengthTable(string source1, string source2)
        {
            int[,] C = new int[source1.Length + 1, source2.Length + 1];
            for (int i = 0; i < source1.Length + 1; i++)
                C[i, 0] = 0;
            for (int j = 0; j < source2.Length + 1; j++)
                C[0, j] = 0;
            for (int i = 1; i < source1.Length + 1; i++)
                for (int j = 1; j < source2.Length + 1; j++)
                    C[i, j] = source1[i - 1].Equals(source2[j - 1]) ? C[i - 1, j - 1] + 1 : Math.Max(C[i, j - 1], C[i - 1, j]);
            return C;
        }
        private static string LongestCommonSubsequenceBacktrack(int[,] C, string source1, string source2, int i, int j)
        {
            return i == 0 || j == 0
                ? ""
                : source1[i - 1].Equals(source2[j - 1])
                ? LongestCommonSubsequenceBacktrack(C, source1, source2, i - 1, j - 1) + source1[i - 1]
                : C[i, j - 1] > C[i - 1, j]
                    ? LongestCommonSubsequenceBacktrack(C, source1, source2, i, j - 1)
                    : LongestCommonSubsequenceBacktrack(C, source1, source2, i - 1, j);
        }
        public static double JaroDistance(this string source1, string source2, bool isCaseSensitive = true)
        {
            FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            int m = source1.Intersect(source2).Count();
            if (m == 0) 
                return 0;
            string sourceTargetIntersectAsString = "";
            string targetSourceIntersectAsString = "";
            IEnumerable<char> sourceIntersectTarget = source1.Intersect(source2);
            IEnumerable<char> targetIntersectSource = source2.Intersect(source1);
            foreach (char character in sourceIntersectTarget) 
                sourceTargetIntersectAsString += character;
            foreach (char character in targetIntersectSource)  
                targetSourceIntersectAsString += character; 
            double t = sourceTargetIntersectAsString.LevenshteinDistance(targetSourceIntersectAsString, isCaseSensitive) / 2;
            return (double)((m / source1.Length) + (m / source2.Length) + ((m - t) / m)) / 3;
        }
        public static double NormalizedLevenshteinDistance(this string source1, string source2, bool isCaseSensitive = true)
        {
            FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            double distance = Convert.ToDouble(Levenshtein2.NormalizedLevenshteinDistance(source1, source2)) / Convert.ToDouble(Math.Max(source1.Length, source2.Length) - Levenshtein2.LevenshteinDistanceLowerBounds(source1, source2));
            return 1.0f - (double)distance;
        }
        public static double Levenshtein2Distance(this string source1, string source2, bool isCaseSensitive = true)
        {
            FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            //double distance = Convert.ToDouble(Levenshtein2.LevenshteinDistance2(source1, source2)) / Convert.ToDouble(Levenshtein2.LevenshteinDistanceUpperBounds(source1, source2)); // LevenshteinDistanceUpperBounds Fails!!!!
            double distance = Convert.ToDouble(Levenshtein2.LevenshteinDistance2(source1, source2)) / Convert.ToDouble(Math.Max(source1.Length, source2.Length));
            return 1.0f - (double)distance;
        }
        public static double TanimotoCoefficientDistance(this string source1, string source2, bool isCaseSensitive = true)
        {
            FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            return 1.0f - source1.TanimotoCoefficient(source2);
        }
        public static double TanimotoCoefficient(this string source1, string source2)
        {
            double Na = source1.Length;
            double Nb = source2.Length;
            double Nc = source1.Intersect(source2).Count();
            return Nc / (Na + Nb - Nc);
        }
        // Function to find the minimum number of operations to convert source1 to source2
        public static int EditDistance(string source1, string source2, bool isCaseSensitive = true)
        {
            FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            int m = source1.Length;
            int n = source2.Length;
            // Stores dp[i-1][j-1]
            int prev;
            int[] curr = new int[n + 1];
            for (int j = 0; j <= n; j++)
                curr[j] = j;
            for (int i = 1; i <= m; i++)
            {
                prev = curr[0];
                curr[0] = i;
                for (int j = 1; j <= n; j++)
                {
                    int temp = curr[j];
                    curr[j] = source1[i - 1] == source2[j - 1] ? prev : 1 + Math.Min(Math.Min(curr[j - 1], prev), curr[j]);
                    prev = temp;
                }
            }
            return curr[n];
        }
        public static double BlockDistance(this string source1, string source2, bool isCaseSensitive = true)
        {
            FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            BlockDistance sim2 = new BlockDistance();
            return sim2.GetSimilarity(source1, source2);
        }
        public static double NeedlemanWunsch(this string source1, string source2, bool isCaseSensitive = true) => NeedlemanWunschClass.Percentage(source1, source2, isCaseSensitive);
        public static double JaccardIndex(this string source1, string source2, bool isCaseSensitive = true) => JaccardDistance(source1, source2, isCaseSensitive);
        public static double ChapmanLengthDeviation(this string source1, string source2, bool isCaseSensitive = true)
        {
            FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            ChapmanLengthDeviation sim3 = new ChapmanLengthDeviation();
            return sim3.GetSimilarity(source1, source2);
        }
        public static double ChapmanMeanLength(this string source1, string source2, bool isCaseSensitive = true)
        {
            FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            ChapmanMeanLength sim0 = new ChapmanMeanLength();
            return sim0.GetSimilarity(source1, source2);
        }
        public static double EuclideanDistance(this string source1, string source2, bool isCaseSensitive = true)
        {
            FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            EuclideanDistance sim4 = new EuclideanDistance();
            return sim4.GetSimilarity(source1, source2);
        }
        public static double MatchingCoefficient(this string source1, string source2, bool isCaseSensitive = true)
        {
            FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            MatchingCoefficient sim5 = new MatchingCoefficient();
            return sim5.GetSimilarity(source1, source2);
        }
        public static double MongeElkan(this string source1, string source2, bool isCaseSensitive = true)
        {
            FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            MongeElkan sim6 = new MongeElkan();
            return sim6.GetSimilarity(source1, source2);
        }
        public static double QGramsDistance(this string source1, string source2, bool isCaseSensitive = true)
        {
            FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            QGramsDistance sim7 = new QGramsDistance();
            return sim7.GetSimilarity(source1, source2);
        }
        public static double SmithWaterman(this string source1, string source2, bool isCaseSensitive = true)
        {
            FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            SmithWaterman sim8 = new SmithWaterman();
            return sim8.GetSimilarity(source1, source2);
        }
        public static double SmithWatermanGotoh(this string source1, string source2, bool isCaseSensitive = true)
        {
            FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            SmithWatermanGotoh sim9 = new SmithWatermanGotoh();
            return sim9.GetSimilarity(source1, source2);
        }
        public static double SmithWatermanGotohWindowedAffine(this string source1, string source2, bool isCaseSensitive = true)
        {
            FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            SmithWatermanGotohWindowedAffine sim1 = new SmithWatermanGotohWindowedAffine();
            return sim1.GetSimilarity(source1, source2);
        }
        public static double DiceSimilarity(this string source1, string source2, bool isCaseSensitive = true)
        {
            FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            DiceSimilarity sim1 = new DiceSimilarity();
            return sim1.GetSimilarity(source1, source2);
        }
        public static double CosineSimilarity(this string source1, string source2, bool isCaseSensitive = true) => CosineSimilarityClass.Percentage(source1, source2, isCaseSensitive);
        public static double JaccardSimilarity(this string source1, string source2, bool isCaseSensitive = true) => JaccardSimilarityClass.Percentage(source1, source2, isCaseSensitive);
        public static double LongestCommonSequence(this string source1, string source2, bool isCaseSensitive = true) => LongestCommonSequenceClass.Percentage(source1, source2, isCaseSensitive);
        public static double PhraseTokenize(this string source1, string source2, bool isCaseSensitive = true)
        {
            FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            return GetPhraseDifference(source1, source2);
        }
        public static double SimplePhraseTokenize(this string source1, string source2, bool isCaseSensitive = true)
        {
            FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            return PhraseSimplifiedDiff(source1, source2);
        }
        // ToDo: Implement the following functions
        public static string NormalizeFirstLastName(string name)
        {
            name = Regex.Replace(name, "[\\s][A-Za-z]\\.", "");
            name = Regex.Replace(name, "[\\s][A-Za-z]$", "");
            name = Regex.Replace(name, "[\\s][0-9][A-Za-z]{2}", "");
            name = Regex.Replace(name, "[\\s][JSjs][Rr]\\.?", "");
            name = Regex.Replace(name, "[\\s][Ii]+$", "");
            name = Regex.Replace(name, "[\\s][Ii]+\\s", "");
            name = Regex.Replace(name, "([A-Za-z]+)\\s*\\,\\s*([A-Za-z]+.*)", "$2 $1");
            name = Regex.Replace(name, "[^A-Za-z\\s]+", "");
            name = name.Replace("  ", " ");
            return name;
        }
        public static bool SameFirstLastName(string source1, string source2, bool isCaseSensitive = false)
        {
            source1 = NormalizeFirstLastName(source1);
            source2 = NormalizeFirstLastName(source2);
            FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            return source1 == source2;
        }
        public static bool SamePhone(string source1, string source2, bool isCaseSensitive = false)
        {// Remove non-numeric characters, and remove first number if it starts with a 1
            FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            return false;
        }
        public static bool SameSocial(string source1, string source2, bool isCaseSensitive = false)
        {// Remove non-numeric characters
            FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            return false;
        }
        public static bool SameZip(string source1, string source2, bool isCaseSensitive = false)
        {
            FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            return false;
        }
        public static bool SameAddress(string source1, string source2, bool isCaseSensitive = false)
        {
            FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            return false;
        }
        public static bool SameDate(string source1, string source2, bool isCaseSensitive = false)
        {
            FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            return false;
        }
        public static bool SameFileName(string source1, string source2, bool isCaseSensitive = false)
        {
            FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            return false;
        }
        public static bool SameNumber(string source1, string source2, bool isCaseSensitive = false)
        {// Convert word numbers (five=5) to numbers, convert roman numbers, and remove non-numeric characters
            FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            return false;
        }
        #endregion Distance functions
        #region Phonetic (sound) functions
        public static bool Caverphone2(this string source1, string source2,
            DistanceMethod distanceMethod,
            bool isVerySimilar = true)
        {
            string s1 = Caverphone.BuildKey(source1);
            string s2 = Caverphone.BuildKey(source2);
            return Compare(s1, s2, distanceMethod, isVerySimilar);
        }
        public static bool Caverphone2(this string source1, string source2) => Caverphone2(source1, source2, DistanceMethod.SameSound_StrCmp);
        public static string Caverphone2(string source1)
        {
            return Caverphone.BuildKey(source1);
        }
        public static bool Soundex2(this string source1, string source2,
            DistanceMethod distanceMethod,
            bool isVerySimilar)
        {
            string s1 = Soundex.Generate(source1);
            string s2 = Soundex.Generate(source2);
            return Compare(s1, s2, distanceMethod, isVerySimilar);
        }
        public static bool Soundex2(this string source1, string source2) => Soundex2(source1, source2, DistanceMethod.SameSound_StrCmp, true);
        public static string Soundex2(string source1)
        {
            return Soundex.Generate(source1);
        }
        public static bool EnPhoneticDistance(this string source1, string source2, bool isVerySimilar = true)
        {
            return FuzzyPhoneticMatching.EnPhoneticDistance_Supported ? FuzzyPhoneticMatching.EnPhoneticDistance(source1, source2, isVerySimilar) : Soundex2(source1, source2, DistanceMethod.SameSound_StrCmp, isVerySimilar);
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
            DistanceMethod distanceMethod = DistanceMethod.SameSound_StrCmp,
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
                case SameSoundMethod.Soundex2:
                default:
                    return Soundex2(source1, source2, distanceMethod, isVerySimilar);
            }
        }
        public static bool Compare(string source1, string source2, DistanceMethod CompareMethod, bool isVerySimilar)
        {
            switch (CompareMethod)
            {
                case DistanceMethod.SameSound_StrCmp:
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
        /// <summary>
        ///     Calculate the number of key words not in each others phrase (All phrase comparisons functions in this class are case INSENSITIVE)
        /// </summary>
        /// <param name="source1">First string</param>
        /// <param name="source2">Second string</param>
        /// <param name="simplify">Set to true in order to remove (A,The), numbers, abbreviated letters, non-alpha</param>
        /// <param name="insertSpacesBetweenCapitalLetters">True to insert spaces between capital letters. IE "MakeThisNormal" converts to "Make This Normal"</param>
        /// <returns>
        ///     Returns the number of key words not in each others phrase
        /// </returns>
        public static int GetPhraseDifference(string source1, string source2, bool simplify = false, bool insertSpacesBetweenCapitalLetters = true)
        {
            string[] list1 = GetKeywordList(ref source1, simplify, insertSpacesBetweenCapitalLetters);
            string[] list2 = GetKeywordList(ref source2, simplify, insertSpacesBetweenCapitalLetters);
            int misMatchCount = 0;
            foreach (string s in list1)
                if (!list2.Contains(s))
                    ++misMatchCount;
            foreach (string s in list2)
                if (!list1.Contains(s))
                    ++misMatchCount;
            return misMatchCount;
        }
        public static int PhraseSimplifiedDiff(string source1, string source2) => GetPhraseDifference(source1, source2, true);
        public static double PhraseHowSimilar(string source1, string source2)
        {
            string[] list1 = GetKeywordList(ref source1, false, true);
            string[] list2 = GetKeywordList(ref source2, false, true);
            double sourceLength = Math.Max(list1.Length, list2.Length);
            double diff = GetPhraseDifference(source1, source2,false, true);
            return diff == 0 ? 1.0f : (sourceLength - diff) / sourceLength;
        }
        public static bool IsPhraseSimilar(string source1, string source2, double desiredSimilarity) => PhraseHowSimilar(source1, source2) >= desiredSimilarity;
        public static bool PhraseVerySimilar(string source1, string source2) => IsPhraseSimilar(source1, source2, 0.9f); // Is 90% similar
        public static bool PhraseSimilar(string source1, string source2) => IsPhraseSimilar(source1, source2, 0.75f); // Is 75% similar
        public static bool PhraseSomeWhatSimilar(string source1, string source2) => IsPhraseSimilar(source1, source2, 0.5f); // Is 50% similar
        public static bool PhraseSlightlySimilar(string source1, string source2) => IsPhraseSimilar(source1, source2, 0.3f); // Is 30% similar
        public static bool PhraseHardlySimilar(string source1, string source2) => IsPhraseSimilar(source1, source2, 0.1f); // Is 10% similar
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
        #region Fuzzy classes
        public static class CosineSimilarityClass
        {
            /// <summary>
            /// Calculates the similarity percentage between two strings via Cosine Similarity. 
            /// </summary>
            /// <param name="source1">The first string.</param>
            /// <param name="source2">The second string.</param>
            /// <returns>The similarity percentage between the two strings. It's a number between 0 and 1 that represents how similar two strings are. The closer to 1, the more similar they are.</returns>
            public static double Percentage(string source1, string source2, bool isCaseSensitive = true) => (double)CalculateSimilarity(source1, source2, isCaseSensitive);
            public static double CalculateSimilarity(string source1, string source2, bool isCaseSensitive = true)
            {
                FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
                if (source1 == source2)
                    return 1;
                string[] words1 = source1.Split();
                string[] words2 = source2.Split();
                Dictionary<string, int> vector1 = GetWordVector(words1);
                Dictionary<string, int> vector2 = GetWordVector(words2);
                IEnumerable<string> intersection = new HashSet<string>(vector1.Keys).Intersect(vector2.Keys);
                double dotProduct = 0;
                double magnitude1 = 0;
                double magnitude2 = 0;
                foreach (string word in intersection)
                    dotProduct += vector1[word] * vector2[word];
                foreach (int value in vector1.Values)
                    magnitude1 += value * value;
                foreach (int value in vector2.Values)
                    magnitude2 += value * value;
                magnitude1 = Math.Sqrt(magnitude1);
                magnitude2 = Math.Sqrt(magnitude2);
                return (magnitude1 == 0 || magnitude2 == 0) ? 0 : dotProduct / (magnitude1 * magnitude2);
            }
            private static Dictionary<string, int> GetWordVector(IReadOnlyCollection<string> words)
            {
                Dictionary<string, int> wordVector = new Dictionary<string, int>(words.Count, StringComparer.OrdinalIgnoreCase);
                foreach (string word in words)
                {
                    string key = word.ToLower();
                    wordVector[key] = wordVector.TryGetValue(key, out int count) ? count + 1 : 1;
                }
                return wordVector;
            }
        }
        public static class LongestCommonSequenceClass   // A class for comparing strings via the Longest Common Sequence algorithm
        {
            /// <summary>
            /// Calculates the similarity between two strings as a percentage.
            /// </summary>
            /// <param name="source1">The first string.</param>
            /// <param name="source2">The second string.</param>
            /// <returns>The similarity between the two strings as a percentage.</returns>
            public static double Percentage(string source1, string source2, bool isCaseSensitive = true) => (double)CalculateSimilarity(source1, source2, isCaseSensitive);
            public static int[] CalculateSimilarityArray(string source1, string source2)
            {
                int m = source1.Length;
                int n = source2.Length;
                int[] lcsRow = new int[n + 1];
                for (int i = 0; i <= m; i++)
                {
                    int prev = 0;
                    for (int j = 0; j <= n; j++)
                    {
                        int current = lcsRow[j];
                        if (i > 0 && j > 0)
                            lcsRow[j] = source1[i - 1] == source2[j - 1] ? prev + 1 : Math.Max(lcsRow[j], lcsRow[j - 1]);
                        prev = current;
                    }
                }
                return lcsRow;
            }
            public static int Difference(string source1, string source2, bool isCaseSensitive)
            {
                FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
                if (source1 == source2)
                    return Math.Max(source1.Length, source2.Length);
                int[] lcsRow = CalculateSimilarityArray(source1, source2);
                int lcsLength = lcsRow[source2.Length];
                return lcsLength;
            }
            public static double CalculateSimilarity(string source1, string source2, bool isCaseSensitive) => (double)Difference(source1, source2, isCaseSensitive) / Math.Max(source1.Length, source2.Length);
        }
    }
    /// <summary>
    /// A class for comparing strings via the Jaccard similarity algorithm
    /// </summary>
    public static class JaccardSimilarityClass
    {
        /// <summary>
        /// Calculates the similarity percentage between two strings via Jaccard Similarity
        /// </summary>
        /// <param name="source1">The first string.</param>
        /// <param name="source2">The second string.</param>
        /// <returns>The similarity percentage between the two strings.</returns>
        public static double Percentage(string source1, string source2, bool isCaseSensitive = true) => (double)CalculateSimilarity(source1, source2, isCaseSensitive);
        public static double CalculateSimilarity(string source1, string source2, bool isCaseSensitive = true)
        {
            if (!isCaseSensitive)
            {
                source1 = source1.ToLower();
                source2 = source2.ToLower();
            }
            if (source1 == source2)
                return 1.0f;
            // Split strings into sets of words and create HashSets
            HashSet<string> hashSet1 = new HashSet<string>(source1.Split(' '));
            HashSet<string> hashSet2 = new HashSet<string>(source2.Split(' '));
            double originalCount1 = hashSet1.Count;
            hashSet1.IntersectWith(hashSet2);
            double intersectionCount = hashSet1.Count;
            double unionCount = originalCount1 + hashSet2.Count - intersectionCount;
            return (double)intersectionCount / unionCount;
        }
    }
    /// <summary>
    /// A class for comparing strings via the Needleman-Wunsch algorithm
    /// </summary>
    public static class NeedlemanWunschClass
    {
        /// <summary>
        /// Calculates the similarity percentage between two strings using the Needleman-Wunsch algorithm.
        /// </summary>
        /// <param name="source1">The first string.</param>
        /// <param name="source2">The second string.</param>
        /// <returns>The similarity percentage between the two strings.</returns>
        public static double Percentage(string source1, string source2, bool isCaseSensitive = true)
        {
            if (!isCaseSensitive)
            {
                source1 = source1.ToLower();
                source2 = source2.ToLower();
            }
            if (source1 == source2)
                return 1.0f;
            int similarityScore = CalculateSimilarity(source1, source2);
            double maxPossibleScore = Math.Max(source1.Length, source2.Length);
            double similarityPercentage = 1 - (similarityScore / maxPossibleScore);
            return similarityPercentage;
        }
        public static int CalculateSimilarity(string source1, string source2)
        {
            int[,] matrix = new int[source1.Length + 1, source2.Length + 1];
            for (int i = 0; i <= source1.Length; i++)
                matrix[i, 0] = i;
            for (var j = 1; j <= source2.Length; j++)
                matrix[0, j] = j;
            // Fill in the matrix
            for (int i = 1; i <= source1.Length; i++)
            {
                for (int j = 1; j <= source2.Length; j++)
                {
                    int cost = source1[i - 1] == source2[j - 1] ? 0 : 1;
                    int deletion = matrix[i - 1, j] + 1;
                    int insertion = matrix[i, j - 1] + 1;
                    int substitution = matrix[i - 1, j - 1] + cost;
                    matrix[i, j] = Math.Min(Math.Min(deletion, insertion), substitution);
                }
            }
            // The similarity score is the value in the bottom-right cell of the matrix
            return matrix[source1.Length, source2.Length];
        }
    }
    public static class Levenshtein2
    {
        const int MaxRecursion = 16; 
        /// <summary>
        /// Calculate the minimum number of single-character edits needed to change the source1 into the source2,
        /// allowing insertions, deletions, and substitutions.
        /// <br/><br/>
        /// Time complexity: at least O(n^2), where n is the length of each string
        /// Accordingly, this algorithm is most efficient when at least one of the strings is very short
        /// </summary>
        /// <param name="source1"></param>
        /// <param name="source2"></param>
        /// <returns>The number of edits required to transform the source1 into the source2. This is at most the length of the longest string, and at least the difference in length between the two strings</returns>
        public static int LevenshteinDistance2(this string source1, string source2)
        {
            int recursion = 0;
            return LevenshteinDistance2_sub(source1, source2, ref recursion);
        }
        public static int LevenshteinDistance2_sub(this string source1, string source2, ref int recursion)
        {
            if (source1.Length == 0 || source2.Length == 0)
                return Math.Max(source1.Length, source2.Length);
            int distance = source1[source1.Length - 1] == source2[source2.Length - 1] ? 0 : 1;
            if (++recursion > MaxRecursion)
                return distance;
            string sourceInitial = source1.Substring(0, source1.Length - 1);
            string targetInitial = source2.Substring(startIndex: 0, source2.Length - 1);
            return Math.Min(Math.Min(LevenshteinDistance2_sub(sourceInitial, source2, ref recursion) + 1,
                                     LevenshteinDistance2_sub(source1, targetInitial, ref recursion)) + 1,
                                     LevenshteinDistance2_sub(sourceInitial, targetInitial, ref recursion) + distance);
        }
        /// <returns>The Levenshtein distance, normalized so that the lower bound is always zero, rather than the difference in length between the two strings</returns>
        public static int NormalizedLevenshteinDistance(this string source1, string source2) => source1.LevenshteinDistance2(source2) - source1.LevenshteinDistanceLowerBounds(source2);
        ///  <returns>The upper bounds is either the length of the longer string, or the Hamming distance.</returns>
        public static int LevenshteinDistanceUpperBounds(this string source1, string source2) => source1.Length == source2.Length ? Fuzzy.Hamming(source1, source2) : Math.Max(source1.Length, source2.Length);
        ///  <returns>The lower bounds is the difference in length between the two strings</returns>
        public static int LevenshteinDistanceLowerBounds(this string source1, string source2) => Math.Abs(source1.Length - source2.Length);
    }
    /// <summary>
    /// Phonetic algorithm created by David Hood
    /// For more information see: <a href="http://en.wikipedia.org/wiki/Caverphone">http://en.wikipedia.org/wiki/Caverphone</a>
    /// </summary>
    public class Caverphone
    {
        public static readonly string[] EmptyKeys = new string[0];
        static readonly Regex Alpha = new Regex("[^a-z]", RegexOptions.Compiled);
        static readonly Regex LowerVowel = new Regex("[aeiou]", RegexOptions.Compiled);

        private static string TranslateRemaining(string key)
        {
            int nameLength = key.Length;
            //Replace
            //cq with 2q
            key = key.Replace("cq", "2q");
            //ci with si
            key = key.Replace("ci", "si");
            //ce with se
            key = key.Replace("ce", "se");
            //cy with sy
            key = key.Replace("cy", "sy");
            //tch with 2ch
            key = key.Replace("tch", "2ch");
            //c with k
            key = key.Replace("c", "k");
            //q with k
            key = key.Replace("q", "k");
            //x with k
            key = key.Replace("x", "k");
            //v with f
            key = key.Replace("v", "f");
            //dg with 2g
            key = key.Replace("dg", "2g");
            //tio with sio
            key = key.Replace("tio", "sio");
            //tia with sia
            key = key.Replace("tia", "sia");
            //d with t
            key = key.Replace("d", "t");
            //ph with fh
            key = key.Replace("ph", "fh");
            //b with p
            key = key.Replace("b", "p");
            //sh with s2
            key = key.Replace("sh", "s2");
            //z with s
            key = key.Replace("z", "s");
            //any initial vowel with an A
            if (LowerVowel.IsMatch(key.Substring(0, 1)))
            {
                key = "A" + key.Substring(1 < nameLength ? 1 : nameLength);
            }
            //all other vowels with a 3
            key = LowerVowel.Replace(key, "3");
            //the next 2 were moved up for the revised caverphone in 2004
            //j with y
            key = key.Replace("j", "y");
            //revised in 2004 to only affect the INITIAL y3.
            //y3 with Y3
            //key = key.Replace("y3", "Y3");
            if (key.Substring(0, 2) == "y3")
            {
                key = "Y3" + key.Substring(2 < nameLength ? 2 : nameLength);
            }
            //this was new in revised 2004
            //any initial y with an A
            if (key.Substring(0, 1) == "y")
            {
                key = "A" + key.Substring(1 < nameLength ? 1 : nameLength);
            }

            //the next one was revised in revised 2004 caverphone to y->3
            ////y with 2
            key = key.Replace("y", "3");

            //3gh3 with 3kh3
            key = key.Replace("3gh3", "3kh3");
            //gh with 22
            key = key.Replace("gh", "22");
            //g with k
            key = key.Replace("g", "k");
            //groups of the letter s with a S
            key = Regex.Replace(key, "[s]{1,}", "S");
            //groups of the letter t with a T
            key = Regex.Replace(key, "[t]{1,}", "T");
            //groups of the letter p with a P
            key = Regex.Replace(key, "[p]{1,}", "P");
            //groups of the letter k with a K
            key = Regex.Replace(key, "[k]{1,}", "K");
            //groups of the letter f with a F
            key = Regex.Replace(key, "[f]{1,}", "F");
            //groups of the letter m with a M
            key = Regex.Replace(key, "[m]{1,}", "M");
            //groups of the letter n with a N
            key = Regex.Replace(key, "[n]{1,}", "N");
            //w3 with W3
            key = key.Replace("w3", "W3");
            //wh3 with Wh3
            key = key.Replace("wh3", "Wh3");
            //next 2 were removed in the revised caverphone in 2004
            ////wy with Wy
            //key = key.Replace("wy", "Wy");
            ////why with Why
            //key = key.Replace("why", "Why");

            //this was new in revised 2004
            //if the name ends in w replace the final w with 3
            if (key.EndsWith("w", System.StringComparison.Ordinal))
            {
                key = key.Substring(0, key.Length - 1) + "3";
            }

            //w with 2
            key = key.Replace("w", "2");
            //any initial h with an A
            if (key.Substring(0, 1) == "h")
            {
                key = "A" + key.Substring(1 < nameLength ? 1 : nameLength);
            }
            //all other occurrences of h with a 2
            key = key.Replace("h", "2");
            //r3 with R3
            key = key.Replace("r3", "R3");

            //this was new in revised 2004
            //if the name ends in r replace the replace final r with 3
            if (key.EndsWith("r", System.StringComparison.Ordinal))
            {
                key = key.Substring(0, key.Length - 1) + "3";
            }

            //The next one was removed in revised 2004 caverphone
            ////ry with Ry
            //key = key.Replace("ry", "Ry");

            //r with 2
            key = key.Replace("r", "2");
            //l3 with L3
            key = key.Replace("l3", "L3");

            //this was new in revised 2004
            //if the name ends in r replace the replace final r with 3
            if (key.EndsWith("l", System.StringComparison.Ordinal))
            {
                key = key.Substring(0, key.Length - 1) + "3";
            }

            //The next one was removed in revised 2004 caverphone
            ////ly with Ly
            //key = key.Replace("ly", "Ly");

            //l with 2
            key = key.Replace("l", "2");

            //remove all
            //2s
            key = key.Replace("2", string.Empty);

            //this was new in revised 2004
            //if the name ends in 3 replace the replace final 3 with A
            if (key.EndsWith("3", System.StringComparison.Ordinal))
            {
                key = key.Substring(0, key.Length - 1) + "A";
            }

            //remove all
            //3s
            key = key.Replace("3", string.Empty);
            return key;
        }

        private static string TranslateStartsWith(string name)
        {
            //If the name starts with
            //cough make it cou2f
            //rough make it rou2f
            //tough make it tou2f
            //enough make it enou2f
            //If the name starts with trough make it trou2f
            //gn make it 2n
            //mb make it m2
            int nameLength = name.Length;

            if (name.StartsWith("cough", System.StringComparison.Ordinal))
            {
                name = "cou2f" + name.Substring(5 < nameLength ? 5 : nameLength);
            }
            else if (name.StartsWith("rough", System.StringComparison.Ordinal))
            {
                name = "rou2f" + name.Substring(5 < nameLength ? 5 : nameLength);
            }
            else if (name.StartsWith("tough", System.StringComparison.Ordinal))
            {
                name = "tou2f" + name.Substring(5 < nameLength ? 5 : nameLength);
            }
            else if (name.StartsWith("trough", System.StringComparison.Ordinal)) //this was new in revised 2004
            {
                name = "trou2f" + name.Substring(6 < nameLength ? 6 : nameLength);
            }
            else if (name.StartsWith("enough", System.StringComparison.Ordinal))
            {
                name = "enou2f" + name.Substring(6 < nameLength ? 6 : nameLength);
            }
            else if (name.StartsWith("gn", System.StringComparison.Ordinal))
            {
                name = "2n" + name.Substring(2 < nameLength ? 2 : nameLength);
            }
            else if (name.StartsWith("mb", System.StringComparison.Ordinal))
            {
                name = "m2" + name.Substring(2 < nameLength ? 2 : nameLength);
            }
            return name;
        }
        /// <summary>
        /// Returns a list of Keys generated from the string passed as parameter
        /// </summary>
        /// <param name="word"></param>
        /// <returns></returns>
        public static string[] BuildKeys(string word)
        {
            return !string.IsNullOrEmpty(word) ? new[] { BuildKey(word) } : EmptyKeys;
        }

        public static string BuildKey(string word)
        {
            if (string.IsNullOrEmpty(word))
                return string.Empty;

            var key = word.ToLower();
            key = Alpha.Replace(key, string.Empty);

            if (key == string.Empty)
                return string.Empty;

            //this was new in revised 2004
            //remove ending e
            if (key.EndsWith("e", System.StringComparison.Ordinal))
            {
                key = key.Substring(0, key.Length - 1);
            }

            key = TranslateStartsWith(key);
            key = TranslateRemaining(key);

            //append 10 "1"s at the end
            key += "1111111111";

            //in 2004 revised caverphone they changed from 6 to 10 characters
            //take the first 10 characters as the code
            return key.Substring(0, 10);
        }
        public static bool IsSimilar(string[] words)
        {
            string[] encoders = new string[words.Length];

            for (var i = 0; i < words.Length; i++)
            {
                encoders[i] = BuildKey(words[i]);
                if (i == 0) 
                    continue;
                if (encoders[i] != encoders[i - 1])
                {
                    return false;
                }
            }
            return true;
        }
    }
    public static class Soundex
    {
        public const string Empty = "0000";

        private static readonly Regex Sanitizer = new Regex(@"[^A-Z]", RegexOptions.Compiled);
        private static readonly Regex CollapseRepeatedNumbers = new Regex(@"(\d)?\1*[WH]*\1*", RegexOptions.Compiled);
        private static readonly Regex RemoveVowelSounds = new Regex(@"[AEIOUY]", RegexOptions.Compiled);

        public static string Generate(string Phrase)
        {
            // Remove non-alphas
            Phrase = Sanitizer.Replace((Phrase ?? string.Empty).ToUpper(), string.Empty);

            // Nothing to soundex, return empty
            if (string.IsNullOrEmpty(Phrase))
                return Empty;

            // Convert consonants to numerical representation
            var Numified = Numify(Phrase);

            // Remove repeated numeric (characters of the same sound class), even if separated by H or W
            Numified = CollapseRepeatedNumbers.Replace(Numified, @"$1");

            if (Numified.Length > 0 && Numified[0] == Numify(Phrase[0]))
            {
                // Remove first numeric as first letter in same class as subsequent letters
                Numified = Numified.Substring(1);
            }

            // Remove vowels
            Numified = RemoveVowelSounds.Replace(Numified, string.Empty);

            // Concatenate, pad and trim to ensure X### format.
            return string.Format("{0}{1}", Phrase[0], Numified).PadRight(4, '0').Substring(0, 4);
        }

        private static string Numify(string Phrase)
        {
            return new string(Phrase.ToCharArray().Select(Numify).ToArray());
        }

        private static char Numify(char Character)
        {
            switch (Character)
            {
                case 'B':
                case 'F':
                case 'P':
                case 'V':
                    return '1';
                case 'C':
                case 'G':
                case 'J':
                case 'K':
                case 'Q':
                case 'S':
                case 'X':
                case 'Z':
                    return '2';
                case 'D':
                case 'T':
                    return '3';
                case 'L':
                    return '4';
                case 'M':
                case 'N':
                    return '5';
                case 'R':
                    return '6';
                default:
                    return Character;
            }
        }
    }
    #region Code from SimMetricsCore
    public interface IStringMetric
    {
        double GetSimilarity(string firstWord, string secondWord);
        string GetSimilarityExplained(string firstWord, string secondWord);
        long GetSimilarityTimingActual(string firstWord, string secondWord);
        double GetSimilarityTimingEstimated(string firstWord, string secondWord);
        double GetUnnormalisedSimilarity(string firstWord, string secondWord);

        string LongDescriptionString { get; }

        string ShortDescriptionString { get; }
    }
    public abstract class AbstractStringMetric : IStringMetric
    {
        protected AbstractStringMetric()
        {
        }

        public double[] BatchCompareSet(string[] setRenamed, string comparator)
        {
            if ((setRenamed == null) || (comparator == null))
            {
                return null;
            }
            double[] numArray = new double[setRenamed.Length];
            for (int i = 0; i < setRenamed.Length; i++)
            {
                numArray[i] = this.GetSimilarity(setRenamed[i], comparator);
            }
            return numArray;
        }

        public double[] BatchCompareSets(string[] firstSet, string[] secondSet)
        {
            double[] numArray;
            if ((firstSet == null) || (secondSet == null))
            {
                return null;
            }
            numArray = firstSet.Length <= secondSet.Length ? (new double[firstSet.Length]) : (new double[secondSet.Length]);
            for (int i = 0; i < numArray.Length; i++)
            {
                numArray[i] = this.GetSimilarity(firstSet[i], secondSet[i]);
            }
            return numArray;
        }

        public abstract double GetSimilarity(string firstWord, string secondWord);
        public abstract string GetSimilarityExplained(string firstWord, string secondWord);
        public long GetSimilarityTimingActual(string firstWord, string secondWord)
        {
            long num = (DateTime.Now.Ticks - 0x89f7ff5f7b58000L) / 0x2710L;
            this.GetSimilarity(firstWord, secondWord);
            long num2 = (DateTime.Now.Ticks - 0x89f7ff5f7b58000L) / 0x2710L;
            return num2 - num;
        }

        public abstract double GetSimilarityTimingEstimated(string firstWord, string secondWord);
        public abstract double GetUnnormalisedSimilarity(string firstWord, string secondWord);

        public abstract string LongDescriptionString { get; }

        public abstract string ShortDescriptionString { get; }
    }
    public sealed class DummyStopTermHandler : ITermHandler
    {
        public void AddWord(string termToAdd)
        {
        }

        public bool IsWord(string termToTest)
        {
            return false;
        }

        public void RemoveWord(string termToRemove)
        {
        }

        public int NumberOfWords
        {
            get
            {
                return 0;
            }
        }

        public string ShortDescriptionString
        {
            get
            {
                return "DummyStopTermHandler";
            }
        }

        public StringBuilder WordsAsBuffer
        {
            get
            {
                return new StringBuilder();
            }
        }
    }
#pragma warning disable IDE0028
#pragma warning disable IDE0079
#pragma warning disable IDE0047
#pragma warning disable IDE0046
#pragma warning disable IDE0044
#pragma warning disable IDE0032 // Use auto property
    public class TokeniserUtilities<T>
    {
        private Collection<T> allTokens;
        private int firstSetTokenCount;
        private int firstTokenCount;
        private int secondSetTokenCount;
        private int secondTokenCount;
        private Collection<T> tokenSet;

        public TokeniserUtilities()
        {
            this.AllTokens = new Collection<T>();
            this.tokenSet = new Collection<T>();
        }

        private void AddTokens(Collection<T> tokenList)
        {
            foreach (T local in tokenList)
            {
                this.AllTokens.Add(local);
            }
        }

        private void AddUniqueTokens(Collection<T> tokenList)
        {
            foreach (T local in tokenList)
            {
                if (!this.tokenSet.Contains(local))
                {
                    this.tokenSet.Add(local);
                }
            }
        }

        private int CalculateUniqueTokensCount(Collection<T> tokenList)
        {
            Collection<T> collection = new Collection<T>();
            foreach (T local in tokenList)
            {
                if (!collection.Contains(local))
                {
                    collection.Add(local);
                }
            }
            return collection.Count;
        }

        public int CommonSetTerms()
        {
            return this.FirstSetTokenCount + this.SecondSetTokenCount - this.tokenSet.Count;
        }

        public int CommonTerms()
        {
            return this.FirstTokenCount + this.SecondTokenCount - this.AllTokens.Count;
        }

        public Collection<T> CreateMergedList(Collection<T> firstTokens, Collection<T> secondTokens)
        {
            this.AllTokens.Clear();
            this.firstTokenCount = firstTokens.Count;
            this.secondTokenCount = secondTokens.Count;
            this.MergeLists(firstTokens);
            this.MergeLists(secondTokens);
            return this.AllTokens;
        }

        public Collection<T> CreateMergedSet(Collection<T> firstTokens, Collection<T> secondTokens)
        {
            this.tokenSet.Clear();
            this.firstSetTokenCount = this.CalculateUniqueTokensCount(firstTokens);
            this.secondSetTokenCount = this.CalculateUniqueTokensCount(secondTokens);
            this.MergeIntoSet(firstTokens);
            this.MergeIntoSet(secondTokens);
            return this.tokenSet;
        }

        public Collection<T> CreateSet(Collection<T> tokenList)
        {
            this.tokenSet.Clear();
            this.AddUniqueTokens(tokenList);
            this.firstTokenCount = this.tokenSet.Count;
            this.secondTokenCount = 0;
            return this.tokenSet;
        }

        public void MergeIntoSet(Collection<T> firstTokens)
        {
            this.AddUniqueTokens(firstTokens);
        }

        public void MergeLists(Collection<T> firstTokens)
        {
            this.AddTokens(firstTokens);
        }

        public int FirstSetTokenCount
        {
            get
            {
                return this.firstSetTokenCount;
            }
        }

        public int FirstTokenCount
        {
            get
            {
                return this.firstTokenCount;
            }
        }

        public Collection<T> MergedTokens
        {
            get
            {
                return this.AllTokens;
            }
        }

        public int SecondSetTokenCount
        {
            get
            {
                return this.secondSetTokenCount;
            }
        }

        public int SecondTokenCount
        {
            get
            {
                return this.secondTokenCount;
            }
        }

        public Collection<T> TokenSet
        {
            get
            {
                return this.tokenSet;
            }
        }

        public Collection<T> AllTokens { get => AllTokens1; set => AllTokens1 = value; }
        public Collection<T> AllTokens1 { get => allTokens; set => allTokens = value; }
    }

    public interface ITermHandler
    {
        void AddWord(string termToAdd);
        bool IsWord(string termToTest);
        void RemoveWord(string termToRemove);

        int NumberOfWords { get; }

        string ShortDescriptionString { get; }

        StringBuilder WordsAsBuffer { get; }
    }
    public interface ITokeniser
    {
        Collection<string> Tokenize(string word);
        Collection<string> TokenizeToSet(string word);

        string Delimiters { get; }

        string ShortDescriptionString { get; }

        ITermHandler StopWordHandler { get; set; }
    }
    public sealed class TokeniserWhitespace : ITokeniser
    {
        private string delimiters = "\r\n\t \x00a0";
        private ITermHandler stopWordHandler = new DummyStopTermHandler();
        private TokeniserUtilities<string> tokenUtilities = new TokeniserUtilities<string>();

        public Collection<string> Tokenize(string word)
        {
            Collection<string> collection = new Collection<string>();
            if (word != null)
            {
                int length;
                for (int i = 0; i < word.Length; i = length)
                {
                    char c = word[i];
                    if (char.IsWhiteSpace(c))
                    {
                        i++;
                    }
                    length = word.Length;
                    for (int j = 0; j < this.delimiters.Length; j++)
                    {
                        int index = word.IndexOf(this.delimiters[j], i);
                        if ((index < length) && (index != -1))
                        {
                            length = index;
                        }
                    }
                    string termToTest = word.Substring(i, length - i);
                    if (!this.stopWordHandler.IsWord(termToTest))
                    {
                        collection.Add(termToTest);
                    }
                }
            }
            return collection;
        }
        public Collection<string> TokenizeToSet(string word)
        {
            return word != null ? this.tokenUtilities.CreateSet(this.Tokenize(word)) : null;
        }

        public string Delimiters
        {
            get
            {
                return this.delimiters;
            }
        }

        public string ShortDescriptionString
        {
            get
            {
                return "TokeniserWhitespace";
            }
        }

        public ITermHandler StopWordHandler
        {
            get
            {
                return this.stopWordHandler;
            }
            set
            {
                this.stopWordHandler = value;
            }
        }
    }
    public sealed class BlockDistance : AbstractStringMetric
    {
        private double estimatedTimingConstant;
        private ITokeniser tokeniser;
        private TokeniserUtilities<string> tokenUtilities;

        public BlockDistance() : this(new TokeniserWhitespace())
        {
        }

        public BlockDistance(ITokeniser tokeniserToUse)
        {
            this.estimatedTimingConstant = 6.4457140979357064E-05;
            this.tokeniser = tokeniserToUse;
            this.tokenUtilities = new TokeniserUtilities<string>();
        }

        private double GetActualSimilarity(Collection<string> firstTokens, Collection<string> secondTokens)
        {
            Collection<string> collection = this.tokenUtilities.CreateMergedList(firstTokens, secondTokens);
            int num = 0;
            foreach (string str in collection)
            {
                int num2 = 0;
                int num3 = 0;
                if (firstTokens.Contains(str))
                {
                    num2++;
                }
                if (secondTokens.Contains(str))
                {
                    num3++;
                }
                if (num2 > num3)
                {
                    num += num2 - num3;
                }
                else
                {
                    num += num3 - num2;
                }
            }
            return (double)num;
        }

        public override double GetSimilarity(string firstWord, string secondWord)
        {
            Collection<string> firstTokens = this.tokeniser.Tokenize(firstWord);
            Collection<string> secondTokens = this.tokeniser.Tokenize(secondWord);
            int num = firstTokens.Count + secondTokens.Count;
            double actualSimilarity = this.GetActualSimilarity(firstTokens, secondTokens);
            return (num - actualSimilarity) / ((double)num);
        }

        public override string GetSimilarityExplained(string firstWord, string secondWord)
        {
            throw new NotImplementedException();
        }

        public override double GetSimilarityTimingEstimated(string firstWord, string secondWord)
        {
            double count = this.tokeniser.Tokenize(firstWord).Count;
            double num2 = this.tokeniser.Tokenize(secondWord).Count;
            return (((count + num2) * count) + ((count + num2) * num2)) * estimatedTimingConstant;
        }

        public override double GetUnnormalisedSimilarity(string firstWord, string secondWord)
        {
            Collection<string> firstTokens = this.tokeniser.Tokenize(firstWord);
            Collection<string> secondTokens = this.tokeniser.Tokenize(secondWord);
            return this.GetActualSimilarity(firstTokens, secondTokens);
        }

        public override string LongDescriptionString
        {
            get
            {
                return "Implements the Block distance algorithm whereby vector space block distance is used to determine a similarity";
            }
        }

        public override string ShortDescriptionString
        {
            get
            {
                return "BlockDistance";
            }
        }
    }
    public sealed class ChapmanLengthDeviation : AbstractStringMetric
    {
        public override double GetSimilarity(string firstWord, string secondWord)
        {
            if ((firstWord == null) || (secondWord == null))
            {
                return 0.0;
            }
            double length = firstWord.Length;
            double num2 = secondWord.Length;
            return length >= num2 ? num2 / length : length / num2;
        }

        public override string GetSimilarityExplained(string firstWord, string secondWord)
        {
            throw new NotImplementedException();
        }

        public override double GetSimilarityTimingEstimated(string firstWord, string secondWord)
        {
            return 0.0;
        }

        public override double GetUnnormalisedSimilarity(string firstWord, string secondWord)
        {
            return this.GetSimilarity(firstWord, secondWord);
        }

        public override string LongDescriptionString
        {
            get
            {
                return "Implements the Chapman Length Deviation algorithm whereby the length deviation of the word strings is used to determine if the strings are similar in size - This approach is not intended to be used single handedly but rather alongside other approaches";
            }
        }

        public override string ShortDescriptionString
        {
            get
            {
                return "ChapmanLengthDeviation";
            }
        }
    }
    public sealed class ChapmanMeanLength : AbstractStringMetric
    {
        private const int chapmanMeanLengthMaxString = 500;
        private const double defaultMismatchScore = 0.0;
        private const double defaultPerfectScore = 1.0;

        public override double GetSimilarity(string firstWord, string secondWord)
        {
            if ((firstWord == null) || (secondWord == null))
            {
                return 0.0;
            }
            double num = secondWord.Length + firstWord.Length;
            if (num > 500.0)
            {
                return 1.0;
            }
            double num2 = (500.0 - num) / 500.0;
            return 1.0 - (num2 * num2 * num2 * num2);
        }

        public override string GetSimilarityExplained(string firstWord, string secondWord)
        {
            throw new NotImplementedException();
        }

        public override double GetSimilarityTimingEstimated(string firstWord, string secondWord)
        {
            return 0.0;
        }

        public override double GetUnnormalisedSimilarity(string firstWord, string secondWord)
        {
            return this.GetSimilarity(firstWord, secondWord);
        }

        public override string LongDescriptionString
        {
            get
            {
                return "Implements the Chapman Mean Length algorithm provides a similarity measure between two strings from size of the mean length of the vectors - this approach is supposed to be used to determine which metrics may be best to apply rather than giving a valid response itself";
            }
        }

        public override string ShortDescriptionString
        {
            get
            {
                return "ChapmanMeanLength";
            }
        }
    }
    public sealed class EuclideanDistance : AbstractStringMetric
    {
        private const double defaultMismatchScore = 0.0;
        private double estimatedTimingConstant;
        private ITokeniser tokeniser;
        private TokeniserUtilities<string> tokenUtilities;

        public EuclideanDistance() : this(new TokeniserWhitespace())
        {
        }

        public EuclideanDistance(ITokeniser tokeniserToUse)
        {
            this.estimatedTimingConstant = 7.4457137088757008E-05;
            this.tokeniser = tokeniserToUse;
            this.tokenUtilities = new TokeniserUtilities<string>();
        }

        private double GetActualDistance(Collection<string> firstTokens, Collection<string> secondTokens)
        {
            Collection<string> collection = this.tokenUtilities.CreateMergedList(firstTokens, secondTokens);
            int num = 0;
            foreach (string str in collection)
            {
                int num2 = 0;
                int num3 = 0;
                if (firstTokens.Contains(str))
                {
                    num2++;
                }
                if (secondTokens.Contains(str))
                {
                    num3++;
                }
                num += (num2 - num3) * (num2 - num3);
            }
            return Math.Sqrt((double)num);
        }

        public double GetEuclidDistance(string firstWord, string secondWord)
        {
            if ((firstWord != null) && (secondWord != null))
            {
                Collection<string> firstTokens = this.tokeniser.Tokenize(firstWord);
                Collection<string> secondTokens = this.tokeniser.Tokenize(secondWord);
                return this.GetActualDistance(firstTokens, secondTokens);
            }
            return 0.0;
        }

        public override double GetSimilarity(string firstWord, string secondWord)
        {
            if ((firstWord != null) && (secondWord != null))
            {
                double unnormalisedSimilarity = this.GetUnnormalisedSimilarity(firstWord, secondWord);
                double num2 = Math.Sqrt((double)(this.tokenUtilities.FirstTokenCount + this.tokenUtilities.SecondTokenCount));
                return (num2 - unnormalisedSimilarity) / num2;
            }
            return 0.0;
        }

        public override string GetSimilarityExplained(string firstWord, string secondWord)
        {
            throw new NotImplementedException();
        }

        public override double GetSimilarityTimingEstimated(string firstWord, string secondWord)
        {
            if ((firstWord != null) && (secondWord != null))
            {
                double count = this.tokeniser.Tokenize(firstWord).Count;
                double num2 = this.tokeniser.Tokenize(secondWord).Count;
                return ((((count + num2) * count) + ((count + num2) * num2)) * this.estimatedTimingConstant);
            }
            return 0.0;
        }

        public override double GetUnnormalisedSimilarity(string firstWord, string secondWord)
        {
            return this.GetEuclidDistance(firstWord, secondWord);
        }

        public override string LongDescriptionString
        {
            get
            {
                return "Implements the Euclidean Distancey algorithm providing a similarity measure between two strings using the vector space of combined terms as the dimensions";
            }
        }

        public override string ShortDescriptionString
        {
            get
            {
                return "EuclideanDistance";
            }
        }
    }
    public sealed class MatchingCoefficient : AbstractStringMetric
    {
        private const double defaultMismatchScore = 0.0;
        private double estimatedTimingConstant;
        private ITokeniser tokeniser;
        private TokeniserUtilities<string> tokenUtilities;

        public MatchingCoefficient() : this(new TokeniserWhitespace())
        {
        }

        public MatchingCoefficient(ITokeniser tokeniserToUse)
        {
            this.estimatedTimingConstant = 0.00019999999494757503;
            this.tokeniser = tokeniserToUse;
            this.tokenUtilities = new TokeniserUtilities<string>();
        }

        private double GetActualSimilarity(Collection<string> firstTokens, Collection<string> secondTokens)
        {
            this.tokenUtilities.CreateMergedList(firstTokens, secondTokens);
            int num = 0;
            foreach (string str in firstTokens)
            {
                if (secondTokens.Contains(str))
                {
                    num++;
                }
            }
            return (double)num;
        }

        public override double GetSimilarity(string firstWord, string secondWord)
        {
            if ((firstWord != null) && (secondWord != null))
            {
                double unnormalisedSimilarity = this.GetUnnormalisedSimilarity(firstWord, secondWord);
                int num2 = Math.Max(this.tokenUtilities.FirstTokenCount, this.tokenUtilities.SecondTokenCount);
                return (unnormalisedSimilarity / ((double)num2));
            }
            return 0.0;
        }

        public override string GetSimilarityExplained(string firstWord, string secondWord)
        {
            throw new NotImplementedException();
        }

        public override double GetSimilarityTimingEstimated(string firstWord, string secondWord)
        {
            if ((firstWord != null) && (secondWord != null))
            {
                double count = this.tokeniser.Tokenize(firstWord).Count;
                double num2 = this.tokeniser.Tokenize(secondWord).Count;
                return ((num2 * count) * this.estimatedTimingConstant);
            }
            return 0.0;
        }

        public override double GetUnnormalisedSimilarity(string firstWord, string secondWord)
        {
            Collection<string> firstTokens = this.tokeniser.Tokenize(firstWord);
            Collection<string> secondTokens = this.tokeniser.Tokenize(secondWord);
            return this.GetActualSimilarity(firstTokens, secondTokens);
        }

        public override string LongDescriptionString
        {
            get
            {
                return "Implements the Matching Coefficient algorithm providing a similarity measure between two strings";
            }
        }

        public override string ShortDescriptionString
        {
            get
            {
                return "MatchingCoefficient";
            }
        }
    }
    public interface ISubstitutionCost
    {
        double GetCost(string firstWord, int firstWordIndex, string secondWord, int secondWordIndex);

        double MaxCost { get; }

        double MinCost { get; }

        string ShortDescriptionString { get; }
    }
    public abstract class AbstractSubstitutionCost : ISubstitutionCost
    {
        protected AbstractSubstitutionCost()
        {
        }

        public abstract double GetCost(string firstWord, int firstWordIndex, string secondWord, int secondWordIndex);

        public abstract double MaxCost { get; }

        public abstract double MinCost { get; }

        public abstract string ShortDescriptionString { get; }
    }
    public interface IAffineGapCost
    {
        double GetCost(string textToGap, int stringIndexStartGap, int stringIndexEndGap);

        double MaxCost { get; }

        double MinCost { get; }

        string ShortDescriptionString { get; }
    }
    public abstract class AbstractAffineGapCost : IAffineGapCost
    {
        protected AbstractAffineGapCost()
        {
        }

        public abstract double GetCost(string textToGap, int stringIndexStartGap, int stringIndexEndGap);

        public abstract double MaxCost { get; }

        public abstract double MinCost { get; }

        public abstract string ShortDescriptionString { get; }
    }
    public sealed class AffineGapRange5To0Multiplier1 : AbstractAffineGapCost
    {
        private const int charExactMatchScore = 5;
        private const int charMismatchMatchScore = 0;

        public override double GetCost(string textToGap, int stringIndexStartGap, int stringIndexEndGap)
        {
            if (stringIndexStartGap >= stringIndexEndGap)
            {
                return 0.0;
            }
            return (double)(5 + ((stringIndexEndGap - 1) - stringIndexStartGap));
        }

        public override double MaxCost
        {
            get
            {
                return 5.0;
            }
        }

        public override double MinCost
        {
            get
            {
                return 0.0;
            }
        }

        public override string ShortDescriptionString
        {
            get
            {
                return "AffineGapRange5To0Multiplier1";
            }
        }
    }
    public sealed class SubCostRange5ToMinus3 : AbstractSubstitutionCost
    {
        private Collection<string>[] approx = new Collection<string>[7];
        private const int charApproximateMatchScore = 3;
        private const int charExactMatchScore = 5;
        private const int charMismatchMatchScore = -3;

        public SubCostRange5ToMinus3()
        {
            this.approx[0] = new Collection<string>();
            this.approx[0].Add("d");
            this.approx[0].Add("t");
            this.approx[1] = new Collection<string>();
            this.approx[1].Add("g");
            this.approx[1].Add("j");
            this.approx[2] = new Collection<string>();
            this.approx[2].Add("l");
            this.approx[2].Add("r");
            this.approx[3] = new Collection<string>();
            this.approx[3].Add("m");
            this.approx[3].Add("n");
            this.approx[4] = new Collection<string>();
            this.approx[4].Add("b");
            this.approx[4].Add("p");
            this.approx[4].Add("v");
            this.approx[5] = new Collection<string>();
            this.approx[5].Add("a");
            this.approx[5].Add("e");
            this.approx[5].Add("i");
            this.approx[5].Add("o");
            this.approx[5].Add("u");
            this.approx[6] = new Collection<string>();
            this.approx[6].Add(",");
            this.approx[6].Add(".");
        }

        public override double GetCost(string firstWord, int firstWordIndex, string secondWord, int secondWordIndex)
        {
            if ((firstWord != null) && (secondWord != null))
            {
                if ((firstWord.Length <= firstWordIndex) || (firstWordIndex < 0))
                {
                    return -3.0;
                }
                if ((secondWord.Length <= secondWordIndex) || (secondWordIndex < 0))
                {
                    return -3.0;
                }
                if (firstWord[firstWordIndex] == secondWord[secondWordIndex])
                {
                    return 5.0;
                }
                char ch = firstWord[firstWordIndex];
                string item = ch.ToString().ToLowerInvariant();
                char ch2 = secondWord[secondWordIndex];
                string str2 = ch2.ToString().ToLowerInvariant();
                for (int i = 0; i < this.approx.Length; i++)
                {
                    if (this.approx[i].Contains(item) && this.approx[i].Contains(str2))
                    {
                        return 3.0;
                    }
                }
            }
            return -3.0;
        }

        public override double MaxCost
        {
            get
            {
                return 5.0;
            }
        }

        public override double MinCost
        {
            get
            {
                return -3.0;
            }
        }

        public override string ShortDescriptionString
        {
            get
            {
                return "SubCostRange5ToMinus3";
            }
        }
    }
    public class SmithWatermanGotohWindowedAffine : AbstractStringMetric
    {
        private AbstractSubstitutionCost dCostFunction;
        private const double defaultMismatchScore = 0.0;
        private const double defaultPerfectScore = 1.0;
        private const int defaultWindowSize = 100;
        private double estimatedTimingConstant;
        private AbstractAffineGapCost gGapFunction;
        private int windowSize;

        public SmithWatermanGotohWindowedAffine() : this(new AffineGapRange5To0Multiplier1(), new SubCostRange5ToMinus3(), 100)
        {
        }

        public SmithWatermanGotohWindowedAffine(AbstractAffineGapCost gapCostFunction) : this(gapCostFunction, new SubCostRange5ToMinus3(), 100)
        {
        }

        public SmithWatermanGotohWindowedAffine(AbstractSubstitutionCost costFunction) : this(new AffineGapRange5To0Multiplier1(), costFunction, 100)
        {
        }

        public SmithWatermanGotohWindowedAffine(int affineGapWindowSize) : this(new AffineGapRange5To0Multiplier1(), new SubCostRange5ToMinus3(), affineGapWindowSize)
        {
        }

        public SmithWatermanGotohWindowedAffine(AbstractAffineGapCost gapCostFunction, AbstractSubstitutionCost costFunction) : this(gapCostFunction, costFunction, 100)
        {
        }

        public SmithWatermanGotohWindowedAffine(AbstractAffineGapCost gapCostFunction, int affineGapWindowSize) : this(gapCostFunction, new SubCostRange5ToMinus3(), affineGapWindowSize)
        {
        }

        public SmithWatermanGotohWindowedAffine(AbstractSubstitutionCost costFunction, int affineGapWindowSize) : this(new AffineGapRange5To0Multiplier1(), costFunction, affineGapWindowSize)
        {
        }

        public SmithWatermanGotohWindowedAffine(AbstractAffineGapCost gapCostFunction, AbstractSubstitutionCost costFunction, int affineGapWindowSize)
        {
            this.estimatedTimingConstant = 4.5000000682193786E-05;
            this.gGapFunction = gapCostFunction;
            this.dCostFunction = costFunction;
            this.windowSize = affineGapWindowSize;
        }

        public override double GetSimilarity(string firstWord, string secondWord)
        {
            if ((firstWord == null) || (secondWord == null))
            {
                return 0.0;
            }
            double unnormalisedSimilarity = this.GetUnnormalisedSimilarity(firstWord, secondWord);
            double num2 = Math.Min(firstWord.Length, secondWord.Length);
            if (this.dCostFunction.MaxCost > -this.gGapFunction.MaxCost)
            {
                num2 *= this.dCostFunction.MaxCost;
            }
            else
            {
                num2 *= -this.gGapFunction.MaxCost;
            }
            if (num2 == 0.0)
            {
                return 1.0;
            }
            return (unnormalisedSimilarity / num2);
        }

        public override string GetSimilarityExplained(string firstWord, string secondWord)
        {
            throw new NotImplementedException();
        }

        public override double GetSimilarityTimingEstimated(string firstWord, string secondWord)
        {
            if ((firstWord != null) && (secondWord != null))
            {
                double length = firstWord.Length;
                double num2 = secondWord.Length;
                return ((((length * num2) * this.windowSize) + ((length * num2) * this.windowSize)) * this.estimatedTimingConstant);
            }
            return 0.0;
        }
        public static class MathFunctions
        {
            public static double MaxOf3(double firstNumber, double secondNumber, double thirdNumber)
            {
                return Math.Max(firstNumber, Math.Max(secondNumber, thirdNumber));
            }

            public static int MaxOf3(int firstNumber, int secondNumber, int thirdNumber)
            {
                return Math.Max(firstNumber, Math.Max(secondNumber, thirdNumber));
            }

            public static double MaxOf4(double firstNumber, double secondNumber, double thirdNumber, double fourthNumber)
            {
                return Math.Max(Math.Max(firstNumber, secondNumber), Math.Max(thirdNumber, fourthNumber));
            }

            public static double MinOf3(double firstNumber, double secondNumber, double thirdNumber)
            {
                return Math.Min(firstNumber, Math.Min(secondNumber, thirdNumber));
            }

            public static int MinOf3(int firstNumber, int secondNumber, int thirdNumber)
            {
                return Math.Min(firstNumber, Math.Min(secondNumber, thirdNumber));
            }
        }
        public override double GetUnnormalisedSimilarity(string firstWord, string secondWord)
        {
            if ((firstWord == null) || (secondWord == null))
            {
                return 0.0;
            }
            int length = firstWord.Length;
            int num2 = secondWord.Length;
            if (length == 0)
            {
                return (double)num2;
            }
            if (num2 == 0)
            {
                return (double)length;
            }
            double[][] numArray = new double[length][];
            for (int i = 0; i < length; i++)
            {
                numArray[i] = new double[num2];
            }
            double num4 = 0.0;
            for (int j = 0; j < length; j++)
            {
                double num6 = this.dCostFunction.GetCost(firstWord, j, secondWord, 0);
                if (j == 0)
                {
                    numArray[0][0] = Math.Max(0.0, num6);
                }
                else
                {
                    double num7 = 0.0;
                    int num8 = j - this.windowSize;
                    if (num8 < 1)
                    {
                        num8 = 1;
                    }
                    for (int n = num8; n < j; n++)
                    {
                        num7 = Math.Max(num7, numArray[j - n][0] - this.gGapFunction.GetCost(firstWord, j - n, j));
                    }
                    numArray[j][0] = MathFunctions.MaxOf3(0.0, num7, num6);
                }
                if (numArray[j][0] > num4)
                {
                    num4 = numArray[j][0];
                }
            }
            for (int k = 0; k < num2; k++)
            {
                double num11 = this.dCostFunction.GetCost(firstWord, 0, secondWord, k);
                if (k == 0)
                {
                    numArray[0][0] = Math.Max(0.0, num11);
                }
                else
                {
                    double num12 = 0.0;
                    int num13 = k - this.windowSize;
                    if (num13 < 1)
                    {
                        num13 = 1;
                    }
                    for (int num14 = num13; num14 < k; num14++)
                    {
                        num12 = Math.Max(num12, numArray[0][k - num14] - this.gGapFunction.GetCost(secondWord, k - num14, k));
                    }
                    numArray[0][k] = MathFunctions.MaxOf3(0.0, num12, num11);
                }
                if (numArray[0][k] > num4)
                {
                    num4 = numArray[0][k];
                }
            }
            for (int m = 1; m < length; m++)
            {
                for (int num16 = 1; num16 < num2; num16++)
                {
                    double num17 = this.dCostFunction.GetCost(firstWord, m, secondWord, num16);
                    double num18 = 0.0;
                    double num19 = 0.0;
                    int num20 = m - this.windowSize;
                    if (num20 < 1)
                    {
                        num20 = 1;
                    }
                    for (int num21 = num20; num21 < m; num21++)
                    {
                        num18 = Math.Max(num18, numArray[m - num21][num16] - this.gGapFunction.GetCost(firstWord, m - num21, m));
                    }
                    num20 = num16 - this.windowSize;
                    if (num20 < 1)
                    {
                        num20 = 1;
                    }
                    for (int num22 = num20; num22 < num16; num22++)
                    {
                        num19 = Math.Max(num19, numArray[m][num16 - num22] - this.gGapFunction.GetCost(secondWord, num16 - num22, num16));
                    }
                    numArray[m][num16] = MathFunctions.MaxOf4(0.0, num18, num19, numArray[m - 1][num16 - 1] + num17);
                    if (numArray[m][num16] > num4)
                    {
                        num4 = numArray[m][num16];
                    }
                }
            }
            return num4;
        }

        public AbstractSubstitutionCost DCostFunction
        {
            get
            {
                return this.dCostFunction;
            }
            set
            {
                this.dCostFunction = value;
            }
        }

        public AbstractAffineGapCost GGapFunction
        {
            get
            {
                return this.gGapFunction;
            }
            set
            {
                this.gGapFunction = value;
            }
        }

        public override string LongDescriptionString
        {
            get
            {
                return "Implements the Smith-Waterman-Gotoh algorithm with a windowed affine gap providing a similarity measure between two string";
            }
        }

        public override string ShortDescriptionString
        {
            get
            {
                return "SmithWatermanGotohWindowedAffine";
            }
        }
    }
    public sealed class SmithWatermanGotoh : SmithWatermanGotohWindowedAffine
    {
        private const int affineGapWindowSize = 0x7fffffff;
        private const double estimatedTimingConstant = 2.2000000171829015E-05;

        public SmithWatermanGotoh() : base(new AffineGapRange5To0Multiplier1(), new SubCostRange5ToMinus3(), 0x7fffffff)
        {
        }

        public SmithWatermanGotoh(AbstractAffineGapCost gapCostFunction) : base(gapCostFunction, new SubCostRange5ToMinus3(), 0x7fffffff)
        {
        }

        public SmithWatermanGotoh(AbstractSubstitutionCost costFunction) : base(new AffineGapRange5To0Multiplier1(), costFunction, 0x7fffffff)
        {
        }

        public SmithWatermanGotoh(AbstractAffineGapCost gapCostFunction, AbstractSubstitutionCost costFunction) : base(gapCostFunction, costFunction, 0x7fffffff)
        {
        }

        public override double GetSimilarityTimingEstimated(string firstWord, string secondWord)
        {
            if ((firstWord != null) && (secondWord != null))
            {
                double length = firstWord.Length;
                double num2 = secondWord.Length;
                return ((((length * num2) * length) + ((length * num2) * num2)) * 2.2000000171829015E-05);
            }
            return 0.0;
        }

        public override string LongDescriptionString
        {
            get
            {
                return "Implements the Smith-Waterman-Gotoh algorithm providing a similarity measure between two string";
            }
        }

        public override string ShortDescriptionString
        {
            get
            {
                return "SmithWatermanGotoh";
            }
        }
    }
    public class MongeElkan : AbstractStringMetric
    {
        private const double defaultMismatchScore = 0.0;
        private double estimatedTimingConstant;
        private AbstractStringMetric internalStringMetric;
        internal ITokeniser tokeniser;

        public MongeElkan() : this(new TokeniserWhitespace())
        {
        }

        public MongeElkan(AbstractStringMetric metricToUse)
        {
            this.estimatedTimingConstant = 0.034400001168251038;
            this.tokeniser = new TokeniserWhitespace();
            this.internalStringMetric = metricToUse;
        }

        public MongeElkan(ITokeniser tokeniserToUse)
        {
            this.estimatedTimingConstant = 0.034400001168251038;
            this.tokeniser = tokeniserToUse;
            this.internalStringMetric = new SmithWatermanGotoh();
        }

        public MongeElkan(ITokeniser tokeniserToUse, AbstractStringMetric metricToUse)
        {
            this.estimatedTimingConstant = 0.034400001168251038;
            this.tokeniser = tokeniserToUse;
            this.internalStringMetric = metricToUse;
        }

        public override double GetSimilarity(string firstWord, string secondWord)
        {
            if ((firstWord == null) || (secondWord == null))
            {
                return 0.0;
            }
            Collection<string> collection = this.tokeniser.Tokenize(firstWord);
            Collection<string> collection2 = this.tokeniser.Tokenize(secondWord);
            double num = 0.0;
            for (int i = 0; i < collection.Count; i++)
            {
                string str = collection[i];
                double num3 = 0.0;
                for (int j = 0; j < collection2.Count; j++)
                {
                    string str2 = collection2[j];
                    double similarity = this.internalStringMetric.GetSimilarity(str, str2);
                    if (similarity > num3)
                    {
                        num3 = similarity;
                    }
                }
                num += num3;
            }
            return (num / ((double)collection.Count));
        }

        public override string GetSimilarityExplained(string firstWord, string secondWord)
        {
            throw new NotImplementedException();
        }

        public override double GetSimilarityTimingEstimated(string firstWord, string secondWord)
        {
            if ((firstWord != null) && (secondWord != null))
            {
                double count = this.tokeniser.Tokenize(firstWord).Count;
                double num2 = this.tokeniser.Tokenize(secondWord).Count;
                return ((((count + num2) * count) + ((count + num2) * num2)) * this.estimatedTimingConstant);
            }
            return 0.0;
        }

        public override double GetUnnormalisedSimilarity(string firstWord, string secondWord)
        {
            return this.GetSimilarity(firstWord, secondWord);
        }

        public override string LongDescriptionString
        {
            get
            {
                return "Implements the Monge Elkan algorithm providing an matching style similarity measure between two strings";
            }
        }

        public override string ShortDescriptionString
        {
            get
            {
                return "MongeElkan";
            }
        }
    }
    public class TokeniserQGram3 : AbstractTokeniserQGramN
    {
        public TokeniserQGram3()
        {
            base.StopWordHandler = new DummyStopTermHandler();
            base.TokenUtilities = new TokeniserUtilities<string>();
            base.CharacterCombinationIndex = 0;
            base.QGramLength = 3;
        }

        public override Collection<string> Tokenize(string word)
        {
            return base.Tokenize(word, false, base.QGramLength, base.CharacterCombinationIndex);
        }

        public override string ToString()
        {
            if (string.IsNullOrEmpty(base.SuppliedWord))
            {
                return string.Format("{0} : not word passed for tokenizing yet.", this.ShortDescriptionString);
            }
            return string.Format("{0} - currently holding : {1}.{2}The method is using a QGram length of {3}.", new object[] { this.ShortDescriptionString, base.SuppliedWord, Environment.NewLine, Convert.ToInt32(base.QGramLength) });
        }

        public override string ShortDescriptionString
        {
            get
            {
                return "TokeniserQGram3";
            }
        }
    }
    public abstract class AbstractTokeniserQGramN : ITokeniser
    {
        private int characterCombinationIndex;
        private const string defaultEndPadCharacter = "#";
        private const string defaultStartPadCharacter = "?";
        private int qGramLength;
        private ITermHandler stopWordHandler;
        private string suppliedWord;
        private TokeniserUtilities<string> tokenUtilities;

        protected AbstractTokeniserQGramN()
        {
        }

        public abstract Collection<string> Tokenize(string word);
        public Collection<string> Tokenize(string word, bool extended, int tokenLength, int characterCombinationIndexValue)
        {
            int num3;
            if (string.IsNullOrEmpty(word))
            {
                return null;
            }
            this.SuppliedWord = word;
            Collection<string> collection = new Collection<string>();
            int length = word.Length;
            int count = 0;
            if (tokenLength > 0)
            {
                count = tokenLength - 1;
            }
            StringBuilder builder = new StringBuilder(length + (2 * count));
            if (extended)
            {
                builder.Insert(0, "?", count);
            }
            builder.Append(word);
            if (extended)
            {
                builder.Insert(builder.Length, "#", count);
            }
            string str = builder.ToString();
            num3 = extended ? length + count : (length - tokenLength) + 1;
            for (int i = 0; i < num3; i++)
            {
                string termToTest = str.Substring(i, tokenLength);
                if (!this.stopWordHandler.IsWord(termToTest))
                {
                    collection.Add(termToTest);
                }
            }
            if (characterCombinationIndexValue != 0)
            {
                str = builder.ToString();
                num3--;
                for (int j = 0; j < num3; j++)
                {
                    string str3 = str.Substring(j, count) + str.Substring(j + tokenLength, 1);
                    if (!this.stopWordHandler.IsWord(str3) && !collection.Contains(str3))
                    {
                        collection.Add(str3);
                    }
                }
            }
            return collection;
        }

        public Collection<string> TokenizeToSet(string word)
        {
            if (!string.IsNullOrEmpty(word))
            {
                this.SuppliedWord = word;
                return this.TokenUtilities.CreateSet(this.Tokenize(word));
            }
            return null;
        }

        public int CharacterCombinationIndex
        {
            get
            {
                return this.characterCombinationIndex;
            }
            set
            {
                this.characterCombinationIndex = value;
            }
        }

        public string Delimiters
        {
            get
            {
                return string.Empty;
            }
        }

        public int QGramLength
        {
            get
            {
                return this.qGramLength;
            }
            set
            {
                this.qGramLength = value;
            }
        }

        public abstract string ShortDescriptionString { get; }

        public ITermHandler StopWordHandler
        {
            get
            {
                return this.stopWordHandler;
            }
            set
            {
                this.stopWordHandler = value;
            }
        }

        public string SuppliedWord
        {
            get
            {
                return this.suppliedWord;
            }
            set
            {
                this.suppliedWord = value;
            }
        }

        public TokeniserUtilities<string> TokenUtilities
        {
            get
            {
                return this.tokenUtilities;
            }
            set
            {
                this.tokenUtilities = value;
            }
        }
    }
    public class TokeniserQGram3Extended : TokeniserQGram3
    {
        public override Collection<string> Tokenize(string word)
        {
            return base.Tokenize(word, true, base.QGramLength, base.CharacterCombinationIndex);
        }

        public override string ToString()
        {
            if (string.IsNullOrEmpty(base.SuppliedWord))
            {
                return string.Format("{0} : not word passed for tokenizing yet.", this.ShortDescriptionString);
            }
            return string.Format("{0} - currently holding : {1}.{2}The method is using a QGram length of {3}.", new object[] { this.ShortDescriptionString, base.SuppliedWord, Environment.NewLine, Convert.ToInt32(base.QGramLength) });
        }

        public override string ShortDescriptionString
        {
            get
            {
                return "TokeniserQGram3Extended";
            }
        }
    }
    public sealed class QGramsDistance : AbstractStringMetric
    {
        private const double defaultMismatchScore = 0.0;
        private double estimatedTimingConstant;
        private ITokeniser tokeniser;
        private TokeniserUtilities<string> tokenUtilities;

        public QGramsDistance() : this(new TokeniserQGram3Extended())
        {
        }

        public QGramsDistance(ITokeniser tokeniserToUse)
        {
            this.estimatedTimingConstant = 0.0001340000017080456;
            this.tokeniser = tokeniserToUse;
            this.tokenUtilities = new TokeniserUtilities<string>();
        }

        private double GetActualSimilarity(Collection<string> firstTokens, Collection<string> secondTokens)
        {
            Collection<string> collection = this.tokenUtilities.CreateMergedSet(firstTokens, secondTokens);
            int num = 0;
            foreach (string str in collection)
            {
                int num2 = 0;
                for (int i = 0; i < firstTokens.Count; i++)
                {
                    if (firstTokens[i].Equals(str))
                    {
                        num2++;
                    }
                }
                int num4 = 0;
                for (int j = 0; j < secondTokens.Count; j++)
                {
                    if (secondTokens[j].Equals(str))
                    {
                        num4++;
                    }
                }
                if (num2 > num4)
                {
                    num += num2 - num4;
                }
                else
                {
                    num += num4 - num2;
                }
            }
            return (double)num;
        }

        public override double GetSimilarity(string firstWord, string secondWord)
        {
            if ((firstWord != null) && (secondWord != null))
            {
                double unnormalisedSimilarity = this.GetUnnormalisedSimilarity(firstWord, secondWord);
                int num2 = this.tokenUtilities.FirstTokenCount + this.tokenUtilities.SecondTokenCount;
                if (num2 != 0)
                {
                    return ((num2 - unnormalisedSimilarity) / ((double)num2));
                }
            }
            return 0.0;
        }

        public override string GetSimilarityExplained(string firstWord, string secondWord)
        {
            throw new NotImplementedException();
        }

        public override double GetSimilarityTimingEstimated(string firstWord, string secondWord)
        {
            if ((firstWord != null) && (secondWord != null))
            {
                double length = firstWord.Length;
                double num2 = secondWord.Length;
                return ((length * num2) * this.estimatedTimingConstant);
            }
            return 0.0;
        }

        public override double GetUnnormalisedSimilarity(string firstWord, string secondWord)
        {
            Collection<string> firstTokens = this.tokeniser.Tokenize(firstWord);
            Collection<string> secondTokens = this.tokeniser.Tokenize(secondWord);
            this.tokenUtilities.CreateMergedList(firstTokens, secondTokens);
            return this.GetActualSimilarity(firstTokens, secondTokens);
        }

        public override string LongDescriptionString
        {
            get
            {
                return "Implements the Q Grams Distance algorithm providing a similarity measure between two strings using the qGram approach check matching qGrams/possible matching qGrams";
            }
        }

        public override string ShortDescriptionString
        {
            get
            {
                return "QGramsDistance";
            }
        }
    }
    public sealed class SubCostRange1ToMinus2 : AbstractSubstitutionCost
    {
        private const int charExactMatchScore = 1;
        private const int charMismatchMatchScore = -2;

        public override double GetCost(string firstWord, int firstWordIndex, string secondWord, int secondWordIndex)
        {
            if ((firstWord == null) || (secondWord == null))
            {
                return -2.0;
            }
            if ((firstWord.Length <= firstWordIndex) || (firstWordIndex < 0))
            {
                return -2.0;
            }
            if ((secondWord.Length <= secondWordIndex) || (secondWordIndex < 0))
            {
                return -2.0;
            }
            return ((firstWord[firstWordIndex] != secondWord[secondWordIndex]) ? ((double)(-2)) : ((double)1));
        }

        public override double MaxCost
        {
            get
            {
                return 1.0;
            }
        }

        public override double MinCost
        {
            get
            {
                return -2.0;
            }
        }

        public override string ShortDescriptionString
        {
            get
            {
                return "SubCostRange1ToMinus2";
            }
        }
    }
    public sealed class SmithWaterman : AbstractStringMetric
    {
        private AbstractSubstitutionCost dCostFunction;
        private const double defaultGapCost = 0.5;
        private const double defaultMismatchScore = 0.0;
        private const double defaultPerfectMatchScore = 1.0;
        private const double estimatedTimingConstant = 0.0001610000035725534;
        private double gapCost;

        public SmithWaterman() : this(0.5, new SubCostRange1ToMinus2())
        {
        }

        public SmithWaterman(AbstractSubstitutionCost costFunction) : this(0.5, costFunction)
        {
        }

        public SmithWaterman(double costG) : this(costG, new SubCostRange1ToMinus2())
        {
        }

        public SmithWaterman(double costG, AbstractSubstitutionCost costFunction)
        {
            this.gapCost = costG;
            this.dCostFunction = costFunction;
        }

        public override double GetSimilarity(string firstWord, string secondWord)
        {
            if ((firstWord == null) || (secondWord == null))
            {
                return 0.0;
            }
            double unnormalisedSimilarity = this.GetUnnormalisedSimilarity(firstWord, secondWord);
            double num2 = Math.Min(firstWord.Length, secondWord.Length);
            if (this.dCostFunction.MaxCost > -this.gapCost)
            {
                num2 *= this.dCostFunction.MaxCost;
            }
            else
            {
                num2 *= -this.gapCost;
            }
            if (num2 == 0.0)
            {
                return 1.0;
            }
            return (unnormalisedSimilarity / num2);
        }

        public override string GetSimilarityExplained(string firstWord, string secondWord)
        {
            throw new NotImplementedException();
        }

        public override double GetSimilarityTimingEstimated(string firstWord, string secondWord)
        {
            if ((firstWord != null) && (secondWord != null))
            {
                double length = firstWord.Length;
                double num2 = secondWord.Length;
                return ((((length * num2) + length) + num2) * 0.0001610000035725534);
            }
            return 0.0;
        }

        public override double GetUnnormalisedSimilarity(string firstWord, string secondWord)
        {
            if ((firstWord == null) || (secondWord == null))
            {
                return 0.0;
            }
            int length = firstWord.Length;
            int num2 = secondWord.Length;
            if (length == 0)
            {
                return (double)num2;
            }
            if (num2 == 0)
            {
                return (double)length;
            }
            double[][] numArray = new double[length][];
            for (int i = 0; i < length; i++)
            {
                numArray[i] = new double[num2];
            }
            double num4 = 0.0;
            for (int j = 0; j < length; j++)
            {
                double thirdNumber = this.dCostFunction.GetCost(firstWord, j, secondWord, 0);
                if (j == 0)
                {
                    numArray[0][0] = MathFunctions.MaxOf3(0.0, -this.gapCost, thirdNumber);
                }
                else
                {
                    numArray[j][0] = MathFunctions.MaxOf3(0.0, numArray[j - 1][0] - this.gapCost, thirdNumber);
                }
                if (numArray[j][0] > num4)
                {
                    num4 = numArray[j][0];
                }
            }
            for (int k = 0; k < num2; k++)
            {
                double num8 = this.dCostFunction.GetCost(firstWord, 0, secondWord, k);
                if (k == 0)
                {
                    numArray[0][0] = MathFunctions.MaxOf3(0.0, -this.gapCost, num8);
                }
                else
                {
                    numArray[0][k] = MathFunctions.MaxOf3(0.0, numArray[0][k - 1] - this.gapCost, num8);
                }
                if (numArray[0][k] > num4)
                {
                    num4 = numArray[0][k];
                }
            }
            for (int m = 1; m < length; m++)
            {
                for (int n = 1; n < num2; n++)
                {
                    double num11 = this.dCostFunction.GetCost(firstWord, m, secondWord, n);
                    numArray[m][n] = MathFunctions.MaxOf4(0.0, numArray[m - 1][n] - this.gapCost, numArray[m][n - 1] - this.gapCost, numArray[m - 1][n - 1] + num11);
                    if (numArray[m][n] > num4)
                    {
                        num4 = numArray[m][n];
                    }
                }
            }
            return num4;
        }

        public AbstractSubstitutionCost DCostFunction
        {
            get
            {
                return this.dCostFunction;
            }
            set
            {
                this.DCostFunction = value;
            }
        }

        public double GapCost
        {
            get
            {
                return this.gapCost;
            }
            set
            {
                this.gapCost = value;
            }
        }

        public override string LongDescriptionString
        {
            get
            {
                return "Implements the Smith-Waterman algorithm providing a similarity measure between two string";
            }
        }

        public override string ShortDescriptionString
        {
            get
            {
                return "SmithWaterman";
            }
        }
    }
    public sealed class DiceSimilarity : AbstractStringMetric
    {
        private double estimatedTimingConstant;
        private ITokeniser tokeniser;
        private TokeniserUtilities<string> tokenUtilities;

        public DiceSimilarity() : this(new TokeniserWhitespace())
        {
        }

        public DiceSimilarity(ITokeniser tokeniserToUse)
        {
            this.estimatedTimingConstant = 3.4457139008736704E-07;
            this.tokeniser = tokeniserToUse;
            this.tokenUtilities = new TokeniserUtilities<string>();
        }

        public override double GetSimilarity(string firstWord, string secondWord)
        {
            if (((firstWord != null) && (secondWord != null)) && (this.tokenUtilities.CreateMergedSet(this.tokeniser.Tokenize(firstWord), this.tokeniser.Tokenize(secondWord)).Count > 0))
            {
                return ((2.0 * this.tokenUtilities.CommonSetTerms()) / ((double)(this.tokenUtilities.FirstSetTokenCount + this.tokenUtilities.SecondSetTokenCount)));
            }
            return 0.0;
        }

        public override string GetSimilarityExplained(string firstWord, string secondWord)
        {
            throw new NotImplementedException();
        }

        public override double GetSimilarityTimingEstimated(string firstWord, string secondWord)
        {
            if ((firstWord != null) && (secondWord != null))
            {
                double length = firstWord.Length;
                double num2 = secondWord.Length;
                return ((length + num2) * ((length + num2) * this.estimatedTimingConstant));
            }
            return 0.0;
        }

        public override double GetUnnormalisedSimilarity(string firstWord, string secondWord)
        {
            return this.GetSimilarity(firstWord, secondWord);
        }

        public override string LongDescriptionString
        {
            get
            {
                return "Implements the DiceSimilarity algorithm providing a similarity measure between two strings using the vector space of present terms";
            }
        }

        public override string ShortDescriptionString
        {
            get
            {
                return "DiceSimilarity";
            }
        }
    }
#pragma warning restore IDE0032
#pragma warning restore IDE0044
#pragma warning restore IDE0046
#pragma warning restore IDE0047
#pragma warning disable IDE0079
#pragma warning disable IDE0028

    #endregion Code from SimMetricsCore
    #endregion Fuzzy classes
}
// Goals for supporting distance algorithms 
//       BlockDistance
//       ChapmanLengthDeviation
//       ChapmanMeanLength
//       *CosineSimilarityClass
//       DiceSimilarity
//       EuclideanDistance
//       *JaccardSimilarityClass
//       *Jaro
//       *JaroWinkler
//       *Levenstein
//       MatchingCoefficient
//       MongeElkan
//       *NeedlemanWunch
//       *OverlapCoefficient
//       QGramsDistance
//       SmithWaterman
//       SmithWatermanGotoh
//       SmithWatermanGotohWindowedAffine
