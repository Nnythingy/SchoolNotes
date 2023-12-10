#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched/signal.h>

MODULE_AUTHOR("CS5231_TAs");
MODULE_DESCRIPTION("CS5231_HelloWorld_loadable_kernel_module");
MODULE_LICENSE("Dual MIT/GPL");
MODULE_VERSION("0.1");

static int __init helloworld_lkm_init(void) {
    size_t processes;
    struct task_struct* task_list;
    time64_t seconds;

    printk(KERN_INFO "Hello, CS5231 Student!\n");

    // Print number of processes running in the system
    processes = 0;
    for_each_process(task_list) {
        processes++;
    }
    printk(KERN_INFO "Number of process: %zu\n", processes);

    // Print current time in seconds since epoch
    seconds = ktime_get_real_seconds();
    printk(KERN_INFO "Current time: %llu\n", seconds);

    return 0;
}

static void __exit helloworld_lkm_exit(void) {
    printk(KERN_INFO "Goodbye, CS5231 Student!\n");
}

module_init(helloworld_lkm_init);
module_exit(helloworld_lkm_exit);
