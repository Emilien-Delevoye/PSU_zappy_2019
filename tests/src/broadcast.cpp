/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** tests for broadcast
*/

#include <gtest/gtest.h>
#include "tests.h"

void test_right(data_server_t data)
{
    data.l_connected.first->next->drone.tile = data.bottom_left->right;
    broadcast(&data);
    EXPECT_STREQ(data.l_connected.first->list_msg->to_write, "ok\n");
    EXPECT_STREQ(data.l_connected.first->next->list_msg->to_write, "message 1, test\n");
    data.l_connected.first->next->drone.tile = data.bottom_left->right->top;
    broadcast(&data);
    EXPECT_STREQ(data.l_connected.first->list_msg->to_write, "ok\n");
    EXPECT_STREQ(data.l_connected.first->next->list_msg->to_write, "message 1, test\n");
    data.l_connected.first->next->drone.tile = data.bottom_left->right->bottom;
    broadcast(&data);
    EXPECT_STREQ(data.l_connected.first->list_msg->to_write, "ok\n");
    EXPECT_STREQ(data.l_connected.first->next->list_msg->to_write, "message 1, test\n");
    data.l_connected.first->next->drone.tile = data.bottom_left->top;
    broadcast(&data);
    EXPECT_STREQ(data.l_connected.first->list_msg->to_write, "ok\n");
    EXPECT_STREQ(data.l_connected.first->next->list_msg->to_write, "message 1, test\n");
    data.l_connected.first->next->drone.tile = data.bottom_left->bottom;
    broadcast(&data);
    EXPECT_STREQ(data.l_connected.first->list_msg->to_write, "ok\n");
    EXPECT_STREQ(data.l_connected.first->next->list_msg->to_write, "message 1, test\n");
}

void test_left(data_server_t data)
{
    data.l_connected.first->next->drone.tile = data.bottom_left->left;
    broadcast(&data);
    EXPECT_STREQ(data.l_connected.first->list_msg->to_write, "ok\n");
    EXPECT_STREQ(data.l_connected.first->next->list_msg->to_write, "message 1, test\n");
    data.l_connected.first->next->drone.tile = data.bottom_left->left->top;
    broadcast(&data);
    EXPECT_STREQ(data.l_connected.first->list_msg->to_write, "ok\n");
    EXPECT_STREQ(data.l_connected.first->next->list_msg->to_write, "message 1, test\n");
    data.l_connected.first->next->drone.tile = data.bottom_left->left->bottom;
    broadcast(&data);
    EXPECT_STREQ(data.l_connected.first->list_msg->to_write, "ok\n");
    EXPECT_STREQ(data.l_connected.first->next->list_msg->to_write, "message 1, test\n");
    test_right(data);
}

TEST(broadcast, test_arg)
{
    data_server_t data;
    memset(&data, 0, sizeof(data_server_t));
    data.l_graphical.first = new client_t;
    data.l_graphical.last = data.l_graphical.first;
    memset(data.l_graphical.first, 0, sizeof(client_t));
    data.l_connected.first = new client_t;
    data.l_connected.last = data.l_connected.first;
    memset(data.l_connected.first, 0, sizeof(client_t));
    data.l_connected.first->next = new client_t;
    data.l_connected.last = data.l_connected.first->next;
    memset(data.l_connected.last, 0, sizeof(client_t));
    data.cli_work = new list_actions_t;
    memset(data.cli_work, 0, sizeof(list_actions_t));
    data.cli_work->cli = data.l_connected.first;
    data.cli_work->cmd_str = (char *)"Broadcast test";
    data.l_connected.first->drone.id = 0;
    data.l_connected.first->next->drone.id = 1;
    data.params.height = 10;
    data.params.width = 10;

    setup_map(&data);
    data.l_connected.first->drone.tile = data.bottom_left;
    test_left(data);
}