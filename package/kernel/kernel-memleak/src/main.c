#include <linux/kmod.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/slab.h>

#include "kernel_memleak.h"

#define FILE_NAME "kernel_memleak"

static struct proc_dir_entry *file = NULL;

static void *my_seq_start(struct seq_file *s, loff_t *pos)
{
        return NULL;
}

static void *my_seq_next(struct seq_file *s, void *v, loff_t *pos)
{
        return NULL;
}

static void my_seq_stop(struct seq_file *s, void *v)
{
        return NULL;
}

static int my_seq_show(struct seq_file *s, void *v)
{
	return 0;
}

static struct seq_operations my_seq_ops = {
	.start = my_seq_start,
	.next  = my_seq_next,
	.stop  = my_seq_stop,
	.show  = my_seq_show
};

static int fops_open(struct inode *inode , struct file *file)
{
        return seq_open(file, &my_seq_ops);
}

static ssize_t fops_write(struct file *file, const char __user *ubuf, size_t count, loff_t *ppos)
{
	char *mm = kmalloc(32*1024, GFP_KERNEL);
	printk("mem leak,ptr = %p\n",mm);
	
        if (mm) {
		memset(mm, 0x0, 32 * 1024);
		mm = kmalloc(32 * 1024, GFP_KERNEL);
		kfree(mm);
		printk("mem leak,ptr = %p\n", mm);
	}

        return count;
}

static long proc_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{

        int ret = 0;

        switch (cmd) {
                case CMD_GET:
                        {
                                char *mm = kmalloc(32*1024, GFP_KERNEL);
                                printk("mem leak,ptr = %p\n",mm);

                                if (mm) {
                                        memset(mm, 0x0, 32 * 1024);
                                        mm = kmalloc(32 * 1024, GFP_KERNEL);
                                        kfree(mm);
                                        printk("mem leak,ptr = %p\n", mm);
                                }

                        }
                        break;

                case CMD_SET:
                        break;

                default:
                        break;
        }

        return ret;
}

static const struct file_operations fops = {
        .owner		= THIS_MODULE,
        .open		= fops_open,
        .read		= seq_read,
        .write		= fops_write,
        .llseek		= seq_lseek,
        .release	= seq_release,
        .unlocked_ioctl = proc_ioctl,
};

static int __init kmemleak_test_init(void)
{
        file = proc_create(FILE_NAME, 0, NULL, &fops);
        printk("create procfs file, %s, %s", FILE_NAME, file? "successful":"fail");
        return 0;
}

static void __exit kmemleak_test_exit(void)
{
        printk("remove procfs file, %s", FILE_NAME);
        proc_remove(file);
}

module_init(kmemleak_test_init);
module_exit(kmemleak_test_exit);

MODULE_AUTHOR("Manbing");
MODULE_DESCRIPTION("test kernel module for kmemleak");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform: openwrt");
