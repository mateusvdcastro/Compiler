/*
 * Entrada: numero cujo fatorial sera calculado.
 * Use um numero pequeno para evitar estouro e excesso de recursao.
 * Exemplo: entrada 5; saida 120.
 */
int fatorial(int n)
{
    int parcial;

    if (n < 2) {
        return 1;
    } else {
        parcial = fatorial(n - 1);
        return parcial * n;
    }
}

void main(void)
{
    int numero;
    int resultado;

    numero = input();
    resultado = fatorial(numero);
    output(resultado);
    return;
}
