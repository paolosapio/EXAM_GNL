#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1000
#endif

int len_until_nl_or_end(char *str, bool stop_at_nl)
{
    int i = 0;
    if (!str)
        return (0);
    while (str[i])
    {
        if (stop_at_nl && str[i] == '\n')
        {
            i++;
            break;
        }
        i++;
    }
    return (i);
}

char *join_str(char *str1, char *str2)
{
    int len1 = len_until_nl_or_end(str1, false);
    int len2 = len_until_nl_or_end(str2, false);
    char *joined = malloc(len1 + len2 + 1);
    if (!joined)
        return (NULL);
    int i = 0, j = 0;
    while (str1 && str1[i])
    {
        joined[i] = str1[i];
        i++;
    }
    while (str2 && str2[j])
    {
        joined[i + j] = str2[j];
        j++;
    }
    joined[i + j] = '\0';
    return (joined);
}

char *split_store(char **original_store)
{
    if (!original_store || !*original_store)
        return (NULL);
    char *store = *original_store;
    int line_len = len_until_nl_or_end(store, true);
    int rest_len = len_until_nl_or_end(store, false) - line_len;

    char *line = malloc(line_len + 1);
    char *new_store = malloc(rest_len + 1);
    if (!line || !new_store)
    {
        free(line);
        free(new_store);
        return (NULL);
    }

    int i = 0;
    while (i < line_len)
    {
        line[i] = store[i];
        i++;
    }
    line[i] = '\0';

    int j = 0;
    while (store[i + j])
    {
        new_store[j] = store[i + j];
        j++;
    }
    new_store[j] = '\0';

    free(store);
    *original_store = new_store;
    return (line);
}

bool contains_nl(char *str)
{
    int i = 0;
    if (!str)
        return (false);
    while (str[i])
    {
        if (str[i] == '\n')
            return (true);
        i++;
    }
    return (false);
}

char *get_next_line(int fd)
{
    static char *store = NULL;
    char *buffer;
    char *line;
    char *tmp;
    int bytes;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    buffer = malloc(BUFFER_SIZE + 1);
    if (!buffer)
        return (NULL);

    while (!contains_nl(store))
    {
        bytes = read(fd, buffer, BUFFER_SIZE);
        if (bytes <= 0)
            break;
        buffer[bytes] = '\0';
        tmp = store;
        store = join_str(tmp, buffer);
        free(tmp);
        if (!store)
            break;
    }
    free(buffer);
    if (!store || store[0] == '\0')
    {
        free(store);
        store = NULL;
        return (NULL);
    }
    line = split_store(&store);
    return (line);
}
