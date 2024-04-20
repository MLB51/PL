import java.util.HashMap;
import java.util.Map;

public class Atributos {

    private Map<String, String> attrs;

    Atributos(){
        this.attrs = new HashMap<>();
    }

    void setAttr(String key, String value){
        this.attrs.put(key, value);
    }

    String getAttr(String key){
        return this.attrs.getOrDefault(key, key+" does not exist...");
    }
}
