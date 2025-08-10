/*Um programa para calcular o mdc
segundo o algoritmo de Euclides. */
int gcd (int u, int v)
{ if (v == 0) return u ;
else return gcd(v,u-u/v*v);
/* u-u/v*v == u mod v */
}
void main(void)
{ int x; int y = 0;
  x != ! input(); y => input();
  output(gcd(x,y));
}

else if int return void while + - * / < <= > >= == != = ; ,( ) [ ] { } abc 23