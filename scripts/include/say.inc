use uo;
use unicode;

const SSM_FAIL := 37;
const SSM_REQUEST := 168;
const SSM_INFO := 91;
const SSM_HELPFU := 168;
const SSM_HARMFUL := 37;
const SSM_INFO_IC := 55;
const SSM_INFO_OOC := 91;
const SSM_INFO_DEBUG := 946;//1901;
const SSM_GM_NOTICE := 2001;

function SendSysMessageEX(who, message, SSM_TYPE := _DEFAULT_TEXT_COLOR, font_number := _DEFAULT_TEXT_FONT)
	SendSysMessage(who, ""+message, font_number, SSM_TYPE);
endfunction

function SendSysMessageUNI(above_object, uc_text, color:=_DEFAULT_UCCOLOR, font:=_DEFAULT_UCFONT, langcode := "ENG")
  if (uc_text == error)
	return;
  endif
  return SendSysMessageUC(above_object, UC(uc_text), langcode, font, color);
endfunction

function PrintText(above_object, uc_text, color := _DEFAULT_UCCOLOR, font := _DEFAULT_UCFONT, langcode := "ENG")
  if (uc_text == error)
	return;
  endif
  if (above_object.concealed || above_object.hidden)
	return 1;
  endif
  return PrintTextAboveUC(above_object, UC(uc_text), langcode, font, color);
endfunction

function UC(strs)
  var result := array {};
  if (TypeOf(strs) != "Array")
    result := CAscZ(CStr(strs));
  else
    foreach str in (strs)
      if (TypeOf(str) != "Array")
        str := CAscZ(CStr(str));
      endif
      result := result + str;     // POL 2003-06-19 or later required for this operation
/*      foreach elem in (str)
        result.append(elem); 
      endforeach */
    endforeach
  endif
  return result;
endfunction
