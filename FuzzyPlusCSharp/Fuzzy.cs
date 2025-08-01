
using System;
using System.Collections.Generic;
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
        public bool IsVerySimilar(string source1, string source2) => Fuzzy.IsMatch(source1, source2, 0.9f, distanceMethod); // Is 90% similar
        public bool IsSimilar(string source1, string source2) => Fuzzy.IsMatch(source1, source2, 0.75f, distanceMethod); // Is 75% similar
        public bool IsSomeWhatSimilar(string source1, string source2) => Fuzzy.IsMatch(source1, source2, 0.5f, distanceMethod); // Is 50% similar
        public bool IsSlightlySimilar(string source1, string source2) => Fuzzy.IsMatch(source1, source2, 0.3f, distanceMethod); // Is 30% similar
        public bool IsHardlySimilar(string source1, string source2) => Fuzzy.IsMatch(source1, source2, 0.1f, distanceMethod); // Is 10% similar
        public bool IsMatch(string source1, string source2, float desiredSimilarity) => Fuzzy.HowSimilar(source1, source2, distanceMethod) >= desiredSimilarity;
        public float HowSimilar(string source1, string source2) => Fuzzy.HowSimilar(source1, source2, distanceMethod);
        public bool IsNotSimilar(string source1, string source2) => Fuzzy.IsNotSimilar(source1, source2, distanceMethod);
    }
    #endregion Non-Static version
    //////////////////////////////////////////////////////////////////////
    /// Static version
    public static class Fuzzy
    {
        #region DistanceMethod definitions
        public const int CASE_INSENSITIVE = 128;
        public const int CPP_ONLY_FUZZY = 64;
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
            EditDistance,

            //Token methods
            CosineSimilarity,
            JaccardSimilarity,
            // Phrase token methods which are all case insensitive only
            PhraseTokenize,
            SimplePhraseTokenize,

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
        #region Similarity functions
        public static bool IsMatch(string source1, string source2, float desiredSimilarity, DistanceMethod distanceMethod = DistanceMethod.UseDefaultDistanceMethod) => HowSimilar(source1, source2, distanceMethod) >= desiredSimilarity;
        // The following HowSimilar method is to let SQLite access to HowSimilar
        public static bool IsCaseSensitive(DistanceMethod distanceMethod) => (int)distanceMethod < CASE_INSENSITIVE;
        public static float HowSimilar(string source1, string source2, int distanceMethod) => HowSimilar(source1, source2, GetDistanceMethod(distanceMethod));
        public static float HowSimilar(string source1, string source2, string distanceMethod) => HowSimilar(source1, source2, GetDistanceMethod(distanceMethod));
        public static float HowSimilar(string source1, string source2, DistanceMethod distanceMethod = DistanceMethod.UseDefaultDistanceMethod)
        {
            if (distanceMethod == DistanceMethod.UseDefaultDistanceMethod)
                distanceMethod = DefaultDistanceMethod;
            bool isCaseSensitive = IsCaseSensitive(distanceMethod);
            float sourceLength = Math.Max(source1.Length, source2.Length);
            float diff;
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
                    return CosineSimilarity.Percentage(source1, source2, isCaseSensitive);
                case DistanceMethod.LongestCommonSequence:
                case DistanceMethod.iLongestCommonSequence:
                    return LongestCommonSequence.Percentage(source1, source2, isCaseSensitive);
                case DistanceMethod.JaccardSimilarity:
                case DistanceMethod.iJaccardSimilarity:
                    return JaccardSimilarity.Percentage(source1, source2, isCaseSensitive);
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
                    return NeedlemanWunsch.Percentage(source1, source2, isCaseSensitive);
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
        public static float Distance(string source1, string source2, DistanceMethod distanceMethod = DistanceMethod.UseDefaultDistanceMethod)
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
                    return CosineSimilarity.Percentage(source1, source2, isCaseSensitive);
                case DistanceMethod.LongestCommonSequence:
                case DistanceMethod.iLongestCommonSequence:
                    return LongestCommonSequence.Percentage(source1, source2, isCaseSensitive);
                case DistanceMethod.JaccardSimilarity:
                case DistanceMethod.iJaccardSimilarity:
                    return JaccardSimilarity.Percentage(source1, source2, isCaseSensitive);
                case DistanceMethod.JaccardIndex:
                case DistanceMethod.iJaccardIndex:
                    return JaccardDistance(source1, source2, isCaseSensitive);
                case DistanceMethod.OverlapCoefficient:
                case DistanceMethod.iOverlapCoefficient:
                    return OverlapCoefficientDistance(source1, source2, isCaseSensitive);
                case DistanceMethod.NeedlemanWunsch:
                case DistanceMethod.iNeedlemanWunsch:
                    return NeedlemanWunsch.Percentage(source1, source2, isCaseSensitive);
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
        public static float Distance(string source1, string source2, int distanceMethod) => Distance(source1, source2, GetDistanceMethod(distanceMethod));
        public static float Distance(string source1, string source2, string distanceMethod) => Distance(source1, source2, GetDistanceMethod(distanceMethod));
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
                    return CosineSimilarity.Percentage(source1, source2, isCaseSensitive) == 0;
                case DistanceMethod.JaccardSimilarity:
                case DistanceMethod.iJaccardSimilarity:
                    return JaccardSimilarity.Percentage(source1, source2, isCaseSensitive) == 0;
                case DistanceMethod.JaccardIndex:
                case DistanceMethod.iJaccardIndex:
                    return JaccardDistance(source1, source2, isCaseSensitive) == Math.Max(source1.Length, source2.Length);
                case DistanceMethod.OverlapCoefficient:
                case DistanceMethod.iOverlapCoefficient:
                    return OverlapCoefficientDistance(source1, source2, isCaseSensitive) == Math.Max(source1.Length, source2.Length);
                case DistanceMethod.NeedlemanWunsch:
                case DistanceMethod.iNeedlemanWunsch:
                    return NeedlemanWunsch.Percentage(source1, source2, isCaseSensitive) == 0;
                case DistanceMethod.LongestCommonSequence:
                case DistanceMethod.iLongestCommonSequence:
                    return LongestCommonSequence.Difference(source1, source2, isCaseSensitive) == Math.Max(source1.Length, source2.Length);
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
            if (!isCaseSensitive)
            {
                source1 = source1.ToLower();
                source2 = source2.ToLower();
            }
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
            if (!isCaseSensitive)
            {
                source1 = source1.ToLower();
                source2 = source2.ToLower();
            }
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
        public static float JaroWinklerPercentage(string source1, string source2, bool isCaseSensitive = true)
        {
            return 1.0f - JaroWinklerDistance(source1, source2, isCaseSensitive);
        }
        /// The Winkler modification will not be applied unless the percent match was at or above the JaroWinklerWeightThreshold percent without the modification. Winkler's paper used a default value of 0.7
        private static readonly float JaroWinklerWeightThreshold = 0.7f;
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
        public static float JaroWinklerDistance(string source1, string source2, bool isCaseSensitive = true)
        {
            int source1Length = source1.Length;
            int source2Length = source2.Length;
            if (source1Length == 0)
                return source2Length == 0 ? 1.0f : 0.0f;
            if (!isCaseSensitive)
            {
                source1 = source1.ToLower();
                source2 = source2.ToLower();
            }
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
            float lNumCommonD = lNumCommon;
            float lWeight = ((lNumCommonD / source1Length) + (lNumCommonD / source2Length) + ((lNumCommon - lNumTransposed) / lNumCommonD)) / 3.0f;
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
        public static float OverlapCoefficientDistance(this string source1, string source2, bool isCaseSensitive = true)
        {
            if (!isCaseSensitive)
            {
                source1 = source1.ToLower();
                source2 = source2.ToLower();
            }
            return 1.0f - (float)source1.OverlapCoefficient(source2);
        }
        public static double OverlapCoefficient(this string source1, string source2) => Convert.ToDouble(source1.Intersect(source2).Count()) / Convert.ToDouble(Math.Min(source1.Length, source2.Length));
        public static float JaccardDistance(this string source1, string source2, bool isCaseSensitive = true)
        {
            if (!isCaseSensitive)
            {
                source1 = source1.ToLower();
                source2 = source2.ToLower();
            }
            return 1.0f - (float)source1.JaccardIndex(source2);
        }

        public static double JaccardIndex(this string source1, string source2) => Convert.ToDouble(source1.Intersect(source2).Count()) / Convert.ToDouble(source1.Union(source2).Count());
        // ToDo: Add the following distance functions to the enum list of DistanceMethods
        public static float SorensenDiceDistance(this string source1, string source2, bool isCaseSensitive = true)
        {
            if (!isCaseSensitive)
            {
                source1 = source1.ToLower();
                source2 = source2.ToLower();
            }
            return 1.0f - (float)source1.SorensenDiceIndex(source2);
        }
        public static double SorensenDiceIndex(this string source1, string source2) => 2 * Convert.ToDouble(source1.Intersect(source2).Count()) / Convert.ToDouble(source1.Length + source2.Length);
        public static float RatcliffObershelpSimilarityDistance(this string source1, string source2, bool isCaseSensitive = true)
        {
            if (!isCaseSensitive)
            {
                source1 = source1.ToLower();
                source2 = source2.ToLower();
            }
            return 1.0f - (float)source1.RatcliffObershelpSimilarity(source2);
        }
        public static double RatcliffObershelpSimilarity(this string source1, string source2) => 2 * Convert.ToDouble(source1.Intersect(source2).Count()) / Convert.ToDouble(source1.Length + source2.Length);
        public static float HammingDistance(this string source1, string source2, bool isCaseSensitive = true)
        {
            if (source1.Length != source2.Length) // Can only use HammingDiceDistance on string of equal length
                return -1.0f;
            if (!isCaseSensitive)
            {
                source1 = source1.ToLower();
                source2 = source2.ToLower();
            }
            return 1.0f - ((float)source1.Hamming(source2) / (float)source2.Length);
        }
        public static int Hamming(this string source1, string source2)
        {
            int distance = 0;
            for (int i = 0; i < source1.Length; i++)
                if (!source1[i].Equals(source2[i]))
                    distance++;
            return distance;
        }
        public static float LongestCommonSubstringDistance(this string source1, string source2, bool isCaseSensitive = true)
        {
            if (!isCaseSensitive)
            {
                source1 = source1.ToLower();
                source2 = source2.ToLower();
            }
            return 1.0f - ((float)source1.GetLongestCommonSubstring(source2).Length / (float)Math.Min(source1.Length, source2.Length));
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
        public static float LongestCommonSubsequenceDistance(this string source1, string source2, bool isCaseSensitive = true)
        {
            if (!isCaseSensitive)
            {
                source1 = source1.ToLower();
                source2 = source2.ToLower();
            }
            return 1.0f - ((float)source1.LongestCommonSubsequence(source2).Length / (float)Math.Min(source1.Length, source2.Length));
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
        public static float JaroDistance(this string source1, string source2, bool isCaseSensitive = true)
        {
            if (!isCaseSensitive)
            {
                source1 = source1.ToLower();
                source2 = source2.ToLower();
            }
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
            return (float)((m / source1.Length) + (m / source2.Length) + ((m - t) / m)) / 3;
        }
        public static float NormalizedLevenshteinDistance(this string source1, string source2, bool isCaseSensitive = true)
        {
            if (!isCaseSensitive)
            {
                source1 = source1.ToLower();
                source2 = source2.ToLower();
            }
            double distance = Convert.ToDouble(Levenshtein2.NormalizedLevenshteinDistance(source1, source2)) / Convert.ToDouble(Math.Max(source1.Length, source2.Length) - Levenshtein2.LevenshteinDistanceLowerBounds(source1, source2));
            return 1.0f - (float)distance;
        }
        public static float Levenshtein2Distance(this string source1, string source2, bool isCaseSensitive = true)
        {
            if (!isCaseSensitive)
            {
                source1 = source1.ToLower();
                source2 = source2.ToLower();
            }
            //double distance = Convert.ToDouble(Levenshtein2.LevenshteinDistance2(source1, source2)) / Convert.ToDouble(Levenshtein2.LevenshteinDistanceUpperBounds(source1, source2)); // LevenshteinDistanceUpperBounds Fails!!!!
            double distance = Convert.ToDouble(Levenshtein2.LevenshteinDistance2(source1, source2)) / Convert.ToDouble(Math.Max(source1.Length, source2.Length));
            return 1.0f - (float)distance;
        }
        public static float TanimotoCoefficientDistance(this string source1, string source2, bool isCaseSensitive = true)
        {
            if (!isCaseSensitive)
            {
                source1 = source1.ToLower();
                source2 = source2.ToLower();
            }
            return 1.0f - source1.TanimotoCoefficient(source2);
        }
        public static float TanimotoCoefficient(this string source1, string source2)
        {
            float Na = source1.Length;
            float Nb = source2.Length;
            float Nc = source1.Intersect(source2).Count();
            return Nc / (Na + Nb - Nc);
        }
        public static bool Caverphone(this string source1, string source2)
        {
            string[] source = {source1, source2};
            return CaverPhone.IsSimilar(source);
        }

        // Function to find the minimum number of operations to convert source1 to source2
        public static int EditDistance(string source1, string source2, bool isCaseSensitive = true)
        {
            if (!isCaseSensitive)
            {
                source1 = source1.ToLower();
                source2 = source2.ToLower();
            }
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
        // ToDo: Implement the following functions
        [System.Diagnostics.CodeAnalysis.SuppressMessage("Remove unused parameter", "IDE0060")]//      These functions are just place holders, so removing IntelliSense warning messages
        public static int SameFirstLastName(string source1, string source2, bool isCaseSensitive = true)
        {
            return 0;
        }
        [System.Diagnostics.CodeAnalysis.SuppressMessage("Remove unused parameter", "IDE0060")]
        public static int SamePhone(string source1, string source2, bool isCaseSensitive = true)
        {// Remove non-numeric characters, and remove first number if it starts with a 1
            return 0;
        }
        [System.Diagnostics.CodeAnalysis.SuppressMessage("Remove unused parameter", "IDE0060")]
        public static int SameSocial(string source1, string source2, bool isCaseSensitive = true)
        {// Remove non-numeric characters
            return 0;
        }
        [System.Diagnostics.CodeAnalysis.SuppressMessage("Remove unused parameter", "IDE0060")]
        public static int SameZip(string source1, string source2, bool isCaseSensitive = true)
        {
            return 0;
        }
        [System.Diagnostics.CodeAnalysis.SuppressMessage("Remove unused parameter", "IDE0060")]
        public static int SameAddress(string source1, string source2, bool isCaseSensitive = true)
        {
            return 0;
        }
        [System.Diagnostics.CodeAnalysis.SuppressMessage("Remove unused parameter", "IDE0060")]
        public static int SameDate(string source1, string source2, bool isCaseSensitive = true)
        {
            return 0;
        }
        [System.Diagnostics.CodeAnalysis.SuppressMessage("Remove unused parameter", "IDE0060")]
        public static int SameFileName(string source1, string source2, bool isCaseSensitive = true)
        {
            return 0;
        }
        [System.Diagnostics.CodeAnalysis.SuppressMessage("Remove unused parameter", "IDE0060")]
        public static int SameNumber(string source1, string source2, bool isCaseSensitive = true)
        {// Convert word numbers (five=5) to numbers, convert roman numbers, and remove non-numeric characters
            return 0;
        }
        #endregion Distance functions
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
        public static float PhraseHowSimilar(string source1, string source2)
        {
            string[] list1 = GetKeywordList(ref source1, false, true);
            string[] list2 = GetKeywordList(ref source2, false, true);
            float sourceLength = Math.Max(list1.Length, list2.Length);
            float diff = GetPhraseDifference(source1, source2,false, true);
            return diff == 0 ? 1.0f : (sourceLength - diff) / sourceLength;
        }
        public static bool IsPhraseSimilar(string source1, string source2, float desiredSimilarity) => PhraseHowSimilar(source1, source2) >= desiredSimilarity;
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
            if (!isCaseSensitive)
            {
                phrase1 = phrase1.ToLower();
                phrase2 = phrase2.ToLower();
            }
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
        public static class CosineSimilarity
        {
            /// <summary>
            /// Calculates the similarity percentage between two strings via Cosine Similarity. 
            /// </summary>
            /// <param name="source1">The first string.</param>
            /// <param name="source2">The second string.</param>
            /// <returns>The similarity percentage between the two strings. It's a number between 0 and 1 that represents how similar two strings are. The closer to 1, the more similar they are.</returns>
            public static float Percentage(string source1, string source2, bool isCaseSensitive = true) => (float)CalculateSimilarity(source1, source2, isCaseSensitive);
            public static double CalculateSimilarity(string source1, string source2, bool isCaseSensitive = true)
            {
                if (!isCaseSensitive)
                {
                    source1 = source1.ToLower();
                    source2 = source2.ToLower();
                }
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
        public static class LongestCommonSequence   // A class for comparing strings via the Longest Common Sequence algorithm
        {
            /// <summary>
            /// Calculates the similarity between two strings as a percentage.
            /// </summary>
            /// <param name="source1">The first string.</param>
            /// <param name="source2">The second string.</param>
            /// <returns>The similarity between the two strings as a percentage.</returns>
            public static float Percentage(string source1, string source2, bool isCaseSensitive = true) => (float)CalculateSimilarity(source1, source2, isCaseSensitive);
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
                if (!isCaseSensitive)
                {
                    source1 = source1.ToLower();
                    source2 = source2.ToLower();
                }
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
    public static class JaccardSimilarity
    {
        /// <summary>
        /// Calculates the similarity percentage between two strings via Jaccard Similarity
        /// </summary>
        /// <param name="source1">The first string.</param>
        /// <param name="source2">The second string.</param>
        /// <returns>The similarity percentage between the two strings.</returns>
        public static float Percentage(string source1, string source2, bool isCaseSensitive = true) => (float)CalculateSimilarity(source1, source2, isCaseSensitive);
        public static float CalculateSimilarity(string source1, string source2, bool isCaseSensitive = true)
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
            float originalCount1 = hashSet1.Count;
            hashSet1.IntersectWith(hashSet2);
            float intersectionCount = hashSet1.Count;
            float unionCount = originalCount1 + hashSet2.Count - intersectionCount;
            return (float)intersectionCount / unionCount;
        }
    }
    /// <summary>
    /// A class for comparing strings via the Needleman-Wunsch algorithm
    /// </summary>
    public static class NeedlemanWunsch
    {
        /// <summary>
        /// Calculates the similarity percentage between two strings using the Needleman-Wunsch algorithm.
        /// </summary>
        /// <param name="source1">The first string.</param>
        /// <param name="source2">The second string.</param>
        /// <returns>The similarity percentage between the two strings.</returns>
        public static float Percentage(string source1, string source2, bool isCaseSensitive = true)
        {
            if (!isCaseSensitive)
            {
                source1 = source1.ToLower();
                source2 = source2.ToLower();
            }
            if (source1 == source2)
                return 1.0f;
            int similarityScore = CalculateSimilarity(source1, source2);
            float maxPossibleScore = Math.Max(source1.Length, source2.Length);
            float similarityPercentage = 1 - (similarityScore / maxPossibleScore);
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
    public class CaverPhone
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
    #endregion Fuzzy classes
}
// Goals for supporting distance algorithms 
//       BlockDistance
//       ChapmanLengthDeviation
//       ChapmanMeanLength
//       *CosineSimilarity
//       DiceSimilarity
//       EuclideanDistance
//       *JaccardSimilarity
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
