/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** tests for msz_command
*/

#include <gtest/gtest.h>
#include "tests.h"

TEST(msz_command, classic_test)
{
    char *arg[2] = {(char *)"useless", NULL};
    data_server_t data;
    client_t cli;

    data.params.width = 1;
    data.params.height = 2;
    cli.list_msg = NULL;
    msz_command(&cli, &data, static_cast<char **>(arg));
}