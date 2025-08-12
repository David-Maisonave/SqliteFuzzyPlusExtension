using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FuzzyPlusCSharp.DistanceMethods
{
    public static class PhraseTokenize
    {
        /// <summary>
        ///     Calculate the number of key words not in each others phrase (All phrase comparisons functions in this class are case INSENSITIVE)
        /// </summary>
        /// <param name="source1">First string</param>
        /// <param name="source2">Second string</param>
        /// <param name="simplify">Set to true in order to remove (A,The), numbers, abbreviated letters, non-alpha</param>
        /// <param name="insertSpacesBetweenCapitalLetters">True to insert spaces between capital letters. IE "MakeThisNormal" converts to "Make This Normal"</param>
        /// <returns>
        ///     Returns the number of key words not in each others phrase
        /// </returns>
        public static int Distance(string source1, string source2, bool isCaseSensitive = true, bool simplify = false, bool insertSpacesBetweenCapitalLetters = true)
        {
            Fuzzy.FixIfIsCaseSensitive(ref source1, ref source2, isCaseSensitive);
            string[] list1 = Fuzzy.GetKeywordList(ref source1, simplify, insertSpacesBetweenCapitalLetters);
            string[] list2 = Fuzzy.GetKeywordList(ref source2, simplify, insertSpacesBetweenCapitalLetters);
            int misMatchCount = 0;
            foreach (string s in list1)
                if (!list2.Contains(s))
                    ++misMatchCount;
            foreach (string s in list2)
                if (!list1.Contains(s))
                    ++misMatchCount;
            return misMatchCount;
        }
    }
    public static class SimplePhraseTokenize
    {
        public static int Distance(string source1, string source2, bool isCaseSensitive = true) => PhraseTokenize.Distance(source1, source2, isCaseSensitive, true);
    }
}
