void main()
{

	Hive ce = CreateHive();
	if ( ce )
		ce.InitOffline();

	Weather weather = g_Game.GetWeather();

	weather.GetOvercast().SetLimits( 0.0 , 1.0 );
	weather.GetRain().SetLimits( 0.0 , 1.0 );
	weather.GetFog().SetLimits( 0.0 , 0.25 );

	weather.GetOvercast().SetForecastChangeLimits( 0.5, 0.8 );
	weather.GetRain().SetForecastChangeLimits( 0.1, 0.3 );
	weather.GetFog().SetForecastChangeLimits( 0.05, 0.10 );

	weather.GetOvercast().SetForecastTimeLimits( 3600 , 3600 );
	weather.GetRain().SetForecastTimeLimits( 300 , 300 );
	weather.GetFog().SetForecastTimeLimits( 3600 , 3600 );

	weather.GetOvercast().Set( Math.RandomFloatInclusive(0.0, 0.3), 0, 0);
	weather.GetRain().Set( Math.RandomFloatInclusive(0.0, 0.2), 0, 0);
	weather.GetFog().Set( Math.RandomFloatInclusive(0.0, 0.1), 0, 0);
	
	weather.SetWindMaximumSpeed(30);
	weather.SetWindFunctionParams(0.1, 1.0, 50);
	
	// ############################## Bridge ##################################
	Object obj; 
	obj = GetGame().CreateObject("Dam_Concrete_20_Floodgate", "12999.700195 -7.890600 3284.985596");
	obj.SetOrientation("55.999985 0.000000 0.000000");
	obj.SetPosition("12999.700195 -7.890600 3284.985596");
	obj = GetGame().CreateObject("Dam_Concrete_20_Floodgate", "12988.517578 -7.890600 3301.570557");
	obj.SetOrientation("55.999985 0.000000 0.000000");
	obj.SetPosition("12988.517578 -7.890600 3301.570557");
	obj = GetGame().CreateObject("Dam_Concrete_20_Floodgate", "12977.330078 -7.890600 3318.156250");
	obj.SetOrientation("56.000000 0.000000 0.000000");
	obj.SetPosition("12977.330078 -7.890600 3318.156250");
	obj = GetGame().CreateObject("Dam_Concrete_20_Floodgate", "12966.149414 -7.890600 3334.729980");
	obj.SetOrientation("56.000000 0.000000 0.000000");
	obj.SetPosition("12966.149414 -7.890600 3334.729980");
	obj = GetGame().CreateObject("Dam_Concrete_20_Floodgate", "12954.969727 -7.890600 3351.300049");
	obj.SetOrientation("56.000000 0.000000 0.000000");
	obj.SetPosition("12954.969727 -7.890600 3351.300049");
	obj = GetGame().CreateObject("Dam_Concrete_20_Floodgate", "12943.798828 -7.890600 3367.870117");
	obj.SetOrientation("56.000000 0.000000 0.000000");
	obj.SetPosition("12943.798828 -7.890600 3367.870117");
	obj = GetGame().CreateObject("Dam_Concrete_20_Floodgate", "12932.620117 -7.890600 3384.443604");
	obj.SetOrientation("56.000000 0.000000 0.000000");
	obj.SetPosition("12932.620117 -7.890600 3384.443604");
	obj = GetGame().CreateObject("Dam_Concrete_20_Floodgate", "12921.450195 -7.890600 3401.000000");
	obj.SetOrientation("56.000000 0.000000 0.000000");
	obj.SetPosition("12921.450195 -7.890600 3401.000000");
	obj = GetGame().CreateObject("Dam_Concrete_20_Floodgate", "12910.259766 -7.890600 3417.581055");
	obj.SetOrientation("56.000000 0.000000 0.000000");
	obj.SetPosition("12910.259766 -7.890600 3417.581055");
	obj = GetGame().CreateObject("Dam_Concrete_20_Floodgate", "12899.080078 -7.890600 3434.149902");
	obj.SetOrientation("56.000000 0.000000 0.000000");
	obj.SetPosition("12899.080078 -7.890600 3434.149902");
	obj = GetGame().CreateObject("Dam_Concrete_20_Floodgate", "12887.900391 -7.890600 3450.728027");
	obj.SetOrientation("56.000000 0.000000 0.000000");
	obj.SetPosition("12887.900391 -7.890600 3450.728027");
	obj = GetGame().CreateObject("Dam_Concrete_20_Floodgate", "12876.709961 -7.890600 3467.312256");
	obj.SetOrientation("56.000000 0.000000 0.000000");
	obj.SetPosition("12876.709961 -7.890600 3467.312256");
	obj = GetGame().CreateObject("Dam_Concrete_20_Floodgate", "12865.540039 -7.890600 3483.872803");
	obj.SetOrientation("56.000000 0.000000 0.000000");
	obj.SetPosition("12865.540039 -7.890600 3483.872803");
	obj = GetGame().CreateObject("Dam_Concrete_20_Floodgate", "12854.360352 -7.890600 3500.449463");
	obj.SetOrientation("56.000000 0.000000 0.000000");
	obj.SetPosition("12854.360352 -7.890600 3500.449463");
	obj = GetGame().CreateObject("Dam_Concrete_20_Floodgate", "12843.179688 -7.890600 3517.039795");
	obj.SetOrientation("56.000000 0.000000 0.000000");
	obj.SetPosition("12843.179688 -7.890600 3517.039795");
	obj = GetGame().CreateObject("Dam_Concrete_20_Floodgate", "12831.998047 -7.890600 3533.620117");
	obj.SetOrientation("56.000000 0.000000 0.000000");
	obj.SetPosition("12831.998047 -7.890600 3533.620117");
	obj = GetGame().CreateObject("Dam_Concrete_20_Floodgate", "12820.809570 -7.890600 3550.198975");
	obj.SetOrientation("56.000000 0.000000 0.000000");
	obj.SetPosition("12820.809570 -7.890600 3550.198975");
	obj = GetGame().CreateObject("Dam_Concrete_20_Floodgate", "12809.627930 -7.890600 3566.780029");
	obj.SetOrientation("56.000000 0.000000 0.000000");
	obj.SetPosition("12809.627930 -7.890600 3566.780029");
	obj = GetGame().CreateObject("Dam_Concrete_20_Floodgate", "12798.440430 -7.890600 3583.360107");
	obj.SetOrientation("56.000000 0.000000 0.000000");
	obj.SetPosition("12798.440430 -7.890600 3583.360107");
	obj = GetGame().CreateObject("Land_Lighthouse", "13057.658203 27.043219 3247.424805");
	obj.SetOrientation("0.000000 0.000000 0.000000");
	obj.SetPosition("13057.658203 27.043219 3247.424805");	
	// ############################## Bridge ##################################	
}

class CustomMission: MissionServer
{	
	void SetRandomHealth(EntityAI itemEnt)
	{
		int rndHlt = Math.RandomInt(40,100);
		itemEnt.SetHealth("","",rndHlt);
	}

	override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName)
	{
		Entity playerEnt;
		playerEnt = GetGame().CreatePlayer(identity, characterName, pos, 0, "NONE");//Creates random player
		Class.CastTo(m_player, playerEnt);
		
		GetGame().SelectPlayer(identity, m_player);
		
		return m_player;
	}
	
	override void StartingEquipSetup(PlayerBase player, bool clothesChosen)
	{
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
		
		// SPAWN A VEHICLE NEAR THE PLAYER
		
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
};
  
Mission CreateCustomMission(string path)
{
	return new CustomMission();
}