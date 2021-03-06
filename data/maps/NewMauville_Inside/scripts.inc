NewMauville_Inside_MapScripts:: @ 82373D7
	map_script MAP_SCRIPT_ON_RESUME, NewMauville_Inside_MapScript1_2373E7
	map_script MAP_SCRIPT_ON_TRANSITION, NewMauville_Inside_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, NewMauville_Inside_MapScript1_23744D
	.byte 0

NewMauville_Inside_MapScript1_2373E7: @ 82373E7
	compare VAR_TEMP_1, 1
	call_if_eq NewMauville_Inside_EventScript_237489
	compare VAR_TEMP_2, 1
	call_if_eq NewMauville_Inside_EventScript_2375D7
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, NewMauville_Inside_EventScript_237407
	end

NewMauville_Inside_EventScript_237407:: @ 8237407
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_ne Common_EventScript_NopReturn
	removeobject VAR_LAST_TALKED
	return

NewMauville_Inside_OnTransition: @ 823741B
	setvar VAR_TEMP_1, 0
	setvar VAR_TEMP_2, 0
	call_if_unset FLAG_DEFEATED_SCRAGGY_1_NEW_MAUVILLE, NewMauville_Inside_EventScript_237441
	call_if_unset FLAG_DEFEATED_SCRAGGY_2_NEW_MAUVILLE, NewMauville_Inside_EventScript_237445
	call_if_unset FLAG_DEFEATED_SCRAGGY_3_NEW_MAUVILLE, NewMauville_Inside_EventScript_237449
	end

NewMauville_Inside_EventScript_237441:: @ 8237441
	clearflag FLAG_HIDE_NEW_MAUVILLE_SCRAGGY_1
	return

NewMauville_Inside_EventScript_237445:: @ 8237445
	clearflag FLAG_HIDE_NEW_MAUVILLE_SCRAGGY_2
	return

NewMauville_Inside_EventScript_237449:: @ 8237449
	clearflag FLAG_HIDE_NEW_MAUVILLE_SCRAGGY_3
	return

NewMauville_Inside_MapScript1_23744D: @ 823744D
	compare VAR_NEW_MAUVILLE_STATE, 2
	call_if_eq NewMauville_Inside_EventScript_23773A
	end

NewMauville_Inside_EventScript_237459:: @ 8237459
	lockall
	setvar VAR_TEMP_1, 1
	setvar VAR_TEMP_2, 0
	playse SE_PIN
	call NewMauville_Inside_EventScript_237489
	special DrawWholeMapView
	releaseall
	end

NewMauville_Inside_EventScript_237471:: @ 8237471
	lockall
	setvar VAR_TEMP_1, 0
	setvar VAR_TEMP_2, 1
	playse SE_PIN
	call NewMauville_Inside_EventScript_2375D7
	special DrawWholeMapView
	releaseall
	end

NewMauville_Inside_EventScript_237489:: @ 8237489
	setmetatile 23, 34, METATILE_BikeShop_Barrier_Hidden_Top, 1
	setmetatile 23, 35, METATILE_BikeShop_Barrier_Hidden_Bottom, 1
	setmetatile 23, 36, METATILE_BikeShop_Floor_Shadow_Top, 0
	setmetatile 23, 37, METATILE_BikeShop_Wall_Edge_Top, 0
	setmetatile 10, 16, METATILE_BikeShop_Barrier_Hidden_Top, 1
	setmetatile 10, 17, METATILE_BikeShop_Barrier_Hidden_Bottom, 1
	setmetatile 10, 18, METATILE_BikeShop_Floor_Shadow_Top, 0
	setmetatile 10, 19, METATILE_BikeShop_Wall_Edge_Top, 0
	setmetatile 10, 0, METATILE_BikeShop_Barrier_Hidden_Top, 1
	setmetatile 10, 1, METATILE_BikeShop_Barrier_Hidden_Bottom, 1
	setmetatile 10, 2, METATILE_BikeShop_Floor_Shadow_Top, 0
	setmetatile 10, 3, METATILE_BikeShop_Wall_Edge_Top, 0
	setmetatile 37, 33, METATILE_BikeShop_Barrier_Green_Top, 1
	setmetatile 37, 34, METATILE_BikeShop_Barrier_Green_TopMid, 1
	setmetatile 37, 35, METATILE_BikeShop_Barrier_Green_BottomMid, 1
	setmetatile 37, 36, METATILE_BikeShop_Barrier_Green_Bottom, 1
	setmetatile 28, 22, METATILE_BikeShop_Barrier_Green_Top, 1
	setmetatile 28, 23, METATILE_BikeShop_Barrier_Green_TopMid, 1
	setmetatile 28, 24, METATILE_BikeShop_Barrier_Green_BottomMid, 1
	setmetatile 28, 25, METATILE_BikeShop_Barrier_Green_Bottom, 1
	setmetatile 10, 24, METATILE_BikeShop_Barrier_Green_Top, 1
	setmetatile 10, 25, METATILE_BikeShop_Barrier_Green_TopMid, 1
	setmetatile 10, 26, METATILE_BikeShop_Barrier_Green_BottomMid, 1
	setmetatile 10, 27, METATILE_BikeShop_Barrier_Green_Bottom, 1
	setmetatile 21, 2, METATILE_BikeShop_Barrier_Green_Top, 1
	setmetatile 21, 3, METATILE_BikeShop_Barrier_Green_TopMid, 1
	setmetatile 21, 4, METATILE_BikeShop_Barrier_Green_BottomMid, 1
	setmetatile 21, 5, METATILE_BikeShop_Barrier_Green_Bottom, 1
	setmetatile 6, 11, METATILE_BikeShop_Button_Pressed, 0
	setmetatile 13, 10, METATILE_BikeShop_Button_Pressed, 0
	setmetatile 16, 22, METATILE_BikeShop_Button_Pressed, 0
	setmetatile 4, 26, METATILE_BikeShop_Button_Pressed, 0
	setmetatile 30, 38, METATILE_BikeShop_Button_Pressed, 0
	setmetatile 2, 11, METATILE_BikeShop_Button_Green, 0
	setmetatile 17, 10, METATILE_BikeShop_Button_Green, 0
	setmetatile 25, 18, METATILE_BikeShop_Button_Green, 0
	setmetatile 18, 36, METATILE_BikeShop_Button_Green, 0
	return

NewMauville_Inside_EventScript_2375D7:: @ 82375D7
	setmetatile 23, 34, METATILE_BikeShop_Barrier_Blue_Top, 1
	setmetatile 23, 35, METATILE_BikeShop_Barrier_Blue_TopMid, 1
	setmetatile 23, 36, METATILE_BikeShop_Barrier_Blue_BottomMid, 1
	setmetatile 23, 37, METATILE_BikeShop_Barrier_Blue_Bottom, 1
	setmetatile 10, 16, METATILE_BikeShop_Barrier_Blue_Top, 1
	setmetatile 10, 17, METATILE_BikeShop_Barrier_Blue_TopMid, 1
	setmetatile 10, 18, METATILE_BikeShop_Barrier_Blue_BottomMid, 1
	setmetatile 10, 19, METATILE_BikeShop_Barrier_Blue_Bottom, 1
	setmetatile 10, 0, METATILE_BikeShop_Barrier_Blue_Top, 1
	setmetatile 10, 1, METATILE_BikeShop_Barrier_Blue_TopMid, 1
	setmetatile 10, 2, METATILE_BikeShop_Barrier_Blue_BottomMid, 1
	setmetatile 10, 3, METATILE_BikeShop_Barrier_Blue_Bottom, 1
	setmetatile 37, 33, METATILE_BikeShop_Barrier_Hidden_Top, 1
	setmetatile 37, 34, METATILE_BikeShop_Barrier_Hidden_Bottom, 1
	setmetatile 37, 35, METATILE_BikeShop_Floor_Shadow_Top, 0
	setmetatile 37, 36, METATILE_BikeShop_Wall_Edge_Top, 0
	setmetatile 28, 22, METATILE_BikeShop_Barrier_Hidden_Top, 1
	setmetatile 28, 23, METATILE_BikeShop_Barrier_Hidden_Bottom, 1
	setmetatile 28, 24, METATILE_BikeShop_Floor_Shadow_Top, 0
	setmetatile 28, 25, METATILE_BikeShop_Wall_Edge_Top, 0
	setmetatile 10, 24, METATILE_BikeShop_Barrier_Hidden_Top, 1
	setmetatile 10, 25, METATILE_BikeShop_Barrier_Hidden_Bottom, 1
	setmetatile 10, 26, METATILE_BikeShop_Floor_Shadow_Top, 0
	setmetatile 10, 27, METATILE_BikeShop_Wall_Edge_Top, 0
	setmetatile 21, 2, METATILE_BikeShop_Barrier_Hidden_Top, 1
	setmetatile 21, 3, METATILE_BikeShop_Barrier_Hidden_Bottom, 1
	setmetatile 21, 4, METATILE_BikeShop_Floor_Shadow_Top, 0
	setmetatile 21, 5, METATILE_BikeShop_Wall_Edge_Top, 0
	setmetatile 2, 11, METATILE_BikeShop_Button_Pressed, 0
	setmetatile 17, 10, METATILE_BikeShop_Button_Pressed, 0
	setmetatile 25, 18, METATILE_BikeShop_Button_Pressed, 0
	setmetatile 18, 36, METATILE_BikeShop_Button_Pressed, 0
	setmetatile 6, 11, METATILE_BikeShop_Button_Blue, 0
	setmetatile 13, 10, METATILE_BikeShop_Button_Blue, 0
	setmetatile 16, 22, METATILE_BikeShop_Button_Blue, 0
	setmetatile 4, 26, METATILE_BikeShop_Button_Blue, 0
	setmetatile 30, 38, METATILE_BikeShop_Button_Blue, 0
	return

NewMauville_Inside_EventScript_237725:: @ 8237725
	lockall
	msgbox NewMauville_Inside_Text_237932, MSGBOX_DEFAULT
	call NewMauville_Inside_EventScript_23773A
	setvar VAR_NEW_MAUVILLE_STATE, 2
	releaseall
	end

NewMauville_Inside_EventScript_23773A:: @ 823773A
	setmetatile 33, 6, METATILE_BikeShop_Button_Pressed, 0
	setmetatile 32, 2, METATILE_BikeShop_Generator_Off_Tile0, 1
	setmetatile 33, 2, METATILE_BikeShop_Generator_Off_Tile1, 1
	setmetatile 34, 2, METATILE_BikeShop_Generator_Off_Tile2, 1
	setmetatile 35, 2, METATILE_BikeShop_Generator_Off_Tile3, 1
	setmetatile 32, 3, METATILE_BikeShop_Generator_Off_Tile4, 1
	setmetatile 33, 3, METATILE_BikeShop_Generator_Off_Tile5, 1
	setmetatile 34, 3, METATILE_BikeShop_Generator_Off_Tile6, 1
	setmetatile 35, 3, METATILE_BikeShop_Generator_Off_Tile7, 1
	special DrawWholeMapView
	return

NewMauville_Inside_EventScript_23778F:: @ 823778F
	lockall
	compare VAR_NEW_MAUVILLE_STATE, 2
	goto_if_eq NewMauville_Inside_EventScript_2377A5
	msgbox NewMauville_Inside_Text_237896, MSGBOX_DEFAULT
	releaseall
	end

NewMauville_Inside_EventScript_2377A5:: @ 82377A5
	msgbox NewMauville_Inside_Text_237916, MSGBOX_DEFAULT
	releaseall
	end

NewMauville_Inside_EventScript_2377AF:: @ 82377AF
	lock
	faceplayer
	setwildbattle SPECIES_SCRAGGY, 25, ITEM_NONE
	waitse
	playmoncry SPECIES_SCRAGGY, 2
	delay 40
	waitmoncry
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq NewMauville_Inside_EventScript_2377F3
	compare VAR_RESULT, B_OUTCOME_RAN
	goto_if_eq NewMauville_Inside_EventScript_2377F3
	compare VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED
	goto_if_eq NewMauville_Inside_EventScript_2377F3
	setflag FLAG_DEFEATED_SCRAGGY_1_NEW_MAUVILLE
	release
	end

NewMauville_Inside_EventScript_2377F3:: @ 82377F3
	setflag FLAG_DEFEATED_SCRAGGY_1_NEW_MAUVILLE
	goto Common_EventScript_RemoveStaticPokemon
	end

NewMauville_Inside_EventScript_2377FC:: @ 82377FC
	lock
	faceplayer
	setwildbattle SPECIES_SCRAGGY, 25, ITEM_NONE
	waitse
	playmoncry SPECIES_SCRAGGY, 2
	delay 40
	waitmoncry
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq NewMauville_Inside_EventScript_237840
	compare VAR_RESULT, B_OUTCOME_RAN
	goto_if_eq NewMauville_Inside_EventScript_237840
	compare VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED
	goto_if_eq NewMauville_Inside_EventScript_237840
	setflag FLAG_DEFEATED_SCRAGGY_2_NEW_MAUVILLE
	release
	end

NewMauville_Inside_EventScript_237840:: @ 8237840
	setflag FLAG_DEFEATED_SCRAGGY_2_NEW_MAUVILLE
	goto Common_EventScript_RemoveStaticPokemon
	end

NewMauville_Inside_EventScript_237849:: @ 8237849
	lock
	faceplayer
	setwildbattle SPECIES_SCRAGGY, 25, ITEM_NONE
	waitse
	playmoncry SPECIES_SCRAGGY, 2
	delay 40
	waitmoncry
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq NewMauville_Inside_EventScript_23788D
	compare VAR_RESULT, B_OUTCOME_RAN
	goto_if_eq NewMauville_Inside_EventScript_23788D
	compare VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED
	goto_if_eq NewMauville_Inside_EventScript_23788D
	setflag FLAG_DEFEATED_SCRAGGY_3_NEW_MAUVILLE
	release
	end

NewMauville_Inside_EventScript_23788D:: @ 823788D
	setflag FLAG_DEFEATED_SCRAGGY_3_NEW_MAUVILLE
	goto Common_EventScript_RemoveStaticPokemon
	end

NewMauville_Inside_Text_237896: @ 8237896
	.string "The generator is radiating heat that\n"
	.string "can be felt even at a distance.\p"
	.string "It looks like it should be turned off\n"
	.string "as soon as possible.$"

NewMauville_Inside_Text_237916: @ 8237916
	.string "The generator quieted down.$"

NewMauville_Inside_Text_237932: @ 8237932
	.string "{PLAYER} stepped on the switch.\p"
	.string "Click…\p"
	.string "… … … … … … … …\n"
	.string "… … … … … … … …\p"
	.string "The generator appears to have\n"
	.string "stopped…$"
