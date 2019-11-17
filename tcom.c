#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>


/* para os codigos de erros que serão utilizados daqui para a frente */
#include <linux/errno.h> 

/* controlar o sistema de arquivos */

#include <linux/fs.h>
#include <linux/proc_fs.h>


#include <asm/uaccess.h>




/* alocar memoria no kernel space */
#include <linux/slab.h> 

/* medir o tamanho das variaveis usado no kmalloc */
#include <linux/types.h> 


#include <linux/fcntl.h> /* O_ACCMODE */


int copy_to_user(void *dst, const void *src, unsigned int size); //TODO: !FIX depends on arch 
int copy_from_user(void *dst, const void *src, unsigned int size); //TODO: !FIX depends on arch 
int memory_major = 60;

/* Buffer to store data */

char *memory_buffer;


static int init_com(void)
{
    printk("\nHello World\n");
    return  0;
}
   
static void finish_com(void)
{
    return;
}

int memory_open(struct inode *inode, struct file *filp) {



  /* Success */

  return 0;

}
int memory_release(struct inode *inode, struct file *filp) {

 

  /* Success */

  return 0;

}
ssize_t memory_read(struct file *filp, char *buf, 

                    size_t count, loff_t *f_pos) { 

 

  /* Transfering data to user space */ 

  copy_to_user(buf,memory_buffer,1);



  /* Changing reading position as best suits */ 

  if (*f_pos == 0) { 

    *f_pos+=1; 

    return 1; 

  } else { 

    return 0; 

  }

}

ssize_t memory_write( struct file *filp, char *buf,

                      size_t count, loff_t *f_pos) {



  char *tmp;



  tmp=buf+count-1;

  copy_from_user(memory_buffer,tmp,1);

  return 1;

}

MODULE_LICENSE("Dual BSD/GPL");

module_init(init_com);
module_exit(finish_com);