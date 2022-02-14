/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmercier <tmercier@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/04 19:07:34 by tmercier      #+#    #+#                 */
/*   Updated: 2022/02/14 20:47:55 by tmercier      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_select_first(char *line)
{
	int		i;
	char	*dest;

	i = 0;
	if (!line[i])
		return (NULL);
	while (line[i] && line[i] != '\n')
		i++;
	dest = malloc(i + 2);
	if (!dest)
	{
		free(line);
		return (NULL);
	}
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		dest[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
		dest[i++] = '\n';
	dest[i] = ('\0');
	return (dest);
}

char	*ft_select_next(char *line)
{
	int		i;
	int		j;
	char	*buff;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (!line[i])
	{
		free(line);
		return (NULL);
	}
	buff = malloc(ft_strlen(line) - i + 1);
	if (!buff)
	{
		free(line);
		return (NULL);
	}
	j = 0;
	while (line[i])
		buff[j++] = line[++i];
	buff[j] = 0;
	free(line);
	return (buff);
}

char	*ft_get_line(int fd, char *save, char *buff)
{
	int			byte;

	byte = 1;
	while (byte)
	{
		byte = read(fd, buff, BUFFER_SIZE);
		if (byte < 0)
			return (NULL);
		buff[byte] = '\0';
		save = ft_strjoin(save, buff);
		if (!save)
			return (0);
		if (ft_strchr(save, '\n'))
			break ;
	}
	if (save[0] == '\0')
	{
		free(save);
		return (NULL);
	}
	return (save);
}

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1];
	static char	*save;	
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	save = ft_read_line(fd, save, buff);
	if (!save)
		return (NULL);
	line = ft_select_first(save);
	save = ft_select_next(save);
	return (line);
}
