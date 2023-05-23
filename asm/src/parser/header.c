/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** header
*/

#include <stdlib.h>

#include "my_str.h"
#include "my_stdio.h"
#include "my_vec.h"
#include "my_cstr.h"

#include "corewar/op.h"
#include "asm/asm.h"
#include "asm/header.h"
#include "asm/error.h"

void write_header(vec_str_t *body, asm_t *assembler)
{
    for (size_t i = 0; i < body->size; i++){
        get_prog_size(body->data[i], &assembler->header->prog_size);
    }
    assembler->header->prog_size = swap_endian(assembler->header->prog_size);
    fwrite(assembler->header, sizeof(header_t), 1, assembler->file);
}

static int check_header_size(header_t *header)
{
    if (my_strlen(header->prog_name) > PROG_NAME_LENGTH) {
        my_dprintf(2, "header: Champion name too long\n");
        return ERROR;
    }
    if (my_strlen(header->comment) > COMMENT_LENGTH) {
        my_dprintf(2, "header: Champion comment too long\n");
        return ERROR;
    }
    return SUCCESS;
}

static int cleanup_header(header_t *header)
{
    char *comment_temp = my_strchr(header->comment, '"');
    char *name_temp = my_strchr(header->prog_name, '"');

    if (name_temp == NULL){
        my_dprintf(2, "header: Invalid .name\n");
        return ERROR;
    }
    if (comment_temp == NULL){
        my_dprintf(2, "header: .comment\n");
        return ERROR;
    }
    *comment_temp = '\0';
    *name_temp = '\0';

    return SUCCESS;
}

static int fill_header(vec_str_t *champ, header_t *header)
{
    int quote_idx = 0;

    for (size_t i = 0; i < champ->size; ++i) {
        if (str_startswith(champ->data[i], STR(NAME_CMD_STRING)) &&
        (quote_idx = str_find(champ->data[i], STR("\""), 0)) != -1)
            my_strcpy(header->prog_name, champ->data[i]->data + quote_idx + 1);
        if (str_startswith(champ->data[i], STR(COMMENT_CMD_STRING )) &&
        (quote_idx = str_find(champ->data[i], STR("\""), 0)) != -1)
            my_strcpy(header->comment, champ->data[i]->data + quote_idx + 1);
    }
    if (header->comment[0] == '\0' || header->prog_name[0] == '\0' ||
        cleanup_header(header) == ERROR || check_header_size(header) == ERROR){
            return ERROR;
        }
    return SUCCESS;
}

vec_str_t *parse_header(char const *champ_path, header_t *header)
{
    str_t *content = read_file(champ_path);
    vec_str_t *champ = NULL;

    if (content == NULL){
        my_dprintf(2, "asm: Can't read source file %s\n", champ_path);
        free(content);
        return NULL;
    }
    champ = str_split(content, STR("\n"));
    for (size_t i = 0; i < champ->size; i++) {
        str_trim(&champ->data[i], '\t');
        str_trim(&champ->data[i], ' ');
    }
    if (fill_header(champ, header) == ERROR){
        free(content);
        vec_free(champ);
        return NULL;
    }
    free(content);
    return champ;
}
