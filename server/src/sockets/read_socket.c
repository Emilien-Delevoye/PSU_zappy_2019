/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** Created by emilien
*/

#include "utils/write_list.h"
#include "server.h"
#include "sockets/select.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void add_to_end_list(command_queue_t *new, command_queue_t *cur, short counter)
{
    while (cur->next) {
        cur = cur->next;
        ++counter;
    }
    if (counter > 10) {
        free(new);
        return;
    }
    cur->next = new;
}

static void add_to_client(client_t *cli, char *buffer)
{
    command_queue_t *new = malloc(sizeof(command_queue_t));
    command_queue_t *cur = cli->cmd_queue;
    short counter = 0;

    if (!new)
        return;
    new->next = NULL;
    new->command = strdup(buffer);
    if (!cli->cmd_queue)
        cli->cmd_queue = new;
    else
        add_to_end_list(new, cur, counter);
}

char *my_strcat(char *origin, const char *to_cat)
{
    size_t len_origin = (origin ? strlen(origin) : 0);
    char *output = malloc(len_origin + strlen(to_cat) + 1);

    if (!output)
        return (NULL);
    if (origin)
        strcpy(output, origin);
    strcpy(output + len_origin, to_cat);
    if (origin)
        free(origin);
    return (output);
}

void read_buffer(client_t *cli)
{
    char tmp_buffer[10] = {0};
    ssize_t len = read(cli->fd, &tmp_buffer, (sizeof(tmp_buffer) - 1));

    while (len == (sizeof(tmp_buffer) - 1)) {
        cli->buffer = my_strcat(cli->buffer, tmp_buffer);
        len = read(cli->fd, &tmp_buffer, (sizeof(tmp_buffer) - 1));
    }
    cli->buffer = my_strcat(cli->buffer, tmp_buffer);
    puts(cli->buffer);
    if (len == 0)
        cli->to_close = true;
}

void read_socket(data_server_t *data)
{
    for (client_t *cli = data->l_cli.first; cli; cli = cli->next)
        if (FD_ISSET(cli->fd, &data->fdset_read))
            read_buffer(cli);
}