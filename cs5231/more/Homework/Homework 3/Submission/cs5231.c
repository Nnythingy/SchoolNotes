#define pr_fmt(fmt) "cs5231_lsm_hook: " fmt

// You can add linux header files you need
#include <linux/lsm_hooks.h>
#include <linux/security.h>
#include <linux/kernel.h>
#include <linux/err.h>
#include <linux/cred.h>
#include <linux/dcache.h>
#include <linux/binfmts.h>
#include <linux/string.h>
#include "cs5231.h"

#define BUFF_SIZE 512

/*
 * LSM info
 */

struct lsm_id cs5231_lsmid __lsm_ro_after_init = {
	.lsm  = "cs5231",
	.slot = LSMBLOB_NEEDED
};


/*
 * LSM hooks. You can add other hook functions whatever you need
 */

/**
 * cs5231_bprm_creds_for_exec - Set the credentials for a new task
 *
 * @bprm: The linux binary preparation structure
 *
 * returns 0 on success.
 */
static int cs5231_bprm_creds_for_exec(struct linux_binprm *bprm)
{
	if (!bprm)
		return 0;

    if (printk_ratelimit())
	    pr_info("Loaded bprm: %s\n", bprm->filename);
	return 0;
}

/**
 * cs5231_file_permission - Check permission for an file being opened
 *
 * @file: the file in question
 * @mask: the access requested
 *
 * This is the important access check hook
 *
 * returns 0 if access is granted, -EACCES otherwise
 *
 */
static int cs5231_file_permission(struct file *file, int mask)
{
	// Get current process name
	struct task_struct * cur_task = get_current();
	char * process_name = cur_task->comm;

	// Get accessed file information
	// char * file_name = file->f_path.dentry->d_name.name;
	char buff[BUFF_SIZE];
	char * file_path = dentry_path_raw(file->f_path.dentry, buff, BUFF_SIZE);

	int isMaliciousProg = strcmp(process_name, "malicious_prog") == 0;
	int isIfH = strcmp(file_path, "/usr/include/linux/if.h") == 0;
	int isUnH = strcmp(file_path, "/usr/include/linux/un.h") == 0;
	int isSensitiveFile = isIfH || isUnH;

	if (isMaliciousProg && isSensitiveFile) {
		pr_info("Sensitive file %s access is detected.\n", file_path);
		return -EACCES;
	}

	return 0;
}

/*
 * This is the current list of hooks that we will using for our security module.
 * If you need to add other hook functions, please fill you new added function into this 
 * `security_hook_list` by calling `LSM_HOOK_INIT`
 */
static struct security_hook_list cs5231_hooks[] = {
	LSM_HOOK_INIT(bprm_creds_for_exec, cs5231_bprm_creds_for_exec),
	LSM_HOOK_INIT(file_permission, cs5231_file_permission),
	/* Please init your hook functions (if needed) here: */
    // LSM_HOOK_INIT(hook_point, my_handler_function),
};

static __init int cs5231_init(void)
{
	pr_info("cs5231 LSM initializing..");

	/*
	 * Register the cs5231 hooks with lsm
	 */
	security_add_hooks(cs5231_hooks, ARRAY_SIZE(cs5231_hooks), &cs5231_lsmid);

	return 0;
}

/*
 * early registration with the kernel
 */
DEFINE_LSM(cs5231) = {
	.name = "cs5231",
	.init = cs5231_init,
};