/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** Created by emilien
*/

#include "utils/parameters.h"
#include <string.h>
#include <stdio.h>

static int get_width(char *width_in)
{
    int width;

    for (int a = 0; width_in[a]; ++a)
        if (width_in[a] > '9' || width_in[a] < '0')
            return (-1);
    if (sscanf(width_in, "%d", &width) != 1)
        width = -1;
    return (width);
}

bool x_flag(char **av, data_server_t *data)
{
    static bool use_flag = false;

    if (strcmp("-x", av[0]) != 0)
        return (true);
    if (use_flag == true || !av[1])
        return (false);
    use_flag = true;
    data->params.width = get_width(av[1]);
    if (data->params.width < 1)
        return (false);
    return (true);
}