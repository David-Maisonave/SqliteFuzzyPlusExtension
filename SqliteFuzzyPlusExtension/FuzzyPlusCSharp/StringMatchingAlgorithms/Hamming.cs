using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FuzzyPlusCSharp.StringMatchingAlgorithms
{
    public class IHamming : FuzzyPlusCSharp.StringMatchingAlgorithms.IDistance
    {
        public double Percentage(string source1, string source2, bool isCaseSensitive = true) => Hamming.Percentage(source1, source2, isCaseSensitive);
        public double Distance(string source1, string source2, bool isCaseSensitive = true) => Hamming.Distance(source1, source2, isCaseSensitive);
    }
    public static class Hamming
    {
        public static double Percentage(string source1, string source2, bool isCaseSensitive = true)
        {
            return source1.Length != source2.Length ? (double)-1.0f : 1.0f - ((double)Distance(source1, source2, isCaseSensitive) / (double)source2.Length);
        }
        public static int Distance(string source1, string source2, bool isCaseSensitive = true)
        {
            if (source1.Length != source2.Length)
                return -1;
            Fuzzy.FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            int distance = 0;
            for (int i = 0; i < source1.Length; i++)
                if (!source1[i].Equals(source2[i]))
                    distance++;
            return distance;
        }
    }
}
