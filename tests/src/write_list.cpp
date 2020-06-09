/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** Created by emilien
*/

#include "tests.h"
#include <gtest/gtest.h>

TEST(write_list, add_to_write_list)
{
    client_t cli;
    std::string input_test("Google Test");

    memset(&cli, 0, sizeof(client_t));
    add_to_write_list(&cli, strdup(input_test.c_str()));
    add_to_write_list(&cli, strdup(input_test.c_str()));
    add_to_write_list(&cli, strdup(input_test.c_str()));
    EXPECT_EQ(std::string(cli.list_msg->to_write), input_test);
    cli.list_msg = cli.list_msg->next;
    EXPECT_EQ(std::string(cli.list_msg->to_write), input_test);
    cli.list_msg = cli.list_msg->next;
    EXPECT_EQ(std::string(cli.list_msg->to_write), input_test);
}