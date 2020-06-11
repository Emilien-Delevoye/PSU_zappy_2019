/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** Created by emilien
*/

#include "tests.h"
#include <gtest/gtest.h>

TEST(time, time)
{
    data_server_t data;
    long timer_1;
    long timer_2;

    memset(&data, 0, sizeof(data_server_t));
    setup_timer(&data);
    timer_1 = data.tv.tv_usec;
    usleep(2000);
    timer(&data);
    timer_2 = data.tv.tv_usec;
    std::cout << timer_1 << " && " << timer_2 << std::endl;
    EXPECT_EQ(timer_1 < timer_2, true);
}