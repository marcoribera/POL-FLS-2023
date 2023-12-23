include ":itemsys:tabelas";
/*
TODO:
ADICIONAR A ATUALIZAÇÃO NO SCRIPT QUE CRIA A PROP CREATEDBY EM TODOS OS ITENS
ADICIONAR PARA SOMAR DEXPENALTY DAS ARMADURAS
VER A QUESTÃO DOS ITENS MÁGICOS
VER ITENS COM RECIPE
*/
function SetarModsNoItem(who, item)
    SetarAllProps(item);
    var attr := PegarProp(item);
    var attr_excp := PegarPropExcep(item);
    //var tipoequip := PegarTipo(item);

    if (attr)
        var hpmod := attr["base_hpmod"];

        var physicalmod := attr["base_physicalmod"];
        var firemod := attr["base_firemod"];
        var coldmod := attr["base_coldmod"];
        var poisonmod := attr["base_poisonmod"];
        var energymod := attr["base_energymod"];
        var dmgmod, speedmod, dexmod, parrymod, parrydelaymod;
        
        item.quality := attr["Quality"];

        if (item.IsA(POLCLASS_ARMOR))
            item.maxhp_mod := hpmod;

            item.resist_physical_mod := physicalmod;
            item.resist_fire_mod := firemod;
            item.resist_cold_mod := coldmod;
            item.resist_poison_mod := poisonmod;
            item.resist_energy_mod := energymod;

            if (IsEscudo(item))
                item.SetProp("penaltybonus", attr["base_dexpenmod"]);
                item.SetProp("parrybonus", attr["base_parrymod"]);
                item.SetProp("parrydelay_mod", attr["base_parrydelaymod"]);
            endif

        elseif (item.IsA(POLCLASS_WEAPON))
            dmgmod := attr["dmgmod"];
            speedmod := attr["speedmod"];

            item.maxhp_mod := hpmod;
            item.dmg_mod := dmgmod;
            item.speed_mod := speedmod; item.SetProp("attackspeedbonus", speedmod); //DEPOIS CONFERIR PARA DEIXAR APENAS 1 DELES

            item.damage_physical_mod := physicalmod;
            item.damage_fire_mod := firemod;
            item.damage_cold_mod := coldmod;
            item.damage_poison_mod := poisonmod;
            item.damage_energy_mod := energymod;
        endif
    else
        SendSysMessageEx(who, "BUG 666: ITEM {} SEM VALORES NO SISTEMA! FAVOR COMUNICAR A STAFF".Format(Hex(item.objtype)));
    endif
endfunction



//FUNCTIONS DE SETAR PROPS COMPLETAS
function SetarAllProps(item) //SETA TODAS AS PROPS BASE DO ITEM
    var attr := PegarProp(item);

    if (attr."Atualiza" == 0)
        return;
    else
        SetarPropTipo(item);
        SetarPropItem(item);
        SetarPropBase(item);
    endif
endfunction

function SetarPropTipo(item) 
    var cfg := ReadConfigFile(":combat:itemdesc");
	var elem := FindConfigElem(cfg, item.objtype);
    
    var attr := PegarProp(item);

   	if (item.IsA(POLCLASS_WEAPON))
		attr["TipoEquip"] := CStr(elem.TipoAtaque);
	elseif (item.IsA(POLCLASS_ARMOR))
		attr["TipoEquip"] := CStr(elem.TipoProtecao);
	endif

    SetarProp(item, attr);
endfunction

function SetarPropItem(item)
    //função para setar os valores base DO ITEM!
    //ADICIONAR VALORES DOS ITENS
    var attr := PegarProp(item);
    var newattr := BuscarValoresSlot(item);
    var elem := BuscarValoresCfg(item);

    attr["item_hp"] := elem.MaxHP;
     if (IsEscudo(item))
        attr["item_dexpen"] := newattr[2];
        attr["item_parry"] := newattr[3];
        attr["item_parrydelay"] := newattr[4];

        attr["item_physical"] := newattr[1];
        attr["item_fire"] := 0;
        attr["item_cold"] := 0;
        attr["item_poison"] := 0;
        attr["item_energy"] := 0;
    elseif (item.isA(POLCLASS_WEAPON))
        attr["item_physical"] := newattr[2];
        attr["item_fire"] := newattr[3];
        attr["item_cold"] := newattr[4];
        attr["item_poison"] := newattr[5];
        attr["item_energy"] := newattr[6];
    elseif (item.isA(POLCLASS_ARMOR))
        attr["item_physical"] := newattr[1];
        attr["item_fire"] := newattr[2];
        attr["item_cold"] := newattr[3];
        attr["item_poison"] := newattr[4];
        attr["item_energy"] := newattr[5];
    endif


    SetarProp(item, attr);
endfunction

function SetarPropBase(item) //SETA AS PROPS DE MODIFICADORES DE (MATERIAL - ITEM) JÁ COM SEUS VALORES - OS MODIFICADORES DE EXCEPCIONAIS SÃO SETADOS NO CRAFTING
    var attr := PegarProp(item);
    var attr_excp := PegarPropExcep(item);
    var newattr := Array;
    var newattr_escudo := Array;
    //var material := Hex(item.GetProp("material"));
    //var tipo := attr."TipoEquip";

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //ADICIONAR MODS BASE
    attr["Atualiza"] := 1;
    if (item.isA(POLCLASS_WEAPON))
        var slot := "weapon";

        attr["base_hpmod"] := CalcPropMod(item, "hpmod", slot);

		attr["base_physicalmod"] := CalcPropMod(item, "physicalmod", slot); //(newattr[1] + attr["item_physical"])-(item.damage_physical-item.damage_physical_mod);
		attr["base_firemod"] := CalcPropMod(item, "firemod", slot);
		attr["base_coldmod"] := CalcPropMod(item, "coldmod", slot);
		attr["base_poisonmod"] := CalcPropMod(item, "poisonmod", slot);
		attr["base_energymod"] := CalcPropMod(item, "energymod", slot);

        //print(newattr[1]+" "+newattr[2]+" "+newattr[3]+" "+newattr[4]+" "+newattr[5]+" "+newattr[6]);
    elseif (item.isA(POLCLASS_ARMOR))
        var slot := "armor";

        attr["base_hpmod"] := CalcPropMod(item, "hpmod", slot);

		attr["base_physicalmod"] := CalcPropMod(item, "physicalmod", slot);
		attr["base_firemod"] := CalcPropMod(item, "firemod", slot);
		attr["base_coldmod"] := CalcPropMod(item, "coldmod", slot);
		attr["base_poisonmod"] := CalcPropMod(item, "poisonmod", slot);
		attr["base_energymod"] := CalcPropMod(item, "energymod", slot);

        if (IsEscudo(item)) //AS COMENTADAS JÁ EXISTEM EM OUTRA PROP EM OUTRO LUGAR. NÃO REMOVI PRA CASO DE PRECISAR REORGANIZAR FUTURAMENTE
            var slot := "shield";
            attr["base_hpmod"] := CalcPropMod(item, "hpmod", slot);

            attr["base_physicalmod"] := CalcPropMod(item, "physicalmod", slot);
            attr["base_dexpenmod"] := CalcPropMod(item, "dexpenmod", slot);
            attr["base_parrymod"] := CalcPropMod(item, "parrymod", slot);
            attr["base_parrydelaymod"] := CalcPropMod(item, "parrydelaymod", slot);
        endif
    endif

    SetarProp(item, attr);
endfunction



//FUNCTIONS DE BUSCA
function BuscarValoresCfg(item) //RETORNA TODOS OS VALORES DO ITEM QUE AINDA ESTIVEREM NO .CFG
    var cfg := ReadConfigFile(":combat:itemdesc");
    var elem := FindConfigElem(cfg, item.objtype);

    return elem;
endfunction

function BuscarValoresSlot(item);
    //var attr := PegarProp(item);
    var valores := Array;
    var valprot := Array;
    var valslot := Array;

    if(IsEscudo(item)) //ESCUDO TEM SOMA BASEADO NO SLOT
        valprot := TabelaProtecao(item);
        valslot := TabelaSlot(item);

        valores := valprot;
        valores[1] := valores[1] + valslot[1];
    elseif(item.IsA(POLCLASS_WEAPON))
        valores := TabelaDanos(item);

    elseif(item.IsA(POLCLASS_ARMOR)) //ARMADURA TAMBÉM
        valprot := TabelaProtecao(item);
        valslot := TabelaSlot(item);

        valores := valprot;
        valores[1] := valores[1] + valslot[1];
    endif

    return valores;
endfunction

function BuscarDebuffSlot(item)
    var valores := Array;
    var valdebuff := Array;
    var valslot := Array;

    if(IsEscudo(item))
        valdebuff := TabelaProtecao(item);
        valslot := TabelaSlot(item);

        valores := valdebuff;
        valores[2] := valores[2] + valslot[2];
    elseif(item.IsA(POLCLASS_ARMOR))
        valdebuff := TabelaProtecao(item);
        valslot := TabelaSlot(item);

        valores := valslot;
    endif

    return valores;
endfunction

function IsEscudo(item)
    var tipoequip := PegarTipo(item);
    var escudo := SplitWords(Lower(tipoequip)); escudo := escudo[1];

    if (escudo == "escudo") return 1;
    else return;
    endif
endfunction



//FUNCTIONS PARA MANIPULAR PROPS
function PegarTipo(item) //PEGA A PROP DO TIPO DO EQUIPAMENTO
    var tipo := PegarProp(item);
    tipo := tipo."TipoEquip";
    return tipo;
endfunction

function PegarSlot(item) //PEGA O SLOT DO ITEM NO .CFG
    var elem := BuscarValoresCfg(item);
    return Lower(elem.Coverage);
endfunction

function PegarProp(item) //PEGA A PROP DE MODIFICADORES BASE
    var prop := item.GetProp("atributos");
    if (!prop) prop := Dictionary{}; endif
    return prop;
endfunction

function PegarPropExcep(item) //PEGA A PROP DE MODIFICADORES EXCEPCIONAL
    var prop := item.GetProp("atributos_excp");
    if (!prop) prop := Dictionary{}; endif
    return prop;
endfunction

function SetarProp(item, prop) //SETA A PROP DE MODIFICADORES BASE
    if (prop.Size() != 0) item.SetProp("atributos", prop); endif
endfunction

function SetarPropExcep(item, prop) //SETA A PROP DE MODIFICADORES EXCEPCIONAL
    if (prop.Size() != 0) item.SetProp("atributos_excp", prop); endif
endfunction



//FUNCTIONS DE CÁLCULO
function CalcPropMod(item, mod, slot) //CALCULA O VALOR REAL PARA DEFINIR NO ITEM
    var valor, newattr, newattr_escudo, newattrdebuff;
    var attr := PegarProp(item);
    var attr_excp := PegarPropExcep(item);
    mod.Lower(); slot.Lower();

    case (mod) //COMUM A TODOS
        "quality":  valor := attr["Quality"]; break;
    endcase
    if (slot == "weapon")
        newattr := TabelaMaterialDamageMod(item);
        
        case (mod)
            "hpmod": valor := (newattr[6] + CInt(attr["item_hp"]) + CInt(attr["hab_hpmod"]) + CInt(attr_excp["hpmod"]))-(item.MaxHP-item.MaxHP_Mod); break;

            "dmgmod": valor := (CInt(attr."hab_dmgmod") + CInt(attr_excp."dmgmod")); break;
            "speedmod": valor := (CInt(attr["item_speed"]) + CInt(attr["hab_speedmod"]) + CInt(attr_excp["speedmod"])); break;

            "physicalmod": valor := (newattr[1] + CInt(attr["item_physical"]) + CInt(attr."hab_physicalmod") + CInt(attr_excp."physicalmod"))-(item.damage_physical-item.damage_physical_mod); break;
            "firemod": valor := (newattr[2] + CInt(attr["item_fire"]) + CInt(attr."hab_firemod") + CInt(attr_excp."firemod"))-(item.damage_fire-item.damage_fire_mod); break;
            "coldmod": valor := (newattr[3] + CInt(attr["item_cold"]) + CInt(attr."hab_coldmod") + CInt(attr_excp."coldmod"))-(item.damage_cold-item.damage_cold_mod); break;
            "poisonmod": valor := (newattr[4] + CInt(attr["item_poison"]) + CInt(attr."hab_poisonmod") + CInt(attr_excp."poisonmod"))-(item.damage_poison-item.damage_poison_mod); break;
            "energymod": valor := (newattr[5] + CInt(attr["item_energy"]) + CInt(attr."hab_energymod") + CInt(attr_excp."energymod"))-(item.damage_energy-item.damage_energy_mod); break;
        endcase
    elseif (slot == "armor")
        newattr := TabelaMaterialResistMod(item);
        newattrdebuff := BuscarDebuffSlot(item);

        case (mod)
            "hpmod": valor := (newattr[6] + CInt(attr["hab_hpmod"]) + CInt(attr_excp["hpmod"]));//-(item.MaxHP-item.MaxHP_Mod);
            print("calculando hp!"); print(newattr[6]); print(item.MaxHP); print(item.MaxHP_Mod); print((item.MaxHP-item.MaxHP_Mod)); print(valor);
            break;
            
            "dexpenmod": valor := (newattrdebuff[2] + CInt(attr["item_dexpen"]) + CInt(attr."hab_dexpenmod") + CInt(attr_excp."dexpenmod")); break;

            "physicalmod": valor := (newattr[1] + CInt(attr["item_physical"]) + CInt(attr."hab_physicalmod") + CInt(attr_excp."physicalmod"))-(item.resist_physical-item.resist_physical_mod); break;
            "firemod": valor := (newattr[2] + CInt(attr["item_fire"]) + CInt(attr."hab_firemod") + CInt(attr_excp."firemod"))-(item.resist_fire-item.resist_fire_mod); break;
            "coldmod": valor := (newattr[3] + CInt(attr["item_cold"]) + CInt(attr."hab_coldmod") + CInt(attr_excp."coldmod"))-(item.resist_cold-item.resist_cold_mod); break;
            "poisonmod": valor := (newattr[4] + CInt(attr["item_poison"]) + CInt(attr."hab_poisonmod") + CInt(attr_excp."poisonmod"))-(item.resist_poison-item.resist_poison_mod); break;
            "energymod": valor := (newattr[5] + CInt(attr["item_energy"]) + CInt(attr."hab_energymod") + CInt(attr_excp."energymod"))-(item.resist_energy-item.resist_energy_mod); break;
        endcase

    elseif (slot == "shield")
        newattr := TabelaMaterialResistMod(item);
        newattr_escudo := TabelaProtecao(item);
        newattrdebuff := BuscarDebuffSlot(item);
        //print("{} {} {}".Format(newattr[1], newattr[2], newattr[3]));

        case (mod)
            "hpmod": valor := ((newattr[6]*5) + CInt(attr["item_hp"]) + CInt(attr["hab_hpmod"]) + CInt(attr_excp["hpmod"]))-(item.MaxHP-item.MaxHP_Mod); break;
 
            "dexpenmod": valor := (newattrdebuff[2] + CInt(attr["item_dexpen"]) + CInt(attr."hab_dexpenmod") + CInt(attr_excp."dexpenmod")); break;
            "parrymod": valor := (CInt(attr["item_parry"]) + CInt(attr."hab_parrymod") + CInt(attr_excp."parrymod")); break;
            "parrydelaymod": valor := (CInt(attr["item_parrydelay"]) + CInt(attr."hab_parrydelaymod") + CInt(attr_excp."parrydelaymod")); break;

            "physicalmod": valor := (newattr[1] + CInt(attr["item_physical"]) + CInt(attr."hab_physicalmod") + CInt(attr_excp."physicalmod"))-(item.resist_physical-item.resist_physical_mod); break;
            "firemod": valor := (newattr[2] + CInt(attr["item_fire"]) + CInt(attr."hab_firemod") + CInt(attr_excp."firemod"))-(item.resist_fire-item.resist_fire_mod); break;
            "coldmod": valor := (newattr[3] + CInt(attr["item_cold"]) + CInt(attr."hab_coldmod") + CInt(attr_excp."coldmod"))-(item.resist_cold-item.resist_cold_mod); break;
            "poisonmod": valor := (newattr[4] + CInt(attr["item_poison"]) + CInt(attr."hab_poisonmod") + CInt(attr_excp."poisonmod"))-(item.resist_poison-item.resist_poison_mod); break;
            "energymod": valor := (newattr[5] + CInt(attr["item_energy"]) + CInt(attr."hab_energymod") + CInt(attr_excp."energymod"))-(item.resist_energy-item.resist_energy_mod); break;
        endcase
    endif

    return valor;
endfunction





//APENAS PARA ATUALIZAR ITENS ANTES DA IMPLEMENTAÇÃO
function AtualizarItemAntigo(who, item) 
    var attr := PegarProp(item);

    if (attr["Atualiza"] != 0 && attr["Atualiza"] != 1)
        SendSysMessageEx(who, "Item {} com base de dados antiga, atualizando para novo modelo...".Format(Hex(item.objtype)), SSM_FAIL);

        SetarPropBase(item);
        SetarPropTipo(item);
        attr := PegarProp(item);
        var tipoequip := PegarTipo(item);
        //var isescudo := IsEscudo(item);
        var propexcpantiga := item.GetProp("Exceptional");

        attr["Quality"] := item.quality; SetarProp(item, attr);

        if (propexcpantiga == 1)
            SendSysMessageEx(who, "Item Excepcional detectado! Adicionando valores...", SSM_INFO);
            var attr_excp := PegarPropExcep(item);

            //attr_excp["hpmod"] := item.maxhp_mod - (CInt(attr."hab_hpmod") + CInt(attr."base_hpmod")); //DESATIVADO POR QUE O SHARD JÁ MULTIPLICA O HP PELA QUALIDADE DO ITEM EM ALGUM OUTRO LUGAR

            if (item.IsA(POLCLASS_WEAPON))
                attr_excp["dmgmod"] := item.dmg_mod - (CInt(attr."hab_dmgmod") + CInt(attr."base_dmgmod"));
                attr_excp["speedmod"] := CInt(item.GetProp("attackspeedbonus")) - (CInt(attr."hab_speedmod") + CInt(attr."base_speedmod"));
                attr_excp["physicalmod"] := item.damage_physical_mod - (CInt(attr."hab_physicalmod") + CInt(attr."base_physicalmod"));
                attr_excp["firemod"] := item.damage_fire_mod - (CInt(attr."hab_firemod") + CInt(attr."base_firemod"));
                attr_excp["coldmod"] := item.damage_cold_mod - (CInt(attr."hab_coldmod") + CInt(attr."base_coldmod"));
                attr_excp["poisonmod"] := item.damage_poison_mod - (CInt(attr."hab_poisonmod") + CInt(attr."base_poisonmod"));
                attr_excp["energymod"] := item.damage_energy_mod - (CInt(attr."hab_energymod") + CInt(attr."base_energymod"));
            elseif(item.IsA(POLCLASS_ARMOR))
                attr_excp["physicalmod"] := item.resist_physical_mod - (CInt(attr."hab_physicalmod") + CInt(attr."base_physicalmod"));
                attr_excp["firemod"] := item.resist_fire_mod - (CInt(attr."hab_firemod") + CInt(attr."base_firemod"));
                attr_excp["coldmod"] := item.resist_cold_mod - (CInt(attr."hab_coldmod") + CInt(attr."base_coldmod"));
                attr_excp["poisonmod"] := item.resist_poison_mod - (CInt(attr."hab_poisonmod") + CInt(attr."base_poisonmod"));
                attr_excp["energymod"] := item.resist_energy_mod - (CInt(attr."hab_energymod") + CInt(attr."base_energymod"));
            endif
            SetarPropExcep(item, attr_excp);

        else
            attr := PegarProp(item);
            var valor, itemhab;
            valor := item.maxhp_mod - CInt(attr."base_hpmod"); if(valor > 0) attr["hab_hpmod"] := valor; itemhab := 1; endif

            if (item.IsA(POLCLASS_WEAPON))
                valor := item.dmg_mod - CInt(attr."base_dmgmod"); if(valor > 0) attr["hab_dmgmod"] := valor; itemhab := 1; endif
                valor := CInt(item.GetProp("attackspeedbonus")) - CInt(attr."base_speedmod"); if(valor > 0) attr["hab_speedmod"] := valor; itemhab := 1; endif
                valor := item.damage_physical_mod - CInt(attr."base_physicalmod"); if(valor > 0) attr["hab_physicalmod"] := valor; itemhab := 1; endif
                valor := item.damage_fire_mod - CInt(attr."base_firemod"); if(valor > 0) attr["hab_firemod"] := valor; itemhab := 1; endif
                valor := item.damage_cold_mod - CInt(attr."base_coldmod"); if(valor > 0) attr["hab_coldmod"] := valor; itemhab := 1; endif
                valor := item.damage_poison_mod - CInt(attr."base_poisonmod"); if(valor > 0) attr["hab_poisonmod"] := valor; itemhab := 1; endif
                valor := item.damage_energy_mod - CInt(attr."base_energymod"); if(valor > 0) attr["hab_energymod"] := valor; itemhab := 1; endif
            elseif(item.IsA(POLCLASS_ARMOR))
                valor := item.resist_physical_mod - CInt(attr."base_physicalmod"); if(valor > 0) attr["hab_base_physicalmod"] := valor; itemhab := 1; endif
                valor := item.resist_fire_mod - CInt(attr."base_firemod"); if(valor > 0) attr["hab_firemod"] := valor; itemhab := 1; endif
                valor := item.resist_cold_mod - CInt(attr."base_coldmod"); if(valor > 0) attr["hab_coldmod"] := valor; itemhab := 1; endif
                valor := item.resist_poison_mod - CInt(attr."base_poisonmod"); if(valor > 0) attr["hab_poisonmod"] := valor; itemhab := 1; endif
                valor := item.resist_energy_mod - CInt(attr."base_energymod"); if(valor > 0) attr["hab_energymod"] := valor; itemhab := 1; endif
            endif
            if (itemhab) SendSysMessageEx(who, "Item com Propriedade de Habilidade detectado! Adicionando valores...", SSM_INFO);
            else SendSysMessageEx(who, "Item sem Propriedade de Habilidade ou Excepcional! Adicionando valores...", SSM_INFO);
            endif
        endif
        if (IsEscudo(item))
            var valor;
            SendSysMessageEx(who, "Escudo detectado! Adicionando valores...", SSM_INFO);
            valor := CInt(item.GetProp("penaltybonus")) - CInt(attr."base_dexpenmod"); if(valor > 0) attr["hab_dexpenmod"] := valor; endif
            valor := CInt(item.GetProp("parrybonus")) - CInt(attr."base_parrymod"); if(valor > 0) attr["hab_parrymod"] := valor; endif
            valor := CInt(item.GetProp("parrydelay_mod")) - CInt(attr."base_parrydelaymod"); if(valor > 0) attr["hab_parrydelaymod"] := valor; endif
        endif

        SetarProp(item, attr);

        SendSysMessageEx(who, "!!! Item {} atualizado para novo modelo de base de dados com SUCESSO !!!".Format(Hex(item.objtype)), SSM_INFO);
    endif
endfunction