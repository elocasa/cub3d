/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diego <diego@student.42.fr>                #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-09-22 14:26:04 by diego             #+#    #+#             */
/*   Updated: 2026-09-22 14:26:04 by diego            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Compatibilidad con código previo: envoltorio sobre init_game. */
t_game	*init_data(void)
{
	return (init_game());
}
