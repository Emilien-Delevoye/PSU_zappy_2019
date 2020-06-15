/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** Created by emilien
*/

#include "tests.h"
#include <gtest/gtest.h>

static data_server_t generate_data()
{
    data_server_t data;

    memset(&data, 0, sizeof(data));
    data.params.r_cli = new unsigned short[4];
    data.params.r_cli[0] = 10;
    data.params.r_cli[1] = 10;
    data.params.r_cli[2] = 10;
    data.params.r_cli[2] = -1;
    data.params.team_names = new char*[4];
    data.params.team_names[0] = strdup("Team1");
    data.params.team_names[1] = strdup("Team2");
    data.params.team_names[2] = strdup("Team3");
    data.params.team_names[3] = nullptr;
    add_client_to_list(&data, 1);
    add_client_to_list(&data, 2);
    return (data);
}

static command_queue_t *create_cmd_queue(const std::string& in)
{
    auto *new_queue = new command_queue_t;

    new_queue->command = strdup(in.c_str());
    new_queue->next = nullptr;
    return (new_queue);
}

TEST(valid_clients, client_add)
{
    data_server_t data = generate_data();
    client_t *cli[2];

    cli[0] = data.l_waiting.first;
    cli[1] = data.l_waiting.last;
    EXPECT_EQ(cli[0]->fd, 1);
    EXPECT_EQ(cli[1]->fd, 2);
}

TEST(valid_clients, valid_clients)
{
    data_server_t data = generate_data();
    client_t *cli[2] = {data.l_waiting.first, data.l_waiting.last};

    cli[0]->cmd_queue = create_cmd_queue("Team1");
    cli[1]->cmd_queue = create_cmd_queue("Team2");
    valid_client(&data, cli[0]);
    EXPECT_EQ(cli[0], data.l_connected.first);
    EXPECT_EQ(cli[0], data.l_connected.last);
    EXPECT_EQ(cli[1], data.l_waiting.first);
    EXPECT_EQ(cli[1], data.l_waiting.last);
    EXPECT_EQ(cli[0]->next, nullptr);
    EXPECT_EQ(cli[0]->prev, nullptr);
    EXPECT_EQ(cli[1]->next, nullptr);
    EXPECT_EQ(cli[1]->prev, nullptr);
    valid_client(&data, cli[1]);
    EXPECT_EQ(data.l_waiting.first, nullptr);
    EXPECT_EQ(data.l_waiting.last, nullptr);
    EXPECT_EQ(cli[1], data.l_connected.last);
    EXPECT_EQ(cli[1], data.l_connected.first->next);
    EXPECT_EQ(cli[1], data.l_connected.last->prev->next);
}

TEST(valid_clients, valid_clients_invert)
{
    data_server_t data = generate_data();
    client_t *cli[2] = {data.l_waiting.first, data.l_waiting.last};

    cli[0]->cmd_queue = create_cmd_queue("Team1");
    cli[1]->cmd_queue = create_cmd_queue("Team2");
    valid_client(&data, cli[1]);
    EXPECT_EQ(cli[1], data.l_connected.first);
    EXPECT_EQ(cli[1], data.l_connected.last);
    EXPECT_EQ(cli[0], data.l_waiting.first);
    EXPECT_EQ(cli[0], data.l_waiting.last);
    EXPECT_EQ(cli[1]->next, nullptr);
    EXPECT_EQ(cli[1]->prev, nullptr);
    EXPECT_EQ(cli[0]->next, nullptr);
    EXPECT_EQ(cli[0]->prev, nullptr);
    valid_client(&data, cli[0]);
    EXPECT_EQ(data.l_waiting.first, nullptr);
    EXPECT_EQ(data.l_waiting.last, nullptr);
    EXPECT_EQ(cli[0], data.l_connected.last);
    EXPECT_EQ(cli[0], data.l_connected.first->next);
    EXPECT_EQ(cli[0], data.l_connected.last->prev->next);
}