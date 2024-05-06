%token funcion id 
%token opas opmul
%token numentero numreal pari pard
%token pyc coma

%{

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>


using namespace std;

#include "comun.h"

// variables y funciones del A. Léxico
extern int ncol,nlin,findefichero;


extern int yylex();
extern char *yytext;
extern FILE *yyin;


int yyerror(char *s);


const int ENTERO=1;
const int REAL=2;

string operador, s1, s2;  // string auxiliares

%}

%%
%{
/* ####################################################################################################### */
/* ####################################################################################################### */
/* ####################################################################################################### */
/* GRAMATICA */
%}

X   : S {
    $$.cod = $1.cod;
};

S   : funcion id pyc S B {
    $$.cod = $4.cod + "float" + $2.lexema + "()" + $5.cod;
} | { 
    /* regla epsilon */
    $$.cod = "";
};

D   : var L fvar {
    $$.trad = $2.trad;
};

L   : L V {
    $$.trad = $1.trad + $2.trad; /* REVISAR ORDEN*/
} | V {
    $$.trad = $1.trad;
};


V   : id dosp C pyc {
    /*
    No pueden haber 2 vars con el mismo nombre en mismo ambito
    No puede llamarse como la funcion
    */
    $$.trad = $3.tipo + $1.lexema + $3.array;
};


C   : A C {
    $$.tipo = $2.tipo;
    $$.array = $1.trad + $2.array;
} | P {
    $$.trad = $1.trad;
    $$.array = "";
};

A   : tabla cori R cord de {
    $$.trad = $3.trad;
};

R   : R coma G {
    $$.trad = $2.trad + $1.trad; /* REVISAR ORDEN*/
} | G {
    $$.trad = $1.trad;
};


G   : numentero ptopto numentero {
    /*COPIAR DE P3*/
    $$.trad = "[" +  + "]"; /* COMPROBAR n1 < n2 */
};

P   : puntero de P {
    $$.trad = $3.trad;
} | Tipo {
    $$.trad = $1.trad;
};

Tipo: entero {
    $$.trad = "int";
} | real {
    $$.trad = "float";
};


B   : blq D SI fblq {
    /*habria que sumar un _ en el attr heredado pero no se como se hace eso*/
    $$.trad = "{" + $2.trad + $3.trad + "}";
};


SI  : SI pyc I {
    $$.trad = $1.trad + $3.trad; /* REVISAR ORDEN*/
} | I {
    $$.trad = $1.trad;
};


I   : id asig E {
    /*
    si id.lex es nom fundion -> return
    si int := float -> ERR
    si float := int -> itor(E.trad)
    si tabla o puntero -> ERR
    */
    $$.trad = $1.lexema + "=" + $3.trad;
} | escribe pari E pard {
    /* TIPO_E es un char que depende del tipo*/
    $$.trad = "printf(\"%"+ TIPO_E + $3.trad + ")";
} | B {
    $$.trad = $1.trad;
};


E   : E opas T {
    /* tras el simbolo debe ir "i" si ambos son int, sino "r" */
    $$.trad = $1.trad + operator + $3.trad;
    $$.tipo = ?; /* not that easy */
} | T {
    $$.trad = $1.trad;
};


T   : T opas F {
    /* 
    tras el simbolo debe ir "i" si ambos son int, sino "r", no aplica a %
    - // y % necesitan 2 enteros, sino -> error
    - / siempre da un real, aunque los operandos sean enteros
    */
    $$.trad = $1.trad + operator + $3.trad;
    $$.tipo = ?; /* not that easy */
} | F {
    $$.trad = $1.trad;
};


F   : numentero {
    $$.trad = $1.lexema;
} | numreal {
    $$.trad = $1.lexema;
} | id {
    /*
    si es un id, debe estar en la tabla de ambito, sino -> error
    si es un id, pero es una tabla o puntero -> error
    */
    $$.trad = $1.lexema;
};












%%
%{
/* ####################################################################################################### */
/* ####################################################################################################### */
/* ####################################################################################################### */
/* CODIGO */
%}

























