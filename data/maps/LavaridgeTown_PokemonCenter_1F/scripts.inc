LavaridgeTown_PokemonCenter_1F_MapScripts:: @ 81FFAFA
	map_script MAP_SCRIPT_ON_TRANSITION, LavaridgeTown_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

LavaridgeTown_PokemonCenter_1F_OnTransition: @ 81FFB05
	setrespawn HEAL_LOCATION_LAVARIDGE_TOWN
	call Common_EventScript_UpdateBrineyLocation
	end

LavaridgeTown_PokemonCenter_1F_EventScript_1FFB0E:: @ 81FFB0E
	setvar VAR_0x800B, 1
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

LavaridgeTown_PokemonCenter_1F_EventScript_1FFB1C:: @ 81FFB1C
	msgbox LavaridgeTown_PokemonCenter_1F_Text_1FFBAD, MSGBOX_NPC
	end

LavaridgeTown_PokemonCenter_1F_EventScript_1FFB25:: @ 81FFB25
	msgbox LavaridgeTown_PokemonCenter_1F_Text_1FFB37, MSGBOX_NPC
	end

LavaridgeTown_PokemonCenter_1F_EventScript_1FFB2E:: @ 81FFB2E
	msgbox LavaridgeTown_PokemonCenter_1F_Text_1FFC21, MSGBOX_NPC
	end

LavaridgeTown_PokemonCenter_1F_Text_1FFB37: @ 81FFB37
	.string "I think POKéMON get closer to their\n"
	.string "TRAINERS if they spend time together.\p"
	.string "The longer the better.\n"
	.string "That's what I think.$"

LavaridgeTown_PokemonCenter_1F_Text_1FFBAD: @ 81FFBAD
	.string "It's sort of magical how just sitting\n"
	.string "in a hot-spring pool can invigorate.\p"
	.string "I wish I could let my POKéMON\n"
	.string "soak, too.$"

LavaridgeTown_PokemonCenter_1F_Text_1FFC21: @ 81FFC21
	.string "Hohoho! Hey, kid, you can reach\n"
	.string "the hot springs from here.\p"
	.string "If POKéMON are getting rest, so too\n"
	.string "should their TRAINERS.$"

