#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/string.h>
#include <asm/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Lucien");
MODULE_DESCRIPTION("création d'un driver de device caracter");

static char ker_buf[100];   //driver local buffer

/* Définition des structures de gestion du FS à implémenter*/

static int dev_open(struct inode *inod, struct file *fil);
static ssize_t dev_read(struct file *filep, char *buf, size_t len, loff_t *off);
static ssize_t dev_write(struct file *flip, const char *buff, size_t len, loff_t *off);
static int dev_release(struct inode *inod, struct file *fil);

/*Structure contenant les opérations du périphérique */

static struct file_operations fops =
{
    .read=dev_read,
    .write=dev_write,
    .open=dev_open,
    .release=dev_release,
};

/* Fonction d'initialisation */

static int init(void){

    int t = register_chrdev(190, "alten", &fops);
    
    if (t<0)
        printk(KERN_ALERT "device registration failed.");

    else
        printk(KERN_ALERT "device registered.");
    
    return 0;
}

/* Fonction de clôture */

static void exit1(void){

    unregister_chrdev(190, "alten");
    printk(KERN_ALERT "exit");
}

/* Fonction d'operation de driver */

static int dev_open(struct inode *inod, struct file *fil){

    printk ("KERN_ALERT device opened");
    return 0;
}

static ssize_t dev_read(struct file *filep, char *buf, size_t len, loff_t *off){

    printk(KERN_DEBUG "test lecture");
    copy_to_user(buf,ker_buf,len);
    return len;
}

static ssize_t dev_write(struct file *flip, const char *buff, size_t len, loff_t *off){

    printk(KERN_ALERT "lecture");
    copy_from_user(ker_buf,buff,len);
    ker_buf[len]=0;
    return len;
}

static int dev_release(struct inode *inod, struct file *fil){
    printk("KERN_ALERT device closed \n");
    return 0;
}

module_init(init);
module_exit(exit1);
