using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FuzzyPlusCSharp.StringMatchingAlgorithms
{
#pragma warning disable CRR0047 // Disabling this warning because we want to keep this class here to simplify the code.
    public class ILongestCommonSubstring : FuzzyPlusCSharp.StringMatchingAlgorithms.IDistance
    {
        public double Percentage(string source1, string source2, bool isCaseSensitive = true) => LongestCommonSubstring.Percentage(source1, source2, isCaseSensitive);
        public double Distance(string source1, string source2, bool isCaseSensitive = true) => LongestCommonSubstring.Distance(source1, source2, isCaseSensitive);
    }
    public static class LongestCommonSubstring
    {
        public static double Distance(this string source1, string source2, bool isCaseSensitive = true)
        {
            return (double)GetLongestCommonSubstring(source1, source2, isCaseSensitive).Length;
        }
        public static double Percentage(this string source1, string source2, bool isCaseSensitive = true)
        {
            return (double)GetLongestCommonSubstring(source1, source2, isCaseSensitive).Length / (double)Math.Min(source1.Length, source2.Length);
        }
        public static string GetLongestCommonSubstring(this string source1, string source2, bool isCaseSensitive)
        {
            if (String.IsNullOrEmpty(source1) || String.IsNullOrEmpty(source2))
                return null;
            Fuzzy.FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
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
    }
}
