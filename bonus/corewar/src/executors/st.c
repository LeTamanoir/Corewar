/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** st
*/

#include "my_stdio.h"

#include "corewar/arguments.h"
#include "corewar/corewar.h"
#include "corewar/instructions.h"
#include "corewar/op.h"

int exec_st(vm_t *vm, program_t *p)
{
    argument_t *args = (argument_t[4]){0};
    ind_state_t ind_state = {vm->arena, p->pc, true};
    int st = p->pc;
    int write_addr = 0;

    get_arg_types(vm->arena, &p->pc, args);
    for (int i = 0; i < 2; ++i) {
        get_arg(&args[i], vm->arena, &p->pc);
        if (args[i].arg_type == 0 ||
            (args[i].arg_type == T_REG && (args[i].data.reg == CHAR_MAX)))
            return 0;
    }
    if (args[1].arg_type == T_REG) {
        p->registers[args[1].data.reg - 1] = get_value(&args[0], p, &ind_state);
    } else {
        write_addr = (st + get_value(&args[1], p, &ind_state)) % MEM_SIZE;
        write_int(vm->arena, write_addr, get_value(&args[0], p, &ind_state));
        my_dprintf(
            2, "{\"action\":\"memory\",\"name\":\"%s\",\"address\":%d,\"size\":%d}\n",
            p->header.prog_name, write_addr, REG_SIZE
        );
    }
    return 0;
}
