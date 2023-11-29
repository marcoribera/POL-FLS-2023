/* By EvilLink
Biblioteca para imersão com Sons e/ou Emotes
Exemplo de uso: EmoteSound(who, "Gritar", 1, 0, 0) - Grita; sai som; não sai emote; não sai animação relacionada
Exemplo2 de uso: EmoteSound(who, "Gritar") - Grita; sai som; sai emote; sai animação relacionada
who = alvo (player/item)
"Gritar" = Emote/Som a ser emitido
1 = EMITE som
0 = NÃO EMITE emote (se tiver)
*/

use uo;

include "include/say";

//REFERÊNCIAS
const EL_GRITAR_SOM_MALE := 0x441;
const EL_GRITAR_SOM_FEMALE := 0x32F;
const EL_GRITAR_EMOTE := "*Gritando*";

const EL_GRITARB_SOM_MALE := 0x44B;
const EL_GRITARB_SOM_FEMALE := 0x339;
const EL_GRITARB_EMOTE := EL_GRITAR_EMOTE;

const EL_HUH_SOM_MALE := 0x430;
const EL_HUH_SOM_FEMALE := 0x320;
const EL_HUH_EMOTE := "*Huh?*";
//const EL_HUH_ANIM := ; //olhar para os lados

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


/////INÍCIO IMERSÃO/////
function EmoteSound(byref who, tipoemote, saisom:=1, saiemote:=0, saianim:=0, saiefeito:=0, byref user)
	var whosound, whoemote, whoanim;
	tipoemote := Lower(tipoemote);
	
	case (tipoemote) //Humanoide
		"gritar":
			whoemote := EL_GRITAR_EMOTE;
			case (who.graphic)
				400:
					whosound := EL_GRITAR_SOM_MALE[1];
				401:
					whosound := EL_GRITAR_SOM_FEMALE[2];
			endcase
			break;

		"huh":
			whoemote := EL_HUH_EMOTE;
			case (who.graphic)
				400:
					whosound := EL_HUH_SOM_MALE[1];
				401:
					whosound := EL_HUH_SOM_FEMALE[2];
			endcase
			break;

		"tossir1":
			whoemote := EL_TOSSIR_EMOTE;
			case (who.graphic)
				400:
					whosound := EL_TOSSIRA_SOM_MALE[1];
				401:
					whosound := EL_TOSSIRA_SOM_FEMALE[2];
			endcase
			break;

		"tossir2":
			whoemote := EL_TOSSIR_EMOTE;
			case (who.graphic)
				400:
					whosound := EL_TOSSIRB_SOM_MALE[1];
				401:
					whosound := EL_TOSSIRB_SOM_FEMALE[2];
			endcase
			break;

		"arfar":
			whoemote := EL_ARFAR_EMOTE;
			case (who.graphic)
				400:
					whosound := EL_ARFAR_SOM_MALE[1];
				401:
					whosound := EL_ARFAR_SOM_FEMALE[2];
			endcase
			break;

		"gemer":
			whoemote := EL_GEMER_EMOTE;
			case (who.graphic)
				400:
					whosound := EL_GEMER_SOM_MALE[1];
				401:
					whosound := EL_GEMER_SOM_FEMALE[2];
			endcase
			break;
		
		"cair":
			whoemote := EL_CAIR_EMOTE;
			whoanim := EL_CAIR_ANIM;
			case (who.graphic)
				400:
					//whosound := EL_CAIR_SOM_MALE[1];
				401:
					//whosound := EL_CAIR_SOM_FEMALE[2];
			endcase
			break;

		"cair2":
			whoemote := EL_CAIR_EMOTE;
			whoanim := EL_CAIR_ANIMB;
			case (who.graphic)
				400:
					//whosound := EL_CAIR_SOM_MALE[1];
				401:
					//whosound := EL_CAIR_SOM_FEMALE[2];
			endcase
			break;

		"golpear":
			whoemote := EL_GOLPEAR_EMOTE;
			whoanim := EL_GOLPEAR_ANIM;
			case (who.graphic)
				400:
					whosound := EL_GOLPEAR_SOM_MALE[1];
				401:
					whosound := EL_GOLPEAR_SOM_FEMALE[2];
			endcase
			break;
	endcase

	case (tipoemote) //Objetos
		"explodir":

		"quebrar":
	endcase

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
		if (whoanim) 
			case (tipoemote)
				"vomitar":
					//vômito no pé do targ
				
				"explodir":
					//efeito de explosão
			endcase
		elseif (user.cmdlevel > 1) SendSysMessageEx(user, "GM: Imersao sem EFEITO!", SSM_FAIL);
		endif
	endif
endfunction