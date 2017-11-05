#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <sys/param.h>
#include <sys/file.h>
#include <unistd.h>

#ifdef __APPLE__
#include <libproc.h>
#endif

#if defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__DragonFly__)
#include <sys/sysctl.h>
#include <sys/types.h>
#include <sys/user.h>
#endif

#ifdef __FreeBSD__
#include <libutil.h>
#endif

#if defined(WINDOWS) || defined(_WIN32) || defined(__CYGWIN__)
#include <windows.h>
#endif

const char PATHDIV = '/';

char *getExecutablePath(char *buf, size_t len) {
	char *p;
  #ifdef __APPLE__
	unsigned int l = len;
	if (_NSGetExecutablePath(buf, &l) != 0)
	  return nullptr;
  #elif defined(__FreeBSD__) || defined(__DragonFly__)
	int mib[4] = { CTL_KERN, KERN_PROC, KERN_PROC_PATHNAME, -1 };
	size_t l = len;
	if (sysctl(mib, 4, buf, &l, nullptr, 0) != 0)
	  return nullptr;
  #elif defined(__OpenBSD__)
	int mib[4] = {CTL_KERN, KERN_PROC_ARGS, getpid(), KERN_PROC_ARGV};
	char **argv;
	size_t l;
	const char *comm;
	int ok = 0;
	if (sysctl(mib, 4, NULL, &l, NULL, 0) < 0)
	  abort();
	argv = new char *[l];
	if (sysctl(mib, 4, argv, &l, NULL, 0) < 0)
	  abort();
	comm = argv[0];
	if (*comm == '/' || *comm == '.') {
	  char *rpath;
	  if ((rpath = realpath(comm, NULL))) {
		strlcpy(buf, rpath, len);
		free(rpath);
		ok = 1;
	  }
	} else {
	  char *sp;
	  char *xpath = strdup(getenv("PATH"));
	  char *path = strtok_r(xpath, ":", &sp);
	  struct stat st;
	  if (!xpath)
		abort();
	  while (path) {
		snprintf(buf, len, "%s/%s", path, comm);
		if (!stat(buf, &st) && (st.st_mode & S_IXUSR)) {
		  ok = 1;
		  break;
		}
		path = strtok_r(NULL, ":", &sp);
	  }
	  free(xpath);
	}
	if (ok)
	  l = strlen(buf);
	else
	  l = 0;
	delete[] argv;
  #elif defined(WINDOWS) || defined(_WIN32) || defined(__CYGWIN__)
	unsigned int l = 0;
	char full_path[MAX_PATH];

	l = GetModuleFileName(NULL, full_path, MAX_PATH);

	while (p = strchr(full_path, '\\')) *p = PATHDIV;
	if (p = strchr(full_path, ':')) *p = PATHDIV;
	snprintf(buf, len, "%c%s%c%s", PATHDIV, "cygdrive", PATHDIV, full_path);
  #else
	ssize_t l = readlink("/proc/self/exe", buf, len - 1);
	assert(l > 0 && "/proc not mounted?");
	if (l > 0) buf[l] = '\0';
  #endif
	if (l <= 0)
	  return NULL;
	buf[len - 1] = '\0';
        // remove the name, but keep the path delimiter !!
        p = strrchr(buf, PATHDIV);
	if (p)
	  *++p = '\0';
	return buf;
}

char *getLibraryPath(char *buf, size_t len) {
	char *p;
        char exe_path[MAXPATHLEN];
	//char full_path[MAX_PATH];
        //char *prefix;

        getExecutablePath(exe_path, MAXPATHLEN);

        p = buf;
        snprintf(p, MAX_PATH, "%s../../lib/powerpc-darwin", exe_path);
        /*
        p = full_path;
        snprintf(p, MAX_PATH, "%s../../lib/powerpc-darwin/MacOSX10.4u.sdk", exe_path);
        (void)printf("donalf: library path: %s\n",full_path);
	prefix = realpath(p, buf);
        */
	return buf;
}
