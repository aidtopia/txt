TXT
Adrian McCarthy

# The TXT Project

## Overview

The TXT Project will be a series of videos about how computers process text, with open source code samples.  The topic may be not be as flashy as graphics or as nerdy as mathematics, but text seems to be an unfilled niche.  Programming forums, like Stack Overflow, are filled with questions about converting string types, searching, sorting, parsing, etc.

I intend to make each episode tightly focused and therefore short.  This should allow people to use the videos as reference material, watching just the bits they need or are interested in, without wading through preliminaries that they don't need.  Video descriptions and/or end cards will link to related videos as other topics are mentioned.  But topics will build on each other, so simply watching the episodes in order should be satisfying as well.

Code samples and video transcripts will be available in the GitHub repository.

## Scope

The broad topics I consider in scope for this project are:

* Characters sets, code pages
* Unicode and Unicode encodings like UTF-8
* String types
* Text files
* Sorting and searching with text
* Windows-specific details (e.g., ANSI vs. Unicode)
* Regular expressions
* Lexing and parsing
* Formatted output
* Higher level text data structures, as used by editors

Code examples will mostly be in C++, but may include some C and Python examples, too.  Generally, they should be portable, except for the cases where they're specifically illustrating Windows issues.

## Episode

### Completed

This will have a list of episode numbers, topics, and URLs for watching the completed videos.

### In Production

- Hello World

  Preliminaries for people who want to code along.  Will show how to set up a Visual Studio project and make a quick Hello World program to ensure the development environment is configured properly.

### Anticipated

This is a fluid list of specific episode topics that I'm considering.

- C character types
- "C strings" zero-terminated strings
- C++ character types
- C++ `std::string`s
- C++ `std::string_view`s
- ASCII
- EBCDIC
- Code Pages
- Text file encodings
- Guessing a code page
- Unicode code points
- UCS-2, UTF-32, UTF-16
- Unicode BOM
- UTF-8 and validation
- `TCHAR`s and related macros
- Counting lines (line terminators)
- Counting words (FSA for simple tokenization)
- lexicographic comparisons
- sorting
- eliminating duplicates
- building a lexicon
- hashing
- hash tables
- bloom filters
- writing a spelling checker
- writing a spelling corrector
- tries
- building a KWIC index (suffix arrays)
- regular expressions
- C and C++ trigraphs and digraphs
- Windows console versus Posix style terminals
- Modern Windows console/pseudo terminal
- `strcpyn` doesn't do what you think
- searching for a substring
- searching for multiple substrings
- searching for expression matches
- Unicode normalization
- string interning
- integers to strings
- floating point numbers to strings
- localized string formatting
- gap buffers
- line buffers
- Memory mapping text files
- piece tables
- a lexical analyzer framework
- a parsing framework
- recursive descent parsing
- quoting and escaping
- punycode
- emoji in Unicode???
- Klingon not in Unicode???
- Bidi
- Dangers of `fseek` in text files
- C character classification functions
- C preprocessor
- glyphs and grapheme clusters
- Unicode scripts
- font linking
- Visual Studio debugging visualizers for text
- Cords
- Windows debug output window
- `std::endl`
- C++ `std::ostream`
