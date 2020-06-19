/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** Created by emilien
*/

#include "utils/parameters.h"
#include <string.h>
#include <stdio.h>

static int get_freq(char *freq_in)
{
    int freq;

    for (int a = 0; freq_in[a]; ++a)
        if (freq_in[a] > '9' || freq_in[a] < '0')
            return (-1);
    if (sscanf(freq_in, "%d", &freq) != 1)
        freq = -1;
    return (freq);
}

bool f_flag(char **av, data_server_t *data)
{
    static bool use_flag = false;

    if (strcmp("-f", av[0]) != 0)
        return (true);
    if (use_flag == true || !av[1])
        return (false);
    use_flag = true;
    data->params.freq = get_freq(av[1]);
    if (data->params.freq < 1)
        return (false);
    return (true);
}
