/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarck <lmarck@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:22:52 by lmarck            #+#    #+#             */
/*   Updated: 2025/02/10 21:10:33 by lmarck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_press_hook(int keycode, void *param)
{
	t_mlx_params	*p;

	p = (t_mlx_params *) param;
	if (keycode == ESC_KEY)
		close_window(p);
	else if (keycode == Q_KEY)
		p->map.ry -= 0.05f;
	else if (keycode == A_KEY)
		p->map.ry += 0.05f;
	else if (keycode == W_KEY)
		p->map.rx -= 0.05f;
	else if (keycode == S_KEY)
		p->map.rx += 0.05f;
	else if (keycode == E_KEY)
		p->map.rz -= 0.05f;
	else if (keycode == D_KEY)
		p->map.rz += 0.05f;
	else if (keycode == PLUS_KEY)
		p->map.h_scale = p->map.h_scale * 1.1f;
	else if (keycode == MINUS_KEY)
		p->map.h_scale = p->map.h_scale * 0.9f;
	extra_press_hook(keycode, param);
	redraw(p);
	return (0);
}

int	extra_press_hook(int keycode, void *param)
{
	t_mlx_params	*p;

	p = (t_mlx_params *) param;
	if (keycode == ARROW_DOWN)
		p->ty = p->ty + 10;
	else if (keycode == ARROW_UP)
		p->ty = p->ty - 10;
	else if (keycode == ARROW_LEFT)
		p->tx = p->tx - 10;
	else if (keycode == ARROW_RIGHT)
		p->tx = p->tx + 10;
	else if (keycode == SPACE_KEY)
	{
		p->tx = 0;
		p->ty = 0;
		p->zoom = 1;
		p->map.rx = 0.61548;
		p->map.ry = -0.785398;
		p->map.rz = 0;
	}
	else if (keycode == T_KEY)
		topview(p);
	return (0);
}

void	topview(t_mlx_params *p)
{
	p->map.rx = 0;
	p->map.ry = 0;
	p->map.rz = 1.5708;
}

int	mouse_press_hook(int button, int x, int y, void *param)
{
	t_mlx_params	*p;

	p = (t_mlx_params *)param;
	(void)x;
	(void)y;
	if (button == SCROLL_UP)
		p->zoom = p->zoom * 1.1f;
	else if (button == SCROLL_DOWN)
		p->zoom = p->zoom * 0.9f;
	redraw(p);
	return (0);
}
