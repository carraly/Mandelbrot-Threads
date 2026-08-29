# Mandelbrot Threads

Programa em C que gera o conjunto de Mandelbrot usando quatro implementações diferentes — Serial, OpenMP, Pthreads (blocos contíguos) e Pthreads (forma cíclica) — e compara o tempo de execução entre elas.

## Compilação

```bash
make
```

## Execução

```bash
./mandelbrot [largura] [altura] [max_iteracoes] [num_threads]
```

Exemplo:

```bash
./mandelbrot 800 600 100 4
```

## Limpeza

```bash
make clean
```

## Saída

Cada execução gera:

- **mandelbrot_vchlm_serial.pgm**
- **mandelbrot_vchlm_openmp.pgm**
- **mandelbrot_vchlm_pthreads1.pgm**
- **mandelbrot_vchlm_pthreads2.pgm**
- **times.txt** — tempo de execução de cada implementação

Cada **.pgm** contém a intensidade de cada pixel (0–255), um valor por pixel, separado por espaço, uma linha por linha da imagem.

## Estratégias de paralelização

- **OpenMP**: **#pragma omp parallel for** com **schedule(dynamic)**.
- **Pthreads 1**: divide a imagem em blocos contíguos de linhas, um bloco por thread.
- **Pthreads 2**: divide as linhas de forma cíclica entre as threads.

## Estrutura do código

- **main.c** — ponto de entrada, orquestra as quatro implementações
- **errors.c** — validação de argumentos e checagem de erros
- **math.c** — mapeamento de coordenadas e alocação da matriz de resultado
- **serial.c** — implementação serial
- **openmp.c** — implementação com OpenMP
- **pthreads1.c** — implementação com Pthreads (blocos contíguos)
- **pthreads2.c** — implementação com Pthreads (forma cíclica)