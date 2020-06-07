/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** Created by emilien
*/

#include "server.h"
#include "sockets/control_socket.h"
#include <sys/socket.h>
#include <netinet/in.h>

int setup_socket(data_server_t *data)
{
    struct sockaddr_in serv_addr = {0};
    int opt = -1;

    data->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (data->fd < 0)
        return (84);
    if (setsockopt(data->fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
        return (84);
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(data->port);
    serv_addr.sin_family = AF_INET;
    if (bind(data->fd, (sockaddr_t *)&serv_addr, sizeof(sockaddr_t)) < 0)
        return (84);
    if (listen(data->fd, 10) < 0)
        return (84);
    return (0);
}