
#include "TablaTipos.h"

TablaTipos::TablaTipos()
{
  // inicializar con los tipos básicos
  
  unTipo b;
  
  b.clase = TIPOBASICO;
  b.tipoBase = ENTERO;
  b.tamanyo = 1;
  tipos.push_back(b);
  
  b.tipoBase = REAL;    
  tipos.push_back(b);
}

unsigned TablaTipos::nuevoTipoArray(unsigned tam,unsigned tbase)
{
  unTipo a;
  
  a.clase = ARRAY;
  a.tamanyo = tam;
  a.tipoBase = tbase;

  tipos.push_back(a);
  return tipos.size()-1;
}

unsigned TablaTipos::getTamanyoRecursivo(unsigned tipo){
  unsigned aux_t = tipo, tam=1;
  while(! ES_TIPO_BASICO(aux_t)){
    unTipo t = tipos[aux_t];
    tam *= t.tamanyo;
    aux_t = t.tipoBase;
  }
  return tam;
}