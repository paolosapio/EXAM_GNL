/*
En este gnl os quiero contar una historia que ha cambiado la vida de muchas personas y ha marcado 
un pueblo que desesperado ha sabido hacer valer su creatividad en escapando a otro pais evitando 
las miliaciones del nazismo durante la segunda guerra mundial:
los immigrantes del sur de italia en NY a principios de la década de 1900.
Por seguridad los USA querian controlar las familia completas antes de desembarcarlas en NY,
asi que amontonavan los immigrantes en Ellis Island (la actual isla de la estatua de la libertad).
Y solamente si la familia estaba entera le daban derecho a un trabajo
y el visado para desembarcar en NY en busqueda del sueno americano.
Los caracteres son  los familiares el salto de linea o el '/0'
representan el capofamilia que cierra una familia completa para finalmente
desembarcar en NY hacia la liberta y lejos de guerras.

espero os guste la analogia aplicada en este maravilloso propyecto
https://es.wikipedia.org/wiki/Inmigraci%C3%B3n_italiana_en_Estados_Unidos
*/

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>

#define ASIENTOS_BARCO      100
#define SICILIA_VACIA       0
#define FAMILIA_COMPLETA    '\n'
#define NEW_LINE	        1

typedef int t_fd;

int len_0_n(char *str, bool len_nl)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (len_nl && str[i] == '\n')
		{
			return (i + 1);
		}
		i++;
	}
	return (i);
}

char *ft_join(char *s1, char *s2)
{
	char *joined;
	int i;
	int j;

	if (!s1 && !s2)
		return (NULL);
	joined = malloc(len_0_n(s1, 0) + len_0_n(s2, 0) + 1);
	if (!joined)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		joined[i++] = s2[j++];
	}
	joined[i] = '\0';
	return (joined);
}

char    *ft_strchr(const char *s, int c)
{
	int	i;
	if (!s)
		return (NULL);
	if (c == '\0')
		return ((char *)&s[len_0_n((char *)s, 0)]);
	i = 0;	
	while (s && s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}

char	*split_family(char **ellis_island)
{
	char	*family;
	char	*people;
	int len_family = len_0_n(*ellis_island, FAMILIA_COMPLETA) + 1;
	int len_people = len_0_n(*ellis_island, 0) - len_0_n(*ellis_island, FAMILIA_COMPLETA) + 1;
	int i;
	int j;

	family = malloc(len_family + 1);
	people = malloc(len_people + 1);
	i = 0;
	while ((*ellis_island)[i] != '\0')
	{
		family[i] = (*ellis_island)[i];
		printf("test desde split: %s\n", family);
		if ((*ellis_island)[i] == '\n')
		{
			family[i] = (*ellis_island)[i];
			printf("sato linea\n");
			i++;
			break ;
		}
		i++;
	}
	family[i] = '\0';
	printf("test desde split: %s\n", family);
	j = 0;
	while ((*ellis_island)[i] != '\0')
	{
		people[j] = (*ellis_island)[i];
		i++;
		j++;
	}
	family[j] = '\0';
	printf("family is: %s", family);
	printf("people is: %s\n", people);
	return (family);
}

char *get_next_line(t_fd sicily)
{
	char        *boat;
	static char *ellis_island = NULL;
	char        *trip_to_ny;
	int         captan_report;
	char		*aux;

	if (sicily < 0)
		return (NULL);
	if (ellis_island == NULL)
	{
		ellis_island = malloc(1);
		*ellis_island = '\0';
	}
	boat = malloc(ASIENTOS_BARCO + 1);
	while (ft_strchr(ellis_island, '\n') == NULL)
	{
		captan_report = read(sicily, boat, ASIENTOS_BARCO);
		if(captan_report <= 0)
		break ;
		boat[captan_report] = '\0';
		aux = ellis_island;
		printf("ellis es antes join: %s\n", ellis_island);
		ellis_island = ft_join(ellis_island, boat);
		printf("ellis es despues join: %s\n", ellis_island);
		free(aux);
		if (ft_strchr(ellis_island, '\n') != NULL)
		{
			trip_to_ny = split_family(&ellis_island);
			// free(family_and_people[0]);
			// free(family_and_people[1]);
			// free(family_and_people);
			return (trip_to_ny);
		}
	}
	free(boat);
	return (trip_to_ny);
}

#include <fcntl.h>

int main(void)
{
	int fd;
	char *line;
	int i = 1;
	fd = open("testo.txt", O_RDONLY);
	line = get_next_line(fd);
	// while(line)
	// {
	// 	printf("line %d: %s", i++, line);
	// 	line = get_next_line(fd);
	// 	if (i == 5)
	// 		break ;
	// }
	printf("line %d: %s", i++, line);
	// printf("line %d: %s", i, get_next_line(fd));
	close(fd);
	free(line);
	return (0);
}
