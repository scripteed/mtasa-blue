/*****************************************************************************
*
*  PROJECT:     Multi Theft Auto v1.0
*  LICENSE:     See LICENSE in the top level directory
*  FILE:        mods/deathmatch/logic/luadefs/CLuaHandlingDefs.cpp
*  PURPOSE:     Lua vehicle handling definitions class
*  DEVELOPERS:  Christian Myhre Lundheim <>
*               Florian Busse <flobu@gmx.net>
*
*  Multi Theft Auto is available from http://www.multitheftauto.com/
*
*****************************************************************************/

#include "StdInc.h"

#define lua_istype(luavm, number,type) (lua_type(luavm,number) == type)

void CLuaHandlingDefs::LoadFunctions ( void )
{
    // Set
    CLuaCFunctions::AddFunction ( "setVehicleHandling", CLuaHandlingDefs::SetVehicleHandling );
    CLuaCFunctions::AddFunction ( "setModelHandling", CLuaHandlingDefs::SetModelHandling );

    // Get
    CLuaCFunctions::AddFunction ( "getVehicleHandling", CLuaHandlingDefs::GetVehicleHandling );
    CLuaCFunctions::AddFunction ( "getModelHandling", CLuaHandlingDefs::GetModelHandling );
    CLuaCFunctions::AddFunction ( "getOriginalHandling", CLuaHandlingDefs::GetOriginalHandling );
}

int CLuaHandlingDefs::SetVehicleHandling ( lua_State* luaVM )
{
    if ( lua_type ( luaVM, 1 ) == LUA_TLIGHTUSERDATA )
    {
        CVehicle* pVehicle = lua_tovehicle ( luaVM, 1 );
        if ( pVehicle )
        {
            if ( lua_type ( luaVM, 2 ) == LUA_TSTRING )
            {
                eHandlingProperty eProperty = m_pHandlingManager->GetPropertyEnumFromName ( lua_tostring ( luaVM, 2 ) );
                if ( eProperty )
                {
                    if ( lua_type ( luaVM, 3 ) == LUA_TNIL )
                    {
                        bool bUseOriginal = false;
                        if ( lua_type ( luaVM, 4 ) == LUA_TBOOLEAN )
                            bUseOriginal = lua_toboolean ( luaVM, 4 ) ? true : false;

                        if ( CStaticFunctionDefinitions::ResetVehicleHandlingProperty ( pVehicle, eProperty, bUseOriginal ) )
                        {
                            lua_pushboolean ( luaVM, true );
                            return 1;
                        }
                    }
                    else
                    {
                        switch ( eProperty )
                        {                
                            case HANDLING_MASS:
                            case HANDLING_TURNMASS:
                            case HANDLING_DRAGCOEFF:
                            case HANDLING_TRACTIONMULTIPLIER:
                            case HANDLING_ENGINEACCELERATION:
                            case HANDLING_ENGINEINERTIA:
                            case HANDLING_MAXVELOCITY:
                            case HANDLING_BRAKEDECELERATION:
                            case HANDLING_BRAKEBIAS:
                            case HANDLING_STEERINGLOCK:
                            case HANDLING_TRACTIONLOSS:
                            case HANDLING_TRACTIONBIAS:
                            case HANDLING_SUSPENSION_FORCELEVEL:
                            case HANDLING_SUSPENSION_DAMPING:
                            case HANDLING_SUSPENSION_HIGHSPEEDDAMPING:
                            case HANDLING_SUSPENSION_UPPER_LIMIT:
                            case HANDLING_SUSPENSION_LOWER_LIMIT:
                            case HANDLING_SUSPENSION_FRONTREARBIAS:
                            case HANDLING_SUSPENSION_ANTIDIVEMULTIPLIER:
                            case HANDLING_COLLISIONDAMAGEMULTIPLIER:
                            case HANDLING_SEATOFFSETDISTANCE:
                                {
                                   if ( lua_type ( luaVM, 3 ) == LUA_TNUMBER )
                                    {
                                        float fValue = (float)lua_tonumber ( luaVM, 3 );
                                        if ( CStaticFunctionDefinitions::SetVehicleHandling ( pVehicle, eProperty, fValue ) )
                                        {
                                            lua_pushboolean ( luaVM, true );
                                            return 1;
                                        }
                                    }
                                    m_pScriptDebugging->LogBadPointer ( luaVM, "setVehicleHandling", "value", 3 );
                                    break;
                                }
                            case HANDLING_PERCENTSUBMERGED: // unsigned int
                            case HANDLING_MONETARY:
                            case HANDLING_HANDLINGFLAGS:
                            case HANDLING_MODELFLAGS:
                                {
                                    if ( lua_type ( luaVM, 3 ) == LUA_TNUMBER )
                                    {
                                        unsigned int uiValue = (unsigned int)lua_tonumber ( luaVM, 3 );
                                        if ( CStaticFunctionDefinitions::SetVehicleHandling ( pVehicle, eProperty, uiValue ) )
                                        {
                                            lua_pushboolean ( luaVM, true );
                                            return 1;
                                        }
                                    }
                                    m_pScriptDebugging->LogBadPointer ( luaVM, "setVehicleHandling", "value", 3 );
                                    break;
                                }
                            case HANDLING_NUMOFGEARS:
                            case HANDLING_ANIMGROUP:
                                {
                                    if ( lua_type ( luaVM, 3 ) == LUA_TNUMBER )
                                    {
                                        unsigned char ucValue = (unsigned char)lua_tonumber ( luaVM, 3 );
                                        if ( CStaticFunctionDefinitions::SetVehicleHandling ( pVehicle, eProperty, ucValue ) )
                                        {
                                            lua_pushboolean ( luaVM, true );
                                            return 1;
                                        }
                                    }
                                    m_pScriptDebugging->LogBadPointer ( luaVM, "setVehicleHandling", "value", 3 );
                                    break;
                                }
                            case HANDLING_CENTEROFMASS:
                                {
                                    if ( lua_type ( luaVM, 3 ) == LUA_TNUMBER && lua_type ( luaVM, 4 ) == LUA_TNUMBER && lua_type ( luaVM, 5 ) == LUA_TNUMBER )
                                    {
                                        float fX = (float)lua_tonumber ( luaVM, 3 );
                                        float fY = (float)lua_tonumber ( luaVM, 4 );
                                        float fZ = (float)lua_tonumber ( luaVM, 5 );
                                        CVector tempVec ( fX, fY, fZ );

                                        if ( CStaticFunctionDefinitions::SetVehicleHandling ( pVehicle, eProperty, tempVec ) )
                                        {
                                            lua_pushboolean ( luaVM, true );
                                            return 1;
                                        }
                                    }
                                    m_pScriptDebugging->LogBadPointer ( luaVM, "setVehicleHandling", "value", 3 );
                                    break;
                                }
                            case HANDLING_DRIVETYPE:
                            case HANDLING_ENGINETYPE:
                            case HANDLING_HEADLIGHT:
                            case HANDLING_TAILLIGHT:
                                {
                                    if ( lua_type ( luaVM, 3 ) == LUA_TSTRING )
                                    {
                                        if ( CStaticFunctionDefinitions::SetVehicleHandling ( pVehicle, eProperty, std::string ( lua_tostring ( luaVM, 3 ) ) ) )
                                        {
                                            lua_pushboolean ( luaVM, true );
                                            return 1;
                                        }
                                    }
                                    m_pScriptDebugging->LogBadPointer ( luaVM, "setVehicleHandling", "value", 3 );
                                    break;
                                }
                            case HANDLING_ABS:
                                {
                                    if ( lua_type ( luaVM, 3 ) == LUA_TBOOLEAN )
                                    {
                                        if ( CStaticFunctionDefinitions::SetVehicleHandling ( pVehicle, eProperty, lua_toboolean ( luaVM, 3 ) ? 1.0f : 0.0f ) )
                                        {
                                            lua_pushboolean ( luaVM, true );
                                            return 1;
                                        }
                                    }
                                    m_pScriptDebugging->LogBadPointer ( luaVM, "setVehicleHandling", "value", 3 );
                                    break;
                                }
                            case HANDLING_MAX:
                                {
                                    m_pScriptDebugging->LogBadPointer ( luaVM, "setVehicleHandling", "property", 2 );
                                    break;
                                }
                        }
                    }
                }
            }
            else if ( lua_type ( luaVM, 2 ) == LUA_TNIL || lua_type ( luaVM, 2 ) == LUA_TBOOLEAN )
            {
                bool bUseOriginal = false;
                if ( lua_type ( luaVM, 2 ) == LUA_TBOOLEAN )
                    bUseOriginal = lua_toboolean ( luaVM, 2 ) ? true : false;

                if ( CStaticFunctionDefinitions::ResetVehicleHandling ( pVehicle, bUseOriginal ) )
                {
                    lua_pushboolean ( luaVM, true );
                    return 1;
                }
            }
            else
                m_pScriptDebugging->LogBadPointer ( luaVM, "setVehicleHandling", "property", 2 );
        }
    }
    else
        m_pScriptDebugging->LogBadType ( luaVM, "setVehicleHandling" );

    lua_pushboolean ( luaVM, false );
    return 1;
}

int CLuaHandlingDefs::SetModelHandling ( lua_State* luaVM )
{
    if ( lua_type ( luaVM, 1 ) == LUA_TNUMBER )
    {
        eVehicleTypes eModel = static_cast < eVehicleTypes > ( (int)lua_tonumber ( luaVM, 1 ) );
        if ( eModel )
        {
            if ( lua_type ( luaVM, 2 ) == LUA_TSTRING )
            {
                eHandlingProperty eProperty = m_pHandlingManager->GetPropertyEnumFromName ( lua_tostring ( luaVM, 2 ) );
                
                if ( eProperty )
                {
                    if ( lua_type ( luaVM, 3 ) == LUA_TNIL )
                    {
                        if ( CStaticFunctionDefinitions::ResetModelHandlingProperty ( eModel, eProperty ) )
                        {
                            lua_pushboolean ( luaVM, true );
                            return 1;
                        }
                    }
                    else
                    {
                        switch ( eProperty )
                        {                
                            case HANDLING_MASS:
                            case HANDLING_TURNMASS:
                            case HANDLING_DRAGCOEFF:
                            case HANDLING_TRACTIONMULTIPLIER:
                            case HANDLING_ENGINEACCELERATION:
                            case HANDLING_ENGINEINERTIA:
                            case HANDLING_MAXVELOCITY:
                            case HANDLING_BRAKEDECELERATION:
                            case HANDLING_BRAKEBIAS:
                            case HANDLING_STEERINGLOCK:
                            case HANDLING_TRACTIONLOSS:
                            case HANDLING_TRACTIONBIAS:
                            case HANDLING_SUSPENSION_FORCELEVEL:
                            case HANDLING_SUSPENSION_DAMPING:
                            case HANDLING_SUSPENSION_HIGHSPEEDDAMPING:
                            case HANDLING_SUSPENSION_UPPER_LIMIT:
                            case HANDLING_SUSPENSION_LOWER_LIMIT:
                            case HANDLING_SUSPENSION_FRONTREARBIAS:
                            case HANDLING_SUSPENSION_ANTIDIVEMULTIPLIER:
                            case HANDLING_COLLISIONDAMAGEMULTIPLIER:
                            case HANDLING_SEATOFFSETDISTANCE:
                            case HANDLING_PERCENTSUBMERGED: // unsigned int
                            case HANDLING_MONETARY:
                            case HANDLING_HANDLINGFLAGS:
                            case HANDLING_MODELFLAGS:
                            case HANDLING_NUMOFGEARS:
                            case HANDLING_ANIMGROUP:
                                {
                                    if ( lua_type ( luaVM, 3 ) == LUA_TNUMBER )
                                    {
                                        float fValue = (float)lua_tonumber ( luaVM, 3 );
                                        if ( CStaticFunctionDefinitions::SetModelHandling ( eModel, eProperty, fValue ) )
                                        {
                                            lua_pushboolean ( luaVM, true );
                                            return 1;
                                        }
                                    }
                                    m_pScriptDebugging->LogBadPointer ( luaVM, "setModelHandling", "value", 3 );
                                    break;
                                }
                            case HANDLING_CENTEROFMASS:
                                {
                                    if ( lua_type ( luaVM, 3 ) == LUA_TNUMBER && lua_type ( luaVM, 4 ) == LUA_TNUMBER && lua_type ( luaVM, 5 ) == LUA_TNUMBER )
                                    {
                                        float fX = (float)lua_tonumber ( luaVM, 3 );
                                        float fY = (float)lua_tonumber ( luaVM, 4 );
                                        float fZ = (float)lua_tonumber ( luaVM, 5 );
                                        CVector tempVec ( fX, fY, fZ );

                                        if ( CStaticFunctionDefinitions::SetModelHandling ( eModel, eProperty, tempVec ) )
                                        {
                                            lua_pushboolean ( luaVM, true );
                                            return 1;
                                        }
                                    }
                                    m_pScriptDebugging->LogBadPointer ( luaVM, "setModelHandling", "value", 3 );
                                    break;
                                }
                            case HANDLING_DRIVETYPE:
                            case HANDLING_ENGINETYPE:
                            case HANDLING_HEADLIGHT:
                            case HANDLING_TAILLIGHT:
                                {
                                    if ( lua_type ( luaVM, 3 ) == LUA_TSTRING )
                                    {
                                        if ( CStaticFunctionDefinitions::SetModelHandling ( eModel, eProperty, std::string ( lua_tostring ( luaVM, 3 ) ) ) )
                                        {
                                            lua_pushboolean ( luaVM, true );
                                            return 1;
                                        }
                                    }
                                }
                            case HANDLING_ABS:
                                {
                                    if ( lua_type ( luaVM, 3 ) == LUA_TBOOLEAN )
                                    {
                                        if ( CStaticFunctionDefinitions::SetModelHandling ( eModel, eProperty, lua_toboolean ( luaVM, 3 ) ? 1.0f : 0.0f ) )
                                        {
                                            lua_pushboolean ( luaVM, true );
                                            return 1;
                                        }
                                    }
                                    m_pScriptDebugging->LogBadPointer ( luaVM, "setModelHandling", "value", 3 );
                                    break;
                                }
                            case HANDLING_MAX:
                                {
                                    m_pScriptDebugging->LogBadPointer ( luaVM, "setModelHandling", "property", 2 );
                                }
                        }
                    }
                }
            }
            else if ( lua_type ( luaVM, 2 ) == LUA_TNIL )
            {
                if ( CStaticFunctionDefinitions::ResetModelHandling ( eModel ) )
                {
                    lua_pushboolean ( luaVM, true );
                    return 1;
                }
            }
            else
                m_pScriptDebugging->LogBadPointer ( luaVM, "setModelHandling", "property", 2 );
        }
    }
    else
        m_pScriptDebugging->LogBadType ( luaVM, "setModelHandling" );
    
    lua_pushboolean ( luaVM, false );
    return 1;
}

int CLuaHandlingDefs::GetVehicleHandling ( lua_State* luaVM )
{
    if ( lua_type ( luaVM, 1 ) == LUA_TLIGHTUSERDATA )
    {
        CVehicle* pVehicle = lua_tovehicle ( luaVM, 1 );
        if ( pVehicle )
        {
            if ( lua_type ( luaVM, 2 ) == LUA_TSTRING )
            {
                eHandlingProperty eProperty = m_pHandlingManager->GetPropertyEnumFromName ( lua_tostring ( luaVM, 2 ) );
                if ( eProperty )
                {
                    switch ( eProperty )
                    {
                        case HANDLING_MASS:
                        case HANDLING_TURNMASS:
                        case HANDLING_DRAGCOEFF:
                        case HANDLING_TRACTIONMULTIPLIER:
                        case HANDLING_ENGINEACCELERATION:
                        case HANDLING_ENGINEINERTIA:
                        case HANDLING_MAXVELOCITY:
                        case HANDLING_BRAKEDECELERATION:
                        case HANDLING_BRAKEBIAS:
                        case HANDLING_STEERINGLOCK:
                        case HANDLING_TRACTIONLOSS:
                        case HANDLING_TRACTIONBIAS:
                        case HANDLING_SUSPENSION_FORCELEVEL:
                        case HANDLING_SUSPENSION_DAMPING:
                        case HANDLING_SUSPENSION_HIGHSPEEDDAMPING:
                        case HANDLING_SUSPENSION_UPPER_LIMIT:
                        case HANDLING_SUSPENSION_LOWER_LIMIT:
                        case HANDLING_SUSPENSION_FRONTREARBIAS:
                        case HANDLING_SUSPENSION_ANTIDIVEMULTIPLIER:
                        case HANDLING_COLLISIONDAMAGEMULTIPLIER:
                        case HANDLING_SEATOFFSETDISTANCE:
                        case HANDLING_PERCENTSUBMERGED: // unsigned int
                        case HANDLING_MONETARY:
                        case HANDLING_HANDLINGFLAGS:
                        case HANDLING_MODELFLAGS:
                        case HANDLING_NUMOFGEARS:
                        case HANDLING_ANIMGROUP:
                            {
                                float fValue;
                                if ( CStaticFunctionDefinitions::GetVehicleHandling ( pVehicle, eProperty, fValue ) )
                                {
                                    lua_pushnumber ( luaVM, fValue );
                                    break;
                                }
                            }
                        case HANDLING_CENTEROFMASS:
                            {
                                CVector vecValue;
                                if ( CStaticFunctionDefinitions::GetVehicleHandling ( pVehicle, eProperty, vecValue ) )
                                {
                                    lua_pushnumber ( luaVM, vecValue.fX );
                                    lua_pushnumber ( luaVM, vecValue.fY );
                                    lua_pushnumber ( luaVM, vecValue.fZ );
                                    return 3;
                                }
                            }
                        case HANDLING_DRIVETYPE:
                        case HANDLING_ENGINETYPE:
                        case HANDLING_HEADLIGHT:
                        case HANDLING_TAILLIGHT:
                            {
                                std::string strValue;
                                if ( CStaticFunctionDefinitions::GetVehicleHandling ( pVehicle, eProperty, strValue ) )
                                {
                                    lua_pushstring ( luaVM, strValue.c_str () );
                                    break;
                                }
                            }
                        case HANDLING_ABS:
                            {
                                float fValue;
                                if ( CStaticFunctionDefinitions::GetVehicleHandling ( pVehicle, eProperty, fValue ) )
                                {
                                    lua_pushboolean ( luaVM, fValue ? true : false );
                                    break;
                                }
                            }
                        default:
                            lua_pushboolean ( luaVM, false );
                    }

                    return 1;
                }
                else
                    m_pScriptDebugging->LogBadPointer ( luaVM, "getVehicleHandling", "property", 2 );
            }
            else if ( lua_type ( luaVM, 2 ) == LUA_TNIL || lua_type ( luaVM, 2 ) == LUA_TNONE )
            {
                CHandlingEntry* pEntry = pVehicle->GetHandlingData ();

                lua_newtable ( luaVM );
                lua_pushnumber ( luaVM, pEntry->GetMass() );
                lua_setfield ( luaVM, -2, "mass" );
                lua_pushnumber ( luaVM, pEntry->GetTurnMass() );
                lua_setfield ( luaVM, -2, "turnMass" );
                lua_pushnumber ( luaVM, pEntry->GetDragCoeff() );
                lua_setfield ( luaVM, -2, "dragCoeff" );
                lua_newtable ( luaVM );
                CVector vecCenter = pEntry->GetCenterOfMass ();
                lua_pushnumber ( luaVM, vecCenter.fX );
                lua_setfield ( luaVM, -2, "posX" );
                lua_pushnumber ( luaVM, vecCenter.fY );
                lua_setfield ( luaVM, -2, "posY" );
                lua_pushnumber ( luaVM, vecCenter.fZ );
                lua_setfield ( luaVM, -2, "posZ" );
                lua_setfield ( luaVM, -2, "centerOfMass" );
                lua_pushnumber ( luaVM, pEntry->GetPercentSubmerged() );
                lua_setfield ( luaVM, -2, "percentSubmerged" );
                lua_pushnumber ( luaVM, pEntry->GetTractionMultiplier() );
                lua_setfield ( luaVM, -2, "tractionMultiplier" );
                CHandlingEntry::eDriveType eDriveType=pEntry->GetCarDriveType();
                if (eDriveType==CHandlingEntry::FWD)
                    lua_pushstring(luaVM,"fwd");
                else if (eDriveType==CHandlingEntry::RWD)
                    lua_pushstring(luaVM,"rwd");
                else if (eDriveType==CHandlingEntry::FOURWHEEL)
                    lua_pushstring(luaVM,"awd");
                else // What the ... (yeah, security)
                    lua_pushnil ( luaVM );
                lua_setfield ( luaVM, -2, "driveType" );
                CHandlingEntry::eEngineType eEngineType=pEntry->GetCarEngineType();
                if (eEngineType==CHandlingEntry::PETROL)
                    lua_pushstring(luaVM,"petrol");
                else if (eEngineType==CHandlingEntry::DIESEL)
                    lua_pushstring(luaVM,"diesel");
                else if (eEngineType==CHandlingEntry::ELECTRIC)
                    lua_pushstring(luaVM,"electric");
                else
                    lua_pushnil ( luaVM );
                lua_setfield ( luaVM, -2, "engineType" );
                lua_pushnumber ( luaVM, pEntry->GetNumberOfGears() );
                lua_setfield ( luaVM, -2, "numberOfGears" );
                lua_pushnumber ( luaVM, pEntry->GetEngineAcceleration() );
                lua_setfield ( luaVM, -2, "engineAcceleration" );
                lua_pushnumber ( luaVM, pEntry->GetEngineInertia() );
                lua_setfield ( luaVM, -2, "engineInertia" );
                lua_pushnumber ( luaVM, pEntry->GetMaxVelocity() );
                lua_setfield ( luaVM, -2, "maxVelocity" );
                lua_pushnumber ( luaVM, pEntry->GetBrakeDeceleration() );
                lua_setfield ( luaVM, -2, "brakeDeceleration" );
                lua_pushnumber ( luaVM, pEntry->GetBrakeBias() );
                lua_setfield ( luaVM, -2, "brakeBias" );
                lua_pushboolean ( luaVM, pEntry->GetABS() );
                lua_setfield ( luaVM, -2, "ABS" );
                lua_pushnumber ( luaVM, pEntry->GetSteeringLock() );
                lua_setfield ( luaVM, -2, "steeringLock" );
                lua_pushnumber ( luaVM, pEntry->GetTractionLoss() );
                lua_setfield ( luaVM, -2, "tractionLoss" );
                lua_pushnumber ( luaVM, pEntry->GetTractionBias() );
                lua_setfield ( luaVM, -2, "tractionBias" );
                lua_pushnumber ( luaVM, pEntry->GetSuspensionForceLevel() );
                lua_setfield ( luaVM, -2, "suspensionForceLevel" );
                lua_pushnumber ( luaVM, pEntry->GetSuspensionDamping() );
                lua_setfield ( luaVM, -2, "suspensionDamping" );
                lua_pushnumber ( luaVM, pEntry->GetSuspensionHighSpeedDamping() );
                lua_setfield ( luaVM, -2, "suspensionHighSpeedDamping" );
                lua_pushnumber ( luaVM, pEntry->GetSuspensionUpperLimit() );
                lua_setfield ( luaVM, -2, "suspensionUpperLimit" );
                lua_pushnumber ( luaVM, pEntry->GetSuspensionLowerLimit() );
                lua_setfield ( luaVM, -2, "suspensionLowerLimit" );
                lua_pushnumber ( luaVM, pEntry->GetSuspensionFrontRearBias() );
                lua_setfield ( luaVM, -2, "suspensionFrontRearBias" );
                lua_pushnumber ( luaVM, pEntry->GetSuspensionAntidiveMultiplier() );
                lua_setfield ( luaVM, -2, "suspensionAntidiveMultiplier" );
                lua_pushnumber ( luaVM, pEntry->GetCollisionDamageMultiplier() );
                lua_setfield ( luaVM, -2, "collisionDamageMultiplier" );
                lua_pushnumber ( luaVM, pEntry->GetSeatOffsetDistance() );
                lua_setfield ( luaVM, -2, "seatOffsetDistance" );
                lua_pushnumber ( luaVM, pEntry->GetHandlingFlags() );
                lua_setfield ( luaVM, -2, "handlingFlags" );
                lua_pushnumber ( luaVM, pEntry->GetModelFlags() );
                lua_setfield ( luaVM, -2, "modelFlags" );
                lua_pushnumber ( luaVM, pEntry->GetMonetary() );
                lua_setfield ( luaVM, -2, "monetary" );
                CHandlingEntry::eLightType eHeadType=pEntry->GetHeadLight();
                if (eHeadType==CHandlingEntry::LONG)
                    lua_pushstring(luaVM,"long");
                else if (eHeadType==CHandlingEntry::SMALL)
                    lua_pushstring(luaVM,"small");
                else if (eHeadType==CHandlingEntry::BIG)
                    lua_pushstring(luaVM,"big");
                else
                    lua_pushnil( luaVM );
                lua_setfield ( luaVM, -2, "headLight" );
                CHandlingEntry::eLightType eTailType=pEntry->GetTailLight();
                if (eTailType==CHandlingEntry::LONG)
                    lua_pushstring(luaVM,"long");
                else if (eTailType==CHandlingEntry::SMALL)
                    lua_pushstring(luaVM,"small");
                else if (eTailType==CHandlingEntry::BIG)
                    lua_pushstring(luaVM,"big");
                else
                    lua_pushnil( luaVM );
                lua_setfield ( luaVM, -2, "tailLight" );
                lua_pushnumber ( luaVM, pEntry->GetAnimGroup() );
                lua_setfield ( luaVM, -2, "animGroup" );
                return 1;
            }
            else
                m_pScriptDebugging->LogBadPointer ( luaVM, "getVehicleHandling", "property", 2 );
        }
        else
            m_pScriptDebugging->LogBadPointer ( luaVM, "getVehicleHandling", "vehicle", 1 );
    }
    else
        m_pScriptDebugging->LogBadType ( luaVM, "getVehicleHandling" );

    lua_pushboolean ( luaVM, false );
    return 1;
}


int CLuaHandlingDefs::GetModelHandling ( lua_State* luaVM )
{
    if ( lua_type ( luaVM, 1 ) == LUA_TNUMBER )
    {
        eVehicleTypes eModel = static_cast < eVehicleTypes > ( (int)lua_tonumber ( luaVM, 1 ) );
        if ( eModel )
        {
            if ( lua_type ( luaVM, 2 ) == LUA_TSTRING )
            {
                eHandlingProperty eProperty = m_pHandlingManager->GetPropertyEnumFromName ( lua_tostring ( luaVM, 2 ) );
                if ( eProperty )
                {
                    switch ( eProperty )
                    {
                        case HANDLING_MASS:
                        case HANDLING_TURNMASS:
                        case HANDLING_DRAGCOEFF:
                        case HANDLING_TRACTIONMULTIPLIER:
                        case HANDLING_ENGINEACCELERATION:
                        case HANDLING_ENGINEINERTIA:
                        case HANDLING_MAXVELOCITY:
                        case HANDLING_BRAKEDECELERATION:
                        case HANDLING_BRAKEBIAS:
                        case HANDLING_STEERINGLOCK:
                        case HANDLING_TRACTIONLOSS:
                        case HANDLING_TRACTIONBIAS:
                        case HANDLING_SUSPENSION_FORCELEVEL:
                        case HANDLING_SUSPENSION_DAMPING:
                        case HANDLING_SUSPENSION_HIGHSPEEDDAMPING:
                        case HANDLING_SUSPENSION_UPPER_LIMIT:
                        case HANDLING_SUSPENSION_LOWER_LIMIT:
                        case HANDLING_SUSPENSION_FRONTREARBIAS:
                        case HANDLING_SUSPENSION_ANTIDIVEMULTIPLIER:
                        case HANDLING_COLLISIONDAMAGEMULTIPLIER:
                        case HANDLING_SEATOFFSETDISTANCE:
                        case HANDLING_PERCENTSUBMERGED: // unsigned int
                        case HANDLING_MONETARY:
                        case HANDLING_HANDLINGFLAGS:
                        case HANDLING_MODELFLAGS:
                        case HANDLING_NUMOFGEARS:
                        case HANDLING_ANIMGROUP:
                            {
                                float fValue;
                                if ( CStaticFunctionDefinitions::GetModelHandling ( eModel, eProperty, fValue ) )
                                    lua_pushnumber ( luaVM, fValue );
                                else
                                    lua_pushboolean ( luaVM, false );

                                break;
                            }
                        case HANDLING_CENTEROFMASS:
                            {
                                CVector vecValue;
                                if ( CStaticFunctionDefinitions::GetModelHandling ( eModel, eProperty, vecValue ) )
                                {
                                    lua_pushnumber ( luaVM, vecValue.fX );
                                    lua_pushnumber ( luaVM, vecValue.fY );
                                    lua_pushnumber ( luaVM, vecValue.fZ );
                                    return 3;
                                }
                                else
                                    lua_pushboolean ( luaVM, false );

                                break;
                            }
                        case HANDLING_DRIVETYPE:
                        case HANDLING_ENGINETYPE:
                        case HANDLING_HEADLIGHT:
                        case HANDLING_TAILLIGHT:
                            {
                                std::string strValue;
                                if ( CStaticFunctionDefinitions::GetModelHandling ( eModel, eProperty, strValue ) )
                                    lua_pushstring ( luaVM, strValue.c_str () );
                                else
                                    lua_pushboolean ( luaVM, false );

                                break;
                            }
                        case HANDLING_ABS:
                            {
                                float fValue;
                                if ( CStaticFunctionDefinitions::GetModelHandling ( eModel, eProperty, fValue ) )
                                    lua_pushboolean ( luaVM, fValue ? true : false );
                                else
                                    lua_pushboolean ( luaVM, false );

                                break;
                            }
                        default:
                            lua_pushboolean ( luaVM, false );
                    }

                    return 1;
                }
                else
                    m_pScriptDebugging->LogBadPointer ( luaVM, "getModelHandling", "property", 2 );
            }
            else if ( lua_type ( luaVM, 2 ) == LUA_TNIL || lua_type ( luaVM, 2 ) == LUA_TNONE )
            {
                const CHandlingEntry* pEntry = g_pGame->GetHandlingManager()->GetModelHandlingData( eModel );

                lua_newtable ( luaVM );
                lua_pushnumber ( luaVM, pEntry->GetMass() );
                lua_setfield ( luaVM, -2, "mass" );
                lua_pushnumber ( luaVM, pEntry->GetTurnMass() );
                lua_setfield ( luaVM, -2, "turnMass" );
                lua_pushnumber ( luaVM, pEntry->GetDragCoeff() );
                lua_setfield ( luaVM, -2, "dragCoeff" );
                lua_newtable ( luaVM );
                CVector vecCenter = pEntry->GetCenterOfMass ();
                lua_pushnumber ( luaVM, vecCenter.fX );
                lua_setfield ( luaVM, -2, "posX" );
                lua_pushnumber ( luaVM, vecCenter.fY );
                lua_setfield ( luaVM, -2, "posY" );
                lua_pushnumber ( luaVM, vecCenter.fZ );
                lua_setfield ( luaVM, -2, "posZ" );
                lua_setfield ( luaVM, -2, "centerOfMass" );
                lua_pushnumber ( luaVM, pEntry->GetPercentSubmerged() );
                lua_setfield ( luaVM, -2, "percentSubmerged" );
                lua_pushnumber ( luaVM, pEntry->GetTractionMultiplier() );
                lua_setfield ( luaVM, -2, "tractionMultiplier" );
                CHandlingEntry::eDriveType eDriveType=pEntry->GetCarDriveType();
                if (eDriveType==CHandlingEntry::FWD)
                    lua_pushstring(luaVM,"fwd");
                else if (eDriveType==CHandlingEntry::RWD)
                    lua_pushstring(luaVM,"rwd");
                else if (eDriveType==CHandlingEntry::FOURWHEEL)
                    lua_pushstring(luaVM,"awd");
                else // What the ... (yeah, security)
                    lua_pushnil ( luaVM );
                lua_setfield ( luaVM, -2, "driveType" );
                CHandlingEntry::eEngineType eEngineType=pEntry->GetCarEngineType();
                if (eEngineType==CHandlingEntry::PETROL)
                    lua_pushstring(luaVM,"petrol");
                else if (eEngineType==CHandlingEntry::DIESEL)
                    lua_pushstring(luaVM,"diesel");
                else if (eEngineType==CHandlingEntry::ELECTRIC)
                    lua_pushstring(luaVM,"electric");
                else
                    lua_pushnil ( luaVM );
                lua_setfield ( luaVM, -2, "engineType" );
                lua_pushnumber ( luaVM, pEntry->GetNumberOfGears() );
                lua_setfield ( luaVM, -2, "numberOfGears" );
                lua_pushnumber ( luaVM, pEntry->GetEngineAcceleration() );
                lua_setfield ( luaVM, -2, "engineAcceleration" );
                lua_pushnumber ( luaVM, pEntry->GetEngineInertia() );
                lua_setfield ( luaVM, -2, "engineInertia" );
                lua_pushnumber ( luaVM, pEntry->GetMaxVelocity() );
                lua_setfield ( luaVM, -2, "maxVelocity" );
                lua_pushnumber ( luaVM, pEntry->GetBrakeDeceleration() );
                lua_setfield ( luaVM, -2, "brakeDeceleration" );
                lua_pushnumber ( luaVM, pEntry->GetBrakeBias() );
                lua_setfield ( luaVM, -2, "brakeBias" );
                lua_pushboolean ( luaVM, pEntry->GetABS() );
                lua_setfield ( luaVM, -2, "ABS" );
                lua_pushnumber ( luaVM, pEntry->GetSteeringLock() );
                lua_setfield ( luaVM, -2, "steeringLock" );
                lua_pushnumber ( luaVM, pEntry->GetTractionLoss() );
                lua_setfield ( luaVM, -2, "tractionLoss" );
                lua_pushnumber ( luaVM, pEntry->GetTractionBias() );
                lua_setfield ( luaVM, -2, "tractionBias" );
                lua_pushnumber ( luaVM, pEntry->GetSuspensionForceLevel() );
                lua_setfield ( luaVM, -2, "suspensionForceLevel" );
                lua_pushnumber ( luaVM, pEntry->GetSuspensionDamping() );
                lua_setfield ( luaVM, -2, "suspensionDamping" );
                lua_pushnumber ( luaVM, pEntry->GetSuspensionHighSpeedDamping() );
                lua_setfield ( luaVM, -2, "suspensionHighSpeedDamping" );
                lua_pushnumber ( luaVM, pEntry->GetSuspensionUpperLimit() );
                lua_setfield ( luaVM, -2, "suspensionUpperLimit" );
                lua_pushnumber ( luaVM, pEntry->GetSuspensionLowerLimit() );
                lua_setfield ( luaVM, -2, "suspensionLowerLimit" );
                lua_pushnumber ( luaVM, pEntry->GetSuspensionFrontRearBias() );
                lua_setfield ( luaVM, -2, "suspensionFrontRearBias" );
                lua_pushnumber ( luaVM, pEntry->GetSuspensionAntidiveMultiplier() );
                lua_setfield ( luaVM, -2, "suspensionAntidiveMultiplier" );
                lua_pushnumber ( luaVM, pEntry->GetCollisionDamageMultiplier() );
                lua_setfield ( luaVM, -2, "collisionDamageMultiplier" );
                lua_pushnumber ( luaVM, pEntry->GetSeatOffsetDistance() );
                lua_setfield ( luaVM, -2, "seatOffsetDistance" );
                lua_pushnumber ( luaVM, pEntry->GetHandlingFlags() );
                lua_setfield ( luaVM, -2, "handlingFlags" );
                lua_pushnumber ( luaVM, pEntry->GetModelFlags() );
                lua_setfield ( luaVM, -2, "modelFlags" );
                lua_pushnumber ( luaVM, pEntry->GetMonetary() );
                lua_setfield ( luaVM, -2, "monetary" );
                CHandlingEntry::eLightType eHeadType=pEntry->GetHeadLight();
                if (eHeadType==CHandlingEntry::LONG)
                    lua_pushstring(luaVM,"long");
                else if (eHeadType==CHandlingEntry::SMALL)
                    lua_pushstring(luaVM,"small");
                else if (eHeadType==CHandlingEntry::BIG)
                    lua_pushstring(luaVM,"big");
                else
                    lua_pushnil( luaVM );
                lua_setfield ( luaVM, -2, "headLight" );
                CHandlingEntry::eLightType eTailType=pEntry->GetTailLight();
                if (eTailType==CHandlingEntry::LONG)
                    lua_pushstring(luaVM,"long");
                else if (eTailType==CHandlingEntry::SMALL)
                    lua_pushstring(luaVM,"small");
                else if (eTailType==CHandlingEntry::BIG)
                    lua_pushstring(luaVM,"big");
                else
                    lua_pushnil( luaVM );
                lua_setfield ( luaVM, -2, "tailLight" );
                lua_pushnumber ( luaVM, pEntry->GetAnimGroup() );
                lua_setfield ( luaVM, -2, "animGroup" );
                return 1;
            }
            else
                m_pScriptDebugging->LogBadPointer ( luaVM, "getModelHandling", "property", 2 );
        }
        else
            m_pScriptDebugging->LogBadPointer ( luaVM, "getModelHandling", "model", 1 );
    }
    else
        m_pScriptDebugging->LogBadType ( luaVM, "getModelHandling" );

    lua_pushboolean ( luaVM, false );
    return 1;
}


int CLuaHandlingDefs::GetOriginalHandling ( lua_State* luaVM )
{
    if ( lua_type ( luaVM, 1 ) == LUA_TNUMBER )
    {
        eVehicleTypes eModel = static_cast < eVehicleTypes > ( (int)lua_tonumber ( luaVM, 1 ) );
        if ( eModel )
        {
            if ( lua_type ( luaVM, 2 ) == LUA_TSTRING )
            {
                eHandlingProperty eProperty = m_pHandlingManager->GetPropertyEnumFromName ( lua_tostring ( luaVM, 2 ) );
                if ( eProperty )
                {
                    switch ( eProperty )
                    {
                        case HANDLING_MASS:
                        case HANDLING_TURNMASS:
                        case HANDLING_DRAGCOEFF:
                        case HANDLING_TRACTIONMULTIPLIER:
                        case HANDLING_ENGINEACCELERATION:
                        case HANDLING_ENGINEINERTIA:
                        case HANDLING_MAXVELOCITY:
                        case HANDLING_BRAKEDECELERATION:
                        case HANDLING_BRAKEBIAS:
                        case HANDLING_STEERINGLOCK:
                        case HANDLING_TRACTIONLOSS:
                        case HANDLING_TRACTIONBIAS:
                        case HANDLING_SUSPENSION_FORCELEVEL:
                        case HANDLING_SUSPENSION_DAMPING:
                        case HANDLING_SUSPENSION_HIGHSPEEDDAMPING:
                        case HANDLING_SUSPENSION_UPPER_LIMIT:
                        case HANDLING_SUSPENSION_LOWER_LIMIT:
                        case HANDLING_SUSPENSION_FRONTREARBIAS:
                        case HANDLING_SUSPENSION_ANTIDIVEMULTIPLIER:
                        case HANDLING_COLLISIONDAMAGEMULTIPLIER:
                        case HANDLING_SEATOFFSETDISTANCE:
                        case HANDLING_PERCENTSUBMERGED: // unsigned int
                        case HANDLING_MONETARY:
                        case HANDLING_HANDLINGFLAGS:
                        case HANDLING_MODELFLAGS:
                        case HANDLING_NUMOFGEARS:
                        case HANDLING_ANIMGROUP:
                            {
                                float fValue;
                                if ( CStaticFunctionDefinitions::GetModelHandling ( eModel, eProperty, fValue, true ) )
                                    lua_pushnumber ( luaVM, fValue );
                                else
                                    lua_pushboolean ( luaVM, false );

                                break;
                            }
                        case HANDLING_CENTEROFMASS:
                            {
                                CVector vecValue;
                                if ( CStaticFunctionDefinitions::GetModelHandling ( eModel, eProperty, vecValue, true ) )
                                {
                                    lua_pushnumber ( luaVM, vecValue.fX );
                                    lua_pushnumber ( luaVM, vecValue.fY );
                                    lua_pushnumber ( luaVM, vecValue.fZ );
                                    return 3;
                                }
                                else
                                    lua_pushboolean ( luaVM, false );

                                break;
                            }
                        case HANDLING_DRIVETYPE:
                        case HANDLING_ENGINETYPE:
                        case HANDLING_HEADLIGHT:
                        case HANDLING_TAILLIGHT:
                            {
                                std::string strValue;
                                if ( CStaticFunctionDefinitions::GetModelHandling ( eModel, eProperty, strValue, true ) )
                                    lua_pushstring ( luaVM, strValue.c_str () );
                                else
                                    lua_pushboolean ( luaVM, false );

                                break;
                            }
                        case HANDLING_ABS:
                            {
                                float fValue;
                                if ( CStaticFunctionDefinitions::GetModelHandling ( eModel, eProperty, fValue, true ) )
                                    lua_pushboolean ( luaVM, fValue ? true : false );
                                else
                                    lua_pushboolean ( luaVM, false );

                                break;
                            }
                        default:
                            lua_pushboolean ( luaVM, false );
                    }

                    return 1;
                }
                else
                    m_pScriptDebugging->LogBadPointer ( luaVM, "getOriginalHandling", "property", 2 );
            }
            else if ( lua_type ( luaVM, 2 ) == LUA_TNIL || lua_type ( luaVM, 2 ) == LUA_TNONE )
            {
                const CHandlingEntry* pEntry = g_pGame->GetHandlingManager()->GetOriginalHandlingData( eModel );

                lua_newtable ( luaVM );
                lua_pushnumber ( luaVM, pEntry->GetMass() );
                lua_setfield ( luaVM, -2, "mass" );
                lua_pushnumber ( luaVM, pEntry->GetTurnMass() );
                lua_setfield ( luaVM, -2, "turnMass" );
                lua_pushnumber ( luaVM, pEntry->GetDragCoeff() );
                lua_setfield ( luaVM, -2, "dragCoeff" );
                lua_newtable ( luaVM );
                CVector vecCenter = pEntry->GetCenterOfMass ();
                lua_pushnumber ( luaVM, vecCenter.fX );
                lua_setfield ( luaVM, -2, "posX" );
                lua_pushnumber ( luaVM, vecCenter.fY );
                lua_setfield ( luaVM, -2, "posY" );
                lua_pushnumber ( luaVM, vecCenter.fZ );
                lua_setfield ( luaVM, -2, "posZ" );
                lua_setfield ( luaVM, -2, "centerOfMass" );
                lua_pushnumber ( luaVM, pEntry->GetPercentSubmerged() );
                lua_setfield ( luaVM, -2, "percentSubmerged" );
                lua_pushnumber ( luaVM, pEntry->GetTractionMultiplier() );
                lua_setfield ( luaVM, -2, "tractionMultiplier" );
                CHandlingEntry::eDriveType eDriveType=pEntry->GetCarDriveType();
                if (eDriveType==CHandlingEntry::FWD)
                    lua_pushstring(luaVM,"fwd");
                else if (eDriveType==CHandlingEntry::RWD)
                    lua_pushstring(luaVM,"rwd");
                else if (eDriveType==CHandlingEntry::FOURWHEEL)
                    lua_pushstring(luaVM,"awd");
                else // What the ... (yeah, security)
                    lua_pushnil ( luaVM );
                lua_setfield ( luaVM, -2, "driveType" );
                CHandlingEntry::eEngineType eEngineType=pEntry->GetCarEngineType();
                if (eEngineType==CHandlingEntry::PETROL)
                    lua_pushstring(luaVM,"petrol");
                else if (eEngineType==CHandlingEntry::DIESEL)
                    lua_pushstring(luaVM,"diesel");
                else if (eEngineType==CHandlingEntry::ELECTRIC)
                    lua_pushstring(luaVM,"electric");
                else
                    lua_pushnil ( luaVM );
                lua_setfield ( luaVM, -2, "engineType" );
                lua_pushnumber ( luaVM, pEntry->GetNumberOfGears() );
                lua_setfield ( luaVM, -2, "numberOfGears" );
                lua_pushnumber ( luaVM, pEntry->GetEngineAcceleration() );
                lua_setfield ( luaVM, -2, "engineAcceleration" );
                lua_pushnumber ( luaVM, pEntry->GetEngineInertia() );
                lua_setfield ( luaVM, -2, "engineInertia" );
                lua_pushnumber ( luaVM, pEntry->GetMaxVelocity() );
                lua_setfield ( luaVM, -2, "maxVelocity" );
                lua_pushnumber ( luaVM, pEntry->GetBrakeDeceleration() );
                lua_setfield ( luaVM, -2, "brakeDeceleration" );
                lua_pushnumber ( luaVM, pEntry->GetBrakeBias() );
                lua_setfield ( luaVM, -2, "brakeBias" );
                lua_pushboolean ( luaVM, pEntry->GetABS() );
                lua_setfield ( luaVM, -2, "ABS" );
                lua_pushnumber ( luaVM, pEntry->GetSteeringLock() );
                lua_setfield ( luaVM, -2, "steeringLock" );
                lua_pushnumber ( luaVM, pEntry->GetTractionLoss() );
                lua_setfield ( luaVM, -2, "tractionLoss" );
                lua_pushnumber ( luaVM, pEntry->GetTractionBias() );
                lua_setfield ( luaVM, -2, "tractionBias" );
                lua_pushnumber ( luaVM, pEntry->GetSuspensionForceLevel() );
                lua_setfield ( luaVM, -2, "suspensionForceLevel" );
                lua_pushnumber ( luaVM, pEntry->GetSuspensionDamping() );
                lua_setfield ( luaVM, -2, "suspensionDamping" );
                lua_pushnumber ( luaVM, pEntry->GetSuspensionHighSpeedDamping() );
                lua_setfield ( luaVM, -2, "suspensionHighSpeedDamping" );
                lua_pushnumber ( luaVM, pEntry->GetSuspensionUpperLimit() );
                lua_setfield ( luaVM, -2, "suspensionUpperLimit" );
                lua_pushnumber ( luaVM, pEntry->GetSuspensionLowerLimit() );
                lua_setfield ( luaVM, -2, "suspensionLowerLimit" );
                lua_pushnumber ( luaVM, pEntry->GetSuspensionFrontRearBias() );
                lua_setfield ( luaVM, -2, "suspensionFrontRearBias" );
                lua_pushnumber ( luaVM, pEntry->GetSuspensionAntidiveMultiplier() );
                lua_setfield ( luaVM, -2, "suspensionAntidiveMultiplier" );
                lua_pushnumber ( luaVM, pEntry->GetCollisionDamageMultiplier() );
                lua_setfield ( luaVM, -2, "collisionDamageMultiplier" );
                lua_pushnumber ( luaVM, pEntry->GetSeatOffsetDistance() );
                lua_setfield ( luaVM, -2, "seatOffsetDistance" );
                lua_pushnumber ( luaVM, pEntry->GetHandlingFlags() );
                lua_setfield ( luaVM, -2, "handlingFlags" );
                lua_pushnumber ( luaVM, pEntry->GetModelFlags() );
                lua_setfield ( luaVM, -2, "modelFlags" );
                lua_pushnumber ( luaVM, pEntry->GetMonetary() );
                lua_setfield ( luaVM, -2, "monetary" );
                CHandlingEntry::eLightType eHeadType=pEntry->GetHeadLight();
                if (eHeadType==CHandlingEntry::LONG)
                    lua_pushstring(luaVM,"long");
                else if (eHeadType==CHandlingEntry::SMALL)
                    lua_pushstring(luaVM,"small");
                else if (eHeadType==CHandlingEntry::BIG)
                    lua_pushstring(luaVM,"big");
                else
                    lua_pushnil( luaVM );
                lua_setfield ( luaVM, -2, "headLight" );
                CHandlingEntry::eLightType eTailType=pEntry->GetTailLight();
                if (eTailType==CHandlingEntry::LONG)
                    lua_pushstring(luaVM,"long");
                else if (eTailType==CHandlingEntry::SMALL)
                    lua_pushstring(luaVM,"small");
                else if (eTailType==CHandlingEntry::BIG)
                    lua_pushstring(luaVM,"big");
                else
                    lua_pushnil( luaVM );
                lua_setfield ( luaVM, -2, "tailLight" );
                lua_pushnumber ( luaVM, pEntry->GetAnimGroup() );
                lua_setfield ( luaVM, -2, "animGroup" );
                return 1;
            }
            else
                m_pScriptDebugging->LogBadPointer ( luaVM, "getOriginalHandling", "property", 2 );
        }
        else
            m_pScriptDebugging->LogBadPointer ( luaVM, "getOriginalHandling", "model", 1 );
    }
    else
        m_pScriptDebugging->LogBadType ( luaVM, "getOriginalHandling" );

    lua_pushboolean ( luaVM, false );
    return 1;
}
