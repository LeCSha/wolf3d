#include "doom.h"

int	reload_ammo(t_env *env)
{
	int	*cur_max;
	int	*cur;
	int	*mag;
	int	tmp;

	cur_max = &env->player.inventory.current->ammo_curr_max;
	cur = &env->player.inventory.current->ammo_current;
	mag = &env->player.inventory.current->ammo_magazine;
	tmp = *cur_max - *cur;
	*cur += *mag >= tmp ? tmp : *mag;
	*mag -= *mag >= tmp ? tmp : *mag;
	return (0);
}

int	load_weapon(t_env *env)
{
	t_weapon	*wpn;

	wpn = env->player.inventory.current;
	if (wpn->ammo_magazine && wpn->ammo_current < wpn->ammo_curr_max)
		env->player.actions.is_loading = 1;
	SDL_FlushEvent(SDL_KEYDOWN | SDL_KEYUP);
	return (0);
}

int	put_gun_shoot(t_env *env, int frame)
{
	t_weapon	*weapon;

	weapon = env->player.inventory.current;
	frame /= 2.5;
	if (frame < weapon->time_shoot)
		put_gun(env, weapon->sprite_shoot[frame]);
	else
		env->player.actions.is_shooting = 0;
	return (1);
}

int	put_gun_load(t_env *env, int frame)
{
	t_weapon	*weapon;

	weapon = env->player.inventory.current;
	frame /= 2.5;
	if (frame < weapon->time_reload - 1)
		put_gun(env, weapon->sprite_reload[frame]);
	else
		env->player.actions.is_loading = 0;
	if (frame == (int)(weapon->time_reload / 2))
		reload_ammo(env);
	return (1);
}

int	put_gun(t_env *env, SDL_Surface *sprite)
{
	int x;
	int y;

	x = W - sprite->w;
	y = H - sprite->h;
	if (x < 0 || y < 0)
		put_img_inv(env, sprite, (t_edge){{0, 0}, {W - W / 16, H}}, (t_edge){{0, 0}, {0, 0}});
	else
		draw_img(env, (t_edge){{x, y}, {W, H}},
		sprite,
		(t_ixy){100, 0});
	return (1);
}