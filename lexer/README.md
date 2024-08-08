# SimpleLexer
A simple lexer.
 
 Usage:
 
The Lexer is in an mjs file (it's in ES6 syntax, and module format). See main.js in the package for a quick way to test the Lexer.

node main.js

As you can see, once the import() Promise has returned, you simply do the following:
 
let lexer = new Lexer('Assuming you install suitable Lex patterns, this string will be successfully tokenized!', installLexRules)
let stack = lexer.lex()
 
Results are also stored in Lexer.Stack (Using above example method, you would peek at 'stack', but you can also peek at 'lexer.Stack'.)
 
There is a sample lex file called "js.txt" with the package, but it's lex rules are generic enough for the majority of programming language strings, and English-language strings, too.


 Input lex file format:
 
 1 pattern & token string per line, as so:
 
 [0-9]+                      $$ "NUM"
 
 The seperator between the pattern and the token string is $$
 
 InventorDave.

