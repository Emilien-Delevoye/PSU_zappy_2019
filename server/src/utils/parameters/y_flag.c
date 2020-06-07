/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** Created by emilien
*/

#include "utils/parameters.h"
#include <string.h>
#include <stdio.h>

static int get_height(char *height_in)
{
    int height;

    for (int a = 0; height_in[a]; ++a)
        if (height_in[a] > '9' || height_in[a] < '0')
            return (-1);
    if (sscanf(height_in, "%d", &height) != 1)
        height = -1;
    return (height);
}

bool y_flag(char **av, data_server_t *data)
{
    static bool use_flag = false;

    if (strcmp("-y", av[0]) != 0)
        return (true);
    if (use_flag == true || !av[1])
        return (false);
    use_flag = true;
    data->params.height = get_height(av[1]);
    if (data->params.height < 1)
        return (false);
    return (true);
}