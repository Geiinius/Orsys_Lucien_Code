#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/kthread.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Fleur de Nanteuil");
MODULE_DESCRIPTION("TP3 de LDI - Exercice 4 - Création de 3 threads");
MODULE_SUPPORTED_DEVICE("device"); 

//parametre: entier 1
static int a=1;
module_param(a, int, 0644);
MODULE_PARM_DESC(a, "premier entier saisit"); 
//parametre: entier 2
static int b=3;
module_param(b, int, 0644);
MODULE_PARM_DESC(b, "deuxième entier saisit"); 
//parametre: message saisit
static char* msg="Hello World";
module_param(msg, charp, 0644);
MODULE_PARM_DESC(msg, "message saisit"); 



//Fonction1: affiche le message saisit
static int kthread_func1(char* arg){

	printk(KERN_INFO "Message saisit: %s\n", arg);
	return 0;
}

//Fonction2: affiche la somme des 2 entiers
static int kthread_func2(int a, int b){

	printk(KERN_INFO "Somme des 2 entiers: %d\n", (a+b));
	return 0;
}

//Fonction2: affiche la différence des 2 entiers
static int kthread_func3(int a, int b){

	printk(KERN_INFO "Diiférence des 2 entiers: %d\n", (a-b));
	return 0;
}

struct task_struct *ts1,*ts2,*ts3;

static int __init init_func(void){

	
	int err;

	printk(KERN_INFO "Starting 3 threads...");

	ts1= kthread_create(kthread_func1(msg),NULL, "thread-1");
	if(IS_ERR(ts1)){
		printk(KERN_INFO "ERROR: Cannot create thread ts1\n");
		err=PTR_ERR(ts1);
		ts1=NULL;
		return err;
	}

	ts2= kthread_create(kthread_func2(a,b),NULL, "thread-2");
	if(IS_ERR(ts2)){
		printk(KERN_INFO "ERROR: Cannot create thread ts2\n");
		err=PTR_ERR(ts2);
		ts2=NULL;
		return err;
	}

	ts3= kthread_create(kthread_func3(a,b),NULL, "thread-3");
	if(IS_ERR(ts3)){
		printk(KERN_INFO "ERROR: Cannot create thread ts3\n");
		err=PTR_ERR(ts3);
		ts3=NULL;
		return err;
	}

	//printk(KERN_INFO "I am thread %s\n", current->comm);
	return 0;


}

static void __exit exit_func(void){
	
	int ret;
	ret=kthread_stop(ts1);
	//printk(KERN_INFO "Stopping thread.. \n");
	ret=kthread_stop(ts2);
	//printk(KERN_INFO "Stopping thread.. \n");
	ret=kthread_stop(ts3);
	//printk(KERN_INFO "Stopping thread.. \n");
	printk(KERN_INFO "Exiting module \n");

}

module_init(init_func);
module_exit(exit_func);
