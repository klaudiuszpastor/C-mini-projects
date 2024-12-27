#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/uaccess.h>
#include <linux/fs.h> 

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Claudius");
MODULE_DESCRIPTION("A simple hello world module");
MODULE_VERSION("1.0.0");

static char kern_buf[100];
static int dev_open(struct inode* inode, struct file* file);
static ssize_t dev_read(struct file* file, char* buf, size_t len, loff_t* off);
static ssize_t dev_write(struct file* file, const char* buf, size_t len, loff_t* off);
static int dev_release(struct inode* inode, struct file* file);

static struct file_operations fops = {
    .read = dev_read,
    .write = dev_write,
    .open = dev_open,
    .release = dev_release
};

static int __init hello_init(void)
{
    int t = register_chrdev(90, "mydev", &fops);
    if (t < 0) 
    {
        printk(KERN_ERR "Problem registering character device\n");
        return -EIO;
    }

    printk(KERN_INFO "Hello, world!\n");
    return 0;
}

static int dev_open(struct inode* inode, struct file* file)
{
    printk(KERN_INFO "Device opened\n");
    return 0;
}

static ssize_t dev_read(struct file* file, char* buf, size_t len, loff_t* off)
{
    if (*off >= sizeof(kern_buf))
        return 0;

    if (len > sizeof(kern_buf))
        len = sizeof(kern_buf);

    if (copy_to_user(buf, kern_buf, len)) {
        return -EFAULT;
    }

    *off += len; 
    return len;
}

static ssize_t dev_write(struct file* file, const char* buf, size_t len, loff_t* off)
{
    if (len >= sizeof(kern_buf))
        return -EIO;

    memset(kern_buf, 0, sizeof(kern_buf));
    if (copy_from_user(kern_buf, buf, len)) {
        return -EFAULT;
    }

    kern_buf[len] = 0; 
    printk(KERN_INFO "Received %zu bytes\n", len);
    return len;
}

static int dev_release(struct inode* inode, struct file* file)
{
    printk(KERN_INFO "Device closed\n");
    return 0;
}

static void __exit hello_exit(void)
{
    unregister_chrdev(90, "mydev");
    printk(KERN_INFO "Goodbye, world!\n");
}

module_init(hello_init);
module_exit(hello_exit);

