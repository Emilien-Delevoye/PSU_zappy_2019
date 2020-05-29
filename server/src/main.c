/*
** EPITECH PROJECT, 2020
** server
** File description:
** Created by emilien
*/

#include "server.h"
#include "utils/parameters.h"

int main(int ac, char **av)
{
    data_server_t data = get_parameters(ac, av);

    (void)data;
    return (0);
}