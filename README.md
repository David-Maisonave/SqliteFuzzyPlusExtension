# SqliteFuzzyPlusExtension
SqliteFuzzyPlusExtension is a SQLite Fuzzy Extension which is build using both C/C++ and CSharp libraries. The Visual Studio solution builds 2 DLL (C++ & C#).
95% of the source is taken from other fuzzy libraries like [SQLean](https://github.com/nalgeon/sqlean), [Edlib](https://github.com/Martinsos/edlib), [SimMetricsCore](https://github.com/HamedFathi/SimMetricsCore), [SimMetrics.Net](https://github.com/StefH/SimMetrics.Net), [soenneker.utils.string.jaccardsimilarity](https://github.com/soenneker/soenneker.utils.string.jaccardsimilarity).

## Using SqliteFuzzyPlusExtension
The two DLL are both required (SqliteFuzzyPlusExtension.dll and FuzzyPlusCSharp.dll).
### Important Note!!!
When using SqliteFuzzyPlusExtension.dll with an executable like **DB Browser for SQLite**, the FuzzyPlusCSharp.dll file MUST be in the same directory as the executable (**DB Browser for SQLite.exe**). While the SqliteFuzzyPlusExtension.dll can be located anywhere.
