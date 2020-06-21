/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** Created by emilien
*/

#include "tests.h"
#include <gtest/gtest.h>

TEST(pnw_command, classic_test)
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
    data.params.team_names = new char *[1];
    data.params.team_names[0] = strdup("Team1");
    pnw_command(&cli, &data);
    EXPECT_EQ(std::string(data.l_graphical.first->list_msg->to_write),
        "pnw 3 0 0 0 0 Team1\n");
}

TEST(ppo_command, classic_test)
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
    cli.drone.orientation = 3;
    ppo_command(&cli, &data);
    cli.drone.orientation = 3 + 4;
    ppo_command(&cli, &data);
    EXPECT_EQ(std::string(data.l_graphical.first->list_msg->to_write),
        "ppo 3 0 0 4\n");
}

TEST(seg_command, classic_test)
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
    cli.drone.orientation = 3;
    seg_command(&data, (char *)"Team1");
    EXPECT_EQ(std::string(data.l_graphical.first->list_msg->to_write),
        "seg Team1\n");
}

TEST(sgt_command, classic_test)
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
    cli.drone.orientation = 3;
    data.params.freq = 40;
    sgt_command(&cli, &data, nullptr);
    EXPECT_EQ(std::string(cli.list_msg->to_write),
        "sgt 40\n");
}

TEST(tna_command, classic_test)
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
    cli.drone.orientation = 3;
    data.params.freq = 40;
    data.params.team_names = new char *[2];
    data.params.team_names[0] = strdup("Team1");
    data.params.team_names[1] = nullptr;
    tna_command(&cli, &data, nullptr);
    EXPECT_EQ(std::string(cli.list_msg->to_write),
        "tna Team1\n");
}