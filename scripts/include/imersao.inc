/* By EvilLink
Biblioteca para imersão com Sons e/ou Emotes
Exemplo de uso: Imersao(who, "Gritar", 1, 0, 0) - Grita; sai som; não sai emote; não sai animação relacionada
Exemplo2 de uso: Imersao(who, "Gritar") - Grita; sai som; sai emote; sai animação relacionada
who = alvo (player/item)
"Gritar" = Emote/Som a ser emitido
1 = EMITE som
0 = NÃO EMITE emote (se tiver)
*/

use uo;
use os;

include "include/say";

//REFERÊNCIAS
//HUMANOIDE
const EL_BOW_ANIM := 0x20;

const EL_GRITAR_SOM_MALE := 0x441;
const EL_GRITAR_SOM_FEMALE := 0x32F;
const EL_GRITAR_EMOTE := "*Gritando*";

const EL_GRITARB_SOM_MALE := 0x44B;
const EL_GRITARB_SOM_FEMALE := 0x339;
const EL_GRITARB_EMOTE := EL_GRITAR_EMOTE;

const EL_HUH_SOM_MALE := 0x430;
const EL_HUH_SOM_FEMALE := 0x320;
const EL_HUH_EMOTE := "*Huh?*";
const EL_HUH_ANIM := 0x05; //olhar para os lados

const EL_TOSSIRA_SOM_MALE := 0x421;
const EL_TOSSIRA_SOM_FEMALE := 0x312;
const EL_TOSSIRB_SOM_MALE := 0x422;
const EL_TOSSIRB_SOM_FEMALE := 0x313;
const EL_TOSSIR_EMOTE := "*Tossindo*";

const EL_ARFAR_SOM_MALE := 0x42A;
const EL_ARFAR_SOM_FEMALE := 0x31A;
const EL_ARFAR_EMOTE := "*Arfando*";

const EL_GEMER_SOM_MALE := 0x42C;
const EL_GEMER_SOM_FEMALE := 0x31C;
const EL_GEMER_EMOTE := "*Gemendo*";

const EL_CAIR_SOM_MALE := 0x42C;
const EL_CAIR_SOM_FEMALE := 0x31C;
const EL_CAIR_EMOTE := "*Cai*";
const EL_CAIR_ANIM := 0x15;
const EL_CAIR_ANIMB := 0x16;

const EL_GOLPEAR_SOM_MALE := EL_GRITARB_SOM_MALE;
const EL_GOLPEAR_SOM_FEMALE := EL_GRITARB_SOM_FEMALE;
const EL_GOLPEAR_EMOTE := "*Golpeando*";
const EL_GOLPEAR_ANIM := 0x09;

const EL_SUSTO_SOM_MALE := 0x434;
const EL_SUSTO_SOM_FEMALE := 0x324;
const EL_SUSTO_EMOTE := "*Oh*";
const EL_SUSTO_ANIM := 0x14;

const EL_VOMITAR_SOM_MALE := 0;
const EL_VOMITAR_SOM_FEMALE := 0;
const EL_VOMITAR_EMOTE := "*Vomita*";
const EL_VOMITAR_ANIM := EL_BOW_ANIM;

//CRAFT
const EL_METAL_SOM := 0x002b;
const EL_MADEIRA_SOM := 0x23e;
const EL_FLECHA_SOM := 0x5a;
const EL_TESOURA_SOM := 0x249;
const EL_CRAFT_MW_SOM := EL_METAL_SOM;
const EL_CRAFT_MW_ANIM := 0x0b;
const EL_CRAFT_WW_SOM := EL_MADEIRA_SOM;
const EL_CRAFT_BC_SOM := EL_FLECHA_SOM;
const EL_CRAFT_DW_SOM := EL_TESOURA_SOM;

//OBJETOS
const EL_VIDRO_SOM := 0x03F;
const EL_VIDRO_EMOTE := "*Quebrou*";

//alchemy 0x243


/////INÍCIO IMERSÃO/////
function Imersao(byref who, tipoemote, saisom:=1, saiemote:=1, saianim:=1, saiefeito:=1, byref user:=0)
	var whosound, whoemote, whoanim, whoefeito, noexist;
	tipoemote := Lower(tipoemote);
	
	case (tipoemote)
		//HUMANOIDE
		"gritar":
			whoemote := EL_GRITAR_EMOTE;
			case (who.graphic)
				400:
					whosound := EL_GRITAR_SOM_MALE;
				401:
					whosound := EL_GRITAR_SOM_FEMALE;
			endcase
			break;

		"huh":
			whoemote := EL_HUH_EMOTE;
			whoanim := EL_HUH_ANIM;
			case (who.graphic)
				400:
					whosound := EL_HUH_SOM_MALE;
				401:
					whosound := EL_HUH_SOM_FEMALE;
			endcase
			break;

		"tossir1":
			whoemote := EL_TOSSIR_EMOTE;
			case (who.graphic)
				400:
					whosound := EL_TOSSIRA_SOM_MALE;
				401:
					whosound := EL_TOSSIRA_SOM_FEMALE;
			endcase
			break;

		"tossir2":
			whoemote := EL_TOSSIR_EMOTE;
			case (who.graphic)
				400:
					whosound := EL_TOSSIRB_SOM_MALE;
				401:
					whosound := EL_TOSSIRB_SOM_FEMALE;
			endcase
			break;

		"arfar":
			whoemote := EL_ARFAR_EMOTE;
			case (who.graphic)
				400:
					whosound := EL_ARFAR_SOM_MALE;
				401:
					whosound := EL_ARFAR_SOM_FEMALE;
			endcase
			break;

		"gemer":
			whoemote := EL_GEMER_EMOTE;
			case (who.graphic)
				400:
					whosound := EL_GEMER_SOM_MALE;
				401:
					whosound := EL_GEMER_SOM_FEMALE;
			endcase
			break;
		
		"cair":
			whoemote := EL_CAIR_EMOTE;
			whoanim := EL_CAIR_ANIM;
			case (who.graphic)
				400:
					//whosound := EL_CAIR_SOM_MALE;
				401:
					//whosound := EL_CAIR_SOM_FEMALE;
			endcase
			break;

		"cair2":
			whoemote := EL_CAIR_EMOTE;
			whoanim := EL_CAIR_ANIMB;
			case (who.graphic)
				400:
					//whosound := EL_CAIR_SOM_MALE;
				401:
					//whosound := EL_CAIR_SOM_FEMALE;
			endcase
			break;

		"golpear":
			whoemote := EL_GOLPEAR_EMOTE;
			whoanim := EL_GOLPEAR_ANIM;
			case (who.graphic)
				400:
					whosound := EL_GOLPEAR_SOM_MALE;
				401:
					whosound := EL_GOLPEAR_SOM_FEMALE;
			endcase
			break;
		
		"susto":
			whoemote := EL_SUSTO_EMOTE;
			whoanim := EL_SUSTO_ANIM;
			case (who.graphic)
				400:
					whosound := EL_SUSTO_SOM_MALE;
				401:
					whosound := EL_SUSTO_SOM_FEMALE;
			endcase
			break;
		
		"vomitar":
			break;
		
		//PROFISSÕES
		"mw":
			//whoemote := ;
			whoanim := EL_CRAFT_MW_ANIM;
			whosound := EL_CRAFT_MW_SOM;
			break;

		"ww":
			//whoemote := ;
			//whoanim := EL_CRAFT_WW_ANIM;
			whosound := EL_CRAFT_WW_SOM;
			break;

		"dw":
			//whoemote := ;
			//whoanim := EL_CRAFT_DW_ANIM;
			whosound := EL_CRAFT_DW_SOM;
			break;

		//OBJETOS
		"explodir":
			break;
		
		"quebrar":
			break;
		
		"metal":
			whosound := EL_METAL_SOM;
			break;

		"vidro":
			whoemote := EL_VIDRO_EMOTE;
			whosound := EL_VIDRO_SOM;
			whoefeito := 1;
			break;

		default: noexist := 1;
	endcase

	if (noexist)
		SendSysMessageEx(user, "Acao inexistente no banco de dados.", SSM_FAIL);
		return;
	endif

	if (saisom == 1)
		if (whosound) PlaySoundEffect(who, whosound);
		elseif (user.cmdlevel > 1) SendSysMessageEx(user, "GM: Imersao sem SOM!", SSM_FAIL);
		endif
	endif

	if (saiemote == 1)
		if (whoemote) PrintText(who, whoemote);
		elseif (user.cmdlevel > 1) SendSysMessageEx(user, "GM: Imersao sem EMOTE!", SSM_FAIL);
		endif
	endif

	if (saianim == 1)
		if (whoanim) PerformAction(who, whoanim);
		elseif (user.cmdlevel > 1) SendSysMessageEx(user, "GM: Imersao sem ANIMACAO!", SSM_FAIL);
		endif
	endif

	if (saiefeito == 1)
		if (whoefeito)
			case (tipoemote)
				"vomitar":
					//vômito no pé do who
					break;
				
				"explodir":
					//efeito de explosão
					break;
				
				"vidro":
					sleep(1);
					DestroyItem(who);
					break;
			endcase
		elseif (user.cmdlevel > 1) SendSysMessageEx(user, "GM: Imersao sem EFEITO!", SSM_FAIL);
		endif
	endif
endfunction