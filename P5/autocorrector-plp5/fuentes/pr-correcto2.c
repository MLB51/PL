
int main()
{
  int i,j,n;
  int laberinto[5][5];
  int lon,error,salir;
  
  
  n=5;
  // rellenar con 0s el laberinto
  i=0;
  while (i<n)
  {
    j=0;
    while (j<n)
    {
      laberinto[i][j] = 0;
      j=j+1;
    }
    i=i+1;
  }
 
  // poner dos caminos: diagonal y abajo+derecha
  i=0;
  while (i<n)
  {
    laberinto[i][i] = 1;
    i=i+1;
  }

  i=0;
  while (i<n)
  {
    laberinto[i][0] = 1;
    i=i+1;
  }  
  
  i=1;
  while (i<n)
  {
    laberinto[n-1][i] = 1;
    i=i+1;
  }

//! MIO
  i=0;
  while (i<n)
  {
    j= 0;
    while(j<n){
      //int aux;
      //aux = laberinto[i][j];
      printf("%d",laberinto[i][j]); 
      j = j+ 1;
    }
    i=i+1;
  } 
//! MIO
  
  // buscar camino  (voraz)
  lon=1;
  error=0;
  salir=0;
  i=0;
  j=0;
  printf("%d",i); //! HASTA AQUI BIEN
  printf("%d",j);
  //while (i<n && j<n && error==0 && salir==0)
  //while ((i<n) * (j<n) * (error==0) * (salir==0))
  //{
  //  if (laberinto[i][j])
  //  {
  //    int mov; mov=0;
  //    // if ((i<n-1) * (j<n-1) * laberinto[i+1][j+1])  // casca por que no es && y no hay evaluación en cortocircuito
  //    if ((i<n-1) * (j<n-1))
  //    {
  //      if (laberinto[i+1][j+1])
  //      {
  //       i=i+1;
  //       j=j+1;
  //       lon=lon+1;
  //       mov=1;
  //      }
  //    }
  //    if ((mov==0) * (i<n-1))
  //      if (laberinto[i+1][j])
  //      {
  //       i=i+1;
  //       lon=lon+1;
  //       mov=1;
  //      }
  //    if ((mov==0) * (j<n-1))
  //      if (laberinto[i][j+1])
  //      {
  //       j=j+1;
  //       lon=lon+1;
  //       mov=1;
  //      }
  //    if (mov==1) 
  //    {
  //      printf("%d",i);
  //      printf("%d",j);
  //    }
  //    else 
  //    {
  //      if ((i<n-1) + (j<n-1)) // si no hemos llegado al final
  //        error=1;
  //      else
  //        salir=2;
  //    }
  //  }
  //}

  if (error) lon=0-1;
  
  printf("%d",lon); // debe salir 5
  
  // capamos la diagonal, y repetimos código (lo ideal sería usar funciones)
  laberinto[1][1]=0;
  
  // código buscar camino repetido
  lon=1;
  error=0;
  salir=0;
  i=0;
  j=0;
  printf("%d",i);
  printf("%d",j);
  //while (i<n && j<n && error==0 && salir==0)
  //while ((i<n) * (j<n) * (error==0) * (salir==0))
  //{
  //  if (laberinto[i][j])
  //  {
  //    int mov; mov=0;
  //    // if ((i<n-1) * (j<n-1) * laberinto[i+1][j+1])  // casca por que no es && y no hay evaluación en cortocircuito
  //    if ((i<n-1) * (j<n-1))
  //    {
  //      if (laberinto[i+1][j+1])
  //      {
  //       i=i+1;
  //       j=j+1;
  //       lon=lon+1;
  //       mov=1;
  //      }
  //    }
  //    if ((mov==0) * (i<n-1))
  //      if (laberinto[i+1][j])
  //      {
  //       i=i+1;
  //       lon=lon+1;
  //       mov=1;
  //      }
  //    if ((mov==0) * (j<n-1))
  //      if (laberinto[i][j+1])
  //      {
  //       j=j+1;
  //       lon=lon+1;
  //       mov=1;
  //      }
  //    if (mov==1) 
  //    {
  //      printf("%d",i);
  //      printf("%d",j);
  //    }
  //    else 
  //    {
  //      if ((i<n-1) + (j<n-1)) // si no hemos llegado al final
  //        error=1;
  //      else
  //        salir=2;
  //    }
  //  }
  //}

  if (error) lon=0-1;
  
  printf("%d",lon); // debe salir 8
}
