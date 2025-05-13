/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabal-m <mzabal-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 21:35:44 by zabal             #+#    #+#             */
/*   Updated: 2025/01/08 09:47:17 by mzabal-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stddef.h>
#include <stdlib.h>
//#include <fcntl.h>	activarlo con el main
//#include <unistd.h>

/*
_____EXTRACT_LINE_____
** Esta función toma un buffer (stash) como entrada 
y extrae la primera línea que encuentra.
** La línea extraída incluye el carácter de nueva línea ('\n'), si está presente.
** Devuelve un puntero a la línea extraída o NULL si ocurre 
un error o si el buffer está vacío.

_____UPDATE_STASH_____
** Esta función actualiza el buffer (stash) eliminando la línea ya procesada.
** Crea un nuevo buffer que contiene los datos 
restantes después del salto de línea ('\n').
** Libera la memoria del buffer original y 
devuelve un puntero al nuevo buffer o NULL si no hay datos restantes.

_____READ_AND_UPDATE_STASH_____
** Lee datos desde un file descriptor(fd)
** en bloques de tamaño`BUFFER_SIZE` y los acumula en `stash` hasta
** encontrar un salto de línea (`\n`) o llegar
** al final del archivo.
	
** Variables:
** - `fd`: Descriptor de archivo desde el que se lee.
** - `stash`: Cadena dinámica donde se acumulan los datos leídos.
** - `buffer`: Arreglo temporal para almacenar cada bloque leído.
** - `bytes_read`: Bytes leídos en cada iteración.

** Proceso:
** 1. Lee datos con `read` mientras no haya salto de línea y no sea EOF.
** 2. Si `read` devuelve -1 (error), libera `stash` y retorna `NULL`.
** 3. Combina `stash` con los datos leídos usando `ft_gnlstrjoin`.
** 4. Si la combinación falla, retorna `NULL`.

** Retorna:
** - `stash` actualizado con los datos leídos o `NULL` en caso de error.

_____GET_NEXT_LINE_____
** `get_next_line` devuelve la siguiente línea 
** leída desde un file descriptor (fd).
** Gestiona el contenido pendiente en 
** una variable estática (`stash`) para permitir
** lecturas consecutivas de líneas.

** Variables:
** - `fd`: Descriptor del archivo a leer.
** - `stash`: Variable estática que almacena los datos leídos pendientes.
** - `line`: Cadena que contiene la línea extraída de `stash`.

** Proceso:
** 1. Verifica si el `fd` o el `BUFFER_SIZE` son 
** 	  inválidos; en ese caso, retorna `NULL`.
** 2. Llama a `read_and_update_stash` para leer y acumular datos en `stash`.
**    - Si falla, retorna `NULL`.
** 3. Usa `extract_line` para extraer la siguiente línea completa desde `stash`.
** 4. Actualiza `stash` eliminando la línea ya extraída con `update_stash`.
** 5. Devuelve la línea extraída.

** Retorno:
** - La siguiente línea del archivo o `NULL` en caso de error o fin de archivo.
*/

static char	*read_and_update_stash(int fd, char *stash)
{
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	bytes_read;

	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr_gnl(stash, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(stash);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		stash = ft_gnlstrjoin(stash, buffer);
		if (!stash)
			return (NULL);
	}
	return (stash);
}

static char	*extract_line(char *stash)
{
	char	*line;
	size_t	len;
	size_t	i;

	if (!stash || *stash == '\0')
		return (NULL);
	len = 0;
	while (stash[len] && stash[len] != '\n')
		len++;
	line = (char *)malloc(sizeof(char) * (len + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[len] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*update_stash(char *stash)
{
	char	*new_stash;
	size_t	i;
	size_t	j;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i] || !stash[i + 1])
	{
		free(stash);
		return (NULL);
	}
	new_stash = (char *)malloc(sizeof(char) * (ft_strlen_gnl(stash) - i));
	if (!new_stash)
		return (NULL);
	i++;
	j = 0;
	while (stash[i])
		new_stash[j++] = stash[i++];
	new_stash[j] = '\0';
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_and_update_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	stash = update_stash(stash);
	return (line);
}

/*
int	main(void)
{
	char	*line;
	int		fd;
	int		i;

	fd = open("tests/test.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (1);
	}

	i = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		printf("Line [%02d]: %s", i, line);
		free(line);
		i++;
	}
	close(fd);
	return (0);
}
	*/
