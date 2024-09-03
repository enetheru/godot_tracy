#ifndef GODOT_TRACY_PROFILER_H
#define GODOT_TRACY_PROFILER_H

#include <core/string/ustring.h>

class Variant;

namespace tracy {
	CharString stringify_method(const String &p_method, const Variant **p_args, int p_argc);

}

#endif
