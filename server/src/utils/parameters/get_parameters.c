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
    if (data.params.team_nb < 1 || !data.params.team_names ||
        data.params.port < 1 || data.params.width < 1
        || data.params.height < 1 || data.params.client_nb < 1 ||
        data.params.freq < 1 || !data.params.r_cli)
        st = false;
    data.params.valid_params = st;
    if (!data.params.r_cli)
        return (data);
    for (unsigned short a = 0; a != data.params.team_nb; ++a) {
        data.params.r_cli[a] = data.params.client_nb;
        data.params.win_cli[a] = 0;
    }
    data.params.win_cli[data.params.team_nb] = -1;
    return (data);
}