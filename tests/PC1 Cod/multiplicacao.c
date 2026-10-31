/*
 * Entradas: dois numeros, na ordem em que forem fornecidos.
 * Exemplo: entradas 6 e 7; saida 42.
 */
void main(void)
{
    int primeiro;
    int segundo;
    int resultado;

    primeiro = input();
    segundo = input();
    resultado = primeiro * segundo;
    output(resultado);
    return;
}
