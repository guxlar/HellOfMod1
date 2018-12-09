
// init-milgear-with-car.c
void main()
{

	Hive ce = CreateHive();
	if ( ce )
		ce.InitOffline();

	Weather weather = g_Game.GetWeather();

	weather.GetOvercast().SetLimits( 0.0 , 0.0 );
	weather.GetRain().SetLimits( 0.0 , 0.0 );
	weather.GetFog().SetLimits( 0.0 , 0.0 );

	weather.GetOvercast().SetForecastChangeLimits( 0.0, 0.0 );
	weather.GetRain().SetForecastChangeLimits( 0.0, 0.0 );
	weather.GetFog().SetForecastChangeLimits( 0.15, 0.0 );

	weather.GetOvercast().SetForecastTimeLimits( 1800 , 1800 );
	weather.GetRain().SetForecastTimeLimits( 600 , 600 );
	weather.GetFog().SetForecastTimeLimits( 1800 , 1800 );

	weather.GetOvercast().Set( Math.RandomFloatInclusive(0.0, 0.0), 0, 0);
	weather.GetRain().Set( Math.RandomFloatInclusive(0.0, 0.0), 0, 0);
	weather.GetFog().Set( Math.RandomFloatInclusive(0.0, 0.0), 0, 0);
	
	weather.SetWindMaximumSpeed(10);
	weather.SetWindFunctionParams(0.1, 1.0, 50);
	GetGame().GetWorld().SetDate( 2018, 6, 7, 13, 0);
	}

class CustomMission: MissionServer
{	
	
	bool verify_admins = false; // true=verify presence of BI UID in admin list
	string cmd_prefix = "/"; // Must be special character
	ref TStringArray admins = {}; // Add your BI UID or SteamID

	bool IsPlayerAnAdmin(PlayerBase player) {
		bool found = false;
		for ( int i = 0; i < admins.Count(); ++i ) {
			if(player.GetIdentity().GetId() == admins[i] || player.GetIdentity().GetPlainId() == admins[i]) { found=true; break; }
		}
		return found;
	}

	void SendMessageToPlayer(PlayerBase player, string message) {
		Param1<string> param = new Param1<string>( message );
		GetGame().RPCSingleParam(player, ERPCs.RPC_USER_ACTION_MESSAGE, param, true, player.GetIdentity());
	}

	bool IsPlayer(string name) { 
		PlayerBase p;
		array<Man> players = new array<Man>; GetGame().GetPlayers(players);
		for ( int i = 0; i < players.Count(); ++i ) {
			p = players.Get(i);
			if(p.GetIdentity().GetName() == name) return true;
		}
		return false;
	}

	PlayerBase GetPlayer(string name) {
		PlayerBase p;
		array<Man> players = new array<Man>; GetGame().GetPlayers(players);
		for ( int i = 0; i < players.Count(); ++i ) {
			p = players.Get(i);
			if(p.GetIdentity().GetName() == name) return p;
		}
		return NULL;
	}

	override void OnEvent(EventType eventTypeId, Param params)  {
		super.OnEvent(eventTypeId,params);
		int i;
		PlayerBase player, temp_player;
		array<Man> players = new array<Man>; GetGame().GetPlayers(players);
		if(eventTypeId != ChatMessageEventTypeID) return; // Is chat message
		ChatMessageEventParams chat_params = ChatMessageEventParams.Cast( params );
		if(chat_params.param1 != 0 || chat_params.param2 == "") return; 
		player = GetPlayer(chat_params.param2);
		if(player == NULL) return;
		if(verify_admins && !IsPlayerAnAdmin(player)) { GetGame().AdminLog("[ADMCMD] (Unauthorized) " + player.GetIdentity().GetName() +" ("+player.GetIdentity().GetPlainId()+", "+player.GetIdentity().GetId()+") tried to execute "+ chat_params.param3); return; }
		string message = chat_params.param3, prefix, param0, command;
		TStringArray tokens = new TStringArray;
		message.Replace("` ", "&SPCESC!"); //Escape spaces before splitting
		message.Split(" ", tokens); int count = tokens.Count();

		for ( i = 0; i < count; ++i ) {
			message = tokens[i];
			message.Replace("&SPCESC!", " "); //.Replace doesn't work directly on TStringArray elements for some reason :(
			tokens[i] = message;
		}

		param0 = tokens.Get(0);
		param0.ParseStringEx(prefix); if(prefix != cmd_prefix) return;
		param0.ParseStringEx(command);
		GetGame().AdminLog("[ADMCMD] PLAYER: "+ player.GetIdentity().GetName() +" ("+player.GetIdentity().GetPlainId()+", "+player.GetIdentity().GetId()+") CMD: "+ command);
		  //=========== Mods ===========
  bool m_FullStatus     = false;  // Warning Full Stat all player
  bool m_FullStamina    = false;  // Warning Full Stamina all player
  bool m_DebugMonitor   = false;  // Debug Monitor off restart serv
  bool verify_admins    = false;  // true = verify presence of BI UID in admin list
  bool m_FreeCamera     = false;  // CameraTool
  bool m_AutoFreezeWalk = false;  // Auto Walk and Freeze Player
  //=========== Misc ===========
  string cmd_prefix = "!";        // Must be special character
  ref TStringArray admins = {};   // Add your BI UID
  //============================
		switch(command) {
			case "spawn": {
				if(count != 2) { SendMessageToPlayer(player, "/spawn [object]"); return; }
				GetGame().CreateObject(tokens[1], player.GetPosition(), false, true );
				SendMessageToPlayer(player, "[ObjectSpawn] Object spawned: " + tokens[1]);
				break;
			}

			case "inv": {
				if(count != 2) { SendMessageToPlayer(player, "/inv [object]"); return; }
				player.GetInventory().CreateInInventory(tokens[1]);
				SendMessageToPlayer(player, "[ObjectSpawn] Object spawned in inventorz: " + tokens[1]);
				break;
			}

			case "weapon": {
				if(count != 2) { SendMessageToPlayer(player, "/weapon [weapon]"); return; }
				EntityAI weapon;
				switch(tokens[1]) {
					case "ump": {
						weapon = player.GetHumanInventory().CreateInHands("UMP45");
						player.GetInventory().CreateInInventory("Mag_UMP_25Rnd");
						break;
					}

					case "cz61": {
						weapon = player.GetHumanInventory().CreateInHands("CZ61");
						player.GetInventory().CreateInInventory("Mag_CZ61_20Rnd");
						break;
					}

					case "mp5": {
						weapon = player.GetHumanInventory().CreateInHands("MP5K");
						weapon.GetInventory().CreateAttachment("MP5k_StockBttstck");
						weapon.GetInventory().CreateAttachment("MP5_PRailHndgrd");
						player.GetInventory().CreateInInventory("Mag_MP5_30Rnd");
						break;
					}

					case "svd": {
						weapon = player.GetHumanInventory().CreateInHands("SVD");
						weapon.GetInventory().CreateAttachment("PSO11Optic");
						player.GetInventory().CreateInInventory("Mag_SVD_10Rnd");
						break;
					}

					case "mp133": {
						weapon = player.GetHumanInventory().CreateInHands("Mp133Shotgun");
						player.GetInventory().CreateInInventory("Ammo_12gaPellets");
						break;
					}

					case "mosin": {
						weapon = player.GetHumanInventory().CreateInHands("Mosin9130");
						weapon.GetInventory().CreateAttachment("PUScopeOptic");
						player.GetInventory().CreateInInventory("Ammo_762x54");
						break;
					}

					case "m4": {
						weapon = player.GetHumanInventory().CreateInHands("M4A1_Black");
						weapon.GetInventory().CreateAttachment("M4_RISHndgrd_Black");
						weapon.GetInventory().CreateAttachment("M4_MPBttstck_Black");
						weapon.GetInventory().CreateAttachment("BUISOptic");
						player.GetInventory().CreateInInventory("Mag_STANAGCoupled_30Rnd");
						break;
					}

					case "akm": {
						weapon = player.GetHumanInventory().CreateInHands("AKM");
						weapon.GetInventory().CreateAttachment("AK_RailHndgrd");
						weapon.GetInventory().CreateAttachment("AK_PlasticBttstck");
						player.GetInventory().CreateInInventory("Mag_AKM_30Rnd");
						break;
					}

					case "izh18": {
						weapon = player.GetHumanInventory().CreateInHands("Izh18");
						player.GetInventory().CreateInInventory("Ammo_762x39");
						break;
					}

					case "fnx": {
						weapon = player.GetHumanInventory().CreateInHands("FNX45");
						player.GetInventory().CreateInInventory("Mag_FNX45_15Rnd");
						break;
					}

					default: {
						SendMessageToPlayer(player, "[WeaponSpawner] " + tokens[1] + " not found");
						break;
					}
				}
				break;
			}

			case "strip": {
				if(count != 2) { SendMessageToPlayer(player, "/strip [player]"); return; }
				temp_player = GetPlayer(tokens[1]);
				if(temp_player == NULL) {
					SendMessageToPlayer(player, "[Strip] Can't find player called: '"+tokens[1]+"'");
				} else {
					temp_player.RemoveAllItems();
					SendMessageToPlayer(player, "[Strip] You stripped " + temp_player.GetIdentity().GetName());
					SendMessageToPlayer(temp_player, "You have been stripped by an admin");
				}
				break;
			}

			case "slap": {
				if(count != 2) { SendMessageToPlayer(player, "/slap [player]"); return; }
				temp_player = GetPlayer(tokens[1]);
				if(temp_player == NULL) {
					SendMessageToPlayer(player, "[Slap] Can't find player called: '"+tokens[1]+"'");
				} else {
					temp_player.SetPosition(temp_player.GetPosition() + "0 3 0");
					SendMessageToPlayer(player, "[Slap] You stripped " + temp_player.GetIdentity().GetName());
					SendMessageToPlayer(temp_player, "You have been slapped by an admin");
				}
				break;
			}
				
			case "topos": {
				if (count < 3) { SendMessageToPlayer(player, "/topos [x] [y] (player)"); return; }
				float ATL_Z = GetGame().SurfaceY(tokens[1].ToFloat(), tokens[2].ToFloat());
				vector reqpos = Vector(tokens[1].ToFloat(), ATL_Z, tokens[2].ToFloat());
				temp_player = player;
				if (count == 4) { 
					temp_player = GetPlayer(tokens[3]); 
					if (temp_player == NULL) {
						SendMessageToPlayer(player, "[Teleport] Can't find player called: '"+tokens[3]+"'"); return;
					} else {
						SendMessageToPlayer(temp_player, "[Teleport] You've been teleported to " + reqpos + " by admin " + player.GetIdentity().GetName());
					}
				}
				temp_player.SetPosition(reqpos);
				SendMessageToPlayer(player, "[Teleport] Target teleported to " + temp_player.GetPosition());
				break;
			}

			case "goto": {
				if(count != 2) { SendMessageToPlayer(player, "/goto [player]"); return; }
				temp_player = GetPlayer(tokens[1]);
				if(temp_player == NULL) {
					SendMessageToPlayer(player, "[Teleport] Can't find player called: '"+tokens[1]+"'");
				} else {
					player.SetPosition(temp_player.GetPosition());
					SendMessageToPlayer(player, "[Teleport] You teleported to " + temp_player.GetIdentity().GetName());
				}
				break;
			}

			case "allgoto": {
				PlayerBase allgoto_target;
				if(count != 2) { SendMessageToPlayer(player, "/allgoto [player]"); return; }
				allgoto_target = GetPlayer(tokens[1]);
				if(allgoto_target == NULL) {
					SendMessageToPlayer(player, "[Teleport] Can't find player called: '"+tokens[1]+"'");
				} else {
					SendMessageToPlayer(player, "[Teleport] You teleported everyone to your location");
					for (i = 0; i < players.Count(); i++) {
						temp_player = players.Get(i);
						SendMessageToPlayer(temp_player, "[Teleport] You have been teleported to player " + allgoto_target.GetIdentity().GetName());
						temp_player.SetPosition(allgoto_target.GetPosition());
					}
				}
				break;
			}

			case "here": {
				if(count != 2) { SendMessageToPlayer(player, "/here [player]"); return; }
				temp_player = GetPlayer(tokens[1]);
				if(temp_player == NULL) {
					SendMessageToPlayer(player, "[Teleport] Can't find player called: '"+tokens[1]+"'");
				} else {
					temp_player.SetPosition(player.GetPosition());
					SendMessageToPlayer(temp_player, "[Teleport] You have been teleported to admin " + player.GetIdentity().GetName());
					SendMessageToPlayer(player, "[Teleport] You teleported " + temp_player.GetIdentity().GetName() + " to your location");
				}
				break;
			}

			case "allhere": {
				SendMessageToPlayer(player, "[Teleport] You teleported everyone to your location");
				for (i = 0; i < players.Count(); i++) {
					temp_player = players.Get(i);
					SendMessageToPlayer(temp_player, "[Teleport] You have been teleported to admin " + player.GetIdentity().GetName());
					temp_player.SetPosition(player.GetPosition());
				}
				break;
			}

			case "time": {
				if(count != 3) { SendMessageToPlayer(player, "/time [hour] [minute]"); return; }
				GetGame().GetWorld().SetDate( 2018, 1, 7, tokens[1].ToInt(), tokens[2].ToInt());
				SendMessageToPlayer(player, "[Servertime] You have set the servertime to " + tokens[1] + ":"+tokens[2]);
				break;
			}
				
			case "day": {
				GetGame().GetWorld().SetDate( 2018, 6, 7, 13, 0);
				SendMessageToPlayer(player, "[Servertime] You have set the servertime to daytime");
				break;
			}

			case "night": {
				GetGame().GetWorld().SetDate( 2018, 6, 7, 24, 0);
				SendMessageToPlayer(player, "[Servertime] You have set the servertime to daytime");
				break;
			}

			case "rain": {
				if(count != 2) { SendMessageToPlayer(player, "/rain [value 0-100]"); return; }
				float rain = tokens[1].ToFloat() / 100;
				GetGame().GetWeather().GetRain().Set(rain, 2, 600);
				SendMessageToPlayer(player, "[Weather] You have set Rain to " + tokens[1] + "% ["+rain+"]");
				break;
			}

			case "fog": {
				if(count != 2) { SendMessageToPlayer(player, "/fog [value 0-100]"); return; }
				float fog = tokens[1].ToFloat() / 100;
				GetGame().GetWeather().GetFog().Set(fog, 2, 600);
				SendMessageToPlayer(player, "[Weather] You have set Fog to " + tokens[1] + "% ["+fog+"]");
				break;
			}

			case "overcast": {
				if(count != 2) { SendMessageToPlayer(player, "/overcast [value 0-100]"); return; }
				float overcast = tokens[1].ToFloat() / 100;
				GetGame().GetWeather().GetOvercast().Set(overcast, 2, 600);
				SendMessageToPlayer(player, "[Weather] You have set Overcast to " + tokens[1] + "% ["+overcast+"]");
				break;
			}

			case "kill": {
				if(count == 2) {
					temp_player = GetPlayer(tokens[1]);
					if(temp_player == NULL) {
						SendMessageToPlayer(player, "[Kill] Can't find player called: '"+tokens[1]+"'");
					} else {
						temp_player.SetHealth(0);
						SendMessageToPlayer(player, "[Kill] You killed " + temp_player.GetIdentity().GetName());
					}
				} else {
					player.SetHealth(0);
					SendMessageToPlayer(player, "[Kill] You killed yourself");
				}
				break;
			}

			case "killall": {
				SendMessageToPlayer(player, "[Kill] You killed everyone");
				for (i = 0; i < players.Count(); i++) {
					temp_player = players.Get(i);
					if(temp_player.GetIdentity().GetId() == player.GetIdentity().GetId()) continue;
					temp_player.SetHealth(0);
				}
				break;
			}

			case "heal": {
				PlayerBase heal_target;
				if(count == 2) {
					heal_target = GetPlayer(tokens[1]);
					if(heal_target == NULL) {
						SendMessageToPlayer(player, "[Heal] Can't find player called: '"+tokens[1]+"'");
					} else {
						SendMessageToPlayer(player, "[Heal] You healed " + heal_target.GetIdentity().GetName());
					}
				} else {
					heal_target = player;
					SendMessageToPlayer(player, "[Heal] You healed yourself");
				}
				if(heal_target != NULL) {
					heal_target.SetHealth(heal_target.GetMaxHealth("", ""));
					heal_target.SetHealth("", "Blood", heal_target.GetMaxHealth("", "Blood"));
					heal_target.GetStatStamina().Set(1000);
					heal_target.GetStatEnergy().Set(1000);
					heal_target.GetStatWater().Set(1000);
				}
				break;
			}

			
			case "offroad": {
				SendMessageToPlayer(player, "[Offroad] Vehicled spawned");
				Car v;
				float playerAngle = MiscGameplayFunctions.GetHeadingAngle(player);
				vector posModifier = Vector(-(3 * Math.Sin(playerAngle)), 0, 3 * Math.Cos(playerAngle));
				v = Car.Cast(GetGame().CreateObject( "OffroadHatchback", player.GetPosition() + posModifier));
				
				v.GetInventory().CreateAttachment("SparkPlug");
				v.GetInventory().CreateAttachment("EngineBelt");
				v.GetInventory().CreateAttachment("CarBattery");
				v.GetInventory().CreateAttachment("CarBattery");
				v.GetInventory().CreateAttachment("HatchbackHood");
				v.GetInventory().CreateAttachment("HatchbackTrunk");
				v.GetInventory().CreateAttachment("HatchbackDoors_CoDriver");
				v.GetInventory().CreateAttachment("HatchbackWheel");
				v.GetInventory().CreateAttachment("HatchbackWheel");
				v.GetInventory().CreateAttachment("HatchbackWheel");
				v.GetInventory().CreateAttachment("HatchbackWheel");
				v.GetInventory().CreateAttachment("HatchbackWheel"); // spare
				break;
			}

			case "cam": {
				PlayerBase pBody = player;
				if (m_FreeCamera)
				{
					GetGame().SelectPlayer(player.GetIdentity(), pBody);
					player.GetInputController().OverrideMovementSpeed( false, 0 );
                    player.GetInputController().OverrideMovementAngle( false, 0 );
                    player.GetInputController().OverrideAimChangeX( false, 0 );
                    player.GetInputController().OverrideAimChangeY( false, 0 );
					m_FreeCamera = false;
				}
				else
				{
					GetGame().SelectPlayer(player.GetIdentity(), NULL);
					GetGame().SelectSpectator(player.GetIdentity(), "freedebugcamera", player.GetPosition());
					player.GetInputController().OverrideMovementSpeed( true, 0 );
                    player.GetInputController().OverrideMovementAngle( true, 0 );
					player.GetInputController().OverrideAimChangeX( true, 0 );
					player.GetInputController().OverrideAimChangeY( true, 0 );
					m_FreeCamera = true;
				}
				break;
			}
			
			case "sniper": {
				PlayerBase sniper_target;
				if(count == 2) {
					sniper_target = GetPlayer(tokens[1]);
					if(sniper_target == NULL) {
						SendMessageToPlayer(player, "Can't find player called: '"+tokens[1]+"'");
					} else {
						SendMessageToPlayer(player, "You Give stuff sniper to " + sniper_target.GetIdentity().GetName());
					}
				} else {
					sniper_target = player;
					SendMessageToPlayer(player, "You Give stuff sniper");
				}
				if(sniper_target != NULL) {
					sniper_target.RemoveAllItems();                                                 // Remove All Items
					sniper_target.GetStatWater().Set(1000);                                         // Water       100%

					sniper_target.GetInventory().CreateInInventory("Balaclava3Holes_Green");
					sniper_target.GetInventory().CreateInInventory("TacticalGloves_Green");         // Tactical Gloves  Green
					sniper_target.GetInventory().CreateInInventory("TTsKOJacket_Camo");	            // TTsKO Jacket     Camo
					sniper_target.GetInventory().CreateInInventory("HighCapacityVest_Olive");       // HighCapacityVest Olive
					sniper_target.GetInventory().CreateInInventory("TTSKOPants");                   // TTSKO Pants
			
					EntityAI mbs = sniper_target.GetInventory().CreateInInventory("MilitaryBoots_Brown");
					mbs.GetInventory().CreateAttachment("CombatKnife");

					sniper_target.GetInventory().CreateInInventory("GhillieHood_Mossy");            // Ghillie Hood
					sniper_target.GetInventory().CreateInInventory("GhillieSuit_Mossy");            // Ghillie Suit
		
					EntityAI Smapct = sniper_target.GetInventory().CreateInInventory("SmallProtectorCase");
					Smapct.GetInventory().CreateInInventory("Lockpick");
					Smapct.GetInventory().CreateInInventory("ChernarusMap");
					Smapct.GetInventory().CreateInInventory("DuctTape");
					Smapct.GetInventory().CreateInInventory("Roadflare");
					Smapct.GetInventory().CreateInInventory("Rope");
					Smapct.GetInventory().CreateInInventory("WaterBottle");
					Smapct.GetInventory().CreateInInventory("Battery9V");
					Smapct.GetInventory().CreateInInventory("Compass");
					Smapct.GetInventory().CreateInInventory("Matchbox");

					EntityAI rds = sniper_target.GetInventory().CreateInInventory("PersonalRadio");
					rds.GetInventory().CreateAttachment("Battery9V");		

					EntityAI boxtf = sniper_target.GetInventory().CreateInInventory("AmmoBox");	
					EntityAI ttaksa = boxtf.GetInventory().CreateInInventory("FNX45");
					ttaksa.GetInventory().CreateAttachment("PistolSuppressor");
					ttaksa.GetInventory().CreateAttachment("FNP45_MRDSOptic");
					ttaksa.GetInventory().CreateAttachment("UniversalLight");
					boxtf.GetInventory().CreateInInventory("AmmoBox_45ACP_25rnd");
					boxtf.GetInventory().CreateInInventory("AmmoBox_45ACP_25rnd");
					boxtf.GetInventory().CreateInInventory("AmmoBox_762x54_20Rnd");
					boxtf.GetInventory().CreateInInventory("AmmoBox_762x54_20Rnd");
					boxtf.GetInventory().CreateInInventory("Mag_FNX45_15Rnd");
					boxtf.GetInventory().CreateInInventory("Mag_FNX45_15Rnd");
					boxtf.GetInventory().CreateInInventory("Mag_SVD_10Rnd");
					boxtf.GetInventory().CreateInInventory("Mag_SVD_10Rnd");
					boxtf.GetInventory().CreateInInventory("Mag_SVD_10Rnd");
					boxtf.GetInventory().CreateInInventory("Mag_SVD_10Rnd");
							
					sniper_target.GetInventory().CreateInInventory("Binoculars");
					sniper_target.GetInventory().CreateInInventory("Cannabis");
					sniper_target.GetInventory().CreateInInventory("Cannabis");
					sniper_target.GetInventory().CreateInInventory("Cannabis");				
					
					EntityAI boxms = sniper_target.GetInventory().CreateInInventory("FirstAidKit");
					boxms.GetInventory().CreateInInventory("SalineBagIV");		
					boxms.GetInventory().CreateInInventory("Morphine");	
					boxms.GetInventory().CreateInInventory("Epinephrine");	
					boxms.GetInventory().CreateInInventory("BandageDressing");	
					boxms.GetInventory().CreateInInventory("BandageDressing");	
					boxms.GetInventory().CreateInInventory("BandageDressing");	
					boxms.GetInventory().CreateInInventory("BandageDressing");					

					sniper_target.GetInventory().CreateInInventory("Chemlight_Green");	            // Chemlight Green
					sniper_target.GetInventory().CreateInInventory("SodaCan_Cola");
					sniper_target.GetInventory().CreateInInventory("SodaCan_Cola");
					sniper_target.GetInventory().CreateInInventory("SardinesCan_Opened");					

					EntityAI aSVD = sniper_target.GetHumanInventory().CreateInHands("SVD");         // SVD
					aSVD.GetInventory().CreateAttachment("GhillieAtt_Woodland");                    // Ghillie Weapons
					aSVD.GetInventory().CreateAttachment("PSO1Optic");                              // PSO1 optique   
				}
				break;
			}		
			case "zombie": {
				PlayerBase zombie_target;
				if(count == 2) {
					zombie_target = GetPlayer(tokens[1]);
					if(zombie_target == NULL) {
						SendMessageToPlayer(player, "Can't find player called: '"+tokens[1]+"'");
					} else {
						SendMessageToPlayer(player, "You spawn zombie to " + zombie_target.GetIdentity().GetName());
					}
				} else {
					zombie_target = player;
					SendMessageToPlayer(player, "Zombie spawned");
				}
				if(zombie_target != NULL) {
					GetGame().CreateObject( "ZmbF_CitizenANormal_Blue", zombie_target.GetPosition()- "10 0 0", false, true );
				}
				break;
			}
            // ---------------------------------------------------------------------------------------------------------				
			case "horde": {
				PlayerBase horde_target;
				if(count == 2) {
					horde_target = GetPlayer(tokens[1]);
					if(horde_target == NULL) {
						SendMessageToPlayer(player, "Can't find player called: '"+tokens[1]+"'");
					} else {
						SendMessageToPlayer(player, "You spawn horde to " + horde_target.GetIdentity().GetName());
					}
				} else {
					horde_target = player;
					SendMessageToPlayer(player, "Horde spawned");
				}
				if(horde_target != NULL) {

					GetGame().CreateObject( "ZmbF_BlueCollarFat_Blue", horde_target.GetPosition()- "50 0 0", false, true );			
					GetGame().CreateObject( "ZmbF_BlueCollarFat_Green", horde_target.GetPosition()- "0 0 50", false, true );
					GetGame().CreateObject( "ZmbF_BlueCollarFat_Red", horde_target.GetPosition()- "50 0 -50", false, true );	
					GetGame().CreateObject( "ZmbF_BlueCollarFat_White", horde_target.GetPosition()- "-50 0 50", false, true );	
					GetGame().CreateObject( "ZmbF_CitizenANormal_Beige", horde_target.GetPosition()- "51 0 0", false, true );		
					GetGame().CreateObject( "ZmbF_CitizenANormal_Blue", horde_target.GetPosition()- "51 0 0", false, true );			
					GetGame().CreateObject( "ZmbF_CitizenANormal_Brown", horde_target.GetPosition()- "0 0 51", false, true );
					GetGame().CreateObject( "ZmbF_CitizenBSkinny", horde_target.GetPosition()- "51 0 -51", false, true );	
					GetGame().CreateObject( "ZmbF_Clerk_Normal_Blue", horde_target.GetPosition()- "-51 0 51", false, true );	
					GetGame().CreateObject( "ZmbF_Clerk_Normal_Green", horde_target.GetPosition()- "52 0 0", false, true );		
					GetGame().CreateObject( "ZmbF_Clerk_Normal_Red", horde_target.GetPosition()- "52 0 0", false, true );			
					GetGame().CreateObject( "ZmbF_Clerk_Normal_White", horde_target.GetPosition()- "0 0 52", false, true );
					GetGame().CreateObject( "ZmbF_DoctorSkinny", horde_target.GetPosition()- "52 0 -52", false, true );	
					GetGame().CreateObject( "ZmbF_HikerSkinny_Blue", horde_target.GetPosition()- "-52 0 52", false, true );		
					GetGame().CreateObject( "ZmbF_HikerSkinny_Green", horde_target.GetPosition()- "53 0 0", false, true );			
					GetGame().CreateObject( "ZmbF_HikerSkinny_Grey", horde_target.GetPosition()- "0 0 53", false, true );
					GetGame().CreateObject( "ZmbF_HikerSkinny_Red", horde_target.GetPosition()- "53 0 -53", false, true );	
					GetGame().CreateObject( "ZmbF_JoggerSkinny_Blue", horde_target.GetPosition()- "-53 0 53", false, true );
					GetGame().CreateObject( "ZmbF_JoggerSkinny_Brown", horde_target.GetPosition()- "54 0 0", false, true );			
					GetGame().CreateObject( "ZmbF_JoggerSkinny_Green", horde_target.GetPosition()- "0 0 54", false, true );
					GetGame().CreateObject( "ZmbF_JoggerSkinny_Red", horde_target.GetPosition()- "54 0 -54", false, true );	
					GetGame().CreateObject( "ZmbF_JournalistNormal_Blue", horde_target.GetPosition()- "-54 0 54", false, true );
					GetGame().CreateObject( "ZmbF_JournalistNormal_Green", horde_target.GetPosition()- "55 0 0", false, true );			
					GetGame().CreateObject( "ZmbF_JournalistNormal_Red", horde_target.GetPosition()- "0 0 55", false, true );
					GetGame().CreateObject( "ZmbF_JournalistNormal_White", horde_target.GetPosition()- "55 0 -55", false, true );	
					GetGame().CreateObject( "ZmbF_MechanicNormal_Beige", horde_target.GetPosition()- "-55 0 55", false, true );
					GetGame().CreateObject( "ZmbF_MechanicNormal_Green", horde_target.GetPosition()- "56 0 0", false, true );			
					GetGame().CreateObject( "ZmbF_MechanicNormal_Grey", horde_target.GetPosition()- "0 0 56", false, true );
					GetGame().CreateObject( "ZmbF_MechanicNormal_Orange", horde_target.GetPosition()- "56 0 -56", false, true );	
					GetGame().CreateObject( "ZmbF_MilkMaidOld_Beige", horde_target.GetPosition()- "-56 0 56", false, true );	
					GetGame().CreateObject( "ZmbF_MilkMaidOld_Black", horde_target.GetPosition()- "57 0 0", false, true );			
					GetGame().CreateObject( "ZmbF_MilkMaidOld_Green", horde_target.GetPosition()- "0 0 57", false, true );
					GetGame().CreateObject( "ZmbF_MilkMaidOld_Grey", horde_target.GetPosition()- "57 0 -57", false, true );	
					GetGame().CreateObject( "ZmbF_NurseFat", horde_target.GetPosition()- "-57 0 57", false, true );	
					GetGame().CreateObject( "ZmbF_ParamedicNormal_Blue", horde_target.GetPosition()- "58 0 0", false, true );			
					GetGame().CreateObject( "ZmbF_ParamedicNormal_Green", horde_target.GetPosition()- "0 0 58", false, true );
					GetGame().CreateObject( "ZmbF_ParamedicNormal_Red", horde_target.GetPosition()- "58 0 -58", false, true );	
					GetGame().CreateObject( "ZmbF_PatientOld", horde_target.GetPosition()- "-58 0 58", false, true );	
					GetGame().CreateObject( "ZmbF_PoliceWomanNormal", horde_target.GetPosition()- "59 0 0", false, true );			
					GetGame().CreateObject( "ZmbF_ShortSkirt_beige", horde_target.GetPosition()- "0 0 59", false, true );
					GetGame().CreateObject( "ZmbF_ShortSkirt_black", horde_target.GetPosition()- "59 0 -59", false, true );	
					GetGame().CreateObject( "ZmbF_ShortSkirt_brown", horde_target.GetPosition()- "-59 0 59", false, true );	
					GetGame().CreateObject( "ZmbF_ShortSkirt_checks", horde_target.GetPosition()- "60 0 0", false, true );			
					GetGame().CreateObject( "ZmbF_ShortSkirt_green", horde_target.GetPosition()- "0 0 60", false, true );
					GetGame().CreateObject( "ZmbF_ShortSkirt_grey", horde_target.GetPosition()- "60 0 -60", false, true );	
					GetGame().CreateObject( "ZmbF_ShortSkirt_red", horde_target.GetPosition()- "-60 0 60", false, true );	
					GetGame().CreateObject( "ZmbF_ShortSkirt_stripes", horde_target.GetPosition()- "61 0 0", false, true );			
					GetGame().CreateObject( "ZmbF_ShortSkirt_white", horde_target.GetPosition()- "0 0 61", false, true );
					GetGame().CreateObject( "ZmbF_ShortSkirt_yellow", horde_target.GetPosition()- "61 0 -61", false, true );	
					GetGame().CreateObject( "ZmbF_SkaterYoung_Brown", horde_target.GetPosition()- "-61 0 61", false, true );						
				}
				break;
			}
            // ---------------------------------------------------------------------------------------------------------				
			case "wolf": {
				PlayerBase wolf_target;
				if(count == 2) {
					wolf_target = GetPlayer(tokens[1]);
					if(wolf_target == NULL) {
						SendMessageToPlayer(player, "Can't find player called: '"+tokens[1]+"'");
					} else {
						SendMessageToPlayer(player, "You spawn wolf to " + wolf_target.GetIdentity().GetName());
					}
				} else {
					wolf_target = player;
					SendMessageToPlayer(player, "Wolf spawned");
				}
				if(wolf_target != NULL) {
					GetGame().CreateObject( "Animal_CanisLupus_Grey", wolf_target.GetPosition()- "10 0 0", false, true );
				}
				break;
			}			
						
			case "refuel": {
				ref array<Object> nearest_objects = new array<Object>;
				ref array<CargoBase> proxy_cargos = new array<CargoBase>;
				Car toBeFilled;
				vector position = player.GetPosition();
				GetGame().GetObjectsAtPosition ( position, 10, nearest_objects, proxy_cargos );
		
				for (i = 0; i < nearest_objects.Count(); i++) {
					if (nearest_objects[i].IsKindOf("CarScript")) {
						SendMessageToPlayer(player, "[Refuel] Found car: '"+nearest_objects[i]+"'");
						toBeFilled = Car.Cast(nearest_objects[i]);
						float fuelReq = toBeFilled.GetFluidCapacity( CarFluid.FUEL ) - (toBeFilled.GetFluidCapacity( CarFluid.FUEL ) * toBeFilled.GetFluidFraction( CarFluid.FUEL ));
						float oilReq = toBeFilled.GetFluidCapacity( CarFluid.OIL ) - (toBeFilled.GetFluidCapacity( CarFluid.OIL ) * toBeFilled.GetFluidFraction( CarFluid.OIL ));
						float coolantReq = toBeFilled.GetFluidCapacity( CarFluid.COOLANT ) - (toBeFilled.GetFluidCapacity( CarFluid.COOLANT ) * toBeFilled.GetFluidFraction( CarFluid.COOLANT ));
						float brakeReq = toBeFilled.GetFluidCapacity( CarFluid.BRAKE ) - (toBeFilled.GetFluidCapacity( CarFluid.BRAKE ) * toBeFilled.GetFluidFraction( CarFluid.BRAKE ));
						toBeFilled.Fill( CarFluid.FUEL, fuelReq );
						toBeFilled.Fill( CarFluid.OIL, oilReq );
						toBeFilled.Fill( CarFluid.COOLANT, coolantReq );
						toBeFilled.Fill( CarFluid.BRAKE, brakeReq );
						SendMessageToPlayer(player, "[Refuel] "+fuelReq+"L added, all fluids maxed");
					}
				}
				
				break;
			}

			default: {
				SendMessageToPlayer(player, "Unknown command: " + command);
				break;
			}
		}
	}
	
	void SetRandomHealth(EntityAI itemEnt)
	{
		int rndHlt = Math.RandomInt(40,100);
		itemEnt.SetHealth("","",rndHlt);
	}

	override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName)
	{
		Entity playerEnt;
		playerEnt = GetGame().CreatePlayer(identity, characterName, pos, 0, "NONE"); //Creates random player
		Class.CastTo(m_player, playerEnt);
		
		GetGame().SelectPlayer(identity, m_player);
		
		return m_player;
	}
	
	override void StartingEquipSetup(PlayerBase player, bool clothesChosen) 
	{
		player.RemoveAllItems();
		
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
		oCar.SetAllowDamage(true);

		auto carfluids = Car.Cast( oCar );
		carfluids.Fill( CarFluid.FUEL, 1000 );
		carfluids.Fill( CarFluid.OIL, 1000 );
		carfluids.Fill( CarFluid.BRAKE, 1000 );
		carfluids.Fill( CarFluid.COOLANT, 1000 );		

		// EQUIP THE CHARACTER
		
		player.GetInventory().CreateInInventory("TTSKOPants");
		player.GetInventory().CreateInInventory("TTsKOJacket_Camo");
		player.GetInventory().CreateInInventory("CombatBoots_Black");
		player.GetInventory().CreateInInventory("HuntingBag");
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
		player.GetInventory().CreateInInventory("Canteen");
		player.GetInventory().CreateInInventory("Binoculars");
		
		// M4A1 Green
		EntityAI ghillie_m4a1 = player.GetHumanInventory().CreateInInventory("M4A1_Green");
		ghillie_m4a1.GetInventory().CreateAttachment("M4_Suppressor");
		ghillie_m4a1.GetInventory().CreateAttachment("M4_RISHndgrd_Green");
		ghillie_m4a1.GetInventory().CreateAttachment("M4_MPBttstck_Green");
		ghillie_m4a1.GetInventory().CreateAttachment("acogoptic");
		
		// Flashlight
		EntityAI ghilly_flashlight = player.GetHumanInventory().CreateInInventory("Flashlight");
		ghilly_flashlight.GetInventory().CreateAttachment("Battery9V");
		
		// Marakov
		EntityAI ghillie_marakov = player.GetHumanInventory().CreateInInventory("MakarovIJ70");
		ghillie_marakov.GetInventory().CreateAttachment("PistolSuppressor");		

		// Fireaxe
		EntityAI Fireaxe_ghilly = player.GetHumanInventory().CreateInInventory("FirefighterAxe_Green");	
		
		// Radio
		EntityAI oRadio = player.GetHumanInventory().CreateInInventory("PersonalRadio");
		oRadio.GetInventory().CreateAttachment("Battery9V");		
				
		// Tent in hands
		EntityAI oMediumTent = player.GetHumanInventory().CreateInHands("MediumTent");
		
	}
		
};
  
Mission CreateCustomMission(string path)
{
	return new CustomMission();
}