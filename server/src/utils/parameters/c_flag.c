/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** Created by emilien
*/

#include "utils/parameters.h"
#include <string.h>
#include <stdio.h>

static unsigned int get_client_nb(char *client_nb_in)
{
    int client_nb;

    if (sscanf(client_nb_in, "%d", &client_nb) != 1)
        client_nb = -1;
    return (client_nb);
}

bool c_flag(char **av, data_server_t *data)
{
    static bool use_flag = false;

    if (strcmp("-c", av[0]) != 0)
        return (true);
    if (use_flag == true || !av[1])
        return (false);
    use_flag = true;
    data->client_nb = get_client_nb(av[1]);
    if (data->client_nb < 1)
        return (false);
    return (true);
}