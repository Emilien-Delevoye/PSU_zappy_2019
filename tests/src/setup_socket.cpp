/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** Created by emilien
*/

#include "tests.h"
#include <gtest/gtest.h>

TEST(setup_socket, setup_socket_error)
{
    data_server_t data;

    memset(&data, 0, sizeof(data_server_t));
    data.params.port = -1;
    EXPECT_EQ(setup_socket(&data), 84);
}

TEST(setup_socket, setup_socket)
{
    data_server_t data;

    memset(&data, 0, sizeof(data_server_t));
    data.params.port = 9942;
    EXPECT_EQ(setup_socket(&data), 0);
}