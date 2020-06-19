/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** tests for my_str_to_word_array
*/

#include <gtest/gtest.h>
#include "tests.h"

TEST(str_to_word_array, classic_test)
{
    char **array = my_str_to_word_array((char *)"test\0");

    EXPECT_STREQ(array[0], "test");
    EXPECT_STREQ(array[1], NULL);
    array = my_str_to_word_array((char *)"test1  \t   test    2    \0");
    EXPECT_STREQ(array[0], "test1");
    EXPECT_STREQ(array[1], "test");
    EXPECT_STREQ(array[2], "2");
    EXPECT_STREQ(array[3], NULL);
    array = my_str_to_word_array(NULL);
    EXPECT_STREQ(array[0], NULL);
    array = my_str_to_word_array((char *)"");
    EXPECT_STREQ(array[0], "");
    EXPECT_STREQ(array[1], NULL);
}