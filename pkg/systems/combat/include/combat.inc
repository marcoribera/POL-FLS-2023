
use uo;
include ":brainai:npcUtil";
include ":combat:weaponInfo";

function DistanceChecks(attacker, defender)
	var cur_range := Distance(attacker, defender);
	var wpn_a_elem2 := GetWpnCfgInfo(attacker, attacker.weapon);
	if ( wpn_a_elem2.MaxRange == error )
		return 1;
	endif
	if ( cur_range > wpn_a_elem2.MaxRange )
		CombatDbgMsg(attacker, "Oponente esta muito longe.");
		return 0;
	elseif ( cur_range < wpn_a_elem2.MinRange )
		CombatDbgMsg(attacker, "Oponente esta muito perto.");
		return 0;
	else
		return 1;
	endif
endfunction

function GetWpnCfgInfo(mobile, weapon)

	var npc_cfg2	:= ReadConfigFile("::npcdesc");
	var item_cfg2	:= ReadConfigFile(":*:itemdesc");

	if ( mobile.IsA(POLCLASS_NPC) && weapon.objtype == 0xF020 )
		var npctemplate := mobile.npctemplate;
		npctemplate := npctemplate[10, len(npctemplate)-9];
		return npc_cfg2[npctemplate];
	else
		return item_cfg2[weapon.objtype];
	endif

endfunction
  
function PlayHitSounds(attacker, defender)
	var wpn_a_elem2 := GetWpnCfgInfo(attacker, attacker.weapon);
	var npc_cfg2	:= ReadConfigFile("::npcdesc");

	if ( wpn_a_elem2.HitSound )
		PlaySoundEffect(attacker, wpn_a_elem2.HitSound);
	else
		//NPC intrinsic weapon
		PlaySoundEffect(attacker, wpn_a_elem2.AttackHitSound);
	endif
	
	var damaged_sound;
	if ( defender.npctemplate )
		var npctemplate := defender.npctemplate;
		npctemplate := npctemplate[10, len(npctemplate)-9];
		damaged_sound := npc_cfg2[npctemplate].DamageSound;		
	else
		var sounds;
		if ( defender.gender == 0 )
			// Male
			sounds := array(341, 342, 343, 345, 346);
		else
			// Female
			sounds := array(332, 333, 334, 335, 336);
		endif
		damaged_sound := sounds[RandomInt(sounds.size())+1];
	endif
	
	PlaySoundEffect(defender, damaged_sound);
endfunction

function PlayMissSound(attacker)
	if ( wpn_a_elem.MissSound )
		PlaySoundEffect(attacker, wpn_a_elem.MissSound);
	else
		//NPC intrinsic weapon
		PlaySoundEffect(attacker, wpn_a_elem.AttackMissSound);
	endif
endfunction

function PlayAttackAnimation(attacker)
	var attack_anim := 0x0c; // Look around for npcs?
	var wpn_a_elem2 := GetWpnCfgInfo(attacker, attacker.weapon);
	if ( wpn_a_elem2.Anim )
		var anim_list := GetConfigStringArray(wpn_a_elem2, "Anim");
		attack_anim := anim_list[RandomInt(anim_list.size())+1];
	endif
	if ( attacker.graphic != 400 || attacker.graphic != 401)
		attack_anim := 0x0c;
	endif
	
	PerformAction(attacker, CInt(attack_anim));
	
	return attack_anim;
endfunction
  
function GetRawDmg(attacker)
  
    if (attacker.npctemplate)
      var npcelem := NPC_GetNPCConfig(attacker.npctemplate);
      var dmg := GetConfigString(npcelem, "AttackDamage");
      return RandomDiceRoll(dmg);
    else
      var dmg := CS_GetWeaponInfo(attacker.weapon, "Damage");
      return RandomDiceRoll(dmg);
    endif
  
endfunction
