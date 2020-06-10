/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** Created by emilien
*/

#include "tests.h"
#include <gtest/gtest.h>
#include <fcntl.h>

TEST(close_server, close_server)
{
    data_server_t data;

    data.fd = open("Makefile", O_RDONLY);
    data.params.team_names = new char *[4];
    data.params.team_names[0] = strdup("Team1");
    data.params.team_names[1] = strdup("Team2");
    data.params.team_names[2] = strdup("Team3");
    data.params.team_names[3] = nullptr;
    data.params.height = 1;
    data.params.width = 2;
    setup_map(&data);
    close_server(data);
}