/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjosephi <jjosephi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 20:56:30 by jjosephi          #+#    #+#             */
/*   Updated: 2019/11/19 05:48:23 by jjosephi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"
#include "fcntl.h"
#include <stdio.h>

char	*get_name(void)
{
	char	*buffer;
	int		b;

	buffer = malloc(200);
	b = read(0, buffer, 199);
	buffer[b - 1] = '\0';
	return (buffer);
}

void	write_to_file(t_data *data, char *filename, int i)
{
	char	*str;
	char	*echo;
	int		fd;

	echo = ft_strdup("touch ");
	str = ft_strnew(0);
	str = ft_better_strjoin(echo, "fdf_maps/");
	str = ft_better_strjoin(str, filename);
	system(str);
	free(str);
	str = ft_strdup("fdf_maps/");
	fd = open((ft_better_strjoin(str, filename)), O_RDWR);
	str = ft_strnew(0);
	while (i < data->size)
	{
		str = ft_better_strjoin(str, ft_itoa((*data->coords)[i]->z));
		if (i > 0 && (i + 1) % data->len == 0)
			str = ft_better_strjoin(str, "\n");
		else
			str = ft_better_strjoin(str, " ");
		i++;
	}
	write(fd, str, ft_strlen(str));
	free(str);
}

void	create_file(t_data *data)
{
	int		fd;
	char	*file;

	fd = open("fdf_maps", O_RDONLY | O_DIRECTORY);
	if (fd <= 0)
		system("mkdir fdf_maps");
	ft_putstr("Input file name :");
	file = get_name();
	write_to_file(data, file, 0);
	free(file);
	free_n_exit(data);
}

void	free_n_exit(t_data *data)
{
	int i;

	i = 0;
	while (i <= (data)->size - 1)
	{
		free((*(data)->coords)[i]);
		i++;
	}
	free(*(data->coords));
	free(data);
	exit(0);
}
