/*
                                
  
                
  
                                               
 */

#include <linux/mm.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/init_task.h>
#include <linux/mqueue.h>

#include <asm/uaccess.h>
#include <asm/pgtable.h>

static struct signal_struct init_signals = INIT_SIGNALS(init_signals);
static struct sighand_struct init_sighand = INIT_SIGHAND(init_sighand);
/*
                            
  
                                                                   
                                                                   
                                 
 */
union thread_union init_thread_union __init_task_data =
	{ INIT_THREAD_INFO(init_task) };

/*
                          
  
                                                              
 */
struct task_struct init_task = INIT_TASK(init_task);

EXPORT_SYMBOL(init_task);
