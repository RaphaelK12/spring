#ifndef WEAPONDEFHANDLER_H
#define WEAPONDEFHANDLER_H

#include <string>
#include <map>

#include "Sim/Misc/CommonDefHandler.h"
#include "Sim/Units/UnitDef.h"
#include "WeaponDef.h"

class LuaTable;
class CExplosionGenerator;

class CExplosionGeneratorHandler;


class CWeaponDefHandler : CommonDefHandler
{
public:
	CWeaponDefHandler();
	~CWeaponDefHandler();

	const WeaponDef* GetWeapon(const std::string weaponname);
	const WeaponDef* GetWeaponById(int weaponDefId);

	void LoadSound(const LuaTable&, GuiSoundSet&, const std::string& name);

	DamageArray DynamicDamages(DamageArray damages, float3 startPos,
					float3 curPos, float range, float exp,
					float damageMin, bool inverted);

public:
	WeaponDef *weaponDefs;
	std::map<std::string, int> weaponID;
	int numWeaponDefs;

private:
	void ParseWeapon(const LuaTable& wdTable, WeaponDef& wd);
	float3 hs2rgb(float h, float s);
};


//not very sweet, but still better than replacing "const WeaponDef" _everywhere_
inline S3DModel* LoadModel(const WeaponDef* wdef)
{
	return const_cast<WeaponDef*>(wdef)->LoadModel();
}


extern CWeaponDefHandler* weaponDefHandler;


#endif /* WEAPONDEFHANDLER_H */
