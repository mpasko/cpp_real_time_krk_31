#include <linux/init.h>
#include <linux/fs.h>
#include <linux/major.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/blkdev.h>
#include <linux/uaccess.h>
#include <linux/spinlock.h>

MODULE_AUTHOR("ABC");
MODULE_DESCRIPTION("char dev mod");
MODULE_VERSION("1.0");
MODULE_LICENSE("GPL");

#define DEVICE_NAME "device"
#define CLASS_NAME "char_test"

static struct class *ppl_class = NULL;
static struct device *char_dev = NULL;
static int dev_major;

static ssize_t char_read(struct file* file, char __user *buf,
                         size_t count, loff_t *ppos);

static ssize_t char_write(struct file* file, const char __user *buf,
                          size_t count, loff_t *ppos);


#define SIZE 1024

char payload[ SIZE ] = "ABCDEF 123456789\n";

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

    num_read = simple_read_from_buffer( buf, count, ppos, payload, strlen(payload) );

    return num_read;
}


static ssize_t char_write(struct file* file, const char __user *buf,
                          size_t count, loff_t *ppos)
{
    ssize_t num_wr;
    printk( KERN_INFO "char_test, called char_write");

    memset( payload, 0, SIZE);

    if( count > (SIZE-1) )
      num_wr = simple_write_to_buffer(payload, SIZE-1, ppos, buf, count);
    else
      num_wr = simple_write_to_buffer(payload, strlen(buf), ppos, buf, count);
    
    return num_wr;
}

static int __init char_init(void)
{
    printk( KERN_INFO "char_test, called char_init");

    dev_major = register_chrdev(0, DEVICE_NAME, &char_fops);
    ppl_class = class_create( THIS_MODULE, CLASS_NAME );
    char_dev = device_create(ppl_class, NULL, MKDEV( dev_major, 0 ), NULL, CLASS_NAME );

    return 0;
}

static void __exit char_exit(void)
{
    printk( KERN_INFO "char_test, called char_init");

    device_destroy( ppl_class, MKDEV( dev_major, 0));
    class_unregister( ppl_class );
    class_destroy( ppl_class );
    unregister_chrdev( dev_major, DEVICE_NAME );
}

module_init(char_init);
module_exit(char_exit);

