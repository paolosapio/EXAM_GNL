#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

//Funciones a hacer
int		len_n_0(char *str, bool is_nl)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (is_nl == true && str[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	return (i);
}

char	*join_str(char *str1, char *str2)
{
	int		len_str1;
	int		len_str2;
	char	*joined;
	int		i;
	int		j;

	if (!str1 && str2)
		return (str2);
	if (str1 && !str2)
		return (str1);
	if (!str1 && !str2)
		return (NULL);
	len_str1 = len_n_0(str1, false);
	len_str2 = len_n_0(str2, false);
	joined = malloc(len_str1 + len_str2 + 1);
	i = 0;
	while(str1[i])
	{
		joined[i] = str1[i];
		i++; 
	}
	j = 0;
	while(str2[j])
	{
		joined[i + j] = str2[j];
		j++;
	}
	joined[i + j] = '\0';
	return (joined);
}



char *split_store(char **original_store)
{
	char	*store = *original_store;
	printf("store: %s\n", store);

	char	*line_to_return;
	char	*new_store;

	int		size_line_to_return;
	int		size_new_store;

	int i;
	int j;

	size_line_to_return = len_n_0(store, true);
	line_to_return = malloc(size_line_to_return + 1);

	size_new_store = len_n_0(store, false) - size_line_to_return;
	new_store = malloc(size_new_store + 1);
	i = 0;
	while(store[i] != '\0')
	{

		line_to_return[i] = store[i];
		i++;
		if (store[i] == '\n')
		{
			i++;
			break ;
		}
	}
	line_to_return[i] = '\0';
	j = 0;
	while(store[i + j] != '\0')
	{
		new_store[j] = store[i + j];
		j++;
	}
	new_store[j] = '\0';
	free(store);
	*original_store = new_store;
	return (NULL);
}

/* char 	*split_store(char **store)
{
	printf("store es: %s\n", *store);
	char	*line_to_return;
	char	*new_store;
	int		len_to_nl;
	int		i;
	
	printf("antes %s\n", *store);
	if (*store == NULL)
		return (NULL);
	len_to_nl = len_n_0(*store, true);
	write(1, *store, len_to_nl);
	(*store)[len_to_nl] = '\0';
	line_to_return = *store;
	new_store = malloc(len_n_0(&store[0][len_to_nl + 1], false) + 1);
	if (!new_store)
		return (NULL);
	i = 0;
	while (i < len_n_0(&store[0][len_to_nl + 1], false))
	{
		new_store[i] = store[0][len_to_nl + 1 + i];
		i++;
	}
	new_store[i] = '\0';
	free(*store);
	*store = new_store;
	printf("despues %s\n", *store);
	return (line_to_return);
} */

/* char 	*split_store(char	**store)
{
	char	*line_to_return;
	char	*new_store;
	int		len_to_nl;
	int		i;

	i = 0;
	if (store == NULL)
		return (NULL);
	len_to_nl = len_n_0(*store, true);
	line_to_return = malloc(len_to_nl + 1);
	while(**store != '\0')
	{
		line_to_return[i] = **store;
		if(**store == '\n')
		{
			(*store)++;
			break ;
		}
		(*store)++;
		i++;
	}
	line_to_return[len_to_nl] = '\0';
	return (line_to_return);
} */

bool	is_nl(char	*str)
{
	if (str == NULL)
		return (false);
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (true);
		i++;
	}
	return (false);
}

char	*get_next_line(int fd)
{
	static char	*store = NULL;
	char		*buffer;
	char		*return_line;
	ssize_t		bytes_readed;
	char		*aux;
	if (fd < 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while(is_nl(store) == false)
	{
		bytes_readed = read(fd, buffer, BUFFER_SIZE);
		if (bytes_readed <= 0)
		{
			if (bytes_readed == -1)
			{
				free(buffer);
				free(store);
				store = NULL;
				return (NULL);
			}
			break ;
		}
		aux = store;
		store = join_str(store, buffer);
		free(aux);
	}
	return_line = split_store(&store);
	return (return_line);
}

int	main(void)
{
	char	*line;
	int	 	fd;
	int	 	n_line;

	n_line = 1;
	fd = open("testo.txt", O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
		line = get_next_line(fd);
		printf("%d %s", n_line, line);
		free(line);
		n_line++;
	}
	printf("%d %s", n_line, get_next_line(fd));
	free(line);
	close(fd);
	return (0);
}
