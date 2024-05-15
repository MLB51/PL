/*------------------------------ plp4.l -------------------------------*/
/* DEFINICIONES */

D    [0-9]
L    [a-zA-Z]
LD   [0-9a-zA-Z]

%{
#include <string.h> 
#include <string>
#include <iostream>

using namespace std;

#include "comun.h"
#include "plp4.tab.h"

int ncol = 1,
    nlin = 1;

int findefichero = 0;

int ret(int token);  
// función que actualiza 'nlin' y 'ncol' y devuelve el token

void msgError(int nerror, int nlin,int ncol,const char *s);
// función para producir mensajes de error

%}


%%
%{
/* ####################################################################################################### */
/* ####################################################################################################### */
/* ####################################################################################################### */
/* REGEX */

/* codigo local */
%}

" "                {ncol++;}
[\t]               {ncol++;}
[\n]               {nlin++;ncol=1;}



"main"              {return ret(main);}
"int"               {return ret(int);}
"float"             {return ret(float);}
"printf"            {return ret(printf);}
"scanf"             {return ret(scanf);}
"if"                {return ret(if);}
"else"              {return ret(else);}
"while"             {return ret(while);}
"for"               {return ret(for);}

{L}({LD})*         {return ret(id);}
{D}+               {return ret(numentero);}
{D}+(\.){D}+       {return ret(numreal);}

","                {return ret(coma);}
";"                {return ret(pyc);}
"("                {return ret(pari);}
")"                {return ret(pard);}

"=="               {return ret(oprel);}
"!="               {return ret(oprel);}
"<"                {return ret(oprel);}
"<="               {return ret(oprel);}
">"                {return ret(oprel);}
">="               {return ret(oprel);}

"+"                {return ret(opas);}
"-"                {return ret(opas);}
"*"                {return ret(opmd);}
"/"                {return ret(opmd);}

"//"(.)*           {; /* comentarios de una linea, no hacer nada */}
"="                {return ret(asig);}
"&"                {return ret(referencia);}

"["                {return ret(cori);}
"]"                {return ret(cord);}
"{"                {return ret(llavei);}
"}"                {return ret(llaved);}

"\"%d\""           {return ret(formato);}
"\"%g\""           {return ret(formato);}

"++"               {return ret(incrdecr);}
"--"               {return ret(incrdecr);}

.                  {msgError(ERRLEXICO,nlin,ncol,yytext);}


%%

/*#######################################################################################################*/
/*#######################################################################################################*/
/*#######################################################################################################*/
/* CODIGO */

int yywrap(void) {findefichero=1; return 1;} /* para no tener que linkar con la
                                libreria del lex */


void msgError(int nerror,int nlin,int ncol,const char *s){
    if(nerror == ERRLEXEOF){
        fprintf(stderr, "Error lexico: fin de fichero inesperado\n"); 
    }else if(nerror == ERRLEXICO){
        fprintf(stderr, "Error lexico (%d,%d): caracter '%c' incorrecto\n", nlin, ncol, s[0]);
    }else if(nerror == ERRSINT){
        fprintf(stderr, "Error sintactico (%d,%d): en '%c'\n", nlin, ncol, s[0]);
    }
}

int ret(int token)
{
   yylval.lexema=strdup(yytext);
   yylval.nlin=nlin;
   yylval.ncol=ncol;
   ncol+=(strlen(yytext));
   return(token);
}
