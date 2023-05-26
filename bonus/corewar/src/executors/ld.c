/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** ld
*/

#include <stddef.h>

#include "corewar/corewar.h"
#include "corewar/op.h"

int exec_ld(vm_t *vm, program_t *p)
{
    u_char *arg_types = (u_char[4]){0};
    int reg = -1;
    int arg1 = 0;
    int st = p->pc;

    p->pc = (p->pc + 1) % MEM_SIZE;
    get_arg_types(vm->arena, p->pc, arg_types);
    p->pc = (p->pc + 1) % MEM_SIZE;

    get_arg(&arg1, vm->arena, &p->pc, arg_types[0]);
    get_arg(&reg, vm->arena, &p->pc, arg_types[1]);
    if (reg == 0)
        return 0;
    p->registers[reg - 1] = (arg_types[0] == T_DIR)
        ? arg1
        : vm->arena[(st + arg1 % IDX_MOD) % MEM_SIZE];
    p->carry = p->registers[reg - 1] == 0;
    return 0;
}