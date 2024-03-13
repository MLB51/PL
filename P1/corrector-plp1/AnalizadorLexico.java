import java.io.RandomAccessFile;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.lang.Thread;
import java.util.ArrayList;

public class AnalizadorLexico {

    private RandomAccessFile entrada;
    private int estado;
    private int fila;
    private int columna;
    private ArrayList<Token> tokens;
    private ArrayList<int[]> positionBuffer;

    public AnalizadorLexico(RandomAccessFile entrada){
        this.entrada = entrada;
        this.estado = 0;
        this.fila = 1;
        this.columna = 0;
        this.tokens = new ArrayList<Token>();
        this.positionBuffer = new ArrayList<int[]>();
    }
    
    private void errorAt(char actual){
        System.err.printf("Error lexico (%d,%d): caracter '%s' incorrecto", this.fila, this.columna, actual);
        System.exit(-1);
    }

    private void goBack(int n){
        try{
            
            //System.out.print("BUFFER: ");
            //for(int[] pos: this.positionBuffer){
            //    System.out.printf("%d, %d // ", pos[0], pos[1]);
            //}
            //System.out.printf("%n");
            //this.positionBuffer.remove(this.positionBuffer.size()-1);
            int bufferSize = this.positionBuffer.size();
            int[] auxCoord = this.positionBuffer.get(bufferSize-n-1);
            this.columna = auxCoord[0];
            this.fila = auxCoord[1];

            for(int i=0; i<=n; i++){
                //System.out.printf("%d, %d %n ", auxCoord[0], auxCoord[1]);
                this.positionBuffer.remove(bufferSize-i-1);
            }
            this.entrada.seek(this.entrada.getFilePointer()-n);
        }catch(Exception e){
            System.out.println(e);
            return;
        }
    }

    public void savePos(){
        int[] aux = {this.columna, this.fila};
        this.positionBuffer.add(aux);
        if(this.positionBuffer.size()>5){
            this.positionBuffer.remove(0);
        }
    }

    public Token siguienteToken(){
        Token token=null;

        try{
            char actual;
            int actual_int;
            do{
                actual_int = this.entrada.read();
                actual = (char) actual_int;
                //System.out.println(actual);
                //Thread.sleep(200);

                if(actual == '\n'){
                    this.fila++;
                    this.columna = 0;
                }else{
                    this.columna++;
                }
                this.savePos();
                if(token == null){
                    token = new Token(this.fila, this.columna);
                }
                switch(this.estado){
                    case -1:
                        // has just exited from a comment or passed a space/tab/enter
                        // used to avoid exiting from the do while
                        // resets the token as the comment is ignored
                        token = new Token(this.fila,this.columna);
                        //System.out.printf("Creates new tk at (%d, %d)", this.fila, this.columna);
                        // no break; so it goes to case 0
                    case 0:                        
                        if(actual_int == -1){
                            this.estado = 0;
                            token.setTipo(Token.EOF);
                        }else if(Character.isLetter(actual)){
                            token.append(actual);
                            this.estado = 1;
                        }else if(Character.isDigit(actual)){
                            token.append(actual);
                            this.estado = 3;
                        }else if(actual == '/'){
                            token.append(actual);
                            this.estado = 9;
                        }else if(actual == '*' || actual == '%'){
                            token.append(actual);
                            token.setTipo(Token.OPMUL);
                            this.estado = 0;
                        }else if(actual == '.'){
                            token.append(actual);
                            this.estado = 16;
                        }else if(actual == ':'){
                            token.append(actual);
                            this.estado = 18;
                        }else if(actual == '+' || actual == '-'){
                            token.append(actual);
                            token.setTipo(Token.OPAS);
                            this.estado = 0;
                        }else if(actual == '('){
                            token.append(actual);
                            token.setTipo(Token.PARI);
                            this.estado = 0;
                        }else if(actual == ')'){
                            token.append(actual);
                            token.setTipo(Token.PARD);
                            this.estado = 0;
                        }else if(actual == '['){
                            token.append(actual);
                            token.setTipo(Token.CORI);
                            this.estado = 0;
                        }else if(actual == ']'){
                            token.append(actual);
                            token.setTipo(Token.CORD);
                            this.estado = 0;
                        }else if(actual == ','){
                            token.append(actual);
                            token.setTipo(Token.COMA);
                            this.estado = 0;
                        }else if(actual == ';'){
                            token.append(actual);
                            token.setTipo(Token.PYC);
                            this.estado = 0;
                        }else if(actual == ' ' || actual == '\t' || actual == '\n'){
                            this.estado = -1;
                        }else{
                            this.errorAt(actual);
                        }
                        break;
                    case 1:
                        if(Character.isLetterOrDigit(actual)){
                            token.append(actual);
                            // this.estado = 1;
                        }else{
                            this.goBack(1);
                            token.setTipo(Token.ID);
                            this.estado = 0;
                        }
                        break;

                    case 3:
                        if(Character.isDigit(actual)){
                            token.append(actual);
                            // this.estado = 3;
                        }else if(actual == '.'){
                            token.append(actual);
                            this.estado = 4;
                        }else{
                            this.goBack(1);
                            token.setTipo(Token.NUMENTERO);
                            this.estado = 0;
                        }
                        break;

                    case 4:
                        if(Character.isDigit(actual)){
                            token.append(actual);
                            this.estado = 5;
                        }else{
                            this.goBack(2);
                            token.goBack(1);
                            token.setTipo(Token.NUMENTERO);
                            this.estado = 0;
                        }
                        break;

                    case 5:
                        if(Character.isDigit(actual)){
                            token.append(actual);
                            // this.estado = 5;
                        }else{
                            this.goBack(1);
                            token.setTipo(Token.NUMREAL);
                            this.estado = 0;
                        }
                        break;

                    case 9:
                        if(actual == '*'){
                            token.clear();
                            this.estado = 10;
                        }else if(actual == '/'){
                            token.append(actual);
                            token.setTipo(Token.OPMUL);
                            this.estado = 0;
                        }else{
                            this.goBack(1);
                            token.setTipo(Token.OPMUL);
                            this.estado = 0;
                        }
                        break;
                        
                    case 10:
                        if(actual == '*'){
                            this.estado = 11;
                        }else if(actual_int == -1){
                            System.err.println("Error lexico: fin de fichero inesperado");
                            this.entrada.close();
                            System.exit(-1);

                        }
                        break;

                    case 11:
                        if(actual == '/'){
                            this.estado = -1;
                        }else if(actual_int == -1){
                            System.err.println("Error lexico: fin de fichero inesperado");
                            this.entrada.close();
                            System.exit(-1);
                        }else{
                            this.estado = 10;
                        }
                        break;

                    case 16:
                        if(actual == '.'){
                            token.append(actual);
                            token.setTipo(Token.PTOPTO);
                            this.estado = 0;
                        }else{
                            // esta linea es de dudosa utilidad para el ASDR, pero vale para el lexico
                            this.columna--;
                            // si, esta hardcodeado, pero esque siempre va a ser '.', asi que para que complicarse...
                            this.errorAt('.');
                        }
                        break;
                        
                    case 18:
                        if(actual == '='){
                            token.append(actual);
                            token.setTipo(Token.ASIG);
                            this.estado = 0;
                        }else{
                            this.goBack(1);
                            token.setTipo(Token.DOSP);
                            this.estado = 0;
                        }
                        break;
                }
                
                if(actual_int == -1 && token.empty()){
                    this.entrada.close();
                    break;
                }else if(actual_int == -1 && !token.empty()){
                    this.entrada.read(); //! what
                    break;
                }
            }while(this.estado != 0); // cuando llega de nuevo al 0 es porque consigue un token

            if(this.estado != 0){
                System.err.println("Error lexico: fin de fichero inesperado");
                this.entrada.close();
                System.exit(-1);
            }
            tokens.add(token);
            return token;
        }catch(IOException e){
            System.out.println("file closed");
            return null;
        }
        //catch(InterruptedException e){
        //    return token;
        //}
    }
}