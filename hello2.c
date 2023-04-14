#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>

MODULE_LICENCSE("GPL");

static int __init hello_start(void)
{
    printk(KERN_INFO "Loading hello module...\n");
    printk(KERN_INFO "Hello world\n");
    return 0;
}
  
static void __exit hello_end(void)
{
    printk(KERN_INFO "Goodbye Mr.\n");
}

module_init(hello_start);
module_exit(hello_end);


/*output:
Loading hello module...
Hello world
Goodbye Mr.
*/