/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** Created by emilien
*/

#include "tests.h"
#include <gtest/gtest.h>

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

TEST(pie_command, classic_test)
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
    pie_command(&cli, &data, 'a');
    EXPECT_EQ(std::string(data.l_graphical.first->list_msg->to_write),
        "pie 3 0 0 a\n");
}

TEST(pin_command, classic_test)
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
    pin_command(&cli, &data);
    EXPECT_EQ(std::string(data.l_graphical.first->list_msg->to_write),
        "pin 3 0 0 0 0 0 0 0\n");
}

TEST(plv_command, classic_test)
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
    plv_command(&cli, &data);
    EXPECT_EQ(std::string(data.l_graphical.first->list_msg->to_write),
        "plv 3 0\n");
}