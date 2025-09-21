using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FuzzyPlusCSharp.StringMatchingAlgorithms
{
#pragma warning disable CRR0050 // Disabling this warning, because using string.compare() does NOT make the code more readable compared to a simple ==  or != operators.
#pragma warning disable CRR0047 // Disabling this warning because we want to keep this class here to simplify the code.
    public class ICosineSimilarity : FuzzyPlusCSharp.StringMatchingAlgorithms.IDistance
    {
        public double Percentage(string source1, string source2, bool isCaseSensitive = true) => CosineSimilarity.Percentage(source1, source2, isCaseSensitive);
        public double Distance(string source1, string source2, bool isCaseSensitive = true) => CosineSimilarity.Distance(source1, source2, isCaseSensitive);
    }
    public class CosineSimilarity
    {
        /// <summary>
        /// Calculates the similarity percentage between two strings via Cosine Similarity. 
        /// </summary>
        /// <param name="source1">The first string.</param>
        /// <param name="source2">The second string.</param>
        /// <returns>The similarity percentage between the two strings. It's a number between 0 and 1 that represents how similar two strings are. The closer to 1, the more similar they are.</returns>
        public static double Percentage(string source1, string source2, bool isCaseSensitive = true) => (double)CalculateSimilarity(source1, source2, isCaseSensitive, false);
        public static double Distance(string source1, string source2, bool isCaseSensitive = true) => (double)CalculateSimilarity(source1, source2, isCaseSensitive, true);
        public static double CalculateSimilarity(string source1, string source2, bool isCaseSensitive = true, bool getDistance = false)
        {
            Fuzzy.FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            if (source1 == source2)
                return getDistance ? 0 : 1;
            string[] words1 = source1.Split();
            string[] words2 = source2.Split();
            Dictionary<string, int> vector1 = GetWordVector(words1);
            Dictionary<string, int> vector2 = GetWordVector(words2);
            IEnumerable<string> intersection = new HashSet<string>(vector1.Keys).Intersect(vector2.Keys);
            double dotProduct = 0;
            double magnitude1 = 0;
            double magnitude2 = 0;
            foreach (string word in intersection)
                dotProduct += vector1[word] * vector2[word];
            if (getDistance)
                return (magnitude1 == 0 || magnitude2 == 0) ? 0 : dotProduct;
            foreach (int value in vector1.Values)
                magnitude1 += value * value;
            foreach (int value in vector2.Values)
                magnitude2 += value * value;
            magnitude1 = Math.Sqrt(magnitude1);
            magnitude2 = Math.Sqrt(magnitude2);
            return (magnitude1 == 0 || magnitude2 == 0) ? 0 : dotProduct / (magnitude1 * magnitude2);
        }
        private static Dictionary<string, int> GetWordVector(IReadOnlyCollection<string> words)
        {
            Dictionary<string, int> wordVector = new Dictionary<string, int>(words.Count, StringComparer.OrdinalIgnoreCase);
            foreach (string word in words)
            {
                string key = word.ToLower();
                wordVector[key] = wordVector.TryGetValue(key, out int count) ? count + 1 : 1;
            }
            return wordVector;
        }
    }
}
