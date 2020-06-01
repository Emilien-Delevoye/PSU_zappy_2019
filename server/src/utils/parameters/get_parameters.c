/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** Created by emilien
*/

#include "server.h"
#include "utils/parameters.h"
#include <stdlib.h>

bool (*fl[7])(char **, data_server_t *) =
{
    p_flag, x_flag, y_flag, n_flag, c_flag, f_flag, NULL
};

data_server_t get_parameters(int ac, char **av)
{
    data_server_t data = {0};
    bool st = true;

    for (int a = 0; a < ac && av[a]; ++a)
        for (int b = 0; fl[b]; ++b)
            st = (fl[b](av + a, &data) == true && st == true ? true : false);
    if (data.team_nb < 1 || !data.team_names || data.port < 1 || data.width < 1
        || data.height < 1 || data.client_nb < 1 || data.freq < 1)
        st = false;
    data.valid_params = st;
    return (data);
}