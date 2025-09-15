using FuzzyPlusCSharp.StringMatchingAlgorithms;

using Phonix;

using System;
using System.Diagnostics;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Security.Cryptography;
using System.Text;
using System.Text.RegularExpressions;

using static FuzzyPlusCSharp.Fuzzy;

namespace FuzzyPlusCSharp
{
    #region Non-Static version
    [ComVisible(true)]
    [Guid("03e496b7-1f0c-4699-b7fc-cf32bb949b75")]
    [InterfaceType(ComInterfaceType.InterfaceIsIDispatch)] // Or InterfaceIsDual, InterfaceIsIDispatch, InterfaceIsIUnknown
    public interface IQueueFuzzy
    {
        bool IsVerySimilar(string source1, string source2); // Is 90% similar
        bool IsSimilar(string source1, string source2); // Is 75% similar
        bool IsSomeWhatSimilar(string source1, string source2); // Is 50% similar
        bool IsSlightlySimilar(string source1, string source2); // Is 30% similar
        bool IsHardlySimilar(string source1, string source2); // Is 10% similar
        bool IsMatch(string source1, string source2, double desiredSimilarity);
        double HowSimilar(string source1, string source2);
        bool IsNotSimilar(string source1, string source2);
        double Distance(string source1, string source2);
    }
    [ComVisible(true)]
    [Guid("812e2762-82ed-4772-a7b8-443e14ee70a4")]
    [ClassInterface(ClassInterfaceType.None)]
    public class FuzzyInst : IQueueFuzzy
    {
        private readonly Fuzzy.StringMatchingAlgorithm_ID stringMatchingAlgorithm = Fuzzy.StringMatchingAlgorithm_ID.iDamerauLevenshtein;
        public FuzzyInst(Fuzzy.StringMatchingAlgorithm_ID stringMatchingAlgorithm = Fuzzy.StringMatchingAlgorithm_ID.iDamerauLevenshtein)
        {
            this.stringMatchingAlgorithm = stringMatchingAlgorithm;
        }
        public bool IsVerySimilar(string source1, string source2) => Fuzzy.IsMatch(source1, source2, Fuzzy.ISVERYSIMILAR, stringMatchingAlgorithm); // Is 90% similar
        public bool IsSimilar(string source1, string source2) => Fuzzy.IsMatch(source1, source2, Fuzzy.ISSIMILAR, stringMatchingAlgorithm); // Is 75% similar
        public bool IsSomeWhatSimilar(string source1, string source2) => Fuzzy.IsMatch(source1, source2, Fuzzy.ISSOMEWHATSIMILAR, stringMatchingAlgorithm); // Is 50% similar
        public bool IsSlightlySimilar(string source1, string source2) => Fuzzy.IsMatch(source1, source2, Fuzzy.ISSLIGHTLYSIMILAR, stringMatchingAlgorithm); // Is 30% similar
        public bool IsHardlySimilar(string source1, string source2) => Fuzzy.IsMatch(source1, source2, Fuzzy.ISHARDLYSIMILAR, stringMatchingAlgorithm); // Is 10% similar
        public bool IsMatch(string source1, string source2, double desiredSimilarity) => Fuzzy.HowSimilar(source1, source2, stringMatchingAlgorithm) >= desiredSimilarity;
        public double HowSimilar(string source1, string source2) => Fuzzy.HowSimilar(source1, source2, stringMatchingAlgorithm);
        public bool IsNotSimilar(string source1, string source2) => Fuzzy.IsNotSimilar(source1, source2, stringMatchingAlgorithm);
        public double Distance(string source1, string source2) => Fuzzy.Distance(source1, source2, stringMatchingAlgorithm);
    }
    [ComVisible(true)]
    [Guid("af9140d6-1ace-41d1-9be4-770d2c20b1f5")]
    [InterfaceType(ComInterfaceType.InterfaceIsIDispatch)] // Or InterfaceIsDual, InterfaceIsIDispatch, InterfaceIsIUnknown
    public interface IQueuePhonetic
    {
        bool SameSound(string source1, string source2);
    }
    [ComVisible(true)]
    [Guid("e21e828e-1e0f-4b26-9479-dc6e8ccb715d")]
    [ClassInterface(ClassInterfaceType.None)]
    public class PhoneticInst : IQueuePhonetic
    {
        private readonly Fuzzy.SameSoundMethod sameSoundMethod = Fuzzy.SameSoundMethod.UseDefaultSameSoundMethod;
        public PhoneticInst(Fuzzy.SameSoundMethod sameSoundMethod = Fuzzy.SameSoundMethod.UseDefaultSameSoundMethod)
        {
            this.sameSoundMethod = sameSoundMethod;
        }
        public bool SameSound(string source1, string source2) => Fuzzy.SameSound(source1, source2, sameSoundMethod);

    }
    #endregion Non-Static version
    //////////////////////////////////////////////////////////////////////
    /// Static version 
    [ComVisible(true)]
    [Guid("9576a745-53b4-4ffa-97c5-a9075a0b5498")]
    [ClassInterface(ClassInterfaceType.None)]
    public static class Fuzzy
    {
        #region Constants
        public const double ISVERYSIMILAR = 0.9f;
        public const double ISSIMILAR = 0.75f;
        public const double ISSOMEWHATSIMILAR = 0.5f;
        public const double ISSLIGHTLYSIMILAR = 0.3f;
        public const double ISHARDLYSIMILAR = 0.1f;
        // Constants for string matching algorithms
        public const int QUANTITY_MAX_ALGORITHMS_PER_GROUP = 32;
        public const int SEQUENCE_ALIGNMENT_ALGORITHMS = QUANTITY_MAX_ALGORITHMS_PER_GROUP;
        public const int TOKEN_STRING_MATCHING_ALGORITHMS = SEQUENCE_ALIGNMENT_ALGORITHMS + QUANTITY_MAX_ALGORITHMS_PER_GROUP;
        public const int HYBRID_STRING_MATCHING_ALGORITHMS = TOKEN_STRING_MATCHING_ALGORITHMS + QUANTITY_MAX_ALGORITHMS_PER_GROUP;
        public const int HASH_STRING_MATCHING_ALGORITHMS = HYBRID_STRING_MATCHING_ALGORITHMS + QUANTITY_MAX_ALGORITHMS_PER_GROUP;
        public const int CASE_INSENSITIVE_STRING_MATCHING_ALGORITHMS = 512;
        public const int CPP_ONLY_FUZZY_ALGORITHM_IMPLEMENTATION = CASE_INSENSITIVE_STRING_MATCHING_ALGORITHMS - (QUANTITY_MAX_ALGORITHMS_PER_GROUP * 2);
        public const int PHRASE_STRING_MATCHING_ALGORITHMS = CPP_ONLY_FUZZY_ALGORITHM_IMPLEMENTATION - QUANTITY_MAX_ALGORITHMS_PER_GROUP;
        public const int BAD_STRING_MATCHING_ALGORITHMS = CASE_INSENSITIVE_STRING_MATCHING_ALGORITHMS - QUANTITY_MAX_ALGORITHMS_PER_GROUP;
        public const int STRING_MATCHING_ALGORITHMS_UP_FOR_DELETION = BAD_STRING_MATCHING_ALGORITHMS + (QUANTITY_MAX_ALGORITHMS_PER_GROUP / 2);
        // Phonetic associated algorithms constants
        public const int PHONETIC_ALGORITHMS = 16384;
        public const int MICROSOFT_PHONETIC_ALGORITHMS = PHONETIC_ALGORITHMS + (QUANTITY_MAX_ALGORITHMS_PER_GROUP * 2);
        public const int CPP_ONLY_PHONETIC_ALGORITHMS = PHONETIC_ALGORITHMS + CPP_ONLY_FUZZY_ALGORITHM_IMPLEMENTATION;
        public const int HASH_UTF8_ENCODE = 32;
        #endregion Constants
        #region Distance, Phonetic class, and misc variable members
        // Distance classes
        public static StringMatchingAlgorithms.BlockDistance blockDistance = new StringMatchingAlgorithms.BlockDistance();
        public static StringMatchingAlgorithms.ChapmanLengthDeviation chapmanLengthDeviation = new StringMatchingAlgorithms.ChapmanLengthDeviation();
        public static StringMatchingAlgorithms.ChapmanMeanLength chapmanMeanLength = new StringMatchingAlgorithms.ChapmanMeanLength();
        public static StringMatchingAlgorithms.EuclideanDistance euclideanDistance = new StringMatchingAlgorithms.EuclideanDistance();
        public static StringMatchingAlgorithms.MatchingCoefficient matchingCoefficient = new StringMatchingAlgorithms.MatchingCoefficient();
        public static StringMatchingAlgorithms.MongeElkan mongeElkan = new StringMatchingAlgorithms.MongeElkan();
        public static StringMatchingAlgorithms.QGramsDistance qGramsDistance = new StringMatchingAlgorithms.QGramsDistance();
        public static StringMatchingAlgorithms.SmithWaterman smithWaterman = new StringMatchingAlgorithms.SmithWaterman();
        public static StringMatchingAlgorithms.SmithWatermanGotoh smithWatermanGotoh = new StringMatchingAlgorithms.SmithWatermanGotoh();
        public static StringMatchingAlgorithms.SmithWatermanGotohWindowedAffine smithWatermanGotohWindowedAffine = new StringMatchingAlgorithms.SmithWatermanGotohWindowedAffine();
        public static StringMatchingAlgorithms.DiceSimilarity diceSimilarity = new StringMatchingAlgorithms.DiceSimilarity();
        public static StringMatchingAlgorithms.NGramsDistance nGramsDistance = new StringMatchingAlgorithms.NGramsDistance();
        // Phonetic classes
        public static MatchRatingApproach matchRatingApproach = new MatchRatingApproach();
        public static Metaphone metaphone = new Metaphone();
        public static CaverPhone caverPhonePhonix = new CaverPhone();
        public static Phonix.Soundex soundexPhonix = new Phonix.Soundex();
        public static DoubleMetaphone doubleMetaphone = new DoubleMetaphone();
        public static SQLite.SQLiteConnection connection = null;
        public static SQLite.SQLiteConnection virtualConnection = null;
        #endregion Distance, Phonetic class, and misc variable members
        #region StringMatchingAlgorithm_ID definitions
        public enum StringMatchingAlgorithm_ID
        {
            // Each group starts with a constant, so that new algorithms can be added without causing all the enum's to get renumbered.
            UseDefaultStringMatchingAlgorithm = 0,
            // Edit Distance Based Methods
            Levenshtein,
            DamerauLevenshtein,
            JaroWinkler,
            HammingDistance,
            JaroDistance,
            NormalizedLevenshteinDistance,
            Levenshtein2Distance,
            ChapmanLengthDeviation,
            EuclideanDistance,

            // Sequence Alignment Based Methods
            LongestCommonSequence = SEQUENCE_ALIGNMENT_ALGORITHMS,
            NeedlemanWunsch, 
            RatcliffObershelpSimilarityDistance, 
            LongestCommonSubstringDistance, 
            LongestCommonSubsequenceDistance, 
            SmithWaterman, 
            SmithWatermanGotoh, 
            SmithWatermanGotohWindowedAffine, 

            // Token Based Methods
            CosineSimilarity = TOKEN_STRING_MATCHING_ALGORITHMS,
            JaccardSimilarity, // ToDo: JaccardSimilarity, JaccardIndex, and TanimotoCoefficientDistance are most likely the same logic.  Remove the duplicates
            JaccardIndex,
            TanimotoCoefficientDistance,
            OverlapCoefficient,
            SorensenDiceDistance,
            DiceSimilarity, 
            BlockDistance,
            MatchingCoefficient,
            QGramsDistance,
            NGramsDistance,
            TverskyIndex_DO_NOT_USE, //Warning: There is NO implementation for this algorithm.  This is just a placeholder
            DO_NOT_USE_PlaceHolder1, // This is a place holder for possible future algorithm. Do not use this enum!
            DO_NOT_USE_PlaceHolder2, // This is a place holder for possible future algorithm. Do not use this enum!
            DO_NOT_USE_PlaceHolder3, // This is a place holder for possible future algorithm. Do not use this enum!

            // Hybrid Algorithms
            MongeElkan = HYBRID_STRING_MATCHING_ALGORITHMS,
            Sift4,
            GeneralizedCompressionDistance_DO_NOT_USE, //Warning: There is NO implementation for this algorithm.  This is just a placeholder
            DO_NOT_USE_PlaceHolder4, // This is a place holder for possible future algorithm. Do not use this enum!
            DO_NOT_USE_PlaceHolder5, // This is a place holder for possible future algorithm. Do not use this enum!
            DO_NOT_USE_PlaceHolder6, // This is a place holder for possible future algorithm. Do not use this enum!

            // String Hash Based
            SimHash = HASH_STRING_MATCHING_ALGORITHMS, // This algorithm is still in development phase.
            MinHash_DO_NOT_USE, //Warning: There is NO implementation for this algorithm.  This is just a placeholder
            DO_NOT_USE_PlaceHolder7, // This is a place holder for possible future algorithm. Do not use this enum!
            DO_NOT_USE_PlaceHolder8, // This is a place holder for possible future algorithm. Do not use this enum!
            DO_NOT_USE_PlaceHolder9, // This is a place holder for possible future algorithm. Do not use this enum!

            // Phrase token methods which are all case insensitive only
            PhraseTokenize = PHRASE_STRING_MATCHING_ALGORITHMS,
            SimplePhraseTokenize,

            // ------------------------------------------------------------
            // These functions are NOT supported by CSharp Fuzzy class code, and are only here for C++ SqliteFuzzyPlusExtension usage.
            // Sqlean Fuzzy external functions. 
            Fuzzy_Damlev = CPP_ONLY_FUZZY_ALGORITHM_IMPLEMENTATION, // Edit Distance Based
            Fuzzy_Hamming,// Edit Distance Based
            Fuzzy_Jarowin, // Edit Distance Based
            Fuzzy_Leven, // Edit Distance Based
            Fuzzy_Osadist,
            Fuzzy_Editdist, // Edit Distance Based
            Fuzzy_Jaro,// Edit Distance Based
            // Other C++ (external) only functions. (NOT part of Sqlean)
            EdlibDistance,// Edit Distance Based
            // ------------------------------------------------------------

            // Bad distance methods (C# and C++)
            // These method(s) are only here for comparisons and testing purposes
            ChapmanMeanLength = BAD_STRING_MATCHING_ALGORITHMS, // Edit Distance Based // Distance method from SimMetricsCore
            
            // EditDistance may get removed, replaced, or logic change 
            EditDistance = STRING_MATCHING_ALGORITHMS_UP_FOR_DELETION,

            //This is NOT a fuzzy method. It's for functions that accepts a comparison argument.
            ExactMatch = CASE_INSENSITIVE_STRING_MATCHING_ALGORITHMS -1,

            ////////////////////////////////////////////////////////////////////////////
            // ToDo: Sort below case insensitive enums in the same order as above
            // Case INSENSITIVE versions
            iLevenshtein = CASE_INSENSITIVE_STRING_MATCHING_ALGORITHMS + Levenshtein,
            iDamerauLevenshtein,
            iJaroWinkler,
            iHammingDistance,
            iJaroDistance,
            iNormalizedLevenshteinDistance,
            iLevenshtein2Distance,
            iChapmanLengthDeviation,
            iEuclideanDistance,

            // Sequence Alignment Based Methods
            iLongestCommonSequence = CASE_INSENSITIVE_STRING_MATCHING_ALGORITHMS + LongestCommonSequence,
            iNeedlemanWunsch,
            iRatcliffObershelpSimilarityDistance,
            iLongestCommonSubstringDistance,
            iLongestCommonSubsequenceDistance,
            iSmithWaterman,
            iSmithWatermanGotoh,
            iSmithWatermanGotohWindowedAffine,

            // Token Based Methods
            iCosineSimilarity = CASE_INSENSITIVE_STRING_MATCHING_ALGORITHMS + CosineSimilarity,
            iJaccardSimilarity, // ToDo: JaccardSimilarity, JaccardIndex, and TanimotoCoefficientDistance are most likely the same logic.  Remove the duplicates
            iJaccardIndex,
            iTanimotoCoefficientDistance,
            iOverlapCoefficient,
            iSorensenDiceDistance,
            iDiceSimilarity,
            iBlockDistance,
            iMatchingCoefficient,
            iQGramsDistance,
            iNGramsDistance,
            iTverskyIndex_DO_NOT_USE, //Warning: There is NO implementation for this algorithm.  This is just a placeholder
            iDO_NOT_USE_PlaceHolder1, // This is a place holder for possible future algorithm. Do not use this enum!
            iDO_NOT_USE_PlaceHolder2, // This is a place holder for possible future algorithm. Do not use this enum!
            iDO_NOT_USE_PlaceHolder3, // This is a place holder for possible future algorithm. Do not use this enum!

            // Hybrid Algorithms
            iMongeElkan = CASE_INSENSITIVE_STRING_MATCHING_ALGORITHMS + MongeElkan,
            iSift4,
            iGeneralizedCompressionDistance_DO_NOT_USE, //Warning: There is NO implementation for this algorithm.  This is just a placeholder
            iDO_NOT_USE_PlaceHolder4, // This is a place holder for possible future algorithm. Do not use this enum!
            iDO_NOT_USE_PlaceHolder5, // This is a place holder for possible future algorithm. Do not use this enum!
            iDO_NOT_USE_PlaceHolder6, // This is a place holder for possible future algorithm. Do not use this enum!

            // String Hash Based
            iSimHash = CASE_INSENSITIVE_STRING_MATCHING_ALGORITHMS + SimHash, // This algorithm is still in development phase.
            iMinHash_DO_NOT_USE, //Warning: There is NO implementation for this algorithm.  This is just a placeholder
            iDO_NOT_USE_PlaceHolder7, // This is a place holder for possible future algorithm. Do not use this enum!
            iDO_NOT_USE_PlaceHolder8, // This is a place holder for possible future algorithm. Do not use this enum!
            iDO_NOT_USE_PlaceHolder9, // This is a place holder for possible future algorithm. Do not use this enum!

            // Bad distance methods (C# and C++)
            // These method(s) are only here for comparisons and testing purposes
            iChapmanMeanLength = CASE_INSENSITIVE_STRING_MATCHING_ALGORITHMS + ChapmanMeanLength,

            // METHODS UP FOR DELETION
            iEditDistance = CASE_INSENSITIVE_STRING_MATCHING_ALGORITHMS + EditDistance,
        }
        public static StringMatchingAlgorithm_ID DefaultStringMatchingAlgorithm { get; private set; } = StringMatchingAlgorithm_ID.iDamerauLevenshtein;

        public static void SetDefaultStringMatchingAlgorithm(StringMatchingAlgorithm_ID stringMatchingAlgorithm) => DefaultStringMatchingAlgorithm = stringMatchingAlgorithm;
        public static StringMatchingAlgorithm_ID GetStringMatchingAlgorithm(int stringMatchingAlgorithm_ID) => (StringMatchingAlgorithm_ID)stringMatchingAlgorithm_ID;
        public static StringMatchingAlgorithm_ID GetStringMatchingAlgorithm(string stringMatchingAlgorithm_Name)
        { // This function is for SQLite extension purposes, and should only be called once!!!
            StringMatchingAlgorithm_ID stringMatchingAlgorithm = DefaultStringMatchingAlgorithm;
            if (stringMatchingAlgorithm_Name != null && !stringMatchingAlgorithm_Name.Equals("UseDefaultStringMatchingAlgorithm", StringComparison.OrdinalIgnoreCase))
            {
                try
                {
                    stringMatchingAlgorithm = (StringMatchingAlgorithm_ID)Enum.Parse(typeof(StringMatchingAlgorithm_ID), stringMatchingAlgorithm_Name, true);
                }
                catch
                {
                    try
                    {
                        int soundEnum = (int)Enum.Parse(typeof(SameSoundMethod), stringMatchingAlgorithm_Name, true);
                        return (StringMatchingAlgorithm_ID)soundEnum;
                    }
                    catch
                    { // ToDo: add error console logging here.
                    }
                }
            }
            return stringMatchingAlgorithm;
        }
        public static bool SetDefaultStringMatchingAlgorithm(int stringMatchingAlgorithm_ID) // This function is to let SQL access setting default method
        {
            DefaultStringMatchingAlgorithm = (StringMatchingAlgorithm_ID)stringMatchingAlgorithm_ID;
            return true;
        }
        public static bool SetDefaultStringMatchingAlgorithm(string stringMatchingAlgorithm_Name)
        { // This function is to let SQL access setting default method by using the distance method name explicitly.
            //But this should only be called once. If repetitive calls are required, use ID method instead.
            DefaultStringMatchingAlgorithm = GetStringMatchingAlgorithm(stringMatchingAlgorithm_Name);
            return true;
        }
        public static string GetStringMatchingAlgorithmName(int stringMatchingAlgorithm_ID)
        {
            StringMatchingAlgorithm_ID stringMatchingAlgorithm = GetStringMatchingAlgorithm(stringMatchingAlgorithm_ID);
            return stringMatchingAlgorithm.ToString();
        }
        public enum IncompleteOrPlaceHolderStringMatchingAlgorithm_ID
        {
            None = 0,
            TverskyIndex_DO_NOT_USE = StringMatchingAlgorithm_ID.TverskyIndex_DO_NOT_USE,
            GeneralizedCompressionDistance_DO_NOT_USE = StringMatchingAlgorithm_ID.GeneralizedCompressionDistance_DO_NOT_USE,
            //SimHash_DO_NOT_USE = StringMatchingAlgorithm_ID.SimHash_DO_NOT_USE,
            MinHash_DO_NOT_USE = StringMatchingAlgorithm_ID.MinHash_DO_NOT_USE,
            iTverskyIndex_DO_NOT_USE = StringMatchingAlgorithm_ID.iTverskyIndex_DO_NOT_USE,
            iGeneralizedCompressionDistance_DO_NOT_USE = StringMatchingAlgorithm_ID.iGeneralizedCompressionDistance_DO_NOT_USE,
            //iSimHash_DO_NOT_USE = StringMatchingAlgorithm_ID.iSimHash_DO_NOT_USE,
            iMinHash_DO_NOT_USE = StringMatchingAlgorithm_ID.iMinHash_DO_NOT_USE,
            DO_NOT_USE_PlaceHolder1 = StringMatchingAlgorithm_ID.DO_NOT_USE_PlaceHolder1,
            DO_NOT_USE_PlaceHolder2 = StringMatchingAlgorithm_ID.DO_NOT_USE_PlaceHolder2,
            DO_NOT_USE_PlaceHolder3 = StringMatchingAlgorithm_ID.DO_NOT_USE_PlaceHolder3,
            DO_NOT_USE_PlaceHolder4 = StringMatchingAlgorithm_ID.DO_NOT_USE_PlaceHolder4,
            DO_NOT_USE_PlaceHolder5 = StringMatchingAlgorithm_ID.DO_NOT_USE_PlaceHolder5,
            DO_NOT_USE_PlaceHolder6 = StringMatchingAlgorithm_ID.DO_NOT_USE_PlaceHolder6,
            DO_NOT_USE_PlaceHolder7 = StringMatchingAlgorithm_ID.DO_NOT_USE_PlaceHolder7,
            DO_NOT_USE_PlaceHolder8 = StringMatchingAlgorithm_ID.DO_NOT_USE_PlaceHolder8,
            DO_NOT_USE_PlaceHolder9 = StringMatchingAlgorithm_ID.DO_NOT_USE_PlaceHolder9,
            iDO_NOT_USE_PlaceHolder1 = StringMatchingAlgorithm_ID.iDO_NOT_USE_PlaceHolder1,
            iDO_NOT_USE_PlaceHolder2 = StringMatchingAlgorithm_ID.iDO_NOT_USE_PlaceHolder2,
            iDO_NOT_USE_PlaceHolder3 = StringMatchingAlgorithm_ID.iDO_NOT_USE_PlaceHolder3,
            iDO_NOT_USE_PlaceHolder4 = StringMatchingAlgorithm_ID.iDO_NOT_USE_PlaceHolder4,
            iDO_NOT_USE_PlaceHolder5 = StringMatchingAlgorithm_ID.iDO_NOT_USE_PlaceHolder5,
            iDO_NOT_USE_PlaceHolder6 = StringMatchingAlgorithm_ID.iDO_NOT_USE_PlaceHolder6,
            iDO_NOT_USE_PlaceHolder7 = StringMatchingAlgorithm_ID.iDO_NOT_USE_PlaceHolder7,
            iDO_NOT_USE_PlaceHolder8 = StringMatchingAlgorithm_ID.iDO_NOT_USE_PlaceHolder8,
            iDO_NOT_USE_PlaceHolder9 = StringMatchingAlgorithm_ID.iDO_NOT_USE_PlaceHolder9,
        }
        public static bool IsInOp_StringMatchingAlgorithm(int stringMatchingAlgorithm_ID)
        { // This function and associated enum is for the automated unit testing program which creates SQL statements.
            string stringMatchingAlgorithm_name = GetStringMatchingAlgorithmName(stringMatchingAlgorithm_ID);
            IncompleteOrPlaceHolderStringMatchingAlgorithm_ID id = GetIncompleteOrPlaceHolderStringMatchingAlgorithm(stringMatchingAlgorithm_name);
            return id != IncompleteOrPlaceHolderStringMatchingAlgorithm_ID.None;
        }
        public static IncompleteOrPlaceHolderStringMatchingAlgorithm_ID GetIncompleteOrPlaceHolderStringMatchingAlgorithm(string stringMatchingAlgorithm_Name)
        {
            IncompleteOrPlaceHolderStringMatchingAlgorithm_ID stringMatchingAlgorithm = IncompleteOrPlaceHolderStringMatchingAlgorithm_ID.None;
            if (stringMatchingAlgorithm_Name != null)
            {
                try
                {
                    stringMatchingAlgorithm = (IncompleteOrPlaceHolderStringMatchingAlgorithm_ID)Enum.Parse(typeof(IncompleteOrPlaceHolderStringMatchingAlgorithm_ID), stringMatchingAlgorithm_Name, true);
                }
                catch
                {
                }
            }
            return stringMatchingAlgorithm;
        }
        #endregion StringMatchingAlgorithm_ID definitions
        #region SameSoundMethod
        public enum SameSoundMethod
        {
            UseDefaultSameSoundMethod = PHONETIC_ALGORITHMS,
            SoundexPhonix, // Default SameSound method
            CaverPhonePhonix,
            MatchRatingApproach,
            Metaphone,
            DoubleMetaphone,
            ColognePhonetics,
            SoundexVer2,
            EnPhoneticDistance = MICROSOFT_PHONETIC_ALGORITHMS,
            // ------------------------------------------------------------
            // These functions are NOT supported by CSharp Fuzzy class code, and are only here for C++ SqliteFuzzyPlusExtension usage.
            // SQLean phonetic external functions. 
            Fuzzy_Soundex = CPP_ONLY_PHONETIC_ALGORITHMS,
            Fuzzy_Caver,
            Fuzzy_Rsoundex,  //Refined Soundex
            Fuzzy_Phonetic,
            Fuzzy_Translit //Transliteration
        }
        public static SameSoundMethod DefaultSameSoundMethod { get; private set; } = SameSoundMethod.SoundexPhonix;
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
        #region PercentDecimalDigits
        public static int PercentDecimalDigits { get; private set; } = 2;
        public static void SetPercentDecimalDigits(int precision) => PercentDecimalDigits = precision;
        public static double GetPercentWithFixedDecimalDigits(double value) => PercentDecimalDigits < 0 ? value : Math.Round(value, PercentDecimalDigits);
        #endregion PercentDecimalDigits
        #region Similarity functions
        public static bool IsMatch(string source1, string source2, double desiredSimilarity, StringMatchingAlgorithm_ID stringMatchingAlgorithm = StringMatchingAlgorithm_ID.UseDefaultStringMatchingAlgorithm) => HowSimilar(source1, source2, stringMatchingAlgorithm) >= desiredSimilarity;
        // The following HowSimilar method is to let SQLite access to HowSimilar
        public static bool IsCaseSensitive(StringMatchingAlgorithm_ID stringMatchingAlgorithm) => (int)stringMatchingAlgorithm < CASE_INSENSITIVE_STRING_MATCHING_ALGORITHMS;
        public static void FixIfIsCaseSensitive(ref string source1, ref string source2, bool isCaseSensitive)
        {
            if (!isCaseSensitive)
            {
                source1 = source1.ToLower();
                source2 = source2.ToLower();
            }
        }
        public static double HowSimilar(string source1, string source2, int stringMatchingAlgorithm) => HowSimilar(source1, source2, GetStringMatchingAlgorithm(stringMatchingAlgorithm));
        public static double HowSimilar(string source1, string source2, string stringMatchingAlgorithm) => HowSimilar(source1, source2, GetStringMatchingAlgorithm(stringMatchingAlgorithm));
        public static double HowSimilar(string source1, string source2, StringMatchingAlgorithm_ID stringMatchingAlgorithm = StringMatchingAlgorithm_ID.UseDefaultStringMatchingAlgorithm)
        {
            if (stringMatchingAlgorithm == StringMatchingAlgorithm_ID.UseDefaultStringMatchingAlgorithm)
                stringMatchingAlgorithm = DefaultStringMatchingAlgorithm;
            bool isCaseSensitive = IsCaseSensitive(stringMatchingAlgorithm);
            IDistance i = GetIDistance(stringMatchingAlgorithm);
            Debug.Assert(i != null);
            return i.Percentage(source1, source2, isCaseSensitive);
        }
        public static double Distance(string source1, string source2, StringMatchingAlgorithm_ID stringMatchingAlgorithm = StringMatchingAlgorithm_ID.UseDefaultStringMatchingAlgorithm)
        {
            if (stringMatchingAlgorithm == StringMatchingAlgorithm_ID.UseDefaultStringMatchingAlgorithm)
                stringMatchingAlgorithm = DefaultStringMatchingAlgorithm;
            bool isCaseSensitive = IsCaseSensitive(stringMatchingAlgorithm);
            IDistance i = GetIDistance(stringMatchingAlgorithm);
            Debug.Assert(i != null);
            return i.Distance(source1, source2, isCaseSensitive);
        }
        public static double Distance(string source1, string source2, int stringMatchingAlgorithm) => Distance(source1, source2, GetStringMatchingAlgorithm(stringMatchingAlgorithm));
        public static double Distance(string source1, string source2, string stringMatchingAlgorithm) => Distance(source1, source2, GetStringMatchingAlgorithm(stringMatchingAlgorithm));
        public static bool IsNotSimilar(string source1, string source2) => IsNotSimilar(source1, source2, StringMatchingAlgorithm_ID.UseDefaultStringMatchingAlgorithm);
        public static bool IsNotSimilar(string source1, string source2, StringMatchingAlgorithm_ID stringMatchingAlgorithm)
        {
            if (stringMatchingAlgorithm == StringMatchingAlgorithm_ID.UseDefaultStringMatchingAlgorithm)
                stringMatchingAlgorithm = DefaultStringMatchingAlgorithm;
            bool isCaseSensitive = IsCaseSensitive(stringMatchingAlgorithm);
            IDistance i = GetIDistance(stringMatchingAlgorithm);
            Debug.Assert(i != null);
            return i != null && i.Percentage(source1, source2, isCaseSensitive) == 0;
        }
        public static bool IsNotSimilarByID(string source1, string source2, int id) => IsNotSimilar(source1, source2, (StringMatchingAlgorithm_ID)id);
        public static bool IsVerySimilar(string source1, string source2) => IsVerySimilar(source1, source2, StringMatchingAlgorithm_ID.UseDefaultStringMatchingAlgorithm);
        public static bool IsVerySimilar(string source1, string source2, StringMatchingAlgorithm_ID stringMatchingAlgorithm) => IsMatch(source1, source2, Fuzzy.ISVERYSIMILAR, stringMatchingAlgorithm); // Is 90% similar
        public static bool IsSimilar(string source1, string source2) => IsSimilar(source1, source2, StringMatchingAlgorithm_ID.UseDefaultStringMatchingAlgorithm);
        public static bool IsSimilar(string source1, string source2, StringMatchingAlgorithm_ID stringMatchingAlgorithm) => IsMatch(source1, source2, Fuzzy.ISSIMILAR, stringMatchingAlgorithm); // Is 75% similar
        public static bool IsSomeWhatSimilar(string source1, string source2) => IsSomeWhatSimilar(source1, source2, StringMatchingAlgorithm_ID.UseDefaultStringMatchingAlgorithm);
        public static bool IsSomeWhatSimilar(string source1, string source2, StringMatchingAlgorithm_ID stringMatchingAlgorithm) => IsMatch(source1, source2, Fuzzy.ISSOMEWHATSIMILAR, stringMatchingAlgorithm); // Is 50% similar
        public static bool IsSlightlySimilar(string source1, string source2) => IsSlightlySimilar(source1, source2, StringMatchingAlgorithm_ID.UseDefaultStringMatchingAlgorithm);
        public static bool IsSlightlySimilar(string source1, string source2, StringMatchingAlgorithm_ID stringMatchingAlgorithm) => IsMatch(source1, source2, Fuzzy.ISSLIGHTLYSIMILAR, stringMatchingAlgorithm); // Is 30% similar
        public static bool IsHardlySimilar(string source1, string source2) => IsHardlySimilar(source1, source2, StringMatchingAlgorithm_ID.UseDefaultStringMatchingAlgorithm);
        public static bool IsHardlySimilar(string source1, string source2, StringMatchingAlgorithm_ID stringMatchingAlgorithm) => IsMatch(source1, source2, Fuzzy.ISHARDLYSIMILAR, stringMatchingAlgorithm); // Is 10% similar
        public static bool IsSimilar(string source1, string source2, int id)
        {
            return id < PHONETIC_ALGORITHMS
                ? IsSimilar(source1, source2, GetStringMatchingAlgorithm(id))
                : IsSimilar(source1, source2, GetSameSoundMethod(id));
        }
        public static bool IsSimilarByID(string source1, string source2, int id) => IsSimilar(source1, source2, id);
        public static bool IsSomeWhatSimilarByID(string source1, string source2, int id) => IsSomeWhatSimilar(source1, source2, (StringMatchingAlgorithm_ID)id);
        public static bool IsSlightlySimilarByID(string source1, string source2, int id) => IsSlightlySimilar(source1, source2, (StringMatchingAlgorithm_ID)id);
        public static bool IsHardlySimilarByID(string source1, string source2, int id) => IsHardlySimilar(source1, source2, (StringMatchingAlgorithm_ID)id);
        public static bool IsVerySimilar(string source1, string source2, int id)
        {
            return id < PHONETIC_ALGORITHMS
                ? IsVerySimilar(source1, source2, GetStringMatchingAlgorithm(id))
                : IsVerySimilar(source1, source2, GetSameSoundMethod(id));
        }
        public static bool IsVerySimilarByID(string source1, string source2, int id) => IsVerySimilar(source1, source2, id);
        // GetIDistance should NOT be used until all associated classes have implementation for Percentage and Distance methods.
        // Classes that do NOT begin with an I, are classes which need work on these methods.
        public static IDistance GetIDistance(StringMatchingAlgorithm_ID stringMatchingAlgorithm)
        {
            if (stringMatchingAlgorithm == StringMatchingAlgorithm_ID.UseDefaultStringMatchingAlgorithm)
                stringMatchingAlgorithm = DefaultStringMatchingAlgorithm;
            switch (stringMatchingAlgorithm)
            {
                case StringMatchingAlgorithm_ID.Levenshtein:
                case StringMatchingAlgorithm_ID.iLevenshtein:
                    return new StringMatchingAlgorithms.ILevenshtein();
                case StringMatchingAlgorithm_ID.JaroWinkler:
                case StringMatchingAlgorithm_ID.iJaroWinkler:
                    return new StringMatchingAlgorithms.IJaroWinkler();
                case StringMatchingAlgorithm_ID.CosineSimilarity:
                case StringMatchingAlgorithm_ID.iCosineSimilarity:
                    return new StringMatchingAlgorithms.ICosineSimilarity();
                case StringMatchingAlgorithm_ID.LongestCommonSequence:
                case StringMatchingAlgorithm_ID.iLongestCommonSequence:
                    return new StringMatchingAlgorithms.ILongestCommonSequence();
                case StringMatchingAlgorithm_ID.JaccardSimilarity:
                case StringMatchingAlgorithm_ID.iJaccardSimilarity:
                    return new StringMatchingAlgorithms.IJaccardSimilarity();
                case StringMatchingAlgorithm_ID.JaccardIndex:
                case StringMatchingAlgorithm_ID.iJaccardIndex:
                    return new StringMatchingAlgorithms.IJaccardIndex();
                case StringMatchingAlgorithm_ID.OverlapCoefficient:
                case StringMatchingAlgorithm_ID.iOverlapCoefficient:
                    return new StringMatchingAlgorithms.IOverlapCoefficient();
                case StringMatchingAlgorithm_ID.NeedlemanWunsch:
                case StringMatchingAlgorithm_ID.iNeedlemanWunsch:
                    return new StringMatchingAlgorithms.INeedlemanWunsch();
                case StringMatchingAlgorithm_ID.SorensenDiceDistance:
                case StringMatchingAlgorithm_ID.iSorensenDiceDistance:
                    return new StringMatchingAlgorithms.ISorensenDice();
                case StringMatchingAlgorithm_ID.RatcliffObershelpSimilarityDistance:
                case StringMatchingAlgorithm_ID.iRatcliffObershelpSimilarityDistance:
                    return new StringMatchingAlgorithms.IRatcliffObershelpSimilarity();
                case StringMatchingAlgorithm_ID.HammingDistance:
                case StringMatchingAlgorithm_ID.iHammingDistance:
                    return new StringMatchingAlgorithms.IHamming();
                case StringMatchingAlgorithm_ID.LongestCommonSubstringDistance:
                case StringMatchingAlgorithm_ID.iLongestCommonSubstringDistance:
                    return new StringMatchingAlgorithms.ILongestCommonSubstring();
                case StringMatchingAlgorithm_ID.LongestCommonSubsequenceDistance:
                case StringMatchingAlgorithm_ID.iLongestCommonSubsequenceDistance:
                    return new StringMatchingAlgorithms.ILongestCommonSubsequence();
                case StringMatchingAlgorithm_ID.JaroDistance:
                case StringMatchingAlgorithm_ID.iJaroDistance:
                    return new StringMatchingAlgorithms.IJaro();
                case StringMatchingAlgorithm_ID.NormalizedLevenshteinDistance:
                case StringMatchingAlgorithm_ID.iNormalizedLevenshteinDistance:
                    return new StringMatchingAlgorithms.INormalizedLevenshtein();
                case StringMatchingAlgorithm_ID.Levenshtein2Distance:
                case StringMatchingAlgorithm_ID.iLevenshtein2Distance:
                    return new StringMatchingAlgorithms.ILevenshtein2();
                case StringMatchingAlgorithm_ID.TanimotoCoefficientDistance:
                case StringMatchingAlgorithm_ID.iTanimotoCoefficientDistance:
                    return new StringMatchingAlgorithms.ITanimotoCoefficient();
                case StringMatchingAlgorithm_ID.EditDistance:
                case StringMatchingAlgorithm_ID.iEditDistance:
                    return new StringMatchingAlgorithms.IEditDistanceWithWildCard();
                case StringMatchingAlgorithm_ID.BlockDistance:
                case StringMatchingAlgorithm_ID.iBlockDistance:
                    return new StringMatchingAlgorithms.BlockDistance();
                case StringMatchingAlgorithm_ID.ChapmanLengthDeviation:
                case StringMatchingAlgorithm_ID.iChapmanLengthDeviation:
                    return new StringMatchingAlgorithms.ChapmanLengthDeviation();
                case StringMatchingAlgorithm_ID.ChapmanMeanLength:
                case StringMatchingAlgorithm_ID.iChapmanMeanLength:
                    return new StringMatchingAlgorithms.ChapmanMeanLength();
                case StringMatchingAlgorithm_ID.EuclideanDistance:
                case StringMatchingAlgorithm_ID.iEuclideanDistance:
                    return new StringMatchingAlgorithms.EuclideanDistance();
                case StringMatchingAlgorithm_ID.MatchingCoefficient:
                case StringMatchingAlgorithm_ID.iMatchingCoefficient:
                    return new StringMatchingAlgorithms.MatchingCoefficient();
                case StringMatchingAlgorithm_ID.MongeElkan:
                case StringMatchingAlgorithm_ID.iMongeElkan:
                    return new StringMatchingAlgorithms.MongeElkan();
                case StringMatchingAlgorithm_ID.Sift4:
                case StringMatchingAlgorithm_ID.iSift4:
                    return new StringMatchingAlgorithms.ISift4();
                case StringMatchingAlgorithm_ID.SimHash:
                case StringMatchingAlgorithm_ID.iSimHash:
                    return new StringMatchingAlgorithms.ISimHash();
                case StringMatchingAlgorithm_ID.QGramsDistance:
                case StringMatchingAlgorithm_ID.iQGramsDistance:
                    return new StringMatchingAlgorithms.QGramsDistance();
                case StringMatchingAlgorithm_ID.NGramsDistance:
                case StringMatchingAlgorithm_ID.iNGramsDistance:
                    return new StringMatchingAlgorithms.NGramsDistance();
                case StringMatchingAlgorithm_ID.SmithWaterman:
                case StringMatchingAlgorithm_ID.iSmithWaterman:
                    return new StringMatchingAlgorithms.SmithWaterman();
                case StringMatchingAlgorithm_ID.SmithWatermanGotoh:
                case StringMatchingAlgorithm_ID.iSmithWatermanGotoh:
                    return new StringMatchingAlgorithms.SmithWatermanGotoh();
                case StringMatchingAlgorithm_ID.SmithWatermanGotohWindowedAffine:
                case StringMatchingAlgorithm_ID.iSmithWatermanGotohWindowedAffine:
                    return new StringMatchingAlgorithms.SmithWatermanGotohWindowedAffine();
                case StringMatchingAlgorithm_ID.DiceSimilarity:
                case StringMatchingAlgorithm_ID.iDiceSimilarity:
                    return new StringMatchingAlgorithms.DiceSimilarity();
                case StringMatchingAlgorithm_ID.PhraseTokenize:
                    return new StringMatchingAlgorithms.IPhraseTokenize();
                case StringMatchingAlgorithm_ID.SimplePhraseTokenize:
                    return new StringMatchingAlgorithms.ISimplePhraseTokenize();
                case StringMatchingAlgorithm_ID.DamerauLevenshtein:
                case StringMatchingAlgorithm_ID.iDamerauLevenshtein:
                    return new StringMatchingAlgorithms.IDamerauLevenshtein();
                case StringMatchingAlgorithm_ID.ExactMatch:
                    return new StringMatchingAlgorithms.IExactMatch();
                //case StringMatchingAlgorithm_ID.TverskyIndex_DO_NOT_USE:
                //case StringMatchingAlgorithm_ID.iTverskyIndex_DO_NOT_USE:
                //case StringMatchingAlgorithm_ID.GeneralizedCompressionDistance_DO_NOT_USE:
                //case StringMatchingAlgorithm_ID.iGeneralizedCompressionDistance_DO_NOT_USE:
                //case StringMatchingAlgorithm_ID.MinHash_DO_NOT_USE:
                //case StringMatchingAlgorithm_ID.iMinHash_DO_NOT_USE:
                default:
                    // Handle use of missing algorithms gracefully by using IExactMatch
                    if (IsInOp_StringMatchingAlgorithm((int)stringMatchingAlgorithm))
                        return new StringMatchingAlgorithms.IExactMatch();
                    return null;
            }
        }
        #endregion Similarity functions
        #region Distance functions
        public static double EditDistance(string source1, string source2, bool isCaseSensitive = true) => StringMatchingAlgorithms.EditDistanceWithWildCard.Distance(source1, source2, isCaseSensitive);
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
        public static double Sift4(this string source1, string source2, bool isCaseSensitive = true)
        {
            ISift4 sift4 = new ISift4();
            return sift4.Distance(source1, source2, isCaseSensitive);
        }
        public static double SimHash(this string source1, string source2, bool isCaseSensitive = true)
        {
            ISimHash simHash = new ISimHash();
            return simHash.Distance(source1, source2, isCaseSensitive);
        }
        public static double QGramsDistance(this string source1, string source2, bool isCaseSensitive = true)
        {
            FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            return qGramsDistance.GetSimilarity(source1, source2);
        }
        public static double NGramsDistance(this string source1, string source2, bool isCaseSensitive = true)
        {
            FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            return nGramsDistance.Distance(source1, source2);
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
        public static double NeedlemanWunsch(this string source1, string source2, bool isCaseSensitive = true) => StringMatchingAlgorithms.NeedlemanWunsch.Percentage(source1, source2, isCaseSensitive);
        public static double CosineSimilarity(this string source1, string source2, bool isCaseSensitive = true) => StringMatchingAlgorithms.CosineSimilarity.Percentage(source1, source2, isCaseSensitive);
        public static double JaccardSimilarity(this string source1, string source2, bool isCaseSensitive = true) => StringMatchingAlgorithms.JaccardSimilarity.Percentage(source1, source2, isCaseSensitive);
        public static double LongestCommonSequence(this string source1, string source2, bool isCaseSensitive = true) => StringMatchingAlgorithms.LongestCommonSequence.Percentage(source1, source2, isCaseSensitive);
        public static double PhraseTokenize(this string source1, string source2, bool isCaseSensitive = true) => StringMatchingAlgorithms.PhraseTokenize.Distance(source1, source2, isCaseSensitive);
        public static double SimplePhraseTokenize(this string source1, string source2, bool isCaseSensitive = true) => StringMatchingAlgorithms.SimplePhraseTokenize.Distance(source1, source2, isCaseSensitive);
        public static double LevenshteinDistance(this string source1, string source2, bool isCaseSensitive = true) => StringMatchingAlgorithms.Levenshtein.Distance(source1, source2, isCaseSensitive);
        public static double DamerauLevenshteinDistance(this string source1, string source2, bool isCaseSensitive = true) => StringMatchingAlgorithms.DamerauLevenshtein.Distance(source1, source2, isCaseSensitive);
        public static double JaroWinklerDistance(this string source1, string source2, bool isCaseSensitive = true) => StringMatchingAlgorithms.JaroWinkler.Distance(source1, source2, isCaseSensitive);
        public static double OverlapCoefficientDistance(this string source1, string source2, bool isCaseSensitive = true) => StringMatchingAlgorithms.OverlapCoefficient.Distance(source1, source2, isCaseSensitive);
        public static double JaccardDistance(this string source1, string source2, bool isCaseSensitive = true) => StringMatchingAlgorithms.JaccardIndex.Distance(source1, source2, isCaseSensitive);
        public static double JaccardIndex(this string source1, string source2, bool isCaseSensitive = true) => StringMatchingAlgorithms.JaccardIndex.Distance(source1, source2, isCaseSensitive);
        public static double SorensenDiceDistance(this string source1, string source2, bool isCaseSensitive = true) => StringMatchingAlgorithms.SorensenDice.Distance(source1, source2, isCaseSensitive);
        public static double RatcliffObershelpSimilarityDistance(this string source1, string source2, bool isCaseSensitive = true) => StringMatchingAlgorithms.RatcliffObershelpSimilarity.Distance(source1, source2, isCaseSensitive);
        public static double HammingDistance(this string source1, string source2, bool isCaseSensitive = true) => StringMatchingAlgorithms.Hamming.Distance(source1, source2, isCaseSensitive);
        public static double LongestCommonSubstringDistance(this string source1, string source2, bool isCaseSensitive = true) => StringMatchingAlgorithms.LongestCommonSubstring.Distance(source1, source2, isCaseSensitive);
        public static double LongestCommonSubsequenceDistance(this string source1, string source2, bool isCaseSensitive = true) => StringMatchingAlgorithms.LongestCommonSubsequence.Distance(source1, source2, isCaseSensitive);
        public static double JaroDistance(this string source1, string source2, bool isCaseSensitive = true) => StringMatchingAlgorithms.Jaro.Distance(source1, source2, isCaseSensitive);
        public static double NormalizedLevenshteinDistance(this string source1, string source2, bool isCaseSensitive = true) => StringMatchingAlgorithms.NormalizedLevenshtein.Distance(source1, source2, isCaseSensitive);
        public static double Levenshtein2Distance(this string source1, string source2, bool isCaseSensitive = true) => StringMatchingAlgorithms.Levenshtein2.Distance(source1, source2, isCaseSensitive);
        public static double TanimotoCoefficientDistance(this string source1, string source2, bool isCaseSensitive = true) => StringMatchingAlgorithms.TanimotoCoefficient.Distance(source1, source2, isCaseSensitive);
        public static double PhraseSimplifiedDiff(this string source1, string source2) => StringMatchingAlgorithms.SimplePhraseTokenize.Distance(source1, source2, false);
        #endregion Distance functions
        #region SameFunc functions
        public static bool SameFirstLastName(string source1, string source2, bool isCaseSensitive = false) => Misc.Sameness.SameFirstLastName(source1, source2, isCaseSensitive);
        public static bool SameNames(string source1, string source2, bool isCaseSensitive = false) => Misc.Sameness.SameNames(source1, source2, isCaseSensitive);
        public static bool SamePhone(string source1, string source2, bool isCaseSensitive = false) => Misc.Sameness.SamePhone(source1, source2, isCaseSensitive);
        public static bool SameSocial(string source1, string source2, bool isCaseSensitive = false) => Misc.Sameness.SameSocial(source1, source2, isCaseSensitive);
        public static bool SameZip(string source1, string source2, bool isCaseSensitive = false) => Misc.Sameness.SameZip(source1, source2, isCaseSensitive);
        public static bool SameAddress(string source1, string source2, bool isCaseSensitive = false) => Misc.Sameness.SameAddress(source1, source2, isCaseSensitive);
        public static bool SameDate(string source1, string source2, bool isCaseSensitive = false) => Misc.Sameness.SameDate(source1, source2, isCaseSensitive);
        public static bool SameFileName(string source1, string source2, bool isCaseSensitive = false) => Misc.Sameness.SameFileName(source1, source2, isCaseSensitive);
        public static bool SameNumber(string source1, string source2, bool isCaseSensitive = false) => Misc.Sameness.SameNumber(source1, source2, isCaseSensitive);
        #endregion SameFunc functions
        #region Phonetic (sound) functions
        public static bool MatchRatingApproach(this string source1, string source2, StringMatchingAlgorithm_ID stringMatchingAlgorithm = StringMatchingAlgorithm_ID.ExactMatch, bool isVerySimilar = true)
        {
            return stringMatchingAlgorithm == StringMatchingAlgorithm_ID.ExactMatch
                ? matchRatingApproach.IsSimilar(source1, source2)
                : Compare(matchRatingApproach.BuildKey(source1), matchRatingApproach.BuildKey(source2), stringMatchingAlgorithm, isVerySimilar);
        }
        public static bool Metaphone(this string source1, string source2, StringMatchingAlgorithm_ID stringMatchingAlgorithm = StringMatchingAlgorithm_ID.ExactMatch, bool isVerySimilar = true)
        {
            string[] sources = { source1,  source2 };
            return stringMatchingAlgorithm == StringMatchingAlgorithm_ID.ExactMatch
                ? metaphone.IsSimilar(sources)
                : Compare(metaphone.BuildKey(source1), metaphone.BuildKey(source2), stringMatchingAlgorithm, isVerySimilar);
        }
        public static bool CaverPhonePhonix(this string source1, string source2,
            StringMatchingAlgorithm_ID stringMatchingAlgorithm,
            bool isVerySimilar)
        {
            string s1 = caverPhonePhonix.BuildKey(source1);
            string s2 = caverPhonePhonix.BuildKey(source2);
            return Compare(s1, s2, stringMatchingAlgorithm, isVerySimilar);
        }
        public static bool CaverPhonePhonix(this string source1, string source2)
        {
            string[] sources = { source1,  source2 };
            return caverPhonePhonix.IsSimilar(sources);
        }
        public static string CaverPhonePhonix(string source1)
        {
            return caverPhonePhonix.BuildKey(source1);
        }
        public static bool DoubleMetaphone(this string source1, string source2, StringMatchingAlgorithm_ID stringMatchingAlgorithm = StringMatchingAlgorithm_ID.ExactMatch, bool isVerySimilar = true)
        {
            string[] sources = { source1,  source2 };
            return stringMatchingAlgorithm == StringMatchingAlgorithm_ID.ExactMatch
                ? doubleMetaphone.IsSimilar(sources)
                : Compare(doubleMetaphone.BuildKey(source1), doubleMetaphone.BuildKey(source2), stringMatchingAlgorithm, isVerySimilar);
        }
        public static bool ColognePhonetics(this string source1, string source2, StringMatchingAlgorithm_ID stringMatchingAlgorithm = StringMatchingAlgorithm_ID.ExactMatch, bool isVerySimilar = true)
        {
            string s1 = ColognePhoneticsSharp.ColognePhonetics.GetPhonetics(source1);
            string s2 = ColognePhoneticsSharp.ColognePhonetics.GetPhonetics(source2);
            return Compare(s1, s2, stringMatchingAlgorithm, isVerySimilar);
        }
        public static bool SoundexPhonix(this string source1, string source2,
            StringMatchingAlgorithm_ID stringMatchingAlgorithm,
            bool isVerySimilar)
        {
            string s1 = soundexPhonix.BuildKey(source1);
            string s2 = soundexPhonix.BuildKey(source2);
            return Compare(s1, s2, stringMatchingAlgorithm, isVerySimilar);
        }
        public static bool SoundexPhonix(this string source1, string source2) => SoundexPhonix(source1, source2, StringMatchingAlgorithm_ID.ExactMatch, true);
        public static string SoundexPhonix(string source1)
        {
            return soundexPhonix.BuildKey(source1);
        }
        public static bool SoundexVer2(this string source1, string source2,
            StringMatchingAlgorithm_ID stringMatchingAlgorithm,
            bool isVerySimilar)
        {
            string s1 = PhoneticMethods.SoundexVer2.Generate(source1);
            string s2 = PhoneticMethods.SoundexVer2.Generate(source2);
            return Compare(s1, s2, stringMatchingAlgorithm, isVerySimilar);
        }
        public static bool SoundexVer2(this string source1, string source2) => SoundexVer2(source1, source2, StringMatchingAlgorithm_ID.ExactMatch, true);
        public static string SoundexVer2(string source1)
        {
            return PhoneticMethods.SoundexVer2.Generate(source1);
        }
        public static bool EnPhoneticDistance_IsSupported() => FuzzyPhoneticMatching.EnPhoneticDistance_Supported;
        public static bool EnPhoneticDistance(this string source1, string source2, bool isVerySimilar = true)
        {
            return FuzzyPhoneticMatching.EnPhoneticDistance(source1, source2, isVerySimilar, soundexPhonix);
        }
        public static string GetSoundCode(string source1, SameSoundMethod sameSoundMethod = SameSoundMethod.UseDefaultSameSoundMethod)
        {
            if (sameSoundMethod == SameSoundMethod.UseDefaultSameSoundMethod)
                sameSoundMethod = DefaultSameSoundMethod;
            switch (sameSoundMethod)
            {
                case SameSoundMethod.EnPhoneticDistance:
                    return FuzzyPhoneticMatching.GetEnPhoneticString(source1, soundexPhonix);
                case SameSoundMethod.CaverPhonePhonix:
                    return caverPhonePhonix.BuildKey(source1);
                case SameSoundMethod.SoundexVer2:
                    return PhoneticMethods.SoundexVer2.Generate(source1);
                case SameSoundMethod.MatchRatingApproach:
                    return matchRatingApproach.BuildKey(source1);
                case SameSoundMethod.Metaphone:
                    return metaphone.BuildKey(source1);
                case SameSoundMethod.DoubleMetaphone:
                    return doubleMetaphone.BuildKey(source1);
                case SameSoundMethod.ColognePhonetics:
                    return ColognePhoneticsSharp.ColognePhonetics.GetPhonetics(source1);
                case SameSoundMethod.SoundexPhonix:
                default:
                    return soundexPhonix.BuildKey(source1);
            }
        }
        public static bool SameSound(this string source1, string source2,
            SameSoundMethod sameSoundMethod = SameSoundMethod.UseDefaultSameSoundMethod,
            StringMatchingAlgorithm_ID stringMatchingAlgorithm = StringMatchingAlgorithm_ID.ExactMatch,
            bool isVerySimilar = true)
        {
            if (sameSoundMethod == SameSoundMethod.UseDefaultSameSoundMethod)
                sameSoundMethod = DefaultSameSoundMethod;
            switch (sameSoundMethod)
            {
                case SameSoundMethod.EnPhoneticDistance:
                    return EnPhoneticDistance(source1, source2, isVerySimilar);
                case SameSoundMethod.MatchRatingApproach:
                    return MatchRatingApproach(source1, source2, stringMatchingAlgorithm, isVerySimilar);
                case SameSoundMethod.Metaphone:
                    return Metaphone(source1, source2, stringMatchingAlgorithm, isVerySimilar);
                case SameSoundMethod.CaverPhonePhonix:
                    return CaverPhonePhonix(source1, source2, stringMatchingAlgorithm, isVerySimilar);
                case SameSoundMethod.DoubleMetaphone:
                    return DoubleMetaphone(source1, source2, stringMatchingAlgorithm,isVerySimilar);
                case SameSoundMethod.ColognePhonetics:
                    return ColognePhonetics(source1, source2, stringMatchingAlgorithm, isVerySimilar);
                case SameSoundMethod.SoundexVer2:
                    return SoundexVer2(source1, source2, stringMatchingAlgorithm, isVerySimilar);
                case SameSoundMethod.SoundexPhonix:
                default:
                    return SoundexPhonix(source1, source2, stringMatchingAlgorithm, isVerySimilar);
            }
        }
        public static bool Compare(string source1, string source2, StringMatchingAlgorithm_ID CompareMethod, bool isVerySimilar)
        {
            switch (CompareMethod)
            {
                case StringMatchingAlgorithm_ID.ExactMatch:
                    return source1 == source2;
                default:
                    return isVerySimilar ? IsVerySimilar(source1, source2, CompareMethod) : IsSimilar(source1, source2, CompareMethod);
            }
        }
        public static bool IsSimilar(string source1, string source2, SameSoundMethod id) => SameSound(source1, source2, id, StringMatchingAlgorithm_ID.UseDefaultStringMatchingAlgorithm, false);
        public static bool IsVerySimilar(string source1, string source2, SameSoundMethod id) => SameSound(source1, source2, id, StringMatchingAlgorithm_ID.UseDefaultStringMatchingAlgorithm, true);
        #endregion Phonetic (sound) functions
        #region Hash Logic
        public enum HashType
        {
            MD5,                        // MD5          (128 bits)  32 characters as a hexadecimal string
            RIPEMD160,                  // RIPEMD-160   (160 bits)  40 characters as a hexadecimal string
            SHA1,                       // SHA-1        (160 bits)  40 characters as a hexadecimal string
            SHA256,                     // SHA-256      (256 bits)  64 characters as a hexadecimal string
            SHA384,                     // SHA-384      (384 bits)  96 characters as a hexadecimal string
            SHA512,                     // SHA-512      (512 bits)  128 characters as a hexadecimal string
            FastHash,                   // Fast Hash    (64  bits)  16 characters as a hexadecimal string
            MD5u = HASH_UTF8_ENCODE,    // MD5          UTF8 encoding
            RIPEMD160u,
            SHA1u,
            SHA256u,
            SHA384u,
            SHA512u,
        }
        //MD6,                // MD6          Variable output length                           
        //CRC32,   // CRC32        (32 bits)   8 characters as a hexadecimal string 
        //CRC64,   // CRC64        (64 bits)   16 characters as a hexadecimal string
        //MD4,     // MD4          (128 bits)  32 characters as a hexadecimal string
        public static HashType GetHashType(string HashType_Name)
        {
            HashType stringMatchingAlgorithm = HashType.MD5;
            if (HashType_Name != null)
            {
                try
                {
                    stringMatchingAlgorithm = (HashType)Enum.Parse(typeof(HashType), HashType_Name, true);
                }
                catch
                {
                }
            }
            return stringMatchingAlgorithm;
        }
        public static string ByteArrayToString(byte[] ba)
        {
            StringBuilder hex = new StringBuilder(ba.Length * 2);
            foreach (byte b in ba)
                hex.AppendFormat("{0:x2}", b);
            return hex.ToString();
        }
        public static string ToHash(string data, HashType hashType)
        {
            HashAlgorithm hash = null;
            switch (hashType)
            {
                case HashType.MD5:
                case HashType.MD5u:
                    hash = MD5.Create();
                    break;
                case HashType.SHA1:
                case HashType.SHA1u:
                    hash = SHA1.Create();
                    break;
                case HashType.SHA256:
                case HashType.SHA256u:
                    hash = SHA256.Create();
                    break;
                case HashType.SHA384:
                case HashType.SHA384u:
                    hash = SHA384.Create();
                    break;
                case HashType.SHA512:
                case HashType.SHA512u:
                    hash = SHA512.Create();
                    break;
                case HashType.RIPEMD160:
                case HashType.RIPEMD160u:
                    hash = RIPEMD160.Create();
                    break;
                case HashType.FastHash:
                    ulong ul = StringMatchingAlgorithms.SimHash.CalculateHash(data);
                    byte[] byte_array = BitConverter.GetBytes(ul);
                    return ByteArrayToString(byte_array);
            }
            if (hash == null)
                return null;
            byte[] byteArray = (int)hashType >= HASH_UTF8_ENCODE ? hash.ComputeHash(Encoding.UTF8.GetBytes(data)) : hash.ComputeHash(Encoding.ASCII.GetBytes(data));
            hash.Dispose();
            return ByteArrayToString(byteArray);
        }
        public static ulong FastHash(string data) => StringMatchingAlgorithms.SimHash.CalculateHash(data);
        #endregion Hash Logic
        #region Miscellaneous functions
        // ToDo: Consider adding the following fuzzy_score, vector search, MD5, UUID, sha256, date parser, JSON, path handler, URL handler, undo-redo
        //      math -> https://github.com/uzbekdev1/SqliteExtension
        //      see following for good FuzzyInst names (https://github.com/schiffma/distlib)
        //      MD5 -> https://github.com/thechampion/sqlite3_extensions (md5, sha1, sha224, sha256, sha384, and sha512)
        public static string HasCharInSameOrder(this string word) => Misc.HasInSameOrder.HasCharInSameOrder(word, "%"); // Needed for CPP code access
        public static string HasCharInSameOrder(this string word, string sep) => Misc.HasInSameOrder.HasCharInSameOrder(word, sep); // SQL function extension
        public static string HasWordFrom(string words, string fieldToCompare) => Misc.HasInSameOrder.HasWordFrom(words, fieldToCompare); // Needed for CPP code access
        public static string HasWordFrom(string words, string fieldToCompare, int minimumWordLenForWordInWordMatch) => Misc.HasInSameOrder.HasWordFrom(words, fieldToCompare, minimumWordLenForWordInWordMatch);
        public static string WordsToJson(string words, int minimumWordLenForWordInWordMatch) => Misc.HasInSameOrder.WordsToJson(words, minimumWordLenForWordInWordMatch);
        public static string ValuesList(string words) => Misc.HasInSameOrder.ValuesList(words);
        public static string ValuesList(string words, int minimumWordLenForWordInWordMatch) => Misc.HasInSameOrder.ValuesList(words, minimumWordLenForWordInWordMatch);
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
        public static SQLite.SQLiteConnection CreateSQLiteConnection(string connectionString)
        {
            connection = new SQLite.SQLiteConnection(connectionString);
            return connection;
        }
        public static SQLite.SQLiteConnection CreateSQLiteConnectionViaPtr(System.IntPtr handle)
        {
            connection = new SQLite.SQLiteConnection(handle);
            return connection;
        }
        public static SQLite.SQLiteConnection CreateSQLiteVirtualConnection(System.IntPtr handle, string DatabasePath)
        {
            virtualConnection = new SQLite.SQLiteConnection(handle, DatabasePath);
            return virtualConnection;
        }
        public static System.Data.DataTable ExecuteQuery(IntPtr _db, string query, params string[] args)
        {
            System.Data.DataTable data = SQLite.SQLite3.ExecuteQuery(_db, query, args);
            return data;
        }
        #endregion Miscellaneous functions
        #region Case INSENSITIVE phrase comparison associated functions (token ratio)
        public static double PhraseHowSimilar(string source1, string source2)
        {
            string[] list1 = GetKeywordList(ref source1, false, true);
            string[] list2 = GetKeywordList(ref source2, false, true);
            double sourceLength = Math.Max(list1.Length, list2.Length);
            double diff = StringMatchingAlgorithms.PhraseTokenize.Distance(source1, source2,false, true);
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
