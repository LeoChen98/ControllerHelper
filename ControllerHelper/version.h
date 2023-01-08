#pragma once

#ifdef _DEBUG
#define PLUGIN_VERSION "Debug build: %%COMMIT_HASH%%"
#else
#define PLUGIN_VERSION "%%COMMIT_HASH%%"
#endif // DEBUG
