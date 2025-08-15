using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FuzzyPlusCSharp.DistanceMethods
{
    // IEditDistanceWithWildCard is a place holder class, and doesn't have implementation for a wildcard yet.
    public class IEditDistanceWithWildCard : FuzzyPlusCSharp.DistanceMethods.IDistance
    {
        public double Percentage(string source1, string source2, bool isCaseSensitive = true) => EditDistanceWithWildCard.Percentage(source1, source2, isCaseSensitive);
        public double Distance(string source1, string source2, bool isCaseSensitive = true) => EditDistanceWithWildCard.Distance(source1, source2, isCaseSensitive);
    }
    public static class EditDistanceWithWildCard
    {
        public static double Percentage(string source1, string source2, bool isCaseSensitive = true)
        {
            return 1.0f - (double)Distance(source1, source2, isCaseSensitive);
        }
        public static int Distance(string source1, string source2, bool isCaseSensitive = true)
        {
            Fuzzy.FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
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
    }
}
