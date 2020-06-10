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

    setup_timer(&data);
    timer_1 = data.timer;
    usleep(2000);
    timer(&data);
    timer_2 = data.timer;
    std::cout << timer_1 << " && " << timer_2 << std::endl;
    EXPECT_EQ(timer_1 < timer_2, true);
}