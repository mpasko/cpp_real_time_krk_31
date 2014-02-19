#include <linux/init.h>
#include <linux/fs.h>
#include <linux/major.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/blkdev.h>
#include <linux/uaccess.h>
#include <linux/spinlock.h>

MODULE_AUTHOR("Pasko");
MODULE_DESCRIPTION("heylo wordl");
MODULE_VERSION("0.1");
MODULE_LICENSE("GPL");

#define DEVICE_NAME "ustroystvo"
#define CLASS_NAME "char_test"

static struct class *plp_class = NULL;
static struct device *char_dev = NULL;
static int dev_major;


static ssize_t char_read(struct file* file, char __user *buf,
                         size_t count, loff_t *ppos);
static ssize_t char_write(struct file* file, const char __user *buf,
                          size_t count, loff_t *ppos);

#define SIZE 1024
char payload [SIZE] = "ASDFGHJKL 1234567890\n\n";

static struct file_operations char_fops =
{
    .read = char_read,
    .write = char_write
};

static ssize_t char_read(struct file* file, char __user *buf,
                         size_t count, loff_t *ppos)
{
    ssize_t num_read;
    printk( KERN_INFO "char_test, called char_read");
    num_read = simple_read_from_buffer(buf, count, ppos, payload, SIZE - 1 );
    return num_read;
}

static ssize_t char_write(struct file* file, const char __user *buf,
                          size_t count, loff_t *ppos)
{
    ssize_t num_read;
    printk( KERN_INFO "char_test, called char_write");
    memset(payload, 0, SIZE);
    num_read = simple_write_to_buffer(payload, count, ppos, buf, SIZE -1 );
    
    return num_read;
}

static int __init char_init(void)
{
	printk( KERN_INFO "char_test, started char_init");
	dev_major = register_chrdev(0, DEVICE_NAME, &char_fops);
	printk( KERN_INFO "char_test, called register");
	plp_class = class_create(THIS_MODULE, CLASS_NAME);
	printk( KERN_INFO "char_test, called class_create");
	char_dev = device_create(plp_class, NULL, MKDEV(dev_major,0), NULL, CLASS_NAME);
    printk( KERN_INFO "char_test, finished char_init");
    return 0;
}

static void __exit char_exit(void)
{
	device_destroy(plp_class, MKDEV(dev_major,0));
	class_unregister(plp_class);
	class_destroy(plp_class);
	unregister_chrdev(dev_major, DEVICE_NAME);
    printk( KERN_INFO "char_test, called char_init");
}

module_init(char_init);
module_exit(char_exit);

