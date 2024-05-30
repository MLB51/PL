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

int yyerror(char *s);

TablaSimbolos *tsa=new TablaSimbolos(NULL);
TablaTipos *tt=new TablaTipos();

string operador, s1, s2;  // string auxiliares

const int ERRYADECL=10,
	ERRNODECL=11,
	ERRDIM=12,
	ERRFALTAN=13,
	ERRSOBRAN=14,
	ERR_NOENTERO=15,
	ERR_NOCABE=100,
	ERR_MAXTMP=101;
	
void errorSemantico(int nerror,char *lexema,int fila,int columna);

int MAX_VAR_DIR = 16000;
int MAX_TMP_DIR = 16383; 

int newVarDir = 0;
int newTempDir = 16000;



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
    //std::cout << newVarDir << std::endl;
    int tam_tsa = 0;
    for(Simbolo s: tsa->simbolos){
        tam_tsa += tt->getTamanyoRecursivo(s.tipo);
    }
    tsa = tsa->getAmbitoAnterior();
    newVarDir -= tam_tsa; // se vacian las pos de memoria
    //std::cout << newVarDir << std::endl;
    
} llaved  {
    // se crearia nuevo ambito aqui y al quitarlo borrar todas las pos de memoria
    $$.cod = "; {\n"+ $3.cod + $4.cod +"; }\n";
};

BDecl   : BDecl DVar {
    $$.cod = $1.cod + $2.cod;
} | {
    $$.cod = "";
};

DVar    : Tipo {
    $$.tipo = $1.tipo;
} LIdent pyc {
    $$.cod = "; Tipo: " + $1.cod + "\n" + $3.cod;
    // hay que mandar el tipo como tipoh
};

LIdent  : LIdent coma {$$.tipo = $0.tipo;} Variable {
    $$.cod = $1.cod + $4.cod;
} | Variable {
    $$.cod = $1.cod;
};



Variable : id {
    $$.tipo = $0.tipo;
    if(tsa->buscarAmbito($1.lexema)!=NULL){
        errorSemantico(ERRYADECL, $1.lexema, $1.nlin, $1.ncol);
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
    int fullTam = tt->getTamanyoRecursivo($3.tipo);
    if(newVarDir + fullTam >= MAX_VAR_DIR) 
        errorSemantico(ERR_NOCABE, $1.lexema, $1.nlin, $1.ncol);

    Simbolo s;
    s.nombre = $1.lexema;
    s.tipo = $3.tipo;
    s.tam = tt->tipos[$3.tipo].tamanyo; //* este no es tam recursivo
    s.dir = newVarDir;
    newVarDir += fullTam;
    tsa->nuevoSimbolo(s); //! cuidao, parecde que sigue haciendo la duplicacion de dfincions WTF

    //std::cout << "; "<< s.nombre << " d:" << s.dir << " tp:" << s.tipo << " tm:" << s.tam << " " << std::endl;

    $$.cod = "; ";
    $$.cod += $1.lexema + $3.cod + " => \n";
    $$.cod += ";  dir:" + std::to_string(s.dir) + " tp:" + std::to_string(s.tipo) + " tm:" + std::to_string(s.tam) + " \n" ;

};


V   :  {
    $$.tipo = $0.tipo;

} | cori nentero cord {$$.tipo = $0.tipo;} V {
    int tam = std::stoi($2.lexema);
    if(tam<=0) errorSemantico(ERRDIM, $2.lexema, $2.nlin, $2.ncol);

    $$.tipo = tt->nuevoTipoArray(
        tam, // tamaño
        $5.tipo// tipo base
    );

    //std::cout << "- tipo: " << $$.tipo  << "- tam: " << tt->tipos[$$.tipo].tamanyo << " - base: " << tt->tipos[$$.tipo].tipoBase << std::endl;
    $$.cod = "[";
    $$.cod += $2.lexema;
    $$.cod += "]";
    $$.cod += $5.cod;
};


/************************************************************************************************************************************/
/************************************************************************************************************************************/

SeqInstr : SeqInstr Instr {
    $$.cod = $1.cod + $2.cod;
} | {
    $$.cod = "\n";
};


Instr : pyc {
    //! nada?
    $$.cod = ";pyc\n";

} | Bloque {
    $$.cod = $1.cod;

} | Ref asig Expr pyc {
    // id = E ;
    $$.cod = $1.cod + $3.cod;

    string dir3 = std::to_string($3.dir);
    if($3.simb!=""){
        // p. ej: a = b;
        // la ref de $1. no viene full calculada
        // la de b si
        $$.cod += "mov " + dir3 + " A\n";

        Simbolo* s = tsa->buscar($1.simb);
        $$.cod += "mov " + std::to_string($1.dir) + " B \n";
        
        $$.cod += "; Asignacion para "+ $1.simb +"="+ $3.simb +"\n";
        //$$.cod += "wri A \n";
        //$$.cod += "wrl \n";
        //$$.cod += "wri B \n";
        //$$.cod += "wrl \n";
        
        $$.cod += "mov @A @B+"+std::to_string(s->dir)+"\n";
        
        //$$.cod += "wrr @B+"+std::to_string(s->dir)+"\n";
        //$$.cod += "wrl \n";

        if($1.tipo!=$3.tipo){
            $$.cod += "; Arregla tipos\n";
            
            $$.cod += "mov @B+"+std::to_string(s->dir)+" A\n";
            if($1.tipo==ENTERO){
                $$.cod += "rtoi\n";
            }else{
                $$.cod += "itor\n";
            }
            $$.cod += "mov A @B+"+std::to_string(s->dir)+"\n";
        }
        if($1.tipo==ENTERO && $3.tipo ==REAL){
        }else if($1.tipo==REAL && $3.tipo ==ENTERO){
        }

    }else{
            
        Simbolo* s = tsa->buscar($1.simb);
        $$.cod += "; Se calcula la pos total para la Ref de la asignacion\n";
        $$.cod += "mov " + std::to_string($1.dir) + " A \n";
        $$.cod += "addi #"+ std::to_string(s->dir) + " \n"; // suma dirbase a la pos en el array
        //std::cout << ";var " << $1.simb << s->dir << std::endl;

        if($1.tipo==ENTERO && $3.tipo ==REAL){
            $$.cod += "rtoi\n";
        }else if($1.tipo==REAL && $3.tipo ==ENTERO){
            $$.cod += "itor\n";
        }

        $$.cod += "; Asignacion para "+ $1.simb +"\n";
        $$.cod += "mov " + dir3 + " @A \n";

    }
    

    // necesito mover
    // de: posicion memoria $3.dir (almacena el resultado de Expr) 
    // a: posicion guardada en A (dirbase + pos_array)

    //$$.cod += "wri " + std::to_string($1.dir) + "  \n";
    /*$$.cod += "wri A \n";
    $$.cod += "wrl \n";
    if($1.tipo==ENTERO){
        $$.cod += "wri @A \n";
        //$$.cod += "wrr 3 \n";
    }else{
        $$.cod += "wrr @A \n";
    }
    $$.cod += "wrl \n";
    if($3.tipo==ENTERO){
        $$.cod += "wri "+std::to_string($3.dir) +"\n";
    }else{
        $$.cod += "wrr "+std::to_string($3.dir) +"\n";
    }
    $$.cod += "wrl \n";
    $$.cod += "wrl \n";*/

} | escribe pari formato coma Expr pard pyc {
    // hacer conversiones para los formatos, also escribe siempre hace wrl AL FINAL, como si tuvies un \n
    //     - wri fuente Imprime el valor (entero) de fuente.
    //     - wrr fuente Imprime el valor (real) de fuente.
    //     - wrc fuente Imprime el carácter representado por los 8 bits más bajos del valor entero 
    //     - wrl Imprime un salto de LInea

    $$.cod = $5.cod;

    if($5.simb!=""){
        $$.cod += "mov " + std::to_string($5.dir) + " B\n";
        $$.cod += "mov @B+0 " + std::to_string($5.dir) + " \n";
    }

    string f = "i";
    $$.cod += "mov " + std::to_string($5.dir) + " A\n";
    if(std::string($3.lexema).find("d") != std::string::npos){
        if($5.tipo == REAL){
            $$.cod += "rtoi\n";
        }
    }else if(std::string($3.lexema).find("g") != std::string::npos){
        f = "r";
        if($5.tipo == ENTERO){
            $$.cod += "itor\n";
        }
    } 
    // if(std::string($3.lexema).find("c") != std::string::npos){
    //    f = "c";
    //    if($5.tipo == REAL){
    //        $$.cod += "itor\n";
    //    }
    //} 

    $$.cod += "wr";
    $$.cod += f;
    $$.cod += " A\n";
    $$.cod += "wrl\n";

} | lee pari formato coma referencia Ref pard pyc {
    //     - rdi destino Lee un entero de la consola y lo carga en destino.
    //     - rdr destino Lee un real de la consola y lo carga en destino.
    //     - rdc destino Lee un carácter de la consola y carga su código ASCII en destino.
    string f = $6.tipo==ENTERO ? "i" : "r";
    $$.cod = $6.cod;
    $$.cod += "rd";
    $$.cod += f;
    $$.cod += " ";
    $$.cod += std::to_string($6.dir); // direccion que devuelve la expresion
    $$.cod += "\n";

} | si pari Expr pard Instr {
    // if y while cumplen lo de if(134) -> True, if(0) -> false


    $$.cod = $3.cod;
    $$.cod += "; IF\n";
    $$.cod += $5.cod;

} | si pari Expr pard Instr sino Instr {

    $$.cod = $3.cod;
    $$.cod += "; IF\n";
    $$.cod += $5.cod;
    $$.cod += "; ELSE\n";
    $$.cod += $7.cod;

} | mientras pari Expr pard Instr {

    $$.cod = $3.cod;
    $$.cod += "; WHILE\n";
    $$.cod += $5.cod;

} | para pari id asig Esimple pyc Expr pyc id incrdecr pard Instr {
    /*
        Se tiene que comprobar en el for
        1. identificador existe
        2. tiene que ser entero antes de asignar
        3. lo mismo con el 2 id
        id1 y id2 pueden ser distintos pero a nadie le importa
    */
    $$.cod = $5.cod;
    $$.cod = $7.cod;
    $$.cod = "; FOR\n";
    $$.cod += $12.cod;


};


/************************************************************************************************************************************/

/*
    Aqui las expresiones son mas complejas, pueden usar arrays y ()
    pero el principio deberia ser practicamente igual

    Toda combinacion de int y float es posible, hayq ue hacer las conversiones necesarias
    Ops relaciones devuelven siempre 0 o 1

*/
Expr :  Expr oprel Esimple {
    $$.cod = $1.cod + $3.cod; 

    string operacion = "";

    if(strcmp($2.lexema, "==")==0){
        operacion = "eql";
    } else if(strcmp($2.lexema, "!=")==0){
        operacion = "neq";
    } else if(strcmp($2.lexema, "<")==0){
        operacion = "lss";
    } else if(strcmp($2.lexema, "<=")==0){
        operacion = "eql";
    } else if(strcmp($2.lexema, ">")==0){
        operacion = "gtr";
    } else if(strcmp($2.lexema, ">=")==0){
        operacion = "geq";
    } 

 
    $$.cod += "; OPREL\n";
    // si cualquiera de los dos es referencia
    // se sacan los valores de la var y se meten en la tmp
    if($1.simb!=""){
        $$.cod += "mov " + std::to_string($1.dir) + " B\n";
        $$.cod += "mov @B+0 " + std::to_string($1.dir) + " \n";
    }
    if($3.simb!=""){
        $$.cod += "mov " + std::to_string($3.dir) + " B\n";
        $$.cod += "mov @B+0 " + std::to_string($3.dir) + " \n";
    }

    if($1.tipo != $3.tipo){
        if($1.tipo == ENTERO){ // si son distintos cambia solo el entero
            $$.cod += "mov " + std::to_string($1.dir) + " A\n";
            $$.cod += "itor\n";
            $$.cod += operacion + "r " + std::to_string($3.dir) + "\n";
        }else {
            $$.cod += "mov " + std::to_string($3.dir) + " A\n";
            $$.cod += "itor\n";
            $$.cod += operacion + "r " + std::to_string($1.dir) + "\n";
        }
        $$.tipo = REAL;

    }else{ // si son iguales no se requiere cambio de tipo
        if($1.tipo == ENTERO){
            $$.cod += "mov " + std::to_string($1.dir) + " A\n";
            $$.cod += operacion + "i " + std::to_string($3.dir) + "\n";
            $$.tipo = ENTERO;
        }else {
            $$.cod += "mov " + std::to_string($1.dir) + " A\n";
            $$.cod += operacion + "r " + std::to_string($3.dir) + "\n";
            $$.tipo = REAL;
        }
    }

    int tmp = newTempDir++;
    $$.dir = tmp;
    if($$.tipo==REAL){
        $$.tipo = ENTERO;
    }
    $$.cod += "mov A " + std::to_string(tmp) + " \n";
    $$.simb = "";

} | Esimple {
    $$.cod = $1.cod;
    $$.tipo = $1.tipo;
    $$.dir = $1.dir;
    $$.simb = $1.simb;

};


Esimple :  Esimple opas Term  {
    $$.cod = $1.cod + $3.cod; 
    string operacion = (strcmp($2.lexema, "+")==0)? "add": "sub";

    $$.cod += "; OPAS\n";

    // si cualquiera de los dos es referencia
    // se sacan los valores de la var y se meten en la tmp
    if($1.simb!=""){
        $$.cod += "mov " + std::to_string($1.dir) + " B\n";
        $$.cod += "mov @B+0 " + std::to_string($1.dir) + " \n";
        //if($1.tipo==ENTERO)
        //$$.cod += "wri " + std::to_string($1.dir) + "\n";
        //else
        //$$.cod += "wrr " + std::to_string($1.dir) + "\n";
    }
    if($3.simb!=""){
        $$.cod += "mov " + std::to_string($3.dir) + " B\n";
        $$.cod += "mov @B+0 " + std::to_string($3.dir) + " \n";
        //if($3.tipo==ENTERO)
        //$$.cod += "wri " + std::to_string($3.dir) + "\n";
        //else
        //$$.cod += "wrr " + std::to_string($3.dir) + "\n";
    }

    if($1.tipo != $3.tipo){
        if($1.tipo == ENTERO){ // si son distintos cambia solo el entero
            $$.cod += "mov " + std::to_string($1.dir) + " A\n";
            $$.cod += "itor\n";
            $$.cod += operacion + "r " + std::to_string($3.dir) + "\n";
        }else {
            $$.cod += "mov " + std::to_string($3.dir) + " A\n";
            $$.cod += "itor\n";
            $$.cod += operacion + "r " + std::to_string($1.dir) + "\n";
        }
        //$$.cod += "wrr A\n";
        $$.tipo = REAL;

    }else{ // si son iguales no se requiere cambio de tipo
        if($1.tipo == ENTERO){
            $$.cod += "mov " + std::to_string($1.dir) + " A\n";
            $$.cod += operacion + "i " + std::to_string($3.dir) + "\n";
            $$.tipo = ENTERO;
        //$$.cod += "wri A\n";
        }else {
            $$.cod += "mov " + std::to_string($1.dir) + " A\n";
            $$.cod += operacion + "r " + std::to_string($3.dir) + "\n";
            $$.tipo = REAL;
        //$$.cod += "wrr A\n";
        }
    }


    int tmp = newTempDir++;
    $$.dir = tmp,
    $$.cod += "mov A " + std::to_string(tmp) + " \n";
    $$.simb = "";

} | Term {
    $$.cod = $1.cod;
    $$.tipo = $1.tipo;
    $$.dir = $1.dir;
    $$.simb = $1.simb;

};


Term :  Term opmd Factor {
// div entre enteros : > entero, si 1 es real se convierte el otro
    $$.cod = $1.cod + $3.cod; 
    
    string operacion = (strcmp($2.lexema, "*")==0)? "mul": "div";

    $$.cod += "; OPMD\n";

    // si cualquiera de los dos es referencia
    // se sacan los valores de la var y se meten en la tmp
    if($1.simb!=""){
        $$.cod += "mov " + std::to_string($1.dir) + " B\n";
        $$.cod += "mov @B+0 " + std::to_string($1.dir) + " \n";
    }
    if($3.simb!=""){
        $$.cod += "mov " + std::to_string($3.dir) + " B\n";
        $$.cod += "mov @B+0 " + std::to_string($3.dir) + " \n";
    }

    if($1.tipo != $3.tipo){
        if($1.tipo == ENTERO){ // si son distintos cambia solo el entero
            $$.cod += "mov " + std::to_string($1.dir) + " A\n";
            $$.cod += "itor\n";
            $$.cod += operacion + "r " + std::to_string($3.dir) + "\n";
        }else {
            $$.cod += "mov " + std::to_string($3.dir) + " A\n";
            $$.cod += "itor\n";
            $$.cod += operacion + "r " + std::to_string($1.dir) + "\n";
        }
        $$.tipo = REAL;
        //$$.cod += "wrr A\n";

    }else{ // si son iguales no se requiere cambio de tipo
        if($1.tipo == ENTERO){
            $$.cod += "mov " + std::to_string($1.dir) + " A\n";
            $$.cod += operacion + "i " + std::to_string($3.dir) + "\n";
            $$.tipo = ENTERO;
        //$$.cod += "wri A\n";
        }else {
            $$.cod += "mov " + std::to_string($1.dir) + " A\n";
            $$.cod += operacion + "r " + std::to_string($3.dir) + "\n";
            $$.tipo = REAL;
        //$$.cod += "wrr A\n";
        }
    }


    int tmp = newTempDir++;
    $$.dir = tmp,
    $$.cod += "mov A " + std::to_string(tmp) + " \n";
    $$.simb = "";
    

} | Factor {
    $$.cod = $1.cod;
    $$.tipo = $1.tipo;
    $$.dir = $1.dir;
    $$.simb = $1.simb;

};


Factor :  Ref {
    if(!ES_TIPO_BASICO($1.tipo)){
        errorSemantico(ERRFALTAN, $$.lexema, $$.nlin, $$.ncol); //! aqui habria que marcar en id o en ], osea, en -1?
    }
    // aqui se devolveria una dir tmp con la DIR de la pos del array
    // sumar a simb.dir y ya estaria?
    Simbolo* s = tsa->buscar($1.simb);
    $$.cod = $1.cod;
    $$.cod += "; Se calcula la pos total para la Ref\n";
    $$.cod += "mov " + std::to_string($1.dir) + " A \n";
    $$.cod += "addi #"+ std::to_string(s->dir) + " \n"; // suma dirbase a la pos en el array
    $$.cod += "mov A " + std::to_string($1.dir) + " \n";
    $$.dir = $1.dir;
    $$.tipo = $1.tipo;
    $$.simb = $1.simb;

} | nentero {
    int tmp = newTempDir++;
    $$.dir = tmp;
    $$.tipo = ENTERO;
    $$.cod = "mov #";
    $$.cod += $1.lexema;
    $$.cod += " ";
    $$.cod += std::to_string(tmp);
    $$.cod += "\n";
    $$.simb = "";

} | nreal {
    int tmp = newTempDir++;
    $$.dir = tmp;
    $$.tipo = REAL;
    $$.cod = "mov $";
    $$.cod += $1.lexema;
    $$.cod += " ";
    $$.cod += std::to_string(tmp);
    $$.cod += "\n";
    $$.simb = "";

} | pari Expr pard {
    $$.cod = $2.cod;
    $$.tipo = $2.tipo;
    $$.dir = $2.dir;
    $$.simb = "";
    //* algo mas?
};


Ref :  id {
    Simbolo* s = tsa->buscar($1.lexema);
    if(s == NULL){
        errorSemantico(ERRNODECL, $1.lexema, $1.nlin, $1.ncol);
    }
    int tmp = newTempDir++;
    $$.dir = tmp;

    $$.cod = "mov #0 " + std::to_string(tmp); // t0 = 0
    $$.cod += "; t0 para: ";
    $$.cod += $1.lexema;
    $$.cod += "\n";
    $$.tipo = s->tipo;
    $$.simb = $1.lexema;

} | Ref cori {
    if(ES_TIPO_BASICO($1.tipo)){
        errorSemantico(ERRSOBRAN, $2.lexema, $2.nlin, $2.ncol);
    }

    $$.simb = $1.simb;

}  Esimple cord {
    /*
        mismos ERRORES en arrray que en clase si sobran o fatan []
        el indice debe ser siempre un int, sino ERROR en ]
    */
    if($4.tipo != ENTERO){
        errorSemantico(ERR_NOENTERO, $5.lexema, $5.nlin, $5.ncol);
    }

    int tmp = newTempDir++;
    $$.dir = tmp;
    // ti = ti-1 * tam + pos
    $$.cod = $1.cod;
    $$.cod += "; Calcula n para array\n";
    $$.cod += $4.cod; // Esimple devuelve el num necesario para seguir calculando
    $$.cod += "; Calcula Ti\n";
    $$.cod += "mov " + std::to_string($1.dir)+ " A\n"; // mete el ti-1 en A
    $$.cod += "muli #" + std::to_string(tt->tipos[$1.tipo].tamanyo) + "\n"; // ti-1 * tam
    $$.cod += "addi " + std::to_string($4.dir) + "\n"; // + pos // guardada en una dir tmp
    //$$.cod += "";
    $$.cod += "mov A " + std::to_string(tmp) + "\n"; // guarda ti en una nueva tmp


    $$.tipo = tt->tipos[$1.tipo].tipoBase; // coge el nuevo tipo
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
             case ERRYADECL: fprintf(stderr,"simbolo ya declarado\n");
               break;
             case ERRNODECL: fprintf(stderr,"identificador no declarado\n");
               break;
             case ERRDIM: fprintf(stderr,"la dimension debe ser mayor que cero\n");
               break;
             case ERRFALTAN: fprintf(stderr,"faltan indices\n");
               break;
             case ERRSOBRAN: fprintf(stderr,"sobran indices\n");
               break;
             case ERR_NOENTERO: fprintf(stderr,"debe ser de tipo entero\n");
               break;

             case ERR_NOCABE:fprintf(stderr,"la variable ya no cabe en memoria\n");
               break;
             case ERR_MAXTMP:fprintf(stderr,"no hay espacio para variables temporales\n");
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

















