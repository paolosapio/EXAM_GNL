#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

#define ASIENTOS_BARCO 100

// Devuelve longitud hasta \n si len_nl es true, o hasta \0 si false
int	len_0_n(char *str, bool len_nl)
{
	int i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (len_nl && str[i] == '\n')
			return (i + 1);
		i++;
	}
	return (i);
}

char	*ft_join(char *s1, char *s2)
{
	int		len_s1 = len_0_n(s1, 0);
	int		len_s2 = len_0_n(s2, 0);
	char	*joined = malloc(len_s1 + len_s2 + 1);
	int		i = 0, j = 0;

	if (!joined)
		return (NULL);
	while (s1 && s1[i])
		joined[i] = s1[i++];
	while (s2 && s2[j])
		joined[i++] = s2[j++];
	joined[i] = '\0';
	free(s1); // liberamos s1 porque ya está copiado
	return (joined);
}

char	*ft_strchr(const char *s, int c)
{
	int	i = 0;

	if (!s)
		return (NULL);
	if (c == '\0')
		return ((char *)&s[len_0_n((char *)s, 0)]);
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
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

char	*get_next_line(int sicily)
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
	while (!ft_strchr(ellis_island, '\n'))
	{
		captain_report = read(sicily, boat, ASIENTOS_BARCO);
		if (captain_report <= 0)
			break ;
		boat[captain_report] = '\0';
		ellis_island = ft_join(ellis_island, boat);
		if (!ellis_island)
			return (free(boat), NULL);
	}
	free(boat);
	if (!ellis_island || ellis_island[0] == '\0')
		return (free(ellis_island), ellis_island = NULL, NULL);
	if (ft_strchr(ellis_island, '\n'))
		return (split_family(&ellis_island));
	// última línea sin '\n'
	family = ellis_island;
	ellis_island = NULL;
	return (family);
}

#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd = open("testo.txt", O_RDONLY);
	char	*line;
	int		i = 1;
  
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("line %d: %s", i++, line);
		free(line);
	}
	close(fd);
	return (0);
}
