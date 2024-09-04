#include "tracy_profiler.h"

#include "core/math/color.h"
#include "tracy/public/tracy/Tracy.hpp"
#include "tracy/public/tracy/TracyC.h"

#include <cstring>

TracyProfiler *TracyProfiler::singleton = nullptr;
#ifdef TRACY_ENABLE
static uint64_t context_to_id(const ___tracy_c_zone_context context) {
	static_assert(sizeof(___tracy_c_zone_context) == sizeof(uint64_t));
	// I want to use std::bit_cast, alas this is c++17.
	uint64_t godot_id;
	std::memcpy(&godot_id, &context, sizeof context);
	return godot_id;
}

static ___tracy_c_zone_context id_to_context(uint64_t godot_id) {
	static_assert(sizeof(___tracy_c_zone_context) == sizeof(uint64_t));
	// I want to use std::bit_cast, alas this is c++17.
	___tracy_c_zone_context context; // NOLINT(*-pro-type-member-init)
	std::memcpy(&context, &godot_id, sizeof godot_id);
	return context;
}
#endif

void TracyProfiler::_bind_methods() {
	ClassDB::bind_static_method("TracyProfiler", D_METHOD("zone_begin", "zone_name"), &TracyProfiler::zone_begin);
	ClassDB::bind_static_method("TracyProfiler", D_METHOD("zone_begin_v", "zone_name", "value"), &TracyProfiler::zone_begin_v);
	ClassDB::bind_static_method("TracyProfiler", D_METHOD("zone_begin_t", "zone_name", "text"), &TracyProfiler::zone_begin_t);
	ClassDB::bind_static_method("TracyProfiler", D_METHOD("zone_begin_tv", "zone_name", "text", "value"), &TracyProfiler::zone_begin_tv);
	ClassDB::bind_static_method("TracyProfiler", D_METHOD("zone_begin_c", "zone_name", "color"), &TracyProfiler::zone_begin_c);
	ClassDB::bind_static_method("TracyProfiler", D_METHOD("zone_begin_ct", "zone_name", "color", "text"), &TracyProfiler::zone_begin_ct);
	ClassDB::bind_static_method("TracyProfiler", D_METHOD("zone_begin_cv", "zone_name", "color", "value"), &TracyProfiler::zone_begin_cv);
	ClassDB::bind_static_method("TracyProfiler", D_METHOD("zone_begin_ctv", "zone_name", "color", "text", "value"), &TracyProfiler::zone_begin_ctv);
	ClassDB::bind_static_method("TracyProfiler", D_METHOD("zone_set_color", "zone_id", "color"), &TracyProfiler::zone_set_color);
	ClassDB::bind_static_method("TracyProfiler", D_METHOD("zone_set_text", "zone_id", "text"), &TracyProfiler::zone_set_text);
	ClassDB::bind_static_method("TracyProfiler", D_METHOD("zone_set_value", "zone_id", "value"), &TracyProfiler::zone_set_value);
	ClassDB::bind_static_method("TracyProfiler", D_METHOD("zone_end", "zone_id"), &TracyProfiler::zone_end);
	ClassDB::bind_static_method("TracyProfiler", D_METHOD("message", "text", "color"), &TracyProfiler::message, DEFVAL(Color()));
}

void TracyProfiler::init_singleton() {
	if (singleton == nullptr) {
		singleton = memnew(TracyProfiler);
	}
}

void TracyProfiler::finalize_singleton() {
	if (singleton) {
		memdelete(singleton);
		singleton = nullptr;
	}
}

TracyProfiler *TracyProfiler::get_singleton() {
	return singleton;
}

uint64_t TracyProfiler::zone_begin(const String &p_zone_name) {
#ifdef TRACY_ENABLE
	TracyCZone(const zone_id, true);

	const CharString c = p_zone_name.utf8();
	TracyCZoneName(zone_id, c, c.size())

	return context_to_id(zone_id);
#else
	return 0;
#endif
}

uint64_t TracyProfiler::zone_begin_v(const String &p_zone_name, const uint64_t p_value) {
#ifdef TRACY_ENABLE
	TracyCZone(const zone_id, true);

	const CharString c = p_zone_name.utf8();
	TracyCZoneName(zone_id, c, c.size());
	TracyCZoneValue(zone_id, p_value);

	return context_to_id(zone_id);
#else
	return 0;
#endif
}

uint64_t TracyProfiler::zone_begin_t(const String &p_zone_name, const String &p_text) {
#ifdef TRACY_ENABLE
	TracyCZone(const zone_id, true);

	const CharString c = p_zone_name.utf8();
	TracyCZoneName(zone_id, c, c.size());

	const CharString t = p_text.utf8();
	TracyCZoneText(zone_id, t, t.size());

	return context_to_id(zone_id);
#else
	return 0;
#endif
}

uint64_t TracyProfiler::zone_begin_tv(const String &p_zone_name, const String &p_text, const uint64_t p_value) {
#ifdef TRACY_ENABLE
	TracyCZone(const zone_id, true);

	const CharString c = p_zone_name.utf8();
	TracyCZoneName(zone_id, c, c.size());

	const CharString t = p_text.utf8();
	TracyCZoneText(zone_id, t, t.size());
	TracyCZoneValue(zone_id, p_value);

	return context_to_id(zone_id);
#else
	return 0;
#endif
}

uint64_t TracyProfiler::zone_begin_c(const String &p_zone_name, const Color &p_color) {
#ifdef TRACY_ENABLE
	TracyCZone(const zone_id, true);

	const CharString c = p_zone_name.utf8();
	TracyCZoneName(zone_id, c, c.size());

	TracyCZoneColor(zone_id,p_color.to_argb32());

	return context_to_id(zone_id);
#else
	return 0;
#endif
}

uint64_t TracyProfiler::zone_begin_ct(const String &p_zone_name, const Color &p_color, const String &p_text) {
#ifdef TRACY_ENABLE
	TracyCZone(const zone_id, true);

	const CharString c = p_zone_name.utf8();
	TracyCZoneName(zone_id, c, c.size());

	TracyCZoneColor(zone_id, p_color.to_argb32());
	const CharString t = p_text.utf8();
	TracyCZoneText(zone_id, t, t.size());

	return context_to_id(zone_id);
#else
	return 0;
#endif
}

uint64_t TracyProfiler::zone_begin_cv(const String &p_zone_name, const Color &p_color, const uint64_t p_value) {
#ifdef TRACY_ENABLE
	TracyCZone(const zone_id, true);

	const CharString c = p_zone_name.utf8();
	TracyCZoneName(zone_id, c, c.size());

	TracyCZoneColor(zone_id, p_color.to_argb32());
	TracyCZoneValue(zone_id, p_value);

	return context_to_id(zone_id);
#else
	return 0;
#endif
}

uint64_t TracyProfiler::zone_begin_ctv(const String &p_zone_name, const Color &p_color, const String &p_text, const uint64_t p_value) {
#ifdef TRACY_ENABLE
	TracyCZone(const zone_id, true);

	const CharString c = p_zone_name.utf8();
	TracyCZoneName(zone_id, c, c.size());

	TracyCZoneColor(zone_id, p_color.to_argb32());
	const CharString t = p_text.utf8();
	TracyCZoneText(zone_id, t, t.size());
	TracyCZoneValue(zone_id, p_value);

	return context_to_id(zone_id);
#else
	return 0;
#endif
}

void TracyProfiler::zone_set_color(const uint64_t p_zone_id, const Color &p_color) {
#ifdef TRACY_ENABLE
	TracyCZoneColor(id_to_context( p_zone_id ), p_color.to_argb32());
#endif
}

void TracyProfiler::zone_set_text(const uint64_t p_zone_id, const String &p_text) {
#ifdef TRACY_ENABLE
	const CharString c = p_text.utf8();
	TracyCZoneText(id_to_context( p_zone_id), c, c.size());
#endif
}

void TracyProfiler::zone_set_value(const uint64_t p_zone_id, const uint64_t p_value) {
#ifdef TRACY_ENABLE
	TracyCZoneValue(id_to_context(p_zone_id), p_value);
#endif
}

void TracyProfiler::zone_end(const uint64_t p_zone_id) {
#ifdef TRACY_ENABLE
	TracyCZoneEnd(id_to_context(p_zone_id));
#endif
}

void TracyProfiler::message(const String &p_text, const Color &p_color) {
#ifdef TRACY_ENABLE
	const CharString c = p_text.utf8();
	TracyCMessageC(c, c.size(), p_color.to_argb32());
#endif
}
