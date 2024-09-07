#include "register_types.h"

#include "core/config/engine.h"
#include "tracy_profiler.h"

void initialize_tracy_module(ModuleInitializationLevel p_level) {
	if (p_level == ModuleInitializationLevel::MODULE_INITIALIZATION_LEVEL_CORE) {

		TracyProfiler::init_singleton();

	} else if (p_level == ModuleInitializationLevel::MODULE_INITIALIZATION_LEVEL_SERVERS) {
		ClassDB::register_class<TracyProfiler>();
		Engine::get_singleton()->add_singleton(Engine::Singleton("TracyProfiler", TracyProfiler::get_singleton()));
	}
}

void uninitialize_tracy_module(ModuleInitializationLevel p_level) {
	if (p_level == ModuleInitializationLevel::MODULE_INITIALIZATION_LEVEL_CORE) {
		TracyProfiler::finalize_singleton();
	}
}
