#include "shell.h"
#include "dbg.h"
#include <stdarg.h>

int Shell_exec(Shell template, ...)
{
	apr_pool_t *p = NULL;
	int rc = -1;
	apr_status_t rv = APR_SUCCESS;
	va_list argp;
	const char *key = NULL;
	const char *arg = NULL;
	int i = 0;
	int found = 0;
	int replaced = 0;
	int va_started = 0;

	rv = apr_pool_create(&p, NULL);
	check(rv == APR_SUCCESS, "Failed to create pool.");

	va_start(argp, template);
	va_started = 1;

	for(key = va_arg(argp, const char *); key != NULL; key = va_arg(argp, const char *))
	{
		arg = va_arg(argp, const char *);
		check(arg != NULL, "Missing value for replacement key: %s", key);
		found = 0;
		for(i = 0; template.args[i] != NULL; i++) {
			if(strcmp(template.args[i], key) == 0) {
					template.args[i] = arg;
					found = 1;
					replaced++;
					break;
					}
		}
		check(found, "Unkown replacement key: %s", key);

	}
	check(replaced == template.replace_count,
			"Wrong number of replacements for %s: expected %d, got %d.",
			template.exe, template.replace_count, replaced);
	rc = Shell_run(p, &template);
	apr_pool_destroy(p);
	va_end(argp);
	return rc;

error:
	if(va_started) va_end(argp);
	if(p) apr_pool_destroy(p);
	return rc;
}

int Shell_run(apr_pool_t *p, Shell *cmd)
{
	apr_procattr_t *attr;
	apr_status_t rv;
	apr_proc_t newproc;

	rv = apr_procattr_create(&attr, p);
	check(rv == APR_SUCCESS, "Failed to create proc attr.");

	rv = apr_procattr_io_set(attr, APR_NO_PIPE, APR_NO_PIPE, APR_NO_PIPE);
	check(rv == APR_SUCCESS, "Failed to set IO of command.");

	rv = apr_procattr_dir_set(attr, cmd->dir);
	check(rv == APR_SUCCESS, "Failed to set root to %s", cmd->dir);

	rv = apr_procattr_cmdtype_set(attr, APR_PROGRAM_PATH);
	check(rv == APR_SUCCESS, "Failed to set cmd type.");

	rv = apr_proc_create(&newproc, cmd->exe, cmd->args, NULL, attr, p);
	check(rv == APR_SUCCESS, "Failed to run command.");

	rv = apr_proc_wait(&newproc, &cmd->exit_code, &cmd->exit_why, APR_WAIT);
	check(rv == APR_CHILD_DONE, "Failed to wait");

	check(cmd->exit_code == 0, "%s exited badly.", cmd->exe);
	check(cmd->exit_why == APR_PROC_EXIT, "%s was killed or crashed.", cmd->exe);

	return 0;

error:
	return -1;
}

Shell CLEANUP_SH = {
	.exe = "rm",
	.dir = "/tmp",
	.replace_count = 0,
	.args = {"rm", "-rf", "/tmp/pkg-build", "/tmp/pkg-src.tar.gz",
		"/tmp/pkg-src.tar.bz2", "/tmp/DEPENDS", NULL}
};

Shell GIT_SH = {
	.exe = "git",
	.dir = "/tmp",
	.replace_count = 1,
	.args = {"git", "clone", "URL", "pkg-build", NULL}
};

Shell TAR_SH = {
	.exe = "tar",
	.dir = "/tmp/pkg-build",
	.replace_count = 1,
	.args = {"tar", "-xzf", "FILE", "--strip-comments", "1", NULL}
};

Shell CURL_SH = {
	.exe = "curl",
	.dir = "/tmp",
	.replace_count = 2,
	.args = {"curl", "-L", "-o", "TARGET", "URL", NULL}
};

Shell CONFIGURE_SH = {
	.exe = "./configure",
	.dir = "/tmp/pkg-build",
	.replace_count = 1,
	.args = {"configure", "OPTS", NULL}
};

Shell MAKE_SH = {
	.exe = "make",
	.dir = "/tmp/pkg-build",
	.replace_count = 1,
	.args = {"make", "OPTS", NULL}
};

Shell INSTALL_SH = {
	.exe = "sudo",
	.dir = "/tmp/pkg-build",
	.replace_count = 1,
	.args = {"sudo", "make", "TARGET", NULL}
};


