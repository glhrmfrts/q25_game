/*
==============================================================================

SOLDIER

==============================================================================
*/

#include "g_local.h"
#include "m_soldier.h"

//ROGUE
#define RUN_SHOOT		1
#define CHECK_TARGET	1
//ROGUE

static int	sound_idle;
static int	sound_sight1;
static int	sound_sight2;
static int	sound_cock;
static int	sound_pain_light;
static int	sound_pain;
static int	sound_pain_ss;
static int	sound_death_light;
static int	sound_death;
static int	sound_death_ss;
// Knightmare- added separate sounds for ripper, hyperblaster and laser soldiers
static int	h_sound_idle;
static int	h_sound_sight1;
static int	h_sound_sight2;
static int	h_sound_cock;
static int	h_sound_pain_ripper;
static int	h_sound_pain_hypergun;
static int	h_sound_pain_lasergun;
static int	h_sound_death_ripper;
static int	h_sound_death_hypergun;
static int	h_sound_death_lasergun;
static int	h_sound_hypergun_loop = 0;
static int	h_sound_hypergun_spindown = 0;
static int	h_sound_lasergun_fire = 0;

static int	q25_sound_idle;
static int	q25_sound_sight1;
static int	q25_sound_sight2;
static int	q25_sound_cock;
static int	q25_sound_pain;
static int	q25_sound_death;

void soldier_duck_up (edict_t *self);

void soldier_start_charge (edict_t *self)
{
	self->monsterinfo.aiflags |= AI_CHARGING;
}

void soldier_stop_charge (edict_t *self)
{
	self->monsterinfo.aiflags &= ~AI_CHARGING;
}

void soldier_idle (edict_t *self)
{
	if (!(self->spawnflags & SF_MONSTER_AMBUSH))
	{
		if (random() > 0.8)
			gi.sound (self, CHAN_VOICE, sound_idle, 1, ATTN_IDLE, 0);
	}
}

void soldier_cock (edict_t *self)
{
	if (self->s.frame == FRAME_stand322)
		gi.sound (self, CHAN_WEAPON, sound_cock, 1, ATTN_IDLE, 0);
	else
		gi.sound (self, CHAN_WEAPON, sound_cock, 1, ATTN_NORM, 0);
}


// STAND

void soldier_stand (edict_t *self);

mframe_t soldier_frames_stand1 [] =
{
	ai_stand, 0, soldier_idle,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,

	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,

	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL
};
mmove_t soldier_move_stand1 = {FRAME_stand101, FRAME_stand130, soldier_frames_stand1, soldier_stand};

mframe_t soldier_frames_stand3 [] =
{
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,

	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,

	ai_stand, 0, NULL,
	ai_stand, 0, soldier_cock,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,

	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL
};
mmove_t soldier_move_stand3 = {FRAME_stand301, FRAME_stand339, soldier_frames_stand3, soldier_stand};

#if 0
mframe_t soldier_frames_stand4 [] =
{
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,

	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,

	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,

	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,

	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 4, NULL,
	ai_stand, 1, NULL,
	ai_stand, -1, NULL,
	ai_stand, -2, NULL,

	ai_stand, 0, NULL,
	ai_stand, 0, NULL
};
//mmove_t soldier_move_stand4 = {FRAME_stand401, FRAME_stand452, soldier_frames_stand4, NULL};
#endif

void soldier_stand (edict_t *self)
{
	if ((self->monsterinfo.currentmove == &soldier_move_stand3) || (random() < 0.8))
		self->monsterinfo.currentmove = &soldier_move_stand1;
	else
		self->monsterinfo.currentmove = &soldier_move_stand3;
}


//
// WALK
//

void soldier_walk1_random (edict_t *self)
{
	if (random() > 0.1)
		self->monsterinfo.nextframe = FRAME_walk101;
}

mframe_t soldier_frames_walk1 [] =
{
	ai_walk, 3,  NULL,
	ai_walk, 6,  NULL,
	ai_walk, 2,  NULL,
	ai_walk, 2,  NULL,
	ai_walk, 2,  NULL,
	ai_walk, 1,  NULL,
	ai_walk, 6,  NULL,
	ai_walk, 5,  NULL,
	ai_walk, 3,  NULL,
	ai_walk, -1, soldier_walk1_random,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL
};
mmove_t soldier_move_walk1 = {FRAME_walk101, FRAME_walk133, soldier_frames_walk1, NULL};

mframe_t soldier_frames_walk2 [] =
{
	ai_walk, 4,  NULL,
	ai_walk, 4,  NULL,
	ai_walk, 9,  NULL,
	ai_walk, 8,  NULL,
	ai_walk, 5,  NULL,
	ai_walk, 1,  NULL,
	ai_walk, 3,  NULL,
	ai_walk, 7,  NULL,
	ai_walk, 6,  NULL,
	ai_walk, 7,  NULL
};
mmove_t soldier_move_walk2 = {FRAME_walk209, FRAME_walk218, soldier_frames_walk2, NULL};

void soldier_walk (edict_t *self)
{
	if (random() < 0.5)
		self->monsterinfo.currentmove = &soldier_move_walk1;
	else
		self->monsterinfo.currentmove = &soldier_move_walk2;
}


//
// RUN
//

void soldier_run (edict_t *self);

mframe_t soldier_frames_start_run [] =
{
	ai_run, 7,  NULL,
	ai_run, 5,  NULL
};
mmove_t soldier_move_start_run = {FRAME_run01, FRAME_run02, soldier_frames_start_run, soldier_run};

#ifdef RUN_SHOOT
void soldier_fire (edict_t *self, int);

void soldier_fire_run (edict_t *self)
{
//	if ( ((self->s.skinnum % 6) <= 1) && (self->enemy) && visible(self, self->enemy) )
	if ( (self->skinnum <= 1) && (self->enemy) && visible(self, self->enemy) )
	{
		soldier_fire(self, 0);
	}
}
#endif

mframe_t soldier_frames_run [] =
{
	ai_run, 10, NULL,
	ai_run, 11, monster_done_dodge,
	ai_run, 11, NULL,
	ai_run, 16, NULL,
	ai_run, 10, NULL,
	ai_run, 15, monster_done_dodge
};

mmove_t soldier_move_run = {FRAME_run03, FRAME_run08, soldier_frames_run, NULL};

void soldier_run (edict_t *self)
{
	monster_done_dodge (self);

	if (self->monsterinfo.aiflags & AI_STAND_GROUND)
	{
		self->monsterinfo.currentmove = &soldier_move_stand1;
		return;
	}

	if (self->monsterinfo.currentmove == &soldier_move_walk1 ||
		self->monsterinfo.currentmove == &soldier_move_walk2 ||
		self->monsterinfo.currentmove == &soldier_move_start_run)
	{
		self->monsterinfo.currentmove = &soldier_move_run;
	}
	else
	{
		self->monsterinfo.currentmove = &soldier_move_start_run;
	}
}


//
// JUMP
//

mframe_t soldier_frames_jump [] =
{
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL
};
mmove_t soldier_move_jump = { FRAME_run01, FRAME_run08, soldier_frames_jump, soldier_run };

void soldier_jump (edict_t *self)
{
	self->monsterinfo.currentmove = &soldier_move_jump;
}


//
// PAIN
//

mframe_t soldier_frames_pain1 [] =
{
	ai_move, -3, NULL,
	ai_move, 4,  NULL,
	ai_move, 1,  NULL,
	ai_move, 1,  NULL,
	ai_move, 0,  NULL
};
mmove_t soldier_move_pain1 = {FRAME_pain101, FRAME_pain105, soldier_frames_pain1, soldier_run};

mframe_t soldier_frames_pain2 [] =
{
	ai_move, -13, NULL,
	ai_move, -1,  NULL,
	ai_move, 2,   NULL,
	ai_move, 4,   NULL,
	ai_move, 2,   NULL,
	ai_move, 3,   NULL,
	ai_move, 2,   NULL
};
mmove_t soldier_move_pain2 = {FRAME_pain201, FRAME_pain207, soldier_frames_pain2, soldier_run};

mframe_t soldier_frames_pain3 [] =
{
	ai_move, -8, NULL,
	ai_move, 10, NULL,
	ai_move, -4, NULL,
	ai_move, -1, NULL,
	ai_move, -3, NULL,
	ai_move, 0,  NULL,
	ai_move, 3,  NULL,
	ai_move, 0,  NULL,
	ai_move, 0,  NULL,
	ai_move, 0,  NULL,
	ai_move, 0,  NULL,
	ai_move, 1,  NULL,
	ai_move, 0,  NULL,
	ai_move, 1,  NULL,
	ai_move, 2,  NULL,
	ai_move, 4,  NULL,
	ai_move, 3,  NULL,
	ai_move, 2,  NULL
};
mmove_t soldier_move_pain3 = {FRAME_pain301, FRAME_pain318, soldier_frames_pain3, soldier_run};

mframe_t soldier_frames_pain4 [] =
{
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, -10, NULL,
	ai_move, -6,  NULL,
	ai_move, 8,   NULL,
	ai_move, 4,   NULL,
	ai_move, 1,   NULL,
	ai_move, 0,   NULL,
	ai_move, 2,   NULL,
	ai_move, 5,   NULL,
	ai_move, 2,   NULL,
	ai_move, -1,  NULL,
	ai_move, -1,  NULL,
	ai_move, 3,   NULL,
	ai_move, 2,   NULL,
	ai_move, 0,   NULL
};
mmove_t soldier_move_pain4 = {FRAME_pain401, FRAME_pain417, soldier_frames_pain4, soldier_run};


void soldier_pain (edict_t *self, edict_t *other, float kick, int damage)
{
	float	r;
	int		n;

	if (self->health < (self->max_health / 2))
		self->s.skinnum |= 1;

	monster_done_dodge (self);
	soldier_stop_charge(self);

	// if we're blind firing, this needs to be turned off here
	self->monsterinfo.aiflags &= ~AI_MANUAL_STEERING;

	if (level.time < self->pain_debounce_time)
	{
		if ((self->velocity[2] > 100) && ( (self->monsterinfo.currentmove == &soldier_move_pain1) || (self->monsterinfo.currentmove == &soldier_move_pain2) || (self->monsterinfo.currentmove == &soldier_move_pain3)))
		{
			// PMM - clear duck flag
			if (self->monsterinfo.aiflags & AI_DUCKED)
				monster_duck_up(self);
			self->monsterinfo.currentmove = &soldier_move_pain4;
		}
		return;
	}

	self->pain_debounce_time = level.time + 3;

//	n = self->s.skinnum | 1;
	n = self->skinnum | 1;
	if (n == 1)
		gi.sound (self, CHAN_VOICE, sound_pain_light, 1, ATTN_NORM, 0);
	else if (n == 3)
		gi.sound (self, CHAN_VOICE, sound_pain, 1, ATTN_NORM, 0);
	else
		gi.sound (self, CHAN_VOICE, sound_pain_ss, 1, ATTN_NORM, 0);

	if (self->velocity[2] > 100)
	{
		// PMM - clear duck flag
		if (self->monsterinfo.aiflags & AI_DUCKED)
			monster_duck_up(self);
		self->monsterinfo.currentmove = &soldier_move_pain4;
//		self->monsterinfo.pausetime = 0;
		return;
	}

	if (skill->value == 3)
		return;		// no pain anims in nightmare

	r = random();

	if (r < 0.33)
		self->monsterinfo.currentmove = &soldier_move_pain1;
	else if (r < 0.66)
		self->monsterinfo.currentmove = &soldier_move_pain2;
	else
		self->monsterinfo.currentmove = &soldier_move_pain3;

	// PMM - clear duck flag
	if (self->monsterinfo.aiflags & AI_DUCKED)
		monster_duck_up(self);
//	self->monsterinfo.pausetime = 0;

}


//
// ATTACK
//

static int blaster_flash [] = {MZ2_SOLDIER_BLASTER_1, MZ2_SOLDIER_BLASTER_2, MZ2_SOLDIER_BLASTER_3, MZ2_SOLDIER_BLASTER_4, MZ2_SOLDIER_BLASTER_5, MZ2_SOLDIER_BLASTER_6, MZ2_SOLDIER_BLASTER_7, MZ2_SOLDIER_BLASTER_8};
static int shotgun_flash [] = {MZ2_SOLDIER_SHOTGUN_1, MZ2_SOLDIER_SHOTGUN_2, MZ2_SOLDIER_SHOTGUN_3, MZ2_SOLDIER_SHOTGUN_4, MZ2_SOLDIER_SHOTGUN_5, MZ2_SOLDIER_SHOTGUN_6, MZ2_SOLDIER_SHOTGUN_7, MZ2_SOLDIER_SHOTGUN_8};
static int machinegun_flash [] = {MZ2_SOLDIER_MACHINEGUN_1, MZ2_SOLDIER_MACHINEGUN_2, MZ2_SOLDIER_MACHINEGUN_3, MZ2_SOLDIER_MACHINEGUN_4, MZ2_SOLDIER_MACHINEGUN_5, MZ2_SOLDIER_MACHINEGUN_6, MZ2_SOLDIER_MACHINEGUN_7, MZ2_SOLDIER_MACHINEGUN_8};
#ifdef KMQUAKE2_ENGINE_MOD
static int plasma_rifle_flash [] = {MZ2_SOLDIER_PLASMA_RIFLE_1, MZ2_SOLDIER_PLASMA_RIFLE_2, MZ2_SOLDIER_PLASMA_RIFLE_3, MZ2_SOLDIER_PLASMA_RIFLE_4, MZ2_SOLDIER_PLASMA_RIFLE_5, MZ2_SOLDIER_PLASMA_RIFLE_6, MZ2_SOLDIER_PLASMA_RIFLE_7, MZ2_SOLDIER_PLASMA_RIFLE_8};
static int ionripper_flash [] = {MZ2_SOLDIER_IONRIPPER_1, MZ2_SOLDIER_IONRIPPER_2, MZ2_SOLDIER_IONRIPPER_3, MZ2_SOLDIER_IONRIPPER_4, MZ2_SOLDIER_IONRIPPER_5, MZ2_SOLDIER_IONRIPPER_6, MZ2_SOLDIER_IONRIPPER_7, MZ2_SOLDIER_IONRIPPER_8};
static int hyperblaster_flash [] = {MZ2_SOLDIER_HYPERBLASTER_1, MZ2_SOLDIER_HYPERBLASTER_2, MZ2_SOLDIER_HYPERBLASTER_3, MZ2_SOLDIER_HYPERBLASTER_4, MZ2_SOLDIER_HYPERBLASTER_5, MZ2_SOLDIER_HYPERBLASTER_6, MZ2_SOLDIER_HYPERBLASTER_7, MZ2_SOLDIER_HYPERBLASTER_8};
#endif	// KMQUAKE2_ENGINE_MOD

//void soldier_fire (edict_t *self, int flash_number)  PMM
void soldier_fire (edict_t *self, int in_flash_number)
{
	vec3_t	start;
	vec3_t	forward, right, up;
	vec3_t	aim;
	vec3_t	dir;
	vec3_t	end;
	float	r, u;
	int		flash_index;
	int		flash_number;
#ifdef RUN_SHOOT
	vec3_t	aim_norm;
	float	angle;
#endif
#ifdef CHECK_TARGET
	trace_t	tr;
	vec3_t aim_good;
#endif

	if ((!self->enemy) || (!self->enemy->inuse))
	{
		self->monsterinfo.aiflags &= ~AI_HOLD_FRAME;
		return;
	}

	if (in_flash_number < 0)
	{
		flash_number = -1 * in_flash_number;
	}
	else
		flash_number = in_flash_number;

//	if ((self->s.skinnum % 6) < 2)
	if (self->skinnum < 2)
		flash_index = blaster_flash[flash_number];
//	else if ((self->s.skinnum % 6) < 4)
	else if (self->skinnum < 4)
		flash_index = shotgun_flash[flash_number];
	else if (self->skinnum < 6)
		flash_index = machinegun_flash[flash_number];
	else // if (self->skinnum < 8)
#ifdef KMQUAKE2_ENGINE_MOD
		flash_index = plasma_rifle_flash[flash_number];
#else
		flash_index = blaster_flash[flash_number];
#endif	// KMQUAKE2_ENGINE_MOD

	AngleVectors (self->s.angles, forward, right, NULL);
	G_ProjectSource (self->s.origin, monster_flash_offset[flash_index], forward, right, start);

	if (flash_number == 5 || flash_number == 6) // he's dead
	{
		VectorCopy (forward, aim);
	}
	else
	{
		VectorCopy (self->enemy->s.origin, end);
		end[2] += self->enemy->viewheight;

		// Lazarus fog reduction of accuracy
		if (self->monsterinfo.visibility < FOG_CANSEEGOOD)
		{
			end[0] += crandom() * 640 * (FOG_CANSEEGOOD - self->monsterinfo.visibility);
			end[1] += crandom() * 640 * (FOG_CANSEEGOOD - self->monsterinfo.visibility);
			end[2] += crandom() * 320 * (FOG_CANSEEGOOD - self->monsterinfo.visibility);
		}

		VectorSubtract (end, start, aim);
#ifdef CHECK_TARGET
		VectorCopy (end, aim_good);
#endif
#ifdef RUN_SHOOT
		//PMM
		if (in_flash_number < 0)
		{
			VectorCopy (aim, aim_norm);
			VectorNormalize (aim_norm);
			angle = DotProduct (aim_norm, forward);
			//gi.dprintf ("Dot Product:  %f", DotProduct (aim_norm, forward));
			if (angle < 0.9)  // ~25 degree angle
			{
			//	if (g_showlogic && g_showlogic->value)
			//		gi.dprintf (" not firing due to bad dotprod %f\n", angle);
				return;
			}
		/*	else
			{
				if (g_showlogic && g_showlogic->value)
					gi.dprintf (" firing:  dotprod = %f\n", angle);
			} */
		}
		//-PMM
#endif
		vectoangles (aim, dir);
		AngleVectors (dir, forward, right, up);
		
		if (skill->value < 2)
		{
			r = crandom()*1000;
			u = crandom()*500;
		}
		else
		{
			r = crandom()*500;
			u = crandom()*250;
		}
		// Knightmare- adjust spread for expanded world size
#ifdef KMQUAKE2_ENGINE_MOD
		r *= (WORLD_SIZE / 8192);
		u *= (WORLD_SIZE / 8192);
#endif
		VectorMA (start, WORLD_SIZE, forward, end);	// was 8192
		VectorMA (end, r, right, end);
		VectorMA (end, u, up, end);

		VectorSubtract (end, start, aim);
		VectorNormalize (aim);
	}
#ifdef CHECK_TARGET
	if (!(flash_number == 5 || flash_number == 6)) // he's dead
	{
		tr = gi.trace (start, NULL, NULL, aim_good, self, MASK_SHOT);
		if ((tr.ent != self->enemy) && (tr.ent != world))
		{
		//	if (g_showlogic && g_showlogic->value)
		//		gi.dprintf ("infantry shot aborted due to bad target\n");
			return;
		}
	}
#endif

//	if ((self->s.skinnum % 6) <= 1)
	if (self->skinnum <= 1)
	{
		monster_fire_blaster (self, start, aim, 5, 600, flash_index, EF_BLASTER, BLASTER_ORANGE);
	}
//	else if ((self->s.skinnum % 6) <= 3)
	else if (self->skinnum <= 3)
	{
		monster_fire_shotgun (self, start, aim, 2, 1, DEFAULT_SHOTGUN_HSPREAD, DEFAULT_SHOTGUN_VSPREAD, DEFAULT_SHOTGUN_COUNT, flash_index);
	}
	else if (self->skinnum <= 5)
	{
		// PMM - changed to wait from pausetime to not interfere with dodge code
		if (!(self->monsterinfo.aiflags & AI_HOLD_FRAME))
			self->wait = level.time + (3 + rand() % 8) * FRAMETIME;

		monster_fire_bullet (self, start, aim, 2, 4, DEFAULT_BULLET_HSPREAD, DEFAULT_BULLET_VSPREAD, flash_index);

		if (level.time >= self->wait)
			self->monsterinfo.aiflags &= ~AI_HOLD_FRAME;
		else
			self->monsterinfo.aiflags |= AI_HOLD_FRAME;
	}
	else // if (self->skinnum <= 7)
	{
		if (self->moreflags & FL2_WEAPON_ALT)
			monster_fire_plasma_rifle (self, start, aim, PLASMA_SPREAD_DAMAGE, PLASMA_SPREAD_SPEED, flash_index, true);
		else
			monster_fire_plasma_rifle (self, start, aim, PLASMA_BOUNCE_DAMAGE, PLASMA_BOUNCE_SPEED, flash_index, false);
	}
}

// ATTACK1 (blaster/shotgun)

void soldier_fire1 (edict_t *self)
{
	soldier_fire (self, 0);
}

void soldier_attack1_refire1 (edict_t *self)
{
	// PMM - blindfire
	if (self->monsterinfo.aiflags & AI_MANUAL_STEERING)
	{
		self->monsterinfo.aiflags &= ~AI_MANUAL_STEERING;
		return;
	}
	// pmm

	if (!self->enemy)
		return;

//	if ((self->s.skinnum % 6) > 1)
	if (self->skinnum > 1)
		return;

	if (self->enemy->health <= 0)
		return;

	if ( ((skill->value == 3) && (random() < 0.5)) || (range(self, self->enemy) == RANGE_MELEE) )
		self->monsterinfo.nextframe = FRAME_attak102;
	else
		self->monsterinfo.nextframe = FRAME_attak110;
}

void soldier_attack1_refire2 (edict_t *self)
{
	if (!self->enemy)
		return;

//	if ((self->s.skinnum % 6) < 2)
	if (self->skinnum < 2)
		return;

	if (self->enemy->health <= 0)
		return;

	if ( ((skill->value == 3) && (random() < 0.5)) || (range(self, self->enemy) == RANGE_MELEE) )
		self->monsterinfo.nextframe = FRAME_attak102;
}

mframe_t soldier_frames_attack1 [] =
{
	ai_charge, 0,  NULL,
	ai_charge, 0,  NULL,
	ai_charge, 0,  soldier_fire1,
	ai_charge, 0,  NULL,
	ai_charge, 0,  NULL,
	ai_charge, 0,  soldier_attack1_refire1,
	ai_charge, 0,  NULL,
	ai_charge, 0,  soldier_cock,
	ai_charge, 0,  soldier_attack1_refire2,
	ai_charge, 0,  NULL,
	ai_charge, 0,  NULL,
	ai_charge, 0,  NULL
};
mmove_t soldier_move_attack1 = {FRAME_attak101, FRAME_attak112, soldier_frames_attack1, soldier_run};

// ATTACK2 (blaster/shotgun)

void soldier_fire2 (edict_t *self)
{
	soldier_fire (self, 1);
}

void soldier_attack2_refire1 (edict_t *self)
{
	if (!self->enemy)
		return;

//	if ((self->s.skinnum % 6) > 1)
	if (self->skinnum > 1)
		return;

	if (self->enemy->health <= 0)
		return;

	if ( ((skill->value == 3) && (random() < 0.5)) || (range(self, self->enemy) == RANGE_MELEE) )
		self->monsterinfo.nextframe = FRAME_attak204;
	else
		self->monsterinfo.nextframe = FRAME_attak216;
}

void soldier_attack2_refire2 (edict_t *self)
{
	if (!self->enemy)
		return;

//	if ((self->s.skinnum % 6) < 2)
	if (self->skinnum < 2)
		return;

	if (self->enemy->health <= 0)
		return;

	if ( ((skill->value == 3) && (random() < 0.5)) || (range(self, self->enemy) == RANGE_MELEE) )
		self->monsterinfo.nextframe = FRAME_attak204;
}

mframe_t soldier_frames_attack2 [] =
{
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, soldier_fire2,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, soldier_attack2_refire1,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, soldier_cock,
	ai_charge, 0, NULL,
	ai_charge, 0, soldier_attack2_refire2,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL
};
mmove_t soldier_move_attack2 = {FRAME_attak201, FRAME_attak218, soldier_frames_attack2, soldier_run};

// ATTACK3 (duck and shoot)
/*
void soldier_duck_down (edict_t *self)
{
	if ((g_showlogic) && (g_showlogic->value))
		gi.dprintf ("duck down - %d!\n", self->s.frame);

	self->monsterinfo.aiflags |= AI_DUCKED;
//	self->maxs[2] -= 32;
	self->maxs[2] =  self->monsterinfo.base_height - 32;
	self->takedamage = DAMAGE_YES;
	if (self->monsterinfo.duck_wait_time < level.time)
	{
		if ((g_showlogic) && (g_showlogic->value))
			gi.dprintf ("soldier duck with no time!\n");
		self->monsterinfo.duck_wait_time = level.time + 1;
	}
	gi.linkentity (self);
}

void soldier_duck_up (edict_t *self)
{
	if ((g_showlogic) && (g_showlogic->value))
		gi.dprintf ("duck up - %d!\n", self->s.frame);
	self->monsterinfo.aiflags &= ~AI_DUCKED;
//	self->maxs[2] += 32;
	self->maxs[2] = self->monsterinfo.base_height;
	self->takedamage = DAMAGE_AIM;
	gi.linkentity (self);
}
*/
void soldier_fire3 (edict_t *self)
{
	monster_duck_down (self);
	soldier_fire (self, 2);
}

void soldier_attack3_refire (edict_t *self)
{
	if ((level.time + 0.4) < self->monsterinfo.duck_wait_time)
		self->monsterinfo.nextframe = FRAME_attak303;
}

mframe_t soldier_frames_attack3 [] =
{
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, soldier_fire3,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, soldier_attack3_refire,
	ai_charge, 0, monster_duck_up,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL
};
mmove_t soldier_move_attack3 = {FRAME_attak301, FRAME_attak309, soldier_frames_attack3, soldier_run};

// ATTACK4 (machinegun)

void soldier_fire4 (edict_t *self)
{
	soldier_fire (self, 3);
//
//	if (self->enemy->health <= 0)
//		return;
//
//	if ( ((skill->value == 3) && (random() < 0.5)) || (range(self, self->enemy) == RANGE_MELEE) )
//		self->monsterinfo.nextframe = FRAME_attak402;
}

mframe_t soldier_frames_attack4 [] =
{
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, soldier_fire4,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL
};
mmove_t soldier_move_attack4 = {FRAME_attak401, FRAME_attak406, soldier_frames_attack4, soldier_run};

#if 0
// ATTACK5 (prone)

void soldier_fire5 (edict_t *self)
{
	soldier_fire (self, 4);
}

void soldier_attack5_refire (edict_t *self)
{
	if (!self->enemy)
		return;

	if (self->enemy->health <= 0)
		return;

	if ( ((skill->value == 3) && (random() < 0.5)) || (range(self, self->enemy) == RANGE_MELEE) )
		self->monsterinfo.nextframe = FRAME_attak505;
}

mframe_t soldier_frames_attack5 [] =
{
	ai_charge, 8, NULL,
	ai_charge, 8, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, soldier_fire5,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, soldier_attack5_refire
};
//mmove_t soldier_move_attack5 = {FRAME_attak501, FRAME_attak508, soldier_frames_attack5, soldier_run};
#endif

// ATTACK6 (run & shoot)

void soldier_fire8 (edict_t *self)
{
	soldier_fire (self, -7);
//	self->monsterinfo.aiflags |= AI_HOLD_FRAME;
//	self->monsterinfo.pausetime = level.time + 1000000;
}

void soldier_attack6_refire (edict_t *self)
{
	// PMM - make sure dodge & charge bits are cleared
	monster_done_dodge (self);
	soldier_stop_charge (self);

	if (!self->enemy)
		return;

	if (self->enemy->health <= 0)
		return;

//	if (range(self, self->enemy) < RANGE_MID)
	if (range(self, self->enemy) < RANGE_NEAR)
		return;

	if ((skill->value == 3) || ((random() < (0.25*((float)skill->value)))))
		self->monsterinfo.nextframe = FRAME_runs03;
}

mframe_t soldier_frames_attack6 [] =
{
//	PMM
//	ai_run, 10, NULL,
	ai_run, 10, soldier_start_charge,
	ai_run,  4, NULL,
	ai_run, 12, soldier_fire8,
	ai_run, 11, NULL,
	ai_run, 13, monster_done_dodge,
	ai_run, 18, NULL,
	ai_run, 15, NULL,
	ai_run, 14, NULL,
	ai_run, 11, NULL,
	ai_run,  8, NULL,
	ai_run, 11, NULL,
	ai_run, 12, NULL,
	ai_run, 12, NULL,
	ai_run, 17, soldier_attack6_refire
};
mmove_t soldier_move_attack6 = {FRAME_runs01, FRAME_runs14, soldier_frames_attack6, soldier_run};

void soldier_attack(edict_t *self)
{
	float r, chance;

	monster_done_dodge (self);

	// PMM - blindfire!
	if (self->monsterinfo.attack_state == AS_BLIND)
	{
		// setup shot probabilities
		if (self->monsterinfo.blind_fire_delay < 1.0)
			chance = 1.0;
		else if (self->monsterinfo.blind_fire_delay < 7.5)
			chance = 0.4;
		else
			chance = 0.1;

		r = random();

		// minimum of 2 seconds, plus 0-3, after the shots are done
		self->monsterinfo.blind_fire_delay += 2.1 + 2.0 + random()*3.0;

		// don't shoot at the origin
		if (VectorCompare (self->monsterinfo.blind_fire_target, vec3_origin))
			return;

		// don't shoot if the dice say not to
		if (r > chance)
		{
//			if ((g_showlogic) && (g_showlogic->value))
//				gi.dprintf ("blindfire - NO SHOT\n");
			return;
		}

		// turn on manual steering to signal both manual steering and blindfire
		self->monsterinfo.aiflags |= AI_MANUAL_STEERING;
		self->monsterinfo.currentmove = &soldier_move_attack1;
		self->monsterinfo.attack_finished = level.time + 1.5 + random();
		return;
	}
	// pmm

// PMM - added this so the soldiers now run toward you and shoot instead of just stopping and shooting
//	if ((range(self, self->enemy) >= RANGE_MID) && (r < (skill->value*0.25) && ((self->s.skinnum % 6) <= 3)))

	r = random();

	if ( (!(self->monsterinfo.aiflags & (AI_BLOCKED|AI_STAND_GROUND))) &&
		(range(self, self->enemy) >= RANGE_NEAR) && 
		(r < (skill->value*0.25) && 
	//	((self->s.skinnum % 6) <= 3)) )
		(self->skinnum <= 3)) )
	{
		self->monsterinfo.currentmove = &soldier_move_attack6;
	}
	else
	{
	//	if ((self->s.skinnum % 6) < 4)
		if (self->skinnum < 4)
		{
			if (random() < 0.5)
			{
				self->monsterinfo.currentmove = &soldier_move_attack1;
			}
			else
			{
				self->monsterinfo.currentmove = &soldier_move_attack2;
			}
		}
		else
		{
			self->monsterinfo.currentmove = &soldier_move_attack4;
		}
	}
}


//
// SIGHT
//

void soldier_sight (edict_t *self, edict_t *other)
{
	if (random() < 0.5)
		gi.sound (self, CHAN_VOICE, sound_sight1, 1, ATTN_NORM, 0);
	else
		gi.sound (self, CHAN_VOICE, sound_sight2, 1, ATTN_NORM, 0);

//	if ((skill->value > 0) && (self->enemy) && (range(self, self->enemy) >= RANGE_MID))
	if ((skill->value > 0) && (self->enemy) && (range(self, self->enemy) >= RANGE_NEAR))
	{
//	PMM - don't let machinegunners run & shoot
	//	if ((random() > 0.75) && ((self->s.skinnum % 6) <= 3))
		if ((random() > 0.75) && (self->skinnum <= 3))
		{
		//	if ((self->classname == "monster_soldier_ripper") || (self->classname == "monster_soldier_hypergun") || (self->classname == "monster_soldier_lasergun"))
		//		self->monsterinfo.currentmove = &soldierh_move_attack6;
		//	else
				self->monsterinfo.currentmove = &soldier_move_attack6;
		}
	}
}

//
// DUCK
//
/*
void soldier_duck_hold (edict_t *self)
{
	if (level.time >= self->monsterinfo.duck_wait_time)
		self->monsterinfo.aiflags &= ~AI_HOLD_FRAME;
	else
		self->monsterinfo.aiflags |= AI_HOLD_FRAME;
}
*/
mframe_t soldier_frames_duck [] =
{
	ai_move, 5, monster_duck_down,
	ai_move, -1, monster_duck_hold,
	ai_move, 1,  NULL,
	ai_move, 0,  monster_duck_up,
	ai_move, 5,  NULL
};
mmove_t soldier_move_duck = {FRAME_duck01, FRAME_duck05, soldier_frames_duck, soldier_run};

/*
void soldier_dodge (edict_t *self, edict_t *attacker, float eta, trace_t *tr)
{
//===========
//PMM - rogue rewrite of dodge code.
// lots o' changes in here.  Basically, they now check the tr and see if ducking would help,
// and if it doesn't, they dodge like mad
	float	r = random();
	float	height;

	if ((g_showlogic) && (g_showlogic->value))
	{
		if (self->monsterinfo.aiflags & AI_DODGING)
			gi.dprintf ("dodging - ");
		if (self->monsterinfo.aiflags & AI_DUCKED)
			gi.dprintf ("ducked - ");
	}
	if (!self->enemy)
	{
		self->enemy = attacker;
		FoundTarget (self);
	}

	// PMM - don't bother if it's going to hit anyway; fix for weird in-your-face etas (I was
	// seeing numbers like 13 and 14)
	if ((eta < 0.1) || (eta > 5))
	{
		if ((g_showlogic) && (g_showlogic->value))
			gi.dprintf ("timeout\n");
		return;
	}

	// skill level determination..
	if (r > (0.25*((skill->value)+1)))
	{
		if ((g_showlogic) && (g_showlogic->value))
			gi.dprintf ("skillout\n");
		return;
	}

	// stop charging, since we're going to dodge (somehow) instead
	soldier_stop_charge (self);

	height = self->absmax[2]-32-1;  // the -1 is because the absmax is s.origin + maxs + 1

	// if we're ducking already, or the shot is at our knees
	if ((tr->endpos[2] <= height) || (self->monsterinfo.aiflags & AI_DUCKED))
	{
		vec3_t right, diff;

		// if we're already dodging, just finish the sequence, i.e. don't do anything else
		if (self->monsterinfo.aiflags & AI_DODGING)
		{
			if ((g_showlogic) && (g_showlogic->value))
				gi.dprintf ("already dodging\n");
			return;
		}

		AngleVectors (self->s.angles, NULL, right, NULL);
		VectorSubtract (tr->endpos, self->s.origin, diff);

		if (DotProduct (right, diff) < 0)
		{
			self->monsterinfo.lefty = 1;
//			gi.dprintf ("left\n");
		} else {
//			gi.dprintf ("right\n");
		}
		// if it doesn't sense to duck, try to strafe and shoot
		// we don't want the machine gun guys running & shooting (looks bad)

		// if we are currently ducked, unduck
		if (self->monsterinfo.aiflags & AI_DUCKED)
		{
			if ((g_showlogic) && (g_showlogic->value))
				gi.dprintf ("unducking - ");
			soldier_duck_up(self);
		}

		self->monsterinfo.aiflags |= AI_DODGING;
		self->monsterinfo.attack_state = AS_SLIDING;

	//	else if ((self->s.skinnum % 6) <= 3)
		else if (self->skinnum  <= 3)
		{
			if ((g_showlogic) && (g_showlogic->value))
				gi.dprintf ("shooting back!\n");
			self->monsterinfo.currentmove = &soldier_move_attack6;
		}
		else
		{
			if ((g_showlogic) && (g_showlogic->value))
				gi.dprintf ("strafing away!\n");
			self->monsterinfo.currentmove = &soldier_move_start_run;
		}
		return;
	}

	// if we're here, we're ducking, so clear the dodge bit if it's set

	if ((g_showlogic) && (g_showlogic->value))
		gi.dprintf ("ducking!\n");
	if (skill->value == 0)
	{
		// set this prematurely; it doesn't hurt, and prevents extra iterations
		self->monsterinfo.aiflags |= AI_DUCKED;
		monster_done_dodge (self);
		self->monsterinfo.currentmove = &soldier_move_duck;
		// PMM - stupid dodge
		self->monsterinfo.duck_wait_time = level.time + eta + 1;
		return;
	}
// PMM - since we're only ducking some of the time, this needs to be moved down below
//	self->monsterinfo.duck_wait_time = level.time + eta + 0.3;

	r = random();

	// set this prematurely; it doesn't hurt, and prevents extra iterations
	self->monsterinfo.aiflags |= AI_DUCKED;
	monster_done_dodge (self);

	if (r > (skill->value * 0.33))
	{
		self->monsterinfo.currentmove = &soldier_move_duck;
		self->monsterinfo.duck_wait_time = level.time + eta + (0.1 * (3 - skill->value));
		// has to be done immediately otherwise he can get stuck
		soldier_duck_down(self);
	}
	else
	{
		// has to be done immediately otherwise he can get stuck
		soldier_duck_down(self);
		self->monsterinfo.duck_wait_time = level.time + eta + 1;
		self->monsterinfo.currentmove = &soldier_move_attack3;
		self->monsterinfo.nextframe = FRAME_attak301;
	}
	return;
//PMM
//===========

}
*/
// pmm - blocking code

qboolean soldier_blocked (edict_t *self, float dist)
{
	// don't do anything if you're dodging
	if ((self->monsterinfo.aiflags & AI_DODGING) || (self->monsterinfo.aiflags & AI_DUCKED))
		return false;

	if (blocked_checkshot (self, 0.25 + (0.05 * skill->value) ))
		return true;

//	if (blocked_checkjump (self, dist, 192, 40))
//	{
//		soldier_jump(self);
//		return true;
//	}

	if (blocked_checkplat (self, dist))
		return true;

	return false;
}

//
// DEATH
//

void soldier_fire6 (edict_t *self)
{
	soldier_fire (self, 5);
}

void soldier_fire7 (edict_t *self)
{
	soldier_fire (self, 6);
}

void soldier_dead (edict_t *self)
{
	VectorSet (self->mins, -16, -16, -24);
	VectorSet (self->maxs, 16, 16, -8);
	self->movetype = MOVETYPE_TOSS;
	self->svflags |= SVF_DEADMONSTER;
	self->nextthink = 0;
	gi.linkentity (self);
	M_FlyCheck (self);

	// Lazarus monster fade
	if (world->effects & FX_WORLDSPAWN_CORPSEFADE)
	{
		self->think = FadeDieSink;
		self->nextthink = level.time+corpse_fadetime->value;
	}
}

// pmm - this quickie does a location trace to try to grow the bounding box
//
// this is because the frames are off; the origin is at the guy's feet.
void soldier_dead2 (edict_t *self)
{
	vec3_t	tempmins, tempmaxs, temporg;
	trace_t	tr;

	VectorCopy (self->s.origin, temporg);
	// this is because location traces done at the floor are guaranteed to hit the floor
	// (inside the sv_trace code it grows the bbox by 1 in all directions)
	temporg[2] += 1;

	VectorSet (tempmins, -32, -32, -24);
	VectorSet (tempmaxs, 32, 32, -8);

	tr = gi.trace (temporg, tempmins, tempmaxs, temporg, self, MASK_SOLID);
	if (tr.startsolid || tr.allsolid)
	{
		VectorSet (self->mins, -16, -16, -24);
		VectorSet (self->maxs, 16, 16, -8);
	}
	else
	{
		VectorCopy (tempmins, self->mins);
		VectorCopy (tempmaxs, self->maxs);
	}
	self->movetype = MOVETYPE_TOSS;
	self->svflags |= SVF_DEADMONSTER;
	self->nextthink = 0;
	gi.linkentity (self);
}

mframe_t soldier_frames_death1 [] =
{
	ai_move, 0,   NULL,
	ai_move, -10, NULL,
	ai_move, -10, NULL,
	ai_move, -10, NULL,
	ai_move, -5,  NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   soldier_fire6,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   soldier_fire7,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL
};
mmove_t soldier_move_death1 = {FRAME_death101, FRAME_death136, soldier_frames_death1, soldier_dead};

mframe_t soldier_frames_death2 [] =
{
	ai_move, -5,  NULL,
	ai_move, -5,  NULL,
	ai_move, -5,  NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL
};
mmove_t soldier_move_death2 = {FRAME_death201, FRAME_death235, soldier_frames_death2, soldier_dead};

mframe_t soldier_frames_death3 [] =
{
	ai_move, -5,  NULL,
	ai_move, -5,  NULL,
	ai_move, -5,  NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
};
mmove_t soldier_move_death3 = {FRAME_death301, FRAME_death345, soldier_frames_death3, soldier_dead};

mframe_t soldier_frames_death4 [] =
{
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL
};
// PMM -changed to soldier_dead2 to get a larger bounding box
mmove_t soldier_move_death4 = {FRAME_death401, FRAME_death453, soldier_frames_death4, soldier_dead2};

mframe_t soldier_frames_death5 [] =
{
	ai_move, -5,  NULL,
	ai_move, -5,  NULL,
	ai_move, -5,  NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL
};
mmove_t soldier_move_death5 = {FRAME_death501, FRAME_death524, soldier_frames_death5, soldier_dead};

mframe_t soldier_frames_death6 [] =
{
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL
};
mmove_t soldier_move_death6 = {FRAME_death601, FRAME_death610, soldier_frames_death6, soldier_dead};

void soldier_die (edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point)
{
	int		n;

	// check for gib
	if (self->health <= self->gib_health && !(self->spawnflags & SF_MONSTER_NOGIB))
	{
		gi.sound (self, CHAN_VOICE, gi.soundindex ("misc/udeath.wav"), 1, ATTN_NORM, 0);
		for (n = 0; n < 3; n++)
			ThrowGib (self, "models/objects/gibs/sm_meat/tris.md2", 0, 0, damage, GIB_ORGANIC);
		ThrowGib (self, "models/objects/gibs/chest/tris.md2", 0, 0, damage, GIB_ORGANIC);
		ThrowHead (self, "models/objects/gibs/head2/tris.md2", 0, 0, damage, GIB_ORGANIC);
		self->deadflag = DEAD_DEAD;
		return;
	}

	if (self->deadflag == DEAD_DEAD)
		return;

	// regular death
	self->s.skinnum |= 1;
	self->deadflag = DEAD_DEAD;
	self->takedamage = DAMAGE_YES;
	self->monsterinfo.power_armor_type = POWER_ARMOR_NONE;

//	if ((self->s.skinnum % 6) == 1)
	if (self->s.skinnum <= 1)
		gi.sound (self, CHAN_VOICE, sound_death_light, 1, ATTN_NORM, 0);
//	else if ((self->s.skinnum % 6) == 3)
	else if (self->s.skinnum <= 3)
		gi.sound (self, CHAN_VOICE, sound_death, 1, ATTN_NORM, 0);
	else // ((self->s.skinnum % 6) == 5)
		gi.sound (self, CHAN_VOICE, sound_death_ss, 1, ATTN_NORM, 0);

	if (fabs((self->s.origin[2] + self->viewheight) - point[2]) <= 4)
	{
		// head shot
		self->monsterinfo.currentmove = &soldier_move_death3;
		return;
	}

	n = rand() % 5;
	if (n == 0)
		self->monsterinfo.currentmove = &soldier_move_death1;
	else if (n == 1)
		self->monsterinfo.currentmove = &soldier_move_death2;
	else if (n == 2)
		self->monsterinfo.currentmove = &soldier_move_death4;
	else if (n == 3)
		self->monsterinfo.currentmove = &soldier_move_death5;
	else
		self->monsterinfo.currentmove = &soldier_move_death6;
}


//=========
//ROGUE
void soldier_blind (edict_t *self);

mframe_t soldier_frames_blind [] =
{
	ai_move, 0, soldier_idle,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,

	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,

	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL
};
mmove_t soldier_move_blind = {FRAME_stand101, FRAME_stand130, soldier_frames_blind, soldier_blind};

void soldier_blind (edict_t *self)
{
	self->monsterinfo.currentmove = &soldier_move_blind;
}
//ROGUE
//=========


// RAFAEL 13-APR-98


#include "m_soldierh.h"

void soldierh_idle (edict_t *self)
{
	if (!(self->spawnflags & SF_MONSTER_AMBUSH))
	{  
		if (random() > 0.8)
			gi.sound (self, CHAN_VOICE, h_sound_idle, 1, ATTN_IDLE, 0);
	}
}

void soldierh_cock (edict_t *self)
{
	if (self->s.frame == FRAME_stand322)
		gi.sound (self, CHAN_WEAPON, h_sound_cock, 1, ATTN_IDLE, 0);
	else
		gi.sound (self, CHAN_WEAPON, h_sound_cock, 1, ATTN_NORM, 0);
}


// STAND

void soldierh_stand (edict_t *self);

mframe_t soldierh_frames_stand1 [] =
{
	ai_stand, 0, soldierh_idle,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,

	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,

	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL
};
mmove_t soldierh_move_stand1 = {FRAME_stand101, FRAME_stand130, soldierh_frames_stand1, soldierh_stand};

mframe_t soldierh_frames_stand3 [] =
{
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,

	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,

	ai_stand, 0, NULL,
	ai_stand, 0, soldierh_cock,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,

	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL
};
mmove_t soldierh_move_stand3 = {FRAME_stand301, FRAME_stand339, soldierh_frames_stand3, soldierh_stand};


void soldierh_stand (edict_t *self)
{
	if ((self->monsterinfo.currentmove == &soldierh_move_stand3) || (random() < 0.8))
		self->monsterinfo.currentmove = &soldierh_move_stand1;
	else
		self->monsterinfo.currentmove = &soldierh_move_stand3;
}


//
// WALK
//

void soldierh_walk1_random (edict_t *self)
{
	if (random() > 0.1)
		self->monsterinfo.nextframe = FRAME_walk101;
}

mframe_t soldierh_frames_walk1 [] =
{
	ai_walk, 3,  NULL,
	ai_walk, 6,  NULL,
	ai_walk, 2,  NULL,
	ai_walk, 2,  NULL,
	ai_walk, 2,  NULL,
	ai_walk, 1,  NULL,
	ai_walk, 6,  NULL,
	ai_walk, 5,  NULL,
	ai_walk, 3,  NULL,
	ai_walk, -1, soldierh_walk1_random,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL
};
mmove_t soldierh_move_walk1 = {FRAME_walk101, FRAME_walk133, soldierh_frames_walk1, NULL};

mframe_t soldierh_frames_walk2 [] =
{
	ai_walk, 4,  NULL,
	ai_walk, 4,  NULL,
	ai_walk, 9,  NULL,
	ai_walk, 8,  NULL,
	ai_walk, 5,  NULL,
	ai_walk, 1,  NULL,
	ai_walk, 3,  NULL,
	ai_walk, 7,  NULL,
	ai_walk, 6,  NULL,
	ai_walk, 7,  NULL
};
mmove_t soldierh_move_walk2 = {FRAME_walk209, FRAME_walk218, soldierh_frames_walk2, NULL};

void soldierh_walk (edict_t *self)
{
	if (random() < 0.5)
		self->monsterinfo.currentmove = &soldierh_move_walk1;
	else
		self->monsterinfo.currentmove = &soldierh_move_walk2;
}


//
// RUN
//

void soldierh_run (edict_t *self);

mframe_t soldierh_frames_start_run [] =
{
	ai_run, 7,  NULL,
	ai_run, 5,  NULL
};
mmove_t soldierh_move_start_run = {FRAME_run01, FRAME_run02, soldierh_frames_start_run, soldierh_run};

mframe_t soldierh_frames_run [] =
{
	ai_run, 10, NULL,
	ai_run, 11, NULL,
	ai_run, 11, NULL,
	ai_run, 16, NULL,
	ai_run, 10, NULL,
	ai_run, 15, NULL
};
mmove_t soldierh_move_run = {FRAME_run03, FRAME_run08, soldierh_frames_run, NULL};

void soldierh_run (edict_t *self)
{
	if (self->monsterinfo.aiflags & AI_STAND_GROUND)
	{
		self->monsterinfo.currentmove = &soldierh_move_stand1;
		return;
	}

	if (self->monsterinfo.currentmove == &soldierh_move_walk1 ||
		self->monsterinfo.currentmove == &soldierh_move_walk2 ||
		self->monsterinfo.currentmove == &soldierh_move_start_run)
	{
		self->monsterinfo.currentmove = &soldierh_move_run;
	}
	else
	{
		self->monsterinfo.currentmove = &soldierh_move_start_run;
	}
}


//
// JUMP
//

mframe_t soldierh_frames_jump [] =
{
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL
};
mmove_t soldierh_move_jump = { FRAME_run01, FRAME_run08, soldierh_frames_jump, soldierh_run };

void soldierh_jump (edict_t *self)
{
	self->monsterinfo.currentmove = &soldierh_move_jump;
}


//
// PAIN
//

mframe_t soldierh_frames_pain1 [] =
{
	ai_move, -3, NULL,
	ai_move, 4,  NULL,
	ai_move, 1,  NULL,
	ai_move, 1,  NULL,
	ai_move, 0,  NULL
};
mmove_t soldierh_move_pain1 = {FRAME_pain101, FRAME_pain105, soldierh_frames_pain1, soldierh_run};

mframe_t soldierh_frames_pain2 [] =
{
	ai_move, -13, NULL,
	ai_move, -1,  NULL,
	ai_move, 2,   NULL,
	ai_move, 4,   NULL,
	ai_move, 2,   NULL,
	ai_move, 3,   NULL,
	ai_move, 2,   NULL
};
mmove_t soldierh_move_pain2 = {FRAME_pain201, FRAME_pain207, soldierh_frames_pain2, soldierh_run};

mframe_t soldierh_frames_pain3 [] =
{
	ai_move, -8, NULL,
	ai_move, 10, NULL,
	ai_move, -4, NULL,
	ai_move, -1, NULL,
	ai_move, -3, NULL,
	ai_move, 0,  NULL,
	ai_move, 3,  NULL,
	ai_move, 0,  NULL,
	ai_move, 0,  NULL,
	ai_move, 0,  NULL,
	ai_move, 0,  NULL,
	ai_move, 1,  NULL,
	ai_move, 0,  NULL,
	ai_move, 1,  NULL,
	ai_move, 2,  NULL,
	ai_move, 4,  NULL,
	ai_move, 3,  NULL,
	ai_move, 2,  NULL
};
mmove_t soldierh_move_pain3 = {FRAME_pain301, FRAME_pain318, soldierh_frames_pain3, soldierh_run};

mframe_t soldierh_frames_pain4 [] =
{
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, -10, NULL,
	ai_move, -6,  NULL,
	ai_move, 8,   NULL,
	ai_move, 4,   NULL,
	ai_move, 1,   NULL,
	ai_move, 0,   NULL,
	ai_move, 2,   NULL,
	ai_move, 5,   NULL,
	ai_move, 2,   NULL,
	ai_move, -1,  NULL,
	ai_move, -1,  NULL,
	ai_move, 3,   NULL,
	ai_move, 2,   NULL,
	ai_move, 0,   NULL
};
mmove_t soldierh_move_pain4 = {FRAME_pain401, FRAME_pain417, soldierh_frames_pain4, soldierh_run};

void soldierh_pain (edict_t *self, edict_t *other, float kick, int damage)
{
	float	r;
	int		n;

	if (self->health < (self->max_health / 2))
			self->s.skinnum |= 1;

	if (level.time < self->pain_debounce_time)
	{
		if ((self->velocity[2] > 100) && ( (self->monsterinfo.currentmove == &soldierh_move_pain1) || (self->monsterinfo.currentmove == &soldierh_move_pain2) || (self->monsterinfo.currentmove == &soldierh_move_pain3)))
			self->monsterinfo.currentmove = &soldierh_move_pain4;
		return;
	}

	self->pain_debounce_time = level.time + 3;

//	n = self->s.skinnum | 1;
	n = self->skinnum | 1;
	if (n == 1)
		gi.sound (self, CHAN_VOICE, h_sound_pain_ripper, 1, ATTN_NORM, 0);
	else if (n == 3)
		gi.sound (self, CHAN_VOICE, h_sound_pain_hypergun, 1, ATTN_NORM, 0);
	else
		gi.sound (self, CHAN_VOICE, h_sound_pain_lasergun, 1, ATTN_NORM, 0);

	if (self->velocity[2] > 100)
	{
		self->monsterinfo.currentmove = &soldierh_move_pain4;
		return;
	}

	if (skill->value == 3)
		return;		// no pain anims in nightmare

	r = random();

	if (r < 0.33)
		self->monsterinfo.currentmove = &soldierh_move_pain1;
	else if (r < 0.66)
		self->monsterinfo.currentmove = &soldierh_move_pain2;
	else
		self->monsterinfo.currentmove = &soldierh_move_pain3;
}


//
// ATTACK
//

extern void brain_dabeam (edict_t *self);

void soldierh_laserbeam (edict_t *self, int flash_index)
{
 
	vec3_t forward, right, up;
	vec3_t tempang, start;
	vec3_t	dir, angles, end;
	vec3_t	tempvec;
	edict_t *ent;

	// RAFAEL
	// this sound can't be called this frequent
//	if (random() > 0.8)
//		gi.sound (self, CHAN_AUTO, h_sound_lasergun_fire, 1, ATTN_STATIC, 0);

	VectorCopy (self->s.origin, start);
	VectorCopy (self->enemy->s.origin, end);
	VectorSubtract (end, start, dir);
	vectoangles (dir, angles);
	VectorCopy (monster_flash_offset[flash_index], tempvec);
	
	// Zaero add
	if (EMPNukeCheck(self, self->s.origin))
	{
		gi.sound (self, CHAN_AUTO, gi.soundindex("items/empnuke/emp_missfire.wav"), 1, ATTN_NORM, 0);
		return;
	}
	// end Zaero

	// RAFAEL
	// this sound can't be called this frequent
	if (random() > 0.8)
		gi.sound (self, CHAN_AUTO, h_sound_lasergun_fire, 1, ATTN_STATIC, 0);

	ent = G_Spawn ();
	VectorCopy (self->s.origin, ent->s.origin);
	VectorCopy (angles, tempang);
	AngleVectors (tempang, forward, right, up);
	VectorCopy (tempang, ent->s.angles);
	VectorCopy (ent->s.origin, start);

	if (flash_index == 85)
	{
		VectorMA (start, tempvec[0]-14, right, start);
		VectorMA (start, tempvec[2]+8, up, start);
		VectorMA (start, tempvec[1], forward, start);
	}
	else 
	{
		VectorMA (start, tempvec[0]+2, right, start);
		VectorMA (start, tempvec[2]+8, up, start);
		VectorMA (start, tempvec[1], forward, start);
	}
			
	VectorCopy (start, ent->s.origin);
	ent->enemy = self->enemy;
	ent->owner = self;
	
	ent->dmg = 2;

	monster_fire_dabeam (ent);
}


void soldierh_fire (edict_t *self, int flash_number)
{
	vec3_t	start;
	vec3_t	forward, right, up;
	vec3_t	aim;
	vec3_t	dir;
	vec3_t	end;
	float	r, u;
	int		flash_index;
	qboolean tone = true;

//	if ((self->s.skinnum % 6) < 2)
	if (self->skinnum < 2)
#ifdef KMQUAKE2_ENGINE_MOD
		flash_index = ionripper_flash[flash_number]; // ripper
#else
		flash_index = blaster_flash[flash_number]; // ripper
#endif	// KMQUAKE2_ENGINE_MOD
//	else if ((self->s.skinnum % 6) < 4)
	else if (self->skinnum < 4)
#ifdef KMQUAKE2_ENGINE_MOD
		flash_index = hyperblaster_flash[flash_number]; // hyperblaster
#else
		flash_index = blaster_flash[flash_number]; // hyperblaster
#endif	// KMQUAKE2_ENGINE_MOD
	else // if (self->skinnum < 6)
		flash_index = machinegun_flash[flash_number]; // laserbeam

	AngleVectors (self->s.angles, forward, right, NULL);
	G_ProjectSource (self->s.origin, monster_flash_offset[flash_index], forward, right, start);

	if (flash_number == 5 || flash_number == 6)
	{
		VectorCopy (forward, aim);
	}
	else
	{
		VectorCopy (self->enemy->s.origin, end);
		end[2] += self->enemy->viewheight;

		// Lazarus fog reduction of accuracy
		if (self->monsterinfo.visibility < FOG_CANSEEGOOD)
		{
			end[0] += crandom() * 640 * (FOG_CANSEEGOOD - self->monsterinfo.visibility);
			end[1] += crandom() * 640 * (FOG_CANSEEGOOD - self->monsterinfo.visibility);
			end[2] += crandom() * 320 * (FOG_CANSEEGOOD - self->monsterinfo.visibility);
		}

		VectorSubtract (end, start, aim);
		vectoangles (aim, dir);
		AngleVectors (dir, forward, right, up);

		r = crandom()*100;
		u = crandom()*50;
		// Knightmare- adjust spread for expanded world size
#ifdef KMQUAKE2_ENGINE_MOD
		r *= (WORLD_SIZE / 8192);
		u *= (WORLD_SIZE / 8192);
#endif
		VectorMA (start, WORLD_SIZE, forward, end);	// was 8192
		VectorMA (end, r, right, end);
		VectorMA (end, u, up, end);

		VectorSubtract (end, start, aim);
		VectorNormalize (aim);
	}

//	if ((self->s.skinnum % 6) <= 1)
	if (self->skinnum <= 1)
	{
		// RAFAEL 24-APR-98
		// droped the damage from 15 to 5 
		monster_fire_ionripper (self, start, aim, 8, 600, flash_index, EF_IONRIPPER);
	}
//	else if ((self->s.skinnum % 6) <= 3)
	else if (self->skinnum <= 3)
	{
	//	monster_fire_blueblaster (self, start, aim, 4, 600, MZ_BLUEHYPERBLASTER, EF_BLUEHYPERBLASTER);
	//	monster_fire_blueblaster (self, start, aim, 4, 600, flash_index, EF_BLUEHYPERBLASTER);	// Knightmare- use an actual monster muzzleflash here!
		monster_fire_blaster (self, start, aim, 4, 600, flash_index, EF_BLUEHYPERBLASTER, BLASTER_BLUE);
	}
	else // if (self->skinnum <= 5)
	{
		if (!(self->monsterinfo.aiflags & AI_HOLD_FRAME))
			self->monsterinfo.pausetime = level.time + (3 + rand() % 8) * FRAMETIME;

		soldierh_laserbeam (self, flash_index);

		if (level.time >= self->monsterinfo.pausetime)
			self->monsterinfo.aiflags &= ~AI_HOLD_FRAME;
		else
			self->monsterinfo.aiflags |= AI_HOLD_FRAME;
	}
}

// ATTACK1 (blaster/shotgun)

void soldierh_hyper_refire1 (edict_t *self)
{
//	if ((self->s.skinnum % 6) < 2)
	if (self->skinnum < 2)
		return;
//	else if ((self->s.skinnum % 6) < 4)
	else if (self->skinnum < 4)
	{
		if (random() < 0.7)
			self->s.frame = FRAME_attak103;
		else
			gi.sound (self, CHAN_AUTO, h_sound_hypergun_spindown, 1, ATTN_NORM, 0);	// Knightmare- use stored index
	}
}

void soldierh_ripper1 (edict_t *self)
{
//	if ((self->s.skinnum % 6) < 2)
	if (self->skinnum < 2)
		soldierh_fire (self, 0);
//	else if ((self->s.skinnum % 6) < 4)
	else if (self->skinnum < 4)
		soldierh_fire (self, 0);
}


void soldierh_fire1 (edict_t *self)
{
	soldierh_fire (self, 0);
}

void soldierh_attack1_refire1 (edict_t *self)
{
//	if ((self->s.skinnum % 6) > 1)
	if (self->skinnum > 1)
		return;

	if (self->enemy->health <= 0)
		return;

	if ( ((skill->value == 3) && (random() < 0.5)) || (range(self, self->enemy) == RANGE_MELEE) )
		self->monsterinfo.nextframe = FRAME_attak102;
	else
		self->monsterinfo.nextframe = FRAME_attak110;
}

void soldierh_attack1_refire2 (edict_t *self)
{
//	if ((self->s.skinnum % 6) < 2)
	if (self->skinnum < 2)
		return;

	if (self->enemy->health <= 0)
		return;

	if ( ((skill->value == 3) && (random() < 0.5)) || (range(self, self->enemy) == RANGE_MELEE) )
		self->monsterinfo.nextframe = FRAME_attak102;
}

void soldierh_hyper_sound (edict_t *self)
{
//	if ((self->s.skinnum % 6) < 2)
	if (self->skinnum < 2)
		return;
//	else if ((self->s.skinnum % 6) < 4)
	else if (self->skinnum < 4)
		gi.sound (self, CHAN_AUTO, h_sound_hypergun_loop, 1, ATTN_NORM, 0);	// Knightmare- use stored index
	else
		return;
}

mframe_t soldierh_frames_attack1 [] =
{
	ai_charge, 0,  NULL,
	ai_charge, 0,  soldierh_hyper_sound,
	ai_charge, 0,  soldierh_fire1,
	ai_charge, 0,  soldierh_ripper1,
	ai_charge, 0,  soldierh_ripper1,
	ai_charge, 0,  soldierh_attack1_refire1,
	ai_charge, 0,  soldierh_hyper_refire1,
	ai_charge, 0,  soldierh_cock,
	ai_charge, 0,  soldierh_attack1_refire2,
	ai_charge, 0,  NULL,
	ai_charge, 0,  NULL,
	ai_charge, 0,  NULL
};
mmove_t soldierh_move_attack1 = {FRAME_attak101, FRAME_attak112, soldierh_frames_attack1, soldierh_run};

// ATTACK2 (blaster/shotgun)

void soldierh_hyper_refire2 (edict_t *self)
{
//	if ((self->s.skinnum % 6) < 2)
	if (self->skinnum < 2)
		return;
//	else if ((self->s.skinnum % 6) < 4)
	else if (self->skinnum < 4)
	{
		if (random() < 0.7)
			self->s.frame = FRAME_attak205;
		else
			gi.sound (self, CHAN_AUTO, h_sound_hypergun_spindown, 1, ATTN_NORM, 0);	// Knightmare- use stored index
	}
}

void soldierh_ripper2 (edict_t *self)
{
//	if ((self->s.skinnum % 6) < 2)
	if (self->skinnum < 2)
		soldierh_fire (self, 1);
//	else if ((self->s.skinnum % 6) < 4)
	else if (self->skinnum < 4)
		soldierh_fire (self, 1);
}

void soldierh_fire2 (edict_t *self)
{
	soldierh_fire (self, 1);
}


void soldierh_attack2_refire1 (edict_t *self)
{
//	if ((self->s.skinnum % 6) > 1)
	if (self->skinnum > 1)
		return;

	if (self->enemy->health <= 0)
		return;

	if ( ((skill->value == 3) && (random() < 0.5)) || (range(self, self->enemy) == RANGE_MELEE))
		self->monsterinfo.nextframe = FRAME_attak204;
	else
		self->monsterinfo.nextframe = FRAME_attak216;
}

void soldierh_attack2_refire2 (edict_t *self)
{
//	if ((self->s.skinnum % 6) < 2)
	if (self->skinnum < 2)
		return;

	if (self->enemy->health <= 0)
		return;

	if ( ((skill->value == 3) && (random() < 0.5))
	//	|| (range(self, self->enemy) == RANGE_MELEE) && (self->s.skinnum % 6) < 4)
		|| (range(self, self->enemy) == RANGE_MELEE) && (self->skinnum < 4) )
		self->monsterinfo.nextframe = FRAME_attak204;
}

mframe_t soldierh_frames_attack2 [] =
{
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, soldierh_hyper_sound,
	ai_charge, 0, soldierh_fire2,
	ai_charge, 0, soldierh_ripper2,
	ai_charge, 0, soldierh_ripper2,
	ai_charge, 0, soldierh_attack2_refire1,
	ai_charge, 0, soldierh_hyper_refire2,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, soldierh_cock,
	ai_charge, 0, NULL,
	ai_charge, 0, soldierh_attack2_refire2,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL
};
mmove_t soldierh_move_attack2 = {FRAME_attak201, FRAME_attak218, soldierh_frames_attack2, soldierh_run};

// ATTACK3 (duck and shoot)

void soldierh_duck_down (edict_t *self)
{
	if (self->monsterinfo.aiflags & AI_DUCKED)
		return;
	self->monsterinfo.aiflags |= AI_DUCKED;
	self->maxs[2] -= 32;
	self->takedamage = DAMAGE_YES;
	self->monsterinfo.pausetime = level.time + 1;
	gi.linkentity (self);
}

void soldierh_duck_up (edict_t *self)
{
	self->monsterinfo.aiflags &= ~AI_DUCKED;
	self->maxs[2] += 32;
	self->takedamage = DAMAGE_AIM;
	gi.linkentity (self);
}

void soldierh_fire3 (edict_t *self)
{
	soldierh_duck_down (self);
	soldierh_fire (self, 2);
}

void soldierh_attack3_refire (edict_t *self)
{
	if ((level.time + 0.4) < self->monsterinfo.pausetime)
		self->monsterinfo.nextframe = FRAME_attak303;
}

mframe_t soldierh_frames_attack3 [] =
{
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, soldierh_fire3,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, soldierh_attack3_refire,
	ai_charge, 0, soldierh_duck_up,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL
};
mmove_t soldierh_move_attack3 = {FRAME_attak301, FRAME_attak309, soldierh_frames_attack3, soldierh_run};

// ATTACK4 (machinegun)

void soldierh_fire4 (edict_t *self)
{
	soldierh_fire (self, 3);
//
//	if (self->enemy->health <= 0)
//		return;
//
//	if ( ((skill->value == 3) && (random() < 0.5)) || (range(self, self->enemy) == RANGE_MELEE) )
//		self->monsterinfo.nextframe = FRAME_attak402;
}

mframe_t soldierh_frames_attack4 [] =
{
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, soldierh_fire4,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL
};
mmove_t soldierh_move_attack4 = {FRAME_attak401, FRAME_attak406, soldierh_frames_attack4, soldierh_run};

#if 0
// ATTACK5 (prone)

void soldierh_fire5 (edict_t *self)
{
	soldierh_fire (self, 4);
}

void soldierh_attack5_refire (edict_t *self)
{
	if (self->enemy->health <= 0)
		return;

	if ( ((skill->value == 3) && (random() < 0.5)) || (range(self, self->enemy) == RANGE_MELEE) )
		self->monsterinfo.nextframe = FRAME_attak505;
}

mframe_t soldierh_frames_attack5 [] =
{
	ai_charge, 8, NULL,
	ai_charge, 8, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, soldierh_fire5,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, soldierh_attack5_refire
};
//mmove_t soldierh_move_attack5 = {FRAME_attak501, FRAME_attak508, soldierh_frames_attack5, soldierh_run};
#endif

// ATTACK6 (run & shoot)

void soldierh_fire8 (edict_t *self)
{
	soldierh_fire (self, 7);
}

void soldierh_attack6_refire (edict_t *self)
{
	if (self->enemy->health <= 0)
		return;

	if (range(self, self->enemy) < RANGE_MID)
		return;

	if (skill->value == 3)
		self->monsterinfo.nextframe = FRAME_runs03;
}

mframe_t soldierh_frames_attack6 [] =
{
	ai_charge, 10, NULL,
	ai_charge,  4, NULL,
	ai_charge, 12, NULL,
	ai_charge, 11, soldierh_fire8,
	ai_charge, 13, NULL,
	ai_charge, 18, NULL,
	ai_charge, 15, NULL,
	ai_charge, 14, NULL,
	ai_charge, 11, NULL,
	ai_charge,  8, NULL,
	ai_charge, 11, NULL,
	ai_charge, 12, NULL,
	ai_charge, 12, NULL,
	ai_charge, 17, soldierh_attack6_refire
};
mmove_t soldierh_move_attack6 = {FRAME_runs01, FRAME_runs14, soldierh_frames_attack6, soldierh_run};

void soldierh_attack (edict_t *self)
{
	float r, chance;

	monster_done_dodge (self);
	//Knightmare- no blindfire for ripper soldiers in old levels
	if (mp_monster_replace->value && (self->monsterinfo.aiflags & AI_BLOCKED))
		return;

	// PMM - blindfire!
	if (self->monsterinfo.attack_state == AS_BLIND)
	{
		// setup shot probabilities
		if (self->monsterinfo.blind_fire_delay < 1.0)
			chance = 1.0;
		else if (self->monsterinfo.blind_fire_delay < 7.5)
			chance = 0.4;
		else
			chance = 0.1;

		r = random();

		// minimum of 2 seconds, plus 0-3, after the shots are done
		self->monsterinfo.blind_fire_delay += 2.1 + 2.0 + random()*3.0;

		// don't shoot at the origin
		if (VectorCompare (self->monsterinfo.blind_fire_target, vec3_origin))
			return;

		// don't shoot if the dice say not to
		if (r > chance)
		{
//			if ((g_showlogic) && (g_showlogic->value))
//				gi.dprintf ("blindfire - NO SHOT\n");
			return;
		}

		// turn on manual steering to signal both manual steering and blindfire
		self->monsterinfo.aiflags |= AI_MANUAL_STEERING;
		self->monsterinfo.currentmove = &soldierh_move_attack1;
		self->monsterinfo.attack_finished = level.time + 1.5 + random();
		return;
	}
	// pmm

// PMM - added this so the soldiers now run toward you and shoot instead of just stopping and shooting
//	if ((range(self, self->enemy) >= RANGE_MID) && (r < (skill->value*0.25) && ((self->s.skinnum % 6) <= 3)))

	r = random();

	if ((!(self->monsterinfo.aiflags & (AI_BLOCKED|AI_STAND_GROUND))) &&
		(range(self, self->enemy) >= RANGE_NEAR) && 
		(r < (skill->value*0.25) && 
	//	((self->s.skinnum % 6) <= 3)))
		(self->skinnum <= 3)))
	{
		self->monsterinfo.currentmove = &soldierh_move_attack6;
	}
	else
	{
	//	if ((self->s.skinnum % 6) < 4)
		if (self->skinnum < 4)
		{
			if (random() < 0.5)
				self->monsterinfo.currentmove = &soldierh_move_attack1;
			else
				self->monsterinfo.currentmove = &soldierh_move_attack2;
		}
		else
		{
			self->monsterinfo.currentmove = &soldierh_move_attack4;
		}
	}
}

//
// SIGHT
//

void soldierh_sight (edict_t *self, edict_t *other)
{
	if (random() < 0.5)
		gi.sound (self, CHAN_VOICE, h_sound_sight1, 1, ATTN_NORM, 0);
	else
		gi.sound (self, CHAN_VOICE, h_sound_sight2, 1, ATTN_NORM, 0);

	if ((skill->value > 0) && (range(self, self->enemy) >= RANGE_MID))
	{
		if (random() > 0.5)
		{
		//	if ((self->s.skinnum % 6) < 4)	
			if (self->skinnum < 4)	
				self->monsterinfo.currentmove = &soldierh_move_attack6;
			else
				self->monsterinfo.currentmove = &soldierh_move_attack4;
		}
	}
}

//
// DUCK
//

void soldierh_duck_hold (edict_t *self)
{
	if (level.time >= self->monsterinfo.pausetime)
		self->monsterinfo.aiflags &= ~AI_HOLD_FRAME;
	else
		self->monsterinfo.aiflags |= AI_HOLD_FRAME;
}

mframe_t soldierh_frames_duck [] =
{
	ai_move, 5, soldierh_duck_down,
	ai_move, -1, soldierh_duck_hold,
	ai_move, 1,  NULL,
	ai_move, 0,  soldierh_duck_up,
	ai_move, 5,  NULL
};
mmove_t soldierh_move_duck = {FRAME_duck01, FRAME_duck05, soldierh_frames_duck, soldierh_run};

void soldierh_dodge (edict_t *self, edict_t *attacker, float eta)
{
	float	r;

	r = random();
	if (r > 0.25)
		return;

	if (!self->enemy)
		self->enemy = attacker;

	if (skill->value == 0)
	{
		self->monsterinfo.currentmove = &soldierh_move_duck;
		return;
	}

	self->monsterinfo.pausetime = level.time + eta + 0.3;
	r = random();

	if (skill->value == 1)
	{
		if (r > 0.33)
			self->monsterinfo.currentmove = &soldierh_move_duck;
		else
			self->monsterinfo.currentmove = &soldierh_move_attack3;
		return;
	}

	if (skill->value >= 2)
	{
		if (r > 0.66)
			self->monsterinfo.currentmove = &soldierh_move_duck;
		else
			self->monsterinfo.currentmove = &soldierh_move_attack3;
		return;
	}

	self->monsterinfo.currentmove = &soldierh_move_attack3;
}

//
// NEW DODGE CODE
//
// Knightmare- moved this code down here below soldierh frame declarations
void soldier_sidestep (edict_t *self)
{
//	if ((self->s.skinnum % 6) <= 3)
	if (self->skinnum <= 3)
	{
//		if ((g_showlogic) && (g_showlogic->value))
//			gi.dprintf ("shooting back!\n");
		if ((self->monsterinfo.currentmove != &soldier_move_attack6)
		|| (self->monsterinfo.currentmove != &soldierh_move_attack6))
		{	//Knightmare- make sure the Xatrix grunts fire the right weapon!!
			if ((!strcmp(self->classname, "monster_soldier_ripper"))
			|| (!strcmp(self->classname, "monster_soldier_hypergun"))
			|| (!strcmp(self->classname, "monster_soldier_lasergun")))
				self->monsterinfo.currentmove = &soldierh_move_attack6;
			else
				self->monsterinfo.currentmove = &soldier_move_attack6;
		}
	}
	else
	{
//		if ((g_showlogic) && (g_showlogic->value))
//			gi.dprintf ("strafing away!\n");
		if (self->monsterinfo.currentmove != &soldier_move_start_run)
			self->monsterinfo.currentmove = &soldier_move_start_run;
	}
}

void soldier_duck (edict_t *self, float eta)
{
	float r;

	// has to be done immediately otherwise he can get stuck
	monster_duck_down(self);

	if (skill->value == 0)
	{
		// PMM - stupid dodge
		self->monsterinfo.nextframe = FRAME_duck01;
		self->monsterinfo.currentmove = &soldier_move_duck;
		self->monsterinfo.duck_wait_time = level.time + eta + 1;
		return;
	}

	r = random();

	if (r > (skill->value * 0.3))
	{
		self->monsterinfo.nextframe = FRAME_duck01;
		self->monsterinfo.currentmove = &soldier_move_duck;
		self->monsterinfo.duck_wait_time = level.time + eta + (0.1 * (3 - skill->value));
	}
	else
	{
		self->monsterinfo.nextframe = FRAME_attak301;
		if ((!strcmp(self->classname, "monster_soldier_ripper"))
		|| (!strcmp(self->classname, "monster_soldier_hypergun"))
		|| (!strcmp(self->classname, "monster_soldier_lasergun")))
			self->monsterinfo.currentmove = &soldierh_move_attack3;
		else
			self->monsterinfo.currentmove = &soldier_move_attack3;
		self->monsterinfo.duck_wait_time = level.time + eta + 1;
	}
	return;
}

//
// DEATH
//

void soldierh_fire6 (edict_t *self)
{
	
	// no fire laser
//	if ((self->s.skinnum % 6) < 4)
	if (self->skinnum < 4)
		soldierh_fire (self, 5);

}

void soldierh_fire7 (edict_t *self)
{
	
	// no fire laser
//	if ((self->s.skinnum % 6) < 4)
	if (self->skinnum < 4)
		soldierh_fire (self, 6);

}

void soldierh_dead (edict_t *self)
{
	VectorSet (self->mins, -16, -16, -24);
	VectorSet (self->maxs, 16, 16, -8);
	self->movetype = MOVETYPE_TOSS;
	self->svflags |= SVF_DEADMONSTER;
	self->nextthink = 0;
	gi.linkentity (self);
	M_FlyCheck (self);

	// Lazarus monster fade
	if (world->effects & FX_WORLDSPAWN_CORPSEFADE)
	{
		self->think=FadeDieSink;
		self->nextthink=level.time+corpse_fadetime->value;
	}
}

mframe_t soldierh_frames_death1 [] =
{
	ai_move, 0,   NULL,
	ai_move, -10, NULL,
	ai_move, -10, NULL,
	ai_move, -10, NULL,
	ai_move, -5,  NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   soldierh_fire6,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   soldierh_fire7,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL
};
mmove_t soldierh_move_death1 = {FRAME_death101, FRAME_death136, soldierh_frames_death1, soldierh_dead};

mframe_t soldierh_frames_death2 [] =
{
	ai_move, -5,  NULL,
	ai_move, -5,  NULL,
	ai_move, -5,  NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL
};
mmove_t soldierh_move_death2 = {FRAME_death201, FRAME_death235, soldierh_frames_death2, soldierh_dead};

mframe_t soldierh_frames_death3 [] =
{
	ai_move, -5,  NULL,
	ai_move, -5,  NULL,
	ai_move, -5,  NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
};
mmove_t soldierh_move_death3 = {FRAME_death301, FRAME_death345, soldierh_frames_death3, soldierh_dead};

mframe_t soldierh_frames_death4 [] =
{
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL
};
mmove_t soldierh_move_death4 = {FRAME_death401, FRAME_death453, soldierh_frames_death4, soldierh_dead};

mframe_t soldierh_frames_death5 [] =
{
	ai_move, -5,  NULL,
	ai_move, -5,  NULL,
	ai_move, -5,  NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL
};
mmove_t soldierh_move_death5 = {FRAME_death501, FRAME_death524, soldierh_frames_death5, soldierh_dead};

mframe_t soldierh_frames_death6 [] =
{
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL
};
mmove_t soldierh_move_death6 = {FRAME_death601, FRAME_death610, soldierh_frames_death6, soldierh_dead};

void soldierh_die (edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point)
{
	int		n;

	// check for gib
	if (self->health <= self->gib_health && !(self->spawnflags & SF_MONSTER_NOGIB))
	{
		gi.sound (self, CHAN_VOICE, gi.soundindex ("misc/udeath.wav"), 1, ATTN_NORM, 0);
		for (n = 0; n < 3; n++)
			ThrowGib (self, "models/objects/gibs/sm_meat/tris.md2", 0, 0, damage, GIB_ORGANIC);
		ThrowGib (self, "models/objects/gibs/chest/tris.md2", 0, 0, damage, GIB_ORGANIC);
		ThrowHead (self, "models/objects/gibs/head2/tris.md2", 0, 0, damage, GIB_ORGANIC);
		
		self->deadflag = DEAD_DEAD;
		return;
	}

	if (self->deadflag == DEAD_DEAD)
		return;

	// regular death
	self->s.skinnum |= 1;
	self->deadflag = DEAD_DEAD;
	self->takedamage = DAMAGE_YES;
	self->monsterinfo.power_armor_type = POWER_ARMOR_NONE;

//	if ((self->s.skinnum % 6) == 1)
	if (self->skinnum <= 1)
		gi.sound (self, CHAN_VOICE, h_sound_death_ripper, 1, ATTN_NORM, 0);
//	else if ((self->s.skinnum % 6) == 3)
	else if (self->skinnum <= 3)
		gi.sound (self, CHAN_VOICE, h_sound_death_hypergun, 1, ATTN_NORM, 0);
	else // ((self->s.skinnum % 6) == 5)
		gi.sound (self, CHAN_VOICE, h_sound_death_lasergun, 1, ATTN_NORM, 0);

	if (fabs((self->s.origin[2] + self->viewheight) - point[2]) <= 4)
	{
		// head shot
		self->monsterinfo.currentmove = &soldierh_move_death3;
		return;
	}

	n = rand() % 5;
	if (n == 0)
		self->monsterinfo.currentmove = &soldierh_move_death1;
	else if (n == 1)
		self->monsterinfo.currentmove = &soldierh_move_death2;
	else if (n == 2)
		self->monsterinfo.currentmove = &soldierh_move_death4;
	else if (n == 3)
		self->monsterinfo.currentmove = &soldierh_move_death5;
	else
		self->monsterinfo.currentmove = &soldierh_move_death6;
}

//
// SPAWN
//

void SP_monster_soldier_x (edict_t *self)
{
	// Lazarus: special purpose skins
	if ( self->style )
		PatchMonsterModel("models/monsters/soldier/tris.md2");

	self->s.modelindex = gi.modelindex ("models/monsters/soldier/tris.md2");
	//PMM
//	self->s.effects |= EF_SPLATTER;
	//PMM
	self->monsterinfo.scale = MODEL_SCALE;
	VectorSet (self->mins, -16, -16, -24);
	VectorSet (self->maxs, 16, 16, 32);
	self->movetype = MOVETYPE_STEP;
	self->solid = SOLID_BBOX;

	sound_idle =	gi.soundindex ("soldier/solidle1.wav");
	sound_sight1 =	gi.soundindex ("soldier/solsght1.wav");
	sound_sight2 =	gi.soundindex ("soldier/solsrch1.wav");
	sound_cock =	gi.soundindex ("infantry/infatck3.wav");

	if (!self->mass)
		self->mass = 100;

	self->pain = soldier_pain;
	self->die = soldier_die;

	self->monsterinfo.stand = soldier_stand;
	self->monsterinfo.walk = soldier_walk;
	self->monsterinfo.run = soldier_run;
	self->monsterinfo.dodge = M_MonsterDodge;
	self->monsterinfo.attack = soldier_attack;
	self->monsterinfo.melee = NULL;
	self->monsterinfo.sight = soldier_sight;

//=====
//ROGUE
	self->monsterinfo.blocked = soldier_blocked;
	self->monsterinfo.duck = soldier_duck;
	self->monsterinfo.unduck = monster_duck_up;
	self->monsterinfo.sidestep = soldier_sidestep;
//ROGUE
//=====

	if (monsterjump->value)
	{
		self->monsterinfo.jump = soldier_jump;
		self->monsterinfo.jumpup = 48;
		self->monsterinfo.jumpdn = 160;
	}

	// Lazarus
	if (self->powerarmor)
	{
		if (self->powerarmortype == 1)
			self->monsterinfo.power_armor_type = POWER_ARMOR_SCREEN;
		else
			self->monsterinfo.power_armor_type = POWER_ARMOR_SHIELD;
		self->monsterinfo.power_armor_power = self->powerarmor;
	}

	if (!self->monsterinfo.flies)
		self->monsterinfo.flies = 0.40;

	gi.linkentity (self);

	self->monsterinfo.stand (self);
	if (self->health < 0)
	{
		mmove_t	*deathmoves[] = {&soldier_move_death1,
			                     &soldier_move_death2,
								 &soldier_move_death3,
								 &soldier_move_death4,
								 &soldier_move_death5,
								 &soldier_move_death6,
								 NULL};
		M_SetDeath (self, (mmove_t **)&deathmoves);
	}
	walkmonster_start (self);
}


/*QUAKED monster_soldier_light (1 .5 0) (-16 -16 -24) (16 16 32) Ambush Trigger_Spawn Sight GoodGuy NoGib
*/
void SP_monster_soldier_light (edict_t *self)
{
	if (deathmatch->value)
	{
		G_FreeEdict (self);
		return;
	}

	sound_pain_light = gi.soundindex ("soldier/solpain2.wav");
	sound_death_light =	gi.soundindex ("soldier/soldeth2.wav");
	gi.modelindex ("models/objects/laser/tris.md2");
	gi.soundindex ("misc/lasfly.wav");
	gi.soundindex ("soldier/solatck2.wav");

	self->common_name = "Light Guard";
	self->class_id = ENTITY_MONSTER_SOLDIER_LIGHT;

//	self->s.skinnum = 0;
	if (!self->health)
		self->health = 20;
	if (!self->gib_health)
		self->gib_health = -40; // was -30

	// PMM - blindfire
	self->monsterinfo.blindfire = true;
	// Knightmare- call generic spawn function LAST, because it
	// calls walkmonster_start, which the health and everything else need to be set up for
	SP_monster_soldier_x (self);
	// Lazarus: custom skins
	self->s.skinnum = 0 + 8 * self->style;	// was 0 + 6 * self->style
	self->skinnum = 0;	// Knightmare- simplify skinnum checks by excluding custom styles
}

/*QUAKED monster_soldier (1 .5 0) (-16 -16 -24) (16 16 32) Ambush Trigger_Spawn Sight GoodGuy NoGib
*/
void SP_monster_soldier (edict_t *self)
{
	if (deathmatch->value)
	{
		G_FreeEdict (self);
		return;
	}

	sound_pain = gi.soundindex ("soldier/solpain1.wav");
	sound_death = gi.soundindex ("soldier/soldeth1.wav");
	gi.soundindex ("soldier/solatck1.wav");

	self->common_name = "Shotgun Guard";
	self->class_id = ENTITY_MONSTER_SOLDIER;

//	self->s.skinnum = 2;
	if (!self->health)
		self->health = 30;
	if (!self->gib_health)
		self->gib_health = -40;
	// Knightmare- call generic spawn function LAST, because it
	// calls walkmonster_start, which the health and everything else need to be set up for
	SP_monster_soldier_x (self);
	// Lazarus: custom skins
	self->s.skinnum = 2 + 8 * self->style;	// was 2 + 6 * self->style
	self->skinnum = 2;	// Knightmare- simplify skinnum checks by excluding custom styles
}

/*QUAKED monster_soldier_ss (1 .5 0) (-16 -16 -24) (16 16 32) Ambush Trigger_Spawn Sight GoodGuy NoGib
*/
void SP_monster_soldier_ss (edict_t *self)
{
	if (deathmatch->value)
	{
		G_FreeEdict (self);
		return;
	}

	sound_pain_ss = gi.soundindex ("soldier/solpain3.wav");
	sound_death_ss = gi.soundindex ("soldier/soldeth3.wav");
	gi.soundindex ("soldier/solatck3.wav");

	self->common_name = "Machinegun Guard";
	self->class_id = ENTITY_MONSTER_SOLDIER_SS;

//	self->s.skinnum = 4;
	if (!self->health)
		self->health = 40;
	if (!self->gib_health)
		self->gib_health = -40;
	// Knightmare- call generic spawn function LAST, because it
	// calls walkmonster_start, which the health and everything else need to be set up for
	SP_monster_soldier_x (self);
	// Lazarus: custom skins
	self->s.skinnum = 4 + 8 * self->style;	// was 4 + 6 * self->style
	self->skinnum = 4;	// Knightmare- simplify skinnum checks by excluding custom styles
}

/*QUAKED monster_soldier_plasma_re (1 .5 0) (-16 -16 -24) (16 16 32) Ambush Trigger_Spawn Sight GoodGuy NoGib
*/
void SP_monster_soldier_plasma_re (edict_t *self)
{
	if (deathmatch->value)
	{
		G_FreeEdict (self);
		return;
	}

	sound_pain_ss = gi.soundindex ("soldier/solpain3.wav");
	sound_death_ss = gi.soundindex ("soldier/soldeth3.wav");
	gi.modelindex (PLASMA_SPRITE_FLY);
	gi.soundindex(PLASMA_SOUND_FLYBY);
#ifdef KMQUAKE2_ENGINE_MOD
	gi.soundindex ("weapons/plasma/fire1.wav");
#else
	gi.soundindex ("soldier/solatck2.wav");
#endif	// KMQUAKE2_ENGINE_MOD

	self->common_name = "Plasma Guard";
	self->class_id = ENTITY_MONSTER_SOLDIER_PLASMA_BOUNCE;

//	self->s.skinnum = 0;
	if (!self->health)
		self->health = 50;
	if (!self->gib_health)
		self->gib_health = -40; // was -30

	// PMM - blindfire
	self->monsterinfo.blindfire = false;
	// Knightmare- call generic spawn function LAST, because it
	// calls walkmonster_start, which the health and everything else need to be set up for
	SP_monster_soldier_x (self);
	// Lazarus: custom skins
	self->s.skinnum = 6 + 8 * self->style;
	self->skinnum = 6;	// Knightmare- simplify skinnum checks by excluding custom styles
}

/*QUAKED monster_soldier_plasma_sp (1 .5 0) (-16 -16 -24) (16 16 32) Ambush Trigger_Spawn Sight GoodGuy NoGib
*/
void SP_monster_soldier_plasma_sp (edict_t *self)
{
	if (deathmatch->value)
	{
		G_FreeEdict (self);
		return;
	}

	sound_pain_ss = gi.soundindex ("soldier/solpain3.wav");
	sound_death_ss = gi.soundindex ("soldier/soldeth3.wav");
	gi.modelindex (PLASMA_SPRITE_FLY);
	gi.soundindex(PLASMA_SOUND_FLYBY);
#ifdef KMQUAKE2_ENGINE_MOD
	gi.soundindex ("weapons/plasma/fire2.wav");
#else
	gi.soundindex ("soldier/solatck2.wav");
#endif	// KMQUAKE2_ENGINE_MOD

	self->common_name = "Plasma Guard";
	self->class_id = ENTITY_MONSTER_SOLDIER_PLASMA_SPREAD;

//	self->s.skinnum = 2;
	if (!self->health)
		self->health = 50;
	if (!self->gib_health)
		self->gib_health = -40;

	// PMM - blindfire
	self->monsterinfo.blindfire = true;
	// Knightmare- call generic spawn function LAST, because it
	// calls walkmonster_start, which the health and everything else need to be set up for
	SP_monster_soldier_x (self);
	// Lazarus: custom skins
	self->s.skinnum = 6 + 8 * self->style;
	self->skinnum = 6;	// Knightmare- simplify skinnum checks by excluding custom styles
	self->moreflags |= FL2_WEAPON_ALT;	// special flag for spread mode
}

//
// SPAWN
//

void SP_monster_soldier_h (edict_t *self)
{
	// Lazarus: special purpose skins
	if ( self->style )
		PatchMonsterModel("models/monsters/soldierh/tris.md2");

	self->s.modelindex = gi.modelindex ("models/monsters/soldierh/tris.md2");
	self->monsterinfo.scale = MODEL_SCALE;
	VectorSet (self->mins, -16, -16, -24);
	VectorSet (self->maxs, 16, 16, 32);
	self->movetype = MOVETYPE_STEP;
	self->solid = SOLID_BBOX;

	h_sound_idle =	gi.soundindex ("soldier/solidle1.wav");
	h_sound_sight1 =	gi.soundindex ("soldier/solsght1.wav");
	h_sound_sight2 =	gi.soundindex ("soldier/solsrch1.wav");
	h_sound_cock =	gi.soundindex ("infantry/infatck3.wav");

	if (!self->mass)
		self->mass = 100;

	self->pain = soldierh_pain;
	self->die = soldierh_die;

	self->monsterinfo.stand = soldierh_stand;
	self->monsterinfo.walk = soldierh_walk;
	self->monsterinfo.run = soldierh_run;
	self->monsterinfo.dodge = M_MonsterDodge;
	self->monsterinfo.attack = soldierh_attack;
	self->monsterinfo.melee = NULL;
	self->monsterinfo.sight = soldierh_sight;

	//=====
//ROGUE
	self->monsterinfo.blocked = soldier_blocked;
	self->monsterinfo.duck = soldier_duck;
	self->monsterinfo.unduck = monster_duck_up;
	self->monsterinfo.sidestep = soldier_sidestep;
//ROGUE
//=====

	if (monsterjump->value)
	{
		self->monsterinfo.jump = soldierh_jump;
		self->monsterinfo.jumpup = 48;
		self->monsterinfo.jumpdn = 160;
	}

	// Lazarus
	if (self->powerarmor)
	{
		if (self->powerarmortype == 1)
			self->monsterinfo.power_armor_type = POWER_ARMOR_SCREEN;
		else
			self->monsterinfo.power_armor_type = POWER_ARMOR_SHIELD;
		self->monsterinfo.power_armor_power = self->powerarmor;
	}

	if (!self->monsterinfo.flies)
		self->monsterinfo.flies = 0.40;

	gi.linkentity (self);

//	self->monsterinfo.stand (self);
	self->monsterinfo.currentmove = &soldierh_move_stand3;	
	if (self->health < 0)
	{
		mmove_t	*deathmoves[] = {&soldierh_move_death1,
			                     &soldierh_move_death2,
								 &soldierh_move_death3,
								 &soldierh_move_death4,
								 &soldierh_move_death5,
								 &soldierh_move_death6,
								 NULL};
		M_SetDeath (self, (mmove_t **)&deathmoves);
	}
	walkmonster_start (self);
}


/*QUAKED monster_soldier_ripper (1 .5 0) (-16 -16 -24) (16 16 32) Ambush Trigger_Spawn Sight GoodGuy NoGib
*/
void SP_monster_soldier_ripper (edict_t *self)
{
	if (deathmatch->value)
	{
		G_FreeEdict (self);
		return;
	}

	h_sound_pain_ripper = gi.soundindex ("soldier/solpain2.wav");
	h_sound_death_ripper =	gi.soundindex ("soldier/soldeth2.wav");
	gi.modelindex ("models/objects/boomrang/tris.md2");
	gi.soundindex ("misc/lasfly.wav");
#ifdef KMQUAKE2_ENGINE_MOD
	gi.soundindex ("weapons/rippfire.wav");
#else
	gi.soundindex ("soldier/solatck2.wav");
#endif	// KMQUAKE2_ENGINE_MOD

	self->common_name = "Ripper Guard";
	self->class_id = ENTITY_MONSTER_SOLDIER_RIPPER;

	if (!self->health)
		self->health = 50;
	if (!self->gib_health)
		self->gib_health = -40;

	// PMM - blindfire
	self->monsterinfo.blindfire = true;
	// Knightmare- call generic spawn function LAST, because it
	// calls walkmonster_start, which the health and everything else need to be set up for
	SP_monster_soldier_h (self);
	// Lazarus: custom skins
	self->s.skinnum = 0 + 6 * self->style;
	self->skinnum = 0;	// Knightmare- simplify skinnum checks by excluding custom styles
}

/*QUAKED monster_soldier_hypergun (1 .5 0) (-16 -16 -24) (16 16 32) Ambush Trigger_Spawn Sight GoodGuy NoGib
*/

void SP_monster_soldier_hypergun (edict_t *self)
{
	if (deathmatch->value)
	{
		G_FreeEdict (self);
		return;
	}

	h_sound_pain_hypergun = gi.soundindex ("soldier/solpain1.wav");
	h_sound_death_hypergun = gi.soundindex ("soldier/soldeth1.wav");
	h_sound_hypergun_loop = gi.soundindex ("weapons/hyprbl1a.wav");	// Knightmare- missing precache
	h_sound_hypergun_spindown = gi.soundindex ("weapons/hyprbd1a.wav");	// Knightmare- missing precache
//	gi.modelindex ("models/objects/blaser/tris.md2");
	gi.modelindex ("models/objects/laser/tris.md2");	// Knightmare- precache shared laser model instead
	gi.soundindex ("misc/lasfly.wav");	// Knightmare added
#ifdef KMQUAKE2_ENGINE_MOD
	gi.soundindex ("weapons/hyprbf1a.wav");	// Knightmare- used by new muzzleflash
#else
	gi.soundindex ("soldier/solatck2.wav");	// Knightmare- used by monster muzzle flash
#endif

	self->common_name = "Hyperblaster Guard";
	self->class_id = ENTITY_MONSTER_SOLDIER_HYPERGUN;

	if (!self->health)
		self->health = 60;
	if (!self->gib_health)
		self->gib_health = -40;

	// PMM - blindfire
	self->monsterinfo.blindfire = true;

	// Knightmare- call generic spawn function LAST, because it
	// calls walkmonster_start, which the health and everything else need to be set up for
	SP_monster_soldier_h (self);
	// Lazarus: custom skins
	self->s.skinnum = 2 + 6 * self->style;
	self->skinnum = 2;	// Knightmare- simplify skinnum checks by excluding custom styles
}

/*QUAKED monster_soldier_lasergun (1 .5 0) (-16 -16 -24) (16 16 32) Ambush Trigger_Spawn Sight GoodGuy NoGib ThroughGlass
*/
void SP_monster_soldier_lasergun (edict_t *self)
{
	if (deathmatch->value)
	{
		G_FreeEdict (self);
		return;
	}

	h_sound_pain_lasergun = gi.soundindex ("soldier/solpain3.wav");
	h_sound_death_lasergun = gi.soundindex ("soldier/soldeth3.wav");
	h_sound_lasergun_fire = gi.soundindex ("misc/lasfly.wav");	// Knightmare- missing precache
//	gi.soundindex ("soldier/solatck3.wav");				// Knightmare- not used

	self->common_name = "Laser Guard";
	self->class_id = ENTITY_MONSTER_SOLDIER_LASER;

	if (!self->health)
		self->health = 70;
	if (!self->gib_health)
		self->gib_health = -40;

	// Knightmare- call generic spawn function LAST, because it
	// calls walkmonster_start, which the health and everything else need to be set up for
	SP_monster_soldier_h (self);
	// Lazarus: custom skins
	self->s.skinnum = 4 + 6 * self->style;
	self->skinnum = 4;	// Knightmare- simplify skinnum checks by excluding custom styles
}

// END 13-APR-98

/*
*
* NOTE(gnemeth): Guggenheim's disruptor soldier
*
*/

void soldierq25_idle (edict_t *self)
{
	if (!(self->spawnflags & SF_MONSTER_AMBUSH))
	{  
		if (random() > 0.8)
			gi.sound (self, CHAN_VOICE, q25_sound_idle, 1, ATTN_IDLE, 0);
	}
}

void soldierq25_cock (edict_t *self)
{
	if (self->s.frame == FRAME_stand322)
		gi.sound (self, CHAN_WEAPON, q25_sound_cock, 1, ATTN_IDLE, 0);
	else
		gi.sound (self, CHAN_WEAPON, q25_sound_cock, 1, ATTN_NORM, 0);
}

// STAND

void soldierq25_stand (edict_t *self);

mframe_t soldierq25_frames_stand1 [] =
{
	ai_stand, 0, soldierq25_idle,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,

	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,

	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL
};
mmove_t soldierq25_move_stand1 = {FRAME_stand101, FRAME_stand130, soldierq25_frames_stand1, soldierq25_stand};

mframe_t soldierq25_frames_stand3 [] =
{
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,

	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,

	ai_stand, 0, NULL,
	ai_stand, 0, soldierq25_cock,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,

	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL
};
mmove_t soldierq25_move_stand3 = {FRAME_stand301, FRAME_stand339, soldierq25_frames_stand3, soldierq25_stand};

void soldierq25_stand (edict_t *self)
{
	if ((self->monsterinfo.currentmove == &soldierq25_move_stand3) || (random() < 0.8))
		self->monsterinfo.currentmove = &soldierq25_move_stand1;
	else
		self->monsterinfo.currentmove = &soldierq25_move_stand3;
}


// RUN

void soldierq25_run (edict_t *self);

mmove_t soldierq25_move_start_run = {FRAME_run01, FRAME_run02, soldierh_frames_start_run, soldierq25_run};

void soldierq25_run (edict_t *self)
{
	if (self->monsterinfo.aiflags & AI_STAND_GROUND)
	{
		self->monsterinfo.currentmove = &soldierq25_move_stand1;
		return;
	}

	if (self->monsterinfo.currentmove == &soldierh_move_walk1 ||
		self->monsterinfo.currentmove == &soldierh_move_walk2 ||
		self->monsterinfo.currentmove == &soldierq25_move_start_run)
	{
		self->monsterinfo.currentmove = &soldierh_move_run;
	}
	else
	{
		self->monsterinfo.currentmove = &soldierq25_move_start_run;
	}
}

// JUMP

mmove_t soldierq25_move_jump = { FRAME_run01, FRAME_run08, soldierh_frames_jump, soldierq25_run };

void soldierq25_jump (edict_t *self)
{
	self->monsterinfo.currentmove = &soldierq25_move_jump;
}

// PAIN

mmove_t soldierq25_move_pain1 = {FRAME_pain101, FRAME_pain105, soldierh_frames_pain1, soldierq25_run};

mmove_t soldierq25_move_pain2 = {FRAME_pain201, FRAME_pain207, soldierh_frames_pain2, soldierq25_run};

mmove_t soldierq25_move_pain3 = {FRAME_pain301, FRAME_pain318, soldierh_frames_pain3, soldierq25_run};

mmove_t soldierq25_move_pain4 = {FRAME_pain401, FRAME_pain417, soldierh_frames_pain4, soldierq25_run};

void soldierq25_pain (edict_t *self, edict_t *other, float kick, int damage)
{
	float	r;

	if (self->health < (self->max_health / 2))
			self->s.skinnum |= 1;

	if (level.time < self->pain_debounce_time)
	{
		if ((self->velocity[2] > 100) && ( (self->monsterinfo.currentmove == &soldierq25_move_pain1) || (self->monsterinfo.currentmove == &soldierq25_move_pain2) || (self->monsterinfo.currentmove == &soldierq25_move_pain3)))
			self->monsterinfo.currentmove = &soldierq25_move_pain4;
		return;
	}

	self->pain_debounce_time = level.time + 3;

	gi.sound (self, CHAN_VOICE, q25_sound_pain, 1, ATTN_NORM, 0);

	if (self->velocity[2] > 100)
	{
		self->monsterinfo.currentmove = &soldierq25_move_pain4;
		return;
	}

	if (skill->value == 3)
		return;		// no pain anims in nightmare

	r = random();

	if (r < 0.33)
		self->monsterinfo.currentmove = &soldierq25_move_pain1;
	else if (r < 0.66)
		self->monsterinfo.currentmove = &soldierq25_move_pain2;
	else
		self->monsterinfo.currentmove = &soldierq25_move_pain3;
}

// ATTACK

void soldierq25_fire (edict_t *self, int flash_number)
{
	vec3_t	start;
	vec3_t	forward, right, up;
	vec3_t	aim;
	vec3_t	dir;
	vec3_t	end;
	float	r, u;
	int		flash_index;
	trace_t	tr;

#ifdef KMQUAKE2_ENGINE_MOD
		flash_index = ionripper_flash[flash_number]; // ripper
#else
		flash_index = blaster_flash[flash_number]; // ripper
#endif

	AngleVectors (self->s.angles, forward, right, NULL);
	G_ProjectSource (self->s.origin, monster_flash_offset[flash_index], forward, right, start);

	if (flash_number == 5 || flash_number == 6)
	{
		VectorCopy (forward, aim);
	}
	else
	{
		VectorCopy (self->enemy->s.origin, end);
		end[2] += self->enemy->viewheight;

		// Lazarus fog reduction of accuracy
		if (self->monsterinfo.visibility < FOG_CANSEEGOOD)
		{
			end[0] += crandom() * 640 * (FOG_CANSEEGOOD - self->monsterinfo.visibility);
			end[1] += crandom() * 640 * (FOG_CANSEEGOOD - self->monsterinfo.visibility);
			end[2] += crandom() * 320 * (FOG_CANSEEGOOD - self->monsterinfo.visibility);
		}

		VectorSubtract (end, start, aim);
		vectoangles (aim, dir);
		AngleVectors (dir, forward, right, up);

		r = crandom()*100;
		u = crandom()*50;
		// Knightmare- adjust spread for expanded world size
#ifdef KMQUAKE2_ENGINE_MOD
		r *= (WORLD_SIZE / 8192);
		u *= (WORLD_SIZE / 8192);
#endif
		VectorMA (start, WORLD_SIZE, forward, end);	// was 8192
		VectorMA (end, r, right, end);
		VectorMA (end, u, up, end);

		VectorSubtract (end, start, aim);
		VectorNormalize (aim);
	}

	tr = gi.trace(start, vec3_origin, vec3_origin, end, self, MASK_SHOT);

	if (tr.ent != world)
	{
		if (tr.ent->svflags & SVF_MONSTER || tr.ent->client || tr.ent->svflags & SVF_DAMAGEABLE || tr.ent->takedamage == DAMAGE_YES)
		{
			if (tr.ent->health > 0) {
				monster_fire_tracker(self, start, aim, 25, 500, tr.ent, MZ2_WIDOW_DISRUPTOR);
				return;
			}
		}
	}
	monster_fire_tracker(self, start, aim, 25, 500, NULL, MZ2_WIDOW_DISRUPTOR);
}

// ATTACK1 (blaster/shotgun)

void soldierq25_fire1 (edict_t *self)
{
	soldierq25_fire (self, 0);
}

void soldierq25_attack1_refire1 (edict_t *self)
{
	if (self->enemy->health <= 0)
		return;

	if ( ((skill->value == 3) && (random() < 0.5)) || (range(self, self->enemy) == RANGE_MELEE) )
		self->monsterinfo.nextframe = FRAME_attak102;
	else
		self->monsterinfo.nextframe = FRAME_attak110;
}

mframe_t soldierq25_frames_attack1 [] =
{
	ai_charge, 0,  NULL,
	ai_charge, 0,  NULL,
	ai_charge, 0,  soldierq25_fire1,
	ai_charge, 0,  NULL,
	ai_charge, 0,  NULL,
	ai_charge, 0,  soldierq25_attack1_refire1,
	ai_charge, 0,  NULL,
	ai_charge, 0,  soldierq25_cock,
	ai_charge, 0,  NULL,
	ai_charge, 0,  NULL,
	ai_charge, 0,  NULL,
	ai_charge, 0,  NULL
};
mmove_t soldierq25_move_attack1 = {FRAME_attak101, FRAME_attak112, soldierq25_frames_attack1, soldierq25_run};

// ATTACK2 (blaster/shotgun)

void soldierq25_fire2 (edict_t *self)
{
	soldierq25_fire (self, 1);
}

void soldierq25_attack2_refire1 (edict_t *self)
{
	if (self->enemy->health <= 0)
		return;

	if ( ((skill->value == 3) && (random() < 0.5)) || (range(self, self->enemy) == RANGE_MELEE))
		self->monsterinfo.nextframe = FRAME_attak204;
	else
		self->monsterinfo.nextframe = FRAME_attak216;
}

mframe_t soldierq25_frames_attack2 [] =
{
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, soldierq25_fire2,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, soldierq25_attack2_refire1,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, soldierq25_cock,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL
};
mmove_t soldierq25_move_attack2 = {FRAME_attak201, FRAME_attak218, soldierq25_frames_attack2, soldierq25_run};

// ATTACK3 (duck and shoot)

void soldierq25_fire3 (edict_t *self)
{
	soldierh_duck_down (self);
	soldierq25_fire (self, 2);
}

mframe_t soldierq25_frames_attack3 [] =
{
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, soldierq25_fire3,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, soldierh_attack3_refire,
	ai_charge, 0, soldierh_duck_up,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL
};
mmove_t soldierq25_move_attack3 = {FRAME_attak301, FRAME_attak309, soldierq25_frames_attack3, soldierq25_run};

// ATTACK6 (run & shoot)

void soldierq25_fire8 (edict_t *self)
{
	soldierq25_fire (self, 7);
}

mframe_t soldierq25_frames_attack6 [] =
{
	ai_charge, 10, NULL,
	ai_charge,  4, NULL,
	ai_charge, 12, NULL,
	ai_charge, 11, soldierq25_fire8,
	ai_charge, 13, NULL,
	ai_charge, 18, NULL,
	ai_charge, 15, NULL,
	ai_charge, 14, NULL,
	ai_charge, 11, NULL,
	ai_charge,  8, NULL,
	ai_charge, 11, NULL,
	ai_charge, 12, NULL,
	ai_charge, 12, NULL,
	ai_charge, 17, soldierh_attack6_refire
};
mmove_t soldierq25_move_attack6 = {FRAME_runs01, FRAME_runs14, soldierq25_frames_attack6, soldierq25_run};

void soldierq25_attack (edict_t *self)
{
	float r, chance;

	monster_done_dodge (self);

	if (self->monsterinfo.attack_state == AS_BLIND)
	{
		if (self->monsterinfo.blind_fire_delay < 1.0)
			chance = 1.0;
		else if (self->monsterinfo.blind_fire_delay < 7.5)
			chance = 0.4;
		else
			chance = 0.1;

		r = random();

		self->monsterinfo.blind_fire_delay += 2.1 + 2.0 + random()*3.0;

		if (VectorCompare (self->monsterinfo.blind_fire_target, vec3_origin))
			return;

		if (r > chance)
			return;

		self->monsterinfo.aiflags |= AI_MANUAL_STEERING;
		self->monsterinfo.currentmove = &soldierq25_move_attack1;
		self->monsterinfo.attack_finished = level.time + 1.5 + random();
		return;
	}

	if ((!(self->monsterinfo.aiflags & (AI_BLOCKED|AI_STAND_GROUND))) &&
		(range(self, self->enemy) >= RANGE_NEAR) && 
		(random() < (skill->value*0.25)))
	{
		self->monsterinfo.currentmove = &soldierq25_move_attack6;
	}
	else
	{
		if (random() < 0.5)
			self->monsterinfo.currentmove = &soldierq25_move_attack1;
		else
			self->monsterinfo.currentmove = &soldierq25_move_attack2;
	}
}

// SIGHT

void soldierq25_sight (edict_t *self, edict_t *other)
{
	if (random() < 0.5)
		gi.sound (self, CHAN_VOICE, q25_sound_sight1, 1, ATTN_NORM, 0);
	else
		gi.sound (self, CHAN_VOICE, q25_sound_sight2, 1, ATTN_NORM, 0);

	if ((skill->value > 0) && (range(self, self->enemy) >= RANGE_MID))
		if (random() > 0.5)
			self->monsterinfo.currentmove = &soldierq25_move_attack6;
}

// NEW DODGE CODE

mmove_t soldierq25_move_duck = {FRAME_duck01, FRAME_duck05, soldierh_frames_duck, soldierq25_run};

void soldierq25_sidestep (edict_t *self)
{
	if ((self->monsterinfo.currentmove != &soldierq25_move_attack6))
		self->monsterinfo.currentmove = &soldierq25_move_attack6;
}

void soldierq25_duck (edict_t *self, float eta)
{
	float r;

	monster_duck_down(self);

	if (skill->value == 0)
	{
		self->monsterinfo.nextframe = FRAME_duck01;
		self->monsterinfo.currentmove = &soldierq25_move_duck;
		self->monsterinfo.duck_wait_time = level.time + eta + 1;
		return;
	}

	r = random();

	if (r > (skill->value * 0.3))
	{
		self->monsterinfo.nextframe = FRAME_duck01;
		self->monsterinfo.currentmove = &soldierq25_move_duck;
		self->monsterinfo.duck_wait_time = level.time + eta + (0.1 * (3 - skill->value));
	}
	else
	{
		self->monsterinfo.nextframe = FRAME_attak301;
		self->monsterinfo.currentmove = &soldierq25_move_attack3;
		self->monsterinfo.duck_wait_time = level.time + eta + 1;
	}
	return;
}

// DEATH

void soldierq25_fire6 (edict_t *self)
{
	soldierq25_fire (self, 5);
}

void soldierq25_fire7 (edict_t *self)
{
	soldierq25_fire (self, 6);
}

mframe_t soldierq25_frames_death1 [] =
{
	ai_move, 0,   NULL,
	ai_move, -10, NULL,
	ai_move, -10, NULL,
	ai_move, -10, NULL,
	ai_move, -5,  NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   soldierq25_fire6,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   soldierq25_fire7,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL
};
mmove_t soldierq25_move_death1 = {FRAME_death101, FRAME_death136, soldierq25_frames_death1, soldierh_dead};

void soldierq25_die (edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point)
{
	int		n;

	if (self->health <= self->gib_health && !(self->spawnflags & SF_MONSTER_NOGIB))
	{
		gi.sound (self, CHAN_VOICE, gi.soundindex ("misc/udeath.wav"), 1, ATTN_NORM, 0);
		for (n = 0; n < 3; n++)
			ThrowGib (self, "models/objects/gibs/sm_meat/tris.md2", 0, 0, damage, GIB_ORGANIC);
		ThrowGib (self, "models/objects/gibs/chest/tris.md2", 0, 0, damage, GIB_ORGANIC);
		ThrowHead (self, "models/objects/gibs/head2/tris.md2", 0, 0, damage, GIB_ORGANIC);
		
		self->deadflag = DEAD_DEAD;
		return;
	}

	if (self->deadflag == DEAD_DEAD)
		return;

	self->s.skinnum |= 1;
	self->deadflag = DEAD_DEAD;
	self->takedamage = DAMAGE_YES;
	self->monsterinfo.power_armor_type = POWER_ARMOR_NONE;

	gi.sound (self, CHAN_VOICE, q25_sound_death, 1, ATTN_NORM, 0);

	if (fabs((self->s.origin[2] + self->viewheight) - point[2]) <= 4)
	{
		self->monsterinfo.currentmove = &soldierh_move_death3;
		return;
	}

	n = rand() % 5;
	if (n == 0)
		self->monsterinfo.currentmove = &soldierq25_move_death1;
	else if (n == 1)
		self->monsterinfo.currentmove = &soldierh_move_death2;
	else if (n == 2)
		self->monsterinfo.currentmove = &soldierh_move_death4;
	else if (n == 3)
		self->monsterinfo.currentmove = &soldierh_move_death5;
	else
		self->monsterinfo.currentmove = &soldierh_move_death6;
}

// SPAWN

void SP_monster_soldier_q25 (edict_t *self)
{
	if ( self->style )
		PatchMonsterModel("models/monsters/soldrq25/tris.md2");

	self->s.modelindex = gi.modelindex ("models/monsters/soldrq25/tris.md2");
	self->monsterinfo.scale = MODEL_SCALE;
	VectorSet (self->mins, -16, -16, -24);
	VectorSet (self->maxs, 16, 16, 32);
	self->movetype = MOVETYPE_STEP;
	self->solid = SOLID_BBOX;

	q25_sound_pain = gi.soundindex ("soldrq25/pain.wav");
	q25_sound_death = gi.soundindex ("soldrq25/deth3.wav");
	q25_sound_idle =	gi.soundindex ("soldrq25/idle.wav");
	q25_sound_sight1 =	gi.soundindex ("soldrq25/sight1.wav");
	q25_sound_sight2 =	q25_sound_sight2;
	q25_sound_cock =	gi.soundindex ("infantry/infatck3.wav");

	if (!self->mass)
		self->mass = 100;

	self->pain = soldierq25_pain;
	self->die = soldierq25_die;

	self->monsterinfo.stand = soldierq25_stand;
	self->monsterinfo.walk = soldierh_walk;
	self->monsterinfo.run = soldierq25_run;
	self->monsterinfo.dodge = M_MonsterDodge;
	self->monsterinfo.attack = soldierq25_attack;
	self->monsterinfo.melee = NULL;
	self->monsterinfo.sight = soldierq25_sight;

	//=====
//ROGUE
	self->monsterinfo.blocked = soldier_blocked;
	self->monsterinfo.duck = soldierq25_duck;
	self->monsterinfo.unduck = monster_duck_up;
	self->monsterinfo.sidestep = soldierq25_sidestep;
//ROGUE
//=====

	if (monsterjump->value)
	{
		self->monsterinfo.jump = soldierq25_jump;
		self->monsterinfo.jumpup = 48;
		self->monsterinfo.jumpdn = 160;
	}

	// Lazarus
	if (self->powerarmor)
	{
		if (self->powerarmortype == 1)
			self->monsterinfo.power_armor_type = POWER_ARMOR_SCREEN;
		else
			self->monsterinfo.power_armor_type = POWER_ARMOR_SHIELD;
		self->monsterinfo.power_armor_power = self->powerarmor;
	}

	if (!self->monsterinfo.flies)
		self->monsterinfo.flies = 0.40;

	gi.linkentity (self);

	self->monsterinfo.currentmove = &soldierq25_move_stand3;	
	if (self->health < 0)
	{
		mmove_t	*deathmoves[] = {&soldierq25_move_death1,
			                     &soldierh_move_death2,
								 &soldierh_move_death3,
								 &soldierh_move_death4,
								 &soldierh_move_death5,
								 &soldierh_move_death6,
								 NULL};
		M_SetDeath (self, (mmove_t **)&deathmoves);
	}
	walkmonster_start (self);
}

void SP_monster_soldier_dist(edict_t* self)
{
	float r;
	
	if (deathmatch->value)
	{
		G_FreeEdict(self);
		return;
	}

	// cache these like widow2 does?
	gi.soundindex ("weapons/disrupt.wav");
	gi.soundindex ("weapons/disint2.wav");
	gi.modelindex ("models/proj/disintegrator/tris.md2");

	self->common_name = "Disruptor Guard";
	self->class_id = ENTITY_MONSTER_SOLDIER_DIST;

	if (!self->health)
		self->health = 80;
	if (!self->gib_health)
		self->gib_health = -40;

	// PMM - blindfire
	self->monsterinfo.blindfire = false;

	// Knightmare- call generic spawn function LAST, because it
	// calls walkmonster_start, which the health and everything else need to be set up for
	SP_monster_soldier_q25(self);

	r = random();

	if (r < 0.80)
	{
		self->s.skinnum = 0 + 6 * self->style;
		self->skinnum = 0;	// Knightmare- simplify skinnum checks by excluding custom styles
	}
	else if (r < 0.90)
	{
		self->s.skinnum = 2 + 6 * self->style;
		self->skinnum = 2;	// Knightmare- simplify skinnum checks by excluding custom styles
	}
	else
	{
		self->s.skinnum = 4 + 6 * self->style;
		self->skinnum = 4;	// Knightmare- simplify skinnum checks by excluding custom styles
	}
}
