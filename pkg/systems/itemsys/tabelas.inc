///////////////////////////////
///// NOVO ".CFG" - START /////
///////////////////////////////
function TabelaMaterialResistMod(item) //objtype do material: return {FISICO, FIRE, COLD, POISON, ENERGY, HP}
    var material := Lower(Hex(item.GetProp("material")));
    case(material)
        //////////METAL
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
        "0x6603": return {-1,0,0,0,0,-30}; //CRISTALITH
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
        "0x699b": return {5,6,6,6,6,60}; //ORICALCUM

        //////////COURO
        //TIER 1
        "0xee45": return {0,0,0,0,0,0}; //CURTIDO
        "0xef24": return {1,0,0,0,0,10}; //PELUDO

        //TIER 2
        "0xef21": return {2,2,0,0,0,20}; //ESPESSO
        "0xef26": return {2,0,2,0,0,20}; //POLAR
        "0xef20": return {2,0,0,2,0,20}; //ESCAMOSO
        "0xef22": return {2,0,0,0,2,20}; //ANFIBIO

        //TIER 3
        "0xc601": return {3,3,0,0,0,30}; //OGRO
        "0xc602": return {3,0,3,0,0,30}; //MARINHO
        "0xc603": return {3,0,0,3,0,30}; //REPTILIANO
        "0xc604": return {3,0,0,0,3,30}; //HIDRA

        //TIER 4
        "0xed29": return {4,4,0,0,0,40}; //DRACONIANO
        "0xef25": return {4,0,4,0,0,40}; //TROLL
        "0xef28": return {4,0,0,4,0,40}; //TERATHAN
        "0xef27": return {4,0,0,0,4,40}; //GIGANTE

        //TIER 5
        "0xef23": return {5,0,3,0,3,50}; //ASPERO
        "0xc605": return {5,3,0,3,0,50}; //NEGRO

        //////////OSSO
        //TIER 1
        "0xf7e": return {0,0,0,0,0,0}; //OSSO
        "0xef32": return {1,0,0,1,0,10}; //CINZA

        //TIER 2
        "0xef30": return {2,0,0,0,2,20}; //VERMELHO
        "0xef31": return {2,0,0,2,0,20}; //PRETO

        //TIER 3
        "0xef38": return {3,0,0,0,3,30}; //LICH
        "0xef39": return {3,0,0,3,0,30}; //REPTILIANO

        //TIER 4
        "0xef3a": return {4,4,0,0,0,40}; //GIGANTE
        "0xef3b": return {4,0,4,0,0,40}; //TERATHAN

        //TIER 5
        "0xef29": return {5,0,0,5,5,50}; //DEMONÍACO

        //////////TECIDO
        //TIER 1
        "0x1765": return {0,0,0,0,0,10}; //LÃ
        "0x1764": return {0,0,0,0,0,20}; //ALGODÃO

        //TIER 2
        "0xf92": return {1,0,0,0,0,30}; //SEDA
        "0xf9f": return {0,1,0,0,0,30}; //LINHO

        //TIER 3
        "0xfa2": return {0,0,0,0,3,40}; //MALVA
        "0xfad": return {0,0,0,3,0,40}; //SISAL
        "0xfaf": return {0,0,3,0,0,40}; //DENIM
        "0xfb2": return {0,3,0,0,0,40}; //RAMI

        //TIER 4
        "0xfb7": return {0,2,0,2,0,50}; //FLAMEL
        "0xfbd": return {0,0,2,0,2,50}; //RAJAL
    endcase
endfunction

function TabelaMaterialDamageMod(item) //objtype do material: return {FISICO, FIRE, COLD, POISON, ENERGY, HP}
    var material := Lower(Hex(item.GetProp("material")));

    case(material)
        //////////METAL
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
        "0x630d": return {-20,40,0,0,0,20}; //FIGIN
        "0x6460": return {-20,0,40,0,0,20}; //ARGONIL
        "0x630c": return {-20,0,0,40,0,20}; //SINQUE
        "0x630b": return {-20,0,0,0,40,20}; //HELCE
        "0x6602": return {-10,0,0,0,0,20}; //ACIELITH
        "0x6603": return {10,0,0,0,0,-30}; //CRITALITH
        "0x6601": return {0,0,0,0,0,80}; //STALITH

        //TIER 3
        "0x6310": return {0,0,0,0,0,0}; //GALVORN
        "0x6605": return {-30,60,0,0,0,30}; //IGNARILITH
        "0x6606": return {-30,0,60,0,0,30}; //GLACIALITH
        "0x6607": return {-30,0,0,60,0,30}; //VENERILITH
        "0x6608": return {-30,0,0,0,60,30}; //ENERLITH
        "0x6604": return {-20,0,0,0,50,30}; //PLATINUM
        "0x6609": return {10,0,0,0,5,-40}; //LUNIUM
        "0x6610": return {20,0,0,0,0,-30}; //CELERIUM

        //TIER 4
        "0x6997": return {-40,80,0,0,0,40}; //SOLIUM
        "0x699a": return {-40,0,80,0,0,40}; //ICELUM
        "0x6999": return {-40,0,0,80,0,40}; //HISSIUM
        "0x6998": return {-40,0,0,0,80,40}; //TESLIUM
        "0x6311": return {-40,20,20,20,20,50}; //MITHRIL
        
        //TIER 5
        "0x699b": return {10,10,10,10,10,60}; //ORICALCUM
        
        /* ---------------- NÃO FAZ ARMA
        //////////COURO
        //TIER 1
        "0xee45": return {0,0,0,0,0}; //CURTIDO
        "0xef24": return {0,0,0,0,0}; //PELUDO

        //TIER 2
        "0xef21": return {0,0,0,0,0}; //ESPESSO
        "0xef26": return {0,0,0,0,0}; //POLAR
        "0xef20": return {0,0,0,0,0}; //ESCAMOSO
        "0xef22": return {0,0,0,0,0}; //ANFIBIO

        //TIER 3
        "0xc601": return {0,0,0,0,0}; //OGRO
        "0xc602": return {0,0,0,0,0}; //MARINHO
        "0xc603": return {0,0,0,0,0}; //REPTILIANO
        "0xc604": return {0,0,0,0,0}; //HIDRA

        //TIER 4
        "0xed29": return {0,0,0,0,0}; //DRACONIANO
        "0xef25": return {0,0,0,0,0}; //TROLL
        "0xef28": return {0,0,0,0,0}; //TERATHAN
        "0xef27": return {0,0,0,0,0}; //GIGANTE

        //TIER 5
        "0xef23": return {0,0,0,0,0}; //ASPERO
        "0xc605": return {0,0,0,0,0}; //NEGRO
        */

        /* ---------------- NÃO FAZ ARMA
        //////////OSSO
        //TIER 1
        "0xF7e": return {0,0,0,0,0}; //OSSO
        "0xef32": return {0,0,0,0,0}; //CINZA

        //TIER 2
        "0xef30": return {0,0,0,0,0}; //VERMELHO
        "0xef31": return {0,0,0,0,0}; //PRETO
        "0xef38": return {0,0,0,0,0}; //LICH
        "0xef39": return {0,0,0,0,0}; //REPTILIANO

        //TIER 4
        "0xef3a": return {0,0,0,0,0}; //GIGANTE
        "0xef3b": return {0,0,0,0,0}; //TERATHAN

        //TIER 5
        "0xef29": return {0,0,0,0,0}; //DEMONÍACO
        */

        /* ---------------- NÃO FAZ ARMA
        //////////TECIDO
        //TIER 1
        "0x1765": return {0,0,0,0,0}; //LÃ
        "0x1764": return {0,0,0,0,0}; //ALGODÃO

        //TIER 2
        "0xf92": return {0,0,0,0,0}; //SEDA
        "0xf9f": return {0,0,0,0,0}; //LINHO

        //TIER 3
        "0xfa2": return {0,0,0,0,0}; //MALVA
        "0xfad": return {0,0,0,0,0}; //SISAL
        "0xfaf": return {0,0,0,0,0}; //DENIM
        "0xfb2": return {0,0,0,0,0}; //RAMI

        //TIER 4
        "0xfb7": return {0,0,0,0,0}; //FLAMEL
        "0xfbd": return {0,0,0,0,0}; //RAJAL
        */
    endcase
endfunction

function TabelaDanos(item) //FUTURAMENTE TROCAR POR UMA LISTA DE ITENS SEMELHANTE ÀS TABELAS ANTERIORES OU A POSTERIOR
    var cfg := ReadConfigFile(":combat:itemdesc");
    var elem := FindConfigElem(cfg, item.objtype);
    var dano := Array;
    dano.append(elem.Damage);
    dano.append(elem.PhysicalDamage);
    dano.append(elem.FireDamage);
    dano.append(elem.ColdDamage);
    dano.append(elem.PoisonDamage);
    dano.append(elem.EnergyDamage);

    return dano;
endfunction
function TabelaProtecao(item)
    var tipo := Lower(PegarTipo(item));
    case(tipo) //ARMADURAS: -=> TipoProtecao: return {FISICO, FIRE, COLD, POISON, ENERGY}
        //TIER 1
        "armadura leve fraca": return {0,0,0,0,0};
        "armadura leve media": return {1,1,1,1,1};
        "armadura leve forte": return {2,2,2,2,2};

        //TIER 2
        "armadura media fraca": return {3,0,0,0,0};
        "armadura media media": return {4,0,0,0,0};
        "armadura media forte": return {5,0,0,0,0};

        //TIER 3
        "armadura pesada fraca": return {6,0,0,0,0};
        "armadura pesada media": return {7,0,0,0,0};
        "armadura pesada forte": return {8,0,0,0,0};
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
function TabelaSlot(item)
    var slot := Lower(PegarSlot(item));

    case(slot) //[1] = ResistBase; [2] = DexPenalty
        "head": return {1,-1};
        "neck": return {1,-1};
        "body": return {4,-3};
        "arms": return {2,-2};
        "hands": return {1,-1};
        "legs/feet": return {3,-2};
        "shield": return {2,-1};
    endcase
endfunction
///////////////////////////
///// NOVO .CFG - END /////
///////////////////////////