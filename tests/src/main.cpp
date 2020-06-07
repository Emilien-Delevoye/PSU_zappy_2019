/*
** EPITECH PROJECT, 2020
** server_tests
** File description:
** Created by emilien
*/

#include <gtest/gtest.h>

int main(int ac, char **av)
{
    ::testing::InitGoogleTest(&ac, av);
    return (RUN_ALL_TESTS());
}