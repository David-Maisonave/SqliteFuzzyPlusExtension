using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace FuzzyPlusCSharp.PhoneticMethods
{
    public static class Soundex
    {
        public const string Empty = "0000";

        private static readonly Regex Sanitizer = new Regex(@"[^A-Z]", RegexOptions.Compiled);
        private static readonly Regex CollapseRepeatedNumbers = new Regex(@"(\d)?\1*[WH]*\1*", RegexOptions.Compiled);
        private static readonly Regex RemoveVowelSounds = new Regex(@"[AEIOUY]", RegexOptions.Compiled);

        public static string Generate(string Phrase)
        {
            // Remove non-alphas
            Phrase = Sanitizer.Replace((Phrase ?? string.Empty).ToUpper(), string.Empty);

            // Nothing to soundex, return empty
            if (string.IsNullOrEmpty(Phrase))
                return Empty;

            // Convert consonants to numerical representation
            var Numified = Numify(Phrase);

            // Remove repeated numeric (characters of the same sound class), even if separated by H or W
            Numified = CollapseRepeatedNumbers.Replace(Numified, @"$1");

            if (Numified.Length > 0 && Numified[0] == Numify(Phrase[0]))
            {
                // Remove first numeric as first letter in same class as subsequent letters
                Numified = Numified.Substring(1);
            }

            // Remove vowels
            Numified = RemoveVowelSounds.Replace(Numified, string.Empty);

            // Concatenate, pad and trim to ensure X### format.
            return string.Format("{0}{1}", Phrase[0], Numified).PadRight(4, '0').Substring(0, 4);
        }

        private static string Numify(string Phrase)
        {
            return new string(Phrase.ToCharArray().Select(Numify).ToArray());
        }

        private static char Numify(char Character)
        {
            switch (Character)
            {
                case 'B':
                case 'F':
                case 'P':
                case 'V':
                    return '1';
                case 'C':
                case 'G':
                case 'J':
                case 'K':
                case 'Q':
                case 'S':
                case 'X':
                case 'Z':
                    return '2';
                case 'D':
                case 'T':
                    return '3';
                case 'L':
                    return '4';
                case 'M':
                case 'N':
                    return '5';
                case 'R':
                    return '6';
                default:
                    return Character;
            }
        }
    }
}
