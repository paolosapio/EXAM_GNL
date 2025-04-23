#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
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

char 	*split_store(char	**store)
{
	char	*line_to_return;
	char	*new_store;
	int		len_to_nl;
	int		i;

	i = 0;
	if (store == NULL)
		return (NULL);


	len_to_nl = len_n_0(*store, true);
	*store[len_to_nl] = '\0';
	line_to_return = *store;
	len_to_nl(store[len_to_nl]);
	
	while( != '\0')
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
}

// char 	*split_store(char	**store)
// {
// 	char	*line_to_return;
// 	char	*new_store;
// 	int		len_to_nl;
// 	int		i;

// 	i = 0;
// 	if (store == NULL)
// 		return (NULL);
// 	len_to_nl = len_n_0(*store, true);
// 	line_to_return = malloc(len_to_nl + 1);
// 	while(**store != '\0')
// 	{
// 		line_to_return[i] = **store;
// 		if(**store == '\n')
// 		{
// 			(*store)++;
// 			break ;
// 		}
// 		(*store)++;
// 		i++;
// 	}
// 	line_to_return[len_to_nl] = '\0';
// 	return (line_to_return);
// }

bool	is_nl(char	*str)
{
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
			aux = store;
			store = join_str(store, buffer);
			free(aux);
		}
	}
	return_line = //extraer la linea con el salto de linea y actualizar el store sin la linea devuelta;
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
