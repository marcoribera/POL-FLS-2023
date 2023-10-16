include ":timedScripts:timedScripts";
include ":tn:cooldown";
include "include/say";
include ":fls_core:fls_characters";
include ":charactercreation:resists";
use cfgfile;


CONST DRINK_SOUND := 0x32;

function checkifcandrink(character, type)
  // Check to make sure they have at least one hand free to drink the potion
  var equippedright := GetEquipmentByLayer(character, 0x01);
  var equippedleft := GetEquipmentByLayer(character, 0x02);
  var cfg := ReadConfigFile(":*:itemdesc");
  var twohanded := Cint(cfg[equippedleft.objtype].TwoHanded);
  if (equippedright and equippedleft || twohanded)
    SendSysMessage(character, "Voce precisa de pelo menos uma mao livre!");
    return 0;
  endif
  if((type != "red") and (type != "green_potion"))
    if(GetCooldown(character, type))
        SendSysMessage(character, "Voce deve esperar um pouco antes de beber outra pocao!");
        return 0;
     else
        SetCooldown(character, type, 10);
        return 1;
     endif
  else
    return 1;
  endif
endfunction


function empty_bottle(character, potion, potiontype := 0)

  if(GetObjProperty(potion, "acabou") == 1)
	var pot2 := SubtractAmount( potion, 1 );
	var stacknow := GetAmount(0x0F0E);
		if (stacknow > 0)
			Addamount(0x0F0E, 1);
		else
			var pot := CreateItemInBackpack(character, 0x0F0E, 1);
		endif
	return 1;
	endif

  PlaySoundEffect(character, DRINK_SOUND);
  PrintText(character, "*usa uma pocao*");
  var goles;

	if (!GetObjProperty(potion, "goles"))
		goles := 3;
		SetObjProperty(potion, "goles", goles);
	else
		goles := cint(GetObjProperty(potion, "goles"));
	endif

	if(potiontype == 1)  //eh uma poção de 1 so gole
		goles := 0;
	endif

	if (goles > 1)
		goles := goles - 1;
		SetObjProperty(potion, "goles", goles);
	else
		SetObjProperty(potion, "acabou", 1);
		SetObjProperty(potion, "goles", 0);
	endif

endfunction

//essa funcao so se mantem pra checar os kindlings. se nao quiser checar isso use .isReagent();
function isotherreagent(what)
	case(what.objtype)
		0xf7a:  return 1;
		0xf7b:  return 1;
		0xf84:  return 1;
		0xf85:  return 1;
		0xf86:  return 1;
		0xf88:  return 1;
		0xf8c:  return 1;
		0xf8d:  return 1;
		0xef1a: return 1;
		0xef1b: return 1;
		0xef1c: return 1;
		0xef1d: return 1;
		0xf7d: return 1;
		0xef1e: return 1;
		0xf87: return 1;
		0xf79: return 1;
		0xf91: return 1;
		0xf89: return 1;
		0xf82: return 1;
		0xF81: return 1;
		0xF78: return 1;
		0xF8F: return 1;
		0xF90: return 1;

		0xee25: return 1;
		0xee26: return 1;
		0xee27: return 1;
		0xee28: return 1;
		0xfc5:  return 1;
		0x0dea: return 1;

		0x1F91: return 1;
	endcase
	return 0;
endfunction

function GetReagName(objtype)

  if (objtype ==  0xf7a)
    return "perola negra";
  elseif (objtype == 0xF78 )
   return "asa de morcego";
  elseif (objtype == 0xf79 )
   return "pedra negra";
  elseif (objtype == 0xf7b )
    return "musgo vermelho";
  elseif (objtype == 0xf7c )
    return "cria do sangue";
  elseif (objtype == 0xF7D)
   return "sangue fresco";
  elseif (objtype == 0xF7E)
   return "ossos";
  elseif (objtype == 0xF7F)
   return "enxofre";
  elseif (objtype == 0xF80)
   return "ossos demoniacos";
  elseif (objtype == 0xF81 )
   return "terra fertil";
  elseif (objtype == 0xf82 )
   return "sangue de dragao";
  elseif (objtype == 0xf83 )
   return "cogumelo negro";
  elseif (objtype == 0xf84)
    return "alho";
  elseif (objtype == 0xf85)
    return "ginseng";
  elseif ( objtype ==  0xf86)
    return "raiz de mandragora";
  elseif (objtype == 0xf87 )
   return "olho da salamandra";
  elseif ( objtype == 0xf88)
    return "solanaceae";
  elseif (objtype == 0xf89 )
   return "obsidiana";
  elseif ( objtype == 0xf8c)
    return "cinzas de enxofre";
  elseif (objtype == 0xf8d)
    return "teia";
  elseif (objtype == 0xf8a)
    return "gusa";
  elseif (objtype == 0xf8b)
    return "pedra pomes";
  elseif (objtype == 0xf8e)
    return "escamas de cobra";
  elseif (objtype == 0xf8f)
    return "cinzas vulcanicas";
  elseif (objtype == 0xF90 )
   return "madeira morta";
  elseif (objtype == 0xf91 )
   return "coracao do verme";

  elseif ( objtype == 0xef1a)
   return "glandula de wyvern";
  elseif (objtype == 0xef1b)
   return "glandula de escorpiao";
  elseif (objtype == 0xef1c)
   return "glandula de aranha";
  elseif (objtype == 0xef1d)
   return "glandula de cobra";
  elseif (objtype == 0xF8F)
   return "po de tumulo";
  elseif (objtype == 0xee27 )
   return "cascas vermelhas";
  elseif (objtype == 0xee28 )
   return "cascas verdes";
  elseif (objtype == 0xee26 )
   return "cascas marrom";
  elseif (objtype == 0xee25 )
   return "cascas amarelas";
  elseif (objtype == 0xfc5 )
   return "conchas";
  elseif (objtype == 0x0dea )
   return "cinzas";
  elseif (objtype == 0x1F91 )
   return "copo de agua";

  endif
endfunction


function is_poison(potion)
  var poison_level := GetObjProperty(potion, "poison_level");
  return poison_level;
endfunction

function do_poison(who, potion)
  var level, difficulty, points, poisonType;
  level := Cint(GetObjProperty(potion, "level"));
  if (!level)
    level := RandomDiceRoll("1d5");
  endif
  //se for uma poçao que nao a default a formula eh essa:
  difficulty := 15*level + 10;
  points := difficulty;
  case(potion.objtype)
    0xbf00: level := 1; difficulty := 40; points := 50; poisonType := "defaultPoison";
    0xbf01: poisonType :="strPoison"; difficulty := 60; points := 70;
    0xbf07: poisonType :="dexPoison"; difficulty := 60; points := 70;
    0xbf06: poisonType :="intPoison"; difficulty := 60; points := 70;
    0xbf02: poisonType:="staminaPoison"; difficulty := 60; points := 70;
    0xbf03: poisonType:="paralyzePoison"; difficulty := 80; points := 100;
    0xef54: poisonType :="manaPoison"; difficulty := 40; points := 70;
    0xbf04: level := 3; difficulty := 80; points := 60; poisonType := "defaultPoison";
    0xdc04: level := 2; difficulty := 60; points := 40; poisonType := "defaultPoison";
    0xbf05: level := 4; difficulty := 100; points := 100; poisonType := "defaultPoison";
    default: difficulty := 0; points := 0; poisonType := "invalid";
  endcase
  PlaySoundEffect(who, 0x248);
    SendSysMessageEx(who, "Voce aplicou o veneno com sucesso.", SSM_INFO);
    var poisonInfo := struct;
    poisonInfo.+name := poisonType;
    poisonInfo.+level := level;
    poisonInfo.+dosage := 20 - (level*2);
    poisonInfo.+acc := who.acctname;
    poisonInfo.+time := 40 + level*10;
    if (temHabilidade(who, "Veneno Puro"))
      poisonInfo.dosage := CInt(poisonInfo.dosage * 1.5);
      poisonInfo.time := CInt(poisonInfo.time * 1.2);
    endif

    if (CheckResist(who, FORTITUDE, 15,-20*poisonInfo.level))
      SendSysMessageEx(who, "Voce resistiu ao veneno.", SSM_INFO);
    else
      TS_StartTimer(who, poisonInfo.name, poisonInfo.time, poisonInfo.level, who);
    endif
endfunction
