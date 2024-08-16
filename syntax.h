// SYNTAX_H

// 1. From the root of the text file,
// 2. Feed buffer through lexer, for keyword granularity.
// 3. feed that buffer through parser, we now have language constructs.

// a syntax.cfg file for the file format (".c", ".js" etc )
// reserved words
// keywords.
// operators
// literals (num, ascii etc)
// comment lines (& blocks)


macroEXP: LABEL (=|==) LITERAL
MACRO: '#' define|ifndef|ifdef|if (ws)+ macroEXP	"\\"?\n"

MACROEND: '#' endif
"if" (ws)* "(" (ws)* conditional (ws)* ")" (ws)* (STTMNT|STTMNTBLOCK)



