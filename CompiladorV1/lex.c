#include "lex.h"		//libreria propia creada para guardar las definiciones de los tokens
#include <stdio.h>
#include <ctype.h>
					//VARIABLES USADAS EN LEX.H
char		*yytext	=	"";	/*Lexema (no terminado con '\0'	*/
int 		yyleng	=	0;	/*lexema de longitud 0		*/
int 		yylineno=	0;	/*Entrada de la linea numero	*/

lex()					//Funcion
{//NOTA para las variables *apuntador la operacion ++apuntador se le suma un "desplazamiento" del tamaño del
 //tipo de dato de *apuntador, si es entreo 4 bytes si es un caracter ASCII 1 byte
	static char input_buffer[128];	//variable estatica, conservara su valor fuera de la funcion
	char	*current;		/*la primera variable contiene el buffer de caracteres de entrada
  					la segunda *current apunta a una posicion dentro del buffer	*/
	current = yytext + yyleng;	/*movemos current al siguiente lexema 				*/
	while (1)			/*Conseguimos el siguiente lexema				*/
	{	
		//--Recorremos el Buffer de Entrada insertando caracteres de  salto de linea y descartando
		//--espacios vacios-//
		while(!*current)	/*mientras no se apunte al final del buffer			*/
		{			/*Obtenga nuevas líneas, omitiendo cualquier 
					  espacio en blanco inicial en la línea, hasta que se encuentre
					  una línea que no esté en blanco	*/
			current = input_buffer; //posicionamos el apuntador "current" al inicio del buffer
			if(!gets(input_buffer)) //si no podemos encontrar alguna caracter en el buffer
			{
				*current='\0'; 	//asumiremos que es un final de cadena y no hay mas caracteres
				return EOFI;	//y enviaremos un mensaje de "FIN DE ARCHIVO"
			}
			++yylineno;	//incrementamos la cuenta del número de lineas
			while(isspace(*curren))	//verificamos si estamos mirando un espacion en blanco
				++current;	//si es asi ignoramos el espacio y movemos el apuntador "current"
		}
		//--al final hemos recorrido "input_buffer" note que *current apunta al final del arreglo-//
		for(; *current; ++current) //No hay valor inicial para el for, avanzaremos un espacio el cursor
		{	/*Comenzamos a revisar los Tokens dentro de "*current" para clasificarlos*/
			yytext=current;	//tomamos el valor del cursor
			yyleng=1;	//reiniciamos yyleng para comenzar a revisar los token dentro de "*cursor"

			switch(*current)
			{
				case EOF: return EOI	;
				case ';': return SEMI	;
				case '+': return PLUS	;
				case '*': return TIMES	;
				case '(': return LP	;
				case ')': return RP	;
				case '\n':		//Descartar saltos de linea
				case '\t':		//tabuladores
				case ' ' : break;	//espacios en blanco 
				default:		//El caracter no corresponde a ninguno de los anteriores
					if(!isalnum(*current)) //y no es un numero tampoco se envia Error
						fprintf(stderr, "Ignoring illegal input <%c> \n", *current);
					else
					{
						while(isalnum(*current)) //El valor numerico se deja tal cual
							++current;//y se mueve el apuntador una posicion
						yyleng=current - yytext;//ajustamos la longitud del "desplazamiento"
						return NUM_OR_ID;//regresamos la clase NUM_OR_ID
					}
					break;					
	}
}
static int Lookahead = -1;	/*Token "vistazo hacia adelante"*/
/*
int match(token)	//Prototipo de la funcion match(token) regresa un entero y acepta un token, pero no tiene
int token;		//definicion ??? la variable token parece ser definida despues de su uso y viene la
{			//definicion de la funcion, creo que esta incorrecto debe ser asi:
*/
int token;
int match(token)
{
	/*Regresa VERDADERO si "token" coincide con el simbolo de busqueda anticipada */
	if (Lookahead == -1 )
		Lookahead = lex();
	return token == Lookahead;
}
void advance()
{	/*Avanza la mirada hacia adelante hasta el siguiente símbolo de entrada. */
	Lookahead = lex();
}

