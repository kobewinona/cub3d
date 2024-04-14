/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_ext_buff.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 05:05:48 by tponutha          #+#    #+#             */
/*   Updated: 2024/04/14 17:46:13 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/*
GNL INSTRUCTION
0: Check bad fd, if yes then return NULL

1: Reading BUFFER -> sb_readone()
- 1. use read() to read file
- 2. if EOF or ERROR then free(buffer)
- 3. return byte from read()

2: Reading oneline (until has \n) -> sb_readline()
- 1. use sb_readone() to read text until has \n
- 2. if ERROR found then free everything and return NULL
- 3. if EOF meet but no \n then just return

3: Serparate buffer to two part
- 1. before \n to line -> ft_strndup
- 2. after \n to temp -> ft_strndup
- 3. free current text
- 4. pointting text to temp

4: Return line and save text
*/

// merge text and buff together
// and free input text & buffer

static char	*sb_buffmanage(char *text, char *buffer)
{
	char	*str;

	str = ft_strjoin(text, buffer);
	free(text);
	free(buffer);
	return (str);
}

// read function is in here
// return byte of what it read

static ssize_t	sb_readone(int fd, char **pbuffer)
{
	ssize_t	byte;

	*pbuffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!(*pbuffer))
		return (-1);
	byte = read(fd, *pbuffer, BUFFER_SIZE);
	if (byte == -1 || byte == 0)
	{
		free(*pbuffer);
		return (byte);
	}
	(*pbuffer)[byte] = 0;
	return (byte);
}

// build string until it has \n + extra
// EOF & Normal give text 
// ERROR or EOF with text = NULL give NULL

static char	*sb_readline(int fd, char *text)
{
	ssize_t	len;
	size_t	i;
	char	*buffer;
	char	flag;

	while (1)
	{
		len = sb_readone(fd, &buffer);
		if (len == 0)
			break ;
		if (len == -1)
		{
			free(text);
			return (NULL);
		}
		i = ft_strclen(buffer, '\n');
		flag = (buffer[i] != '\n');
		text = sb_buffmanage(text, buffer);
		if (!flag || !text)
			break ;
	}
	return (text);
}

// if separate line malloc fail
// then free everything and return NULL

static char	*sb_failsafe(char **text, char *line, char *temp)
{
	free(*text);
	*text = NULL;
	if (line)
		free(line);
	if (temp)
		free(temp);
	return (NULL);
}

// text -> line + temp
// free(text)
// temp -> text
// return line

char	*get_next_line_ext_buff(int fd, char **ext_buff)
{
	size_t		i;
	size_t		templen;
	char		*line;
	char		*temp;

	if (fd <= -1)
		return (NULL);
	*ext_buff = sb_readline(fd, *ext_buff);
	if (!(*ext_buff))
		return (NULL);
	i = ft_strclen(*ext_buff, '\n');
	templen = ft_strclen(&(*ext_buff)[i + ((*ext_buff)[i] != 0)], 0);
	line = ft_strndup((*ext_buff), i + ((*ext_buff)[i] != 0));
	temp = ft_strndup(&(*ext_buff)[i + ((*ext_buff)[i] != 0)], templen);
	if (!line || !temp)
		return (sb_failsafe(ext_buff, line, temp));
	free(*ext_buff);
	*ext_buff = temp;
	if ((*ext_buff)[0] == 0)
		sb_failsafe(ext_buff, NULL, NULL);
	return (line);
}
