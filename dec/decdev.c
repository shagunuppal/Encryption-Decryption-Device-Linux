#include <linux/module.h>
#include <linux/string.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

MODULE_LICENSE("NIKI");


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
	int t = register_chrdev(160,"decdev",&fo);
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
	unregister_chrdev(160,"decdev");
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
		//printk("read");
		put_user(msg[readPos],buf++);
		count++;
		len--;
		readPos++;
	}
	return count;
}

static ssize_t file_write(struct file *fil, char *buf, size_t len,loff_t *off )
{
	short ind = 16;
	short count =0;
	memset(msg,0,100);
	readPos = 0;
	char byte[16];
	int i =0;
    char ch;
	printk("this is len %d",len);
	//printk("this is string %s",buf);
	char copy[1000];
	if(copy_from_user(copy,buf,1000)!=0)
		return -EFAULT;
	
	//strcpy(copy,buf);
	char tem[1000];
	strcpy(tem,copy);
	printk("%c",copy[16]);

	while(i<16)
	{
		/*ch = copy[i]^copy[ind++];
		printk("%c %c %c\n",ch,copy[i],copy[ind]);
		msg[count++] = ch;
		len--;*/
		byte[i] = copy[i];
		i++;
		count++;
	}
	int j = 16;
	while(len>16)
	{

		// while(j<16)
		// {
		msg[j-16]=copy[j]^copy[j-16];
		++j;
		++count;
		// byte[j] = msg[j];
		// j++;
		// ind++;
		len--;
		printk("this is %c\n", msg[j-17]);
		//}

		//printk("in %d %c\n", len, copy[ind] );
		/*ch = copy[i]^copy[ind];
		printk("1%c %c %c\n",ch,copy[i],copy[ind]);
		if(ch=='@')
			break;
		msg[count++] = ch;
		ind++;                   
		len--;
		i++;*/
		///printk("this is count1 %d",count);
	}
	/*printk("this is count %d",count);
	while(len>0)
	{
		printk("heloow");
		msg[count++]='0';
		len--;
	}*/
	
	printk("this is count %d",count);
	
	return count;


}

static int file_release(struct inode *in , struct file *fil)
{
	printk("done");
	return 0;
}

