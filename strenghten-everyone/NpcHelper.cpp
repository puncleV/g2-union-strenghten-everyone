// Supported with union (c) 2020 Union team
// Union SOURCE file
#include <vector>

namespace GOTHIC_ENGINE {
	std::vector<zSTRING> partnersList = { "PC_THIEF", "PC_MAGE", "PC_FIGHTER", "PC_PSIONIC", "_LARES", "_BILGOT" };
	std::vector<zSTRING> ignoreNpcList = { "TOTEM", "CRAIT", "KHUBA", "SUMKHUBI", "PET_JINA" };


	bool RX_IsSummon(oCNpc* npc) {
		return (npc && npc->aiscriptvars[AIV_SUMMON] == TRUE);
	}

	bool ignoredNpc(oCNpc* npc) {
		auto npcName = npc->GetObjectName();
		if (RX_IsSummon(npc)) {
			return TRUE;
		}
		
		if (IGNORED_NPCS.HasWordI(npcName)) {
			return TRUE;
		}

		for (auto i = 0; i < max(ignoreNpcList.size(), partnersList.size()); i += 1) {
			if (ignoreNpcList.size() > i && npcName.HasWordI(ignoreNpcList[i])) {
				return TRUE;
			}

			if (partnersList.size() > i && npcName.HasWordI(partnersList[i])) {
				return TRUE;
			}
		}

		return FALSE;
	}
}