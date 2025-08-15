using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FuzzyPlusCSharp.DistanceMethods
{
    public class INeedlemanWunsch : FuzzyPlusCSharp.DistanceMethods.IDistance
    {
        public double Percentage(string source1, string source2, bool isCaseSensitive = true) => NeedlemanWunsch.Percentage(source1, source2, isCaseSensitive);
        public double Distance(string source1, string source2, bool isCaseSensitive = true) => NeedlemanWunsch.Distance(source1, source2, isCaseSensitive);
    }
    /// <summary>
    /// A class for comparing strings via the Needleman-Wunsch algorithm
    /// </summary>
    public class NeedlemanWunsch
    {
        /// <summary>
        /// Calculates the similarity percentage between two strings using the Needleman-Wunsch algorithm.
        /// </summary>
        /// <param name="source1">The first string.</param>
        /// <param name="source2">The second string.</param>
        /// <returns>The similarity percentage between the two strings.</returns>
        public static double Percentage(string source1, string source2, bool isCaseSensitive = true)
        {
            if (!isCaseSensitive)
            {
                source1 = source1.ToLower();
                source2 = source2.ToLower();
            }
            if (source1 == source2)
                return 1.0f;
            int similarityScore = CalculateSimilarity(source1, source2);
            double maxPossibleScore = Math.Max(source1.Length, source2.Length);
            double similarityPercentage = 1 - (similarityScore / maxPossibleScore);
            return similarityPercentage;
        }
        public static double Distance(string source1, string source2, bool isCaseSensitive = true)
        {
            if (!isCaseSensitive)
            {
                source1 = source1.ToLower();
                source2 = source2.ToLower();
            }
            return CalculateSimilarity(source1, source2);
        }
        public static int CalculateSimilarity(string source1, string source2)
        {
            int[,] matrix = new int[source1.Length + 1, source2.Length + 1];
            for (int i = 0; i <= source1.Length; i++)
                matrix[i, 0] = i;
            for (var j = 1; j <= source2.Length; j++)
                matrix[0, j] = j;
            // Fill in the matrix
            for (int i = 1; i <= source1.Length; i++)
            {
                for (int j = 1; j <= source2.Length; j++)
                {
                    int cost = source1[i - 1] == source2[j - 1] ? 0 : 1;
                    int deletion = matrix[i - 1, j] + 1;
                    int insertion = matrix[i, j - 1] + 1;
                    int substitution = matrix[i - 1, j - 1] + cost;
                    matrix[i, j] = Math.Min(Math.Min(deletion, insertion), substitution);
                }
            }
            // The similarity score is the value in the bottom-right cell of the matrix
            return matrix[source1.Length, source2.Length];
        }
    }
}
