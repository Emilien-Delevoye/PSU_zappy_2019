/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** Created by emilien
*/

#include "sockets/select.h"
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int len(const char *str, char c)
{
    int i = 0;

    while (str[i] != c && str[i] != '\0')
        ++i;
    return (i);
}

char *m_scat_rb(char *str, char *src, int nb)
{
    strncat(str, src, nb);
    for (int j = 0; src[j] != '\0'; ++j)
        src[j] = src[j + nb + 1] ? src[j + nb + 1] : '\0';
    return (str);
}

char *gnl(int fd, char *str, bool *to_close)
{
    static char buffer[READ_SIZE] = "";
    ssize_t a_r = READ_SIZE;

    if (str == NULL)
        return (NULL);
    str[0] = 0;
    while (len(buffer, '\n') == strlen(buffer) && (a_r > 0)) {
        str = m_scat_rb(str, buffer, READ_SIZE);
        a_r = read(fd, buffer, READ_SIZE);
        if ((a_r == 0 || (a_r == 1 && buffer[0] == 4)) && (*to_close = true))
            return (NULL);
    }
    str = m_scat_rb(str, buffer, len(buffer, '\n'));
    if (strlen(str) || strlen(buffer) || strlen(str) < a_r)
        return (str);
    return (NULL);
}