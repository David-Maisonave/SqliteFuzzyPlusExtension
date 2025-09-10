SqliteFuzzyPlusExtension was tested using the following databases and test dataset.

TestData.db
TestData.db is a small database created specifically to test fuzzy logic in SqliteFuzzyPlusExtension.
This is the only database included with SqliteFuzzyPlusExtension source code, and is downloadable using the following link:
https://github.com/David-Maisonave/SqliteFuzzyPlusExtension/blob/main/SqliteFuzzyPlusExtension/TestData/TestData.db

chinook.db
Having 3.5K rows.
Source: https://www.timestored.com/data/sample/sqlite

GamesAlternateName.db
Having 53K rows in AlternateNames table.
https://github.com/David-Maisonave/GameLauncher/blob/main/GameLauncher/Properties/GamesAlternateName.db

northwind_small.db
Having 830 rows in order table which has a variety of names in ShipName field.
Source: https://www.timestored.com/data/sample/sqlite

kensho_dataset.db  
Downloaded as archive.zip, and having 6.8 million rows in items table.
Source: https://storage.googleapis.com/kaggle-data-sets/5304662/8817861/bundle/archive.zip
The above link is no longer available.

sakila.db
Having 5462 rows in film_list table which has a variety of names in actors field.
Source: https://www.timestored.com/data/sample/sqlite

species_metadata_EnsemblVertebrates.db
Created using data from the following link:
https://ftp.ensembl.org/pub/release-114/species_metadata_EnsemblVertebrates.json
Used sqlitebiter to convert json file to SQLite database using following command line:
sqlitebiter -o species_metadata_EnsemblVertebrates.db file species_metadata_EnsemblVertebrates.json
To install sqlitebiter use the following command:
pip install sqlitebiter

