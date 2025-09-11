# TestAndExamples
## Content
- [Projected completion schedule](#projected-completion-schedule)
- [Project Requirements](#project-Requirements)
- [Example Projects](#example-projects)
  - [Visual Studio Example Projects](#visual-studio-example-projects)
  - [GCC (MinGw) Example Projects](#gcc-mingw-example-projects)
- [TestDatabase](#TestDatabase)
- [Test Projects](#test-projects)
## Projected completion schedule
- Important!!!! At this stage (**beta release**) most of the test and example projects are incomplete or empty.
- The following are the test and example project projected completion schedule.
  - 1.0.0 for all test projects.
  - 1.0.0 for the Visual Studio projects under Example_VS folder for languages C, C++, and C#.
  - 1.0.2 for the Visual Studio projects under Example_VS folder for Python.
  - 1.0.3 for the Visual Studio projects under Example_VS folder for Visual Basic.
  - 1.0.5 for the Visual Studio projects under Example_VS folder for F#.
  - 1.0.7 for the GCC projects under Example_GCC folder for languages C and C++.
  - 1.0.9 for the GCC projects under Example_GCC folder for languages Objective-C and Objective-C++.
  - 1.1.0 for the GCC projects under Example_GCC folder for Rust. (Implementation is not certan at this time)
  - 1.1.5 for the GCC projects under Example_GCC folder for Ada. (Implementation is not certan at this time)
  - 1.1.7 for the GCC projects under Example_GCC folder for D Language. (Implementation is not certan at this time)
  - 1.1.9 for the GCC projects under Example_GCC folder for languages Fortran and Go. (Implementation is not certan at this time)
## Project Requirements
- Most of the projects have names that are self explanatory. 
- The following rules apply to test projects and example projects:
  - All the test and example projects require FuzzyPlusCSharp.DLL and most require SqliteFuzzyPlusExtension.DLL.
  - Project files that have Fuzzy in the name and do NOT have SQLite in the name, are projects that don't need SQLite3.DLL.  
  - **Most** projects that have SQLite in the name require SQLite3.DLL to exist in same folder as the executable. The SQLite3.DLL is usually runtime loaded via LoadLibrary function.
	- The exception to this rule are projects TestSQLite_ConsoleApp_Cpp and ExampleSQLite_CPP which are projects that are built with SQLite3 code included in the project.
## Example Projects
### Visual Studio Example Projects
- All VS example projects where created using Microsoft Visual Studio Community 2022 (64-bit) - Current Version 17.14.14.
  - Some Visual Studio extensions where used for languages like Python, PHP, and Fortran.
  - Visual Studio extensison where used for GCC projects listed under Eamples_VS folder.
- Project Example List:
  - [ExampleFuzzy_C](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/tree/main/TestAndExamples/Eamples_VS/ExampleFuzzy_C)
  - [ExampleFuzzy_CPP](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/tree/main/TestAndExamples/Eamples_VS/ExampleFuzzy_CPP)
  - [ExampleFuzzy_DotNet_C#](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/tree/main/TestAndExamples/Eamples_VS/ExampleFuzzy_DotNet_C%23)
  - [ExampleFuzzy_DotNetFramework_C#](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/tree/main/TestAndExamples/Eamples_VS/ExampleFuzzy_DotNetFramework_C%23)
  - [ExampleFuzzy_DotNetFramework_CPP](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/tree/main/TestAndExamples/Eamples_VS/ExampleFuzzy_DotNetFramework_CPP)
  - [ExampleSQLite3_C](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/tree/main/TestAndExamples/Eamples_VS/ExampleSQLite3_C)
  - [ExampleSQLite3_CPP](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/tree/main/TestAndExamples/Eamples_VS/ExampleSQLite3_CPP)
  - [ExampleSQLite3_DotNet_C#](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/tree/main/TestAndExamples/Eamples_VS/ExampleSQLite3_DotNet_C%23)
  - [ExampleSQLite3_DotNetFrameWork_C#](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/tree/main/TestAndExamples/Eamples_VS/ExampleSQLite3_DotNetFrameWork_C%23)
  - [ExampleSQLite3_DotNetFrameWork_CPP](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/tree/main/TestAndExamples/Eamples_VS/ExampleSQLite3_DotNetFrameWork_CPP)
  - [ExampleSQLite3_DotNetFrameWork_F#](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/tree/main/TestAndExamples/Eamples_VS/ExampleSQLite3_DotNetFrameWork_F%23)
  - [ExampleSQLite3_DotNetFrameWork_VisualBasic](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/tree/main/TestAndExamples/Eamples_VS/ExampleSQLite3_DotNetFrameWork_VisualBasic)
  - [ExampleSQLite3_F#](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/tree/main/TestAndExamples/Eamples_VS/ExampleSQLite3_F%23)
  - [ExampleSQLite3_MakeFileGcc_CPP](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/tree/main/TestAndExamples/Eamples_VS/ExampleSQLite3_MakeFileGcc_CPP)
  - [ExampleSQLite3_PHP](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/tree/main/TestAndExamples/Eamples_VS/ExampleSQLite3_PHP)
  - [ExampleSQLite3_Python](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/tree/main/TestAndExamples/Eamples_VS/ExampleSQLite3_Python)
  - [ExampleSQLite3_VisualBasic](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/tree/main/TestAndExamples/Eamples_VS/ExampleSQLite3_VisualBasic) 
### GCC (MinGw) Example Projects

## TestDatabase
- The TestDatabase folder contains SQL files used to test **kensho_dataset.db** and **GameNames.db** databases. These databases are too large to post in GitHub. 
- See the follow link for databases source details: [TestDatabase](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/edit/main/TestAndExamples/TestDatabase)
- This project does include one database in GitHub:
  - **TestDB.db** which is a small database used for testing fuzzy functions.
  - See the following link to download TestDB.db: [TestDB.db](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/SqliteFuzzyPlusExtension/TestData)
  - The above link also includes SQL scripts used to test fuzzy functions.
	- All the SQL scripts where run using [DB Browser for SQLite](https://sqlitebrowser.org/dl/) with the SqliteFuzzyPlusExtension loaded as an extension.
## Test Projects
- [TestFuzzy_ConsoleApp_DotNetFrameworkCpp](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/edit/main/TestAndExamples/TestFuzzy_ConsoleApp_DotNetFrameworkCpp)
- [TestFuzzy_ConsoleApp_DotNetFrameworkCSharp](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/edit/main/TestAndExamples/TestFuzzy_ConsoleApp_DotNetFrameworkCSharp)
- [TestSQLite_ConsoleApp_Cpp](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/edit/main/TestAndExamples/TestSQLite_ConsoleApp_Cpp)
- [TestSQLite_ConsoleApp_DotNet_CSharp](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/edit/main/TestAndExamples/TestSQLite_ConsoleApp_DotNet_CSharp)
- [TestSQLite_ConsoleApp_DotNetFrameWork_CSharp](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/edit/main/TestAndExamples/TestSQLite_ConsoleApp_DotNetFrameWork_CSharp)
- [TestSQLite3_ConsoleApp_DotNetFrameWork_CPP](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/edit/main/TestAndExamplesTestSQLite3_ConsoleApp_DotNetFrameWork_CPP/)
- [UnitTestConsole_C_Runner](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/edit/main/TestAndExamples/UnitTestConsole_C_Runner)
- [UnitTestCreator_PostCodeModifier](https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/edit/main/TestAndExamples/UnitTestCreator_PostCodeModifier)

