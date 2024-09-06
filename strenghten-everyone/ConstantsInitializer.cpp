// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
	void updateConstantsWithOptions() {
		IGNORED_NPCS = zoptions->ReadString("PUNCLEVSTRONG", "IgnoredNpcs", "NONE");
		STRENGTHEN_HP_PERCENT = zoptions->ReadInt("PUNCLEVSTRONG", "HpPercent", 15);
		STRENGTHEN_STATS_PERCENT = zoptions->ReadInt("PUNCLEVSTRONG", "StatsPercent", 15);
		STRENGTHEN_DEFENCE_PERCENT = zoptions->ReadInt("PUNCLEVSTRONG", "DefencePercent", 15);

		RANDOMIZE_STATS = zoptions->ReadBool("PUNCLEVSTRONG", "RandomizeStats", TRUE);
		MOD_IS_ON = zoptions->ReadBool("PUNCLEVSTRONG", "PluginOn", TRUE);
		IS_DEBUG = zoptions->ReadBool("PUNCLEVSTRONG", "Debug", FALSE);
	}
}