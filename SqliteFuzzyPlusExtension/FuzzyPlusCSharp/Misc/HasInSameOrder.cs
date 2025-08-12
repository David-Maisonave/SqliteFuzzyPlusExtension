using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FuzzyPlusCSharp.Misc
{
    public static class HasInSameOrder
    {
        public static string HasCharInSameOrder(this string word) => HasCharInSameOrder(word, "%"); // Needed for CPP code access
        public static string HasCharInSameOrder(this string word, string sep) // SQL function extension
        {
            string returnWord = "";
            foreach (char c in word)
                returnWord += $"{c}{sep}";
            return $"{sep}{returnWord}";
        }
        public static string HasWordsInSameOrder(string words, string fieldToCompare) => HasWordsInSameOrder(words, fieldToCompare, false); // Needed for CPP code access
        public static string HasWordsInSameOrder(string words, string fieldToCompare, bool doNearWordSearch, int minimumWordLenForWordInWordMatch = 1, bool simplify = false) // SQL function extension
        {
            string[] keywords = Fuzzy.KeywordList(words, simplify);
            string returnStr = "";
            for (int i = 0; i < keywords.Length; ++i)
            {
                if (keywords[i].Length >= minimumWordLenForWordInWordMatch)
                {
                    string nearWordSearch = doNearWordSearch ? $" OR {fieldToCompare} LIKE '%{Fuzzy.HasCharInSameOrder(keywords[i])}%' " : "";
                    returnStr += $"({fieldToCompare} LIKE '%{keywords[i]}%'  {nearWordSearch}) ";
                }
                else
                    returnStr += $"(' '||{fieldToCompare}||' ' LIKE '% {keywords[i]} %') ";
                if (i + 1 < keywords.Length)
                    returnStr += " + ";
            }
            return returnStr;
        }
    }
}
