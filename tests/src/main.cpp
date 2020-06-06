/*
** EPITECH PROJECT, 2020
** server_tests
** File description:
** Created by emilien
*/

#include <gtest/gtest.h>

#if defined (__cplusplus)
extern "C" {
#endif
    #include "server.h"
    #include "utils/write_list.h"
#if defined (__cplusplus)
}
#endif

TEST (test1, pouet)
{
    auto pouet = new client_t;

    pouet->list_msg = nullptr;
    add_to_write_list(pouet, (char *)std::string("test").c_str());
    EXPECT_EQ(0, 0);
}

int main(int ac, char **av)
{
    ::testing::InitGoogleTest(&ac, av);
    return (RUN_ALL_TESTS());
}