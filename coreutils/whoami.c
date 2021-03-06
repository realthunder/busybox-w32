/* vi: set sw=4 ts=4: */
/*
 * Mini whoami implementation for busybox
 *
 * Copyright (C) 2000  Edward Betts <edward@debian.org>.
 *
 * Licensed under GPLv2 or later, see file LICENSE in this source tree.
 */

/* BB_AUDIT SUSv3 N/A -- Matches GNU behavior. */

#include "libbb.h"

/* This is a NOFORK applet. Be very careful! */

int whoami_main(int argc, char **argv) MAIN_EXTERNALLY_VISIBLE;
int whoami_main(int argc UNUSED_PARAM, char **argv UNUSED_PARAM)
{
#if ENABLE_PLATFORM_MINGW32
	char buf[64];
	DWORD len = 64;
#endif

	if (argv[1])
		bb_show_usage();

#if ENABLE_PLATFORM_MINGW32
	GetUserName(buf, &len);
	puts(buf);
#else
	/* Will complain and die if username not found */
	puts(xuid2uname(geteuid()));
#endif

	return fflush_all();
}
