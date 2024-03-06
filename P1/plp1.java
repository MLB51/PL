/*

import java.io.RandomAccessFile;
import java.io.FileNotFoundException;
import java.io.IOException;

class plp1 {
    public static void main(String[] args) {

        if (args.length == 1){
            try {
                RandomAccessFile entrada = new RandomAccessFile(args[0],"r");
                AnalizadorLexico al = new AnalizadorLexico(entrada);
                Token tk;
                do{
                    tk = al.siguienteToken();
                    int[] pos = tk.getPos();
                    System.out.printf("%s -> %s at %d, %d %n",tk, tk.getLexema(), pos[0], pos[1]);
                }while(tk.getTipo() != Token.EOF);

                // AnalizadorSintacticoDR asdr = new AnalizadorSintacticoDR(al);
                // asdr.S(); // simbolo inicial de la gramatica
                // asdr.comprobarFinFichero();
            } catch (FileNotFoundException e) {
                System.out.println("Error, fichero no encontrado: " + args[0]);
            }

        } else {
            System.out.println("Error, uso: java plp1 <nomfichero>");
        }
    }
}

*/


import java.io.RandomAccessFile;
import java.io.FileNotFoundException;
import java.io.IOException;

class plp1 {
    public static void main(String[] args) {

        if (args.length == 1)
        {
          try {
            RandomAccessFile entrada = new RandomAccessFile(args[0],"r");
            AnalizadorLexico al = new AnalizadorLexico(entrada);
            AnalizadorSintacticoDR asdr = new AnalizadorSintacticoDR(al);
            asdr.S(); // simbolo inicial de la gramatica
            asdr.comprobarFinFichero();
          }
          catch (FileNotFoundException e) {
            System.out.println("Error, fichero no encontrado: " + args[0]);
          }
        } 
        else System.out.println("Error, uso: java plp1 <nomfichero>");
    }
}



