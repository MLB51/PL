import java.util.TreeSet;

public class TraductorDR {
    private final int ERRYADECL=1,ERRNOMFUNC=2,ERRNOSIMPLE=3,ERRNODECL=4,ERRTIPOS=5,ERRNOENTEROIZQ=6,ERRNOENTERODER=7,ERRRANGO=8;
    private AnalizadorLexico al;
    private TablaSimbolos tsActual;
    private Token tokenActual;
    private int tipoToken;
    boolean printeaReglas = true;
    StringBuilder reglas = new StringBuilder();
    int profundidad_S;

    public TraductorDR(AnalizadorLexico al){
        this.al = al;
        this.tokenActual = al.siguienteToken();
        this.tipoToken = this.tokenActual.getTipo();
        this.profundidad_S = 0;
        this.tsActual = new TablaSimbolos(null);
                // crea el hijo como -> tsActual = new TablaSimbolos(tsActual);
        // vuelve al padre -> tsActual = tsActual.getAmbitoAnterior();

    }


    private void errorSintaxis(int... tipos){
        //! printear error y hacer exit(-1)
        TreeSet<Integer> set = new TreeSet<Integer>();
        for(int tipo: tipos){
            set.add(tipo);
        }
        StringBuilder aux_tipos = new StringBuilder();
        for(int tipo: set){
            aux_tipos.append(Token.nombreToken.get(tipo));
            aux_tipos.append(' ');
        }

        if(tipoToken == Token.EOF){
            System.err.printf(
                "Error sintactico: encontrado fin de fichero, esperaba %s%n",
                aux_tipos.toString()
            );
        }else{
            //System.out.println(tokenActual==null);
            //System.out.println(tokenActual.getLexema());
            //System.out.println(tipos==null);
            
            System.err.printf(
                "Error sintactico (%d,%d): encontrado '%s', esperaba %s%n",
                tokenActual.getPos()[0],
                tokenActual.getPos()[1],
                tokenActual.getLexema(),
                aux_tipos.toString()
            );
            
        }
        //! TEMPORAL; BORRAR
        //System.out.println(reglas.toString());
        System.exit(-1);
    }
    private void errorSemantico(int nerror,Token tok){
        System.err.print("Error semantico ("+tok.fila+","+tok.columna+"): en '"+tok.lexema+"', ");
        switch (nerror) {
            case ERRYADECL: System.err.println("ya existe en este ambito");
                break;
            case ERRNOMFUNC: System.err.println("no puede llamarse igual que la funcion");
                break;
            case ERRNOSIMPLE: System.err.println("debe ser de tipo entero o real");
                break;
            case ERRNODECL: System.err.println("no ha sido declarado");
                break;
            case ERRTIPOS: System.err.println("tipos incompatibles entero/real");
                break;
            case ERRNOENTEROIZQ: System.err.println("el operando izquierdo debe ser entero");
                break;
            case ERRNOENTERODER: System.err.println("el operando derecho debe ser entero");
                break;
            case ERRRANGO: System.err.println("rango incorrecto");
                break;
        }
        System.exit(-1);
    }

    public void comprobarFinFichero(){
        //if(printeaReglas){
        //    System.out.println(reglas.toString());
        //}
        return;
    }

    private void emparejar(int tipo){
        if(tipoToken == tipo){
            this.tokenActual = al.siguienteToken();
            this.tipoToken = this.tokenActual.getTipo();
        }else{
            errorSintaxis(tipo);
        }
    }

    //#################################################################################################################################
    //#################################################################################################################################
    //#################################################################################################################################
    public String S(){
        // simbolo inciial es publico, el resto no
        if(tipoToken == Token.FUNCION){
            reglas.append(1);
            reglas.append(' ');
            emparejar(Token.FUNCION);
            
            String id_lex = tokenActual.getLexema();
            emparejar(Token.ID);
            emparejar(Token.PYC);
            
            this.profundidad_S++;
            String s1_trad = S();
            this.profundidad_S--;
            
            Atributos atrs_transmitidos = new Atributos();
            atrs_transmitidos.setAttr("nombre_funcion", id_lex);
            atrs_transmitidos.setAttr("prefijo", "");
            String b_trad = B(atrs_transmitidos);

            if(this.profundidad_S==0){
                if(tipoToken == Token.EOF){
                    this.tipoToken = this.tokenActual.getTipo();
                }else{
                    errorSintaxis(Token.EOF);
                }
            }
            return s1_trad + " \nfloat " + id_lex + "() " + b_trad;
            
        }else if(tipoToken == Token.EOF || tipoToken == Token.BLQ){
            // regla  epsilon == pasar de largo, no?
            reglas.append(2);
            reglas.append(' ');
            return "";
        }else{
            errorSintaxis(Token.FUNCION, Token.EOF, Token.BLQ);
            return "";
        }
    } 

    private String D(Atributos atrs_heredados){
        if(tipoToken == Token.VAR){
            reglas.append(3);
            reglas.append(' ');
            emparejar(Token.VAR);
            String l_trad = L(atrs_heredados);
            emparejar(Token.FVAR);
            return l_trad;
        }else{
            errorSintaxis(Token.VAR);
            return "";
        }
    }

    private String L(Atributos atrs_heredados){
        if(tipoToken == Token.ID){
            reglas.append(4);
            reglas.append(' ');
            String v_trad = V(atrs_heredados);
            String lp_trad = Lp(atrs_heredados);
            return v_trad + ";\n" + lp_trad;
        }else{
            errorSintaxis(Token.ID);
            return "";
        }
    }

    private String Lp(Atributos atrs_heredados){
        if(tipoToken == Token.ID){
            reglas.append(5);
            reglas.append(' ');
            String v_trad = V(atrs_heredados);
            String lp_trad = Lp(atrs_heredados);
            return v_trad + ";\n" + lp_trad;
        }else if(tipoToken == Token.FVAR){
            // regla eps
            reglas.append(6);
            reglas.append(' ');
            return "";
        }else{
            errorSintaxis(Token.ID, Token.FVAR);
            return "";
        }
    }

    private String V(Atributos atrs_heredados){
        if(tipoToken == Token.ID){
            reglas.append(7);
            reglas.append(' ');
            Token auxToken = tokenActual;
            String id_lex = tokenActual.getLexema();
            emparejar(Token.ID);
            // una vez se comprueba que es un id, se comprueba si este ya existe en el ambito
            Simbolo simb = tsActual.buscarAmbito(id_lex);
            if(simb != null){
                errorSemantico(ERRYADECL, auxToken);
            }
            if(id_lex == atrs_heredados.getAttr("nombre_funcion")){
                errorSemantico(ERRNOMFUNC, auxToken);
            }

            emparejar(Token.DOSP);
            Atributos c_atrs = C();
            emparejar(Token.PYC);
            
            int aux_tipo=0;
            if(c_atrs.getAttr("tipo").indexOf('*') != -1){
                aux_tipo = Simbolo.PUNTERO;
            }else if(c_atrs.getAttr("array")!=""){
                aux_tipo = Simbolo.TABLA;
            }else if(c_atrs.getAttr("tipo").indexOf("int") != -1){
                aux_tipo = Simbolo.ENTERO;
            }else if(c_atrs.getAttr("tipo").indexOf("float") != -1){
                aux_tipo = Simbolo.REAL;
            }else{
                System.err.printf("ERROR cuando buscaba el tipo de la nueva var: %s", c_atrs.getAttr("tipo"));
            }

            simb = new Simbolo(
                id_lex, 
                aux_tipo, 
                atrs_heredados.getAttr("prefijo")+id_lex
            );
            tsActual.nuevoSimbolo(simb);

            return c_atrs.getAttr("tipo") + " " + simb.nomtrad + c_atrs.getAttr("array");
        }else{
            errorSintaxis(Token.ID);
            return "";
        }
    }

    private Atributos C(){
        Atributos atrs = new Atributos();
        if(tipoToken == Token.TABLA){
            reglas.append(8);
            reglas.append(' ');
            String a_trad = A();
            Atributos c1_atrs = C();

            atrs.setAttr("tipo", c1_atrs.getAttr("tipo"));
            atrs.setAttr("array", a_trad+c1_atrs.getAttr("array"));
        }else if(tipoToken == Token.ENTERO || tipoToken==Token.REAL || tipoToken==Token.PUNTERO){
            reglas.append(9);
            reglas.append(' ');
            atrs.setAttr("tipo", P());
            atrs.setAttr("array", "");
        }else{
            errorSintaxis(Token.TABLA, Token.ENTERO, Token.REAL);
        }
        return atrs;
    }

    private String A(){
        if(tipoToken == Token.TABLA){
            reglas.append(10);
            reglas.append(' ');
            emparejar(Token.TABLA);
            emparejar(Token.CORI);
            String r_trad = R();
            emparejar(Token.CORD);
            emparejar(Token.DE);
            return r_trad;
        }else{
            errorSintaxis(Token.TABLA);
            return "";
        }
    }

    private String R(){
        if(tipoToken == Token.NUMENTERO){
            reglas.append(11);
            reglas.append(' ');
            String g_trad = G();
            String rp_trad = Rp();
            return g_trad + " " + rp_trad;
        }else{
            errorSintaxis(Token.NUMENTERO);
            return "";
        }
    }

    private String Rp(){
        if(tipoToken == Token.COMA){
            reglas.append(12);
            reglas.append(' ');
            emparejar(Token.COMA);
            String g_trad = G();
            String rp_trad = Rp();
            return g_trad + " " + rp_trad;
        }else if(tipoToken == Token.CORD){
            // regla eps
            reglas.append(13);
            reglas.append(' ');
            return "";
        }else{
            errorSintaxis(Token.COMA, Token.CORD);
            return "";
        }
    }

    private String G(){
        if(tipoToken == Token.NUMENTERO){
            reglas.append(14);
            reglas.append(' ');
            String aux_lex = tokenActual.getLexema();
            emparejar(Token.NUMENTERO);
            Integer num1 = Integer.parseInt(aux_lex);
            emparejar(Token.PTOPTO);
            aux_lex = tokenActual.getLexema();
            Token auxToken = tokenActual;
            emparejar(Token.NUMENTERO);
            Integer num2 = Integer.parseInt(aux_lex);
            if(num1>=num2){
                errorSemantico(ERRRANGO, auxToken);
            }
            num2++;
            num2 -= num1;
            return "["+ num2.toString() +"]";
        }else{
            errorSintaxis(Token.NUMENTERO);
            return "";
        }
    }

    private String P(){
        if(tipoToken == Token.PUNTERO){
            reglas.append(15);
            reglas.append(' ');
            emparejar(Token.PUNTERO);
            emparejar(Token.DE);
            
            return P() + "*";
        }else if(tipoToken == Token.ENTERO || tipoToken == Token.REAL){
            reglas.append(16);
            reglas.append(' ');
            return TIPO();
        }else{
            errorSintaxis(Token.PUNTERO, Token.ENTERO, Token.REAL);
            return "";
        }
    }

    private String TIPO(){
        if(tipoToken == Token.ENTERO){
            reglas.append(17);
            reglas.append(' ');
            emparejar(Token.ENTERO);
            return "int";
        }else if(tipoToken == Token.REAL){
            reglas.append(18);
            reglas.append(' ');
            emparejar(Token.REAL);
            return "float";
        }else{
            errorSintaxis(Token.ENTERO, Token.REAL);
            return "";
        }
    }

    //#################################################################################################################################
    //#################################################################################################################################
    //#################################################################################################################################

    private String B(Atributos atrs_heredados){
        if(tipoToken == Token.BLQ){
            Atributos atrs_transmitidos = new Atributos();
            atrs_transmitidos.setAttr("prefijo", atrs_heredados.getAttr("prefijo"));
            atrs_transmitidos.setAttr("nombre_funcion", atrs_heredados.getAttr("nombre_funcion"));
            reglas.append(19);
            reglas.append(' ');
            emparejar(Token.BLQ);
            // apila nuevo ambito antes de entrar a D (definicion de variables - var L fvar)
            tsActual = new TablaSimbolos(tsActual);
            String d_trad = D(atrs_transmitidos);
            String si_trad = SI(atrs_transmitidos);
            // desapila tabla al volver de SI (bloque de codigo y otros sub ambitos)
            tsActual = tsActual.getAmbitoAnterior();
            emparejar(Token.FBLQ);
            return "{\n"+d_trad+" "+si_trad+"}";
        }else{
            errorSintaxis(Token.BLQ);
            return "";
        }
    }

    private String SI(Atributos atrs_heredados){
        if(tipoToken == Token.ID || tipoToken == Token.ESCRIBE || tipoToken == Token.BLQ){
            reglas.append(20);
            reglas.append(' ');
            String i_trad = I(atrs_heredados);
            String m_trad = M(atrs_heredados);
            return i_trad + " " + m_trad;
        }else{
            errorSintaxis(Token.ID, Token.ESCRIBE, Token.BLQ);
            return "";
        }
    }

    private String M(Atributos atrs_heredados){
        if(tipoToken == Token.PYC){
            reglas.append(21);
            reglas.append(' ');
            emparejar(Token.PYC);
            String i_trad = I(atrs_heredados);
            String m_trad = M(atrs_heredados);
            return i_trad + " " + m_trad;
        }else if(tipoToken == Token.FBLQ){
            // regla eps
            reglas.append(22);
            reglas.append(' ');
            return "";
        }else{
            errorSintaxis(Token.PYC, Token.FBLQ);
            return "";
        }
    }

    private String I(Atributos atrs_heredados){
        String n_funcion = atrs_heredados.getAttr("nombre_funcion");

        if(tipoToken == Token.ID){
            reglas.append(23);
            reglas.append(' ');
            String id_lex = tokenActual.getLexema();
            Token auxToken = tokenActual;
            emparejar(Token.ID);
            Token auxToken2 = tokenActual;
            emparejar(Token.ASIG);
            Atributos e_atrs = E(atrs_heredados);
            String e_trad=e_atrs.getAttr("trad"), e_tipo=e_atrs.getAttr("tipo");

            String prefijo = "";
            if(id_lex.equals(n_funcion)){
                prefijo = "return ";
                if(e_tipo == "int"){
                    e_trad = "itor("+e_trad+")";
                }

            }else{


                Simbolo simb = tsActual.buscar(id_lex); 
                //! OJO, buscar o buscarAmbito?
                //! yo creo que buscar tiene mas sentido 
                if(simb == null){
                    errorSemantico(ERRNODECL, auxToken);
                }else if(simb.tipo == Simbolo.ENTERO){
                    if(e_tipo == "float"){
                        errorSemantico(ERRTIPOS, auxToken2);
                    }
                }else if(simb.tipo == Simbolo.REAL){
                    if(e_tipo == "int"){
                        e_trad = "itor("+e_trad+")";
                    }
                }else{
                    errorSemantico(ERRNOSIMPLE, auxToken);
                }
                prefijo = simb.nomtrad+" = ";
            }

            return prefijo + e_trad + ";\n";
        }else if(tipoToken == Token.ESCRIBE){
            reglas.append(24);
            reglas.append(' ');
            emparejar(Token.ESCRIBE);
            emparejar(Token.PARI);
            Atributos e_atrs = E(atrs_heredados);
            emparejar(Token.PARD);
            String format_type = (e_atrs.getAttr("tipo")=="float") ? "f" : "d";
            return "printf(\"%" + format_type + "\", " + e_atrs.getAttr("trad") +");\n";
        }else if(tipoToken == Token.BLQ){
            reglas.append(25);
            reglas.append(' ');
            Atributos atrs_transmitidos = new Atributos();
            atrs_transmitidos.setAttr("nombre_funcion", n_funcion);
            atrs_transmitidos.setAttr("prefijo", atrs_heredados.getAttr("prefijo")+"_");
            String trad = B(atrs_transmitidos);
            return trad+"\n";
        }else{
            errorSintaxis(Token.ID, Token.ESCRIBE, Token.BLQ);
            return "";
        }
    }
    
    //#################################################################################################################################
    //#################################################################################################################################
    //#################################################################################################################################

    
    private Atributos E(Atributos atrs_heredados){
        Atributos atrs = new Atributos();
        if(tipoToken == Token.NUMENTERO || tipoToken == Token.NUMREAL || tipoToken == Token.ID){
            reglas.append(26);
            reglas.append(' ');
            Atributos t_atrs  = T(atrs_heredados);
            Atributos ep_atrs = Ep(atrs_heredados);
            
            if(ep_atrs.getAttr("trad")==""){
                // si Tp -> epsilon
                // devuelve el tipo de f y "op f.trad"
                atrs.setAttr("tipo", t_atrs.getAttr("tipo"));
                atrs.setAttr("trad", t_atrs.getAttr("trad"));
            }else{
                // si Tp devuelve trad hay que procesar los tipos comparando F y Tp
                String tipo1=t_atrs.getAttr("tipo"), tipo2=ep_atrs.getAttr("tipo");
                String trad1=t_atrs.getAttr("trad"), trad2=ep_atrs.getAttr("trad");
                String previous_op = trad2.substring(0, 2).replaceAll("\\s", "");
                trad2 = trad2.substring(2); // se le quita el operador a la trad
                
                if(tipo1==tipo2 && tipo1=="int"){
                    atrs.setAttr("tipo", "int");
                    atrs.setAttr(
                        "trad", 
                        trad1 + " " + previous_op + "i " + trad2
                    );
                }else if(tipo1==tipo2 && tipo1=="float"){
                    atrs.setAttr("tipo", "float");
                    atrs.setAttr(
                        "trad", 
                        trad1 + " " + previous_op + "r " + trad2
                    );
                }else if(tipo1=="float"){
                    atrs.setAttr("tipo", "float");
                    atrs.setAttr(
                        "trad", 
                        trad1 + " " + previous_op + "r itor(" + trad2 + ")"
                    );
                }else if(tipo2=="float"){
                    atrs.setAttr("tipo", "float");
                    atrs.setAttr(
                        "trad", 
                        "itor(" + trad1 + ") " + previous_op + "r " + trad2
                    );
                }
            }
        }else{
            errorSintaxis(Token.ID, Token.NUMENTERO, Token.NUMREAL);
        }
        return atrs;
    }
    
    private Atributos Ep(Atributos atrs_heredados){
        Atributos atrs = new Atributos();
        if(tipoToken == Token.OPAS){
            reglas.append(27);
            reglas.append(' ');
            String operation = tokenActual.getLexema();
            emparejar(Token.OPAS);

            Atributos t_atrs  = T(atrs_heredados);
            Atributos ep_atrs = Ep(atrs_heredados);
            
            if(ep_atrs.getAttr("trad")==""){
                // si Tp -> epsilon
                // devuelve el tipo de f y "op f.trad"
                atrs.setAttr("tipo", t_atrs.getAttr("tipo"));
                atrs.setAttr("trad", operation + " " + t_atrs.getAttr("trad"));
            }else{
                // si Tp devuelve trad hay que procesar los tipos comparando F y Tp
                String tipo1=t_atrs.getAttr("tipo"), tipo2=ep_atrs.getAttr("tipo");
                String trad1=t_atrs.getAttr("trad"), trad2=ep_atrs.getAttr("trad");
                String previous_op = trad2.substring(0, 2).replaceAll("\\s", "");
                trad2 = trad2.substring(2); // se le quita el operador a la trad
        
                if(tipo1==tipo2 && tipo1=="int"){
                    atrs.setAttr("tipo", "int");
                    atrs.setAttr(
                        "trad", 
                        operation + " " + trad1 + " " + previous_op + "i " + trad2
                    );
                }else if(tipo1==tipo2 && tipo1=="float"){
                    atrs.setAttr("tipo", "float");
                    atrs.setAttr(
                        "trad", 
                        operation + " " + trad1 + " " + previous_op + "r " + trad2
                    );
                }else if(tipo1=="float"){
                    atrs.setAttr("tipo", "float");
                    atrs.setAttr(
                        "trad", 
                        operation + " " + trad1 + " " + previous_op + "r itor(" + trad2 + ")"
                    );
                }else if(tipo2=="float"){
                    atrs.setAttr("tipo", "float");
                    atrs.setAttr(
                        "trad", 
                        operation + " itor(" + trad1 + ") " + previous_op + "r " + trad2
                    );
                }
            }


        }else if(tipoToken == Token.PYC || tipoToken == Token.FBLQ || tipoToken == Token.PARD){
            // regla eps
            reglas.append(28);
            reglas.append(' ');
            atrs.setAttr("tipo", "");
            atrs.setAttr("trad", "");
        }else{
            errorSintaxis(Token.OPAS, Token.PYC, Token.FBLQ, Token.PARD);
        }
        return atrs;
    }

    private Atributos T(Atributos atrs_heredados){
        Atributos atrs = new Atributos();
        if(tipoToken == Token.NUMENTERO || tipoToken == Token.NUMREAL || tipoToken == Token.ID){
            reglas.append(29);
            reglas.append(' ');

            Atributos f_atrs  = F(atrs_heredados);
            Atributos tp_atrs = Tp(atrs_heredados);

            if(tp_atrs.getAttr("trad")==""){
                // si Tp -> epsilon
                // devuelve el tipo de f y "op f.trad"
                atrs.setAttr("tipo", f_atrs.getAttr("tipo"));
                atrs.setAttr("trad", f_atrs.getAttr("trad"));
            }else{
                // si Tp devuelve trad hay que procesar los tipos comparando F y Tp
                String tipo1=f_atrs.getAttr("tipo"), tipo2=tp_atrs.getAttr("tipo");
                String trad1=f_atrs.getAttr("trad"), trad2=tp_atrs.getAttr("trad");
                String previous_op = trad2.substring(0, 2).replaceAll("\\s", "");
                trad2 = trad2.substring(2); // se le quita el operador a la trad

                if(previous_op=="%"){
                    if(tipo1==tipo2 && tipo1=="int"){
                        atrs.setAttr("tipo", "int");
                        atrs.setAttr(
                            "trad", 
                            trad1 + " " + previous_op + " " + trad2
                        );
                    }else if(tipo1=="float"){
                        errorSemantico(ERRNOENTEROIZQ, tokenActual); //! DUDA, donde salta el err aqui??
                    }else if(tipo2=="float"){
                        errorSemantico(ERRNOENTERODER, tokenActual);
                    }
                }else if(previous_op=="//"){
                    if(tipo1==tipo2 && tipo1=="int"){
                        atrs.setAttr("tipo", "int");
                        atrs.setAttr(
                            "trad", 
                            trad1 + " /i " + trad2
                        );
                    }else if(tipo1=="float"){
                        errorSemantico(ERRNOENTEROIZQ, tokenActual);
                    }else if(tipo2=="float"){
                        errorSemantico(ERRNOENTERODER, tokenActual);
                    }
                }else if(previous_op=="/"){
                    if(tipo1=="int"){
                        trad1 = "itor("+trad1+")";
                    }
                    if(tipo2=="int"){
                        trad2 = "itor("+trad2+")";
                    }
                    atrs.setAttr("tipo", "float");
                    atrs.setAttr(
                        "trad", 
                        trad1 + " " + previous_op + "r " + trad2
                    );
                }else{ // TIENE que ser "*" si o si
                    if(tipo1==tipo2 && tipo1=="int"){
                        atrs.setAttr("tipo", "int");
                        atrs.setAttr(
                            "trad", 
                            trad1 + " " + previous_op + "i " + trad2
                        );
                    }else if(tipo1==tipo2 && tipo1=="float"){
                        atrs.setAttr("tipo", "float");
                        atrs.setAttr(
                            "trad", 
                            trad1 + " " + previous_op + "r " + trad2
                        );
                    }else if(tipo1=="float"){
                        atrs.setAttr("tipo", "float");
                        atrs.setAttr(
                            "trad", 
                            trad1 + " " + previous_op + "r itor(" + trad2 + ")"
                        );
                    }else if(tipo2=="float"){
                        atrs.setAttr("tipo", "float");
                        atrs.setAttr(
                            "trad", 
                            " itor(" + trad1 + ") " + previous_op + "r " + trad2
                        );
                    }
                }
            }
        }else{
            errorSintaxis(Token.ID, Token.NUMENTERO, Token.NUMREAL);
        }
        return atrs;
    }
    
    private Atributos Tp(Atributos atrs_heredados){
        Atributos atrs = new Atributos();
        if(tipoToken == Token.OPMUL){
            reglas.append(30);
            reglas.append(' ');
            String operation = tokenActual.getLexema();
            emparejar(Token.OPMUL);

            Atributos f_atrs  = F(atrs_heredados);
            Atributos tp_atrs = Tp(atrs_heredados);
            
            if(tp_atrs.getAttr("trad")==""){
                // si Tp -> epsilon
                // devuelve el tipo de f y "op f.trad"
                atrs.setAttr("tipo", f_atrs.getAttr("tipo"));
                atrs.setAttr("trad", operation + " " + f_atrs.getAttr("trad"));
            }else{
                // si Tp devuelve trad hay que procesar los tipos comparando F y Tp
                String tipo1=f_atrs.getAttr("tipo"), tipo2=tp_atrs.getAttr("tipo");
                String trad1=f_atrs.getAttr("trad"), trad2=tp_atrs.getAttr("trad");
                String previous_op = trad2.substring(0, 2).replaceAll("\\s", "");
                trad2 = trad2.substring(2); // se le quita el operador a la trad

                if(previous_op=="%"){
                    if(tipo1==tipo2 && tipo1=="int"){
                        atrs.setAttr("tipo", "int");
                        atrs.setAttr(
                            "trad", 
                            operation + " " + trad1 + " " + previous_op + " " + trad2
                        );
                    }else if(tipo1=="float"){
                        errorSemantico(ERRNOENTEROIZQ, tokenActual);
                    }else if(tipo2=="float"){
                        errorSemantico(ERRNOENTERODER, tokenActual);
                    }
                }else if(previous_op=="//"){
                    if(tipo1==tipo2 && tipo1=="int"){
                        atrs.setAttr("tipo", "int");
                        atrs.setAttr(
                            "trad", 
                            operation + " " + trad1 + " /i " + trad2
                        );
                    }else if(tipo1=="float"){
                        errorSemantico(ERRNOENTEROIZQ, tokenActual);
                    }else if(tipo2=="float"){
                        errorSemantico(ERRNOENTERODER, tokenActual);
                    }
                }else if(previous_op=="/"){
                    if(tipo1=="int"){
                        trad1 = "itor("+trad1+")";
                    }
                    if(tipo2=="int"){
                        trad2 = "itor("+trad2+")";
                    }
                    atrs.setAttr("tipo", "float");
                    atrs.setAttr(
                        "trad", 
                        operation + " " + trad1 + " " + previous_op + "r " + trad2
                    );
                }else{ // TIENE que ser "*" si o si
                    if(tipo1==tipo2 && tipo1=="int"){
                        atrs.setAttr("tipo", "int");
                        atrs.setAttr(
                            "trad", 
                            operation + " " + trad1 + " " + previous_op + "i " + trad2
                        );
                    }else if(tipo1==tipo2 && tipo1=="float"){
                        atrs.setAttr("tipo", "float");
                        atrs.setAttr(
                            "trad", 
                            operation + " " + trad1 + " " + previous_op + "r " + trad2
                        );
                    }else if(tipo1=="float"){
                        atrs.setAttr("tipo", "float");
                        atrs.setAttr(
                            "trad", 
                            operation + " " + trad1 + " " + previous_op + "r itor(" + trad2 + ")"
                        );
                    }else if(tipo2=="float"){
                        atrs.setAttr("tipo", "float");
                        atrs.setAttr(
                            "trad", 
                            operation + " itor(" + trad1 + ") " + previous_op + "r " + trad2
                        );
                    }
                }
            }



        }else if(tipoToken == Token.OPAS || tipoToken == Token.PYC || tipoToken == Token.FBLQ || tipoToken == Token.PARD){
            // regla eps
            reglas.append(31);
            reglas.append(' ');
            atrs.setAttr("tipo", "");
            atrs.setAttr("trad", "");
        }else{
            errorSintaxis(Token.OPMUL, Token.OPAS, Token.PYC, Token.FBLQ, Token.PARD);
        }
        return atrs;
    }

    private Atributos F(Atributos atrs_heredados){
        Atributos atrs = new Atributos();
        if(tipoToken == Token.NUMENTERO){
            reglas.append(32);
            reglas.append(' ');
            String id_lex = tokenActual.getLexema();
            emparejar(Token.NUMENTERO);
            atrs.setAttr("tipo", "int");
            atrs.setAttr("trad", id_lex);
        }else if(tipoToken == Token.NUMREAL){
            reglas.append(33);
            reglas.append(' ');
            String id_lex = tokenActual.getLexema();
            emparejar(Token.NUMREAL);
            atrs.setAttr("tipo", "float");
            atrs.setAttr("trad", id_lex);
        }else if(tipoToken == Token.ID) {
            reglas.append(34);
            reglas.append(' ');
            String id_lex = tokenActual.getLexema();
            Token auxToken = tokenActual;
            emparejar(Token.ID);

            if(id_lex==atrs_heredados.getAttr("nombre_funcion")){
                errorSemantico(ERRNOMFUNC, auxToken);
            }else{
                Simbolo simb = tsActual.buscar(id_lex); 
                //! OJO, buscar o buscarAmbito?
                //! yo creo que buscar tiene mas sentido 
                if(simb == null){
                    errorSemantico(ERRNODECL, auxToken);
                }else if(simb.tipo == Simbolo.ENTERO){
                    atrs.setAttr("tipo", "int");
                }else if(simb.tipo == Simbolo.REAL){
                    atrs.setAttr("tipo", "float");
                }else{
                    errorSemantico(ERRNOSIMPLE, auxToken);
                }
                atrs.setAttr("trad", simb.nomtrad);
            }

        }else{
            errorSintaxis(Token.NUMENTERO, Token.NUMREAL, Token.ID);
        }
        return atrs;
    }


       
}    

