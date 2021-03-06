/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** Created by emilien
*/

#include "tests.h"
#include <gtest/gtest.h>

TEST(pbc_command, classic_test)
{
    data_server_t data{};
    client_t cli{};

    data.l_graphical.first = new client_t;
    memset(data.l_graphical.first, 0, sizeof(client_t));
    memset(&cli, 0, sizeof(client_t));
    cli.drone.id = 3;
    pbc_command(&cli, &data);
    EXPECT_EQ(std::string(data.l_graphical.first->list_msg->to_write),
        "pbc 3\n");
}