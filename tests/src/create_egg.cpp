/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** Created by emilien
*/

#include <gtest/gtest.h>
#include "tests.h"

data_server_t *create_data_server()
{
    auto *data = new data_server_t;

    memset(data, 0, sizeof(data_server_t));
    add_client_to_list(data, 0);
    data->l_waiting.first->drone.tile = new struct map_s;
    data->l_waiting.first->drone.tile->coord[0] = 0;
    data->l_waiting.first->drone.tile->coord[1] = 0;
    return (data);
}

TEST(create_egg, classic_test)
{
    data_server_t *data = create_data_server();

    create_egg(data, data->l_waiting.first);
    create_egg(data, data->l_waiting.first);
    EXPECT_NE(data->egg_waiting, nullptr);
    EXPECT_NE(data->egg_waiting->next, nullptr);
}