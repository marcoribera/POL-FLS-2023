include ":attributes:advanceCheck";
include ":charactercreation:habilidades";
include ":attributes:attributes";

function CraftCheckSkill(who, craft_skill, difficulty, points, report:=0)

  difficulty := CDbl(difficulty);
  points := CDbl(points);
  if(difficulty == error)
    return 0;
  elseif(difficulty == 0.0)
    if (report)
      return 100;
    endif
    return 1;
  endif

  var chance;
  var effective := CDbl(AP_GetSkill(who, craft_skill));
  if(effective < 0)
    effective := 0.0;
  endif
  chance :=  35.0 + (effective - difficulty);

  if(chance < 0)
    chance := 0;
  elseif(chance > 100)
    chance := 100;
  endif

  if(report)
    return Cdbl(chance);
  endif

  if(chance >= 100)
    points := 0;
  endif
  if(points > 0)
//	CheckSkillAdvance(who, craft_skill, points, chance);
	SkillCheck(who, craft_skill, difficulty, points);
  endif
  if(RandomInt(100) < chance)
    if (report)
	return 100;
    endif
    return 1;
  else
    return 0;
  endif

endfunction


function ExceptionalCraftChance(who, skillvalue, skillreq, theitem)
  var chance := CDbl(skillvalue - skillreq) / 5.0; //Variação de 0% a 20% de chance
  //SendSysMessage(who, "who:"+who.name+" skillvalue:"+ skillvalue+" skillreq:"+ skillreq+ " theitem:" +theitem);
  if(chance > 0.0) //A diferença de skill entre o crafter e o necessário passa a ser o percentual de fazer excepcional
    if(TemHabilidade(who,"Maestria em Laminas") && (theitem.TipoAtaque == "Cortante"))
      chance := (chance * 5.0) + CDbl(GetObjProperty(who, "craftexcepmod"));
    endif

    if(TemHabilidade(who,"Maestria em Pontas") && (theitem.TipoAtaque == "Perfurante"))
      chance := (chance * 5.0) + CDbl(GetObjProperty(who, "craftexcepmod"));
    endif

    if(TemHabilidade(who,"Maestria em Impacto") && (theitem.TipoAtaque == "Contusivo"))
      chance := (chance * 5.0) + CDbl(GetObjProperty(who, "craftexcepmod"));
    endif

    if(TemHabilidade(who,"Maestria em Armaduras") && (theitem.TipoProtecao == "ArmaduraPesada" || theitem.TipoProtecao == "ArmaduraMedia" || theitem.TipoProtecao == "ArmaduraLeve"))
      chance := (chance * 5.0) + CDbl(GetObjProperty(who, "craftexcepmod"));
    endif

    if(TemHabilidade(who,"Maestria em Escudos") && (theitem.TipoProtecao == "EscudoPesado" || theitem.TipoProtecao == "EscudoMedio" || theitem.TipoProtecao == "EscudoLeve"))
      chance := (chance * 5.0) + CDbl(GetObjProperty(who, "craftexcepmod"));
    endif
  else
    chance := 0.0;
  endif
  //SendSysMessage(who, "Calculada chance de Excepcional:"+chance);
  return chance;
endfunction

function ExceptionalCraft( who, theitem, skillvalue, skillreq)
  var cfg:=ReadConfigFile(":combat:itemdesc");
  var elem := FindConfigElem(cfg, theitem.objtype);
  var chance := Cdbl(ExceptionalCraftChance(who, skillvalue, skillreq, elem));
  var teste := RandomFloat(100.0);
  //SendSysMessage(who, "Chance:"+chance+" Rolagem:"+teste);
  if(teste < chance)
    var margem := chance - teste;
    return 1.2 + (margem/50);
  else
    return 1.0;
  endif
endfunction