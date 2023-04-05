# -------------------------------
# SPDX-License-Identifier: ISC
#
# Copyright © 2023 Daniel Wolf <<nephatrine@gmail.com>>
#
# Permission to use, copy, modify, and/or distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
# REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
# AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
# INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
# LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
# OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
# PERFORMANCE OF THIS SOFTWARE.
# -------------------------------

cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
project(
	QuakeII-Game25
	DESCRIPTION "25th Anniversary Game Module"
	LANGUAGES C)

# ================= GAME LIBRARY =============== #

set(GAME25_SOURCES
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/dm_ball.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/dm_tag.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/fmod.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/g_ai.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/g_camera.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/g_chase.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/g_cmds.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/g_combat.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/g_crane.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/g_fog.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/g_func.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/g_items.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/g_jetpack.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/g_lights.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/g_local.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/g_lock.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/g_main.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/g_mappack.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/g_misc.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/g_misc_laz.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/g_misc_nm.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/g_misc_q1.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/g_model.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/g_monster.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/g_newai.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/g_newdm.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/g_newfnc.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/g_newtarg.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/g_newtrig.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/g_newutils.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/g_newweap.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/g_patchplayermodels.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/g_pendulum.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/g_phys.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/g_reflect.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/g_save.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/g_sound.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/g_spawn.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/g_sphere.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/g_svcmds.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/g_target.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/g_target_laz.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/g_thing.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/g_tracktrain.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/g_trigger.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/g_turret.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/g_utils.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/g_utils_q1.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/g_vehicle.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/g_weapon.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/g_weapon_km.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/g_weapon_lm.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/g_weapon_q1.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/g_weapon_xatrix.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/game.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/km_cvar.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/km_cvar.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/laz_misc.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_actor.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_actor.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_actor_weap.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_berserk.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_berserk.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_boss2.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_boss2.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_boss3.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_boss31.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_boss31.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_boss32.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_boss32.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_boss5.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_brain.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_brain.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_brainbeta.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_carrier.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_carrier.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_chick.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_chick.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_dog.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_dog.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_fixbot.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_fixbot.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_flash.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_flipper.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_flipper.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_float.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_float.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_flyer.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_flyer.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_gekk.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_gekk.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_gladb.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_gladiator.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_gladiator.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_gunner.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_gunner.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_hover.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_hover.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_infantry.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_infantry.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_insane.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_insane.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_medic.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_medic.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_move.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_mutant.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_mutant.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_parasite.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_parasite.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_player.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_q1dog.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_q1dog.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_q1enforcer.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_q1enforcer.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_q1fiend.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_q1fiend.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_q1freddie.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_q1freddie.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_q1grunt.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_q1grunt.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_q1hknight.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_q1hknight.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_q1knight.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_q1knight.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_q1ogre.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_q1ogre.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_q1rotfish.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_q1rotfish.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_q1scrag.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_q1scrag.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_q1shalrath.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_q1shalrath.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_q1shambler.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_q1shambler.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_q1tarbaby.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_q1tarbaby.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_q1zombie.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_q1zombie.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_rider.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_soldier.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_soldier.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_soldierh.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_stalker.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_stalker.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_supertank.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_supertank.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_tank.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_tank.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_turret.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_turret.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_vulture.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_vulture.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_widow.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_widow.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_widow2.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/m_widow2.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/menu.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/p_chasecam.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/p_client.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/p_hud.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/p_menu.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/p_menu.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/p_text.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/p_text.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/p_trail.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/p_view.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/p_weapon.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/pak.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/q_shared.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/q_shared.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/z_acannon.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/z_ai.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/z_anim.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/z_boss.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/z_boss.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/z_camera.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/z_handler.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/z_handler.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/z_hound.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/z_hound.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/z_item.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/z_sentien.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/z_sentien.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/z_trigger.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/missionpack/z_weapon.c")

# GAME DLL NAMING

if(NOT DEFINED GAME25_NAME)
	if(CMAKE_SIZEOF_VOID_P EQUAL 8 AND CMAKE_SYSTEM_PROCESSOR MATCHES "AMD64|X86|x86_64|i[0-9]86")
		if(WIN32)
			set(GAME25_NAME "gamex64")
		else()
			set(GAME25_NAME "gamex86_64")
		endif()
	elseif(CMAKE_SIZEOF_VOID_P EQUAL 4 AND CMAKE_SYSTEM_PROCESSOR MATCHES "AMD64|X86|x86_64|i[0-9]86")
		if(WIN32)
			set(GAME25_NAME "gamex86")
		else()
			set(GAME25_NAME "gamei386")
		endif()
	else()
		set(GAME25_NAME "game")
	endif()
endif()

# SET UP MODULE TARGET

set(CMAKE_C_VISIBILITY_PRESET hidden)
set(CMAKE_SHARED_MODULE_PREFIX "")

add_library(game25 MODULE ${GAME25_SOURCES})
set_target_properties(game25 PROPERTIES
	DEFINE_SYMBOL "GAME_EXPORTS"
	OUTPUT_NAME "${GAME25_NAME}")

if(NOT WIN32 OR NOT MSVC)
	target_compile_definitions(game25 PRIVATE "C_ONLY")
endif()
if(UNIX)
	target_link_libraries(game25 PRIVATE "m" ${CMAKE_DL_LIBS})
endif()

install(TARGETS game25 DESTINATION ".")

# This is an abomination.

if(WIN32)
	set(EXTRACTFUNCS_EXECUTABLE "${CMAKE_CURRENT_SOURCE_DIR}/missionpack/extractfuncs/extractfuncs.exe")
else()
	set(EXTRACTFUNCS_EXECUTABLE "${CMAKE_CURRENT_SOURCE_DIR}/missionpack/extractfuncs/extractfuncs")
endif()

add_custom_command(TARGET game25 PRE_BUILD
	COMMAND "${EXTRACTFUNCS_EXECUTABLE}" *.c -o g_func_list.h g_func_decs.h
	COMMAND "${EXTRACTFUNCS_EXECUTABLE}" *.c -t mmove_t -o g_mmove_list.h g_mmove_decs.h
	WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/missionpack"
)

# TODO: There is apparently no consensus on the name for 64-bit dll/so.

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	add_custom_command(TARGET game25 POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:game25> "game${CMAKE_SHARED_MODULE_SUFFIX}"
	)
	install(PROGRAMS "game${CMAKE_SHARED_MODULE_SUFFIX}" DESTINATION ".")
endif()

# PACK IT UP, PACK IT IN, LET ME BEGIN

string(TOLOWER "q25-${GAME25_NAME}-${CMAKE_SYSTEM_NAME}" CPACK_PACKAGE_FILE_NAME)
set(CPACK_SOURCE_PACKAGE_FILE_NAME "q25-source")
set(CPACK_SOURCE_IGNORE_FILES "build.*/" ".*~$" "/[.]")
if(WIN32)
	set(CPACK_GENERATOR "ZIP" "7Z")
	set(CPACK_SOURCE_GENERATOR "ZIP")
else()
	set(CPACK_GENERATOR "TGZ" "TXZ")
	set(CPACK_SOURCE_GENERATOR "TGZ")
endif()
include(CPack)
