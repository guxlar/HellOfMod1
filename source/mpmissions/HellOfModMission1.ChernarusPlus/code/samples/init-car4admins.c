// init-car4admins.c

void main()
{
	Hive ce = CreateHive();
	if ( ce )
		ce.InitOffline();

	Weather weather = g_Game.GetWeather();

	weather.GetOvercast().SetLimits( 0.0 , 1.0 );
	weather.GetRain().SetLimits( 0.0 , 0.0 );
	weather.GetFog().SetLimits( 0.0 , 0.25 );

	weather.GetOvercast().SetForecastChangeLimits( 0.0, 0.2 );
	weather.GetRain().SetForecastChangeLimits( 0.0, 0.0 );
	weather.GetFog().SetForecastChangeLimits( 0.15, 0.45 );

	weather.GetOvercast().SetForecastTimeLimits( 1800 , 1800 );
	weather.GetRain().SetForecastTimeLimits( 600 , 600 );
	weather.GetFog().SetForecastTimeLimits( 1800 , 1800 );

	weather.GetOvercast().Set( Math.RandomFloatInclusive(0.0, 0.3), 0, 0);
	weather.GetRain().Set( Math.RandomFloatInclusive(0.0, 0.2), 0, 0);
	weather.GetFog().Set( Math.RandomFloatInclusive(0.0, 0.1), 0, 0);
	
	weather.SetWindMaximumSpeed(15);
	weather.SetWindFunctionParams(0.1, 0.3, 50);
}



class CustomMission: MissionServer
{	
	override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName)
	{
		Entity playerEnt = GetGame().CreatePlayer(identity, characterName, pos, 0, "NONE");
		Class.CastTo(m_player, playerEnt);
		GetGame().SelectPlayer(identity, m_player);
		return m_player;
	}
	
	void SetRandomHealth(EntityAI itemEnt)
	{
		int rndHlt = Math.RandomInt(60,100);
		itemEnt.SetHealth("","",rndHlt);
	}
	
	//! OnInit
	// ###################################
	override void OnInit()
    {
        GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(NumPLayersOnServer, 300000, true);      // 5 minutes
	}
   
    void NumPLayersOnServer()
    {
        ref array<Man> players = new array<Man>;
        GetGame().GetPlayers( players );
        int numPlayers = players.Count();
        for ( int i = 0; i < players.Count(); ++i )
        {
            Man player = players.Get(i);
            if( player )
            {
                string messPlayers = "Players on the server: " + numPlayers.ToString() + "/120"
                Param1<string> m_MessageParam = new Param1<string>(messPlayers);
                GetGame().RPCSingleParam(player, ERPCs.RPC_USER_ACTION_MESSAGE, m_MessageParam, true, player.GetIdentity());
            }
        }
    }
	
	override void StartingEquipSetup(PlayerBase player, bool clothesChosen)
	{	
	bool IsAdmin = false;
	string SteamId_sasaa = "76561198182095246";
	string SteamId_rene = "76561197973590083";
	string SteamId_Mauss = "76561198015299671";
	string SteamId_stefan = "76561198021971615";
	string SteamId_tijmen = "76561198023029756";
	
	if (player.GetIdentity().GetPlainId() == SteamId_sasaa){
		IsAdmin = true;
	} else if (player.GetIdentity().GetPlainId() == SteamId_rene){
		IsAdmin = true;
	} else if (player.GetIdentity().GetPlainId() == SteamId_Mauss){
		IsAdmin = true;
	} else if (player.GetIdentity().GetPlainId() == SteamId_stefan){
		IsAdmin = true;
	} else if (player.GetIdentity().GetPlainId() == SteamId_tijmen){
		IsAdmin = true;
	} else {
		IsAdmin = false;
	}
	if (IsAdmin){
		// Admins
		if (player.GetIdentity().GetPlainId() == SteamId_sasaa){
			EntityAI MyV3S;
			vector NewPosition;
			vector OldPosition;
			OldPosition = player.GetPosition();
			NewPosition[0] = OldPosition[0] + 2;
			NewPosition[1] = OldPosition[1] + 0.2;
			NewPosition[2] = OldPosition[2] + 2;
			MyV3S = GetGame().CreateObject( "OffroadHatchback", NewPosition, false, true, true );		            
			MyV3S.GetInventory().CreateAttachment("HatchbackHood");
			MyV3S.GetInventory().CreateAttachment("HatchbackTrunk");
			MyV3S.GetInventory().CreateAttachment("HatchbackDoors_Driver");
			MyV3S.GetInventory().CreateAttachment("HatchbackDoors_CoDriver");
			MyV3S.GetInventory().CreateAttachment("HatchbackWheel");
			MyV3S.GetInventory().CreateAttachment("HatchbackWheel");
			MyV3S.GetInventory().CreateAttachment("HatchbackWheel");
			MyV3S.GetInventory().CreateAttachment("HatchbackWheel");
			MyV3S.GetInventory().CreateAttachment("HatchbackWheel"); //spare
			MyV3S.GetInventory().CreateAttachment("SparkPlug");
			MyV3S.GetInventory().CreateAttachment("EngineBelt");
			MyV3S.GetInventory().CreateAttachment("CarBattery");
			auto carfluids = Car.Cast( MyV3S );
			carfluids.Fill( CarFluid.FUEL, 1000 );
			carfluids.Fill( CarFluid.OIL, 1000 );
			carfluids.Fill( CarFluid.BRAKE, 1000 );
			carfluids.Fill( CarFluid.COOLANT, 1000 );
		}
		player.RemoveAllItems();
		player.GetInventory().CreateInInventory("TTSKOPants");
		player.GetInventory().CreateInInventory("TTsKOJacket_Camo");
		player.GetInventory().CreateInInventory("CombatBoots_Black");
		if (player.GetIdentity().GetPlainId() == SteamId_sasaa){
			player.GetInventory().CreateInInventory("GhillieSuit_Woodland");
			player.GetInventory().CreateInInventory("GhillieHood_Woodland");
			
			// SmershVestBackpack
			EntityAI SmershVestBackpack = player.GetHumanInventory().CreateInInventory("SmershVest");
			SmershVestBackpack.GetInventory().CreateAttachment("SmershBag");
			
			// SawedoffMosin
			//EntityAI ghillie_SawedoffMosin = player.GetHumanInventory().CreateInInventory("SawedoffMosin9130_Camo");
			//ghillie_SawedoffMosin.GetInventory().CreateAttachment("ImprovisedSuppressor");
			//player.GetInventory().CreateInInventory("AmmoBox_762x54_20Rnd");
			//player.GetInventory().CreateInInventory("AmmoBox_762x54_20Rnd");
			//player.GetInventory().CreateInInventory("AmmoBox_762x54_20Rnd");
		} else {
			player.GetInventory().CreateInInventory("HuntingBag");
		}
		player.GetInventory().CreateInInventory("StoneKnife");
		player.GetInventory().CreateInInventory("SodaCan_Cola");
		player.GetInventory().CreateInInventory("SodaCan_Cola");
		player.GetInventory().CreateInInventory("SodaCan_Cola");
		player.GetInventory().CreateInInventory("SodaCan_Cola");
		player.GetInventory().CreateInInventory("TacticalBaconCan");
		player.GetInventory().CreateInInventory("TacticalBaconCan");
		player.GetInventory().CreateInInventory("CanOpener");
		player.GetInventory().CreateInInventory("BandageDressing");
		player.GetInventory().CreateInInventory("BandageDressing");
		player.GetInventory().CreateInInventory("DuctTape");
		player.GetInventory().CreateInInventory("AmmoBox_556x45_20Rnd");
		player.GetInventory().CreateInInventory("AmmoBox_556x45_20Rnd");
		player.GetInventory().CreateInInventory("AmmoBox_556x45_20Rnd");
		player.GetInventory().CreateInInventory("AmmoBox_556x45_20Rnd");
		player.GetInventory().CreateInInventory("Mag_STANAGCoupled_30Rnd");
		player.GetInventory().CreateInInventory("Mag_STANAGCoupled_30Rnd");
		player.GetInventory().CreateInInventory("Mag_IJ70_8Rnd");
		player.GetInventory().CreateInInventory("Mag_IJ70_8Rnd");
		player.GetInventory().CreateInInventory("Mag_IJ70_8Rnd");
		player.GetInventory().CreateInInventory("AmmoBox_380_35rnd");
		player.GetInventory().CreateInInventory("AmmoBox_380_35rnd");
		
		EntityAI ghilly_flashlight = player.GetHumanInventory().CreateInInventory("Flashlight");
		ghilly_flashlight.GetInventory().CreateAttachment("Battery9V");
		
		// M4A1 Green
		EntityAI ghillie_m4a1 = player.GetHumanInventory().CreateInHands("M4A1_Green");
		ghillie_m4a1.GetInventory().CreateAttachment("M4_Suppressor");
		ghillie_m4a1.GetInventory().CreateAttachment("M4_RISHndgrd_Green");
		ghillie_m4a1.GetInventory().CreateAttachment("M4_MPBttstck_Green");
		ghillie_m4a1.GetInventory().CreateAttachment("acogoptic");
		//! glitched ghillie_m4a1.GetInventory().CreateAttachment("Mag_STANAGCoupled_30Rnd");
		
		// Marakov
		EntityAI ghillie_marakov = player.GetHumanInventory().CreateInInventory("MakarovIJ70");
		ghillie_marakov.GetInventory().CreateAttachment("PistolSuppressor");
		
		/*!  - Not working jet
		//Glock19
		EntityAI Glock_ghilly = player.GetHumanInventory().CreateInInventory("Glock19");
		Glock_ghilly.GetInventory().CreateAttachment("PistolSuppressor");
		player.GetInventory().CreateInInventory("Mag_Glock_15Rnd");
		player.GetInventory().CreateInInventory("Mag_Glock_15Rnd");
		player.GetInventory().CreateInInventory("Mag_VSS_10Rnd");
		player.GetInventory().CreateInInventory("Mag_VSS_10Rnd");
		ItemBase sp6_ammo0 = player.GetInventory().CreateInInventory("Ammo_9x39");
		sp6_ammo0.SetQuantity(20);
		ItemBase sp6_ammo1 = player.GetInventory().CreateInInventory("Ammo_9x39");
		sp6_ammo1.SetQuantity(20);
		// Vss - Not working jet
		EntityAI vss = player.GetHumanInventory().CreateInHands("VSS");
		vss.GetInventory().CreateAttachment("GhillieAtt_Woodland");
		vss.GetInventory().CreateAttachment("PSO11Optic");
		// Rangefinder
		EntityAI Tools_rangefinder = player.GetHumanInventory().CreateInInventory("Rangefinder");
		Tools_rangefinder.GetInventory().CreateAttachment("Battery9V");
		*/
		
		// Fireaxe
		EntityAI Fireaxe_ghilly = player.GetHumanInventory().CreateInInventory("FirefighterAxe_Green");
	} else {
		switch (Math.RandomInt(3, 11)) {
			case 0:
			// Knight
			player.RemoveAllItems();
			player.GetInventory().CreateInInventory("TaloonBag_Blue");
			player.GetInventory().CreateInInventory("GreatHelm");
			player.GetInventory().CreateInInventory("Kiwi");
			player.GetInventory().CreateInInventory("Kiwi");
			player.GetInventory().CreateInInventory("SodaCan_cola");
			player.GetInventory().CreateInInventory("SodaCan_spite");
			EntityAI Melee_Sword = player.GetInventory().CreateInInventory("Sword");
			break;

			case 1:
			// Miner
			player.RemoveAllItems();
			player.GetInventory().CreateInInventory("TaloonBag_Green");
			player.GetInventory().CreateInInventory("WorkingGloves_Yellow");
			player.GetInventory().CreateInInventory("Apple");
			player.GetInventory().CreateInInventory("Apple");
			player.GetInventory().CreateInInventory("SodaCan_Pipsi");
			player.GetInventory().CreateInInventory("SodaCan_cola");
			player.GetInventory().CreateInInventory("SpaghettiCan");
			EntityAI Melee_Pickaxe = player.GetHumanInventory().CreateInInventory("Pickaxe");
			break;
			
			case 2:
			// Lumberjack
			player.RemoveAllItems();
			player.GetInventory().CreateInInventory("Shirt_RedCheck");
			player.GetInventory().CreateInInventory("WorkingGloves_Brown");
			player.GetInventory().CreateInInventory("Jeans_Blue");
			player.GetInventory().CreateInInventory("WorkingBoots_Brown");
			player.GetInventory().CreateInInventory("Ushanka_Green");
			EntityAI Melee_woodaxe = player.GetHumanInventory().CreateInInventory("WoodAxe");
			break;
			
			case 4:
			// firefighter
			player.RemoveAllItems();
			player.GetInventory().CreateInInventory("FirefightersPants_Black");
			player.GetInventory().CreateInInventory("FirefighterJacket_Black");
			player.GetInventory().CreateInInventory("FirefightersHelmet_Red");
			player.GetInventory().CreateInInventory("WorkingGloves_Black");
			player.GetInventory().CreateInInventory("CombatBoots_Black");
			player.GetInventory().CreateInInventory("SodaCan_Pipsi");
			player.GetInventory().CreateInInventory("SodaCan_Cola");
			player.GetInventory().CreateInInventory("BakedBeansCan");
			EntityAI Melee_Fireaxe = player.GetInventory().CreateInInventory("FirefighterAxe_Black");
			break;
			
			case 5:
			// armyman
			player.RemoveAllItems();
			player.GetInventory().CreateInInventory("TTSKOPants");
			player.GetInventory().CreateInInventory("TTsKOJacket_Camo");
			player.GetInventory().CreateInInventory("TacticalGloves_Green");
			player.GetInventory().CreateInInventory("CombatBoots_Black");
			player.GetInventory().CreateInInventory("ImprovisedBag");
			player.GetInventory().CreateInInventory("CombatKnife");
			player.GetInventory().CreateInInventory("SodaCan_Cola");
			player.GetInventory().CreateInInventory("SodaCan_Pipsi");
			player.GetInventory().CreateInInventory("TacticalBaconCan");
			player.GetInventory().CreateInInventory("BandageDressing");
			player.GetInventory().CreateInInventory("AmmoBox_556x45_20Rnd");
			player.GetInventory().CreateInInventory("AmmoBox_556x45_20Rnd");
			// Army_porta
			EntityAI portable1 = player.GetHumanInventory().CreateInInventory("PersonalRadio");
			portable1.GetInventory().CreateAttachment("Battery9V");
			break;

			case 6:
			// paramedic
			player.RemoveAllItems();			
			player.GetInventory().CreateInInventory("TaloonBag_Black");
			player.GetInventory().CreateInInventory("ParamedicPants_Green");
			player.GetInventory().CreateInInventory("ParamedicJacket_Green");
			player.GetInventory().CreateInInventory("Athleticshoes_Grey");
			player.GetInventory().CreateInInventory("KitchenKnife");
			player.GetInventory().CreateInInventory("TaloonBag_Red");
			player.GetInventory().CreateInInventory("Canteen");
			player.GetInventory().CreateInInventory("SalineBagIV");
			player.GetInventory().CreateInInventory("BandageDressing");
			player.GetInventory().CreateInInventory("Morphine");
			player.GetInventory().CreateInInventory("BloodBagIV");
			player.GetInventory().CreateInInventory("Morphine");
			player.GetInventory().CreateInInventory("KitchenKnife");
			break;

			
			case 7:
			// Hunter Autumn
			player.RemoveAllItems();
			player.GetInventory().CreateInInventory("HunterPants_Autumn");
			player.GetInventory().CreateInInventory("HuntingJacket_Autumn");
			player.GetInventory().CreateInInventory("TacticalGloves_Black");
			player.GetInventory().CreateInInventory("CombatBoots_Black");
			player.GetInventory().CreateInInventory("HuntingKnife");
			player.GetInventory().CreateInInventory("ImprovisedBag");
			break;


			case 8:
			// hunter Spring
			player.RemoveAllItems();
			player.GetInventory().CreateInInventory("HuntingJacket_Spring");
			player.GetInventory().CreateInInventory("HunterPants_Spring");
			player.GetInventory().CreateInInventory("TacticalGloves_Green");
			player.GetInventory().CreateInInventory("HuntingJacket_Spring");
			player.GetInventory().CreateInInventory("CombatBoots_Black");
			player.GetInventory().CreateInInventory("ImprovisedBag");
			player.GetInventory().CreateInInventory("HuntingKnife");
			player.GetInventory().CreateInInventory("Canteen");
			player.GetInventory().CreateInInventory("TacticalBaconCan");
			player.GetInventory().CreateInInventory("TacticalBaconCan");
			break;
			
			case 9:
			// Cop
			player.RemoveAllItems();
			player.GetInventory().CreateInInventory("PoliceJacket");
			player.GetInventory().CreateInInventory("PolicePants");
			player.GetInventory().CreateInInventory("CombatBoots_Grey");
			player.GetInventory().CreateInInventory("Apple");
			player.GetInventory().CreateInInventory("Apple");
			player.GetInventory().CreateInInventory("Apple");
			// Porto
			EntityAI Police_porto = player.GetHumanInventory().CreateInInventory("PersonalRadio");
			Police_porto.GetInventory().CreateAttachment("Battery9V");
			// flashlight
			EntityAI Police_flashlight = player.GetHumanInventory().CreateInInventory("Flashlight");
			Police_flashlight.GetInventory().CreateAttachment("Battery9V");
			break;
			
			case 10:
			// Biker
			player.RemoveAllItems();
			player.GetInventory().CreateInInventory("Jeans_Black");
			player.GetInventory().CreateInInventory("RidersJacket_Black");
			player.GetInventory().CreateInInventory("MotoHelmet_Black");
			player.GetInventory().CreateInInventory("CombatBoots_Black");
			player.GetInventory().CreateInInventory("WorkingGloves_Black");
			player.GetInventory().CreateInInventory("HuntingKnife");
			player.GetInventory().CreateInInventory("BaseballBat");
			break;
			
			case 11:
			// mule
			player.RemoveAllItems();
			player.GetInventory().CreateInInventory("Jeans_Black");
			player.GetInventory().CreateInInventory("Hoodie_Black");
			player.GetInventory().CreateInInventory("AliceBag_Black");
			player.GetInventory().CreateInInventory("Wellies_Black");
			player.GetInventory().CreateInInventory("SodaCan_cola");
			player.GetInventory().CreateInInventory("SodaCan_cola");
			player.GetInventory().CreateInInventory("SodaCan_spite");
			player.GetInventory().CreateInInventory("SodaCan_spite");
			player.GetInventory().CreateInInventory("SodaCan_Kvass");
			player.GetInventory().CreateInInventory("SodaCan_Kvass");
			player.GetInventory().CreateInInventory("SodaCan_pipsi");
			player.GetInventory().CreateInInventory("SodaCan_pipsi");
			player.GetInventory().CreateInInventory("SpaghettiCan_Opened");
			player.GetInventory().CreateInInventory("SpaghettiCan_Opened");
			player.GetInventory().CreateInInventory("Apple");
			player.GetInventory().CreateInInventory("Apple");
			player.GetInventory().CreateInInventory("Apple");
			player.GetInventory().CreateInInventory("Apple");
			player.GetInventory().CreateInInventory("AmmoBox_00buck_10rnd");
			player.GetInventory().CreateInInventory("AmmoBox_00buck_10rnd");
			player.GetInventory().CreateInInventory("AmmoBox_380_35rnd");
			player.GetInventory().CreateInInventory("AmmoBox_380_35rnd");
			player.GetInventory().CreateInInventory("AmmoBox_45ACP_25rnd");
			player.GetInventory().CreateInInventory("AmmoBox_45ACP_25rnd");
			player.GetInventory().CreateInInventory("AmmoBox_556x45_20Rnd");
			player.GetInventory().CreateInInventory("AmmoBox_556x45_20Rnd");
			player.GetInventory().CreateInInventory("AmmoBox_762x39_20Rnd");
			player.GetInventory().CreateInInventory("AmmoBox_762x39_20Rnd");
			player.GetInventory().CreateInInventory("AmmoBox_762x54_20Rnd");
			player.GetInventory().CreateInInventory("AmmoBox_762x54_20Rnd");
			player.GetInventory().CreateInInventory("AmmoBox_9x19_25rnd");
			player.GetInventory().CreateInInventory("AmmoBox_9x19_25rnd");
			ItemBase sp6_ammo2 = player.GetInventory().CreateInInventory("Ammo_9x39");
			sp6_ammo2.SetQuantity(20);
			ItemBase sp6_ammo3 = player.GetInventory().CreateInInventory("Ammo_9x39");
			sp6_ammo3.SetQuantity(20);
			break;
			
			
			case 12:
			// Woodsman
			player.RemoveAllItems();
			player.GetInventory().CreateInInventory("BandanaMask_CamoPattern");
			player.GetInventory().CreateInInventory("HuntingJacket_Autumn");
			player.GetInventory().CreateInInventory("HunterPants_Autumn");
			player.GetInventory().CreateInInventory("BaseballCap_Cammo");
			player.GetInventory().CreateInInventory("CombatBoots_Black");
			player.GetInventory().CreateInInventory("ImprovisedBag");
			player.GetInventory().CreateInInventory("HuntingKnife");
			player.GetInventory().CreateInInventory("HuntingKnife");
			player.GetInventory().CreateInInventory("BaseballCap_Cammo");
			player.GetInventory().CreateInInventory("Mag_Arrows_Quiver");
			player.GetInventory().CreateInInventory("RecurveBow");
			player.GetInventory().CreateInInventory("Ammo_ArrowPrimitive");
			ItemBase Arrow_ammo0 = player.GetInventory().CreateInInventory("Ammo_ArrowPrimitive");
			Arrow_ammo0.SetQuantity(5);
			ItemBase Arrow_ammo1 = player.GetInventory().CreateInInventory("Ammo_ArrowPrimitive");
			Arrow_ammo1.SetQuantity(5);
			ItemBase Arrow_ammo2 = player.GetInventory().CreateInInventory("Ammo_ArrowPrimitive");
			Arrow_ammo1.SetQuantity(5);
			break;
		}
		
		// Rags
        ItemBase Items_Rags = player.GetInventory().CreateInInventory("Rag");
        Items_Rags.SetQuantity(Math.RandomInt(3, 6));
	}
	}
};
  
Mission CreateCustomMission(string path)
{
	return new CustomMission();
}