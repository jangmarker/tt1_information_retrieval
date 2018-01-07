[![Build status](https://ci.appveyor.com/api/projects/status/8g0562yqm3x3vb1j?svg=true)](https://ci.appveyor.com/project/jangmarker/tt1-information-retrieval) [![Build Status](https://travis-ci.org/jangmarker/tt1_information_retrieval.svg?branch=master)](https://travis-ci.org/jangmarker/tt1_information_retrieval) [![codecov](https://codecov.io/gh/jangmarker/tt1_information_retrieval/branch/master/graph/badge.svg)](https://codecov.io/gh/jangmarker/tt1_information_retrieval)
# TT1 Information Retrieval - Lösung Jan Marker

# Dependencies

The program is mainly based on the C++ standard library, except for:
* Catch (http://catch-lib.net/) - a unit testing framework for C++
* CLI11 (https://github.com/CLIUtils/CLI11) - framework to parse CLI parameters

The two dependencies are included in `3rdparty/` and are to no concern of a user.

The code uses features of C++17, including:
- structured bindings (not supported by CLion, KDevelop, QtCreator)
- string_view
- filesystem

It was tested with Visual Studio 15.0 2017 and GCC 7.2.1.

# Usage

**Use `--db=/path/to/corpus` to pass the path a directory containing .txt files.**

`--help` can be used to gain information about possible parameters:
```
Text Technologie 1 - Aufgabe 4 - Lösung Jan Marker
Usage: ./tt1_information_retrieval [OPTIONS] query...

Positionals:
  query TEXT ...              Query to the database

Options:
  -h,--help                   Print this help message and exit
  --db TEXT                   Path to the directory where the texts are located.
  --print-matrix              Show database matrix
  --save-matrix-csv           Save matrix to 'matrix.csv' in CSV format
```

See ./00_EXAMPLE_OUTPUT_AND_ANSWERS.md for some example invocations. Please note
that when saving the matrix you also need to provide a query, although the matrix
doesn't depend on the query.

# Code Organisation

## `cli.cpp`
* command line parsing
* setup of database
* query of database
* output of result
* (optional) output of matrix

## `database.{h,cpp}`
* calculation of term weights
* implementation of similarity measure
* storage of the documents
* storage of the weight matrix
  - a list of documents
  - each documents holds its term weights
* search (unordered)
* term frequencies over all documents

## `document.{h,cpp}`
* representation of a document
* id is the file name (without extension)
* stores term frequencies in the document
* stores term weights of document's terms
* stores euclidean norm for document's
  term weights (cache for similarity calculation)

## `fileaccess.{h,cpp}`
* namespace for interaction with files
* creation of document vector from a database directory
* creation of one document from one file in database
* writing the matrix to a CSV file

## `search.{h,cpp}`
* definition of Query type
  - document with special constructors to easily
    create document from user input
* definition of a search result
  - document id
  - similarity
* definition of sort and output operations over SearchResult

## `tokenizer.{h,cpp}`
* definition of Token type
  - a named type around std::wstring to
    be able to do tokenization by using `operator>>`
* `normalize` is used in `operator>>(stream, Token)` and
  in `Query` for normalization of word forms
  - to lower
  - removal of non-alphabetic characters
* all of this is done in the de_DE.UTF-8 locale

## `tst_*.cpp`
* tests of the respective code
* with `main_tst.cpp` providing the Catch library's test runner