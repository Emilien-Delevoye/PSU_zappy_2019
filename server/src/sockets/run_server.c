/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** Created by emilien
*/

#include "sockets/accept_connections.h"
#include "sockets/run_server.h"
#include "sockets/select.h"
#include "utils/timer.h"
#include <signal.h>
#include <unistd.h>

static int memory_running(int new_val)
{
    static int run = 0;

    if (new_val == 1)
        run = 1;
    else if (new_val == 42)
        return (run);
    return (0);
}

static void sig_handler(int signal)
{
    if (signal == SIGINT)
        memory_running(1);
}

static int setup_sigcatch(void)
{
    struct sigaction sig_act = {0};

    sig_act.sa_handler = sig_handler;
    signal(SIGPIPE, SIG_IGN);
    return (sigaction(SIGINT, &sig_act, NULL));
}

static bool server_running(void)
{
    if (memory_running(42) == 1)
        return (false);
    return (true);
}

int run_server(data_server_t *data)
{
    if (setup_sigcatch() < 0)
        return (84);
    setup_timer(data);
    while (server_running()) {
        setup_fdset(data);
        if (!select_fd(data))
            return (0);
        accept_connections(data);
        read_socket(data);
        close_clients(data);
        timer(data);
    }
    return (0);
}