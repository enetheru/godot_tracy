#include "profiler.h"

#include <core/variant/variant.h>

#include <limits>

namespace tracy {

String stringify_method(const String &p_method, const Variant **p_args, const int p_argc) {
	String out = p_method;
	out += "(";
	for (int i = 0; i < p_argc; i += 1) {
		if (i != 0) {
			out += ", ";
		}
		out += p_args[i]->operator String();
	}
	if (out.length() >= 256) {
		out.resize( 256 );
		out += " ... )";
	} else {
		out += ")";
	}
	return out;
}

}
