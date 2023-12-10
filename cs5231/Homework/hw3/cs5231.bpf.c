#include <asm-generic/errno-base.h>  // EACCES definition
#include <vmlinux.h>
//#include <bpf/bpf_helper_defs.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h> 
#include <bpf/bpf_core_read.h> 

char LICENSE[] SEC("license") = "GPL";
const volatile int pid_target = 0;

// HINT: https://github.com/iovisor/bcc/blob/master/libbpf-tools/filetop.bpf.c
// HINT: The hook you are looking for starts with "file_".
// There are more than one hooks that can be used for this task.
int STRNCMP (const char *s1, const char *s2, size_t n) {
	unsigned char c1 = '\0';
	unsigned char c2 = '\0';
	if (n >= 4) {
		size_t n4 = n >> 2;
		do {
			c1 = (unsigned char) *s1++;
			c2 = (unsigned char) *s2++;
			if (c1 == '\0' || c1 != c2)
				return c1 - c2;
			c1 = (unsigned char) *s1++;
			c2 = (unsigned char) *s2++;
			if (c1 == '\0' || c1 != c2)
				return c1 - c2;
			c1 = (unsigned char) *s1++;
			c2 = (unsigned char) *s2++;
			if (c1 == '\0' || c1 != c2)
				return c1 - c2;
			c1 = (unsigned char) *s1++;
			c2 = (unsigned char) *s2++;
			if (c1 == '\0' || c1 != c2)
				return c1 - c2;
		} while (--n4 > 0);
		n &= 3;
	}
	while (n > 0) {
		c1 = (unsigned char) *s1++;
		c2 = (unsigned char) *s2++;
		if (c1 == '\0' || c1 != c2)
			return c1 - c2;
		n--;
	}
	return c1 - c2;
}

SEC("lsm/file_open")
int BPF_PROG(file_open, struct file *file, int mode) {
	char buf[50];
	struct qstr dname;
	struct task_struct *task;
	const char *sensitive_file1 = "if.h";
	const char *sensitive_file2 = "un.h";
	const char *prgm_to_prevent = "malicious-prog";
	char taskname[16]; //size of task_comm_len
	task = (struct task_struct *)bpf_get_current_task();
	bpf_core_read(&taskname, sizeof(taskname), &task->comm);
	if (STRNCMP(taskname, prgm_to_prevent, sizeof(prgm_to_prevent)) == 0) {
		// Get the filename
		dname = BPF_CORE_READ(file, f_path.dentry, d_name);
		bpf_probe_read_kernel(buf, sizeof(buf), dname.name);

		if (STRNCMP(buf, sensitive_file1, sizeof(sensitive_file1)) == 0 || STRNCMP(buf, sensitive_file2, sizeof(sensitive_file2)) == 0) {
			bpf_printk("Access to sensitive file %s is detected.\n", buf);
			// Return -EACCES to deny access
			return -EACCES;
		}
	}
	return 0;
}