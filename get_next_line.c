/*
En este GNL os quiero contar una historia que ha cambiado la vida de muchas
personas y ha marcado a un pueblo que, desesperado, supo hacer valer su
creatividad escapando a otro país, evitando las humillaciones del nazismo
durante la Segunda Guerra Mundial: los inmigrantes del sur de Italia en
Nueva York a principios del siglo XX.

Por seguridad, EE.UU. quería controlar a las familias completas antes de
desembarcarlas en NY, así que amontonaban a los inmigrantes en Ellis Island
(la actual isla de la Estatua de la Libertad). Y solamente si la familia
estaba completa se les daba el derecho a un trabajo y el visado para
desembarcar en NY en búsqueda del sueño americano.

Los caracteres son los familiares; el salto de línea o el '\0' representan
al capofamilia que cierra una familia completa para finalmente desembarcar
en NY hacia la libertad y lejos de las guerras.

Espero que os guste la analogía aplicada a este maravilloso proyecto:
https://es.wikipedia.org/wiki/Inmigraci%C3%B3n_italiana_en_Estados_Unidos
*/

#include <fcntl.h> //open, closed
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>

#define SICILIA_VACIA       0
#define BROKEN_BOAT			-1
#define FAMILIA_COMPLETA    '\n'
#define NEW_LINE	        1

typedef int t_fd;

#define ASIENTOS_BARCO BUFFER_SIZE

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

// Devuelve longitud hasta \n si len_nl es true, o hasta \0 si false
int	len_0_n(char *str, bool len_nl)
{
	int i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (len_nl && str[i] == '\n')
			return (i + 1); // incluido el '\n'
		i++;
	}
	return (i);
}

char	*ft_join(char *s1, char *s2)
{
	int		len_s1 = len_0_n(s1, 0);
	int		len_s2 = len_0_n(s2, 0);
	char	*joined;
	int		i;
	int		j;

	joined = malloc(len_s1 + len_s2 + 1);
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
		joined[i + j] = s2[j];
		j++;
	}
	joined[i + j] = '\0';
	if (s1)
		free(s1); // libero s1 porque ya está copiado
	return (joined);
}

char	*ft_strchr(char *s, char c)
{
	int	i = 0;

	if (!s)
		return (NULL);
	if (c == '\0')
		return (&s[len_0_n(s, 0)]);
	while (s[i])
	{
		if (s[i] == c)
			return (&s[i]);
		i++;
	}
	return (NULL);
}

// Separa la primera línea de ellis_island y actualiza ellis_island con el resto
char	*split_family(char **ellis_island)
{
	int		len_line = len_0_n(*ellis_island, true);
	int		len_rest = len_0_n(*ellis_island, false) - len_line;
	char	*line = malloc(len_line + 1);
	char	*rest = malloc(len_rest + 1);
	int		i = 0;
    int     j = 0;

	if (!line || !rest)
		return (free(line), free(rest), NULL);
	while (i < len_line)
	{
		line[i] = (*ellis_island)[i];
		i++;
	}
	line[i] = '\0';
	while ((*ellis_island)[i])
		rest[j++] = (*ellis_island)[i++];
	rest[j] = '\0';
	free(*ellis_island);
	*ellis_island = rest;
	return (line);
}

#include <unistd.h>

char	*get_next_line(t_fd sicily)
{
	static char	*ellis_island = NULL;
	char		*boat;
	char		*family;
	int			captain_report;

	if (sicily < 0)
		return (NULL);
	boat = malloc(ASIENTOS_BARCO + 1);
	if (!boat)
		return (NULL);
	while (ft_strchr(ellis_island, '\n') == NULL)
	{
		captain_report = read(sicily, boat, ASIENTOS_BARCO);
		if (captain_report <= 0)
		{
			if (captain_report == -1)
			{
				free(boat);
				free(ellis_island);
				ellis_island = NULL;
				return (NULL);
			}
			break ;
		}
		boat[captain_report] = '\0';
		ellis_island = ft_join(ellis_island, boat);
		if (!ellis_island)
			return (free(boat), NULL);
	}
	free(boat);
	if (!ellis_island || ellis_island[0] == '\0')
	{
		free(ellis_island);
		ellis_island = NULL;
		return (NULL);
	}
	if (ft_strchr(ellis_island, '\n')) // Última línea sin '\n' — copia y liberar
		return (split_family(&ellis_island));
	char *temp = ellis_island;
	ellis_island = NULL;
	return (temp);
}

int	main(void)
{
	int		fd;
	char	*line;
	int		i = 1;
  
    fd = open("testo.txt", O_RDONLY);
    line = get_next_line(fd);
	while (line != NULL)
	{
		printf("line %d: %s", i++, line);
		free(line);
        line = get_next_line(fd);
	}
    free(line);
	close(fd);
	return (0);
}
