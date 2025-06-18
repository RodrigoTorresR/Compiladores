char *Names[]={"t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7" };
char **Namep = Names;

char *newname()
{
	if (Namep >= &Names [sizeof(Names)/sizeof(*Names)])
	{
		fprintf(stderr, "%d: Expresion too complex\n", yylineno);
		exit(1);
	}
	return (*Namep++);
}
freename(s)
char *s;
{
	if(Name > Names)
		*--Name = s;
	else
		fprintf(stderr, "%d: (Internal error) Name stack undeerflow\n", yylineno);
}

