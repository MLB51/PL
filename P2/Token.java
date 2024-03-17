import java.util.ArrayList;

public class Token {

	public int fila;
	public int columna;

	public String lexema;
	public int tipo;		// tipo es: ID, ENTERO, REAL ...
	public static final ArrayList<String> nombreToken = new ArrayList<String>();

	static{
		nombreToken.add("(");
		nombreToken.add(")");
		nombreToken.add(":");
		nombreToken.add(":=");
		nombreToken.add(";");
		nombreToken.add("+ -");
		nombreToken.add("'funcion'");
		nombreToken.add("'var'");
		nombreToken.add("'fvar'");
		nombreToken.add("'entero'");
		nombreToken.add("'real'");
		nombreToken.add("'blq'");
		nombreToken.add("'fblq'");
		nombreToken.add("'escribe'");
		nombreToken.add("identificador");
		nombreToken.add("numero entero");
		nombreToken.add("numero real");
		nombreToken.add("fin de fichero");
	}
	public static final int
		PARI 		= 0,
		PARD		= 1,
		DOSP            = 2,
		ASIG		= 3,
		PYC		= 4,
		OPAS		= 5,
		FUNCION		= 6,
		VAR		= 7,
		FVAR		= 8,
		ENTERO		= 9,
		REAL		= 10,
		BLQ		= 11,
		FBLQ		= 12,
		ESCRIBE		= 13,
		ID		= 14,
		NUMENTERO	= 15,
		NUMREAL		= 16,
		EOF		= 17;
		/*
		Hay que quitar:
			COMA
			CORI
			CORD
			PTOPTO
			OPMUL
			TABLA
			DE
			PUNTERO
		*/

	public Token(int f, int c){
		this.fila = f;
		this.columna = c;
		this.lexema = "";
	}

	public void setTipo(int t){
		if(t != ID){
			this.tipo = t;
			return;
		}
		// si es ID hay que comporbar las palabras
		switch (this.lexema) {
			case "funcion":
				this.tipo = FUNCION;
				break;

			case "var":
				this.tipo = VAR;
				break;
			
			case "fvar":
				this.tipo = FVAR;
				break;
			
			case "entero":
				this.tipo = ENTERO;
				break;
			
			case "real":
				this.tipo = REAL;
				break;

			case "blq":
				this.tipo = BLQ;
				break;
			
			case "fblq":
				this.tipo = FBLQ;
				break;
			
			case "escribe":
				this.tipo = ESCRIBE;
				break;
				
			default:
				this.tipo = t;
				break;
		}
	}

	public int getTipo(){
		return this.tipo;
	}

	public String getLexema(){
		return this.lexema;
	}

	public int[] getPos(){
		int[] aux = {this.fila, this.columna};
		return aux;
	}
	public void append(char c){
		this.lexema += c;
	}

	public void clear(){
		this.lexema = "";
	}
	public void goBack(int n){
		this.lexema = this.lexema.substring(0, this.lexema.length()-n);
	}

	public boolean empty(){
		return this.lexema=="";
	}

	public String toString(){
		return nombreToken.get(tipo);
	}
}

