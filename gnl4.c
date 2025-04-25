#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

//funciones utiles:


//caracteres encontrados en string incluido el '\n'
int len_nl(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			i++;
			return (i); 
		}
		i++;
	}
	i = 0;
	return (i);
}

//len_str
int len_str(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
//join_str
char *join_str(char *str1, char *str2)
{
	int		len_str1 = 0;
	int		len_str2 = 0;
	char	*str_joined;
	int		i = 0;
	int		j = 0;

	if (!str1 && !str2)
		return (NULL);
	if (str1)
		len_str1 = len_str(str1);

	if (str2)
		len_str2 = len_str(str2);
	str_joined = malloc(len_str1 + len_str2 + 1);
	if(str1)
	{
		while(str1[i])
		{
			str_joined[i] = str1[i];
			i++;
		}
	}
	if(str2)
	{
		while(str2[j])
		{
			str_joined[i + j] = str2[j];
			j++;
		}
	}
	str_joined[i + j] = '\0';
	return (str_joined);
}

//split_nl (actualiza el store)
char *split_nl(char **old_store)
{
	char	*store = *old_store;
	char	*line_to_return;
	char	*rest;
	int		len_to_nl;
	int		len_rest;
	int		i = 0;

	len_to_nl = len_nl(store);
	len_rest = len_str(store) - len_to_nl;

	line_to_return = malloc(len_to_nl + 1);
	while (store[i])
	{

		line_to_return[i] = store[i];
		if (line_to_return[i] == '\n')
			break ;
		i++;
	}
	line_to_return[len_to_nl] = '\0';

	/* ------------------------- */

	i = 0;
	rest = malloc(len_rest + 1);
	while (store[len_to_nl + i])
	{
		rest[i] = store[len_to_nl +  i];
		i++;
	}
	rest[i] = '\0';
	free(*old_store);
	*old_store = rest;
	printf("REST  ISSSSS:%s\n", rest);
	printf("STORE ISSSSS:%s\n", *old_store);
	return (line_to_return);
}
/* 
fun(fd)
{
	static char *rest;
	char *buffer;
	char *line;

	if (rest no tiene newline)
	{
		buffer = get_buffer(fd);
	}
	else
	{
		buffer = rest;
	}
	line = store_line(buffer);
	rest = store_rest(buffer);
	return line;
}
*/

/* int main()
{
	char *frase;
	frase = malloc(14);
	frase = strcpy(frase, "viva la \nVIDA");

	printf("store ANTES de ser actualizado: [%s]\n", frase);
	printf("frase hasta el NL: [%s]\n", split_nl(&frase));
	printf("store despues de ser actualizado: [%s]\n", frase);
	return (0);
} */

char *get_next_line(int fd)
{
	if (fd < 0)
		return (NULL);
	static char	*store = NULL;
	char		*line;
	char		*buffer;
	int			read_bytes;
	char		*aux;

	buffer = malloc(BUFFER_SIZE + 1);
	while(len_nl(store) == 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes <= 0)
		{
			if (read_bytes == -1)
			{
				free(buffer);
				free(store);
				return (NULL);
			}
			break ;
		}
		aux = store;
		store = join_str(store, buffer);
		free(aux);
	}
	return(split_nl(&store));
}

int main(void)
{
	int		fd;
	char	*line;

	fd = open("testo.txt", O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	printf("%s\n", line);
	free(line);
	close(fd);
	return (0);
}
