using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FuzzyPlusCSharp.StringMatchingAlgorithms
{
    public class IJaccardSimilarity : FuzzyPlusCSharp.StringMatchingAlgorithms.IDistance
    {
        public double Percentage(string source1, string source2, bool isCaseSensitive = true) => JaccardSimilarity.Percentage(source1, source2, isCaseSensitive);
        public double Distance(string source1, string source2, bool isCaseSensitive = true) => JaccardSimilarity.Distance(source1, source2, isCaseSensitive);
    }
    /// <summary>
    /// A class for comparing strings via the Jaccard similarity algorithm
    /// </summary>
    public class JaccardSimilarity
    {
        /// <summary>
        /// Calculates the similarity percentage between two strings via Jaccard Similarity
        /// </summary>
        /// <param name="source1">The first string.</param>
        /// <param name="source2">The second string.</param>
        /// <returns>The similarity percentage between the two strings.</returns>
        public static double Percentage(string source1, string source2, bool isCaseSensitive = true) => (double)CalculateSimilarity(source1, source2, isCaseSensitive, false);
        public static double Distance(string source1, string source2, bool isCaseSensitive = true) => (double)CalculateSimilarity(source1, source2, isCaseSensitive, true);
        public static double CalculateSimilarity(string source1, string source2, bool isCaseSensitive = true, bool getDistance = false)
        {
            if (!isCaseSensitive)
            {
                source1 = source1.ToLower();
                source2 = source2.ToLower();
            }
            if (source1 == source2)
                return getDistance ? 0 : 1.0f;
            // Split strings into sets of words and create HashSets
            HashSet<string> hashSet1 = new HashSet<string>(source1.Split(' '));
            HashSet<string> hashSet2 = new HashSet<string>(source2.Split(' '));
            double originalCount1 = hashSet1.Count;
            hashSet1.IntersectWith(hashSet2);
            double intersectionCount = hashSet1.Count;
            if (getDistance)
                return intersectionCount;
            double unionCount = originalCount1 + hashSet2.Count - intersectionCount;
            return (double)intersectionCount / unionCount;
        }
    }
}
