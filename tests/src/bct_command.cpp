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
    client_t cli;

    cli.list_msg = NULL;
    data.params.width = 10;
    data.params.height = 10;
    setup_map(&data);
    data.bottom_left->right->top->top->items[0] = FOOD;
    data.bottom_left->right->top->top->items[1] = FOOD;
    data.bottom_left->right->top->top->items[2] = FOOD;
    data.bottom_left->right->top->top->items[3] = FOOD;
    data.bottom_left->right->top->top->items[4] = FOOD;
    data.bottom_left->right->top->top->items[5] = FOOD;
    data.bottom_left->right->top->top->items[6] = FOOD;
    bct_command(&cli, &data, static_cast<char **>(arg));
    EXPECT_STREQ(cli.list_msg->to_write, "bct 1 2 0 0 0 0 0 0 0\n");
    free_map(data);
}