/*
** EPITECH PROJECT, 2020
** server
** File description:
** Created by emilien
*/

#include "server.h"
#include "map/setup_map.h"
#include "utils/parameters.h"
#include "utils/close_server.h"
#include "sockets/control_socket.h"
#include <stdio.h>

int usage(int return_val, char *av)
{
    printf("USAGE %s: -p port -x width -y height -n name1 name2 ... "
            "-c clientsNb -f freq\n"
            "\tport\tis the port number\n"
            "\twidth\tis the width of the world\n"
            "\theight\tis the height of the world\n"
            "\tnameX\tis the name of the Team X\n"
            "\tclientsNb\tis the number of authorized clients per team\n"
            "\tfreq\tis the reciprocal of time unit for execution of actions"
            , av);
    return (return_val);
}

int main(int ac, char **av)
{
    data_server_t data = get_parameters(ac, av);

    if (data.valid_params == false)
        return (usage(84, av[0]));
    if (setup_map(&data) == 84)
        return (84);
    if (setup_socket(&data) == 84)
        return (84);
    close_server(data);
    return (0);
}