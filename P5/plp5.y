%token main_f entero real 
%token escribe lee si sino mientras para 
%token id nentero nreal coma pyc 
%token pari pard oprel opas opmd asig 
%token referencia cori cord llavei llaved 
%token formato incrdecr




%{

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>


using namespace std;

#include "TablaSimbolos.h"
#include "TablaTipos.h"
#include "comun.h"

// variables y funciones del A. Léxico
extern int ncol,nlin,findefichero;


extern int yylex();
extern char *yytext;
extern FILE *yyin;
void errorSemantico(int nerror,int fila,int columna,char *lexema);

int yyerror(char *s);

TablaSimbolos *tsa=new TablaSimbolos(NULL);
TablaTipos *tt=new TablaTipos();

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


S   : FVM {
    $$.cod = "; START\n" + $1.cod + "halt";
};

FVM : DVar FVM {
    $$.cod = "; VARS\n" + $1.cod + $2.cod;

} | entero main_f pari pard Bloque {
    $$.cod = "; MAIN\n" + $5.cod;
};

Tipo    : entero {
    $$.cod = "int";
    $$.tipo = ENTERO;
} | real {
    $$.cod = "float";
    $$.tipo = REAL;
};

Bloque  : llavei {
    tsa = new TablaSimbolos(tsa);
} BDecl SeqInstr {
    tsa = tsa->getAmbitoAnterior();
} llaved  {
    // se crearia nuevo ambito aqui y al quitarlo borrar todas las pos de memoria
    $$.cod = "; {\n"+ $2.cod + $3.cod +"; }\n";
};

BDecl   : BDecl DVar {
    $$.cod = $1.cod + $2.cod;
} | {
    $$.cod = "";
};

DVar    : Tipo LIdent pyc {
    $$.cod = "; Tipo: " + $1.cod + "\n" + $2.cod;
    // hay que mandar el tipo como tipoh
};

LIdent  : LIdent coma Variable {
    $$.cod = $1.cod + $3.cod;
} | Variable {
    $$.cod = $1.cod;
};


Variable : id {
    if($1.lexema == $$.nombre_funcion){
        errorSemantico(ERRNOMFUNC, $1.nlin, $1.ncol, $1.lexema);
    }
    if(tsa->buscarAmbito($1.lexema)!=NULL){
        errorSemantico(ERRYADECL, $1.nlin, $1.ncol, $1.lexema);
    }
} V {
    /*Aqui se heredaria el tipo y se guardaria cada una de los SIMBS 
    Also se guardarian los tipos int y float si no estuviesen
    Hay 16k pos para vars, int y float ocupan 1, los arrays depende del tamaño
    Si supera 15999 - ERROR
    16k a 16383 - vars temporales, aqui tambien ERROR si se pasa

    1. V vacio?
    2.1 SI - se guarda con tipo heredado
    2.2 NO - se guarda con el tipo definido que se devlveria desde V
    En cualquier caso seria V.tipo
    */

    Simbolo s;
    s.nombre = $1.lexema;
    s.tipo = $3.tipo;
    s.tam = tt.tipos[$3.tipo].tamanyo;
    s.dir = NuevaVar();
    /*if($4.array != ""){
        s.tipo = TABLA;
    }else if($4.cod.find('*') != std::string::npos){
        s.tipo = PUNTERO;
    }else {
        s.tipo = $4.tipo;
    }*/

    tsa->nuevoSimbolo(s);


    $$.cod = "; ";
    $$.cod += $1.lexema + $3.cod;
    $$.cod += "\n";

};


V   :  {
    //$$.tipo = $0.tipoh; // empezamos a jgar con fuego, esto seria asi?

} | cori nentero cord V {
    /*aqui se guardaria cada uno de los tipos array
    el num tiene que ser siempre mayor que 0*/
    $$.cod = "[";
    $$.cod += $2.lexema;
    $$.cod += "]";
    $$.cod += $4.cod;
    $$.tipo = 23; // aqui iria el tipo del array en cuestion
};

/************************************************************************************************************************************/

SeqInstr : SeqInstr Instr {} | {};
Instr : pyc {};
Instr : Bloque {
    $$.cod = S1.cod;
};
Instr : Ref asig Expr pyc {};
// hacer conversiones para los formatos, also escribe siempre hace wrl AL FINAL, como si tuvies un \n
Instr : escribe pari formato coma Expr pard pyc {};
Instr : lee pari formato coma referencia Ref pard pyc {};
// if y while cumplen lo de if(134) -> True, if(0) -> false
Instr : si pari Expr pard Instr {};
Instr : si pari Expr pard Instr sino Instr {};
Instr : mientras pari Expr pard Instr {};
/*
    Se tiene que comprobar en el for
    1. identificador existe
    2. tiene que ser entero antes de asignar
    3. lo mismo con el 2 id
    id1 y id2 pueden ser distintos pero a nadie le importa
*/
Instr : para pari id asig Esimple pyc Expr pyc id incrdecr pard Instr {};



/************************************************************************************************************************************/

/*
    Aqui las expresiones son mas complejas, pueden usar arrays y ()
    pero el principio deberia ser practicamente igual

    Toda combinacion de int y float es posible, hayq ue hacer las conversiones necesarias
    Ops relaciones devuelven siempre 0 o 1

*/
Expr :  Expr oprel Esimple {};
Expr :  Esimple {};
Esimple :  Esimple opas Term  {};// no se pueden usar arrays en ningun lado, solo si son con corchetes
Esimple :  Term {};
Term :  Term opmd Factor {}; // div entre enteros : > entero, si 1 es real se convierte el otro 
Term :  Factor {};
Factor :  Ref {};
Factor :  nentero {};
Factor :  nreal {};
Factor :  pari Expr pard {};
Ref :  id {};
Ref :  Ref cori Esimple cord {}; 
/*
    mismos ERRORES en arrray que en clase si sobran o fatan []
    el indice debe ser siempre un int, sino ERROR en ]
*/






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

















