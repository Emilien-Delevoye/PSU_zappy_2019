/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** tests for bct_command
*/

#include <gtest/gtest.h>
#include "tests.h"

TEST(bct_command, wrong_arg)
{
    char *arg[2] = {(char *)"useless", NULL};
    data_server_t data;
    client_t cli;

    bct_command(&cli, &data, static_cast<char **>(arg));
}

TEST(bct_command, other_wrong_arg)
{
    char *arg[3] = {(char *)"useless", (char *)"useless", NULL};
    data_server_t data;
    client_t cli;

    bct_command(&cli, &data, static_cast<char **>(arg));
}

TEST(bct_command, good_arg)
{
    char *arg[4] = {(char *)"useless", (char *)"1", (char *)"2", NULL};
    data_server_t data;

    data.l_graphical.first->list_msg = NULL;
    data.params.width = 10;
    data.params.height = 10;
    setup_map(&data);
    data.bottom_left->right->right->top->items[FOOD] = 0;
    data.bottom_left->right->right->top->items[LINEMATE] = 0;
    data.bottom_left->right->right->top->items[DERAUMERE] = 0;
    data.bottom_left->right->right->top->items[SIBUR] = 0;
    data.bottom_left->right->right->top->items[MENDIANE] = 0;
    data.bottom_left->right->right->top->items[PHIRAS] = 0;
    data.bottom_left->right->right->top->items[THYSTAME] = 0;
    bct_command(data.l_graphical.first, &data, static_cast<char **>(arg));
    EXPECT_STREQ(data.l_graphical.first->list_msg->to_write, "bct 2 1 0 0 0 0 0 0 0\n");
    free_map(data);
}