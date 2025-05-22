/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:59:55 by #+#    #+#             */
/*   Updated: 2025/05/21 13:59:55 by ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdio.h> // REMOVE BEFORE PUSHING
# include <stdlib.h>
# include <fcntl.h> // REMOVE BEFORE PUSHING
# include <unistd.h>

# ifndef BUFFER_SIZE 
#  define BUFFER_SIZE 42
# endif

typedef struct s_fd_node
{
	int					fd;
	char				*stash;
	struct s_fd_node	*next;
}	t_fd_node;

char		*get_next_line(int fd);
t_fd_node	*get_current_node(t_fd_node **head, int fd);
char		*read_to_stash(int fd, char *stash);
char		*extract_line(char *stash);
char		*trim_stash(char *stash);
size_t		ft_strlen(char *s);
char		*ft_strchr(char *s, int c);
char		*ft_strdup(char *s);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_substr(char *s, unsigned int start, size_t len);
void		remove_node(t_fd_node **head, int fd);

#endif
