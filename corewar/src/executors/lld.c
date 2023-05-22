/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** lld
*/

#include <sys/types.h>
#include "corewar/corewar.h"

int exec_lld(vm_t *vm, program_t *p)
{
    int arg = 0;
    int reg = 0;
    u_char *arg_types = (u_char[4]){0};

    p->pc = (p->pc + 1) % MEM_SIZE;
    get_arg_types(vm->arena, p->pc, arg_types);
    p->pc = (p->pc + 1) % MEM_SIZE;
    get_arg(&arg, vm->arena, &p->pc, arg_types[0]);
    get_arg(&reg, vm->arena, &p->pc, arg_types[1]);
    if (reg == 0)
        return 0;
    p->registers[reg - 1] = arg;
    p->carry = 1;
    return 0;
}