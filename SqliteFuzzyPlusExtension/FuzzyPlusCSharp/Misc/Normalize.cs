using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Xml.Linq;

using USAddress;

namespace FuzzyPlusCSharp.Misc
{
    public static class Normalize
    {
        private static readonly AddressParser Parser = AddressParser.Default;
        // All Normalize functions returns a string, because if distance method usage is required, a string is needed.
        public static string FirstLastName(string name)
        {
            name = Regex.Replace(name, "[\\s][A-Za-z]\\.", "");
            name = Regex.Replace(name, "[\\s][A-Za-z]$", "");
            name = Regex.Replace(name, "[\\s][0-9][A-Za-z]{2}", "");
            name = Regex.Replace(name, "[\\s][JSjs][Rr]\\.?", "");
            name = Regex.Replace(name, "[\\s][Ii]+$", "");
            name = Regex.Replace(name, "[\\s][Ii]+\\s", "");
            name = Regex.Replace(name, "([A-Za-z]+)\\s*\\,\\s*([A-Za-z]+.*)", "$2 $1");
            name = Regex.Replace(name, "[^A-Za-z\\s]+", "");
            name = name.Replace("  ", " ");
            name = Regex.Replace(name, "([A-Za-z]+)\\s+[A-Za-z.]+\\s+([A-Za-z]+)", "$1 $2");
            return name;
        }
        public static string ReverseNames(string name)
        {
            name = Regex.Replace(name, "([A-Za-z]+)\\s+([A-Za-z]+)", "$2 $1");
            return name;
        }
        public static string Phone(string numberStr)
        {
            numberStr = Regex.Replace(numberStr, "(?i)ext[^0-9]*\\s?[0-9]+", "");
            numberStr = Number(numberStr);
            if (numberStr.StartsWith("1"))
                numberStr = numberStr.Substring(1);
            return numberStr;
        }
        public static string Zip(string numberStr)
        {
            numberStr = Regex.Replace(numberStr, ".*([0-9]{5})$", "$1");
            numberStr = Regex.Replace(numberStr, ".*([0-9]{5})[^0-9][0-9]{4}$", "$1");
            numberStr = Number(numberStr);
            if (numberStr.Length > 5)
                numberStr = numberStr.Substring(0, 5);
            return numberStr;
        }
        public static string Address(string address)
        {
            AddressParseResult normal = Parser.ParseAddress(address);
            address = normal.ToString();
            address = Regex.Replace(address, "(.*[0-9]{5})[^0-9][0-9]{4}$", "$1");
            return address;
        }
        public static string Date(string name) => throw new NotImplementedException();
        public static string Time(string name) => throw new NotImplementedException();
        public static string FileName(string name) => throw new NotImplementedException();
        // Number function returns a string instead of a number, because if distance method usage is required, a string is required
        public static string Number(this string input)
        {
            //input = Regex.Replace(input, "[^0-9]", "");
            return new string(input.Where(char.IsDigit).ToArray());
        }
        public static string Title(string name) => throw new NotImplementedException();
        public static string Fraction(string name) => throw new NotImplementedException();
        public static string Month(string name) => throw new NotImplementedException();
        public static string Year(string name) => throw new NotImplementedException();
        public static string Weight(string name) => throw new NotImplementedException();
    }
}
