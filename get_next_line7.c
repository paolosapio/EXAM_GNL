
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif

//devuelve len de str hasta el nl incluido
int		len_nl(char *str)
{
	int	i = 0;

	while (str && str[i])
	{
		if (str[i] == '\n')
		{
			i++;
			return (i);
		}
		i++;
	}
	return (0);
}

int		ft_strlen(char *str)
{
	int	i = 0;

	while (str &&str[i])
	{
		i++;
	}
	return (i);
}

char	*ft_join(char *store, char *buffer)
{
	char	*new_store;
	int 	len_store = 0;
	int 	len_buffer = 0;
	int		i = 0;
	int		j = 0;

	if (!store && !buffer)
	{
		return (NULL);
	}
	if (store)
		len_store = ft_strlen(store);
	if (buffer)
		len_buffer = ft_strlen(buffer);
	new_store = malloc(len_store + len_buffer + 1);
	while (store && store[i])
	{
		new_store[i] = store[i];
		i++;
	}
	while (buffer && buffer[j])
	{
		new_store[i + j] = buffer[j];
		j++;
	}
	new_store[i + j] = '\0';
	return (new_store);
}

char	*extract_nl(char *store)
{
	char	*new_store;
	int		i = 0;

	new_store = malloc(len_nl(store) + 1);
	while (store[i])
	{
		new_store[i] = store[i];
		i++;
	}
	new_store[i] = '\0';
	return (new_store);
}

char	*refresh_store(char *store)
{
	char	*new_store;
	int		len_to_nl;
	int		i = 0;
	len_to_nl = len_nl(store);

	new_store = malloc(ft_strlen(store) - len_to_nl + 1);
	while(store[len_to_nl + i])
	{
		new_store[i] = store[len_to_nl + i];
		i++;
	}
	new_store[i] = '\0';
	// printf("new_store is[%s]\n", new_store);
	return (new_store);
}

char	*get_next_line(int fd)
{
		static char	*store = NULL;
		char		buffer[BUFFER_SIZE + 1] = {0};
		int 		bytes_leidos;
		char		*line = NULL;
		char		*aux;

		if(fd == -1)
		{
			return (NULL);
		}
		while(!len_nl(store))
		{
			bytes_leidos = read(fd, buffer, BUFFER_SIZE);
			if (bytes_leidos <= 0)
			{
				if (bytes_leidos == -1)
				{
					free(store);
					return (NULL);
				}
				break ;
			}
			aux = store;
			store = ft_join(store, buffer);
			free(aux);
		}
	//extraer lina desde store si hay salto de linea:
	if (len_nl(store))
	{
		line = extract_nl(store);
		aux = store;
		store = refresh_store(store);
		free(aux);
		return (line);
	}
	if (store && !len_nl(store))
	{
		line = ft_join(store, "");
		free(store);
		store = NULL;
		return (line);
	}
	// printf("line es:[%s]\n", line);

	return (NULL);
}

int main (void)
{
	char	*line;
	int		fd;
	int		count_line = 1;

	fd = open("testo.txt", O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		printf("%d	[%s]\n", count_line++, line);
		free(line);
		line = get_next_line(fd);
	}
	printf("%d	[%s]\n", count_line++, line);
	close(fd);
	return (0);
}