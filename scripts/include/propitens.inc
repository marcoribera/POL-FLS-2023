/*

*/

///////////////////////////////
///// NOVO ".CFG" - START /////
///////////////////////////////
function TabelaResistMod(material) //objtype do material: return {FISICO, FIRE, COLD, POISON, ENERGY, HP}
    material := Lower(material);
    case(material)
        //METAL
        //TIER 1
        "0x6309": return {0,0,0,0,0,0}; //FERRO
        "0x6993": return {-2,0,0,0,0,-10}; //PRATA LUNAR
        "0x6991": return {-2,0,0,0,0,-20}; //ESTANHO
        "0x6465": return {-2,1,0,0,0,-10}; //COBRE
        "0x6995": return {1,0,0,0,0,10}; //AÇO
        "0x6994": return {-1,1,0,0,0,0}; //BRONZE
        "0x630e": return {-4,0,0,0,0,-40}; //OURO

        //TIER 2
        "0x630a": return {2,0,0,0,0,0}; //LITAN
        "0x630d": return {1,4,0,0,0,20}; //FIGIN
        "0x6460": return {1,0,4,0,0,20}; //ARGONIL
        "0x630c": return {1,0,0,4,0,20}; //SINQUE
        "0x630b": return {1,0,0,0,4,20}; //HELCE
        "0x6602": return {2,1,1,1,1,20}; //ACIELITH
        "0x6603": return {-1,0,0,0,0,-30}; //CRITALITH
        "0x6601": return {1,0,0,0,0,80}; //STALITH

        //TIER 3
        "0x6310": return {3,0,0,0,0,0}; //GALVORN
        "0x6605": return {3,6,0,0,0,30}; //IGNARILITH
        "0x6606": return {3,0,6,0,0,30}; //GLACIALITH
        "0x6607": return {3,0,0,6,0,30}; //VENERILITH
        "0x6608": return {3,0,0,0,6,30}; //ENERLITH
        "0x6604": return {4,0,0,0,5,30}; //PLATINUM
        "0x6609": return {-2,0,0,0,5,-50}; //LUNIUM
        "0x6610": return {3,0,0,0,0,-30}; //CELERIUM
        
        //TIER 4
        "0x6997": return {4,8,0,0,0,40}; //SOLIUM
        "0x699a": return {4,0,8,0,0,40}; //ICELUM
        "0x6999": return {4,0,0,8,0,40}; //HISSIUM
        "0x6998": return {4,0,0,0,8,40}; //TESLIUM
        "0x6311": return {4,4,4,4,4,50}; //MITHRIL

        //TIER 5
        "0x699a": return {5,6,6,6,6,60}; //ORICALCUM

        //COURO
        /*Curtido->{0,0,0,0,0}, 
        Peludo->{0,0,0,0,0}, 
        Espesso->{0,0,0,0,0}, 
        Polar->{0,0,0,0,0}, 
        Escamoso->{0,0,0,0,0}, 
        Anfíbio->{0,0,0,0,0}, 
        Ogro->{0,0,0,0,0}, 
        Aquático->{0,0,0,0,0}, 
        Reptiliano->{0,0,0,0,0}, 
        Hidra->{0,0,0,0,0}, 
        Draconiano->{0,0,0,0,0}, 
        Troll->{0,0,0,0,0}, 
        Terathan->{0,0,0,0,0}, 
        Gigante->{0,0,0,0,0}, 
        Aspero->{0,0,0,0,0}, 
        Negro->{0,0,0,0,0}, 

        //OSSO
        Osso->{0,0,0,0,0}, 
        Osso Cinza->{0,0,0,0,0}, 
        Osso Vermelho->{0,0,0,0,0}, 
        Osso Preto->{0,0,0,0,0}, 
        Osso de Lich->{0,0,0,0,0}, 
        Osso de Reptiliano->{0,0,0,0,0}, 
        Osso de Gigante->{0,0,0,0,0}, 
        Osso de Terathan->{0,0,0,0,0}, 
        Osso Demoníaco->{0,0,0,0,0}, 

        //TECIDO
        Lã->{0,0,0,0,0}, 
        Algodão->{0,0,0,0,0}, 
        Seda->{0,0,0,0,0}, 
        Linho->{0,0,0,0,0}, 
        Malva->{0,0,0,0,0}, 
        Sisal->{0,0,0,0,0}, 
        Denim->{0,0,0,0,0}, 
        Rami->{0,0,0,0,0}, 
        Flamel->{0,0,0,0,0}, 
        Rajal->{0,0,0,0,0}, */
    endcase
endfunction

function TabelaDamageMod(material) //objtype do material: return {FISICO, FIRE, COLD, POISON, ENERGY, HP}
    material := Lower(material);
    case(material)
        //METAL
        //TIER 1
        "0x6309": return {0,0,0,0,0,0}; //FERRO
        "0x6993": return {-5,0,0,0,10,-10}; //PRATA LUNAR
        "0x6991": return {-20,0,0,0,0,-20}; //ESTANHO
        "0x6465": return {-10,5,0,0,0,-10}; //COBRE
        "0x6995": return {5,0,0,0,0,10}; //AÇO
        "0x6994": return {-10,10,0,0,0,0}; //BRONZE
        "0x630e": return {-40,0,0,0,0,-40}; //OURO

        //TIER 2
        "0x630a": return {-20,5,5,5,5,0}; //LITAN
        /*"0x630d"->{-20,40,0,0,0,20}; //FIGIN
        "0x6460"->{-20,0,40,0,0,20}; //ARGONIL
        "0x630c"->{-20,0,0,40,0,20}; //SINQUE
        "0x630b"->{-20,0,0,0,40,20}; //HELCE
        "0x6602"->{-10,0,0,0,0,20}; //ACIELITH
        "0x6603"->{10,0,0,0,0,-30}; //CRITALITH
        "0x6601"->{0,0,0,0,0,80}; //STALITH

        //TIER 3
        "0x6310"->{0,0,0,0,0,0}; //GALVORN
        "0x6605"->{-30,60,0,0,0,30}; //IGNARILITH
        "0x6606"->{-30,0,60,0,0,30}; //GLACIALITH
        "0x6607"->{-30,0,0,60,0,30}; //VENERILITH
        "0x6608"->{-30,0,0,0,60,30}; //ENERLITH
        "0x6604"->{-20,0,0,0,50,30}; //PLATINUM
        "0x6609"->{10,0,0,0,5,-40}; //LUNIUM
        "0x6610"->{20,0,0,0,0,-30}; //CELERIUM

        //TIER 4
        "0x6997"->{-40,80,0,0,0,40}; //SOLIUM
        "0x699A"->{-40,0,80,0,0,40}; //ICELUM
        "0x6999"->{-40,0,0,80,0,40}; //HISSIUM
        "0x6998"->{-40,0,0,0,80,40}; //TESLIUM
        "0x6311"->{-40,20,20,20,20,50}; //MITHRIL

        //TIER 5
        "0x699B"->{10,10,10,10,10,60}; //ORICALCUM

        //COURO
        Curtido->{0,0,0,0,0}, 
        Peludo->{0,0,0,0,0}, 
        Espesso->{0,0,0,0,0}, 
        Polar->{0,0,0,0,0}, 
        Escamoso->{0,0,0,0,0}, 
        Anfíbio->{0,0,0,0,0}, 
        Ogro->{0,0,0,0,0}, 
        Aquático->{0,0,0,0,0}, 
        Reptiliano->{0,0,0,0,0}, 
        Hidra->{0,0,0,0,0}, 
        Draconiano->{0,0,0,0,0}, 
        Troll->{0,0,0,0,0}, 
        Terathan->{0,0,0,0,0}, 
        Gigante->{0,0,0,0,0}, 
        Aspero->{0,0,0,0,0}, 
        Negro->{0,0,0,0,0}, 

        //OSSO
        Osso->{0,0,0,0,0}, 
        Osso Cinza->{0,0,0,0,0}, 
        Osso Vermelho->{0,0,0,0,0}, 
        Osso Preto->{0,0,0,0,0}, 
        Osso de Lich->{0,0,0,0,0}, 
        Osso de Reptiliano->{0,0,0,0,0}, 
        Osso de Gigante->{0,0,0,0,0}, 
        Osso de Terathan->{0,0,0,0,0}, 
        Osso Demoníaco->{0,0,0,0,0}, 

        //TECIDO
        Lã->{0,0,0,0,0}, 
        Algodão->{0,0,0,0,0}, 
        Seda->{0,0,0,0,0}, 
        Linho->{0,0,0,0,0}, 
        Malva->{0,0,0,0,0}, 
        Sisal->{0,0,0,0,0}, 
        Denim->{0,0,0,0,0}, 
        Rami->{0,0,0,0,0}, 
        Flamel->{0,0,0,0,0}, 
        Rajal->{0,0,0,0,0},*/
    endcase
endfunction

function TabelaValoresProtecao(tipo)
    tipo := Lower(tipo);
    case(tipo) //ARMADURAS: -=> TipoProtecao: return {FISICO, FIRE, COLD, POISON, ENERGY}
        //TIER 1
        "armadura leve fraca": return {1,1,1,1,1};
        "armadura leve media": return {2,2,2,2,2};
        "armadura leve forte": return {3,3,3,3,3};

        //TIER 2
        "armadura media fraca": return {4,4,4,4,4};
        "armadura media media": return {5,5,5,5,5};
        "armadura media forte": return {6,6,6,6,6};

        //TIER 3
        "armadura pesada fraca": return {7,7,7,7,7};
        "armadura pesada media": return {8,8,8,8,8};
        "armadura pesada forte": return {9,9,9,9,9};
    endcase

    case(tipo) //ESCUDOS: -=> TipoProtecao: return {RESIST, DEXPENALTY, PARRYBONUS, PARRYDELAY}
        //TIER 1
        "escudo leve fraco": return {0,0,0,-1};
        "escudo leve medio": return {1,-1,1,0};
        "escudo leve forte": return {2,-2,2,1};

        //TIER 2
        "escudo medio fraco": return {2,-2,2,1};
        "escudo medio medio": return {3,-4,3,2};
        "escudo medio forte": return {5,-6,5,2};

        //TIER 3
        "escudo pesado fraco": return {6,-8,6,3};
        "escudo pesado medio": return {7,-9,7,4};
        "escudo pesado forte": return {8,-10,8,5};

        //TIER 4
        "escudo de corpo fraco": return {9,-12,10,6};
        "escudo de corpo medio": return {10,-14,12,6};
        "escudo de corpo forte": return {11,-16,14,6};
    endcase
endfunction

function TabelaValoresBase(slot)
    var valores := Dictionary;
    slot := Lower(slot);

    case(slot) //[1] = ResistBase; [2] = DexPenalty
        "head": return {1,1};
        "neck": return {1,1};
        "body": return {4,3};
        "arms": return {2,2};
        "hands": return {1,1};
        "legs/feet": return {3,2};
        "shield": return {2,1};
    endcase

    return valores;
endfunction
///////////////////////////
///// NOVO .CFG - END /////
///////////////////////////

/////////////////////////////////////
///// CÓDIGO DE VERDADE - START /////
/////////////////////////////////////
function SetarValoresNoItem(who, item)
    var attr := PegarProp(item);

    //if (!attr)
    SetarAllProps(item);
    attr := PegarProp(item);
    //endif

    var isescudo := Array;
    isescudo := SplitWords(attr."TipoEquip"); isescudo := Lower(isescudo[1]);
   
    if (attr)
        //if (attr."Atualiza" == 1)
            if (item.IsA(POLCLASS_ARMOR))
                item.resist_physical_mod := attr."physicalmod";
                item.resist_fire_mod := attr."firemod";
                item.resist_cold_mod := attr."coldmod";
                item.resist_poison_mod := attr."poisonmod";
                item.resist_energy_mod := attr."energymod";
                item.maxhp_mod := attr."hpmod";

                /*if (isescudo == "escudo")
                    SetarProp(item, attr);
                    item.SetProp("parrybonus", valores[3]);
                    item.SetProp("parrydelay_mod", valores[4]);
                endif*/
            elseif (item.IsA(POLCLASS_WEAPON))
                item.damage_physical_mod := attr."physicalmod";
                item.damage_fire_mod := attr."firemod";
                item.damage_cold_mod := attr."coldmod";
                item.damage_poison_mod := attr."poisonmod";
                item.damage_energy_mod := attr."energymod";
                item.maxhp_mod := attr."hpmod";
                item.dmg_mod := attr."dmgmod";
                item.speed_mod := attr."speedmod";
                item.quality := attr."quality";
            endif
        //endif
    else
        SendSysMessageEx(who, "BUG 666: ITEM {} SEM VALORES NO SISTEMA! FAVOR COMUNICAR A STAFF".Format(Hex(item.objtype)));
    endif
endfunction

function SetarAllProps(item)
    var attr := PegarProp(item);

    if (attr."Atualiza" == 0)
        return;
    else
        SetarPropTipo(item);
        SetarPropMods(item);
    endif
endfunction

function SetarPropTipo(item)
    var cfg := ReadConfigFile(":*:itemdesc");
	var elem := FindConfigElem(cfg, item.objtype);
    var attr := PegarProp(item);
    if (!attr) attr := Dictionary{}; endif

   	if (item.IsA(POLCLASS_WEAPON))
		attr["TipoEquip"] := CStr(elem.TipoAtaque);
	elseif (item.IsA(POLCLASS_ARMOR))
		attr["TipoEquip"] := CStr(elem.TipoProtecao);
	endif

    SetarProp(item, attr);
    //item.SetProp("atributos", attr);
endfunction

function BuscarValoresTipo(item);
    var valores;
    var attr := Dictionary;
    attr := PegarProp(item);

   	if (item.IsA(POLCLASS_WEAPON))
		valores := TabelaValoresProtecao(item."TipoAtaque");
	elseif (item.IsA(POLCLASS_ARMOR))
		valores := TabelaValoresProtecao(item."TipoProtecao");
	endif

    return valores;
endfunction

function SetarPropMods(item)
    var attr := PegarProp(item);
    if (!attr) attr := Dictionary{}; endif
    var newattr := Array;
    var newattr_escudo := Array;
    var material := Hex(item.GetProp("material"));
    var tipo := attr."TipoEquip";

    if (item.isA(POLCLASS_WEAPON))
        newattr := TabelaDamageMod(material);
        attr["Atualiza"] := 1;

		attr["physicalmod"] := newattr[1];
		attr["firemod"] := newattr[2];
		attr["coldmod"] := newattr[3];
		attr["poisonmod"] := newattr[4];
		attr["energymod"] := newattr[5];
        attr["hpmod"] := newattr[6];

        SetarProp(item, attr);
        //item.SetProp("atributos", attr);

    elseif (item.isA(POLCLASS_ARMOR))
        newattr := TabelaResistMod(material);
        newattr_escudo := TabelaValoresProtecao(tipo);

        attr["Atualiza"] := 1;

		attr["physicalmod"] := newattr[1];
		attr["firemod"] := newattr[2];
		attr["coldmod"] := newattr[3];
		attr["poisonmod"] := newattr[4];
		attr["energymod"] := newattr[5];
        attr["hpmod"] := newattr[6];

        if (newattr_escudo) //AS COMENTADAS JÁ EXISTEM EM OUTRA PROP EM OUTRO LUGAR. NÃO REMOVI PRA CASO DE PRECISAR REORGANIZAR FUTURAMENTE
            //attr["escudoResist"] := newattr_escudo[1]; 
            attr["escudoDexPen"] := newattr_escudo[2];
            //attr["escudoParry"] := newattr_escudo[3];
            //attr["escudoParryDelay"] := newattr_escudo[4];
        endif

        SetarProp(item, attr);
        //item.SetProp("atributos", attr);
    endif
endfunction

function PegarTipo(item)
    var tipo := PegarProp(item);
    tipo := tipo."TipoEquip";
    return tipo;
endfunction
function PegarProp(item)
    var prop := item.GetProp("atributos");
    return prop;
endfunction
function SetarProp(item, prop)
    item.SetProp("atributos", prop);
endfunction
function PegarPropExcep(item)
    var prop := item.GetProp("atributos_excp");
    return prop;
endfunction
function SetarPropExcep(item, prop)
    item.SetProp("atributos_excp", prop);
endfunction