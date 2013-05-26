#ifndef PGNMGLOBALS_H
#define PGNMGLOBALS_H

#ifdef _MSC_VER
#	ifdef	PGNM_LIB
#			define PGNM_EXPORT __declspec(dllexport)
#	else
#			define PGNM_EXPORT __declspec(dllimport)
#endif
#else
#	define PGNM_EXPORT
#endif

#endif // PGNMGLOBALS_H