/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** Created by emilien
*/

#include "utils/parameters.h"
#include <string.h>

bool x_flag(char **av, data_server_t *data)
{
    if (strcmp("-x", av[0]) == 0)
        return (true);
    (void)data;
    return (true);
}