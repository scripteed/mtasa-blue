/*****************************************************************************
*
*  PROJECT:     Multi Theft Auto v1.0
*  LICENSE:     See LICENSE in the top level directory
*  FILE:        game_sa/CMonsterTruckSA.h
*  PURPOSE:     Header file for monster truck vehicle entity class
*  DEVELOPERS:  Ed Lyons <eai@opencoding.net>
*               Christian Myhre Lundheim <>
*
*  Multi Theft Auto is available from http://www.multitheftauto.com/
*
*****************************************************************************/

#ifndef __CGAMESA_MONSTERTRUCK
#define __CGAMESA_MONSTERTRUCK

#include <game/CMonsterTruck.h>
#include "CAutomobileSA.h"

class CMonsterTruckSAInterface : public CAutomobileSAInterface
{
    
};
C_ASSERT(sizeof(CMonsterTruckSAInterface) == 0x99C);

class CMonsterTruckSA : public CMonsterTruck, public CAutomobileSA
{
private:
//  CMonsterTruckSAInterface        * internalInterface;
public:
    CMonsterTruckSA( CMonsterTruckSAInterface * monstertruck );
    CMonsterTruckSA( eVehicleTypes dwModelID, unsigned char ucVariation, unsigned char ucVariation2 );
};

#endif
