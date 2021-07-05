#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

#define MAJOR_NUM 60
#define MODULE_NAME "demo"

static int iCount = 0;
static char status[4]={'-1','-1','-1','-1'};

static ssize_t drv_read(struct file *filp,  char *buf, size_t count, loff_t *ppos) {
 printk("device read\n");
   char userChar[count];
   copy_from_user(userChar, buf, count);
   printk("Count: %d",count);
   userChar[count - 1] = '\0';
   printk("userChar(char): %s\n", userChar);
   char gpio[10] = {0};
   char fileStr[100];
   char status[10] ={0};
   strcpy(gpio,userChar);

   struct file *io;
   loff_t pos = 0;
   mm_segment_t old_fs;
   old_fs = get_fs();
   set_fs(get_ds());

   printk("Read-Value: %s",gpio);
   sprintf(fileStr,"/sys/class/gpio/gpio%s/value",gpio);
   io = filp_open(fileStr, O_RDONLY, 0);
   if(IS_ERR(io)){
      status[0]= '0';
      copy_to_user(buf,status,sizeof(status));
      return count;
   }
   vfs_read(io, status, 1, &pos);
   filp_close(io, NULL);

   pos = 0;
   set_fs(old_fs);
    
    copy_to_user(buf,status,sizeof(status));
    return count;
}

static ssize_t drv_write(struct file *filp, const char *buf, size_t count, loff_t *ppos) {
 printk("device write\n");
 printk("%d\n", iCount);
 printk("W_buf_size: %d\n", (int)count);
 char userChar[12] = {'0'};
 copy_from_user(userChar, buf, count);
 userChar[count - 1] = '\0';
 printk("userChar(char): %s\n", userChar);
 char gpio[10] = {'0'};
 strncpy(gpio, userChar, 5);
 printk("gpio: %s, length: %d\n", gpio, strlen(gpio));
 struct file *io;
 loff_t pos = 0;
 mm_segment_t old_fs;
 old_fs = get_fs();
 set_fs(get_ds());

  io = filp_open("/sys/class/gpio/export", O_WRONLY, 0);
  vfs_write(io, gpio, strlen(gpio), &pos);
  filp_close(io, NULL);
 //set-dir
 if(strncmp(gpio, "396 1",5) == 0 || strncmp(gpio, "396 0",5) == 0) {
  io = filp_open("/sys/class/gpio/gpio396/direction", O_WRONLY, 0);
  printk("out");
  vfs_write(io, "out", 3, &pos);
  filp_close(io, NULL);
 }
 
 
 pos = 0;
 //set-value
 if(strncmp(gpio, "396 1",5) == 0 || strncmp(gpio, "396 0",5) == 0) {
  io = filp_open("/sys/class/gpio/gpio396/value", O_WRONLY, 0);
  vfs_write(io, &userChar[count -4], 1, &pos);
  filp_close(io, NULL);
 }
 


if(strncmp(gpio, "481 0",5) == 0 || strncmp(gpio, "481 1",5) == 0) {
  io = filp_open("/sys/class/gpio/gpio481/direction", O_WRONLY, 0);
  vfs_write(io, "out", 3, &pos);
  filp_close(io, NULL);
 }

 
 pos = 0;
 //set-value
 if(strncmp(gpio, "481 0",5) == 0 || strncmp(gpio, "481 1",5) == 0 ){
  io = filp_open("/sys/class/gpio/gpio481/value", O_WRONLY, 0);
  vfs_write(io, &userChar[count -4], 1, &pos);
 filp_close(io, NULL);
 }
 

 if(strncmp(gpio, "255 0",5) == 0 || strncmp(gpio, "255 1",5) == 0) {
  io = filp_open("/sys/class/gpio/gpio255/direction", O_WRONLY, 0);
  vfs_write(io, "out", 3, &pos);
  filp_close(io, NULL);
 }

 
 pos = 0;
 //set-value
 if(strncmp(gpio, "255 0",5) == 0 || strncmp(gpio, "255 1",5) == 0) {
  io = filp_open("/sys/class/gpio/gpio255/value", O_WRONLY, 0);
  vfs_write(io, &userChar[count -4], 1, &pos);
 filp_close(io, NULL);
 }
 

if(strncmp(gpio, "397 1",5) == 0 || strncmp(gpio, "397 0",5) == 0)  {
  io = filp_open("/sys/class/gpio/gpio397/direction", O_WRONLY, 0);
  vfs_write(io, "out", 3, &pos);
  filp_close(io, NULL);
 }

 
 pos = 0;
 //set-value
  if(strncmp(gpio, "397 1",5) == 0|| strncmp(gpio, "397 0",5) == 0){
  io = filp_open("/sys/class/gpio/gpio397/value", O_WRONLY, 0);
  vfs_write(io, &userChar[count -4], 1, &pos);
  filp_close(io, NULL);
 }
 


 pos = 0;
 set_fs(old_fs);
 
 iCount++;
 return count;
}

long drv_ioctl(struct file *flip, unsigned int cmd, unsigned long arg) {
 printk("device ioctl\n");
 return 0;
}

static int drv_open(struct inode *inode, struct file *filp){
 printk("device open\n");
 return 0;
}

static int drv_release(struct inode *inode, struct file *filp){
 printk("device close\n");
 return 0;
}
struct file_operations drv_fops = {
 read : drv_read,
 write : drv_write,
 unlocked_ioctl : drv_ioctl,
 open : drv_open,
 release : drv_release,
};

static int demo_init(void) {
 if(register_chrdev(MAJOR_NUM, "demo", &drv_fops) < 0) {
  printk("<1>%s : can't get major %d\n", MODULE_NAME, MAJOR_NUM);
  return (-EBUSY);
 }
 printk("<1>%s : started\n", MODULE_NAME);
 return 0;
}

static void demo_exit(void) {
 unregister_chrdev(MAJOR_NUM, "demo");
 printk("<1>%s : removed\n", MODULE_NAME);
}

module_init(demo_init); 
module_exit(demo_exit); 
MODULE_LICENSE("GPL");
