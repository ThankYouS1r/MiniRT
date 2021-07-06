/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmellos <lmellos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:47:33 by lmellos           #+#    #+#             */
/*   Updated: 2021/04/10 17:44:37 by lmellos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static char	**append_to_commands(const char *str, char **commands)
{
	char		**new_commands;
	size_t		i;

	new_commands = ft_malloc(sizeof(char *) * (ft_split_length(commands) + 2),
			NULL);
	i = 0;
	while (commands && commands[i])
	{
		new_commands[i] = ft_strdup(commands[i]);
		++i;
	}
	new_commands[i] = ft_strdup(str);
	ft_free_split(commands);
	return (new_commands);
}

static int	is_rt_file(const char *path)
{
	const size_t	len = ft_strlen(path);

	if (!path || len < 4)
		return (0);
	if (path[len - 1] != 't' || path[len - 2] != 'r' || path[len - 3] != '.')
		return (0);
	return (1);
}

char	**ft_read_config(const char *path)
{
	char		*line;
	char		**commands;
	int			fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		ft_crash("Cannot open this file", NULL, 2);
	if (!is_rt_file(path))
		ft_crash("You provided not *.rt file", NULL, 2);
	commands = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_str_is_empty(line))
			continue ;
		commands = append_to_commands(line, commands);
		free(line);
	}
	commands = append_to_commands(line, commands);
	free(line);
	return (commands);
}
