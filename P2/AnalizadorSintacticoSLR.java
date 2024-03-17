import java.util.HashMap;
import java.util.Map;
import java.util.TreeSet;
import java.util.ArrayList;
import java.util.List;



public class AnalizadorSintacticoSLR {
    private class Reglas{
        public static final int
            S = 91,
            D = 92,
            L = 93,
            V = 94,
            Tipo = 95,
            B = 96,
            SI = 97,
            I = 98,
            E = 99,
            F = 100;
        
        public final Character LENGTH='l', ID='i';
        
        public ArrayList<Map<Character, Integer>> data = new ArrayList<Map<Character, Integer>>();
        
        Reglas(){
            data.add(createMap(S, 4));
            data.add(createMap(D, 3));
            data.add(createMap(L, 2));
            data.add(createMap(L, 1));
            data.add(createMap(V, 4));
            data.add(createMap(Tipo, 1));
            data.add(createMap(Tipo, 1));
            data.add(createMap(B, 4));
            data.add(createMap(SI, 3));
            data.add(createMap(SI, 1));
            data.add(createMap(I, 3));
            data.add(createMap(I, 4));
            data.add(createMap(I, 1));
            data.add(createMap(E, 3));
            data.add(createMap(E, 1));
            data.add(createMap(F, 1));
            data.add(createMap(F, 1));
            data.add(createMap(F, 1));

        }

        private Map<Character, Integer> createMap(int id, int len){
            Map<Character, Integer> aux = new HashMap<Character, Integer>();
            aux.put(ID, id);
            aux.put(LENGTH, len);
            return aux;
        }

        public Map<Character, Integer> getData(int i){
            return data.get(i);
        }
        
    }



    private class Acciones{
        private Map<Integer, Map<Integer, String>> data = new HashMap<>();
        
        Acciones(){
            set(0,Token.FUNCION ,"d2");
            set(0,Reglas.S,"1");
            set(1,Token.EOF,"acepta");
            set(2,Token.ID,"d3");
            set(2,Reglas.B,"5");
            set(3,Token.PYC,"d4");
            set(4,Token.BLQ,"d6");
            set(5,Token.EOF,"r1");
            set(6,Token.VAR,"d7");
            set(6,Reglas.D,"18");
            set(7,Token.ID,"d12");
            set(7,Reglas.L,"9");
            set(7,Reglas.V,"8");
            set(8,Token.ID,"r4");
            set(8,Token.FVAR,"r4");
            set(9,Token.ID,"d12");
            set(9,Token.FVAR,"d11");
            set(9,Reglas.V,"10");
            set(10,Token.ID,"r3");
            set(10,Token.FVAR,"r3");
            set(11,Token.ID,"r2");
            set(11,Token.BLQ,"r2");
            set(11,Token.ESCRIBE,"r2");
            set(12,Token.DOSP,"d13");
            set(13,Token.ENTERO,"d14");
            set(13,Token.REAL,"d15");
            set(13,Reglas.Tipo,"16");
            set(14,Token.PYC,"r6");
            set(15,Token.PYC,"r7");
            set(16,Token.PYC,"d17");
            set(17,Token.ID,"r5");
            set(17,Token.FVAR,"r5");
            set(18,Token.ID,"d20");
            set(18,Token.BLQ,"d6");
            set(18,Token.ESCRIBE,"d19");
            set(18,Reglas.B,"22");
            set(18,Reglas.SI,"21");
            set(18,Reglas.I,"23");
            set(19,Token.PARI,"d24");
            set(20,Token.ASIG,"d25");
            set(21,Token.PYC,"d35");
            set(21,Token.FBLQ,"d37");
            set(22,Token.PYC,"r13");
            set(22,Token.FBLQ,"r13");
            set(23,Token.PYC,"r10");
            set(23,Token.FBLQ,"r10");
            set(24,Token.ID,"d29");
            set(24,Token.NUMENTERO,"d27");
            set(24,Token.NUMREAL,"d28");
            set(24,Reglas.E,"30");
            set(24,Reglas.F,"26");
            set(25,Token.ID,"d29");
            set(25,Token.NUMENTERO,"d27");
            set(25,Token.NUMREAL,"d28");
            set(25,Reglas.E,"32");
            set(25,Reglas.F,"26");
            set(26,Token.PYC,"r15");
            set(26,Token.FBLQ,"r15");
            set(26,Token.PARD,"r15");
            set(26,Token.OPAS,"r15");
            set(27,Token.PYC,"r16");
            set(27,Token.FBLQ,"r16");
            set(27,Token.PARD,"r16");
            set(27,Token.OPAS,"r16");
            set(28,Token.PYC,"r17");
            set(28,Token.FBLQ,"r17");
            set(28,Token.PARD,"r17");
            set(28,Token.OPAS,"r17");
            set(29,Token.PYC,"r18");
            set(29,Token.FBLQ,"r18");
            set(29,Token.PARD,"r18");
            set(29,Token.OPAS,"r18");
            set(30,Token.PARD,"d31");
            set(30,Token.OPAS,"d33");
            set(31,Token.PYC,"r12");
            set(31,Token.FBLQ,"r12");
            set(32,Token.PYC,"r11");
            set(32,Token.FBLQ,"r11");
            set(32,Token.OPAS,"d33");
            set(33,Reglas.F,"34");
            set(34,Token.PYC,"r14");
            set(34,Token.FBLQ,"r14");
            set(34,Token.PARD,"r14");
            set(34,Token.OPAS,"r14");
            set(35,Token.ID,"d20");
            set(35,Token.BLQ,"d6");
            set(35,Token.ESCRIBE,"d19");
            set(35,Reglas.B,"22");
            set(35,Reglas.I,"36");
            set(36,Token.PYC,"r9");
            set(36,Token.FBLQ,"r9");
            set(37,Token.PYC,"r8");
            set(37,Token.FBLQ,"r8");
            set(37,Token.EOF,"r8");
        }

        public void set(int state, int token, String action) {
            data.putIfAbsent(state, new HashMap<>());
            data.get(state).put(token, action);
        }
        public String get(int state, int token) {
            return data.getOrDefault(state, new HashMap<>()).getOrDefault(token, "No action found");
        }
        
    }
    
    AnalizadorLexico al;
    int estado;
    Token tokenActual;
    int tipoToken;
    ArrayList<Integer> pilaEstados;

    private Reglas reglas;
    private Acciones acciones;

    public AnalizadorSintacticoSLR(AnalizadorLexico al){
        this.al = al;
        this.pilaEstados = new ArrayList<Integer>();
        this.reglas = new Reglas();
        this.acciones = new Acciones();
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
            
            System.err.printf(
                "Error sintactico (%d,%d): encontrado '%s', esperaba %s%n",
                tokenActual.getPos()[0],
                tokenActual.getPos()[1],
                tokenActual.getLexema(),
                aux_tipos.toString()
            );
            
        }
        System.exit(-1);
    }

    private int estadoActual(){
        return this.pilaEstados.get(this.pilaEstados.size()-1);
    }

    private void desapilaEstados(int n){
        ArrayList<Integer> aux = new ArrayList<>(this.pilaEstados.subList(0, this.pilaEstados.size()-n));
        this.pilaEstados.clear();
        for(int i: aux){
            this.pilaEstados.add(i);
        }
    }

    public void analizar(){
        String action;

        this.tokenActual = al.siguienteToken();
        this.tipoToken = this.tokenActual.getTipo();

        this.pilaEstados.add(0);
        int estado = estadoActual();

        do{
            action = acciones.get(estado, this.tipoToken);
            if(action.charAt(0) == 'd'){
                // añade el estado a la pila
                estado = Integer.parseInt(action.substring(1));
                this.pilaEstados.add(estado);

                // coge el nuevo token
                this.tokenActual = al.siguienteToken();
                this.tipoToken = this.tokenActual.getTipo();

            }else if(action.charAt(0) == 'r'){
                Map<Character, Integer> data = reglas.getData(Integer.parseInt(action.substring(1)));

                // desapila los ultimos <len(regla)> estados
                this.desapilaEstados(data.get(reglas.LENGTH));
                estado = estadoActual();

                // apila el nuevo estado
                this.pilaEstados.add(
                    Integer.parseInt(
                        acciones.get(estado, data.get(reglas.ID))
                    )
                );
                estado = estadoActual();

            }else if(action != "acepta"){
                errorSintaxis(); //! REVISAR 
            }

        }while(action != "acepta");
    }

    
}



