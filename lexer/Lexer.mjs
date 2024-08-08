// Lexer.mjs

export class Lexer	{

	const fs = require('node:fs');	
	
	LexPatterns = []
	LexTokens = []
	LexTokens_rev = []
	Stack = []
	s = ''
	//_fs = fs;
	
	statusMsg = ''
	errorRecord = {}
	
	init()	{
		
		let _ = new this.installLexRules(this)
		//console.log("TEST4");
	}
	
	constructor(s, lexRules)	{
		
		this.s = s || 'You forgot to provide a language string to tokenize, silly!'
		
		if(lexRules)
			this.installLexRules = lexRules;
			
		else
			this.installLexRules = installLexRules;
		
		//init();
	}
	
	
	lex(s)	{
		
		if(this.LexPatterns.length<1)	{
		
			console.error("%cNo patterns & token types registered with this Lexer!", new Utils().error)
			return;
		}
		
		if(s)
			this.s = s
		
		s = String(this.s)
		
		let match = false
		let matches = []
		let IN = new String(s)
		
		let curr_s_length_matched = false
		let curr_s_length_matches = [{str: 'Null Entry', pattern: /\./ }]
		let i = 1
		let t_str = '';
		
		while(s)	{

			matches = []

			if(curr_s_length_matched)	{

				this.Stack.push(curr_s_length_matches.pop())
				//console.info(`%cPushed token: '${Stack[Stack.length-1].str}', (${Stack[Stack.length-1].pattern.toString()}) onto Stack.`, new Utils().info)

				curr_s_length_matched = false
				curr_s_length_matches = []

				if(s.length-(i-1)<=0)	{

					this.statusMsg = 'SUCCESS'
					this.errorRecord = {}
					
					console.log("%cSUCCESS: Lexer tokenized " + this.Stack.length + " tokens.", new Utils().success)
					return this.Stack;
				}

				s = s.substring(i-1)
				i = 1;
			}


			do	{

				let j = 0
				t_str = s.substring(0, i)
				match = false

				if(s.length<i)
					j = Number.MAX_SAFE_INTEGER - 1

				for (; j < this.LexPatterns.length; j++)
					if(this.LexPatterns[j].test(t_str))	{

						//console.log(`%cMatched pattern ${LexTokens[j]} via string: ${t_str}`, new Utils().success)
						match = true
						break;
					}

				if(match)	{

					matches.push({ str: t_str, pattern: this.LexTokens[j] })
					i++
				}

			} while(match)

			if(matches.length>0)	{

				let k = matches.length - 1
				let curr_len = matches[k].str.length
				let prev_len = curr_len

				let r_prev = null
				let r = null

				for(; k > -1; k--)	{

					
					r = matches.pop()
					curr_len = r.str.length

					if (prev_len == curr_len)	{

						r_prev = r
						prev_len = r.str.length
					}
					else
						break;
				}

				// r_prev contains "1st" & longest entry/match, unless r_prev
				// is null, in which case "r" contains the hit.
				if(!r_prev)
					curr_s_length_matches.push(r)
				else
					curr_s_length_matches.push(r_prev)

				
				curr_s_length_matched = true
				matches = [];
			}

			else { // No Matches, so Abort

				this.statusMsg = 'ERROR'
				console.error("%cError! Invalid String!", new Utils().error)
				return (this.errorRecord = { 'offset': IN.length - s.length, 'char': s[0] });
			}
		}
		
		return this.stack;
	}
	
	
    installToken(pattern, tokenStr) {

        this.LexPatterns.push(new RegExp(`^${pattern}\$`))
        this.LexTokens.push(tokenStr)
        this.LexTokens_rev[tokenStr] = this.LexPatterns.length - 1
            
        return this.LexPatterns.length - 1;
    }
	
	loadSourceFile( sfn ){
	
	this.fs.open(sfn, "r", function( err,file ){
		if( err )
		return undefined;}
	
	this.fs.readFile( fn, function( err,data ){
		if( err )
		return `Error: ${err}`;}
		
	let scLines = data.split("\n")
	return true;  )


    loadLexFile(fn) {

        this._fs.open(fn, "r", function(err, file)    {

            if(err) {
                return undefined;
            }
        });

        this._fs.readFile(fn, function(err, data) {

            if(err)
                return `Error: ${err}`;

            let lines = data.split("\n")

            for(var i = 0; i < lines.length; i++)   {
                
                let line = lines[i]
				if(line.trim()=='')
					continue
				
                let lr = line.split("$$")

                this.installToken(lr[0].trim(), lr[1].trim()); 
            }
			
			return true;
        });
    }
}


export class installLexRules	{
	
	constructor(lexer)	{
		
		this.lexer = lexer;
		
		this.installToken("[\\s]+", "WS")
		this.installToken("[\\t]", "TAB")
		this.installToken("[\\n]", "NL")
		
		this.installToken("[a-zA-Z_](([a-zA-Z_0-9])+)?", "VARIABLE")

		this.installToken("var", "VAR_KWD")
		this.installToken("continue", "CONT_KWD")
		this.installToken("break", "BREAK_KWD")
		this.installToken("function", "FNC_KWD")
		this.installToken("while", "WHILE_KWD")
		this.installToken("for", "FOR_KWD")
		this.installToken("if", "IF_KWD")
		this.installToken("do", "DO_KWD")

		this.installToken("[0-9]+", "NUM")
		this.installToken("[0-9]+([\\.][0-9+])", "FP")

		this.installToken("[\\+]", "PLUS")
		this.installToken("[\\-]", "MINUS")
		this.installToken("[\\*]", "MUL")
		this.installToken("[/]", "DIV")
		this.installToken("[\\^]", "EXP")

		this.installToken("===", "STRICT_EQ")
		this.installToken("==", "EQ")
		this.installToken("[\\=]", "EQUALS")

		this.installToken("[\\>]", "GT")
		this.installToken("[\\<]", "LT")

		this.installToken("[\\(]", "OPEN_BRACK")
		this.installToken("[\\)]", "CLOSE_BRACK")
		this.installToken("[\\[]", "OPEN_SQ_BRACK")
		this.installToken("[\\]]", "CLOSE_SQ_BRACK")
		this.installToken("[\\{]", "OPEN_CURLY_BRACK")
		this.installToken("[\\}]", "CLOSE_CURLY_BRACK")
		this.installToken("[\\\\]", "BACK_SLASH")

		this.installToken("[\\?]", "Q_MARK")
		this.installToken("[\\$]", "DOLLAR")
		this.installToken("[\\#]", "HASH")
		this.installToken("[\%]", "PERCENT")


		this.installToken("[\\.]", "PERIOD")
		this.installToken("[;]", "SCOLON")
		this.installToken("[\\:]", "COLON")
		this.installToken("[\\,]", "COMMA")

		this.installToken('"', "DBL_QUOTE")
		this.installToken("[\']", "S_QUOTE")
		this.installToken("[\`]", "BACK_TICK")

		this.installToken("[\\!]", "NOT")
		this.installToken("\\&", "AMP")
		this.installToken("\\|", "OR")
		this.installToken("\\~", "BITWISE_NOT")

		this.installToken("//[\S\s]*[\n]+", "SL_COMMENT");
		this.installToken("/[\*][\*]*[\n\S\s]*[\*][/]", "ML_COMMENT");
		
		return this.lexer;
	}
	
	
	installToken(pattern, tokenStr)	{
		
		//console.log("TEST2")
		
		let wrapped_pattern = new RegExp(`^${pattern}\$`)
		this.lexer.LexPatterns.push(wrapped_pattern)
		this.lexer.LexTokens.push(tokenStr)
		this.lexer.LexTokens_rev[tokenStr] = this.lexer.LexPatterns.length - 1
		
		//console.log("TEST3")
		return this.lexer.LexPatterns.length - 1;
	};
}


export class Utils	{
	
	constructor()	{
		
	}

	success="background: green; color: yellow;"
	error = "background: red; color: yellow;"
	warn  = "background: yellow; color: black;"
	info  = "background: blue; color: yellow;"
	
	black = {fg:30, bg:40, rgb:{r:0,g:0,b:0}}
	green = {fg:32, bg:42, rgb:{r:0,g:255,b:0}}
	red =	{fg:31, bg:41, rgb:{r:255,g:0,b:0}}
	yellow ={fg:33, bg:43}
	blue =	{fg:34, bg:44}
	magenta ={fg:35, bg:45}
	cyan =	{fg:36, bg:46}
	white =	{fg:37, bg:47}
	gray =	{fg:90, bg:100}
	brightRed ={fg:91, bg:101}
	brightGreen ={fg:92, bg:102}
	brightYellow ={fg:93, bg:103}
	brightBlue = {fg:94, bg:104}
	brightMagenta ={fg:95, bg:105}
	brightCyan ={fg:96, bg:106}
	brightWhite = {fg:97, bg:107}
	
	//_col1 = (16 + 36 * + R + 6 * G + B)
	// where r,g and b are 0 -> 5.
	// 2
	// https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
	/*
	
	// 8-bit:
	ESC[38;5;⟨n⟩m Select foreground color
ESC[48;5;⟨n⟩m Select background color
  0-  7:  standard colors (as in ESC [ 30–37 m)
  8- 15:  high intensity colors (as in ESC [ 90–97 m)
 16-231:  6 × 6 × 6 cube (216 colors): 16 + 36 × r + 6 × g + b (0 ≤ r, g, b ≤ 5)
232-255:  grayscale from black to white in 24 steps
	
	*/

	_colTest()	{
		
		// `\x1b[0m`
		// 3-4 bit
		return "\x1b[48;5;"+this._col1+"m" + "%s\x1b[0m";
	}
	
	c(fg,bg,opt)	{
		
		// \x1b[36m%s\x1b[0m
		// 0m resets all colors
		// \x1b is the ESC[ prefix for selecting a color
		// see: https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
		
		if(!(fg.length>0))	{
			
			switch(fg)	{
				
				case 0: fg = "black"; break;
				case 1: fg = "red"; break;
				case 2: fg = "green"; break;
				case 3: fg = "yellow"; break;
				case 4: fg = "blue"; break;
				case 5: fg = "magenta"; break;
				case 6: fg = "cyan"; break;
				case 7: fg = "white"; break;
				case 8: fg = "gray"; break;
				case 9: fg = "brightRed"; break;
				case 10:fg = "brightGreen"; break;
				case 11:fg = "brightYellow"; break;
				case 12:fg = "brightBlue"; break;
				case 13:fg = "brightMagenta"; break;
				case 14:fg = "brightCyan"; break;
				case 15:fg = "brightWhite"; break;
			
				default:
					fg = "white"; break;
			}		
		}

		if(!(bg.length>0))	{
			
			switch(bg)	{
				
				case 0: bg = "black"; break;
				case 1: bg = "red"; break;
				case 2: bg = "green"; break;
				case 3: bg = "yellow"; break;
				case 4: bg = "blue"; break;
				case 5: bg = "magenta"; break;
				case 6: bg = "cyan"; break;
				case 7: bg = "white"; break;
				case 8: bg = "gray"; break;
				case 9: bg = "brightRed"; break;
				case 10:bg = "brightGreen"; break;
				case 11:bg = "brightYellow"; break;
				case 12:bg = "brightBlue"; break;
				case 13:bg = "brightMagenta"; break;
				case 14:bg = "brightCyan"; break;
				case 15:bg = "brightWhite"; break;
			
				default:
					bg = "white"; break;
			}		
		}		
		
		let _fg = 7, _bg = 0;
		
		try	{
			_fg = this[fg].fg
			_bg = this[bg].bg
		}
		catch(e)	{
			
			// Dodgy colour refs passed in.
			console.log("\x1b["+this['brightYellow'].fg+"m"
			+ "\x1b["+this['brightBlue'].bg+"m"
			+ "%s" + "\x1b[0m",
			"The color values '"+fg+"' and '"+bg+"' are not accepted as a FG/BG color-pair by Utils. Is there a typo in one of them?");
			
			_fg = this["white"].fg, _bg = this["black"].bg;
		}
		
		let fStr = '';
		
		if(opt)	{
			/**
			Underscore = "\x1b[4m"
			Blink = "\x1b[5m"
			Reverse = "\x1b[7m"
			*/
			switch(opt)	{
				
				case "us": fStr += "\x1b[4m"; break;
				case "bl": fStr += "\x1b[5m"; break; // NB: blink and reverse don't work Node.js cmd-line/Windows 10
				case "rv": fStr += "\x1b[7m"; break;
				default: break;
			}
		}
			
		
		return (this.lfs = fStr + `\x1b[${_fg}m` + `\x1b[${_bg}m` + "%s" + `\x1b[0m`);
	}
	
	stub()	{
	
		return [];
	}
	
	swap(a, b)	{
		
		return { b, a };
	} // syntax: { b, a } = new Utils().swap(a, b) // but wouldn't { b, a } = { a, b } work as an inline?
	
	max(a, b)	{
		
		if(a>=b)
			return a;
		
		return b;
	}
	
	min(a, b)	{
		
		if(a<=b)
			return a;
		
		return b;
	}
	
	abs(a)	{
		
		if((a<0.0)||(a==-0.0))
			return -a;
		
		return a;
	}	
}
