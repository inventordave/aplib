// int_const char_const float_const id string enumeration_const

/**
definitions
%%
rules
%%
user code
*/


ID       			[a-zA-Z_][0-9a-zA-Z_]*
DIGIT    			[0-9]
float_const			[\+\-]?[0-9]+[\.][0-9]+
int_const			[\+\-]?[0-9]+
octal_int_const		[\+\-]?[\\][0-7]+
hex_int_const		[\+\-]?[\\][x][0-9a-fA-F]+
char_const			[\'][\\]?[\.][\']
string				[\"][\.]*[\"]

SL_COMMENT			[/]{2,2}[.]*
ML_COMMENT			[/][\*]+[.\n\r]*[\*]+[/]


APINT_KWD			["ap"|"AP"][_]{0,17}["integer"|"Integer"|"INTEGER"|"int"|"Int"|"INT"]
INT_KWD				"integer"|"Integer"|"INTEGER"|"int"|"Int"|"INT"

APFLOAT_KWD			["ap"|"AP"][_]{0,17}["float"|"Float"|"FLOAT"]
FLOAT_KWD			"float"|"Float"|"FLOAT"

APDOUBLE_KWD		["ap"|"AP"][_]{0,17}["double"|"Double"|"DOUBLE"]
DOUBLE_KWD			"double"|"Double"|"DOUBLE"

APFRACT_KWD			["ap"|"AP"][_]{0,17}["fract"|"Fract"|"FRACT"|"fractional"|"Fractional"|"FRACTIONAL"]
FRACT_KWD			"fract"|"Fract"|"FRACT"|"fractional"|"Fractional"|"FRACTIONAL"

STRUCT_KWD			"struct"|"Struct"|"STRUCT"
CHAR_KWD			"char"|"Char"|"CHAR"
STRING_KWD			"string"|"String"|"STRING"
PORT_KWD			"port"|"PORT"
AP_KWD				"ap"|"AP"

ARRAY_KWD			"array"|"Array"|"ARRAY"
TYPEDEF_KWD			"typedef"
INSTANCEOF_KWD		"instanceof"
SIZEOF_KWD			"sizeof"

UNARY_INC			[\+]{2,2}
UNARY_DEC			[\-]{2,2}
PLUS				'+'
MINUS				'-'
MODULO				'\%'
AMPERSAND			'\&'
DBLQUOT				'\"'
SGLQUOT				[\']

GT_EQ				'<'[\=]{1,}
GT					'>'
LT_EQ				'<'[\=]{1,}
LT					'<'

HASH_SYM			'\#'
ASTERISK			'*'
FORWARD_SLASH		'/'
BACK_SLASH			'\\'
SEMI_COLON			';'
COLON				':'
PERIOD				'\.'
CURLY_BRACE_OPEN	'{'
CURLY_BRACE_CLOSE	'}'
SQUARE_BRACE_OPEN	'['
SQUARE_BRACE_CLOSE	']'
ROUND_BRACE_OPEN	'('
ROUND_BRACE_CLOSE	')'
PLUS				'+'
MINUS				'-'
COMMA				','


XOR					'^'
BITWISE_NOT			'~'
LOGICAL_NOT			'!'
CONDITIONAL_OP		'?'
AT_SYM				'@'
LOGICAL_EQUALS		[\=]{2,}
ASSIGN_OP			[\=]

NL					[\n]




end_of_file			‘<<EOF>>’
