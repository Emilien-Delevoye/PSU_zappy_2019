/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** Created by emilien
*/

#include "tests.h"
#include <gtest/gtest.h>

TEST(close_clients, remove_a_client)
{
    data_server_t data;

    memset(&data, 0, sizeof(data_server_t));
    add_client_to_list(&data, 0);
    add_client_to_list(&data, 0);
    add_client_to_list(&data, 0);
    add_client_to_list(&data, 0);
    add_client_to_list(&data, 0);
    remove_a_client(&data, data.l_waiting.first->next);
    remove_a_client(&data, data.l_waiting.last->prev);
    remove_a_client(&data, data.l_waiting.first);
    remove_a_client(&data, data.l_waiting.last);
    remove_a_client(&data, data.l_waiting.first);
}

TEST(close_clients, remove_a_cli_co)
{
    data_server_t data;

    memset(&data, 0, sizeof(data_server_t));
    for (int a = 0; a < 5; ++a)
        add_client_to_list(&data, 0);
    for (int a = 0; a < 5; ++a)
        client_validation(&data, data.l_waiting.first, 0);
    remove_a_client_connected(&data, data.l_connected.first->next);
    remove_a_client_connected(&data, data.l_connected.last->prev);
    remove_a_client_connected(&data, data.l_connected.first);
    remove_a_client_connected(&data, data.l_connected.last);
    remove_a_client_connected(&data, data.l_connected.first);
}

TEST(close_clients, close_clients)
{
    data_server_t data;

    memset(&data, 0, sizeof(data_server_t));
    add_client_to_list(&data, 0);
    add_client_to_list(&data, 0);
    add_client_to_list(&data, 0);
    add_client_to_list(&data, 0);
    add_client_to_list(&data, 0);
    data.l_waiting.first->cmd_queue = new command_queue_t;
    data.l_waiting.first->cmd_queue->command = strdup("pouet test pouet");
    data.l_waiting.first->cmd_queue->next = nullptr;
    for (client_t *cur = data.l_waiting.first; cur; cur = cur->next)
        cur->to_close = true;
    for (int a = 0; a < 2; ++a)
        client_validation(&data, data.l_waiting.first, 0);
    close_clients(&data);
    EXPECT_EQ(data.l_connected.first, nullptr);
    EXPECT_EQ(data.l_connected.last, nullptr);
    EXPECT_EQ(data.l_waiting.first, nullptr);
    EXPECT_EQ(data.l_waiting.last, nullptr);
}