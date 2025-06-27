/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: layang <layang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:54:08 by layang            #+#    #+#             */
/*   Updated: 2025/06/27 14:01:01 by layang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	sort_sprites(t_cam	*pl, t_point p, int *order)
{
	t_point	c;
	int		max;
	t_point	*spr;
	int		tmp_order;

	c.x = 0;
	spr = pl->sprites;
	while (c.x < pl->nb_sprites - 1)
	{
		max = c.x;
		c.y = c.x + 1;
		while (c.y < pl->nb_sprites)
		{
			if (sp_dist(pl, p, spr[c.y], 0) > sp_dist(pl, p, spr[max], 0))
				max = c.y;
			c.y++;
		}
		if (max != c.x)
		{
			tmp_order = order[c.x];
			order[c.x] = order[max];
			order[max] = tmp_order;
		}
		c.x++;
	}
}

static int	get_pos_sprite(t_sprite *spt, t_cam *pl, t_point sp)
{
	double	camera_dist;

	spt->dx = (double)sp.x - (pl->posx + pl->ray2->offx / pl->ray2->grid);
	spt->dy = (double)sp.y - (pl->posy + pl->ray2->offy / pl->ray2->grid);
	spt->tx = spt->dy * cos(pl->p_angle) + spt->dx * sin(pl->p_angle);
	spt->ty = spt->dx * cos(pl->p_angle) - spt->dy * sin(pl->p_angle);
	if (spt->ty <= 0)
		return (0);
	camera_dist = (WIDTH / 2) / tan(pl->fov / 2);
	spt->sprix = (int)((WIDTH / 2) + (spt->tx * camera_dist / spt->ty));
	spt->sprih = abs((int)(HEIGHT / spt->ty));
	spt->spriw = spt->sprih;
	spt->ds.y = -spt->sprih / 2 + HEIGHT / 2 + (int)(pl->pitch);
	if (spt->ds.y < 0)
		spt->ds.y = 0;
	spt->de.y = spt->sprih / 2 + HEIGHT / 2 + (int)(pl->pitch);
	if (spt->de.y >= HEIGHT)
		spt->de.y = HEIGHT - 1;
	spt->ds.x = -spt->spriw / 2 + spt->sprix;
	if (spt->ds.x < 0)
		spt->ds.x = 0;
	spt->de.x = spt->spriw / 2 + spt->sprix;
	if (spt->de.x >= WIDTH)
		spt->de.x = WIDTH - 1;
	return (1);
}

/* static int	get_pos_sprite(t_sprite	*spt, t_cam	*pl, t_point	sp)
{
	spt->sprite_x = (double)sp.x - (pl->posx + pl->ray2->offx / pl->ray2->grid);
	spt->sprite_y = (double)sp.y - (pl->posy + pl->ray2->offy / pl->ray2->grid);
	spt->inv_det = 1.0 / (pl->planex * pl->diry - pl->dirx * pl->planey);
	spt->tx = spt->inv_det * (pl->diry * spt->sprite_x
			- pl->dirx * spt->sprite_y);
	spt->ty = spt->inv_det * (-pl->planey * spt->sprite_x
			+ pl->planex * spt->sprite_y);
	if (spt->ty <= 0)
		return (0);
	spt->sprix = (int)((WIDTH / 2) * (1 + spt->tx / spt->ty));
	spt->sprih = abs((int)(HEIGHT / spt->ty));
	spt->spriw = spt->sprih;
	spt->ds.y = -spt->sprih / 2 + HEIGHT / 2 + (int)(pl->pitch);
	if (spt->ds.y < 0)
		spt->ds.y = 0;
	spt->de.y = spt->sprih / 2 + HEIGHT / 2 + (int)(pl->pitch);
	if (spt->de.y >= HEIGHT)
		spt->de.y = HEIGHT - 1;
	spt->ds.x = -spt->spriw / 2 + spt->sprix;
	if (spt->ds.x < 0)
		spt->ds.x = 0;
	spt->de.x = spt->spriw / 2 + spt->sprix;
	if (spt->de.x >= WIDTH)
		spt->de.x = WIDTH - 1;
	return (1);
} */

void	put_col_sprite(t_sprite	spt, t_pic	sprt, t_scene	*sc, t_point	*c)
{
	double	step;
	double	tex_pos;
	t_point	tex;
	int		color;
	t_cam	*pl;

	pl = sc->tmap->player;
	tex.x = (int)(256 * ((*c).x - (-spt.spriw / 2 + spt.sprix))
			* sprt.width / spt.spriw) / 256;
	step = 1.0 * sprt.height / spt.sprih;
	tex_pos = (spt.ds.y - HEIGHT / 2 + spt.sprih / 2 - pl->pitch) * step;
	(*c).y = spt.ds.y;
	while ((*c).y < spt.de.y)
	{
		tex.y = (int)tex_pos & (sprt.height - 1);
		tex_pos += step;
		color = get_color_at(&sprt, tex.x, tex.y);
		if (color != 0x432600)
			put_pixel(&sc->img, (t_point){(*c).x, (*c).y, color});
		(*c).y++;
	}
}

static void	draw_sprites(t_scene	*sc, int i)
{
	t_cam		*pl;
	t_point		sp;
	t_sprite	spt;
	t_point		c;
	t_pic		sprt;

	pl = sc->tmap->player;
	sp = pl->sprites[i];
	if (abs(sp.x - pl->posx) <= 1 && abs(sp.x - pl->posx) >= 0
		&& abs(sp.y - pl->posy) <= 1 && abs(sp.y - pl->posy) >= 0)
	{
		sc->tmap->sprite_on = (sc->tmap->sprite_on == 0);
		sc->tmap->the_map[sp.y][sp.x] = '0';
	}
	if (!get_pos_sprite(&spt, pl, sp))
		return ;
	sprt = sc->tmap->sprite;
	c.x = spt.ds.x;
	while (c.x < spt.de.x)
	{
		if (spt.ty > 0 && c.x >= 0 && c.x < WIDTH
			&& spt.ty * 30 < pl->zbuffer[WIDTH - c.x - 1])
			put_col_sprite(spt, sprt, sc, &c);
		c.x++;
	}
}

/* void	sort_draw_sprites(t_scene	*scene, t_point	p)
{
	int	nb;
	int	*order;
	int	i;

	nb = scene->tmap->player->nb_sprites;
	if (nb == 0)
		return ;
	order = ft_calloc(nb + 1, sizeof(int));
	if (!order)
		return ;
	i = 0;
	while (i < nb)
	{
		order[i] = i;
		i++;
	}
	sort_sprites(scene->tmap->player, p, order);
	i = 0;
	while (i < nb)
	{
		draw_sprites(scene, order[i]);
		i++;
	}
	free(order);
} */

void	sort_draw_sprites(t_scene	*scene, t_point	p)
{
	int	nb;
	int	i;

	nb = scene->tmap->player->nb_sprites;
	if (nb == 0)
		return ;
	scene->tmap->order = ft_calloc(nb + 1, sizeof(int));
	if (!scene->tmap->order)
		return ;
	i = 0;
	while (i < nb)
	{
		scene->tmap->order[i] = i;
		i++;
	}
	sort_sprites(scene->tmap->player, p, scene->tmap->order);
	i = 0;
	while (i < nb)
	{
		draw_sprites(scene, scene->tmap->order[i]);
		i++;
	}
	free(scene->tmap->order);
	scene->tmap->order = NULL;
}
