int main()
{
  int a,b,c;
  int v[3];
  int i;
  i = 0;
  //for (i = 0 ; i < 3 ; i++)
  //{
  //  v[i] = i;
  //  printf("%d",v[i]);
  //}
  a = 0;
  b = 1;
  c = 10;
  while (a < c)
  {
    a = a + b;
    printf("%d",a);
  }
  // printf("%d",a);
  // printf("%d",b);
  // printf("%d",c);

  
  a = 0;
  while (a<3)
  {
    v[a] = a;
    printf("%d",v[a]);
    a = a+1;
  }
  a = 0;

  while (a<3)
  {
    printf("%d",v[a]);
    a = a+1;
  }

}
