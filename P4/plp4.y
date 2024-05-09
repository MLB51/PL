%token funcion id var fvar puntero de blq fblq asig
%token opas opmul entero real 
%token numentero numreal pari pard cori cord 
%token pyc coma ptopto dosp escribe tabla

%{

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>


using namespace std;

#include "TablaSimbolos.h"
#include "comun.h"

// variables y funciones del A. Léxico
extern int ncol,nlin,findefichero;


extern int yylex();
extern char *yytext;
extern FILE *yyin;
void errorSemantico(int nerror,int fila,int columna,char *lexema);

int yyerror(char *s);

TablaSimbolos *tsa=new TablaSimbolos(NULL);

string operador, s1, s2;  // string auxiliares

const int ERRYADECL=1,
	ERRNOMFUNC=2,
	ERRNOSIMPLE=3,
	ERRNODECL=4,
	ERRTIPOS=5,
	ERRNOENTEROIZQ=6,
	ERRNOENTERODER=7,
	ERRRANGO=8;

%}

%%

/* ####################################################################################################### */
/* ####################################################################################################### */
/* ####################################################################################################### */
/* GRAMATICA */


X   : S {
    int token = yylex();
    if (token == 0) // si es fin de fichero, yylex() devuelve 0
    {
        printf("%s\n",$1.cod.c_str());
    }
    else
    yyerror("");
};

S   : funcion id pyc S {$5.prefijo="";} B {
    $$.cod = $4.cod + "float " + $2.lexema + "()\n" + $5.cod;
} | { 
    /* regla epsilon */
    $$.cod = "";
};

D   : var {
    $2.prefijo = $$.prefijo;
} L fvar {
    $$.cod = $2.cod;
};

L   : {
    $1.prefijo = $$.prefijo;
    $2.prefijo = $$.prefijo;
} L V {
    $$.cod = $1.cod + $2.cod; /* REVISAR ORDEN*/

} | {$1.prefijo = $$.prefijo;} V {
    $$.cod = $1.cod;
};


V   : id {
    /* falta ver si es nombre funcion */
    if(tsa->buscarAmbito($$.prefijo + $1.lexema)==NULL){
        errorSemantico(ERRYADECL, $1.nlin, $1.ncol, $1.lexema);
    }
} dosp C pyc {
    Simbolo s;
    s.nombre = $1.lexema;
    s.tipo = $3.tipo;
    s.nomtrad = $$.prefijo + $1.lexema; /*falta añadir el _*/
    tsa->nuevoSimbolo(s);
    $$.cod = $3.cod + $1.lexema + $3.array;
};


C   : A C {
    $$.cod = $2.cod;
    $$.tipo = $2.tipo;
    $$.array = $1.cod + $2.array;
} | P {
    $$.tipo = $1.tipo;
    $$.cod = $1.cod;
    $$.array = "";
};

A   : tabla cori R cord de {
    $$.cod = $3.cod;
};

R   : R coma G {
    $$.cod = $2.cod + $1.cod; /* REVISAR ORDEN*/
} | G {
    $$.cod = $1.cod;
};


G   : numentero ptopto numentero {
    int num1 = stoi($1.lexema), num2 = stoi($3.lexema);
    if(num1>=num2){
        errorSemantico(ERRRANGO, $3.nlin, $3.ncol, $3.lexema);
    }
    num2++;
    num2 -= num1;

    $$.cod = "[";
    $$.cod += to_string(num2);
    $$.cod += "]";
};

P   : puntero de P {
    $$.cod = $3.cod + "*";
    $$.tipo = $3.tipo;
} | Tipo {
    $$.cod = $1.cod;
    $$.tipo = $1.tipo;
};

Tipo: entero {
    $$.cod = "int";
    $$.tipo = ENTERO;
} | real {
    $$.cod = "float";
    $$.tipo = REAL;
};


B   : blq {
    tsa = new TablaSimbolos(tsa);
    $2.prefijo = $$.prefijo;
    $3.prefijo = $$.prefijo;
} D SI {
    tsa = tsa->getAmbitoAnterior();
} fblq {
    /*habria que sumar un _ en el attr heredado pero no se como se hace eso*/
    $$.cod = "{\n" + $2.cod + $3.cod + "}\n";
};


SI  : SI pyc I {
    $$.cod = $1.cod + $3.cod; /* REVISAR ORDEN*/
} | I {
    $$.cod = $1.cod;
};


I   : id asig E {
    /*
    si id.lex es nom fundion -> return
    si int := float -> ERR
    si float := int -> itor(E.cod)
    si tabla o puntero -> ERR
    */
    $$.cod = $1.lexema;
    $$.cod += "=";
    $$.cod += $3.cod;
} | escribe pari E pard {
    /* TIPO_E es un char que depende del tipo*/
    string TIPO_E="";
    if($3.tipo==ENTERO){
        TIPO_E = "d";
    }else if($3.tipo == REAL){
        TIPO_E = "f";
    }else{
        errorSemantico(ERRNOSIMPLE, $3.nlin, $3.ncol, $3.lexema);
    }
    $$.cod = "printf(\"%"+ TIPO_E + "\", " + $3.cod + ");\n";
} | {$1.prefijo = "_"+$$.prefijo} B {
    $$.cod = $1.cod;
};


E   : E opas T {
    /* tras el simbolo debe ir "i" si ambos son int, sino "r" */
    string op="";
    $$.cod = $1.cod;
    $$.cod += op;
    $$.cod += $3.cod;


    $$.tipo = 1; /* not that easy */
} | T {
    $$.cod = $1.cod;
};


T   : T opas F {
    /* 
    tras el simbolo debe ir "i" si ambos son int, sino "r", no aplica a %
    - // y % necesitan 2 enteros, sino -> error
    - / siempre da un real, aunque los operandos sean enteros
    */    
    string op="";
    $$.cod = $1.cod;
    $$.cod += op;
    $$.cod += $3.cod;

    $$.tipo = 1; /* not that easy */
} | F {
    $$.cod = $1.cod;
};


F   : numentero {
    $$.cod = $1.lexema;
    $$.tipo = ENTERO;
} | numreal {
    $$.cod = $1.lexema;
    $$.tipo = REAL;
} | id {
    /*
    si es un id, debe estar en la tabla de ambito, sino -> error
    si es un id, pero es una tabla o puntero -> error
    */
    Simbolo* simb = tsa->buscar($1.lexema);
    if(simb == NULL){
        errorSemantico(ERRNODECL, $1.nlin, $1.ncol, $1.lexema);
    }

    if(simb->tipo == ENTERO){
        $$.tipo = ENTERO;
    }else if(simb->tipo == REAL){
        $$.tipo = REAL;
    }else{
        errorSemantico(ERRNOSIMPLE, $1.nlin, $1.ncol, $1.lexema);
    }
    $$.cod = $1.lexema;
};












%%
/* ####################################################################################################### */
/* ####################################################################################################### */
/* ####################################################################################################### */
/* CODIGO */



void errorSemantico(int nerror,int fila,int columna,char *lexema)
{
    fprintf(stderr,"Error semantico (%d,%d): en '%s', ",fila,columna,lexema);
    switch (nerror) {
      case ERRYADECL: fprintf(stderr,"ya existe en este ambito\n");
         break;
      case ERRNOMFUNC: fprintf(stderr,"no puede llamarse igual que la funcion");
         break;
      case ERRNOSIMPLE: fprintf(stderr,"debe ser de tipo entero o real\n");
         break;
      case ERRNODECL: fprintf(stderr,"no ha sido declarado\n");
         break;
      case ERRTIPOS: fprintf(stderr,"tipos incompatibles entero/real\n");
         break;
      case ERRNOENTEROIZQ: fprintf(stderr,"el operando izquierdo debe ser entero\n");
         break;
      case ERRNOENTERODER: fprintf(stderr,"el operando derecho debe ser entero\n");
         break;
      case ERRRANGO: fprintf(stderr,"rango incorrecto\n");
         break;
    }
    exit(-1);
}



int yyerror(char *s)
{
    if (findefichero) 
    {
       msgError(ERREOF,0,0,"");
    }
    else
    {  
       msgError(ERRSINT,nlin,ncol-strlen(yytext),yytext);
    }
    return 0;
}

int main(int argc,char *argv[])
{
    FILE *fent;

    if (argc==2)
    {
        fent = fopen(argv[1],"rt");
        if (fent)
        {
            yyin = fent;
            yyparse();
            fclose(fent);
        }
        else
            fprintf(stderr,"No puedo abrir el fichero\n");
    }
    else
        fprintf(stderr,"Uso: ejemplo <nombre de fichero>\n");
}

















