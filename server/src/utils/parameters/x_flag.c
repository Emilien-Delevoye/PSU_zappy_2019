/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** Created by emilien
*/

#include "utils/parameters.h"
#include <string.h>
#include <stdio.h>

static unsigned int get_width(char *width_in)
{
    int width;

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
    data->width = get_width(av[1]);
    if (data->width < 1)
        return (false);
    return (true);
}