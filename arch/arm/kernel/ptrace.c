/*
 *  linux/arch/arm/kernel/ptrace.c
 *
 *  By Ross Biro 1/23/92
 * edited by Linus Torvalds
 * ARM modifications Copyright (C) 2000 Russell King
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/mm.h>
#include <linux/elf.h>
#include <linux/smp.h>
#include <linux/ptrace.h>
#include <linux/user.h>
#include <linux/security.h>
#include <linux/init.h>
#include <linux/signal.h>
#include <linux/uaccess.h>
#include <linux/perf_event.h>
#include <linux/hw_breakpoint.h>
#include <linux/regset.h>
#include <linux/audit.h>
#include <linux/unistd.h>

#include <asm/pgtable.h>
#include <asm/traps.h>

#define REG_PC	15
#define REG_PSR	16
/*
                                                       
                            
 */

#if 0
/*
                                          
 */
#define BREAKINST_ARM	0xef9f0001
#define BREAKINST_THUMB	0xdf00		/*                    */
#else
/*
                                                                        
                                                                   
                                                               
  
                                                  
                              
 */
#define BREAKINST_ARM	0xe7f001f0
#define BREAKINST_THUMB	0xde01
#endif

struct pt_regs_offset {
	const char *name;
	int offset;
};

#define REG_OFFSET_NAME(r) \
	{.name = #r, .offset = offsetof(struct pt_regs, ARM_##r)}
#define REG_OFFSET_END {.name = NULL, .offset = 0}

static const struct pt_regs_offset regoffset_table[] = {
	REG_OFFSET_NAME(r0),
	REG_OFFSET_NAME(r1),
	REG_OFFSET_NAME(r2),
	REG_OFFSET_NAME(r3),
	REG_OFFSET_NAME(r4),
	REG_OFFSET_NAME(r5),
	REG_OFFSET_NAME(r6),
	REG_OFFSET_NAME(r7),
	REG_OFFSET_NAME(r8),
	REG_OFFSET_NAME(r9),
	REG_OFFSET_NAME(r10),
	REG_OFFSET_NAME(fp),
	REG_OFFSET_NAME(ip),
	REG_OFFSET_NAME(sp),
	REG_OFFSET_NAME(lr),
	REG_OFFSET_NAME(pc),
	REG_OFFSET_NAME(cpsr),
	REG_OFFSET_NAME(ORIG_r0),
	REG_OFFSET_END,
};

/* 
                                                                     
                                
  
                                                                          
                                                                       
 */
int regs_query_register_offset(const char *name)
{
	const struct pt_regs_offset *roff;
	for (roff = regoffset_table; roff->name != NULL; roff++)
		if (!strcmp(roff->name, name))
			return roff->offset;
	return -EINVAL;
}

/* 
                                                                   
                                                       
  
                                                                     
                                                                          
 */
const char *regs_query_register_name(unsigned int offset)
{
	const struct pt_regs_offset *roff;
	for (roff = regoffset_table; roff->name != NULL; roff++)
		if (roff->offset == offset)
			return roff->name;
	return NULL;
}

/* 
                                                              
                                                           
                                        
  
                                                                              
                                                                               
 */
bool regs_within_kernel_stack(struct pt_regs *regs, unsigned long addr)
{
	return ((addr & ~(THREAD_SIZE - 1))  ==
		(kernel_stack_pointer(regs) & ~(THREAD_SIZE - 1)));
}

/* 
                                                           
                                                      
                           
  
                                                                            
                                                                        
                  
 */
unsigned long regs_get_kernel_stack_nth(struct pt_regs *regs, unsigned int n)
{
	unsigned long *addr = (unsigned long *)kernel_stack_pointer(regs);
	addr += n;
	if (regs_within_kernel_stack(regs, (unsigned long)addr))
		return *addr;
	else
		return 0;
}

/*
                                                                      
                                                                    
                                                                 
              
 */
static inline long get_user_reg(struct task_struct *task, int offset)
{
	return task_pt_regs(task)->uregs[offset];
}

/*
                                                                  
                                                                    
                                                                 
              
 */
static inline int
put_user_reg(struct task_struct *task, int offset, long data)
{
	struct pt_regs newregs, *regs = task_pt_regs(task);
	int ret = -EINVAL;

	newregs = *regs;
	newregs.uregs[offset] = data;

	if (valid_user_regs(&newregs)) {
		regs->uregs[offset] = data;
		ret = 0;
	}

	return ret;
}

/*
                                             
 */
void ptrace_disable(struct task_struct *child)
{
	/*                */
}

/*
                               
 */
void ptrace_break(struct task_struct *tsk, struct pt_regs *regs)
{
	siginfo_t info;

	info.si_signo = SIGTRAP;
	info.si_errno = 0;
	info.si_code  = TRAP_BRKPT;
	info.si_addr  = (void __user *)instruction_pointer(regs);

	force_sig_info(SIGTRAP, &info, tsk);
}

static int break_trap(struct pt_regs *regs, unsigned int instr)
{
	ptrace_break(current, regs);
	return 0;
}

static struct undef_hook arm_break_hook = {
	.instr_mask	= 0x0fffffff,
	.instr_val	= 0x07f001f0,
	.cpsr_mask	= PSR_T_BIT,
	.cpsr_val	= 0,
	.fn		= break_trap,
};

static struct undef_hook thumb_break_hook = {
	.instr_mask	= 0xffff,
	.instr_val	= 0xde01,
	.cpsr_mask	= PSR_T_BIT,
	.cpsr_val	= PSR_T_BIT,
	.fn		= break_trap,
};

static struct undef_hook thumb2_break_hook = {
	.instr_mask	= 0xffffffff,
	.instr_val	= 0xf7f0a000,
	.cpsr_mask	= PSR_T_BIT,
	.cpsr_val	= PSR_T_BIT,
	.fn		= break_trap,
};

static int __init ptrace_break_init(void)
{
	register_undef_hook(&arm_break_hook);
	register_undef_hook(&thumb_break_hook);
	register_undef_hook(&thumb2_break_hook);
	return 0;
}

core_initcall(ptrace_break_init);

/*
                                                            
                                                          
 */
static int ptrace_read_user(struct task_struct *tsk, unsigned long off,
			    unsigned long __user *ret)
{
	unsigned long tmp;

	if (off & 3)
		return -EIO;

	tmp = 0;
	if (off == PT_TEXT_ADDR)
		tmp = tsk->mm->start_code;
	else if (off == PT_DATA_ADDR)
		tmp = tsk->mm->start_data;
	else if (off == PT_TEXT_END_ADDR)
		tmp = tsk->mm->end_code;
	else if (off < sizeof(struct pt_regs))
		tmp = get_user_reg(tsk, off >> 2);
	else if (off >= sizeof(struct user))
		return -EIO;

	return put_user(tmp, ret);
}

/*
                                                         
                                                          
 */
static int ptrace_write_user(struct task_struct *tsk, unsigned long off,
			     unsigned long val)
{
	if (off & 3 || off >= sizeof(struct user))
		return -EIO;

	if (off >= sizeof(struct pt_regs))
		return 0;

	return put_user_reg(tsk, off >> 2, val);
}

#ifdef CONFIG_IWMMXT

/*
                              
 */
static int ptrace_getwmmxregs(struct task_struct *tsk, void __user *ufp)
{
	struct thread_info *thread = task_thread_info(tsk);

	if (!test_ti_thread_flag(thread, TIF_USING_IWMMXT))
		return -ENODATA;
	iwmmxt_task_disable(thread);  /*                 */
	return copy_to_user(ufp, &thread->fpstate.iwmmxt, IWMMXT_SIZE)
		? -EFAULT : 0;
}

/*
                              
 */
static int ptrace_setwmmxregs(struct task_struct *tsk, void __user *ufp)
{
	struct thread_info *thread = task_thread_info(tsk);

	if (!test_ti_thread_flag(thread, TIF_USING_IWMMXT))
		return -EACCES;
	iwmmxt_task_release(thread);  /*                */
	return copy_from_user(&thread->fpstate.iwmmxt, ufp, IWMMXT_SIZE)
		? -EFAULT : 0;
}

#endif

#ifdef CONFIG_CRUNCH
/*
                              
 */
static int ptrace_getcrunchregs(struct task_struct *tsk, void __user *ufp)
{
	struct thread_info *thread = task_thread_info(tsk);

	crunch_task_disable(thread);  /*                 */
	return copy_to_user(ufp, &thread->crunchstate, CRUNCH_SIZE)
		? -EFAULT : 0;
}

/*
                              
 */
static int ptrace_setcrunchregs(struct task_struct *tsk, void __user *ufp)
{
	struct thread_info *thread = task_thread_info(tsk);

	crunch_task_release(thread);  /*                */
	return copy_from_user(&thread->crunchstate, ufp, CRUNCH_SIZE)
		? -EFAULT : 0;
}
#endif

#ifdef CONFIG_HAVE_HW_BREAKPOINT
/*
                                                                    
                                                                      
                                                                       
                                                                             
                                                              
 */
static int ptrace_hbp_num_to_idx(long num)
{
	if (num < 0)
		num = (ARM_MAX_BRP << 1) - num;
	return (num - 1) >> 1;
}

/*
                                                             
                           
 */
static long ptrace_hbp_idx_to_num(int idx)
{
	long mid = ARM_MAX_BRP << 1;
	long num = (idx << 1) + 1;
	return num > mid ? mid - num : num;
}

/*
                                  
 */
static void ptrace_hbptriggered(struct perf_event *bp,
				     struct perf_sample_data *data,
				     struct pt_regs *regs)
{
	struct arch_hw_breakpoint *bkpt = counter_arch_bp(bp);
	long num;
	int i;
	siginfo_t info;

	for (i = 0; i < ARM_MAX_HBP_SLOTS; ++i)
		if (current->thread.debug.hbp[i] == bp)
			break;

	num = (i == ARM_MAX_HBP_SLOTS) ? 0 : ptrace_hbp_idx_to_num(i);

	info.si_signo	= SIGTRAP;
	info.si_errno	= (int)num;
	info.si_code	= TRAP_HWBKPT;
	info.si_addr	= (void __user *)(bkpt->trigger);

	force_sig_info(SIGTRAP, &info, current);
}

/*
                                                        
                                                                          
                                    
 */
void clear_ptrace_hw_breakpoint(struct task_struct *tsk)
{
	memset(tsk->thread.debug.hbp, 0, sizeof(tsk->thread.debug.hbp));
}

/*
                                                                  
                     
 */
void flush_ptrace_hw_breakpoint(struct task_struct *tsk)
{
	int i;
	struct thread_struct *t = &tsk->thread;

	for (i = 0; i < ARM_MAX_HBP_SLOTS; i++) {
		if (t->debug.hbp[i]) {
			unregister_hw_breakpoint(t->debug.hbp[i]);
			t->debug.hbp[i] = NULL;
		}
	}
}

static u32 ptrace_get_hbp_resource_info(void)
{
	u8 num_brps, num_wrps, debug_arch, wp_len;
	u32 reg = 0;

	num_brps	= hw_breakpoint_slots(TYPE_INST);
	num_wrps	= hw_breakpoint_slots(TYPE_DATA);
	debug_arch	= arch_get_debug_arch();
	wp_len		= arch_get_max_wp_len();

	reg		|= debug_arch;
	reg		<<= 8;
	reg		|= wp_len;
	reg		<<= 8;
	reg		|= num_wrps;
	reg		<<= 8;
	reg		|= num_brps;

	return reg;
}

static struct perf_event *ptrace_hbp_create(struct task_struct *tsk, int type)
{
	struct perf_event_attr attr;

	ptrace_breakpoint_init(&attr);

	/*                                     */
	attr.bp_addr	= 0;
	attr.bp_len	= HW_BREAKPOINT_LEN_4;
	attr.bp_type	= type;
	attr.disabled	= 1;

	return register_user_hw_breakpoint(&attr, ptrace_hbptriggered, NULL,
					   tsk);
}

static int ptrace_gethbpregs(struct task_struct *tsk, long num,
			     unsigned long  __user *data)
{
	u32 reg;
	int idx, ret = 0;
	struct perf_event *bp;
	struct arch_hw_breakpoint_ctrl arch_ctrl;

	if (num == 0) {
		reg = ptrace_get_hbp_resource_info();
	} else {
		idx = ptrace_hbp_num_to_idx(num);
		if (idx < 0 || idx >= ARM_MAX_HBP_SLOTS) {
			ret = -EINVAL;
			goto out;
		}

		bp = tsk->thread.debug.hbp[idx];
		if (!bp) {
			reg = 0;
			goto put;
		}

		arch_ctrl = counter_arch_bp(bp)->ctrl;

		/*
                                                   
                                            
   */
		while (!(arch_ctrl.len & 0x1))
			arch_ctrl.len >>= 1;

		if (num & 0x1)
			reg = bp->attr.bp_addr;
		else
			reg = encode_ctrl_reg(arch_ctrl);
	}

put:
	if (put_user(reg, data))
		ret = -EFAULT;

out:
	return ret;
}

static int ptrace_sethbpregs(struct task_struct *tsk, long num,
			     unsigned long __user *data)
{
	int idx, gen_len, gen_type, implied_type, ret = 0;
	u32 user_val;
	struct perf_event *bp;
	struct arch_hw_breakpoint_ctrl ctrl;
	struct perf_event_attr attr;

	if (num == 0)
		goto out;
	else if (num < 0)
		implied_type = HW_BREAKPOINT_RW;
	else
		implied_type = HW_BREAKPOINT_X;

	idx = ptrace_hbp_num_to_idx(num);
	if (idx < 0 || idx >= ARM_MAX_HBP_SLOTS) {
		ret = -EINVAL;
		goto out;
	}

	if (get_user(user_val, data)) {
		ret = -EFAULT;
		goto out;
	}

	bp = tsk->thread.debug.hbp[idx];
	if (!bp) {
		bp = ptrace_hbp_create(tsk, implied_type);
		if (IS_ERR(bp)) {
			ret = PTR_ERR(bp);
			goto out;
		}
		tsk->thread.debug.hbp[idx] = bp;
	}

	attr = bp->attr;

	if (num & 0x1) {
		/*         */
		attr.bp_addr	= user_val;
	} else {
		/*         */
		decode_ctrl_reg(user_val, &ctrl);
		ret = arch_bp_generic_fields(ctrl, &gen_len, &gen_type);
		if (ret)
			goto out;

		if ((gen_type & implied_type) != gen_type) {
			ret = -EINVAL;
			goto out;
		}

		attr.bp_len	= gen_len;
		attr.bp_type	= gen_type;
		attr.disabled	= !ctrl.enabled;
	}

	ret = modify_user_hw_breakpoint(bp, &attr);
out:
	return ret;
}
#endif

/*                                */

static int gpr_get(struct task_struct *target,
		   const struct user_regset *regset,
		   unsigned int pos, unsigned int count,
		   void *kbuf, void __user *ubuf)
{
	struct pt_regs *regs = task_pt_regs(target);

	return user_regset_copyout(&pos, &count, &kbuf, &ubuf,
				   regs,
				   0, sizeof(*regs));
}

static int gpr_set(struct task_struct *target,
		   const struct user_regset *regset,
		   unsigned int pos, unsigned int count,
		   const void *kbuf, const void __user *ubuf)
{
	int ret;
	struct pt_regs newregs;

	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				 &newregs,
				 0, sizeof(newregs));
	if (ret)
		return ret;

	if (!valid_user_regs(&newregs))
		return -EINVAL;

	*task_pt_regs(target) = newregs;
	return 0;
}

static int fpa_get(struct task_struct *target,
		   const struct user_regset *regset,
		   unsigned int pos, unsigned int count,
		   void *kbuf, void __user *ubuf)
{
	return user_regset_copyout(&pos, &count, &kbuf, &ubuf,
				   &task_thread_info(target)->fpstate,
				   0, sizeof(struct user_fp));
}

static int fpa_set(struct task_struct *target,
		   const struct user_regset *regset,
		   unsigned int pos, unsigned int count,
		   const void *kbuf, const void __user *ubuf)
{
	struct thread_info *thread = task_thread_info(target);

	thread->used_cp[1] = thread->used_cp[2] = 1;

	return user_regset_copyin(&pos, &count, &kbuf, &ubuf,
		&thread->fpstate,
		0, sizeof(struct user_fp));
}

#ifdef CONFIG_VFP
/*
                                        
  
                                                                           
                                                
                                                                 
                                                                  
                 
  
                                                
                                                                  
                                    
  
                                                      
                               
  
                       
  
                                                                       
                                                                             
                                                            
 */
static int vfp_get(struct task_struct *target,
		   const struct user_regset *regset,
		   unsigned int pos, unsigned int count,
		   void *kbuf, void __user *ubuf)
{
	int ret;
	struct thread_info *thread = task_thread_info(target);
	struct vfp_hard_struct const *vfp = &thread->vfpstate.hard;
	const size_t user_fpregs_offset = offsetof(struct user_vfp, fpregs);
	const size_t user_fpscr_offset = offsetof(struct user_vfp, fpscr);

	vfp_sync_hwstate(thread);

	ret = user_regset_copyout(&pos, &count, &kbuf, &ubuf,
				  &vfp->fpregs,
				  user_fpregs_offset,
				  user_fpregs_offset + sizeof(vfp->fpregs));
	if (ret)
		return ret;

	ret = user_regset_copyout_zero(&pos, &count, &kbuf, &ubuf,
				       user_fpregs_offset + sizeof(vfp->fpregs),
				       user_fpscr_offset);
	if (ret)
		return ret;

	return user_regset_copyout(&pos, &count, &kbuf, &ubuf,
				   &vfp->fpscr,
				   user_fpscr_offset,
				   user_fpscr_offset + sizeof(vfp->fpscr));
}

/*
                                                                  
                                                                     
           
 */
static int vfp_set(struct task_struct *target,
			  const struct user_regset *regset,
			  unsigned int pos, unsigned int count,
			  const void *kbuf, const void __user *ubuf)
{
	int ret;
	struct thread_info *thread = task_thread_info(target);
	struct vfp_hard_struct new_vfp;
	const size_t user_fpregs_offset = offsetof(struct user_vfp, fpregs);
	const size_t user_fpscr_offset = offsetof(struct user_vfp, fpscr);

	vfp_sync_hwstate(thread);
	new_vfp = thread->vfpstate.hard;

	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				  &new_vfp.fpregs,
				  user_fpregs_offset,
				  user_fpregs_offset + sizeof(new_vfp.fpregs));
	if (ret)
		return ret;

	ret = user_regset_copyin_ignore(&pos, &count, &kbuf, &ubuf,
				user_fpregs_offset + sizeof(new_vfp.fpregs),
				user_fpscr_offset);
	if (ret)
		return ret;

	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				 &new_vfp.fpscr,
				 user_fpscr_offset,
				 user_fpscr_offset + sizeof(new_vfp.fpscr));
	if (ret)
		return ret;

	vfp_flush_hwstate(thread);
	thread->vfpstate.hard = new_vfp;

	return 0;
}
#endif /*            */

enum arm_regset {
	REGSET_GPR,
	REGSET_FPR,
#ifdef CONFIG_VFP
	REGSET_VFP,
#endif
};

static const struct user_regset arm_regsets[] = {
	[REGSET_GPR] = {
		.core_note_type = NT_PRSTATUS,
		.n = ELF_NGREG,
		.size = sizeof(u32),
		.align = sizeof(u32),
		.get = gpr_get,
		.set = gpr_set
	},
	[REGSET_FPR] = {
		/*
                                                               
                                                            
   */
		.core_note_type = NT_PRFPREG,
		.n = sizeof(struct user_fp) / sizeof(u32),
		.size = sizeof(u32),
		.align = sizeof(u32),
		.get = fpa_get,
		.set = fpa_set
	},
#ifdef CONFIG_VFP
	[REGSET_VFP] = {
		/*
                                                                 
                                                          
   */
		.core_note_type = NT_ARM_VFP,
		.n = ARM_VFPREGS_SIZE / sizeof(u32),
		.size = sizeof(u32),
		.align = sizeof(u32),
		.get = vfp_get,
		.set = vfp_set
	},
#endif /*            */
};

static const struct user_regset_view user_arm_view = {
	.name = "arm", .e_machine = ELF_ARCH, .ei_osabi = ELF_OSABI,
	.regsets = arm_regsets, .n = ARRAY_SIZE(arm_regsets)
};

const struct user_regset_view *task_user_regset_view(struct task_struct *task)
{
	return &user_arm_view;
}

long arch_ptrace(struct task_struct *child, long request,
		 unsigned long addr, unsigned long data)
{
	int ret;
	unsigned long __user *datap = (unsigned long __user *) data;

	switch (request) {
		case PTRACE_PEEKUSR:
			ret = ptrace_read_user(child, addr, datap);
			break;

		case PTRACE_POKEUSR:
			ret = ptrace_write_user(child, addr, data);
			break;

		case PTRACE_GETREGS:
			ret = copy_regset_to_user(child,
						  &user_arm_view, REGSET_GPR,
						  0, sizeof(struct pt_regs),
						  datap);
			break;

		case PTRACE_SETREGS:
			ret = copy_regset_from_user(child,
						    &user_arm_view, REGSET_GPR,
						    0, sizeof(struct pt_regs),
						    datap);
			break;

		case PTRACE_GETFPREGS:
			ret = copy_regset_to_user(child,
						  &user_arm_view, REGSET_FPR,
						  0, sizeof(union fp_state),
						  datap);
			break;

		case PTRACE_SETFPREGS:
			ret = copy_regset_from_user(child,
						    &user_arm_view, REGSET_FPR,
						    0, sizeof(union fp_state),
						    datap);
			break;

#ifdef CONFIG_IWMMXT
		case PTRACE_GETWMMXREGS:
			ret = ptrace_getwmmxregs(child, datap);
			break;

		case PTRACE_SETWMMXREGS:
			ret = ptrace_setwmmxregs(child, datap);
			break;
#endif

		case PTRACE_GET_THREAD_AREA:
			ret = put_user(task_thread_info(child)->tp_value,
				       datap);
			break;

		case PTRACE_SET_SYSCALL:
			task_thread_info(child)->syscall = data;
			ret = 0;
			break;

#ifdef CONFIG_CRUNCH
		case PTRACE_GETCRUNCHREGS:
			ret = ptrace_getcrunchregs(child, datap);
			break;

		case PTRACE_SETCRUNCHREGS:
			ret = ptrace_setcrunchregs(child, datap);
			break;
#endif

#ifdef CONFIG_VFP
		case PTRACE_GETVFPREGS:
			ret = copy_regset_to_user(child,
						  &user_arm_view, REGSET_VFP,
						  0, ARM_VFPREGS_SIZE,
						  datap);
			break;

		case PTRACE_SETVFPREGS:
			ret = copy_regset_from_user(child,
						    &user_arm_view, REGSET_VFP,
						    0, ARM_VFPREGS_SIZE,
						    datap);
			break;
#endif

#ifdef CONFIG_HAVE_HW_BREAKPOINT
		case PTRACE_GETHBPREGS:
			if (ptrace_get_breakpoints(child) < 0)
				return -ESRCH;

			ret = ptrace_gethbpregs(child, addr,
						(unsigned long __user *)data);
			ptrace_put_breakpoints(child);
			break;
		case PTRACE_SETHBPREGS:
			if (ptrace_get_breakpoints(child) < 0)
				return -ESRCH;

			ret = ptrace_sethbpregs(child, addr,
						(unsigned long __user *)data);
			ptrace_put_breakpoints(child);
			break;
#endif

		default:
			ret = ptrace_request(child, request, addr, data);
			break;
	}

	return ret;
}

asmlinkage int syscall_trace(int why, struct pt_regs *regs, int scno)
{
	unsigned long ip;

	if (why)
		audit_syscall_exit(regs);
	else
		audit_syscall_entry(AUDIT_ARCH_ARM, scno, regs->ARM_r0,
				    regs->ARM_r1, regs->ARM_r2, regs->ARM_r3);

	if (why == 0 && test_and_clear_thread_flag(TIF_SYSCALL_RESTARTSYS))
		scno = __NR_restart_syscall - __NR_SYSCALL_BASE;
	if (!test_thread_flag(TIF_SYSCALL_TRACE))
		return scno;
	if (!(current->ptrace & PT_PTRACED))
		return scno;

	current_thread_info()->syscall = scno;

	/*
                                            
                               
  */
	ip = regs->ARM_ip;
	regs->ARM_ip = why;

	/*                                                              
                                                */
	ptrace_notify(SIGTRAP | ((current->ptrace & PT_TRACESYSGOOD)
				 ? 0x80 : 0));
	/*
                                                                   
                                                               
                                         
  */
	if (current->exit_code) {
		send_sig(current->exit_code, current, 1);
		current->exit_code = 0;
	}
	regs->ARM_ip = ip;

	return current_thread_info()->syscall;
}
