/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadric_normals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 23:15:12 by abenaiss          #+#    #+#             */
/*   Updated: 2020/01/16 22:25:36 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_ellipsoid_normal(t_cam *cam, t_ellipsoid *ellipsoid, double distance)
{
	t_vector	normal;
	t_vector	radius;

	ft_intersection_position(cam, distance);
	radius = ft_sub_vector(cam->hit.position, ellipsoid->center);
	normal.x = 2 * radius.x / FT_SQR(ellipsoid->axis.x);
	normal.y = 2 * radius.y / FT_SQR(ellipsoid->axis.y);
	normal.z = 2 * radius.z / FT_SQR(ellipsoid->axis.z);
	ft_get_hit_info(ft_normalise_vector(normal),
		(t_point *)ellipsoid, cam);
}

void	ft_hyperboloid_normal(t_cam *cam, t_hyperboloid *hyperboloid,
	double distance)
{
	t_vector	normal;
	t_vector	radius;

	ft_intersection_position(cam, distance);
	radius = ft_sub_vector(cam->hit.position, hyperboloid->center);
	normal.x = 2 * radius.x;
	normal.y = -2 * radius.y;
	normal.z = 2 * radius.z;
	ft_get_hit_info(ft_normalise_vector(normal),
		(t_point *)hyperboloid, cam);
}

void	ft_paraboloid_normal(t_cam *cam, t_paraboloid *paraboloid,
	double distance)
{
	t_vector	normal;
	t_vector	radius;

	ft_intersection_position(cam, distance);
	radius = ft_sub_vector(cam->hit.position, paraboloid->center);
	normal.x = 2 * radius.x;
	normal.y = -1;
	normal.z = 2 * radius.z;
	ft_get_hit_info(ft_normalise_vector(normal),
		(t_point *)paraboloid, cam);
}
