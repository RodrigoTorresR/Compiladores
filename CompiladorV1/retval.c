#include <stdio.h>
#include "lex.h"

char 	*factor		(void);
char	*term		(void);
char	*expresion	(void);

extern	char *newname	(void		);
extern	void freename	(char	*name	);

statements()
{
	/*statements -> expression SEMI | expression SEMI statements */
	
	char *tempvar;

	while (!match(EOI))
	{
		termpvar = expresion();
		if(match(SEMI))
			advance();
		else
			fprint(stderr, "%d: Inserting missing semicolon\n", yylineno);
		freename(tempvar);
	}
}
char	*expresion()
{
	/*expression -> term expression'
	 * expresion' -> PLUS term expression' | epsilon
	 */
	 char *tempvar, *tempvar2;
	 
	 tempvar=term();
	 while(match(PLUS))
	 {
		 advance();
		 tempvar=term();
		 printf("	%s += %s\n", tempvar, tempavar2);
		 freename(tempvar2);
	 }
	 return tempvar;
}
char	*term()
{
	char 	*tempvar, *tempvar2;

	tempvar = factor();
	while(match(TIMES))
	{
		advance();
		tempvar2=factor();
		printf("	%s *= %s\n", tempvar, tempvar2);
		freename(tempvar2);
	}
	retun tempvar;
}
char	*factor()
{
	char *tempvar;
	if(match(NUM_OR_ID))
	{
		/*Print the asignment instruction, The %0,. *s conversion is a form of %X.Ys, where X is the field
		 * width and Y is the maximum number of characters that will be printed (even if the string is
		 * longer). I'm using the &0.*s to print the string because it's not \0 terminated. The field has a
		 * defaultwidth of 0, but it will grown the size needed to print the string. The ".*" tells printf()
		 * to take the  maximum-number-of-characters count from the next argument (yyleng).
		 */
		printf("	%s = %0.*s\n", tempvar=newname(), yyleng, yytext);
		advance();
	}
	else if(match(LP))
	{
		advance();
		tempvar=expression();
		if(match(RP))
			advance();
		else
			fprintf(stderr, "%d: Mismatched parenthesis\n", yylineno);
	}
	else
		fprintf(stderr,"%d: Number or idenifier expectd\n", yylineno);
	return tempvar;
}





