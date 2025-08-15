using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace FuzzyPlusCSharp.Misc
{
    public static class Normalize
    {
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
            return name;
        }
        public static string Phone(string name) => throw new NotImplementedException();
        public static string Social(string name) => throw new NotImplementedException();
        public static string Zip(string name) => throw new NotImplementedException();
        public static string Address(string name) => throw new NotImplementedException();
        public static string Date(string name) => throw new NotImplementedException();
        public static string Time(string name) => throw new NotImplementedException();
        public static string FileName(string name) => throw new NotImplementedException();
        public static string Number(string name) => throw new NotImplementedException();
        public static string Title(string name) => throw new NotImplementedException();
        public static string Fraction(string name) => throw new NotImplementedException();
        public static string Month(string name) => throw new NotImplementedException();
        public static string Year(string name) => throw new NotImplementedException();
        public static string Weight(string name) => throw new NotImplementedException();
    }
}
