#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/kthread.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Fleur de Nanteuil");
MODULE_DESCRIPTION("TP3 de LDI - Création de 2 threads du noyau");
MODULE_SUPPORTED_DEVICE("device"); 

static int kthread_func2(char * arg){
	printk(KERN_INFO "I am thread: %s\n", arg);
	return 0;
}

static int __init init_func(void){

	struct task_struct *ts1;
	int err;

	printk(KERN_INFO "Starting 2 threads...");

	ts1= kthread_create(kthread_func2("1"),NULL, "thread-1");
	if(IS_ERR(ts1)){
		printk(KERN_INFO "ERROR: Cannot create thread ts1\n");
		err=PTR_ERR(ts1);
		ts1=NULL;
		return err;
	}

	ts1= kthread_create(kthread_func2("2"),NULL, "thread-2");
	if(IS_ERR(ts1)){
		printk(KERN_INFO "ERROR: Cannot create thread ts1\n");
		err=PTR_ERR(ts1);
		ts1=NULL;
		return err;
	}

	printk(KERN_INFO "I am thread %s\n", current->comm);
	return 0;


}

static void __exit exit_func(void){
	printk(KERN_INFO "Exiting module \n");

}

module_init(init_func);
module_exit(exit_func);
