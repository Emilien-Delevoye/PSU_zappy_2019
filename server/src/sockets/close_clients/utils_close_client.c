/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** Created by emilien
*/

#include "server.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static void remove_middle_element(client_t *cli)
{
    cli->prev->next = cli->next;
    cli->next->prev = cli->prev;
    printf("User %d disconnected\n", cli->fd);
    close(cli->fd);
    free(cli);
}

static void remove_last_element(data_server_t *data, client_t *cli)
{
    cli->prev->next = NULL;
    data->l_cli.last = cli->prev;
    printf("User %d disconnected\n", cli->fd);
    close(cli->fd);
    free(cli);
}

static void remove_first_element(data_server_t *data, client_t *cli)
{
    cli->next->prev = NULL;
    data->l_cli.first = cli->next;
    printf("User %d disconnected\n", cli->fd);
    close(cli->fd);
    free(cli);
}

static void remove_alone_element(data_server_t *data, client_t *cli)
{
    data->l_cli.first = NULL;
    data->l_cli.last = NULL;
    printf("User %d disconnected\n", cli->fd);
    close(cli->fd);
    free(cli);
}

void remove_a_client(data_server_t *data, client_t *cli)
{
    if (cli->next && cli->prev) {
        remove_middle_element(cli);
        return;
    }
    if (!cli->next && cli->prev) {
        remove_last_element(data, cli);
        return;
    }
    if (cli->next && !cli->prev) {
        remove_first_element(data, cli);
        return;
    }
    if (!cli->next && !cli->prev) {
        remove_alone_element(data, cli);
        return;
    }
}
