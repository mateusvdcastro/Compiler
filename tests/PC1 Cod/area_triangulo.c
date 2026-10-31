/*
 * Entradas: base e altura, nesta ordem.
 * Calcula a area inteira do triangulo: base * altura / 2.
 * Exemplo: entradas 10 e 6; saida 30.
 */
void main(void)
{
    int base;
    int altura;
    int produto;
    int area;

    base = input();
    altura = input();
    produto = base * altura;
    area = produto / 2;
    output(area);
    return;
}
