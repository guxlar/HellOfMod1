#include "$CurrentDir:mpmissions\\HellOfModMission1.ChernarusPlus\\code\\WorldWeather.c"
#include "$CurrentDir:mpmissions\\HellOfModMission1.ChernarusPlus\\code\\WorldDateTime.c"
#include "$CurrentDir:mpmissions\\HellOfModMission1.ChernarusPlus\\code\\SpawnObject.c"
#include "$CurrentDir:mpmissions\\HellOfModMission1.ChernarusPlus\\code\\BridgePrisonIsland.c"
#include "$CurrentDir:mpmissions\\HellOfModMission1.ChernarusPlus\\code\\BridgeSkalistyIsland.c"
#include "$CurrentDir:mpmissions\\HellOfModMission1.ChernarusPlus\\code\\Lighthouses.c"

// MAIN FUNCTION
void main() {

	Hive ce = CreateHive();
	if ( ce )
		ce.InitOffline();

	WorldDateTime(2015, 4, 8, 10, 23);
	WorldWeather();
	BridgePrisonIsland();
	BridgeSkalistyIsland();
	Lighthouses();
}

// CREATE THE CUSTOM MISSION
Mission CreateCustomMission(string path) {
	return new CustomMission();
}

// CLASS: CUSTOM MISSION CLASS
class CustomMission: MissionServer {	
	void SetRandomHealth(EntityAI itemEnt) {
		int rndHlt = Math.RandomInt(80,100);
		itemEnt.SetHealth("","",rndHlt);
	}

	override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName) {
		Entity playerEnt;
		playerEnt = GetGame().CreatePlayer(identity, characterName, pos, 0, "NONE");
		Class.CastTo(m_player, playerEnt);
		GetGame().SelectPlayer(identity, m_player);
		return m_player;
	}
	
	override void StartingEquipSetup(PlayerBase player, bool clothesChosen) {
		
		player.RemoveAllItems();
		
		// EQUIP THE CHARACTER
		player.GetInventory().CreateInInventory("TTSKOPants");
		player.GetInventory().CreateInInventory("TTsKOJacket_Camo");
		player.GetInventory().CreateInInventory("CombatBoots_Black");
		player.GetInventory().CreateInInventory("HighCapacityVest_Black"); 
		player.GetInventory().CreateInInventory("AliceBag_Black");
		player.GetInventory().CreateInInventory("Balaclava3Holes_Black");
		player.GetInventory().CreateInInventory("TacticalGloves_Black"); 
		player.GetInventory().CreateInInventory("BallisticHelmet_Black"); 
		player.GetInventory().CreateInInventory("AviatorGlasses");		
		player.GetInventory().CreateInInventory("StoneKnife");
		player.GetInventory().CreateInInventory("TacticalBaconCan");
		player.GetInventory().CreateInInventory("TacticalBaconCan");
		player.GetInventory().CreateInInventory("CanOpener");
		player.GetInventory().CreateInInventory("BandageDressing");
		player.GetInventory().CreateInInventory("BandageDressing");
		player.GetInventory().CreateInInventory("DuctTape");
		player.GetInventory().CreateInInventory("Matchbox");
		player.GetInventory().CreateInInventory("Compass");
		player.GetInventory().CreateInInventory("AmmoBox_556x45_20Rnd");
		player.GetInventory().CreateInInventory("AmmoBox_556x45_20Rnd");
		player.GetInventory().CreateInInventory("AmmoBox_556x45_20Rnd");
		player.GetInventory().CreateInInventory("AmmoBox_556x45_20Rnd");
		player.GetInventory().CreateInInventory("Mag_STANAGCoupled_30Rnd");
		player.GetInventory().CreateInInventory("Mag_STANAGCoupled_30Rnd");
		player.GetInventory().CreateInInventory("Mag_IJ70_8Rnd");
		player.GetInventory().CreateInInventory("Mag_IJ70_8Rnd");
		player.GetInventory().CreateInInventory("Mag_IJ70_8Rnd");
		player.GetInventory().CreateInInventory("Canteen");
		player.GetInventory().CreateInInventory("Binoculars");
		
		// FNX45 in Ammo Box
		EntityAI oBox = player.GetInventory().CreateInInventory("AmmoBox");	
		EntityAI oFnx45 = oBox.GetInventory().CreateInInventory("FNX45");
		
		oFnx45.GetInventory().CreateAttachment("PistolSuppressor");
		oFnx45.GetInventory().CreateAttachment("FNP45_MRDSOptic");
		oFnx45.GetInventory().CreateAttachment("UniversalLight");
		
		oBox.GetInventory().CreateInInventory("AmmoBox_45ACP_25rnd");
		oBox.GetInventory().CreateInInventory("AmmoBox_45ACP_25rnd");
		oBox.GetInventory().CreateInInventory("AmmoBox_762x54_20Rnd");
		oBox.GetInventory().CreateInInventory("AmmoBox_762x54_20Rnd");
		oBox.GetInventory().CreateInInventory("Mag_FNX45_15Rnd");
		oBox.GetInventory().CreateInInventory("Mag_FNX45_15Rnd");
		oBox.GetInventory().CreateInInventory("Mag_SVD_10Rnd");
		oBox.GetInventory().CreateInInventory("Mag_SVD_10Rnd");
		oBox.GetInventory().CreateInInventory("Mag_SVD_10Rnd");
		oBox.GetInventory().CreateInInventory("Mag_SVD_10Rnd");		
		
		// M4A1
		EntityAI oM4a1 = player.GetHumanInventory().CreateInInventory("M4A1_Black");
		oM4a1.GetInventory().CreateAttachment("M4_Suppressor");
		oM4a1.GetInventory().CreateAttachment("M4_RISHndgrd_Black");
		oM4a1.GetInventory().CreateAttachment("M4_MPBttstck_Black");
		oM4a1.GetInventory().CreateAttachment("ACOGOptic");
		
		// Flashlight
		EntityAI oFlashlight = player.GetHumanInventory().CreateInInventory("Flashlight");
		oFlashlight.GetInventory().CreateAttachment("Battery9V");
		
		// Marakov
		EntityAI oMarakov = player.GetHumanInventory().CreateInInventory("MakarovIJ70");
		oMarakov.GetInventory().CreateAttachment("PistolSuppressor");	

		// Fireaxe
		EntityAI oAxe = player.GetHumanInventory().CreateInInventory("FirefighterAxe_Black");	
		
		// Radio
		EntityAI oRadio = player.GetHumanInventory().CreateInInventory("PersonalRadio");
		oRadio.GetInventory().CreateAttachment("Battery9V");	

		// SVD in hands
		EntityAI oSVD = player.GetHumanInventory().CreateInHands("SVD");
		oSVD.GetInventory().CreateAttachment("PSO1Optic");
		
		// SPAWN A VEHICLE NEAR THE PLAYER - WITH TENT AND GAS CANISTER
		
		vector NewPosition;
		vector OldPosition;
		OldPosition = player.GetPosition();
		NewPosition[0] = OldPosition[0] + 2;
		NewPosition[1] = OldPosition[1] + 0.2;
		NewPosition[2] = OldPosition[2] + 2;

		EntityAI oCar = EntityAI.Cast(GetGame().CreateObject("OffroadHatchback", NewPosition, false, true));
		oCar.GetInventory().CreateAttachment("HatchbackWheel");
		oCar.GetInventory().CreateAttachment("HatchbackWheel");
		oCar.GetInventory().CreateAttachment("HatchbackWheel");
		oCar.GetInventory().CreateAttachment("HatchbackWheel");
		oCar.GetInventory().CreateAttachment("HatchbackWheel");
		oCar.GetInventory().CreateAttachment("HatchbackDoors_CoDriver");
		oCar.GetInventory().CreateAttachment("HatchbackDoors_Driver");
		oCar.GetInventory().CreateAttachment("HatchbackHood");
		oCar.GetInventory().CreateAttachment("HatchbackTrunk");
		oCar.GetInventory().CreateAttachment("HeadlightH7");
		oCar.GetInventory().CreateAttachment("HeadlightH7");
		oCar.GetInventory().CreateAttachment("SparkPlug");
		oCar.GetInventory().CreateAttachment("EngineBelt");
		oCar.GetInventory().CreateAttachment("CarRadiator");
		oCar.GetInventory().CreateAttachment("CarBattery");
		oCar.GetInventory().CreateInInventory("MediumTent");
		oCar.GetInventory().CreateInInventory("CanisterGasoline");		
		oCar.SetAllowDamage(true);

		auto carfluids = Car.Cast( oCar );
		carfluids.Fill( CarFluid.FUEL, 1000 );
		carfluids.Fill( CarFluid.OIL, 1000 );
		carfluids.Fill( CarFluid.BRAKE, 1000 );
		carfluids.Fill( CarFluid.COOLANT, 1000 );
	}
}
