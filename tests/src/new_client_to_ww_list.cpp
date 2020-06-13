/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** Created by emilien
*/

#include "tests.h"
#include <gtest/gtest.h>

TEST(new_client_to_ww_list, new_list)
{
    list_actions_t *actions = nullptr;
    auto *cli1 = new client_t;
    auto *cli2 = new client_t;
    auto *cli3 = new client_t;

    new_client_to_ww_list(cli1, &actions);
    new_client_to_ww_list(cli2, &actions);
    new_client_to_ww_list(cli3, &actions);
    EXPECT_EQ(actions->cli, cli1);
    EXPECT_EQ(actions->next->cli, cli2);
    EXPECT_EQ(actions->next->next->cli, cli3);
}

TEST(new_client_to_ww_list, error_check)
{
    list_actions_t *actions = nullptr;

    new_client_to_ww_list(nullptr, &actions);
    EXPECT_EQ(actions, nullptr);
}