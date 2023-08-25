
function NivelHabilidade(habilidade, classe)

	var habcfg := ReadConfigFile(":charactercreation:config/habilidades");
	var elem := FindConfigElem( habcfg, habilidade );

	var nivel := GetConfigStringDictionary( elem, "classe" );

	return nivel[classe];

endfunction



function TemRequisito(who, habilidade, msg := 1)

	var habcfg := ReadConfigFile(":charactercreation:config/habilidades");
	var elem := FindConfigElem( habcfg, habilidade );

	var requisitos := GetConfigStringArray(elem, "requisito");

	foreach req in (requisitos)
		if (req["kit"]) // Ver se tem Kit!
			req["kit "] := "";
			if ((!GetObjProperty(who, "chardata")).kit in (req))
				if (msg == 1)
					SendSysMessageEx(who, "Voce nao possui o kit: " + req, SSM_FAIL);
				endif
				return 0;
			endif
		elseif ( !TemHabilidade(who, req) )
			if (msg == 1)
				SendSysMessageEx(who, "Voce nao possui o pre requisito: " + req, SSM_FAIL);
			endif
			return 0;
		endif

	endforeach

	return 1;


endfunction


function retornaRequisitos( habilidade)

	var habcfg := ReadConfigFile(":charactercreation:config/habilidades");
	var elem := FindConfigElem( habcfg, habilidade );

	var requisitos := GetConfigStringArray(elem, "requisito");

	return requisitos;

endfunction

function TemHabilidade(who, habilidade)

	var habs := GetObjProperty(who, "myhabs");

	foreach key in (habs.keys())
		if (habs[key] == habilidade)
			return 1;
		endif

	endforeach


	return 0;

endfunction

function IsBloodied(mobile)
	if (mobile.npctemplate)
		if (AP_GetVital(mobile, HITS) < CInt(AP_GetVitalMaximumValue(mobile, HITS)/2))
			return 1;
		endif
	elseif (AP_GetVital(mobile, HITS) < GetHP(mobile))
		return 1;
	endif
	return 0;
endfunction

function IsRaging(mobile)
	//Bonus da habilidde baixo limiar de furia
	var bonus_limiar_furia_hp := 0;
	if (TemHabilidade(mobile, "Baixo Limiar de Furia"))
		bonus_limiar_furia_hp := bonus_limiar_furia_hp + 100;
	endif

	if (!mobile.npctemplate && AP_GetVital(mobile, HITS) <= (GetHP(mobile) + bonus_limiar_furia_hp))
		return 1;
	endif

	if (mobile.npctemplate)
		if (AP_GetVital(mobile, HITS) < ( CInt(AP_GetVitalMaximumValue(mobile, HITS)/2) + bonus_limiar_furia_hp))
			return 1;
		endif
	elseif (AP_GetVital(mobile, HITS) < GetHP(mobile) + bonus_limiar_furia_hp)
		return 1;
	endif
	return 0;
endfunction

function HabilidadesPorNivel(who, classe, lvl)

	var possiveis := array;

	var habcfg := ReadConfigFile(":charactercreation:config/habilidades");
	var keys := getConfigStringKeys( habcfg );

	foreach key in keys
		var elem := FindConfigElem( habcfg, key );
		var d := GetConfigStringDictionary( elem, "classe" );
//		sendsysmessage(who, "elem " + elem + " classe " + classe  + " d[classe] " + d[classe]  );
		if ( cint(d[classe]) == lvl && d[classe] != error)
			possiveis.append(key);
		endif
	endforeach

	return possiveis;

endfunction

function HabilidadesPorNivelFaccao(who, faccao, lvl)

	var possiveis := array;

	var habcfg := ReadConfigFile(":charactercreation:config/habilidades");
	var keys := getConfigStringKeys( habcfg );

	foreach key in keys
		var elem := FindConfigElem( habcfg, key );
		var d := GetConfigStringDictionary( elem, "faccao" );
		if ( cint(d[faccao]) == lvl && d[faccao] != error)
			possiveis.append(key);
		endif
	endforeach

	return possiveis;

endfunction