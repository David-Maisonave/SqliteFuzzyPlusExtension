using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

using static FuzzyPlusCSharp.StringMatchingAlgorithms.Sift4;

namespace FuzzyPlusCSharp.StringMatchingAlgorithms
{
    public class ISimHash : FuzzyPlusCSharp.StringMatchingAlgorithms.IDistance
    {
        public double Percentage(string source1, string source2, bool isCaseSensitive = true)
        {
            double d = Distance(source1, source2, isCaseSensitive);
            return 1.0f - (d / Math.Max(source1.Length, source2.Length));
        }
        public double Distance(string source1, string source2, bool isCaseSensitive = true)
        {
            Fuzzy.FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            return (double)SimHash.GetStringSim(source1, source2);
        }
    }
    public class SimHash
    {
        private static readonly Regex SplitterRegex = new Regex(@"[a-zA-Z0-9]+");
        public static bool IsStringSim(string left, string right, UInt64 threshold)
        {
            return GetStringSim(left, right) < threshold;
        }

        public static ulong GetStringSim(string left, string right)
        {
            List<string> leftList = SplitterRegex.Matches(left.ToLower()).Cast<Match>().Select(m => m.Value).ToList();
            List<string> rightList = SplitterRegex.Matches(right.ToLower()).Cast<Match>().Select(m => m.Value).ToList();

            ulong leftDocumentVector = GetDocumentHashVector(leftList);
            ulong rightDocumentVector = GetDocumentHashVector(rightList);
            return HammingDistance(leftDocumentVector, rightDocumentVector);
        }

        private static ulong GetDocumentHashVector(List<string> wordsInDocument)
        {
            var frequencies = wordsInDocument.GroupBy(w => w).ToDictionary(w => w.Key, w => w.Count());
            var documentHashVector = Enumerable.Repeat(0, 64).ToArray(); // 64
            wordsInDocument.ForEach(word =>
            {
                var wordHashVector = GetWordHashVector(word, frequencies[word]);
                documentHashVector = AddWordHashVector(documentHashVector, wordHashVector);
            });
            documentHashVector = NormalizeHashVector(documentHashVector);
            var documentHashVectorString = documentHashVector.Aggregate("", (current, t) => current + t);
            return Convert.ToUInt64(documentHashVectorString, 2);
        }

        private static int[] GetWordHashVector(string word, int weight)
        {
            var wordHashString = Convert.ToString((long)CalculateHash(word), 2);
            string zeros = "";
            for (var i = 0; i < 64 - wordHashString.Length; i++)
            {
                zeros += "0";
            }
            wordHashString = zeros + wordHashString;
            return (from c in wordHashString select c == '1' ? 1 * weight : -1 * weight).ToArray();
        }

        private static int[] AddWordHashVector(IReadOnlyList<int> left, IReadOnlyList<int> right)
        {
            var result = Enumerable.Repeat(0, 64).ToArray();
            for (var i = 0; i < result.Length; i++)
            {
                result[i] = left[i] + right[i];
            }
            return result;
        }

        private static int[] NormalizeHashVector(IReadOnlyList<int> hashVector)
        {
            var result = new int[64];
            for (var i = 0; i < result.Length; i++)
            {
                result[i] = hashVector[i] > 0 ? 1 : 0;
            }
            return result;
        }

        /// <summary>
        /// Fast Hash
        /// From http://stackoverflow.com/a/9545731
        /// </summary>
        /// <param name="read"></param>
        /// <returns></returns>
        private static ulong CalculateHash(string read)
        {
            var hashedValue = 3074457345618258791ul;
            foreach (var t in read)
            {
                hashedValue += t;
                hashedValue *= 3074457345618258799ul;
            }
            return hashedValue;
        }

        /// <summary>
        /// Fast HammingDistance
        /// From 
        /// </summary>
        /// <param name="left"></param>
        /// <param name="right"></param>
        /// <returns></returns>
        private static ulong HammingDistance(ulong left, ulong right)
        {
            var bb = left ^ right;
            const ulong c55 = 0x5555555555555555ul;
            const ulong c33 = 0x3333333333333333ul;
            const ulong c0F = 0x0f0f0f0f0f0f0f0ful;
            const ulong c01 = 0x0101010101010101ul;

            bb -= (bb >> 1) & c55;
            bb = (bb & c33) + ((bb >> 2) & c33);
            bb = (bb + (bb >> 4)) & c0F;
            return (bb * c01) >> 56;
        }
    }
}
