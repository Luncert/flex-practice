%option   warn nodefault
%option   yylineno
%option   outfile="scanner.c" header-file="scanner.h"
%option   noyywrap
NUMBER [0-9]+
VOID void
STR str
STRING string
RETURN return
IF if
ELSE else
INT int
WHILE while
CMP >|<|≥|≤
PRINT print
SCAN scan
letter [A-Za-z]
ID ({letter}|[_])({letter}|{NUMBER}|[_])*

SEMI [;]
COMMA [,]
ASSIGN [=]
PLUS [+]
MINUS [-]
STAR [*]
DIV [/]
LP \(
RP \)
LB \[
RB \]
LC \{
RC \}
BAI %
EN \/\/
END \n\n\n\n\n|\t\t\t\t\t\t\t\t

%{
    enum yytokentype {
	BAI=899,
	SEMI=901,
	COMMA=902,
	PLUS=904,
	MINUS=905,
	STAR=906,
	DIV=907,
	LP=908,
	RP=909,
	LB=910,
	RB=911,
	LC=912,
	RC=913,
	NUMBER = 258,
	EOL = 259,
	ID = 112,
	WHILE = 113,
	ELSE = 114,
	RETURN = 115,
	PRINT = 1116,
	SCAN = 117,
	INT =  301,
	STR =302,
	VOID = 303,
	STRING = 304,
	IF=305,
	CMP=306,
	ASSIGN=903,
	EN=904,
	END=999,
};
%}
%%
{COMMA} {return COMMA;}
{SEMI} {return SEMI;}
{ASSIGN} {return ASSIGN;}
{PLUS} {return PLUS;}
{MINUS} {return MINUS;}
{STAR} {return STAR;}
{DIV} {return DIV;}
{LP} {return LP;}
{RP} {return RP;}
{LB} {return LB;}
{RB} {return RB;}
{LC} {return LC;}
{RC} {return RC;}
{BAI} {return BAI;}
{RETURN} {return RETURN;}
{VOID}  {return VOID;}
{IF} {
    return IF;
}
{ELSE} {
    return ELSE;
}
{WHILE} {
    return WHILE;
}
{NUMBER} {
    return NUMBER;
}
{INT} {
    return INT;
}
{CMP} {
    return CMP;
}
{STR} {return STR;}
{STRING} {return STRING;}
{PRINT} {return PRINT;}
{SCAN} {return SCAN;}
{END} {
	return END;
	exit(0);
}
{letter} { 
	return ID;}

\n	{ return EOL; }
[ \t] { /* ignore whitespace */ }
. {
/*ABANDON THESE CHARACTORS*/
}
"//".* {}
{ID} {
    return ID;
}	
%%