#!/usr/bin/python
# Copyright (c) PLUMgrid, Inc.
# Licensed under the Apache License, Version 2.0 (the "License")

from __future__ import print_function
from bcc import BPF
from bcc.utils import printb

REQ_WRITE = 1		# from include/linux/blk_types.h

# load BPF program
bpf_text="""
#include <uapi/linux/ptrace.h>
#include <uapi/linux/limits.h>
#include <linux/fs_struct.h>
#include <linux/dcache.h>
#include <linux/sched.h>
#include <linux/path.h>

static long MY_STRNCMP(char *s1, size_t n, const char *s2) {
  unsigned char c1 = '\\0';
  unsigned char c2 = '\\0';
  if (n >= 4) {
      size_t n4 = n >> 2;
      do {
	  c1 = (unsigned char) *s1++;
	  c2 = (unsigned char) *s2++;
	  if (c1 == '\\0' || c1 != c2)
	    return c1 - c2;
	  c1 = (unsigned char) *s1++;
	  c2 = (unsigned char) *s2++;
	  if (c1 == '\\0' || c1 != c2)
	    return c1 - c2;
	  c1 = (unsigned char) *s1++;
	  c2 = (unsigned char) *s2++;
	  if (c1 == '\\0' || c1 != c2)
	    return c1 - c2;
	  c1 = (unsigned char) *s1++;
	  c2 = (unsigned char) *s2++;
	  if (c1 == '\\0' || c1 != c2)
	    return c1 - c2;
	} while (--n4 > 0);
      n &= 3;
    }
  while (n > 0) {
      c1 = (unsigned char) *s1++;
      c2 = (unsigned char) *s2++;
      if (c1 == '\\0' || c1 != c2)
	return c1 - c2;
      n--;
    }
  return c1 - c2;
}

static void check_path(char *comm, struct dentry *working_dentry, char *filename) {
    char full_path[22] = "/home/student/secret/";
    char home_path[16] = "student/secret/";
    char stu_path[8] = "secret/";
    char name[64];

    bpf_probe_read_kernel(name, sizeof(name), working_dentry->d_name.name);

    if (filename[0] == '/') { //file path is absolute
        //program directly opening with absolute path
        long match = MY_STRNCMP(filename, sizeof(full_path)-1, full_path);
        if (match == 0) {
            bpf_trace_printk("%s has accessed %s from %s directory\\n", comm, filename, name);
        }
    } else if (MY_STRNCMP(name, sizeof("home"), "home") == 0) {
        long match = MY_STRNCMP(filename, sizeof(home_path)-1, home_path);
        if (match == 0) {
            char parent[10];
            bpf_probe_read_kernel(parent, sizeof(parent), working_dentry->d_parent->d_name.name);
            match = MY_STRNCMP(parent, 1, "/");
            if (match == 0) {
                bpf_trace_printk("%s has accessed %s from %s directory\\n", comm, filename, name);
            }
        }
    } else if (MY_STRNCMP(name, sizeof("student"), "student") == 0) {
        long match = MY_STRNCMP(filename, sizeof(stu_path)-1, stu_path);
        if (match == 0) {
            char parent[10];
            bpf_probe_read_kernel(parent, sizeof(parent), working_dentry->d_parent->d_name.name);
            if (MY_STRNCMP(parent, sizeof("home"), "home") == 0) {
                bpf_trace_printk("%s has accessed %s from %s directory\\n", comm, filename, name);
            }
        }
    } else if (MY_STRNCMP(name, sizeof("secret"), "secret") == 0) {
        //current directory is in the 'secure' folder
        //hence the filename will only have the file being read
        char parent[10];
        bpf_probe_read_kernel(parent, sizeof(parent), working_dentry->d_parent->d_name.name);
        working_dentry = working_dentry->d_parent;
        if (MY_STRNCMP(parent, sizeof("student"), "student") == 0) {
            char parentparent[10];
            bpf_probe_read_kernel(parentparent, sizeof(parentparent), working_dentry->d_parent->d_name.name);
            if (MY_STRNCMP(parentparent, sizeof("home"), "home") == 0) {
                bpf_trace_printk("%s has accessed %s from %s directory\\n", comm, filename, name);
            }
        }
    } else {
        //a program is accessing a secret folder from a relative path
        //to try and catch programs like cat ../../secret/secret.txt
        for (int i = 0; i < sizeof(filename); i++) {
            if (MY_STRNCMP(filename + i, sizeof(stu_path)-1, stu_path) == 0) {
                bpf_trace_printk("%s has accessed %s from %s directory\\n", comm, filename, name);
                break;
            }
        }
    }
}

int syscall__openat_entry(struct pt_regs *ctx, int dfd, const char __user *filename, int flags) {
    char comm[64];
    struct task_struct *task;
    struct dentry *working_dentry;

    task = bpf_get_current_task();
    working_dentry = task->fs->pwd.dentry;
    bpf_get_current_comm(&comm, sizeof(comm));

    check_path(comm, working_dentry, filename);
    return 0;
};
"""

b = BPF(text=bpf_text)
b.attach_kprobe(event=b.get_syscall_fnname("openat"), fn_name="syscall__openat_entry")

while 1:
    try:
        (task, pid, cpu, flags, ts, msg) = b.trace_fields()
    except ValueError:
        continue
    except KeyboardInterrupt:
        exit()
    printb(b"%-18.9f %-16s %-6d %s" % (ts, task, pid, msg))