/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** Created by emilien
*/

#include "tests.h"
#include <gtest/gtest.h>

static void test_get_max_fd(data_server_t *data)
{
    setup_fdset(data);
    EXPECT_EQ(select_fd(data), true);
}

TEST(write_socket, write_socket)
{
    data_server_t data = {0};
    std::string out[2];

    FD_SET(1, &data.fdset_write);
    FD_SET(2, &data.fdset_write);
    add_client_to_list(&data, 1);
    add_client_to_list(&data, 2);
    client_validation(&data, data.l_waiting.first, 1);
    test_get_max_fd(&data);
    client_validation(&data, data.l_waiting.first, 2);
    add_to_write_list(data.l_connected.first, strdup("test1"));
    add_to_write_list(data.l_connected.last, strdup("test2"));
    test_get_max_fd(&data);
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();
    write_socket(&data);
    out[0] = testing::internal::GetCapturedStdout();
    out[1] = testing::internal::GetCapturedStderr();
    EXPECT_EQ(out[0], "test1");
    EXPECT_EQ(out[1], "test2");
}