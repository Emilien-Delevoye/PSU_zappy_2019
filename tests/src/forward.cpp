/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** Created by emilien
*/

#include "tests.h"
#include <gtest/gtest.h>

void do_move(data_server_t *data, client_t *cli)
{
    cli->drone.orientation = NORTH;
    forward(data);
    EXPECT_EQ(cli->drone.tile->coord[0], 1);
    EXPECT_EQ(cli->drone.tile->coord[1], 0);
    cli->drone.orientation = SOUTH;
    forward(data);
    EXPECT_EQ(cli->drone.tile->coord[0], 0);
    EXPECT_EQ(cli->drone.tile->coord[1], 0);
    cli->drone.orientation = EAST;
    forward(data);
    EXPECT_EQ(cli->drone.tile->coord[0], 0);
    EXPECT_EQ(cli->drone.tile->coord[1], 1);
    cli->drone.orientation = WEST;
    forward(data);
    EXPECT_EQ(cli->drone.tile->coord[0], 0);
    EXPECT_EQ(cli->drone.tile->coord[1], 0);
}

TEST(forward, classic_test)
{
    data_server_t data{};
    client_t *cli = new client_t;

    memset(&data, 0, sizeof(data_server_t));
    memset(cli, 0, sizeof(client_t));
    data.params.height = 2;
    data.params.width = 2;
    setup_map(&data);
    data.cli_work = new list_actions_t;
    memset(data.cli_work, 0, sizeof(list_actions_t));
    data.cli_work->cli = cli;
    cli->drone.tile = data.bottom_left;
    cli->drone.tile->list_players = new tile_players_t;
    cli->drone.tile->list_players->cli = cli;
    cli->drone.tile->list_players->next = new tile_players_t;
    cli->drone.tile->list_players->next->next = nullptr;
    do_move(&data, cli);
}
