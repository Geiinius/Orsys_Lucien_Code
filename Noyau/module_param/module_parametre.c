#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_AUTHOR("lucien");
MODULE_DESCRIPTION("exemple de module");
MODULE_SUPPORTED_DEVICE("none");
MODULE_LICENSE("none");

static char* formation[5] = {"AGL", "RX", "LX", "RPI", "ANDRO"};
static const int ad = 15;
module_param_array(formation, charp, &ad, 0644);
MODULE_PARM_DESC(formation, "liste des formations");


static int nb_left = 3;
module_param(nb_left, int, 0644);
MODULE_PARM_DESC(nb_left, "nombre de formation restante");


static int __init first_init(void)
{
    int i;
    int j;
    //int nb_done = ad-nb_left;
    pr_info("Bienvenue au parcours embarqué!\n");
    
    for (i = 0; i< 5; i++){
        printk(KERN_DEBUG "%s  \n", formation[i]);
    }

    return 0;
}

static void __exit first_exit(void)
{
    printk(KERN_DEBUG "Il reste %d formation \n", nb_left);

}


//Points d'entré

module_init(first_init);
module_exit(first_exit);
