#ifndef EXCLUSIVE_ALL
#define EXCLUSIVE_ALL

#include <Tutorial1/exclusive_init.h>
#include <Tutorial1/exclusive_update.h>
#include <Tutorial2/exclusive_init.h>
#include <Tutorial2/exclusive_update.h>
#include <Tutorial3/exclusive_init.h>
#include <Tutorial3/exclusive_update.h>
#include <Tutorial4/exclusive_init.h>
#include <Tutorial4/exclusive_update.h>

#include <LobbyInside/exclusive_init.h>
#include <LobbyInside/exclusive_update.h>

#include <LobbyOutside/exclusive_init.h>
#include <LobbyOutside/exclusive_update.h>

#include <SunlightValley/exclusive_init.h>
#include <SunlightValley/exclusive_update.h>

#include <SnowyCanyon/exclusive_init.h>
#include <SnowyCanyon/exclusive_update.h>

#include <DustyMirage/exclusive_init.h>
#include <DustyMirage/exclusive_update.h>

#include <AncientEmrald/exclusive_init.h>
#include <AncientEmrald/exclusive_update.h>

#include <DeepCavern/exclusive_init.h>
#include <DeepCavern/exclusive_update.h>

#include <DeadAhead/exclusive_init.h>
#include <DeadAhead/exclusive_update.h>

#include <SeaHorizon/exclusive_init.h>
#include <SeaHorizon/exclusive_update.h>

#include <CloudHighway/exclusive_init.h>
#include <CloudHighway/exclusive_update.h>

void applyExclusive(Map *map)
{
    if (map->MapInfo.name == "Tutorial1")
    { Tutorial1Init(map); map->UpdateExclusive = Tutorial1Update; }
    if (map->MapInfo.name == "Tutorial2")
    { Tutorial2Init(map); map->UpdateExclusive = Tutorial2Update; }
    if (map->MapInfo.name == "Tutorial3")
    { Tutorial3Init(map); map->UpdateExclusive = Tutorial3Update; }
    if (map->MapInfo.name == "Tutorial4")
    { Tutorial4Init(map); map->UpdateExclusive = Tutorial4Update; }

    // Main Map
    if (map->MapInfo.name == "LobbyInside")
    { LobbyInsideInit(map); map->UpdateExclusive = LobbyInsideUpdate; }
    
    if (map->MapInfo.name == "LobbyOutside")
    { LobbyOutsideInit(map); map->UpdateExclusive = LobbyOutsideUpdate; }
    
    if (map->MapInfo.name == "SunlightValley")
    { SunlightValleyInit(map); map->UpdateExclusive = SunlightValleyUpdate; }
    
    if (map->MapInfo.name == "SnowyCanyon")
    { SnowyCanyonInit(map); map->UpdateExclusive = SnowyCanyonUpdate; }
    
    if (map->MapInfo.name == "DustyMirage")
    { DustyMirageInit(map); map->UpdateExclusive = DustyMirageUpdate; }
    
    if (map->MapInfo.name == "AncientEmrald")
    { AncientEmraldInit(map); map->UpdateExclusive = AncientEmraldUpdate; }
    
    if (map->MapInfo.name == "DeepCavern")
    { DeepCavernInit(map); map->UpdateExclusive = DeepCavernUpdate; }
    
    if (map->MapInfo.name == "DeadAhead")
    { DeadAheadInit(map); map->UpdateExclusive = DeadAheadUpdate; }

    if (map->MapInfo.name == "SeaHorizon")
    { SeaHorizonInit(map); map->UpdateExclusive = SeaHorizonUpdate; }
    
    if (map->MapInfo.name == "CloudHighway")
    { CloudHighwayInit(map); map->UpdateExclusive = CloudHighwayUpdate; }
}

#endif