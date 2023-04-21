#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/device.h>
#include<linux/slab.h>
#include<linux/uaccess.h>

#define mem_size 1024

dev_t dev =0;
static struct class *dev_class;
static struct cdev my_cdev;
uint8_ *kernel_buffer;
 
static int __init chr_driver_init(void);
static void __exit chr_driver_exit(void);
static int my_open(struct inode *inode,struct file *file);
static int my_release(struct inode *inode,struct file *file);
static ssize_t my_read(struct file *filp,char __user *buf,size_t len,loff_t *off);
static ssize_t my_write(struct file *filp,const char *buf,size_t len,loff_t *off);

static struct file_operations fops =
{
	.owner = THIS_MODULE,
	.read = my_read,
	.write = my_write,
	.open = my_open,
	.release = my_release,
};

static int my_open(struct inode *inode,struct file *file)
{
	if((kernel_buffer = kmalloc(mem_size,GFP_KERNEL))==0)
	{
		printk(KERN_INFO "cannot allocate the memory to the kernel..\n");	
	return -1;
	}
	printk(KERN_INFO "Device file opened....\n");
	return 0;
}

static my_release(struct inode *inode,struct file *file)
{
	kfree(kernel_buffer);
	printk(KERN_INFO "Device file closed...\n");
	return 0;
}

static ssize_t my_read(struct file *flip,char_user *buf,size_t len,loff_t *off)
{
	copy_to_user(buf,kernel_buffer,mem_size);
	printk(KERN_INFO "Data read : Done...\n");
	return mem_size;
}

static ssize_t my_write(struct file *flip,const char __user *buf,size_t len,loff_t *off)
{
	copy_from_user(kernel_buffer,buf,len);
	printk(KERN_INFO "Data is written sucessfully...\n");
	return len;
}

static int __init chr_driver_init(void)
{
	//allocating major number
	if((alloc_chrdev_region(&dev,0,1,"my_Dev")<0))
	{
		printk(KERN_INFO"Can not allocate the major number...\n");
		return -1;
	}
	printk(KERN_INFO "Major = %d minor = %d..\n",MAJOR(dev),MINOR(dev));
	//creating cdev structure
	cdev_init(&my_cdev,&fops);
	//adding character device to the system
	if((cdev_add(&my_cdev,dev,1))<0)
	{
		printk(KERN_INFO "Cannot add the device to the systme..\n");
		goto r_class;
	}
	//creating struct class
	if((dev_class = class_create(THIS_MODULE,"my_class")) == NULL)
	{
		printk(KERN_INFO "Cannot create the struct class....\n ");
		goto r_class;
	}
	//creating device
	
	if((device_create(dev_class,NULL,dev,NULL,"my_device")) == NULL)
	{
		printk(KERN_INFO"Cannot create the device...\n");
		goto r_device;
	}
	printk(KERN_INFO"Device driver insert... done properly..\n");
	return 0;
r_device:
	class_destroy(dev_class);
r_class:
	unregister_chrdev_region(dev,1);
	return -1;
}
void __exit chr_driver_exit(void)
{
	device_destroy(dev_class,dev);
	class_destroy(dev_class);
	cdev_del(&my_cdev);
	unregister_chrdev_region(dev,1);
	printk(KERN_INFO"Device driver is removed sucessfully....\n");
}

module_init(chr_driver_init);
module_exit(chr_driver_exit);

MODULE_LICENSE("GPL");
	
/*output:
Major = 238 minor = 0..
[25143.683778] Device driver insert... done properly..

sudo rmmod chr_drv.ko
Major = 238 minor = 0..
[25143.683778] Device driver insert... done properly..
[25273.440331] Device file opened....
[25280.374004] Data is written sucessfully...
[25303.351359] Data read : Done...
[25308.722122] Data is written sucessfully...
[25335.121934] Data read : Done...
[25341.178244] Device file closed...
[25349.398623] Device file opened....
[25405.958522] Data is written sucessfully...
[25411.103836] Data is written sucessfully...
[25659.599883] Data is written sucessfully...
[25662.579846] Data is written sucessfully...
[25664.212096] Data is written sucessfully...
[25672.954054] Data is written sucessfully...
[25701.950130] Device file closed...
[25721.938069] Device file opened....
[25735.759911] Data is written sucessfully...
[25761.676379] Device file closed...
[25773.451252] Device file opened....
[25777.082958] Data is written sucessfully...
[25799.620037] Data read : Done...
[25809.998333] Device file closed...
[25945.808766] Device file opened....
[25951.566565] Data is written sucessfully...
[25970.278524] Device file closed...
[26129.438746] Device file opened....
[26153.885888] Data is written sucessfully...
[27249.954880] Data read : Done...
[27256.089072] Device file closed...
[27548.650059] Device file opened....
[27580.027124] Data is written sucessfully...
[27603.240564] Data read : Done...
[27617.252443] Device file closed...
[27745.198921] Device driver is removed sucessfully...
*/







