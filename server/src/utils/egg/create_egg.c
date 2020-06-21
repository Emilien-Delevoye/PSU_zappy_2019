/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** Created by emilien
*/

#include "server.h"
#include <stdlib.h>

void create_egg(data_server_t *data, client_t *cli)
{
    list_egg_t *new = malloc(sizeof(list_egg_t));

    if (!new)
        return;
    new->next = NULL;
    new->team_id = cli->team_id;
    new->egg_id = init_id();
    (void)data;
}