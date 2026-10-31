# Binarios recompilados para o modo nao preemptivo

A pasta Bin original foi preservada. A comparacao considera palavras de 32 bits, sem diferencas de quebra de linha.

| ID | Programa | Bin: instrucoes | Bin2: instrucoes | Palavras diferentes |
|---|---|---:|---:|---:|
| 1 | area_circulo | 33 | 35 | 32 |
| 2 | area_triangulo | 32 | 34 | 30 |
| 3 | divisao | 37 | 39 | 36 |
| 4 | fatorial_recursivo | 68 | 70 | 45 |
| 5 | gcd | 76 | 78 | 50 |
| 6 | maior | 34 | 36 | 33 |
| 7 | multiplicacao | 26 | 28 | 25 |
| 8 | potencia | 41 | 43 | 40 |
| 9 | soma | 26 | 28 | 25 |
| 10 | sort | 187 | 189 | 144 |

SO.txt: 373 instrucoes, compilado de Compiler/tests/SO/SO.cm.

Os binarios mudam porque o main agora incorpora a base de dados aos ponteiros e usa a area de parametros do segmento. A sequencia adicional tambem altera enderecos de labels e destinos locais.

A ordem dos IDs e a mesma definida explicitamente em montar_imagem.py. Os dez programas ocupam os slots simples; todos ficaram dentro de 256 instrucoes.

Para gerar a ROM, execute python3 montar_imagem.py na raiz LabSO. O script resolve os caminhos a partir do proprio arquivo.
O slot complexo (ID 11) usa complexo.txt, se fornecido nesta pasta; enquanto ausente, recebe HALT para retornar ao SO.

Compilacao e formato/tamanhos foram verificados. Esta recompilacao nao equivale a validar a execucao funcional de cada programa na FPGA.
