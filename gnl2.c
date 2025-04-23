#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE
# endif

//Funciones que necesito:
//  len_n_0
//  check if is a \n in str
//  split family from people
//  JOIN

bool is_new_line(char *store)
{
    int i;

    i = 0;
    while (store[i])
    {
        if (store[i] == '\n')
            return (true);
        i++;
    }
    return (false);
}

char *get_next_line(int fd)
{
    static char *store = NULL;
    char        *buffer;
    char        *return_line;
    int         n_bytes_readed;

    if (fd < 0)
        return (NULL);
    buffer = malloc(BUFFER_SIZE + 1);
    if (!buffer)
        return (NULL);
    while(store && is_new_line(store) == false)
    {
        //si no lo tenemos vamos acumulando caracteres
        n_bytes_readed = read(fd, buffer, BUFFER_SIZE);
        if (n_bytes_readed <= 0)
        {
            if (n_bytes_readed == -1)
            {
                free(buffer);
                free(store);
                store = NULL;
                return (NULL);
            }
            break ;
        }
        buffer[n_bytes_readed] = '\n';
    }
    // encontrado un salto de linea tenemos que devolver la linea
    
    return (NULL);
}

int main(void)
{
    int fd;
    char *line;
    int n_line;

    fd = open("texto.txt", O_RDONLY);
    line = get_next_line(fd);
    while (line != NULL)
    {
        printf("%d  %s", n_line++, line);
        free(line);
        line = get_next_line(fd);
    }
    free(line);
    close(fd);
    return (0);
}
