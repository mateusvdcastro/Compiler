#ifndef MEMORY_LAYOUT_H
#define MEMORY_LAYOUT_H

/* Enderecos em palavras de 32 bits. */
#define INSTR_ADDR_WIDTH             13
#define DATA_ADDR_WIDTH              13

#define INSTR_MEMORY_WORDS           8192
#define DATA_MEMORY_WORDS            8192

/* Memoria de instrucoes. */
#define SO_INTERVAL                  2048

#define MAX_PROGS_SIMPLE             10
#define MAX_PROGS_COMPLEX            1
#define MAX_PROGS                    11
#define COMPLEX_PROG_ID              11

#define START_IM                     2048
#define PROGRAM_INTERVAL             256

#define START_IM_COMPLEX             4608
#define PROGRAM_INTERVAL_COMPLEX     3584

/* Memoria de dados. */
#define SO_DATA_RESERVED             512

#define START_DM                     512
#define PROG_INTERVAL_DM             512

#define START_DM_COMPLEX             5632
#define PROG_INTERVAL_DM_COMPLEX      2560

/* Reservas no fim de cada segmento de dados. */
#define CONTEXT_WORDS                32
#define PARAM_AREA_WORDS             32

/* SO e programas simples: parametros 448..479, contexto 480..511. */
#define INIT_CONTEXT_SWITCH \
    (SO_DATA_RESERVED - CONTEXT_WORDS)

#define INIT_STACK_PARAMS \
    (INIT_CONTEXT_SWITCH - PARAM_AREA_WORDS)

/* Complexo: parametros 2496..2527, contexto 2528..2559. */
#define INIT_STACK_PARAMS_COMPLEX \
    (PROG_INTERVAL_DM_COMPLEX - CONTEXT_WORDS - PARAM_AREA_WORDS)

/* Usar somente com IDs de usuario entre 1 e 11. */
#define PROG_IM_BASE(N) \
    ((N) <= MAX_PROGS_SIMPLE \
        ? START_IM + ((N) - 1) * PROGRAM_INTERVAL \
        : START_IM_COMPLEX)

#define PROG_DM_BASE(N) \
    ((N) <= MAX_PROGS_SIMPLE \
        ? START_DM + ((N) - 1) * PROG_INTERVAL_DM \
        : START_DM_COMPLEX)

#endif