/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: layang <layang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:09:52 by  layang           #+#    #+#             */
/*   Updated: 2025/06/23 17:29:42 by layang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	clear_zbuffer_sprites(t_cam *player)
{
	int	i;

	i = 0;
	while (i < WIDTH)
	{
		player->zbuffer[i] = 0.0;
		i++;
	}
	i = 0;
	while (i < MAX_HITS_PER_RAY)
	{
		player->sprites[i].x = 0;
		player->sprites[i].y = 0;
		player->sprites[i].color = 0;
		i++;
	}
	player->nb_sprites = 0;
}

/* static double	get_background_dist(t_scene	*sc, int r)
{
	t_cam	*pl;
	t_point sprite;
	double sprite_x, sprite_y;
	double inv_det, ty;

	pl = sc->tmap->player;
	//printf("cam dir: (%.6f, %.6f), plane: (%.6f, %.6f)\n",
    //pl->dirx, pl->diry, pl->planex, pl->planey);
	sprite = pl->zbuffer[WIDTH - r - 1];
	// 相对于玩家位置的偏移
	//printf("sprite orig position: (%d, %d)\n", sprite.x, sprite.y);
	// sprite_x = sprite.x + 0.5 - pl->posx;
	// sprite_y = sprite.y + 0.5 - pl->posy;
	sprite_x = sprite.x - (pl->posx + pl->ray2->offx / pl->ray2->grid);
	sprite_y = sprite.y - (pl->posy + pl->ray2->offy / pl->ray2->grid);
	//printf("sprite position: (%f, %f)\n", sprite_x, sprite_y);
	// 矩阵变换：世界坐标 -> 相机坐标
	inv_det = 1.0 / (pl->planex * pl->diry - pl->dirx * pl->planey);
	//tx = inv_det * (pl->diry * sprite_x - pl->dirx * sprite_y);
	ty = inv_det * (-pl->planey * sprite_x + pl->planex * sprite_y);
	return (ty);
} */

static void draw_sprites(t_scene	*sc, int i)
{
	t_cam	*pl;
	t_point sprite;
	double sprite_x, sprite_y;
	double inv_det, tx, ty;
	int sprix, sprih, spriw;
	t_point	ds;
	t_point de;
	int st, y;
	t_pic	sprt;
	double	bac;

	pl = sc->tmap->player;
	printf("cam dir: (%.6f, %.6f), plane: (%.6f, %.6f)\n",
    pl->dirx, pl->diry, pl->planex, pl->planey);
	sprite = pl->sprites[i];
	// 相对于玩家位置的偏移
	printf("sprite orig position: (%d, %d)\n", sprite.x, sprite.y);
	// sprite_x = sprite.x + 0.5 - pl->posx;
	// sprite_y = sprite.y + 0.5 - pl->posy;
	sprite_x = sprite.x - (pl->posx + pl->ray2->offx / pl->ray2->grid);
	sprite_y = sprite.y - (pl->posy + pl->ray2->offy / pl->ray2->grid);
	printf("sprite position: (%f, %f)\n", sprite_x, sprite_y);
	// 矩阵变换：世界坐标 -> 相机坐标
	inv_det = 1.0 / (pl->planex * pl->diry - pl->dirx * pl->planey);
	//inv_det = 1.0 / (pl->dirx * pl->planey - pl->planex * pl->diry);
	tx = inv_det * (pl->diry * sprite_x - pl->dirx * sprite_y);
	ty = inv_det * (-pl->planey * sprite_x + pl->planex * sprite_y);
	//tx = inv_det * (-pl->diry * sprite_x + pl->dirx * sprite_y);
	//ty = inv_det * (pl->planey * sprite_x - pl->planex * sprite_y);
	printf("inv_det = %f, tx = %f, ty = %f -----\n", inv_det, tx, ty);
	if (ty <= 0)
	{
		printf("SKIP: behind player\n");
		return ; // 在玩家后方，不画
	}
	sprix = (int)((WIDTH / 2) * (1 + tx / ty));
	// sprite 高度 & 宽度（可等比例缩放）
	sprih = abs((int)(HEIGHT / ty));
	spriw = sprih;

	// Y 坐标（垂直）绘制范围
	ds.y = -sprih / 2 + HEIGHT / 2 + (int)(pl->pitch);
	if (ds.y < 0) 
		ds.y = 0;
	de.y = sprih / 2 + HEIGHT / 2 + (int)(pl->pitch);
	if (de.y >= HEIGHT)
		de.y = HEIGHT - 1;
	// X 坐标（水平方向）绘制范围
	ds.x = -spriw / 2 + sprix;
	if (ds.x < 0)
		ds.x = 0;
	de.x = spriw / 2 + sprix;
	if (de.x >= WIDTH)
		de.x = WIDTH - 1;
	// 遍历 sprite 的每一条竖线
	// tex_x: 当前 stripe 对应贴图的 X 坐标
	sprt = sc->tmap->sprite;
	for (st = ds.x; st < de.x; st++)
	{
		//if (ty > 0 && st >= 0 && st < WIDTH && pl->zbuffer[st] == 1.0)
		//if (ty > 0 && st >= 0 && st < WIDTH && ty * 30 < pl->zbuffer[st])
		//printf("st: %d, zbuffer [x, y]: (%d, %d))\n", st, pl->zbuffer[WIDTH - st - 1].x, pl->zbuffer[WIDTH - st - 1].y);
		printf("player pos: (%d, %d)\n", pl->posx, pl->posy);
		if (ty > 0 && st >= 0 && st < WIDTH)
		{
			//bac =  get_background_dist(sc, st);
			bac = pl->zbuffer[WIDTH - st - 1];
			printf("bac pix distance ----: %f\n", bac);
			if (ty * 30 < bac)
			{
				int tex_x = (int)(256 * (st - (-spriw / 2 + sprix)) * sprt.width / spriw) / 256;
				// 垂直方向步进
				double step = 1.0 * sprt.height / sprih;
				// 起始的 y 纹理位置
				double tex_pos = (ds.y - HEIGHT / 2 + sprih / 2 - pl->pitch) * step;
				for (y = ds.y; y < de.y; y++)
				{
					// 获取贴图的 Y 坐标
					if (y == ds.y)
						printf("DRAWING sprite.\n");
					int tex_y = (int)tex_pos & (sprt.height - 1);
					tex_pos += step;
					// 获取贴图颜色
					int color = get_color_at(&sprt, tex_x, tex_y);
					// 忽略透明颜色（比如：颜色为0或某个mask值）(color & 0xFFFFFF) != 0
					if (color != 0x432600)
						put_pixel(&sc->img, (t_point){st, y, color});
				}
			}
		}
		else
			printf("SKIP: out of screen range\n");
	}
}

static double sprite_dist(t_cam *player, t_point	po, t_point	s, int	n)
{
	double	ox;
	double	oy;
	double	dis;
	int		gr;
	
	ox = player->ray2->offx;
	oy = player->ray2->offy;
	gr = player->ray2->grid;
	if (n == 1)
		return (s.x * gr -(po.x * gr + ox));
	else if (n == 2)
		return (s.y * gr -(po.y * gr + oy));
	else  // n = 0
	{
		dis = dist(s.x * gr, s.y * gr, po.x * gr + ox, po.y * gr + oy);
		return (dis);
	}
}

static void	sort_sprites(t_cam	*player, t_point p, int *order)
{
	int	i;
	int	j;
	int max;
	t_point	*spr;
	int tmp_order;

	i = 0;
	spr = player->sprites;
	while (i < player->nb_sprites - 1) 
	{
		max = i;
		j = i + 1;
		while (j < player->nb_sprites)
		{
			if (sprite_dist(player, p, spr[j], 0) > sprite_dist(player, p, spr[max], 0))
				max = j;
			j++;
		}
		if (max != i)
		{
			tmp_order = order[i];
			order[i] = order[max];
			order[max] = tmp_order;
		}
		i++;
	}
	i = 0;
	while (i < player->nb_sprites)
		printf("sprite order: %d\n", order[i++]);
}

static void sort_draw_sprites(t_scene *scene, t_point p)
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

static void	get_render_height(t_raycastor	*cast, t_scene *scene, t_ray_hit	hit)
{			
	double	ca;
	double	no_fisheye_dist;
	double	proj_plane_dist;
	
	ca = normalize_angle(scene->tmap->player->p_angle - cast->ra);
	no_fisheye_dist = hit.dist * cos(ca);
	proj_plane_dist = (WIDTH / 2.0) / tan(scene->tmap->player->fov / 2.0);
	cast->rend_h = (int)((cast->grid / no_fisheye_dist) * proj_plane_dist);
	cast->ori_rend_h = cast->rend_h;
	if (cast->rend_h > HEIGHT)
		cast->rend_h = HEIGHT;
	//cast->ori_off = (HEIGHT - cast->rend_h) / 2;
	cast->ori_off = (HEIGHT - cast->rend_h) / 2;
	//cast->draw_off = floor((1.0 - scene->tmap->player->pitch) * cast->ori_off);
	cast->draw_off = cast->ori_off;
}

static void	draw_wall_column(t_raycastor	*cast, t_scene *scene, t_ray_hit	hit)
{
	int	i;
	int	start;
	int	j;

	get_render_height(cast, scene, hit);
	start = WIDTH - cast->this_r * cast->pix_ray - 1;
	i = start;
	cast->step_tt = (double)hit.tt_pic.height / cast->ori_rend_h;
	while (i > start - cast->pix_ray)
	{
		j = 0;
		while (j < cast->draw_off)
		{
			put_pixel(&scene->img, (t_point){i, j, scene->tmap->color_c});
			j++;
		}
		texture_3d(scene, (t_point){i, j, PURPLE}, cast, hit);
		j += cast->rend_h;
		while (j < HEIGHT)
		{
			put_pixel(&scene->img, (t_point){i, j, scene->tmap->color_f});
			j++;
		}
		i--;
	}	
}

static void	draw_door_height(t_raycastor	*cast, t_scene *scene, t_ray_hit	hit)
{
	int	i;
	int	start;
	int	j;

	get_render_height(cast, scene, hit);
	start = WIDTH - cast->this_r * cast->pix_ray - 1;
	i = start;
	cast->step_tt = (double)hit.tt_pic.height / cast->ori_rend_h;
	while (i > start - cast->pix_ray)
	{
		j = cast->draw_off;
		texture_3d(scene, (t_point){i, j, PURPLE}, cast, hit);
		i--;
	}	
}
static int sprite_already_saved(t_cam *player, int x, int y)
{
	int i;

	i = 0;
	while (i < player->nb_sprites)
	{
		if (player->sprites[i].x == x && player->sprites[i].y == y)
			return (1);
		i++;
	}
	return (0);
}

static void	save_sprite_status(t_scene *scene, t_ray_hit	hit)
{
	int	i;
	t_cam	*player;

	player = scene->tmap->player;
	i = player->nb_sprites;
	if (i >= MAX_HITS_PER_RAY)
		return ;
	if (sprite_already_saved(player, hit.hit_map.x, hit.hit_map.y))
		return ;
	printf("save sprite now. i is: %d\n", i);
	player->sprites[i].x = hit.hit_map.x;
	player->sprites[i].y = hit.hit_map.y;
	player->nb_sprites++;
}

void	get_correct_dist(t_raycastor	*cast)
{
    if (cast->disV < cast->disH)
	{
		cast->final_x = cast->vx;
		cast->final_y = cast->vy;
		cast->hit = cast->vhit;
		cast->hit_dir = cast->vhit_dir;		
		cast->dist = cast->disV;
	}
	else
	{
		cast->final_x = cast->hx;
		cast->final_y = cast->hy;
		cast->hit = cast->hhit;
		cast->hit_dir = cast->hhit_dir;	
		cast->dist = cast->disH;
	}
}

/* static void print_hit_points(t_ray	*hitps, t_raycastor	*cast, t_scene *scene)
{
	int	i;

	i = 0;
	while (i < hitps->hit_count)
	{
		printf("**------------------------------------------****\n");
		printf("oooooooooNUM: %d, ray : %d\n", i + 1, cast->this_r);
		printf("player at [x, y]: [%d, %d]\n", scene->tmap->player->posx, scene->tmap->player->posy);
		if (hitps->hits[i].hit_type == SPRITE)
		{
			printf("*************************** *****************\n");
			printf("**                                       ****\n");
			printf("**        SPRITE !!!                     ****\n");
			printf("**                                       ****\n");
			printf("**                                       ****\n");
			printf("**                                       ****\n");
			printf("**                                       ****\n");
			printf("*************************** *****************\n");
			printf("hit type: %d, hit dir: %d\n", hitps->hits[i].hit_type, hitps->hits[i].hit_dir);
			printf("distance : %f, is vertical? %d\n", hitps->hits[i].dist, hitps->hits[i].vert_side);
			printf("hit map (x, y): [%d, %d]\n", hitps->hits[i].hit_map.x, hitps->hits[i].hit_map.y);
			printf("hit pix (rx, ry): [%f, %f]\n", hitps->hits[i].hit_x, hitps->hits[i].hit_y);
			printf("*************************** *****************\n");
			exit (1);
		}		
		printf("hit type: %d, hit dir: %d\n", hitps->hits[i].hit_type, hitps->hits[i].hit_dir);
		printf("distance : %f, is vertical? %d\n", hitps->hits[i].dist, hitps->hits[i].vert_side);
		printf("hit map (x, y): [%d, %d]\n", hitps->hits[i].hit_map.x, hitps->hits[i].hit_map.y);
		printf("hit pix (rx, ry): [%f, %f]\n", hitps->hits[i].hit_x, hitps->hits[i].hit_y);
		i++;		
	}
} */

static void draw_pix_column(t_ray	*hitps, t_raycastor	*cast, t_scene *scene)
{
	int		i;
	t_hit	h;
	int		dst;

	sort_hit_points(hitps);
	// for test
	//print_hit_points(hitps, cast, scene);
	//get_zbuffer();//position of : wall or nearest closed(closed, opening, closing) door
 	i = hitps->hit_count - 1;
	while (i >= 0)
	{
		h = hitps->hits[i].hit_type;
		if (i == hitps->hit_count - 1)
			scene->tmap->player->zbuffer[cast->this_r] = hitps->hits[i].dist;
		if (h == NORTH || h == SOUTH || h == EAST || h == WEST)
		{
			draw_wall_column(cast, scene, hitps->hits[i]);			
		}
		else if (h == DOOR)
		{
			draw_door_height(cast, scene, hitps->hits[i]);
			if (i - 1 >= 0 && hitps->hits[i - 1].hit_type == SPRITE)
			{
				dst = scene->tmap->door_state[hitps->hits[i].hit_map.y][hitps->hits[i].hit_map.x];
				if (dst == DOOR_CLOSED || dst == DOOR_OPENING || dst == DOOR_CLOSING)
				{				
					scene->tmap->player->zbuffer[cast->this_r] = hitps->hits[i].dist;								
				}
			}
		}
		else if (h == SPRITE)
		{
			// if (i == 0)
			// 	scene->tmap->player->zbuffer[cast->this_r] = 1.0;
			// else if (i == 1)
			// {
			// 	hp = hitps->hits[0].hit_map;
			// 	if (hitps->hits[0].hit_type == DOOR && scene->tmap->door_state[hp.y][hp.x] == DOOR_OPEN)
			// 		scene->tmap->player->zbuffer[cast->this_r] = 1.0;
			// }
			save_sprite_status(scene, hitps->hits[i]);
		}
		i--;
	}
}

static void dda_raycasting_3d(t_raycastor	*cast, t_scene *s, int r, t_point p)
{
    double	off_r;
	int		depth;
	int		n;
	t_ray	hitps;


    n = s->tmap->player->ray_nb;
    off_r = ((double)r / (n - 1)) * cast->fov - (cast->fov / 2.0);
    cast->ra = normalize_angle(s->tmap->player->p_angle + off_r);
	cast->this_r = r;
    cast->dirx = cos(cast->ra);
    cast->diry = sin(cast->ra);
	cast->p = p;
	hitps.hit_count = 0;
	hitps.distW = 0.0;
	//
	init_raycastor(p, cast);
	intersect_v(cast, p, &depth);
	get_hit_v(cast, s, &depth, &hitps);
	//init_raycastor(p, cast);
	
	intersect_h(cast, p, &depth);
	get_hit_h(cast, s, &depth, &hitps);
	//
	draw_pix_column(&hitps, cast, s);
}

void	draw_3d_scene(t_scene *scene, t_point p, int grid, t_point	off)
{
	t_raycastor	*cast;
	int		r;
	int		n;
    
	cast = scene->tmap->player->ray2;
	cast->ra = scene->tmap->player->p_angle;
	cast->fov = scene->tmap->player->fov;
	cast->dof = fmax(scene->tmap->count.map_lines, scene->tmap->count.map_width);
	cast->grid = grid;
	r = 0;
	p.x -= off.x;
	p.y -= off.y;
	cast->offset.x = off.x;
	cast->offset.y = off.y;
	n = scene->tmap->player->ray_nb;
	cast->pix_ray = WIDTH / scene->tmap->player->ray_nb;
	clear_zbuffer_sprites(scene->tmap->player);
	//r = 581;
	//n = 583;
	while (r < n)
	{
		dda_raycasting_3d(cast, scene, r, p);
		r++;
	}
	sort_draw_sprites(scene, p);
}
