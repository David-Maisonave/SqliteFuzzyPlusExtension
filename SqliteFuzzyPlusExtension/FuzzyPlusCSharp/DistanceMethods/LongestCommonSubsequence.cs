using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FuzzyPlusCSharp.DistanceMethods
{
    public static class LongestCommonSubsequence
    {
        public static double Distance(this string source1, string source2, bool isCaseSensitive = true)
        {
            return (double)GetDistanceString(source1, source2, isCaseSensitive).Length;
        }
        public static double Percentage(this string source1, string source2, bool isCaseSensitive = true)
        {
            return 1.0f - ((double)GetDistanceString(source1, source2, isCaseSensitive).Length / (double)Math.Min(source1.Length, source2.Length));
        }
        public static string GetDistanceString(string source1, string source2, bool isCaseSensitive)
        {
            Fuzzy.FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            int[,] C = LengthTable(source1, source2);
            return Backtrack(C, source1, source2, source1.Length, source2.Length);
        }
        private static int[,] LengthTable(string source1, string source2)
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
        private static string Backtrack(int[,] C, string source1, string source2, int i, int j)
        {
            return i == 0 || j == 0
                ? ""
                : source1[i - 1].Equals(source2[j - 1])
                ? Backtrack(C, source1, source2, i - 1, j - 1) + source1[i - 1]
                : C[i, j - 1] > C[i - 1, j]
                    ? Backtrack(C, source1, source2, i, j - 1)
                    : Backtrack(C, source1, source2, i - 1, j);
        }
    }
}
