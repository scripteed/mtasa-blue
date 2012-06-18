/*****************************************************************************
*
*  PROJECT:     Multi Theft Auto v1.0
*  LICENSE:     See LICENSE in the top level directory
*  FILE:        game_sa/CParticleSystemManagerSA.h
*  PURPOSE:     Header file for particle system manager class
*  DEVELOPERS:  
*
*  Multi Theft Auto is available from http://www.multitheftauto.com/
*
*****************************************************************************/

#pragma once

// int __stdcall CParticleFx::Add(CParticleFx* pThis, CVector* pVecPosition, CVector* pVecVelocity, float fBlur, CParticleInfo* pParticleInfo, int a6, float fBrightness, float a8, int a9)
#define FUNC_CParticleFx__Add					0x4AA440

class CParticleFxSAInterface
{
public:
    uint32 pad1;
    uint32 pNext;
    class CFxSystem* pFxSystem; // must be initialized before this class is used
    RwMatrix* pMatrixPos;
    RwMatrix matrix;
    uint8 pad2[4];
    uint32 pad3[2];
    uint16 pad4[3];
    uint8 flags;
    uint8 pad5;
    uint32 pad6;
    CVector vecUnk;
    uint32 pad7;
    class CParticleEmitterManager** pParticleEmitterManagers; // allocated array of pointers
    uint32 pad8[34];
};
C_ASSERT(sizeof(CParticleFxSAInterface) == 0x104);

