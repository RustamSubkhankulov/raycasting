#pragma once

//===================================================================

#define DEF_ERR(code, name, string) 								 \
																	 \
	name  = code,													 \

//===================================================================

enum errors {

	#include "../../codegen/err_descr.txt"
};

#undef DEF_ERR

