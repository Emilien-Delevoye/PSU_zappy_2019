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

TEST(pdi_command, classic_test)
{
    data_server_t data{};
    client_t cli{};

    data.l_graphical.first = new client_t;
    memset(data.l_graphical.first, 0, sizeof(client_t));
    memset(&cli, 0, sizeof(client_t));
    cli.drone.id = 3;
    pdi_command(&cli, &data);
    EXPECT_EQ(std::string(data.l_graphical.first->list_msg->to_write),
        "pdi 3\n");
}

TEST(pic_command, classic_test)
{
    data_server_t data{};
    client_t cli{};

    data.l_graphical.first = new client_t;
    memset(data.l_graphical.first, 0, sizeof(client_t));
    memset(&cli, 0, sizeof(client_t));
    cli.drone.tile = new map_t;
    cli.drone.tile->coord[0] = 0;
    cli.drone.tile->coord[1] = 0;
    cli.drone.id = 3;
    pic_command(&cli, &data);
    EXPECT_EQ(std::string(data.l_graphical.first->list_msg->to_write),
        "pic 0 0 0 3 3\n");
}