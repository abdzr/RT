/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <merras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 16:12:32 by abiri             #+#    #+#             */
/*   Updated: 2020/02/21 00:56:47 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

const t_xml_part_type	g_xml_parser_syntax_table[] = {
	{.type = TYPE_TAGNAME, .function = &ft_xml_parse_tagname},
	{.type = TYPE_PROP, .function = &ft_xml_parse_prop},
	{.type = TYPE_TAGCLOSE, .function = &ft_xml_parse_tagclose}
};

static int			ft_parse_part(char **line, t_xml_tag *tag, int types)
{
	int						index;
	int						next_types;

	index = 0;
	next_types = 0;
	while (index < TYPES_COUNT)
	{
		if ((1 << index) & types)
			next_types = g_xml_parser_syntax_table[index].function(line, tag);
		if (next_types != 0)
			break ;
		index++;
	}
	return (next_types);
}

static t_xml_tag	*ft_parse_tag(int fd, int *status)
{
	t_xml_tag	*tag;
	char		*line;
	int			types;

	*status = 1;
	if (get_next_line(fd, &line) <= 0)
		return (NULL);
	ft_putstr_fd("received line : {{{{{{ ", 2);
	ft_putstr_fd(line, 2);
	ft_putstr_fd(" }}}}}}\n", 2);
	if (!(tag = ft_memalloc(sizeof(t_xml_tag))))
		return (NULL);
	if (ft_strequ(line, "!"))
		return (NULL);
	types = TYPE_TAGNAME;
	while (types != 0 && types != TYPE_NONE)
		types = ft_parse_part(&line, tag, types);
	if (types == 0)
	{
		*status = 0;
		return (NULL);
	}
	return (tag);
}

static t_xml_tag	*ft_xml_push_tag(t_xml_data *data, t_xml_tag *tag)
{
	if (!data->last_tag || !data->tags)
	{
		data->tags = tag;
		data->last_tag = tag;
	}
	else
	{
		data->last_tag->next = tag;
		data->last_tag = tag;
	}
	return (tag);
}

void				ft_xml_free_props(t_xml_tag *tag)
{
	t_xml_prop	*prop;
	t_xml_prop	*temp;

	prop = tag->props;
	while (prop)
	{
		temp = prop->next;
		free(prop->name);
		free(prop->value);
		free(prop);
		prop = temp;
	}
}

t_xml_data			*ft_read_xml(char *filename)
{
	t_xml_data	*data;
	t_xml_tag	*newtag;
	int			fd;
	int			status;

	fd = 0;
	if (!(data = ft_memalloc(sizeof(t_xml_data))))
		return (NULL);
	while ((newtag = ft_parse_tag(fd, &status)))
		ft_xml_push_tag(data, newtag);
	if (status == 0)
		return (ft_xml_free_data(data));
	return (data);
}
