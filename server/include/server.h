/*
** EPITECH PROJECT, 2020
** server
** File description:
** Created by emilien
*/

#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

#include <stdbool.h>
#include <sys/select.h>
#include <stdio.h>

#define WIDTH 1
#define HEIGHT 0
#define NORTH 1
#define EAST 2
#define SOUTH 3
#define WEST 4

enum items_type {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME
};

typedef struct client_s client_t;

typedef struct tile_players_s {
    client_t *cli;
    struct tile_players_s *next;
} tile_players_t;

typedef struct map_s {
    unsigned int coord[2];
    struct map_s *right;
    struct map_s *left;
    struct map_s *top;
    struct map_s *bottom;
    tile_players_t *list_players;
    unsigned int items[7];
} map_t;

typedef struct write_cli_s {
    char *to_write;
    struct write_cli_s *next;
} write_cli_t;

typedef struct command_queue_s {
    char *command;
    struct command_queue_s *next;
} command_queue_t;

typedef struct drone_s {
    unsigned int inventory[7];
    int lvl;
    int orientation;
    int id;
    map_t *tile;
} drone_t;

typedef struct client_s {
    int fd;
    bool to_close;
    char *buffer;
    unsigned short team_id;
    command_queue_t *cmd_queue;
    write_cli_t *list_msg;
    drone_t drone;
    bool dead;
    struct timeval tv_food;
    struct client_s *prev;
    struct client_s *next;
} client_t;

struct list_client_s {
    client_t *first;
    client_t *last;
};

typedef struct list_actions_s {
    client_t *cli;
    short cmd_nb;
    char *cmd_str;
    struct timeval tv;
    struct list_actions_s *next;
} list_actions_t;

typedef struct param_s {
    int port;
    int width;
    int height;
    char **team_names;
    unsigned int team_nb;
    unsigned short client_nb;
    unsigned int freq;
    unsigned short *r_cli;
    unsigned short *egg_r_c;
    unsigned short *win_cli;
    bool valid_params;
} param_t;

typedef struct list_egg_s {
    int egg_id;
    struct timeval tv;
    unsigned short team_id;
    int coord[2];
    struct list_egg_s *next;
} list_egg_t;

typedef struct data_server_s {
    //Server settings
    param_t params;

    //Server socket
    int fd;
    fd_set fdset_read;
    fd_set fdset_write;

    //Clients structures
    struct list_client_s l_waiting;
    struct list_client_s l_connected;
    struct list_client_s l_graphical;

    //Egg structures
    list_egg_t *egg_waiting;
    list_egg_t *hatch_eggs;

    //Map pointer :
    map_t *bottom_left;

    //Working clients :
    list_actions_t *cli_work;
    list_actions_t *cli_wait;

    //Timer structures
    struct timeval tv;
    struct tm *tm;
} data_server_t;

struct cmd_ai_s {
    const char *c;
    int duration;
};

#define READ_SIZE 2048

bool add_to_client(client_t *, char *);
bool select_fd(data_server_t *);
void setup_fdset(data_server_t *);
void read_socket(data_server_t *);
void write_socket(data_server_t *);
void close_clients(data_server_t *);
void remove_a_client(data_server_t *, client_t *);
void remove_a_client_connected(data_server_t *, client_t *);
void extract_command(client_t *);
void valid_client(data_server_t *, client_t *);
void remove_first_cmd_queue(client_t *);
void add_to_write_list(client_t *cli, char *buffer);
void ai_interaction(data_server_t *data);
void read_new_cmd(data_server_t *data, client_t *cl, struct timeval cu_time);
void move_wait_to_work_list(data_server_t *data, client_t *cli,
    struct timeval cu_time, short cmd_nb);
void new_client_to_ww_list(client_t *cli, list_actions_t **cli_work);
void loop_tmp_check_every_buffer(data_server_t *data);
void close_in_cli_ww_list(data_server_t *data, client_t *cli);
void move_to_wait_list(data_server_t *data);
void forward(data_server_t *data);
void right(data_server_t *data);
void left(data_server_t *data);
void broadcast(data_server_t *data);
void spawn_player(data_server_t *data, client_t *cli, const int c[2]);
void inventory(data_server_t *data);
void look(data_server_t *data);
void connect_nbr(data_server_t *data);
void eject(data_server_t *data);
void fork_cmd(data_server_t *data);
void take(data_server_t *data);
void set(data_server_t *data);
void incantation_before(client_t *cli, data_server_t *data);
void incantation_after(data_server_t *data);
void move_to_other_tile(map_t *dest, tile_players_t *cu_l);
void end_client_validation(data_server_t *data, client_t *cli, char t_nb[62]);
void update_food(data_server_t *data);
void create_egg(data_server_t *data, client_t *cli);
int init_id(void);
void update_egg(data_server_t *data);
void egg_to_player(data_server_t *data, client_t *cli);
void calc_food_time(data_server_t *d, struct timeval tv, client_t *cli);
map_t *get_good_tile(map_t *cur, data_server_t *data);

#define get_direction1(c, o) \
    (o <= 2 ? (o == 1 ? c->top : c->right) : (o == 3 ? c->bottom : c->left))
#define get_direction2(c, o) \
    (o <= 2 ? (o == 1 ? c->left : c->top) : (o == 3 ? c->right : c->bottom))
#define get_direction3(c, o) \
    (o <= 2 ? (o == 1 ? c->right : c->bottom) : (o == 3 ? c->left : c->top))

#endif //SERVER_SERVER_H
