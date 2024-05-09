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

%x COMENTARIO


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

"/*"                    {ncol += strlen(yytext);BEGIN(COMENTARIO);}
<COMENTARIO>[^/*\n]+    {ncol += strlen(yytext);}
<COMENTARIO>\n          {nlin++;ncol=1;}
<COMENTARIO><<EOF>>     {msgError(ERRLEXEOF,-1,-1,"");}
<COMENTARIO>"*/"        {ncol+=strlen(yytext); BEGIN(INITIAL);}
<COMENTARIO>[*/]        {ncol += strlen(yytext);}

"funcion"           {return ret(funcion);}
"var"               {return ret(var);}
"fvar"              {return ret(fvar);}
"entero"            {return ret(entero);}
"real"              {return ret(real);}
"tabla"             {return ret(tabla);}
"de"                {return ret(de);}
"puntero"           {return ret(puntero);}
"blq"               {return ret(blq);}
"fblq"              {return ret(fblq);}
"escribe"           {return ret(escribe);}

{L}({LD})*         {return ret(id);}
{D}+               {return ret(numentero);}
{D}+(\.){D}+       {return ret(numreal);}

"+"                {return ret(opas);}
"-"                {return ret(opas);}

"*"                {return ret(opmul);}
"/"                {return ret(opmul);}
"//"               {return ret(opmul);}
"%"                {return ret(opmul);}

"["                {return ret(cori);}
"]"                {return ret(cord);}

"("                {return ret(pari);}
")"                {return ret(pard);}

".."               {return ret(ptopto);}
":"                {return ret(dosp);}
":="               {return ret(asig);}
";"                {return ret(pyc);}
","                {return ret(coma);}
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
