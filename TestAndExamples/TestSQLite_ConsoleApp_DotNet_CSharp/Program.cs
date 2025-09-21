// See https://aka.ms/new-console-template for more information
using FuzzyPlusCSharp;

Console.WriteLine("Hello, World!");

FuzzyInst fuzzyInst = new(Fuzzy.StringMatchingAlgorithm_ID.iChapmanLengthDeviation);
bool b1 = fuzzyInst.IsSimilar("David", "Davie");
Console.WriteLine(b1);
string s = Fuzzy.HasWordsInSameOrder("This is a similar phrase test", "Phrases");
Console.WriteLine(s);