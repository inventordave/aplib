# SimpleLexer_C--

A simple lexer, written in even simpler C, that performs even simpler tokenizatin of an input source file.
Takes as input a lexer file that defines the token types, and their regexps, and passes the linear
sequence of parsed (at the lexical level) tokens.



# Below is a 'hint' sequence to help understand the pointer
# type (char***), which is "A pointer to a pointer of pointers",
# used in the body-file, "lexer.c", by the data structure
# 'LexInstance', defined in "lexer.h".
	
	char*** x;
	char** y = *x;
	char* z_0 = *y;
	char* z_1 = *(++y);
	

InventorDave (2024).
(c) LEE/DAVELIB/Barnyard.
Licensed under the whimsical, but true in letter, and spirit, DAVELICENSE 1.0
