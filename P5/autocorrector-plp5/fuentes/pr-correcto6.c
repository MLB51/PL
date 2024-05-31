int main()
{
  int a,b,c;
  int zero, uno;
  zero = 0;
  uno = 1;

  a = 1;
  b = 2;
  c = 3;

  if(a<b){
    printf("%d",uno);
  }else{
    printf("%d",zero);
  }

  if(a<=b){
    printf("%d",uno);
  }else{
    printf("%d",zero);
  }


  if(a>b){
    printf("%d",uno);
  }else{
    printf("%d",zero);
  }
  if(a>=b){
    printf("%d",uno);
  }else{
    printf("%d",zero);
  }



  if(a==uno){
    printf("%d",uno);
  }else{
    printf("%d",zero);
  }
  if(a!=b){
    printf("%d",uno);
  }else{
    printf("%d",zero);
  }


  if((a<b) * (b<c)){
    printf("%d",uno);
  }else{
    printf("%d",zero);
  }
  if((a>b) + (b<=c)){
    printf("%d",uno);
  }else{
    printf("%d",zero);
  }

}
