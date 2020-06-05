/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** Created by emilien
*/

#include "sockets/select.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int len(const char *str, char c)
{
    int i = 0;

    while (str[i] != c && str[i] != '\0')
        i++;
    return (i);
}

char *my_lstrcat(char *str, char *src, int nb)
{
    int i = len(str, '\0');
    char *new_str = malloc(sizeof(char) * (len(str, '\0') + (READ_SIZE) + 1));

    if (new_str == NULL)
        return (NULL);
    for (int e = 0; e < len(str, '\0') || e < nb || e < len(src, '\0'); ++e) {
        new_str[e] = e < len(str, '\0') ? str[e] : new_str[e];
        new_str[i] = e < nb ? src[e] : new_str[i];
        i += e < nb ? 1 : 0;
    }
    new_str[i] = '\0';
    for (int j = 0; src[j] != '\0'; ++j)
        src[j] = src[j + nb + 1] ? src[j + nb + 1] : '\0';
    free(str);
    return (new_str);
}

char *gnl(int fd, bool *to_close)
{
    static char buffer[READ_SIZE] = "";
    ssize_t a_r = READ_SIZE;
    char *str = malloc(sizeof(char) * (READ_SIZE));

    if (str == NULL)
        return (NULL);
    str[0] = 0;
    while (len(buffer, '\n') == len(buffer, '\0') &&
        (a_r > 0)) {
        str = my_lstrcat(str, buffer, READ_SIZE);
        a_r = read(fd, buffer, READ_SIZE);
        if ((a_r == 0 || (a_r == 1 && buffer[0] == 4)) && (*to_close = true))
            return (NULL);
    }
    str = my_lstrcat(str, buffer, len(buffer, '\n'));
    if (len(str, '\0') || len(buffer, '\0') || len(str, '\0') < a_r)
        return (str);
    free(str);
    return (NULL);
}