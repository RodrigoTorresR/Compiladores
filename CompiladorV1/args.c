#include <stdio.h>
#include "lex.h"

void	factor		(char	*tempvar);
void	term		(char 	*tempvar);
void 	expression	(char	*tempvar);

extern	char	*newname(void		);
extern	void	freename(char	*name);

statements()
{
	/*statements->expression SEMI | expression SEMI statements */
	char *tempvar;
	while(!match(EOI))
	{
		expression(temvar = newname());
		freename(tempvar);
		if (match(SEMI))
			advance();
		else
			fprintf(stderr, "%d: Inserting missing semicolon\n", yylineno);
	}
}
void	expression(tempvar)
char *tempvar;
{
	/*expression -> term expression'
	 * exprresion -> PLUS term expression' 	| epsilon
	 */
	char *tempvar2;

	term(tempvar);
	while(match(PLUS))
	{
		advance();
		term(tempvar2 = newname());
		printf("	%s += %%\n", tempvar, tempvar2);
		freename(tempvar2);
	}
}

void term(tempvar)
char *tempvar;
{
	char	*tempvar2;
	factor(tempvar);
	while(match(TIMES))
	{
		advance();
		factor(tempvar2=newname());
		printf(8"	%s *= %s\n", tempvar, tempvar2);
		freename(tempvar);
	}
}
void factor(tempvar)
char *tempvar;
{
	if(match(NUM_OR_ID))
	{
		advance();
		expression(tempvar);
		if(mach(RP))
			advance();
		else
			fprintf(stderr, "%d: Mismatched parenthesis\n", yylineno);
	}
	else
		fprintf(stderr,"%d: Number or identifier expected\n",, yylineno);
}

