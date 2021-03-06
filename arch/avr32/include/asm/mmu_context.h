/*
 * Copyright (C) 2004-2006 Atmel Corporation
 *
 * ASID handling taken from SH implementation.
 *   Copyright (C) 1999 Niibe Yutaka
 *   Copyright (C) 2003 Paul Mundt
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#ifndef __ASM_AVR32_MMU_CONTEXT_H
#define __ASM_AVR32_MMU_CONTEXT_H

#include <asm/tlbflush.h>
#include <asm/sysreg.h>
#include <asm-generic/mm_hooks.h>

/*
                                            
                           
                                         
 */
#define MMU_CONTEXT_ASID_MASK		0x000000ff
#define MMU_CONTEXT_VERSION_MASK	0xffffff00
#define MMU_CONTEXT_FIRST_VERSION       0x00000100
#define NO_CONTEXT			0

#define MMU_NO_ASID			0x100

/*                          */
#define MMU_VPN_MASK	0xfffff000

/*                                */
extern unsigned long mmu_context_cache;

/*
                            
 */
static inline void
get_mmu_context(struct mm_struct *mm)
{
	unsigned long mc = mmu_context_cache;

	if (((mm->context ^ mc) & MMU_CONTEXT_VERSION_MASK) == 0)
		/*                             */
		return;

	/*                                                       */
	mc = ++mmu_context_cache;
	if (!(mc & MMU_CONTEXT_ASID_MASK)) {
		/*
                                                 
                                       
   */
		flush_tlb_all();
		/*
                                               
                               
   */
		if (!mc)
			mmu_context_cache = mc = MMU_CONTEXT_FIRST_VERSION;
	}
	mm->context = mc;
}

/*
                                                          
            
 */
static inline int init_new_context(struct task_struct *tsk,
				       struct mm_struct *mm)
{
	mm->context = NO_CONTEXT;
	return 0;
}

/*
                                                              
                     
 */
static inline void destroy_context(struct mm_struct *mm)
{
	/*            */
}

static inline void set_asid(unsigned long asid)
{
	/*                                    */
	sysreg_write(TLBEHI, asid & MMU_CONTEXT_ASID_MASK);
	cpu_sync_pipeline();
}

static inline unsigned long get_asid(void)
{
	unsigned long asid;

	asid = sysreg_read(TLBEHI);
	return asid & MMU_CONTEXT_ASID_MASK;
}

static inline void activate_context(struct mm_struct *mm)
{
	get_mmu_context(mm);
	set_asid(mm->context & MMU_CONTEXT_ASID_MASK);
}

static inline void switch_mm(struct mm_struct *prev,
				 struct mm_struct *next,
				 struct task_struct *tsk)
{
	if (likely(prev != next)) {
		unsigned long __pgdir = (unsigned long)next->pgd;

		sysreg_write(PTBR, __pgdir);
		activate_context(next);
	}
}

#define deactivate_mm(tsk,mm) do { } while(0)

#define activate_mm(prev, next) switch_mm((prev), (next), NULL)

static inline void
enter_lazy_tlb(struct mm_struct *mm, struct task_struct *tsk)
{
}


static inline void enable_mmu(void)
{
	sysreg_write(MMUCR, (SYSREG_BIT(MMUCR_S)
			     | SYSREG_BIT(E)
			     | SYSREG_BIT(MMUCR_I)));
	nop(); nop(); nop(); nop(); nop(); nop(); nop(); nop();

	if (mmu_context_cache == NO_CONTEXT)
		mmu_context_cache = MMU_CONTEXT_FIRST_VERSION;

	set_asid(mmu_context_cache & MMU_CONTEXT_ASID_MASK);
}

static inline void disable_mmu(void)
{
	sysreg_write(MMUCR, SYSREG_BIT(MMUCR_S));
}

#endif /*                           */
