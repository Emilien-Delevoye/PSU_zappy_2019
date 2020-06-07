/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** Created by emilien
*/

#include "utils/parameters.h"
#include <string.h>
#include <stdio.h>

static int get_port(char *port_in)
{
    int port;

    for (int a = 0; port_in[a]; ++a)
        if (port_in[a] > '9' || port_in[a] < '0')
            return (-1);
    if (sscanf(port_in, "%d", &port) != 1)
        port = -1;
    return (port);
}

bool p_flag(char **av, data_server_t *data)
{
    static bool use_flag = false;

    if (strcmp("-p", av[0]) != 0)
        return (true);
    if (use_flag == true || !av[1])
        return (false);
    use_flag = true;
    data->port = get_port(av[1]);
    if (data->port < 1)
        return (false);
    return (true);
}
