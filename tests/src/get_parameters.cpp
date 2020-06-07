/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** Created by emilien
*/

#include <gtest/gtest.h>
#include "tests.h"

TEST(get_parameters, classic_test)
{
    char *params[18] = {(char *)"-p", (char *)"4242", (char *)"-x",
        (char *)"1", (char *)"-y", (char *)"3", (char *)"-n", (char *)"Team1",
        (char *)"Team2", (char *)"Team3", (char *)"Team4", (char *)"Team5",
        (char *)"Team6", (char *)"-c", (char *)"12", (char *)"-f",
        (char *)"400", nullptr};
    data_server_t data = get_parameters(18, static_cast<char **>(params));

    EXPECT_EQ(data.port, 4242);
    EXPECT_EQ(data.width, 1);
    EXPECT_EQ(data.height, 3);
    EXPECT_EQ(data.freq, 400);
    EXPECT_EQ(data.team_nb, 6);
    EXPECT_EQ(data.valid_params, true);
}

TEST(get_parameters, no_teams)
{
    char *params[12] = {(char *)"-p", (char *)"4242", (char *)"-x",
        (char *)"1", (char *)"-y", (char *)"3", (char *)"-n", (char *)"-c",
        (char *)"12", (char *)"-f", (char *)"400", nullptr};
    data_server_t data = get_parameters(12, static_cast<char **>(params));

    EXPECT_EQ(data.team_nb, 0);
    EXPECT_EQ(data.valid_params, false);
}

TEST(get_parameters, no_params_after_team)
{
    char *params[12] = {(char *)"-p", (char *)"4242", (char *)"-x",
        (char *)"1", (char *)"-y", (char *)"3", (char *)"-c",
        (char *)"12", (char *)"-f", (char *)"400", (char *)"-n", nullptr};
    data_server_t data = get_parameters(12, static_cast<char **>(params));

    EXPECT_EQ(data.team_nb, 0);
    EXPECT_EQ(data.valid_params, false);
}

TEST(get_parameters, p_wrong_flag)
{
    char *params[18] = {(char *)"-p", (char *)"4a42", (char *)"-x",
        (char *)"1", (char *)"-y", (char *)"3", (char *)"-n", (char *)"Team1",
        (char *)"Team2", (char *)"Team3", (char *)"Team4", (char *)"Team5",
        (char *)"Team6", (char *)"-c", (char *)"12", (char *)"-f",
        (char *)"400", nullptr};
    data_server_t data = get_parameters(18, static_cast<char **>(params));

    EXPECT_EQ(data.port, 0);
    EXPECT_EQ(data.valid_params, false);
}