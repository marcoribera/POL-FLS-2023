include ":attributes:attributes";
include ":tn:cooldown";
include ":charactercreation:habilidades";

const FORTITUDE := "Fortitude";
const REFLEXOS := "Reflexos";
const VONTADE := "Vontade";
//const VALOR_REFERENCIA := 10;

//------------------------------------------------------
//DIFICULDADES REFERÊNCIA PARA OS TESTES DE RESISTÊNCIA
//
//Fácil 				30
//Médio 				45
//Difícil 				60
//Muito Difícil 		75
//Extremamente Difícil 	90
//Quase Impossível 		105
//
//------------------------------------------------------


function GetResist(who, resist)
	// Coleta informações da ficha do personagem
	var chardata := GetObjProperty(who, "chardata");
	var classe := chardata.classe;
	var vantagem := chardata.vantagemracial;
	var kit := chardata.kit;

	var valor := 0;

 	// Faz a resistência de Vontade para utilizar o valor de Reflexos quanto usando a habilidade "Desviar Mente"
	if (resist == VONTADE && (GetCooldown(who, "desviarmente") > 0))
		resist := REFLEXOS;
	endif

	// Aplica os bonus e redutores dos Kits
	if (kit == "Fortitude do Urso")
		if (resist == FORTITUDE)
			valor := valor + 20; // +200% do VALOR_REFERENCIA
		else
			valor := valor - 10; // -100% do VALOR_REFERENCIA
		endif
	elseif (kit == "Reflexos de Pantera")
		if (resist == REFLEXOS)
			valor := valor + 20; // +200% do VALOR_REFERENCIA
		else
			valor := valor - 10; // -100% do VALOR_REFERENCIA
		endif
	elseif (kit == "Vontade da Aguia")
		if (resist == VONTADE)
			valor := valor + 20; // +200% do VALOR_REFERENCIA
		else
			valor := valor - 10; // -100% do VALOR_REFERENCIA
		endif
	endif

	if (resist == FORTITUDE)

		// Aplica os bonus base do Caminho para a resistência
		if (classe == "Guerreiro")
			valor := valor + 30; // +300% do VALOR_REFERENCIA
		else
			valor := valor + 15; // +150% do VALOR_REFERENCIA
		endif

		// Aplica bonus de Atributo atual para a resistência
		valor := valor + CInt(AP_GetStat(who, STRENGTH)/10); // STRENGTH % do VALOR_REFERENCIA

		// Aplica os modificadores temporários para a resistência
		valor := valor + CInt(GetObjProperty(who, "#FortitudeMod"));

	elseif (resist == REFLEXOS)

		// Aplica os bonus base do Caminho para a resistência
		if (classe == "Ladino")
			valor := valor + 30; // +300% do VALOR_REFERENCIA
		else
			valor := valor + 15; // +150% do VALOR_REFERENCIA
		endif

		// Aplica bonus de Atributo atual para a resistência
		valor := valor + CInt(AP_GetStat(who, DEXTERITY)/10); // DEXTERITY % do VALOR_REFERENCIA


		// Aplica os modificadores temporários para a resistência
		valor := valor + CInt(GetObjProperty(who, "#ReflexosMod"));

	else // (resist == VONTADE)

		// Aplica os bonus base do Caminho para a resistência
		if (classe == "Sabio")
			valor := valor + 30; // +300% do VALOR_REFERENCIA
		else
			valor := valor + 15; // +150% do VALOR_REFERENCIA
		endif

		// Aplica bonus de Atributo atual para a resistência
		valor := valor + CInt(AP_GetStat(who, INTELLIGENCE)/10); // INTELLIGENCE % do VALOR_REFERENCIA

		// Aplica os modificadores temporários para a resistência
		valor := valor + CInt(GetObjProperty(who, "#VontadeMod"));

		// Aplica modificadores de vantagens raciais
		if (vantagem == "Vontade de Ferro")
			valor := valor + 20; // +200% do VALOR_REFERENCIA
		endif

		// Aplica modificadores decorrentes de habilidades
		if ( GetCooldown(who, "VontadeIndomavel")) // Habilidade ativa
			valor := valor + 40; // +400% do VALOR_REFERENCIA
		elseif (temHabilidade(who, "Treinamento Vigilante")) // Habilidade passiva
			valor := valor + 40; // +400% do VALOR_REFERENCIA
		endif
	endif

    //vantagem dos zharkianos q da +10 nos 3 resists
    if (vantagem == "Resistentes")
		valor := valor + 10; // +100% do VALOR_REFERENCIA
    endif

	return valor;
endfunction

function CheckResist(who, resist, dif, mod := 0)

	// Rola o dado da aleatoriedade permitindo superar testes de até +400% do VALOR_REFERENCIA além da resistência base do personagem
	var dado := RandomInt(40) + 1;
	var valor := GetResist(who, resist);

	//printtextabove(who, "dado " + dado + " valor " + valor + " diff " + dif);

	if (dado + valor + mod >= dif)
		return 1;

	//Quando é Zharkiano e estiver Bloodied ativa a habilidade racial "Segunda chance"
	elseif ((GetObjProperty(who, "chardata")).povo == "Zharkiano" && IsBloodied(who))
		dado := RandomInt(40) + 1;
		if (dado + valor + mod >= dif)
			SendSysMessageEx(who, "Zharkia esta do seu lado!", SSM_INFO);
			return 1;
		endif

	//Não passando no teste de resistência, informa ao pobre infeliz.
	else
		SendSysMessageEx(who, "Falhou no teste de resistencia", SSM_INFO);
		return 0;
	endif
endfunction
