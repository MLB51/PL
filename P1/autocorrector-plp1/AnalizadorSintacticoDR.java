import java.util.TreeSet;

public class AnalizadorSintacticoDR {
    private AnalizadorLexico al;
    private Token tokenActual;
    private int tipoToken;
    boolean printeaReglas = true;
    StringBuilder reglas = new StringBuilder();


    public AnalizadorSintacticoDR(AnalizadorLexico al){
        this.al = al;
        this.tokenActual = al.siguienteToken();
        this.tipoToken = this.tokenActual.getTipo();
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

    public void comprobarFinFichero(){
        if(printeaReglas){
            System.out.println(reglas.toString());
        }
    }

    private void emparejar(int tipo){
        if(tipoToken == tipo){
            this.tokenActual = al.siguienteToken();
            this.tipoToken = this.tokenActual.getTipo();
        }else{
            errorSintaxis(tipo);
        }
    }

    public void S(){
        // simbolño inciial es publico, el resto no
        if(tipoToken == Token.FUNCION){
            reglas.append(1);
            reglas.append(' ');
            emparejar(Token.FUNCION);
            emparejar(Token.ID);
            emparejar(Token.PYC);
            S();
            B();
        }else if(tipoToken == Token.EOF || tipoToken == Token.BLQ){
            // regla  epsilon == pasar de largo, no?
            reglas.append(2);
            reglas.append(' ');
        }else{
            errorSintaxis(Token.FUNCION, Token.EOF, Token.BLQ);
        }
    } 

    private void D(){
        if(tipoToken == Token.VAR){
            reglas.append(3);
            reglas.append(' ');
            emparejar(Token.VAR);
            L();
            emparejar(Token.FVAR);
        }else{
            errorSintaxis(Token.VAR);
        }
    }

    private void L(){
        if(tipoToken == Token.ID){
            reglas.append(4);
            reglas.append(' ');
            V();
            Lp();
        }else{
            errorSintaxis(Token.ID);
        }
    }

    private void Lp(){
        if(tipoToken == Token.ID){
            reglas.append(5);
            reglas.append(' ');
            V();
            Lp();
        }else if(tipoToken == Token.FVAR){
            // regla eps
            reglas.append(6);
            reglas.append(' ');
        }else{
            errorSintaxis(Token.ID, Token.FVAR);
        }
    }

    private void V(){
        if(tipoToken == Token.ID){
            reglas.append(7);
            reglas.append(' ');
            emparejar(Token.ID);
            emparejar(Token.DOSP);
            C();
            emparejar(Token.PYC);
        }else{
            errorSintaxis(Token.ID);
        }
    }

    private void C(){
        if(tipoToken == Token.TABLA){
            reglas.append(8);
            reglas.append(' ');
            A();
            C();
        }else if(tipoToken == Token.ENTERO || tipoToken==Token.REAL || tipoToken==Token.PUNTERO){
            reglas.append(9);
            reglas.append(' ');
            P();
        }else{
            errorSintaxis(Token.TABLA, Token.ENTERO, Token.REAL);
        }
    }

    private void A(){
        if(tipoToken == Token.TABLA){
            reglas.append(10);
            reglas.append(' ');
            emparejar(Token.TABLA);
            emparejar(Token.CORI);
            R();
            emparejar(Token.CORD);
            emparejar(Token.DE);
        }else{
            errorSintaxis(Token.TABLA);
        }
    }

    private void R(){
        if(tipoToken == Token.NUMENTERO){
            reglas.append(11);
            reglas.append(' ');
            G();
            Rp();
        }else{
            errorSintaxis(Token.NUMENTERO);
        }
    }

    private void Rp(){
        if(tipoToken == Token.COMA){
            reglas.append(12);
            reglas.append(' ');
            emparejar(Token.COMA);
            G();
            Rp();
        }else if(tipoToken == Token.CORD){
            // regla eps
            reglas.append(13);
            reglas.append(' ');
        }else{
            errorSintaxis(Token.COMA, Token.CORD);
        }
    }

    private void G(){
        if(tipoToken == Token.NUMENTERO){
            reglas.append(14);
            reglas.append(' ');
            emparejar(Token.NUMENTERO);
            emparejar(Token.PTOPTO);
            emparejar(Token.NUMENTERO);
        }else{
            errorSintaxis(Token.NUMENTERO);
        }
    }

    private void P(){
        if(tipoToken == Token.PUNTERO){
            reglas.append(15);
            reglas.append(' ');
            emparejar(Token.PUNTERO);
            emparejar(Token.DE);
            P();
        }else if(tipoToken == Token.ENTERO || tipoToken == Token.REAL){
            reglas.append(16);
            reglas.append(' ');
            TIPO();
        }else{
            errorSintaxis(Token.PUNTERO, Token.ENTERO, Token.REAL);
        }
    }

    private void TIPO(){
        if(tipoToken == Token.ENTERO){
            reglas.append(17);
            reglas.append(' ');
            emparejar(Token.ENTERO);
        }else if(tipoToken == Token.REAL){
            reglas.append(18);
            reglas.append(' ');
            emparejar(Token.REAL);
        }else{
            errorSintaxis(Token.ENTERO, Token.REAL);
        }
    }

    private void B(){
        if(tipoToken == Token.BLQ){
            reglas.append(19);
            reglas.append(' ');
            emparejar(Token.BLQ);
            D();
            SI();
            emparejar(Token.FBLQ);
        }else{
            errorSintaxis(Token.BLQ);
        }
    }

    private void SI(){
        if(tipoToken == Token.ID || tipoToken == Token.ESCRIBE || tipoToken == Token.BLQ){
            reglas.append(20);
            reglas.append(' ');
            I();
            M();
        }else{
            errorSintaxis(Token.ID, Token.ESCRIBE, Token.BLQ);
        }
    }

    private void M(){
        if(tipoToken == Token.PYC){
            reglas.append(21);
            reglas.append(' ');
            emparejar(Token.PYC);
            I();
            M();
        }else if(tipoToken == Token.FBLQ){
            // regla eps
            reglas.append(22);
            reglas.append(' ');
        }else{
            errorSintaxis(Token.PYC, Token.FBLQ);
        }
    }

    private void I(){
        if(tipoToken == Token.ID){
            reglas.append(23);
            reglas.append(' ');
            emparejar(Token.ID);
            emparejar(Token.ASIG);
            E();
        }else if(tipoToken == Token.ESCRIBE){
            reglas.append(24);
            reglas.append(' ');
            emparejar(Token.ESCRIBE);
            emparejar(Token.PARI);
            E();
            emparejar(Token.PARD);
        }else if(tipoToken == Token.BLQ){
            reglas.append(25);
            reglas.append(' ');
            B();
        }else{
            errorSintaxis(Token.ID, Token.ESCRIBE, Token.BLQ);
        }
    }

    private void E(){
        if(tipoToken == Token.NUMENTERO || tipoToken == Token.NUMREAL || tipoToken == Token.ID){
            reglas.append(26);
            reglas.append(' ');
            T();
            Ep();
        }else{
            errorSintaxis(Token.ID, Token.NUMENTERO, Token.NUMREAL);
        }
    }
    private void Ep(){
        if(tipoToken == Token.OPAS){
            reglas.append(27);
            reglas.append(' ');
            emparejar(Token.OPAS);
            T();
            Ep();
        }else if(tipoToken == Token.PYC || tipoToken == Token.FBLQ || tipoToken == Token.PARD){
            // regla eps
            reglas.append(28);
            reglas.append(' ');
        }else{
            errorSintaxis(Token.OPAS, Token.PYC, Token.FBLQ, Token.PARD);
        }
    }

    private void T(){
        if(tipoToken == Token.NUMENTERO || tipoToken == Token.NUMREAL || tipoToken == Token.ID){
            reglas.append(29);
            reglas.append(' ');
            F();
            Tp();
        }else{
            errorSintaxis(Token.ID, Token.NUMENTERO, Token.NUMREAL);
        }
    }
    private void Tp(){
        if(tipoToken == Token.OPMUL){
            reglas.append(30);
            reglas.append(' ');
            emparejar(Token.OPMUL);
            F();
            Tp();
        }else if(tipoToken == Token.OPAS || tipoToken == Token.PYC || tipoToken == Token.FBLQ || tipoToken == Token.PARD){
            // regla eps
            reglas.append(31);
            reglas.append(' ');
        }else{
            errorSintaxis(Token.OPMUL, Token.OPAS, Token.PYC, Token.FBLQ, Token.PARD);
        }
    }

    private void F(){
        if(tipoToken == Token.NUMENTERO){
            reglas.append(32);
            reglas.append(' ');
            emparejar(Token.NUMENTERO);
        }else if(tipoToken == Token.NUMREAL){
            reglas.append(33);
            reglas.append(' ');
            emparejar(Token.NUMREAL);
        }else if(tipoToken == Token.ID) {
            reglas.append(34);
            reglas.append(' ');
            emparejar(Token.ID);
        }else{
            errorSintaxis(Token.NUMENTERO, Token.NUMREAL, Token.ID);
        }
    }

}