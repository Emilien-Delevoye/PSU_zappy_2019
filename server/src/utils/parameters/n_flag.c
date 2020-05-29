/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** Created by emilien
*/

#include "utils/parameters.h"
#include <string.h>

bool n_flag(char **av, data_server_t *data)
{
    if (strcmp("-n", av[0]) == 0)
        return (true);
    (void)data;
    return (true);
}
