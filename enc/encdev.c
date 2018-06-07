#include <linux/module.h>
#include <linux/string.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/random.h>

MODULE_LICENSE("NIKS");


static char msg[100]={0};
static short readPos =0;

static int file_open(struct inode * , struct file *);
static int file_release(struct inode * , struct file *);
static ssize_t file_read(struct file *, char *, size_t,loff_t * );
static ssize_t file_write(struct file *, char *, size_t,loff_t * );

static struct file_operations fo = 
{
	.read = file_read,
	.open = file_open,
	.write = file_write,
	.release = file_release,
};

int init_module(void)
{
	int t = register_chrdev(150,"encdev",&fo);
	if(t<0)
	{
		printk("error");
	}
	else
	{
		printk("success");
	}
	return t;
}

void cleanup_module(void)
{
	unregister_chrdev(150,"encdev");
}

static int file_open(struct inode *in , struct file *fil)
{
	return 0;
}

static ssize_t file_read(struct file *fil, char *buf, size_t len,loff_t *off )
{
	short count=0;
	printk("here %d",msg[0]!=0);
	while(len && (msg[readPos]!=0))
	{
		printk("read");
		put_user(msg[readPos],buf++);
		count++;
		len--;
		readPos++;
	}
	return count;
}

static ssize_t file_write(struct file *fil, char *buf, size_t len,loff_t *off )
{
	short ind = 0;
	short count =0;
	memset(msg,0,100);
	readPos = 0;
	int i =0;
	char bytes[16];
	char rand;
	while(i<16)
	{
		get_random_bytes(&rand, sizeof(rand));
 		bytes[i]=rand;
		++count;
		i++;
	}
	int _len = len+16;
	while(_len>0 || count%16){
		if(ind<16) msg[ind] = bytes[ind];
		else{
			msg[ind] = (_len>0?buf[ind-16]:'@')^msg[ind-16];
		}
		++ind;
		--_len;
		++count;
	}
 //    while(i<16)
 //    {
 //    	//get_random_bytes(&rand, sizeof(rand));
 //        //bytes[i]=rand;
 //        bytes[count] = 'a'+i;
 //        msg[count] = bytes[count];
 //        count++;
 //        //printk("rand %c \n",rand);
 //        i++;
 //    }
	// printk("this is len %d",len);
	// i=0;
	// while(len>0)
	// {
	// 	printk("%d  %d\n",msg[i],buf[ind%16]);
	// 	msg[count++] = bytes[ind%16]^buf[ind];
	// 	bytes[ind%16] = msg[count-1];
	// 	//printk("%c\n",msg[ind]^buf[ind] );
	// 	ind++;
	// 	len--;
	// 	i++;
	// }
	/*i=0;
	while(len>0)
	{
		printk("%c  %c\n",msg[i],buf[ind]);
		msg[count++] = msg[i]^buf[ind];
		msg[ind] = msg[count-1];
		//printk("%c\n",msg[ind]^buf[ind] );
		ind++;
		len--;
		i++;
	}*/
	// char ch = '@';
	// while(ind%16!=0)
	// {
	// 	msg[ind] = msg[ind-16]^ch;
	// 	ind++;
	// 	++count;
	// }
	return count;
	
}

static int file_release(struct inode *in , struct file *fil)
{
	printk("done");
	return 0;
}

