/*****************************************************************************
*
*  PROJECT:     Multi Theft Auto v1.0
*  LICENSE:     See LICENSE in the top level directory
*  FILE:        Shared/sdk/net/rpc_enums.h
*  PURPOSE:     Lua common functions
*  DEVELOPERS:  Christian Myhre Lundheim <>
*               Jax <>
*               Alberto Alonso <rydencillo@gmail.com>
*
*  Multi Theft Auto is available from http://www.multitheftauto.com/
*
*****************************************************************************/

#pragma once

enum eRPCFunctions
{
    DONT_USE_0 = 0,
    SET_TIME,
    SET_WEATHER,
    SET_WEATHER_BLENDED,
    SET_MINUTE_DURATION,

    SET_ELEMENT_PARENT,
    SET_ELEMENT_DATA,
    SET_ELEMENT_POSITION,
    SET_ELEMENT_VELOCITY,
    SET_ELEMENT_INTERIOR,
    SET_ELEMENT_DIMENSION,
    ATTACH_ELEMENTS,
    DETACH_ELEMENTS,
    SET_ELEMENT_ALPHA,
    SET_ELEMENT_NAME,
    SET_ELEMENT_HEALTH,
    SET_ELEMENT_MODEL,
    SET_ELEMENT_ATTACHED_OFFSETS,
    
    SET_PLAYER_MONEY,            
    SHOW_PLAYER_HUD_COMPONENT,
    FORCE_PLAYER_MAP,
    SET_PLAYER_NAMETAG_TEXT,
    REMOVE_PLAYER_NAMETAG_COLOR,
    SET_PLAYER_NAMETAG_COLOR,
    SET_PLAYER_NAMETAG_SHOWING,                 

    SET_PED_ARMOR,
    SET_PED_ROTATION,
    GIVE_PED_JETPACK,
    REMOVE_PED_JETPACK,
    REMOVE_PED_CLOTHES,
    SET_PED_GRAVITY,
    SET_PED_CHOKING,
    SET_PED_FIGHTING_STYLE,
    SET_PED_MOVE_ANIM,
    WARP_PED_INTO_VEHICLE,
    REMOVE_PED_FROM_VEHICLE,
    SET_PED_DOING_GANG_DRIVEBY,
    SET_PED_ANIMATION,
    SET_PED_ON_FIRE,
    SET_PED_HEADLESS,
    SET_PED_FROZEN,
    RELOAD_PED_WEAPON,

    DESTROY_ALL_VEHICLES,
    FIX_VEHICLE,
    BLOW_VEHICLE,
    SET_VEHICLE_ROTATION,
    SET_VEHICLE_TURNSPEED,
    SET_VEHICLE_COLOR,
    SET_VEHICLE_LOCKED,
    SET_VEHICLE_DOORS_UNDAMAGEABLE,
    SET_VEHICLE_SIRENE_ON,
    SET_VEHICLE_LANDING_GEAR_DOWN,
    SET_HELICOPTER_ROTOR_SPEED,
    ADD_VEHICLE_UPGRADE,
    ADD_ALL_VEHICLE_UPGRADES,
    REMOVE_VEHICLE_UPGRADE,
    SET_VEHICLE_DAMAGE_STATE,
    SET_VEHICLE_OVERRIDE_LIGHTS,
    SET_VEHICLE_ENGINE_STATE,
    SET_VEHICLE_DIRT_LEVEL,
    SET_VEHICLE_DAMAGE_PROOF,
    SET_VEHICLE_PAINTJOB,
    SET_VEHICLE_FUEL_TANK_EXPLODABLE,
    SET_VEHICLE_WHEEL_STATES,
    SET_VEHICLE_FROZEN,
    SET_TRAIN_DERAILED,
    SET_TRAIN_DERAILABLE,
    SET_TRAIN_DIRECTION,
    SET_TRAIN_SPEED,
    SET_TAXI_LIGHT_ON,
    SET_VEHICLE_HEADLIGHT_COLOR,

    GIVE_WEAPON,
    TAKE_WEAPON,
    TAKE_ALL_WEAPONS,
    GIVE_WEAPON_AMMO,
    TAKE_WEAPON_AMMO,
    SET_WEAPON_AMMO,
    SET_WEAPON_SLOT,

    DESTROY_ALL_BLIPS,
    SET_BLIP_ICON,
    SET_BLIP_SIZE,
    SET_BLIP_COLOR,
    SET_BLIP_ORDERING,

    DESTROY_ALL_OBJECTS,
    SET_OBJECT_ROTATION,
    MOVE_OBJECT,
    STOP_OBJECT,

    DESTROY_ALL_RADAR_AREAS,
    SET_RADAR_AREA_SIZE,
    SET_RADAR_AREA_COLOR,
    SET_RADAR_AREA_FLASHING,

    DESTROY_ALL_MARKERS,
    SET_MARKER_TYPE,
    SET_MARKER_COLOR,
    SET_MARKER_SIZE,
    SET_MARKER_TARGET,
    SET_MARKER_ICON,

    DESTROY_ALL_PICKUPS,
    SET_PICKUP_TYPE,
    SET_PICKUP_VISIBLE,

    PLAY_SOUND,

    BIND_KEY,
    UNBIND_KEY,
    BIND_COMMAND,
    UNBIND_COMMAND,
    TOGGLE_CONTROL_ABILITY,
    TOGGLE_ALL_CONTROL_ABILITY,
    SET_CONTROL_STATE,
    FORCE_RECONNECT,

    SET_TEAM_NAME,
    SET_TEAM_COLOR,
    SET_PLAYER_TEAM,
    SET_TEAM_FRIENDLY_FIRE,

    SET_WANTED_LEVEL,

    SET_CAMERA_MATRIX,
    SET_CAMERA_TARGET,
    SET_CAMERA_INTERIOR,
    FADE_CAMERA,

    SHOW_CURSOR,
    SHOW_CHAT,

    SET_GRAVITY,
    SET_GAME_SPEED,
    SET_WAVE_HEIGHT,
    SET_SKY_GRADIENT,
    RESET_SKY_GRADIENT,
    SET_BLUR_LEVEL,
    SET_FPS_LIMIT,
    SET_GARAGE_OPEN,
    RESET_MAP_INFO,
    SET_GLITCH_ENABLED,
    SET_CLOUDS_ENABLED,

    REMOVE_ELEMENT_DATA,

    HANDLING_SET_DEFAULT,
    HANDLING_RESTORE_DEFAULT,
    HANDLING_SET_PROPERTY,

    TOGGLE_DEBUGGER,

    SET_WATER_LEVEL,
    SET_WATER_VERTEX_POSITION,

    // bitstream version 0x0c
    SET_ELEMENT_DOUBLESIDED,

    SET_TRAFFIC_LIGHT_STATE,

    SET_VEHICLE_TURRET_POSITION,

    SET_OBJECT_SCALE,

    SET_ELEMENT_COLLISIONS_ENABLED,

    SET_JETPACK_MAXHEIGHT,

    NUM_RPC_FUNCS
};
