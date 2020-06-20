/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** Created by emilien
*/

#include "server.h"

static void calc_food_time(data_server_t *d, struct timeval tv, client_t *cli)
{
    double time = (double)126 / d->params.freq;
    int seconds = (int)time;
    double microseconds = ((time - (int)time) * 1000000);

    cli->tv_food.tv_sec = tv.tv_sec;
    cli->tv_food.tv_usec = tv.tv_usec;
    cli->tv_food.tv_usec += microseconds;
    if (cli->tv_food.tv_usec > 1000000)
        seconds += (int)(microseconds / 1000000);
    cli->tv_food.tv_sec += seconds;
}

void end_client_validation(data_server_t *data, client_t *cli, char t_nb[62])
{
    add_to_write_list(cli, t_nb);
    new_client_to_ww_list(cli, &data->cli_wait);
    spawn_player(data, cli);
    calc_food_time(data, data->tv, cli);
}

void check_food(data_server_t *data, client_t *cli)
{
    if (cli->drone.inventory[FOOD] > 0) {
        --cli->drone.inventory[FOOD];
        //move_to_end_of_the_list
    } else {
        add_to_write_list(cli, "dead\n");
        cli->to_close = true;
    }
}

void update_food(data_server_t *data)
{
    struct timeval tv_server = data->tv;
    client_t *cli = data->l_connected.first;

    if (!cli)
        return;
    if ((cli->tv_food.tv_sec == tv_server.tv_sec &&
        cli->tv_food.tv_usec < tv_server.tv_usec) ||
        (cli->tv_food.tv_sec < tv_server.tv_sec)) {
        check_food(data, cli);
        return;
        update_food(data);
    } else {
        return;
    }
}