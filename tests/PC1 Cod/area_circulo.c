/*
 * Entrada: raio do circulo.
 * Usa pi aproximado por 314 / 100 e retorna somente a parte inteira.
 * Exemplo: entrada 10; saida 314.
 */
void main(void)
{
    int raio;
    int quadrado;
    int area;

    raio = input();
    quadrado = raio * raio;
    area = quadrado * 314;
    area = area / 100;
    output(area);
    return;
}