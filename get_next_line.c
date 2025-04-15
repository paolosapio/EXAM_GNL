#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
/*
En este gnl os quiero contar una historia que ha cambiado la vida de muchas personas y ha marcado 
un pueblo que desesperado ha sabido hacer valer su creatividad en escapando a otro pais evitando 
las miliaciones del nazismo durante la segunda guerra mundial:
los immigrantes del sur de italia en NY a principios de la década de 1900.
espero os guste la analogia aplicada en este maravilloso propyecto
https://es.wikipedia.org/wiki/Inmigraci%C3%B3n_italiana_en_Estados_Unidos
*/

#define ASIENTOS_BARCO  42
#define SICILIA_VACIA   0

typedef int t_fd;

#define FAMILIA_COMPLETA '\n'
// #define 

// hacer funcion que busque un salto de linea
int len_0_n(char *str, bool)
{
    int i;

    i = 0;
    while(str[i])
    {
        if (str[i] == '\n')
            return (i);
        i++;
    }
}
// hacer un join
// hacer un len
// split index string en dos

char *get_next_line(t_fd sicily)
{
    char        *boat;
    static char *ellis_island;
    char        *trip_to_ny;
    int         captan_report;

    if (sicily < 0)
        return (NULL);
    boat = malloc(ASIENTOS_BARCO + 1);
    while(ellis_island == FAMILIA_COMPLETA)
    {
        captan_report = read(sicily, boat, ASIENTOS_BARCO);
        ellis_island = /*join(entre ellis_island y boat*/;
        if(captan_report == 0) //TODO GESTIONAR ERRORES DEL READ
            break ;
    }

    return (trip_to_ny);

}

#include <fcntl.h>

int main(void)
{
    int fd;
    char *line;
    
    fd = open("testo.txt", O_RDONLY);
    line = get_next_line(fd);
    while(line)
    {
        printf("%s", line);
        line = get_next_line(fd);
    }
    printf("%s", get_next_line(fd));
    close(fd);
    return (0);
}