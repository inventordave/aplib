# SimpleLexer
A simple lexer.
 
Usage:
 
See main.js in the package for a quick way to test the Lexer.

Test.html
Open the dev-console, and type runlexer(), optoinally with a token index to manually indicate which of the tokenized document buffer you wish to see the entry details for. Once you have run the function the first time, you can simply look at global object 'stack' to see the ordered list of tokens lexed from the source document. To choose the source document, click the left-hand "Open File." button and select the source code file you wish to Lex. (Currently, behaviour when reading a UTF-encoded input file rather than narrow-char (ASCII), is undefined. Won't be difficult for me to remedy that, though. 


As you can see, you simply do the following:
let lexer = new Lexer('Assuming you install suitable Lex patterns, this string will be successfully tokenized!', installLexRules)
let stack = lexer.lex()
 
Results are also stored in Lexer.Stack (Using above example method, you would peek at 'stack', but you can also peek at 'lexer.Stack'.)
 
There is a sample lex file called "js.txt" with the package, but it's lex rules are generic enough for the majority of programming language strings, and English-language strings, too.


Input lex file format:
 
1 pattern & token string per line, as so:
 
[0-9]+                      $$ "NUM"
 
The seperator between the pattern and the token string is $$
 
InventorDave.

