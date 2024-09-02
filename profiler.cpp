#include "profiler.h"

#include "core/variant/variant.h"

CharString Profiler ::stringify_method(const StringName &p_method, const Variant **p_args, const int p_argc) {
#ifdef TRACY_ENABLE
	String out = p_method;
	out += "(";
	for (int i = 0; i < p_argc; i += 1) {
		if (i != 0) {
			out += ", ";
		}
		out += p_args[i]->operator String();
	}
	out += ")";
	CharString c = out.utf8();
	if (c.size() >= std::numeric_limits<uint16_t>::max()) {
		c.resize(std::numeric_limits<uint16_t>::max() - 1);
	}
	return c;
#else
	return CharString();
#endif
}
