
function GetWoodType(tree)
    case (tree.objtype)
         0xcd6:
               return UOBJ_PINE_LOG; //pinheiro
         0xcd8:
                return UOBJ_PINE_LOG;
         0xcda:
                return UOBJ_OAK_LOG; //carvalho
         0xcdd:
                return UOBJ_OAK_LOG;
         0xce0:
                return UOBJ_WALNUT_LOG; //nogueira
         0xce3:
                return UOBJ_WALNUT_LOG;
         0xce6:
                return UOBJ_WILLOW_LOG; //salgueiro
         0xcf8:
                return UOBJ_CYPRESS_LOG;
         0xcfb:
                return UOBJ_CYPRESS_LOG;
         0xcfe:
                return UOBJ_CYPRESS_LOG;
         0xd01:
                return UOBJ_CYPRESS_LOG;
        0x309c:
                return 0x309c; // mogno
	 0x3fef: //naofunciona
	 0x3ff0: //naofunciona
	 0x3ff1: //naofunciona
	 0x3ff2: //naofunciona
	 0x3ff3: //naofunciona
	 0x3ff4: //naofunciona
	 0x3ff5: //naofunciona
	 0x3ff6: //naofunciona
		return 0xee3b; //ebano
	 0x2c0c: //naofunciona
	 0x2c0d: //naofunciona
	 0x2c10: //naofunciona
	 0x2c11: //naofunciona
	 0x2c12: //naofunciona
	 0x2c13: //naofunciona
	 0x2c14: //naofunciona
	 0x2c15: //naofunciona
	 0x2c17: //naofunciona
	 0x2c1c: //naofunciona
	 0x2c1f: //naofunciona
	 0x2c23: //naofunciona
		return 0xee3c; //cogumelo
       default: 
              return UOBJ_DEFAULT_LOG;
    endcase
endfunction
