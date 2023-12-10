#include <linux/init.h> 
#include <linux/kernel.h> 
#include <linux/module.h>
#include <linux/sched/signal.h>
#include <linux/time.h>


MODULE_AUTHOR("CS5231_TAs"); 
MODULE_DESCRIPTION("CS5231_HelloWorld_loadable_kernel_module");
MODULE_LICENSE("Dual MIT/GPL"); 
MODULE_VERSION("0.1");


static int __init helloworld_lkm_init(void) {
    struct task_struct *tasks;
    int process_count = 0;

	printk(KERN_INFO "Hello, CS5231 Student!\n"); 

    // Traverse the process list
    for_each_process(tasks) {
        // Check if the process is running (not in a stopped state)
        if (get_current_state() == TASK_RUNNING) {
            process_count++;
        }
    }

    printk(KERN_INFO "Number of running processes: %d\n", process_count);

    //get time
    printk(KERN_INFO "Current Epoch time is %llu\n", ktime_get_real_seconds());
	return 0; // success
}

static void __exit helloworld_lkm_exit(void) { 
	printk(KERN_INFO "Goodbye, CS5231 Student!\n"); 
}

module_init(helloworld_lkm_init); 
module_exit(helloworld_lkm_exit);
