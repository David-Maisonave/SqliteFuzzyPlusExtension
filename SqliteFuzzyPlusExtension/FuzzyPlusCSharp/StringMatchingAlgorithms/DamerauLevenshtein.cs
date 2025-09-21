using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FuzzyPlusCSharp.StringMatchingAlgorithms
{
#pragma warning disable CRR0050 // Disabling this warning, because using string.compare() does NOT make the code more readable compared to a simple ==  or != operators.
#pragma warning disable CRR0047 // Disabling this warning because we want to keep this class here to simplify the code.
    public class IDamerauLevenshtein : FuzzyPlusCSharp.StringMatchingAlgorithms.IDistance
    {
        public double Percentage(string source1, string source2, bool isCaseSensitive = true) => DamerauLevenshtein.Percentage(source1, source2, isCaseSensitive);
        public double Distance(string source1, string source2, bool isCaseSensitive = true) => DamerauLevenshtein.Distance(source1, source2, isCaseSensitive);
    }
    public class DamerauLevenshtein
    {
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
        public static int Distance(string source1, string source2, bool isCaseSensitive = true)
        {
            if (source1 == source2)
                return 0;
            // If any entry empty return full length of other
            if (source1.Length == 0 || source2.Length == 0)
                return Math.Max(source1.Length, source2.Length);
            Fuzzy.FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
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
        public static double Percentage(string source1, string source2, bool isCaseSensitive = true)
        {
            double d = (double)Distance(source1, source2, isCaseSensitive);
            return 1.0f - (d / Math.Max(source1.Length, source2.Length));
        }
    }
}
