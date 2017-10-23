#include<linux/module.h>
#include<linux/string.h>
#include<linux/fs.h>
#include<asm/uaccess.h>
#include <linux/tty.h>          /* For fg_console, MAX_NR_CONSOLES */
#include <linux/kd.h>           /* For KDSETLED */
#include <linux/vt.h>
#include <linux/console_struct.h>       /* For vc_cons */
#include <linux/vt_kern.h>
 
//module attributes
MODULE_LICENSE("@Karthick2016"); //   this avoids kernel taint warning
MODULE_DESCRIPTION("Block Device Driver & LED Blink");
MODULE_AUTHOR("Karthick");
#define BLINK_DELAY   HZ/5
#define ALL_LEDS_ON   0x07
#define RESTORE_LEDS  0xFF 
static char msg[100]={0};
static short readPos=0;
static int times=0;
 struct timer_list my_timer;
char kbledstatus = 0;
//prototypes, else the structure initialization tat follows fail
struct tty_driver *my_driver; 
static int dev_open(struct inode *n, struct file *fil);
static int dev_rls(struct inode *n,struct file *fil);
static ssize_t dev_read(struct file *fil, char *c, size_t len);
static ssize_t dev_write(struct file *fil, const char *c, size_t len);
static void my_timer_func(unsigned long ptr);
 
// structure containing callbacks
static struct file_operations fops=
{
    .read=dev_read, //address of dev_read
    .open=dev_open,
    .write=dev_write,
    .release=dev_rls,
};
//called when module is loaded, similar to main()
int init_module(void)
{
    my_driver = vc_cons[fg_console].d->port.tty->driver;
   init_timer(&my_timer);
    my_timer.function = my_timer_func;
	my_timer.data = (unsigned long)&kbledstatus;
	my_timer.expires = jiffies + BLINK_DELAY;
	add_timer(&my_timer);
    int t= register_chrdev(89,"myDev",&fops); //register with major number
 
    if(t<0)printk(KERN_ALERT "Device registration failed.. \n");
    else printk(KERN_ALERT "device registered \n");
   
	
    return t;
}
 
//called when module is unloaded, similar to destroy
void cleanup_module(void)
{
   del_timer(&my_timer);
	(my_driver->ops->ioctl) (vc_cons[fg_console].d->port.tty, KDSETLED,RESTORE_LEDS);
    unregister_chrdev(89,"myDev");
    
}
 
static void my_timer_func(unsigned long ptr)
{
	int *pstatus = (int *)ptr;

	if (*pstatus == ALL_LEDS_ON)
		*pstatus = RESTORE_LEDS;
	else
		*pstatus = ALL_LEDS_ON;

	(my_driver->ops->ioctl) (vc_cons[fg_console].d->port.tty, KDSETLED,
			    *pstatus);

	my_timer.expires = jiffies + BLINK_DELAY;
	add_timer(&my_timer);
}

//called when "open" system call is done on the device file
static int dev_open(struct inode *inod, struct file *fil)
{
    times++;
    printk(KERN_ALERT "device opened %d times \n", times);

    printk(KERN_INFO "kbleds: tty driver magic %x\n", my_driver->magic);
	
    return 0;
}
 
// called when 'read' system call
 
static ssize_t dev_read(struct file *filp, char *buff, size_t len)
{
    short count=0;
    while(len &&(msg[readPos]!=0))
    {
        put_user(msg[readPos],buff++);//copy byte from kernel space to user space
        count++;
        len--;
        readPos++;
    }

    return count;
}
 
//called when 'write' is called on device file
 
static ssize_t dev_write(struct file *flip,const char *buff, size_t len)
{
    short ind=len-1;
    short count=0;
    memset(msg,0,100);
    readPos=0;
    while(len>0)
    {
        msg[count++]=buff[ind--];//copy the string to driver but in reverse
        len--;
    }
    return count;
}
//called when 'close' system call
static int dev_rls(struct inode *inod, struct file *fil)
{
    printk(KERN_ALERT "device closed \n");
   
	
    return 0;
}
