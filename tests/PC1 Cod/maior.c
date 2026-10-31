/*
 * Entradas: dois numeros.
 * Saida: o maior deles.
 * Exemplo: entradas 8 e 3; saida 8.
 */
void main(void)
{
    int primeiro;
    int segundo;
    int resultado;

    primeiro = input();
    segundo = input();

    if (primeiro > segundo) {
        resultado = primeiro;
    } else {
        resultado = segundo;
    }

    output(resultado);
    return;
}
