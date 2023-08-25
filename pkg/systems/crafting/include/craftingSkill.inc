include ":attributes:advanceCheck";

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


function ExceptionalCraft( who, aidskill)

  var chance := Cint(aidskill/20 ) + cint(GetObjProperty(who, "craftexcepmod"));

  if(RandomInt(100) < chance)
    return 1;
  else
    return 0;
  endif

endfunction
