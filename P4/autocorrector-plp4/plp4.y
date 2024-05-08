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
void errorSemantico(int nerror,char *lexema,int fila,int columna);

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

S   : funcion id pyc S B {
    $$.cod = $4.cod + "float " + $2.lexema + "()\n" + $5.cod;
} | { 
    /* regla epsilon */
    $$.cod = "";
};

D   : var L fvar {
    $$.cod = $2.cod;
};

L   : L V {
    $$.cod = $1.cod + $2.cod; /* REVISAR ORDEN*/
} | V {
    $$.cod = $1.cod;
};


V   : id dosp C pyc {
    /*
    No pueden haber 2 vars con el mismo nombre en mismo ambito
    No puede llamarse como la funcion
    */
    $$.cod = $3.tipo + $1.lexema + $3.array;
};


C   : A C {
    $$.tipo = $2.tipo;
    $$.array = $1.cod + $2.array;
} | P {
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
    /*COPIAR DE P3*/
    int n = 1;
    $$.cod = "";
    $$.cod += "[";
    $$.cod += to_string(n);/* COMPROBAR n1 < n2 */
    $$.cod += "]";

};

P   : puntero de P {
    $$.cod = $3.cod;
} | Tipo {
    $$.cod = $1.cod;
};

Tipo: entero {
    $$.cod = "int";
    $$.tipo = ENTERO;
} | real {
    $$.cod = "float";
    $$.tipo = REAL;
};


B   : blq {tsa = new TablaSimbolos(tsa);} D SI {tsa = tsa->getAmbitoAnterior();} fblq {
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
        errorSemantico(ERRNOSIMPLE, $3.lexema, $3.nlin, $3.ncol);
    }
    $$.cod = "printf(\"%"+ TIPO_E + "\", " + $3.cod + ");\n";
} | B {
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
} | numreal {
    $$.cod = $1.lexema;
} | id {
    /*
    si es un id, debe estar en la tabla de ambito, sino -> error
    si es un id, pero es una tabla o puntero -> error
    */
    $$.cod = $1.lexema;
};












%%
/* ####################################################################################################### */
/* ####################################################################################################### */
/* ####################################################################################################### */
/* CODIGO */



void errorSemantico(int nerror,char *lexema,int fila,int columna)
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

















