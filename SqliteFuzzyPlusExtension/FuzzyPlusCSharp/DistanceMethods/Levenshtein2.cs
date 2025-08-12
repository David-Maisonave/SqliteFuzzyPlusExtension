using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FuzzyPlusCSharp.DistanceMethods
{
    public static class Levenshtein2
    {
        public static int Distance(this string source1, string source2, bool isCaseSensitive = true)
        {
            Fuzzy.FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            return source1.LevenshteinDistance2(source2);
            // return source1.LevenshteinDistance2(source2) - source1.LevenshteinDistanceLowerBounds(source2);
        }
        public static double Percentage(this string source1, string source2, bool isCaseSensitive = true)
        {
            Fuzzy.FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            double distance = Convert.ToDouble(LevenshteinDistance2(source1, source2)) / Convert.ToDouble(Math.Max(source1.Length, source2.Length));
            return 1.0f - (double)distance;
        }
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
        public static int LevenshteinDistanceUpperBounds(this string source1, string source2) => source1.Length == source2.Length ? DistanceMethods.Hamming.Distance(source1, source2) : Math.Max(source1.Length, source2.Length);
        ///  <returns>The lower bounds is the difference in length between the two strings</returns>
        public static int LevenshteinDistanceLowerBounds(this string source1, string source2) => Math.Abs(source1.Length - source2.Length);
    }
}
