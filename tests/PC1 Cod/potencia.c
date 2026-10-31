/*
 * Entradas: base e expoente nao negativo, nesta ordem.
 * Exemplo: entradas 2 e 5; saida 32.
 */
void main(void)
{
    int base;
    int expoente;
    int resultado;

    base = input();
    expoente = input();
    resultado = 1;

    while (expoente > 0) {
        resultado = resultado * base;
        expoente = expoente - 1;
    }

    output(resultado);
    return;
}
