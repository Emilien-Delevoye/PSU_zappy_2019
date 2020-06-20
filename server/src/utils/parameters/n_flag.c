/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** Created by emilien
*/

#include "utils/parameters.h"
#include <string.h>
#include <stdlib.h>

static unsigned int count_teams(char **av)
{
    int a = 1;

    if (!av[1])
        return (0);
    while (av[a] && av[a][0] != '-')
        ++a;
    return (a - 1);
}

static void create_tab(data_server_t *d, char **av)
{
    d->params.team_names =
        malloc(sizeof(char *) * (d->params.team_nb + 1));
    if (!d->params.team_names)
        return;
    for (unsigned int a = 0; a < d->params.team_nb; ++a) {
        d->params.team_names[a] = strdup(av[a + 1]);
        d->params.team_names[a + 1] = NULL;
    }
}

static bool create_names(data_server_t *data)
{
    data->params.r_cli =
        malloc(sizeof(unsigned short) * (data->params.team_nb + 1));
    data->params.win_cli =
        malloc(sizeof(unsigned short) * (data->params.team_nb + 1));

    if (!data->params.r_cli)
        return (false);
    if (!data->params.win_cli)
        return (false);
    memset(data->params.r_cli, 0,
        sizeof(unsigned short) * (data->params.team_nb + 1));
    memset(data->params.win_cli, 0,
        sizeof(unsigned short) * (data->params.team_nb + 1));
    return (true);
}

bool n_flag(char **av, data_server_t *data)
{
    static bool use_flag = false;
    unsigned int nb_team;

    if (strcmp("-n", av[0]) != 0)
        return (true);
    nb_team = count_teams(av);
    if (use_flag == true || !av[1] || nb_team == 0)
        return (false);
    use_flag = true;
    data->params.team_nb = nb_team;
    create_tab(data, av);
    if (!data->params.team_names || data->params.team_nb < 1)
        return (false);
    return (create_names(data));
}
