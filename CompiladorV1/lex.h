#define EOI		0		/*	finalizacion de la entrada			*/
#define SEMI		1		/*	;						*/
#define PLUS		2		/*	+						*/
#define TIMES		3		/*	*						*/
#define LP		4		/*	(						*/
#define RP		5		/*	)						*/
#define NUM_OR_ID	6		/*	numero decimal o indentificador			*/

extern char 	*yytext;		/*	Variable externa definida dentro de lex.c	*/
extern int	yyleng;			/*	Variables externas				*/
extern int	yylineno;

