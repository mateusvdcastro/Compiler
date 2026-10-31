/*
 * Entradas: dividendo e divisor, nesta ordem.
 * A divisao e inteira. Se o divisor for zero, a saida sera zero.
 * Exemplo: entradas 20 e 4; saida 5.
 */
void main(void)
{
    int dividendo;
    int divisor;
    int resultado;

    dividendo = input();
    divisor = input();

    if (divisor == 0) {
        resultado = 0;
    } else {
        resultado = dividendo / divisor;
    }

    output(resultado);
    return;
}
