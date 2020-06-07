/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** Created by emilien
*/

#include <gtest/gtest.h>
#include "tests.h"

void test_map(map_t *cur, int x, int y)
{
    EXPECT_EQ(cur->coord[0], x);
    EXPECT_EQ(cur->coord[1], y);
}

TEST(setup_map, setup_1x1_map)
{
    data_server_t data;
    data.width = 1;
    data.height = 1;
    map_t *cur;

    EXPECT_EQ(setup_map(&data), 0);
    cur = data.bottom_left;
    test_map(cur, 0, 0);
    test_map(cur->top, 0, 0);
    test_map(cur->bottom, 0, 0);
    test_map(cur->right, 0, 0);
    test_map(cur->left, 0, 0);
    free_map(data);
}

TEST(setup_map, setup_10x10_map)
{
    data_server_t data;
    data.width = 10;
    data.height = 10;
    map_t *cur;

    EXPECT_EQ(setup_map(&data), 0);
    cur = data.bottom_left;
    test_map(cur, 0, 0);
    test_map(cur->right, 0, 1);
    test_map(cur->right->right, 0, 2);
    test_map(cur->left, 0, 9);
    test_map(cur->left->left, 0, 8);
    test_map(cur->top, 1, 0);
    test_map(cur->top->top, 2, 0);
    test_map(cur->bottom, 9, 0);
    test_map(cur->bottom->bottom, 8, 0);
    free_map(data);
}

TEST(setup_map, setup_negative_map)
{
    data_server_t data;
    data.width = -1;
    data.height = -1;

    EXPECT_EQ(setup_map(&data), 84);
}