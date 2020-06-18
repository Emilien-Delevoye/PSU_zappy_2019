/*
** EPITECH PROJECT, 2019
** str_to
** File description:
** word_array
*/

#include <stdlib.h>
#include <string.h>

int spaces(const char *str)
{
    int counter_spaces = 0;

    if (!str)
        return counter_spaces;
    for (int i = 0; str[i + 1] != '\0'; i++) {
        if ((str[i] == ' ' && (str[i + 1] != ' ' && str[i + 1] != '\0' &&
        str[i + 1] != '\t')) || (str[i] == '\t' &&
        (str[i + 1] != ' ' && str[i + 1] != '\0' && str[i + 1] != '\t')))
            counter_spaces++;
    }
    return (counter_spaces);
}

char **check_null()
{
    char **all = malloc(sizeof(char *) * 2);

    if (all == NULL)
        return NULL;
    all[0] = strdup("\0");
    all[1] = NULL;
    return (all);
}

char *get_dup(const char *str, int *i, char *dup)
{
    int counter_malloc = 0;

    for (int j = *i; str[j] != ' ' && str[j] != '\0' && str[j] != '\t'; j++)
        counter_malloc++;
    dup = malloc(sizeof(char) * counter_malloc + 1);
    if (dup == NULL)
        return NULL;
    for (int j = 0; str[*i] != ' ' && str[*i] != '\0' &&
    str[*i] != '\t'; j++) {
        dup[j] = str[*i];
        *i += 1;
    }
    if (str[*i] != ' ' && str[*i] != '\t')
        *i -= 1;
    dup[counter_malloc] = '\0';
    return (dup);
}

char **my_str_to_word_array(char *str)
{
    int counter_str = 0;
    char *dup = NULL;
    char **all = malloc(sizeof(char *) * (spaces(str) + 2));

    if (all == NULL)
        return NULL;
    if (str && spaces(str) == 0 &&
        (str[0] == ' ' || str[0] == '\0' || str[0] == '\t'))
        return (check_null());
    for (int i = 0; str && str[i] != '\0'; i++) {
        dup = get_dup(str, &i, dup);
        if (dup && dup[0] != '\0') {
            all[counter_str] = dup;
            counter_str++;
        }
    }
    all[counter_str] = NULL;
    return (all);
}