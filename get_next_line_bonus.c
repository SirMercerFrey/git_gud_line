/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:50:40 by #+#    #+#             */
/*   Updated: 2025/05/21 13:50:40 by ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static t_fd_node	*head;
	t_fd_node			*current;
	char				*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	current = get_current_node(&head, fd);
	if (!current)
		return (NULL);
	current->stash = read_to_stash(fd, current->stash);
	if (!current->stash)
	{
		return (NULL);
	}
	line = extract_line(current->stash);
	current->stash = trim_stash(current->stash);
	return (line);
}

t_fd_node	*get_current_node(t_fd_node **head, int fd)
{
	t_fd_node	*temp;

	temp = *head;
	while (temp)
	{
		if (temp->fd == fd)
			return (temp);
		temp = temp->next;
	}
	temp = (t_fd_node *)malloc(sizeof(t_fd_node));
	if (!temp)
		return (NULL);
	temp->fd = fd;
	temp->stash = NULL;
	temp->next = *head;
	*head = temp;
	return (temp);
}

char	*read_to_stash(int fd, char *stash)
{
	char	*buf;
	ssize_t	bytes_read;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(stash, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buf);
			free(stash);
			return (NULL);
		}
		buf[bytes_read] = '\0';
		stash = ft_strjoin(stash, buf);
	}
	free(buf);
	return (stash);
}

char	*extract_line(char *stash)
{
	size_t	i;
	char	*line;

	if (!stash || !*stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		++i;
	line = ft_substr(stash, 0, i + (stash[i] == '\n'));
	return (line);
}

char	*trim_stash(char *stash)
{
	char	*new_stash;
	size_t	i;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		++i;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	new_stash = ft_strdup(stash + i + 1);
	free(stash);
	return (new_stash);
}

/*void	remove_node(t_fd_node **head, int fd)
{
	t_fd_node	*temp;
	t_fd_node	*prev;

	temp = *head;
	prev = NULL;
	while (temp)
	{
		if (temp->fd == fd)
		{
			if (prev)
				prev->next = temp->next;
			else
				*head = temp->next;
			free(temp->stash);
			free(temp);
			return ;
		}
		prev = temp;
		temp = temp->next;
	}
}*/

/*int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		printf("%s", line);
		free(line);
	}
	return (0);
}*/
