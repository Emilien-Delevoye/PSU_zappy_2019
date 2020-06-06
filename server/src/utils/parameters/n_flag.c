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
    return (a);
}

static void create_tab(data_server_t *data, char **av)
{
    data->team_names = malloc(sizeof(char *) * (data->team_nb + 1));
    if (!data->team_names)
        return;
    for (unsigned int a = 0; a < (data->team_nb - 1); ++a) {
        data->team_names[a] = strdup(av[a + 1]);
        data->team_names[a + 1] = NULL;
    }
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
    data->team_nb = nb_team;
    create_tab(data, av);
    if (!data->team_names || data->team_nb < 1)
        return (false);
    return (true);
}
