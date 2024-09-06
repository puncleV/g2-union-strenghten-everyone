// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
	auto const NPC_STRENGTHENED = 391;

	bool strengthenNpc(oCNpc* npc) {
		auto extraHp = npc->attribute[NPC_ATR_HITPOINTSMAX] * (STRENGTHEN_HP_PERCENT / 100.0);
		auto addedHp = RANDOMIZE_STATS ? randomizer.Random(1, extraHp) : extraHp;

		npc->attribute[NPC_ATR_HITPOINTSMAX] += addedHp;
		npc->attribute[NPC_ATR_HITPOINTS] += addedHp;

		auto addedStrength = npc->attribute[NPC_ATR_STRENGTH] * (STRENGTHEN_STATS_PERCENT / 100.0);
		npc->attribute[NPC_ATR_STRENGTH] += RANDOMIZE_STATS ? randomizer.Random(1, addedStrength) : addedStrength;

		auto addedDexterity = npc->attribute[NPC_ATR_STRENGTH] * (STRENGTHEN_STATS_PERCENT / 100.0);
		npc->attribute[NPC_ATR_DEXTERITY] += RANDOMIZE_STATS ? randomizer.Random(1, addedDexterity) : addedDexterity;

		if (npc->protection[oEDamageIndex_Blunt] != -1) {
			auto addedDefence = npc->protection[oEDamageIndex_Blunt] * (STRENGTHEN_DEFENCE_PERCENT / 100.0);
			npc->protection[oEDamageIndex_Blunt] += RANDOMIZE_STATS ? randomizer.Random(1, addedDefence) : addedDefence;
		}

		if (npc->protection[oEDamageIndex_Edge] != -1) {
			auto addedDefence = npc->protection[oEDamageIndex_Edge] * (STRENGTHEN_DEFENCE_PERCENT / 100.0);
			npc->protection[oEDamageIndex_Edge] += RANDOMIZE_STATS ? randomizer.Random(1, addedDefence) : addedDefence;
		}

		if (npc->protection[oEDamageIndex_Fire] != -1) {
			auto addedDefence = npc->protection[oEDamageIndex_Fire] * (STRENGTHEN_DEFENCE_PERCENT / 100.0);
			npc->protection[oEDamageIndex_Fire] += RANDOMIZE_STATS ? randomizer.Random(1, addedDefence) : addedDefence;
		}

		if (npc->protection[oEDamageIndex_Point] != -1) {
			auto addedDefence = npc->protection[oEDamageIndex_Point] * (STRENGTHEN_DEFENCE_PERCENT / 100.0);
			npc->protection[oEDamageIndex_Point] += RANDOMIZE_STATS ? randomizer.Random(1, addedDefence) : addedDefence;
		}

		if (npc->protection[oEDamageIndex_Magic] != -1) {
			auto addedDefence = npc->protection[oEDamageIndex_Magic] * (STRENGTHEN_DEFENCE_PERCENT / 100.0);
			npc->protection[oEDamageIndex_Magic] += RANDOMIZE_STATS ? randomizer.Random(1, addedDefence) : addedDefence;
		}

		npc->setNpcVar(NPC_STRENGTHENED, TRUE);

		return TRUE;
	}

	void oCNpc::setNpcVar(int varIdx, int value = 1) {
		parser->SetInstance("NPCVARINST", this);
		parser->CallFunc(parser->GetIndex("SetNpcVar"), varIdx, value);
	}

	int oCNpc::getNpcVar(int varIdx) {
		parser->SetInstance("NPCVARINST", this);
		auto value = *(int*)parser->CallFunc(parser->GetIndex("GetNpcVar"), varIdx);

		return value;
	}

	void goThroughNpcHandlers(oCNpc* npc) {
		if (!npc) {
			return;
		}

		if (!npc->IsDead() && npc != oCNpc::player) {
			if (!npc->getNpcVar(NPC_STRENGTHENED) && MOD_IS_ON && !RX_IsSummon(npc)) {
				strengthenNpc(npc);
			}
		}
	}

	zCArray<oCNpc*> oCNpc::getNpcInRadius(float radius) {
		ClearVobList();
		CreateVobList(radius);

		zCArray<zCVob*> vobList = this->vobList;
		zCArray<oCNpc*> npcList;
		zCVob* pVob = NULL;
		oCNpc* npc = NULL;

		for (int i = 0; i < vobList.GetNum(); i++) {
			pVob = vobList.GetSafe(i);
			if (!pVob)
				continue;
			npc = zDYNAMIC_CAST<oCNpc>(pVob);
			if (!npc)
				continue;
			if (npc->IsDead())
				continue;

			goThroughNpcHandlers(npc);
		}

		return npcList;
	}
}