using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FuzzyPlusCSharp.DistanceMethods
{
    public class IJaroWinkler : FuzzyPlusCSharp.DistanceMethods.IDistance
    {
        public double Percentage(string source1, string source2, bool isCaseSensitive = true) => JaroWinkler.Percentage(source1, source2, isCaseSensitive);
        public double Distance(string source1, string source2, bool isCaseSensitive = true) => JaroWinkler.Distance(source1, source2, isCaseSensitive);
    }
    public static class JaroWinkler
    {
        /// <summary>
        ///     Jaro-Winkler distance between the specified strings.
        ///     Similar to Damerau-LevenshteinDistance, but it has a character edit-once restriction to make equal.
        /// </summary>
        /// <param name="source1">First String</param>
        /// <param name="source2">Second String</param>
        /// <returns>
        ///     Returns the Jaro-Winkler distance between the specified strings. The distance is symmetric and will fall in the range 0 (perfect match) to 1 (no match). 
        /// </returns>
        public static double Percentage(string source1, string source2, bool isCaseSensitive = true)
        {
            return 1.0f - Distance(source1, source2, isCaseSensitive);
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
        public static double Distance(string source1, string source2, bool isCaseSensitive = true)
        {
            int source1Length = source1.Length;
            int source2Length = source2.Length;
            if (source1Length == 0)
                return source2Length == 0 ? 1.0f : 0.0f;
            Fuzzy.FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
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
    }
}
