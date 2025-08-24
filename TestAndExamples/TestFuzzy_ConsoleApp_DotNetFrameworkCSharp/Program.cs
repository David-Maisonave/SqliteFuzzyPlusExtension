using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FuzzyPlusCSharp;

namespace TestFuzzy_ConsoleApp_DotNetFrameworkCSharp
{
    internal class Program
    {
        public class D
        {
            public static double f = 0.0f; // Created this class and variable to remove compiler message about unrequired assignment variable
            public static string s;
            public static Fuzzy.StringMatchingAlgorithm_ID d = Fuzzy.StringMatchingAlgorithm_ID.UseDefaultStringMatchingAlgorithm;
        }
        static void Main()//string[] args)
        {
            D.s = Fuzzy.HasWordsInSameOrder("This is a similar phrase test", "Phrases");
            D.s = Fuzzy.HasWordsInSameOrder("This is a similar phrase test", "Phrases");
            D.s = Fuzzy.HasCharInSameOrder("david");
            //D.f = Fuzzy.HowSimilar("This is a test", "This is a similar phrase test", Fuzzy.GetStringMatchingAlgorithm("NormalizedLevenshteinDistance"));

            //D.f = Fuzzy.HowSimilar("This is a test", "This is a similar phrase test", "Levenshtein2Distance");

            //D.f = Fuzzy.LevenshteinDistance("David", "Davie");
            //D.f = Fuzzy.LevenshteinDistance("David", "Davie");
            //D.f = Fuzzy.DamerauLevenshteinDistance("David", "Davie");
            //D.f = Fuzzy.JaroWinklerDistance("David", "Davie");
            //D.f = Fuzzy.OverlapCoefficientDistance("David", "Davie");
            //D.f = Fuzzy.JaccardDistance("David", "Davie");
            //D.f = Fuzzy.SorensenDiceDistance("David", "Davie");
            //D.f = Fuzzy.RatcliffObershelpSimilarityDistance("David", "Davie");
            //D.f = Fuzzy.HammingDistance("David", "Davie");
            //D.f = Fuzzy.LongestCommonSubstringDistance("David", "Davie");
            //D.f = Fuzzy.LongestCommonSubsequenceDistance("David", "Davie");
            //D.f = Fuzzy.JaroDistance("David", "Davie");
            //D.f = Fuzzy.NormalizedLevenshteinDistance("David", "Davie");
            //D.f = Fuzzy.Levenshtein2Distance("David", "Davie");
            //D.f = Fuzzy.TanimotoCoefficientDistance("David", "Davie");
            //D.f = JaccardSimilarity.Percentage("David", "Davie");
            //D.f = JaccardSimilarity.Percentage("David", "David");
            //D.f = JaccardSimilarity.Percentage("David", "david");
            //D.f = JaccardSimilarity.Percentage("David", "12345");
            //D.f = JaccardSimilarity.Percentage("David", "daxyz");
            //D.f = JaccardSimilarity.Percentage("This is a test", "This is another test");
            //D.f = JaccardSimilarity.Percentage("This is a test", "This is test");
            //D.f = Fuzzy.HowSimilar("This is a test", "This is another test", "CosineSimilarity");
            //D.f = Fuzzy.HowSimilar("This is a test", "This is test", "CosineSimilarity");

            //D.f = Fuzzy.HowSimilar("David", "david", "LevenshteinDistance");
            //D.f = Fuzzy.HowSimilar("David", "Davie", "LevenshteinDistance");
            //D.f = Fuzzy.HowSimilar("David", "Davie", "DamerauLevenshteinDistance");
            //D.f = Fuzzy.HowSimilar("David", "Davie", "JaroWinklerDistance");
            //D.f = Fuzzy.HowSimilar("David", "Davie", "CosineSimilarity");
            //D.f = Fuzzy.HowSimilar("David", "Davie", "LongestCommonSequence");
            //D.f = Fuzzy.HowSimilar("David", "David", "JaccardSimilarity");
            //D.f = Fuzzy.HowSimilar("David", "david", "JaccardSimilarity");
            //D.f = Fuzzy.HowSimilar("David", "Davie", "JaccardSimilarity");
            //D.f = Fuzzy.HowSimilar("David", "Davie", "JaccardIndex");
            //D.f = Fuzzy.HowSimilar("David", "Davie", "OverlapCoefficient");
            //D.f = Fuzzy.HowSimilar("David", "Davie", "NeedlemanWunsch");
            //D.f = Fuzzy.HowSimilar("David", "Davie", "SorensenDiceDistance");
            //D.f = Fuzzy.HowSimilar("David", "Davie", "RatcliffObershelpSimilarityDistance");
            //D.f = Fuzzy.HowSimilar("David", "Davie", "HammingDistance");
            //D.f = Fuzzy.HowSimilar("David", "Davie", "LongestCommonSubstringDistance");
            //D.f = Fuzzy.HowSimilar("David", "Davie", "LongestCommonSubsequenceDistance");
            //D.f = Fuzzy.HowSimilar("David", "Davie", "JaroDistance");
            //D.f = Fuzzy.HowSimilar("David", "Davie", "NormalizedLevenshteinDistance");
            //D.f = Fuzzy.HowSimilar("David", "David", "Levenshtein2Distance");
            //D.f = Fuzzy.HowSimilar("David", "david", "Levenshtein2Distance");
            //D.f = Fuzzy.HowSimilar("David", "12345", "Levenshtein2Distance");
            //D.f = Fuzzy.HowSimilar("David", "davxx", "Levenshtein2Distance");
            //D.f = Fuzzy.HowSimilar("David", "Davie", "Levenshtein2Distance");
            //D.f = Fuzzy.HowSimilar("David", "Davie", "TanimotoCoefficientDistance");

            //D.f = Fuzzy.HowSimilar("David", "david", "iLevenshteinDistance");
            //D.f = Fuzzy.HowSimilar("David", "david", "iDamerauLevenshteinDistance");
            //D.f = Fuzzy.HowSimilar("David", "david", "iJaroWinklerDistance");
            //D.f = Fuzzy.HowSimilar("David", "david", "iCosineSimilarity");
            //D.f = Fuzzy.HowSimilar("David", "david", "iLongestCommonSequence");
            //D.f = Fuzzy.HowSimilar("David", "david", "iJaccardSimilarity");
            //D.f = Fuzzy.HowSimilar("David", "david", "iJaccardIndex");
            //D.f = Fuzzy.HowSimilar("David", "david", "iOverlapCoefficient");
            //D.f = Fuzzy.HowSimilar("David", "david", "iNeedlemanWunsch");
            //D.f = Fuzzy.HowSimilar("David", "david", "iSorensenDiceDistance");
            //D.f = Fuzzy.HowSimilar("David", "david", "iRatcliffObershelpSimilarityDistance");
            //D.f = Fuzzy.HowSimilar("David", "david", "iHammingDistance");
            //D.f = Fuzzy.HowSimilar("David", "david", "iLongestCommonSubstringDistance");
            //D.f = Fuzzy.HowSimilar("David", "david", "iLongestCommonSubsequenceDistance");
            //D.f = Fuzzy.HowSimilar("David", "david", "iJaroDistance");
            //D.f = Fuzzy.HowSimilar("David", "david", "iNormalizedLevenshteinDistance");
            //D.f = Fuzzy.HowSimilar("David", "david", "iLevenshtein2Distance");
            //D.f = Fuzzy.HowSimilar("David", "david", "iTanimotoCoefficientDistance");

            //D.f = Fuzzy.HowSimilar("David", "Davie", "iLevenshteinDistance");
            //D.f = Fuzzy.HowSimilar("David", "Davie", "iDamerauLevenshteinDistance");
            //D.f = Fuzzy.HowSimilar("David", "Davie", "iJaroWinklerDistance");
            //D.f = Fuzzy.HowSimilar("David", "Davie", "iCosineSimilarity");
            //D.f = Fuzzy.HowSimilar("David", "Davie", "iLongestCommonSequence");
            //D.f = Fuzzy.HowSimilar("David", "Davie", "iJaccardSimilarity");
            //D.f = Fuzzy.HowSimilar("David", "Davie", "iJaccardIndex");
            //D.f = Fuzzy.HowSimilar("David", "Davie", "iOverlapCoefficient");
            //D.f = Fuzzy.HowSimilar("David", "Davie", "iNeedlemanWunsch");
            //D.f = Fuzzy.HowSimilar("David", "Davie", "iSorensenDiceDistance");
            //D.f = Fuzzy.HowSimilar("David", "Davie", "iRatcliffObershelpSimilarityDistance");
            //D.f = Fuzzy.HowSimilar("David", "Davie", "iHammingDistance");
            //D.f = Fuzzy.HowSimilar("David", "Davie", "iLongestCommonSubstringDistance");
            //D.f = Fuzzy.HowSimilar("David", "Davie", "iLongestCommonSubsequenceDistance");
            //D.f = Fuzzy.HowSimilar("David", "Davie", "iJaroDistance");
            //D.f = Fuzzy.HowSimilar("David", "Davie", "iNormalizedLevenshteinDistance");
            //D.f = Fuzzy.HowSimilar("David", "Davie", "iLevenshtein2Distance");
            //D.f = Fuzzy.HowSimilar("David", "Davie", "iTanimotoCoefficientDistance");

            //D.f = Fuzzy.HowSimilar("David", "david", 1);
            //D.f = Fuzzy.HowSimilar("David", "Davie", 1);
            //D.f = Fuzzy.HowSimilar("David", "Davie", 2);
            //D.f = Fuzzy.HowSimilar("David", "Davie", 3);
            //D.f = Fuzzy.HowSimilar("David", "Davie", 4);
            //D.f = Fuzzy.HowSimilar("David", "Davie", 5);
            //D.f = Fuzzy.HowSimilar("David", "Davie", 6);
            //D.f = Fuzzy.HowSimilar("David", "Davie", 7);
            //D.f = Fuzzy.HowSimilar("David", "Davie", 8);
            //D.f = Fuzzy.HowSimilar("David", "Davie", 9);
            //D.f = Fuzzy.HowSimilar("David", "Davie", 10);
            //D.f = Fuzzy.HowSimilar("David", "Davie", 11);
            //D.f = Fuzzy.HowSimilar("David", "Davie", 12);
            //D.f = Fuzzy.HowSimilar("David", "Davie", 13);
            //D.f = Fuzzy.HowSimilar("David", "Davie", 14);
            //D.f = Fuzzy.HowSimilar("David", "Davie", 15);
            //D.f = Fuzzy.HowSimilar("David", "Davie", 16);
            //D.f = Fuzzy.HowSimilar("David", "Davie", 17);
            //D.f = Fuzzy.HowSimilar("David", "Davie", 18);

            //D.f = Fuzzy.HowSimilar("David", "david", Fuzzy.CASE_INSENSITIVE_STRING_MATCHING_ALGORITHMS + 1);
            //D.f = Fuzzy.HowSimilar("David", "Davie", Fuzzy.CASE_INSENSITIVE_STRING_MATCHING_ALGORITHMS + 1);
            //D.f = Fuzzy.HowSimilar("David", "Davie", Fuzzy.CASE_INSENSITIVE_STRING_MATCHING_ALGORITHMS + 2);
            //D.f = Fuzzy.HowSimilar("David", "Davie", Fuzzy.CASE_INSENSITIVE_STRING_MATCHING_ALGORITHMS + 3);
            //D.f = Fuzzy.HowSimilar("David", "Davie", Fuzzy.CASE_INSENSITIVE_STRING_MATCHING_ALGORITHMS + 4);
            //D.f = Fuzzy.HowSimilar("David", "Davie", Fuzzy.CASE_INSENSITIVE_STRING_MATCHING_ALGORITHMS + 5);
            //D.f = Fuzzy.HowSimilar("David", "Davie", Fuzzy.CASE_INSENSITIVE_STRING_MATCHING_ALGORITHMS + 6);
            //D.f = Fuzzy.HowSimilar("David", "Davie", Fuzzy.CASE_INSENSITIVE_STRING_MATCHING_ALGORITHMS + 7);
            //D.f = Fuzzy.HowSimilar("David", "Davie", Fuzzy.CASE_INSENSITIVE_STRING_MATCHING_ALGORITHMS + 8);
            //D.f = Fuzzy.HowSimilar("David", "Davie", Fuzzy.CASE_INSENSITIVE_STRING_MATCHING_ALGORITHMS + 9);
            //D.f = Fuzzy.HowSimilar("David", "Davie", Fuzzy.CASE_INSENSITIVE_STRING_MATCHING_ALGORITHMS + 10);
            //D.f = Fuzzy.HowSimilar("David", "Davie", Fuzzy.CASE_INSENSITIVE_STRING_MATCHING_ALGORITHMS + 11);
            //D.f = Fuzzy.HowSimilar("David", "Davie", Fuzzy.CASE_INSENSITIVE_STRING_MATCHING_ALGORITHMS + 12);
            //D.f = Fuzzy.HowSimilar("David", "Davie", Fuzzy.CASE_INSENSITIVE_STRING_MATCHING_ALGORITHMS + 13);
            //D.f = Fuzzy.HowSimilar("David", "Davie", Fuzzy.CASE_INSENSITIVE_STRING_MATCHING_ALGORITHMS + 14);
            //D.f = Fuzzy.HowSimilar("David", "Davie", Fuzzy.CASE_INSENSITIVE_STRING_MATCHING_ALGORITHMS + 15);
            //D.f = Fuzzy.HowSimilar("David", "Davie", Fuzzy.CASE_INSENSITIVE_STRING_MATCHING_ALGORITHMS + 16);
            //D.f = Fuzzy.HowSimilar("David", "Davie", Fuzzy.CASE_INSENSITIVE_STRING_MATCHING_ALGORITHMS + 17);
            //D.f = Fuzzy.HowSimilar("David", "Davie", Fuzzy.CASE_INSENSITIVE_STRING_MATCHING_ALGORITHMS + 18);
        }
    }
}
