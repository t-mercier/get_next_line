/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmercier <tmercier@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/04 19:07:34 by tmercier      #+#    #+#                 */
/*   Updated: 2022/02/14 20:46:51 by tmercier      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*first_(char *save)
{
	int		i;
	char	*line;

	i = 0;
	if (!save[i])
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	line = malloc(i + 2);
	if (!line)
		return (NULL);
	i = -1;
	while (save[++i] != '\n')
		line[i] = save[i];
	if (save[i] == '\n')
		line[i++] = '\n';
	line[i] = ('\0');
	return (line);
}

char	*ft_select_after(char *save)
{
	int		i;
	int		j;
	char	*str;

	i = -1;
	while (save[++i] != '\n');
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	str = malloc(ft_strlen(save) - i + 1);
	if (!str)
		return (NULL);
	j = -1;
	while (save[++i])
		str[j] = save[i];
	str[j] = ('\0');
	free(save);
	return (str);
}

char	*after_(int fd, char *save)
{
	int		r_byte;
	char	*buff;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	r_byte = 1;
	while (!ft_strchr(save, '\n') && r_byte != 0)
	{
		r_byte = read(fd, buff, BUFFER_SIZE);
		if (r_byte < 0)
		{
			free(buff);
			return (NULL);
		}
		buff[r_byte] = ('\0');
		save = ft_strjoin(save, buff);
	}
	free(buff);
	return (save);
}

char	*get_next_line(int fd)
{
	static char	*save[MAX_FD];
	char		*line;	

	if (fd < 0 || BUFFER_SIZE < 1 || fd > MAX_FD)
		return (NULL);
	save[fd] = get_line(fd, save[fd]);
	if (!save[fd])
		return (NULL);
	line = first_(save[fd]);
	save[fd] = after_(save[fd]);
	return (line);
}
