int menu(void)
{
    int escolha;

    escolha = 0;

    setLcd(10);
    escolha = input();

    return escolha;
}

void main(void)
{
    int escolha;

    escolha = menu();
    output(escolha);
}