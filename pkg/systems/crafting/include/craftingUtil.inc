use cfgfile;

include "include/damage";
include ":tn:tngumps";

const  EXCEP := 1;
const  NORMAL := 2;
const  POOR := 3;
const STR_ERRORCHANCE := "ERROR 666";
const STR_NULLCHANCE := "nula";
const STR_VERYLOWCHANCE := "muito baixa";
const STR_LOWCHANCE := "baixa";
const STR_INTERMEDIATECHANCE := "media";
const STR_GOODCHANCE := "alta";
const STR_VERYHIGHCHANCE := "muito alta";

//funcao que pergunta por fechadura, caso o item seja lockable
function CraftLockable(who, theitem)
		if (theitem.isDoor())
			SetObjProperty(theitem, "pedreiro", who.serial);
			SetObjProperty(theitem, "criador", who.acctname);
			SetObjProperty(theitem, "validade", CInt(ReadGameClock()+360));
			MoveObjectToLocation(theitem, who.x, who.y, who.z, who.realm, MOVEOBJECT_NORMAL);
			theitem.movable := 0;
		endif

		if (KP_IsLockable(theitem ))
			var fechadura := YesNo(who, "Voce deseja por uma fechadura nesse item?");
			if (fechadura)
				SendSysMessageEx(who, "Escolha a fechadura para por neste item.", SSM_REQUEST);
				var targ := Target(who);
				if (targ)
					if (targ.objtype == 4001)
						if (!theitem.isDoor())
							var lvl := Cint(GetObjProperty(targ, "level"));
							if (!lvl)
								lvl := 1;
							endif
							SetObjProperty(theitem, "level", lvl);
						endif
						var lockid := CInt(GetObjProperty(targ, "LockId"));
						SetObjProperty(theitem, "LockId", lockid);
						DestroyItem(targ);
						SendSysMessageEx(who, "Voce instalou a fechadura com sucesso.", SSM_INFO);
					else
						SendSysMessageEx(who, "Isto nao parece uma fechadura.", SSM_FAIL);
					endif
				endif
			endif
		endif
endfunction

function GetMaterialName(obj);

  if ( (obj == "wood") || (obj == "leather") || (obj == "cloth") || (obj == "metal") || (obj == "glass") || (obj == "ossos") || (obj == "stone") || obj == "arrowhead")
    return obj;
  else
    var items := ReadconfigFile("::itemdesc");
    if (items[obj])
      return items[obj].desc;
    endif
  endif


endfunction

//Reference: http://uo.stratics.com/content/aos/baseproperties.shtml#exceptional
// as stratics says, exceptional weapons add +35 dmg increase

function AddQualityDamageMod(who, craft_skill, byref theitem, quality )
	if (quality >= 1.2)
		var randomDmg;
		var maxBonus := CInt(quality*20); //mínimo 24

		//adiciona 5% a 20%
		var i := 0;
		var cfg:=ReadConfigFile(":combat:itemdesc");
		var elem := FindConfigElem(cfg, theitem.objtype);
		var qtd := 5;
		while(i < maxBonus)
			if(qtd < maxBonus)
				qtd := maxBonus;
			endif
			randomDmg := RandomInt(5) + 1;
			case(randomDmg)
				1: theitem.damage_physical_mod := theitem.damage_physical_mod + qtd; break;
				2: theitem.damage_fire_mod     := theitem.damage_fire_mod + qtd; break;
				3: theitem.damage_cold_mod     := theitem.damage_cold_mod + qtd; break;
				4: theitem.damage_energy_mod   := theitem.damage_energy_mod + qtd; break;
				5: theitem.damage_poison_mod   := theitem.damage_poison_mod + qtd; break;
			endcase
			maxBonus := maxBonus - qtd;
			sleepms(3);
		endwhile
		if(craft_skill == "MetalWorking")
			if(TemHabilidade(who,"Armas Velozes"))
				//SendSysMessage(who,"bonus velocidade" + (quality-1)/2 + "qualidade: "+ quality);
				SetObjProperty(theitem,"attackspeedbonus", CInt(elem.Speed * (0.1 + (quality-1)/4)));
				//theitem.speed_mod := CInt(elem.Speed * (0.1 + (quality-1)/4));
			endif
			//Acplica dano extra pra arma
			if(TemHabilidade(who,"Amolador de Laminas") && (elem.TipoAtaque == "Cortante"))
				//SendSysMessage(who,"bonus dano" + theitem.quality-1);
				theitem.dmg_mod := CInt(elem.MaxDam * (0.1 + (quality-1)/4));
			endif
			if(TemHabilidade(who,"Ponta Temperada") && (elem.TipoAtaque == "Perfurante"))
				theitem.dmg_mod := CInt(elem.MaxDam * (0.1 + (quality-1)/4));
			endif
			if(TemHabilidade(who,"Densidade Esmagadora") && (elem.TipoAtaque == "Contusivo"))
				theitem.dmg_mod := CInt(elem.MaxDam * (0.1 + (quality-1)/4));
			endif
		elseif(craft_skill == "WoodWorking")
			if(TemHabilidade(who,"Entalhe para Combate"))
				theitem.speed_mod := CInt(elem.Speed * (0.1 + (quality-1)/4));
			endif
			if(TemHabilidade(who,"Flexao da Madeira")) //&& (Cint(elem.maxrange) > 2))
				theitem.dmg_mod := CInt(elem.MaxDam * (0.1 + (quality-1)/4));
			endif
		endif
	endif
	return;
endfunction

function AddQualityResistMod(who, craft_skill, byref theitem, quality)
	var i;
	if (quality >= 1.2)
		var randomDmg;
		var maxBonus := CInt(quality);
		//SendSysMessage(who,"Adicionando resistencia do excepcional");

		//Soma um bonus em todas as resistencias que o item já dá
		for (i := 1; i <= maxBonus; i := i + 1)
			if (theitem.resist_physical_mod)
				theitem.resist_physical_mod := theitem.resist_physical_mod +1; break;
			endif
			if (theitem.resist_fire_mod)
				theitem.resist_fire_mod := theitem.resist_fire_mod +1; break;
			endif
			if (theitem.resist_cold_mod)
				theitem.resist_cold_mod := theitem.resist_cold_mod +1; break;
			endif
			if (theitem.resist_energy_mod)
				theitem.resist_energy_mod := theitem.resist_energy_mod +1; break;
			endif
			if (theitem.resist_poison_mod)
				theitem.resist_poison_mod := theitem.resist_poison_mod +1; break;
			endif
		endfor
	else
		return;
	endif
endfunction

 function AddItemDescription(who, item)
	var repeating := 1;
	var str;
	SendSysMessage(who, "Utilize apenas 3 linhas do gump.");
	while (repeating)
		str := SmallRequestGump(who, "Descreva o item", 1);
		if (len(str) < 84)
			break;
		endif
		SendSysMessage(who, "Voce excedeu o numero maximo de caracteres! Utilize apenas 3 linhas do gump");
	endwhile
	SetObjProperty(item, "description", str);
endfunction

function GetChanceString(value)
	if (TypeOf(value) == "String")
		return STR_ERRORCHANCE;
	elseif (value == 0)
		return STR_NULLCHANCE;
	elseif (value <= 20)
		return STR_VERYLOWCHANCE;
	elseif (value <= 40)
		return STR_LOWCHANCE;
	elseif (value <= 60)
		return STR_INTERMEDIATECHANCE;
	elseif (value <= 80)
		return STR_GOODCHANCE;
	elseif (value > 80)
		return STR_VERYHIGHCHANCE;
	endif
endfunction
