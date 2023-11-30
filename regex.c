// REGEX_C

#include "wregex.h"

// FROM "wregex.h"::


/*
 *1	wregex
 *#	This is my regular expression engine implementation. It supports a fairly
 *#	large language, with curly braces, anchors, sub-match extraction, back
 *#	references and lazy (non-greedy) evaluation.\n
 *# 
 *#	This document describes the API used for embedding {*wregex*} into an
 *#	application.
 *# Please refer to the {{README.md}} for a more detailed description of the
 *# syntax, symantics and internal aspects of {*wregex*}.
 *{
 **	In general, a regular expression is compiled into a {{wregex_t}} structure using
 *#	{{wrx_comp()}}.
 **	This {{wregex_t}} structure is then matched against one or more strings using
 *#	the {{wrx_exec()}} function.
 **	When everything is done, the {{wregex_t}}'s memory is deallocated with the
 *#	{{wrx_free()}} function
 *#
 **	If errors happen along the way, their meanings can be found using the
 *#	{{wrx_error()}} function.
 *}
 *#	The file {{wgrep.c}} example program demonstrates this process. It contains an example 
 *# that demonstrates the library by using it in a grep-like utility.\n
 *#
 *# The file {{test.c}} contains a series of unit tests that the engine is supposed to
 *# handle.
 */
 
 