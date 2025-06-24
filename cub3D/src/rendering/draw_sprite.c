/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: layang <layang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:54:08 by layang            #+#    #+#             */
/*   Updated: 2025/06/24 18:44:01 by layang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	sort_sprites(t_cam	*pl, t_point p, int *order)
{
    t_point c;
	int max;
	t_point	*spr;
	int tmp_order;

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

// i = 0;
// while (i < player->nb_sprites)
//     printf("sprite order: %d\n", order[i++]);


// pl = sc->tmap->player;
// printf("cam dir: (%.6f, %.6f), plane: (%.6f, %.6f)\n",
// pl->dirx, pl->diry, pl->planex, pl->planey);
// sprite = pl->sprites[i];
// printf("sprite orig position: (%d, %d)\n", sprite.x, sprite.y);
// sprite_x = sprite.x - (pl->posx + pl->ray2->offx / pl->ray2->grid);
// sprite_y = sprite.y - (pl->posy + pl->ray2->offy / pl->ray2->grid);
// printf("sprite position: (%f, %f)\n", sprite_x, sprite_y);
// inv_det = 1.0 / (pl->planex * pl->diry - pl->dirx * pl->planey);
// tx = inv_det * (pl->diry * sprite_x - pl->dirx * sprite_y);
// ty = inv_det * (-pl->planey * sprite_x + pl->planex * sprite_y);
// printf("inv_det = %f, tx = %f, ty = %f\n", inv_det, tx, ty);
// if (ty <= 0)
// {
//     printf("SKIP: behind player\n");
//     return ; // 在玩家后方，不画
// }

// for (st = ds.x; st < de.x; st++)
// {
//     //if (ty > 0 && st >= 0 && st < WIDTH && pl->zbuffer[st] == 1.0)
//     printf("st: %d, zbuffer st: %f\n", st, pl->zbuffer[st]);
//     printf("player pos: (%d, %d)\n", pl->posx, pl->posy);
//     if (ty > 0 && st >= 0 && st < WIDTH && ty * 30 < pl->zbuffer[WIDTH - st - 1])
//     {
//         int tex_x = (int)(256 * (st - (-spriw / 2 + sprix)) * sprt.width / spriw) / 256;
//         // 垂直方向步进
//         double step = 1.0 * sprt.height / sprih;
//         // 起始的 y 纹理位置
//         double tex_pos = (ds.y - HEIGHT / 2 + sprih / 2 - pl->pitch) * step;
//         for (y = ds.y; y < de.y; y++)
//         {
//             // 获取贴图的 Y 坐标
//             if (y == ds.y)
//                 printf("DRAWING sprite.\n");
//             int tex_y = (int)tex_pos & (sprt.height - 1);
//             tex_pos += step;
//             // 获取贴图颜色
//             int color = get_color_at(&sprt, tex_x, tex_y);
//             // 忽略透明颜色（比如：颜色为0或某个mask值）(color & 0xFFFFFF) != 0
//             if (color != 0x432600)
//                 put_pixel(&sc->img, (t_point){st, y, color});
//         }
//     }
//     else
//         printf("SKIP: out of screen range\n");
// }

static void get_pos_sprite(t_sprite	*spt, t_cam	*pl, t_point	sp)
{
    spt->sprite_x = sp.x - (pl->posx + pl->ray2->offx / pl->ray2->grid);
	spt->sprite_y = sp.y - (pl->posy + pl->ray2->offy / pl->ray2->grid);
	spt->inv_det = 1.0 / (pl->planex * pl->diry - pl->dirx * pl->planey);
	spt->tx = spt->inv_det * (pl->diry * spt->sprite_x
			- pl->dirx * spt->sprite_y);
	spt->ty = spt->inv_det * (-pl->planey * spt->sprite_x 
			+ pl->planex * spt->sprite_y);
	if (spt->ty <= 0)
		return ;
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
}

void put_col_sprite(t_sprite	spt, t_pic	sprt, t_scene	*sc, t_point	*c)
{
	int tex_x;
	double step;
	double tex_pos;
	int tex_y;
	int color;
	t_cam       *pl;
	
	pl = sc->tmap->player;
	tex_x = (int)(256 * ((*c).x - (-spt.spriw / 2 + spt.sprix))
		* sprt.width / spt.spriw) / 256;
	step = 1.0 * sprt.height / spt.sprih;
	tex_pos = (spt.ds.y - HEIGHT / 2 + spt.sprih / 2 - pl->pitch) * step;
	(*c).y = spt.ds.y;
	while ((*c).y < spt.de.y)
	{
		tex_y = (int)tex_pos & (sprt.height - 1);
		tex_pos += step;
		color = get_color_at(&sprt, tex_x, tex_y);
		if (color != 0x432600)
			put_pixel(&sc->img, (t_point){(*c).x, (*c).y, color});
		(*c).y++;
	}
}

static void draw_sprites(t_scene	*sc, int i)
{
	t_cam       *pl;
	t_point     sp;
    t_sprite    spt;
    t_point     c;
	t_pic       sprt;

	pl = sc->tmap->player;
	sp = pl->sprites[i];
    get_pos_sprite(&spt, pl, sp);
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

void sort_draw_sprites(t_scene *scene, t_point p)
{
	int	nb;
	int	*order;
	int	i;

	nb = scene->tmap->player->nb_sprites;
	printf("nb of sprite hit: %d\n", nb);
	if (nb == 0)
		return ;
	order = malloc(sizeof(int) * nb);
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
}
