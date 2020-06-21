/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** Created by emilien
*/

#include "tests.h"
#include <gtest/gtest.h>
#include <fcntl.h>

TEST(read_socket, read_socket)
{
    data_server_t data;
    int fd = open("Makefile", O_RDONLY);

    std::cout << "fd:" << fd << std::endl;
    if (fd < 0)
        return;
    memset(&data, 0, sizeof(data_server_t));
    data.params.egg_r_c = new unsigned short[5]{0, 0, 0, 0, 0};
    FD_SET(fd, &data.fdset_read);
    add_client_to_list(&data, fd);
    add_client_to_list(&data, fd);
    client_validation(&data, data.l_waiting.first, fd);
    read_socket(&data);
    EXPECT_NE(data.l_waiting.first->cmd_queue, nullptr);
    EXPECT_EQ(std::string(data.l_connected.first->cmd_queue->command), "##");
}