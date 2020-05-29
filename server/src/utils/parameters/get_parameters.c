/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** Created by emilien
*/

#include "server.h"
#include "utils/parameters.h"
#include <stdlib.h>

//const char *flags[] = {"-p", "-x", "-y", "-n", "-c", "-f", NULL};

bool (*flags[7])(char **, data_server_t *) =
{
    p_flag, x_flag, y_flag, n_flag, c_flag, f_flag, NULL
};

data_server_t get_parameters(int ac, char **av)
{
    data_server_t data = {0};

    for (int a = 0; a < ac && av[a]; ++a) {
        for (int b = 0; flags[b]; ++b);
    }
    return (data);
}