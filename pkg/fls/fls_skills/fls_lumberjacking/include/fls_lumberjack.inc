
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
	 0x3fef:
	 0x3ff0:
	 0x3ff1:
	 0x3ff2:
	 0x3ff3:
	 0x3ff4:
	 0x3ff5:
	 0x3ff6:
		return 0xee3b;
	 0x2c0c:
	 0x2c0d:
	 0x2c10:
	 0x2c11:
	 0x2c12:
	 0x2c13:
	 0x2c14:
	 0x2c15:
	 0x2c17:
	 0x2c1c:
	 0x2c1f:
	 0x2c23:
		return 0xee3c;
         default: 
                return UOBJ_DEFAULT_LOG;
    endcase
endfunction
