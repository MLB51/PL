
int a,b,c;
float p[4][4];

int main()
{
  int i,j;

  for (i=0;i<4;i++)
    for (j=0;j<4;j++)  
      scanf("%g",&p[i][j]);
  
  if (i==j)
  {
    float sumafila,sumatotal;
    int div;
    scanf("%d",&div);
    
    i=0;
    sumatotal=0;
    while (i<4)
    {
      j=0;
      sumafila=0;
      while (j<4)
      {
        sumafila=sumafila+p[i][j];
        j=j+1;
      }
      printf("%g",sumafila);
      i=i+1;
      sumatotal = sumatotal+sumafila;
    }
    printf("%d",sumatotal/div);
  }
}
