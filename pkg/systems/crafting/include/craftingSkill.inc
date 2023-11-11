include ":attributes:advanceCheck";
include ":charactercreation:habilidades";
include ":attributes:attributes";

function CraftCheckSkill(who, craft_skill, difficulty, points, report:=0)

  //difficulty := CDbl(difficulty);
  //points := CDbl(points);
  //if(difficulty == error)
  /*
  elseif(difficulty == 0.0)
    if (report)
      return 100;
    endif
    return 1;
  endif
  */
  
  var chance;
  var effective := CDbl(AP_GetSkill(who, craft_skill));
  /*
  if(effective < 0)
    effective := 0.0;
  endif
  */
  //chance :=  35.0 + (effective - difficulty); //antigo craft
  if ((difficulty - effective) <= -20 ) //PREVENÇÃO DA PARÁBOLA
    chance := 100;
  elseif ((difficulty - effective) <= -10 )
    chance := 50;
  else
    chance := ((difficulty-10)-effective)*(-(difficulty/10));
  endif
  SendSysMessage(who, "DEBUG: VALORES: DIFFI" +difficulty+ "- EFFEC: " +effective+ "- CHANCE: " +chance);
/*
  if(chance < 0)
    chance := 0;
  elseif(chance > 100)
    chance := 100;
  endif
*/
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


function ExceptionalCraftChance(who, skillname, skillvalue, skillreq, theitem)
  var chance := CDbl(skillvalue - skillreq) / 5.0; //Variação de 0% a 20% de chance
  //SendSysMessage(who, "who:"+who.name+" skillvalue:"+ skillvalue+" skillreq:"+ skillreq+ " theitem:" +theitem);
  if(chance > 0.0) //A diferença de skill entre o crafter e o necessário passa a ser o percentual de fazer excepcional
    if(skillname == "MetalWorking")
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
    elseif(skillname == "WoodWorking")
      if(TemHabilidade(who,"Carpintaria Combativa"))
        chance := (chance * 5.0) + CDbl(GetObjProperty(who, "craftexcepmod"));
      endif
      if(TemHabilidade(who,"Mobiliario Exclusivo") && !theitem.isa(POLCLASS_WEAPON) && !theitem.isa(POLCLASS_ARMOR))
        chance := 100.0;
      endif
    elseif(skillname == "DomesticWork")
      if((CInt(theitem.resist_physical)==0)) //Não é armadura
        if(TemHabilidade(who,"Maestria em Alfaiataria"))
          chance := (chance * 5.0) + CDbl(GetObjProperty(who, "craftexcepmod"));
        endif
      else
        if(TemHabilidade(who,"Maestria em Curticao") && (theitem.TipoProtecao == "ArmaduraPesada" || theitem.TipoProtecao == "ArmaduraMedia" || theitem.TipoProtecao == "ArmaduraLeve"))
          chance := (chance * 5.0) + CDbl(GetObjProperty(who, "craftexcepmod"));
        endif
      endif
    endif
  else
    chance := 0.0;
  endif
  //SendSysMessage(who, "Calculada chance de Excepcional:"+chance);
  return chance;
endfunction

function ExceptionalCraft( who, skillname, theitem, skillvalue, skillreq)
  var cfg:=ReadConfigFile(":combat:itemdesc");
  var elem := FindConfigElem(cfg, theitem.objtype);
  var chance := Cdbl(ExceptionalCraftChance(who, skillname, skillvalue, skillreq, elem));
  var teste := RandomFloat(100.0);
  //SendSysMessage(who, "Chance:"+chance+" Rolagem:"+teste);
  if(teste < chance)
    var margem := chance - teste;
    return 1.2 + (margem/50);
  else
    return 1.0;
  endif
endfunction