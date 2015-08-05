/*
 * fakelogin
 *
 * This program fakes a portion of the normal login process by
 * creating a `utmp` user database table entry and writing it to
 * `/run/utmp`. This does not allocate a TTY nor does it actually log
 * the user in, but adding the entry is enough to enable the
 * `getlogin()` family to return a username, instead of `NULL`.
 *
 * Alternatives to this include running `login -f root`, but as this
 * allocates a new tty, it does not work well with scripts, nor with
 * `docker run`.
 *
 * This is an implementation of the example in the `man 3 getutent`.
 *
 * Compile with `gcc -o fakelogin fakelogin.c`.
 * Tested on Ubuntu * 14.04.
 *
 * Andrew Schwartzmeyer <andschwa@microsoft.com>
 */

#include <string.h>
#include <stdlib.h>
#include <pwd.h>
#include <unistd.h>
#include <utmp.h>
#include <time.h>

int main() {
	struct utmp entry;

	entry.ut_type = USER_PROCESS;
	entry.ut_pid = getpid();
	strcpy(entry.ut_line, ttyname(STDIN_FILENO) + strlen("/dev/"));
	/* only correct for ptys named /dev/tty[pqr][0-9a-z] */
	strcpy(entry.ut_id, ttyname(STDIN_FILENO) + strlen("/dev/tty"));
	/* time(&entry.ut_time); */
	strcpy(entry.ut_user, getpwuid(getuid())->pw_name);
	memset(entry.ut_host, 0, UT_HOSTSIZE);
	entry.ut_addr = 0;
	setutent();
	pututline(&entry);

	return 0;
}
