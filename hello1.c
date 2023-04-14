#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>

int __init hw_init(void){
	printk(KERN_INFO"Hello World\n");
return 0;
}

void  __exit hw_exit(void)
{
	printk(KERN_INFO"Exit World\n");
}

MODULE_LICENSE("GPL");
module_init(hw_init);
module_exit(hw_exit);


/*output:
pid=31463 comm="firefox" exe="/snap/firefox/2559/usr/lib/firefox/firefox" sig=0 arch=c000003e syscall=314 compat=0 ip=0x7f158324973d code=0x50000
[ 3067.908757] Hello World*/
