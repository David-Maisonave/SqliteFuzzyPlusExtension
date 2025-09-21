using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FuzzyPlusCSharp.StringMatchingAlgorithms
{
#pragma warning disable CRR0050 // Disabling this warning, because using string.compare() does NOT make the code more readable compared to a simple ==  or != operators.
#pragma warning disable CRR0047 // Disabling this warning because we want to keep this class here to simplify the code.
    public class ILongestCommonSequence : FuzzyPlusCSharp.StringMatchingAlgorithms.IDistance
    {
        public double Percentage(string source1, string source2, bool isCaseSensitive = true) => LongestCommonSequence.Percentage(source1, source2, isCaseSensitive);
        public double Distance(string source1, string source2, bool isCaseSensitive = true) => LongestCommonSequence.Distance(source1, source2, isCaseSensitive);
    }
    public class LongestCommonSequence
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
            Fuzzy.FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            if (source1 == source2)
                return Math.Max(source1.Length, source2.Length);
            int[] lcsRow = CalculateSimilarityArray(source1, source2);
            int lcsLength = lcsRow[source2.Length];
            return lcsLength;
        }
        public static int Distance(string source1, string source2, bool isCaseSensitive)
        {
            Fuzzy.FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            if (source1 == source2)
                return 0;
            int[] lcsRow = CalculateSimilarityArray(source1, source2);
            int lcsLength = lcsRow[source2.Length];
            return lcsLength;
        }
        public static double CalculateSimilarity(string source1, string source2, bool isCaseSensitive) => (double)Difference(source1, source2, isCaseSensitive) / Math.Max(source1.Length, source2.Length);
    }
}
