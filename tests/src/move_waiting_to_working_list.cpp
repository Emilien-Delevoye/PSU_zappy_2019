/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** Created by emilien
*/

#include "tests.h"
#include <gtest/gtest.h>

TEST(move_waiting_to_working_list, classic_test)
{
    data_server_t *data = create_data_server();
    struct timeval tv{};

    data->cli_wait = new list_actions_t;
    memset(data->cli_wait, 0, sizeof(list_actions_t));
    data->cli_wait->cli = data->l_waiting.first;
    data->l_waiting.first->cmd_queue = new command_queue_t;
    data->l_waiting.first->cmd_queue->command = nullptr;
    move_wait_to_work_list(data, data->l_waiting.first, tv, 0);
}