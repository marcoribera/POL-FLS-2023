include ":itemsys:tabelas";
/*
TODO:

*/
function SetarModsNoItem(who, item)
    SetarAllProps(item);
    var attr := PegarProp(item);
    var attr_excp := PegarPropExcep(item);
    //var tipoequip := PegarTipo(item);

    //attr := PegarProp(item);

    if (attr)
        //if (attr."Atualiza" == 1)
            var hpmod := CalcPropMod(item, "hpmod");

            var physicalmod := CalcPropMod(item, "physicalmod");
            var firemod := CalcPropMod(item, "firemod");
            var coldmod := CalcPropMod(item, "coldmod");
            var poisonmod := CalcPropMod(item, "poisonmod");
            var energymod := CalcPropMod(item, "energymod");
            var dmgmod, speedmod, dexmod, parrymod, parrydelaymod;
            
            item.quality := CalcPropMod(item, "quality");

            if (item.IsA(POLCLASS_ARMOR))
                item.maxhp_mod := hpmod;

                item.resist_physical_mod := physicalmod;
                item.resist_fire_mod := firemod;
                item.resist_cold_mod := coldmod;
                item.resist_poison_mod := poisonmod;
                item.resist_energy_mod := energymod;

                if (IsEscudo(item))
                    /*var newattr := PegarProp(item);
                    var attr_escudo := BuscarValoresProtecao(item);
                    
                    newattr["item_dexpen"] := attr_escudo[2];
                    newattr["item_parry"] := attr_escudo[3];
                    newattr["item_parrydelay"] := attr_escudo[4];
                    SetarProp(item, newattr);*/

                    //CalcPropMod(item, "dexpenmod");
                    //item.SetProp("parrybonus", CalcPropMod(item, "parrymod"));
                    //item.SetProp("parrydelay_mod", CalcPropMod(item, "parrydelaymod"));
                endif

            elseif (item.IsA(POLCLASS_WEAPON))
                dmgmod := CalcPropMod(item, "dmgmod");
                speedmod := CalcPropMod(item, "speedmod");

                item.maxhp_mod := hpmod;
                item.dmg_mod := dmgmod;
                item.speed_mod := speedmod; item.SetProp("attackspeedbonus", speedmod); //DEPOIS CONFERIR PARA DEIXAR APENAS 1 DELES

                item.damage_physical_mod := physicalmod;
                item.damage_fire_mod := firemod;
                item.damage_cold_mod := coldmod;
                item.damage_poison_mod := poisonmod;
                item.damage_energy_mod := energymod;
            endif
        //endif
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
    var new_attr := BuscarValoresProtecao(item);
    var elem := BuscarValoresCfg(item);
    
    attr["item_hp"] := elem.MaxHP;
    if (item.isA(POLCLASS_WEAPON))
        attr["item_physical"] := elem.PhysicalDamage;
        attr["item_fire"] := elem.FireDamage;
        attr["item_cold"] := elem.ColdDamage;
        attr["item_poison"] := elem.PoisonDamage;
        attr["item_energy"] := elem.EnergyDamage;

    elseif (item.isA(POLCLASS_ARMOR))
        attr["item_physical"] := elem.PhysicalResist;
        attr["item_fire"] := elem.FireResist;
        attr["item_cold"] := elem.ColdResist;
        attr["item_poison"] := elem.PoisonResist;
        attr["item_energy"] := elem.EnergyResist;

    endif
    if (IsEscudo(item))
        attr["item_dexpen"] := new_attr[2];
        attr["item_parry"] := new_attr[3];
        attr["item_parrydelay"] := new_attr[4];

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
        newattr := TabelaDamageMod(item);

        attr["base_hpmod"] := (newattr[6]);

		attr["base_physicalmod"] := (newattr[1] + attr["item_physical"])-(item.damage_physical-item.damage_physical_mod);
		attr["base_firemod"] := (newattr[2] + attr["item_fire"])-(item.damage_fire-item.damage_fire_mod);
		attr["base_coldmod"] := (newattr[3] + attr["item_cold"])-(item.damage_cold-item.damage_cold_mod);
		attr["base_poisonmod"] := (newattr[4] + attr["item_poison"])-(item.damage_poison-item.damage_poison_mod);
		attr["base_energymod"] := (newattr[5] + attr["item_energy"])-(item.damage_energy-item.damage_energy_mod);

        //print(newattr[1]+" "+newattr[2]+" "+newattr[3]+" "+newattr[4]+" "+newattr[5]+" "+newattr[6]);
    elseif (item.isA(POLCLASS_ARMOR))
        newattr := TabelaResistMod(item);

        attr["base_hpmod"] := (newattr[6])-(item.hpmax-item.hpmax_mod);

		attr["base_physicalmod"] := (newattr[1])-(CInt(item.resist_physical_mod));
		attr["base_firemod"] := (newattr[2])-(CInt(item.resist_fire_mod));
		attr["base_coldmod"] := (newattr[3])-(CInt(item.resist_cold_mod));
		attr["base_poisonmod"] := (newattr[4])-(CInt(item.resist_poison_mod));
		attr["base_energymod"] := (newattr[5])-(CInt(item.resist_energy_mod));

        if (IsEscudo(item)) //AS COMENTADAS JÁ EXISTEM EM OUTRA PROP EM OUTRO LUGAR. NÃO REMOVI PRA CASO DE PRECISAR REORGANIZAR FUTURAMENTE
            newattr_escudo := TabelaValoresProtecao(item);

            attr["base_hpmod"] := (newattr[6]*5)-(item.hpmax-item.hpmax_mod);

            //attr["escudoResist"] := newattr_escudo[1];
            //attr["base_physicalmod"] := (attr["item_physical"]+newattr[1])-(item.resist_physical-item.resist_physical_mod);
            attr["base_dexpenmod"] := (newattr_escudo[2] - attr["item_dexpen"]);
            attr["base_parrymod"] := (newattr_escudo[3] - attr["item_parry"]);
            attr["base_parrydelaymod"] := (newattr_escudo[4] - attr["item_parrydelay"]);

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

function BuscarValoresProtecao(item);
    //var attr := PegarProp(item);
    var valores := Array;
    var valprot := Array;
    var valslot := Array;

    if(IsEscudo(item)) valores := TabelaValoresProtecao(item);
    elseif(item.IsA(POLCLASS_WEAPON)) //ARMA NÃO PRECISA. JÁ ATUALIZA AUTOMÁTICO NO START PELO .CFG MESMO
    elseif(item.IsA(POLCLASS_ARMOR)) //ARMADURA TEM SOMA BASEADO NO SLOT
        valprot := TabelaValoresProtecao(item);
        valslot := TabelaValoresSlot(item);

        valores := valprot;
        valores[1] += valslot[1];
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
function CalcPropMod(item, mod) //CALCULA O VALOR REAL PARA DEFINIR NO ITEM
    var valor;
    var attr := PegarProp(item);
    var attr_excp := PegarPropExcep(item);
    
    case (Lower(mod))
        "quality": valor := attr["Quality"]; break;

        "hpmod": valor := (CInt(attr["base_hpmod"]) + CInt(attr["hab_hpmod"]) + CInt(attr_excp["hpmod"])); break;

        "dmgmod": valor := (CInt(attr."base_dmgmod") + CInt(attr."hab_dmgmod") + CInt(attr_excp."dmgmod")); break;
        "speedmod": valor := (CInt(attr."base_speedmod") + CInt(attr."hab_speedmod") + CInt(attr_excp."speedmod")); break;

        "dexpenmod": valor := (CInt(attr."base_dexpenmod") + CInt(attr."hab_dexpenmod") + CInt(attr_excp."dexpenmod")); break;
        "parrymod": valor := (CInt(attr."base_parrymod") + CInt(attr."hab_parrymod") + CInt(attr_excp."parrymod")); break;
        "parrydelaymod": valor := (CInt(attr."base_parrydelaymod") + CInt(attr."hab_parrydelaymod") + CInt(attr_excp."parrydelaymod")); break;

        "physicalmod": valor := (CInt(attr."base_physicalmod") + CInt(attr."hab_physicalmod") + CInt(attr_excp."physicalmod")); break;
        "firemod": valor := (CInt(attr."base_firemod") + CInt(attr."hab_firemod") + CInt(attr_excp."firemod")); break;
        "coldmod": valor := (CInt(attr."base_coldmod") + CInt(attr."hab_coldmod") + CInt(attr_excp."coldmod")); break;
        "poisonmod": valor := (CInt(attr."base_poisonmod") + CInt(attr."hab_poisonmod") + CInt(attr_excp."poisonmod")); break;
        "energymod": valor := (CInt(attr."base_energymod") + CInt(attr."hab_energymod") + CInt(attr_excp."energymod")); break;
    endcase

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