#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

static int __init first_init(void)
{
	pr_info("Bienvenue au parcours embarqué!\n");
	return 0;
}

static void __exit first_exit(void)
{
	pr_info("fin du parcours, j'espère que cela vous bien plu\n");
}


module_init(first_init);
module_exit(first_exit);
