using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FuzzyPlusCSharp.StringMatchingAlgorithms
{
    public class ILevenshtein : FuzzyPlusCSharp.StringMatchingAlgorithms.IDistance
    {
        public double Percentage(string source1, string source2, bool isCaseSensitive = true) => Levenshtein.Percentage(source1, source2, isCaseSensitive);
        public double Distance(string source1, string source2, bool isCaseSensitive = true) => Levenshtein.Distance(source1, source2, isCaseSensitive);
    }
    public static class Levenshtein
    {
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
        public static int Distance(this string source1, string source2, bool isCaseSensitive = true)
        {
            // If any entry empty return full length of other
            if (source1.Length == 0 || source2.Length == 0)
                return Math.Max(source1.Length, source2.Length);
            Fuzzy.FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
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
        public static double Percentage(this string source1, string source2, bool isCaseSensitive = true)
        {
            double d = (double)Distance(source1, source2, isCaseSensitive);
            return 1.0f - (d / Math.Max(source1.Length, source2.Length));
        }
    }
}
