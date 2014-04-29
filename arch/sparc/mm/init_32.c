/*
 *  linux/arch/sparc/mm/init.c
 *
 *  Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 *  Copyright (C) 1995 Eddie C. Dost (ecd@skynet.be)
 *  Copyright (C) 1998 Jakub Jelinek (jj@sunsite.mff.cuni.cz)
 *  Copyright (C) 2000 Anton Blanchard (anton@samba.org)
 */

#include <linux/module.h>
#include <linux/signal.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/string.h>
#include <linux/types.h>
#include <linux/ptrace.h>
#include <linux/mman.h>
#include <linux/mm.h>
#include <linux/swap.h>
#include <linux/initrd.h>
#include <linux/init.h>
#include <linux/highmem.h>
#include <linux/bootmem.h>
#include <linux/pagemap.h>
#include <linux/poison.h>
#include <linux/gfp.h>

#include <asm/sections.h>
#include <asm/vac-ops.h>
#include <asm/page.h>
#include <asm/pgtable.h>
#include <asm/vaddrs.h>
#include <asm/pgalloc.h>	/*                                           */
#include <asm/tlb.h>
#include <asm/prom.h>
#include <asm/leon.h>

unsigned long *sparc_valid_addr_bitmap;
EXPORT_SYMBOL(sparc_valid_addr_bitmap);

unsigned long phys_base;
EXPORT_SYMBOL(phys_base);

unsigned long pfn_base;
EXPORT_SYMBOL(pfn_base);

unsigned long page_kernel;
EXPORT_SYMBOL(page_kernel);

struct sparc_phys_banks sp_banks[SPARC_PHYS_BANKS+1];
unsigned long sparc_unmapped_base;

struct pgtable_cache_struct pgt_quicklists;

/*                       */
extern unsigned int sparc_ramdisk_image;
extern unsigned int sparc_ramdisk_size;

unsigned long highstart_pfn, highend_pfn;

pte_t *kmap_pte;
pgprot_t kmap_prot;

#define kmap_get_fixmap_pte(vaddr) \
	pte_offset_kernel(pmd_offset(pgd_offset_k(vaddr), (vaddr)), (vaddr))

void __init kmap_init(void)
{
	/*                          */
	kmap_pte = kmap_get_fixmap_pte(__fix_to_virt(FIX_KMAP_BEGIN));
	kmap_prot = __pgprot(SRMMU_ET_PTE | SRMMU_PRIV | SRMMU_CACHE);
}

void show_mem(unsigned int filter)
{
	printk("Mem-info:\n");
	show_free_areas(filter);
	printk("Free swap:       %6ldkB\n",
	       get_nr_swap_pages() << (PAGE_SHIFT-10));
	printk("%ld pages of RAM\n", totalram_pages);
	printk("%ld free pages\n", nr_free_pages());
#if 0 /*                                              */
	printk("%ld pages in page table cache\n",pgtable_cache_size);
#ifndef CONFIG_SMP
	if (sparc_cpu_model == sun4m || sparc_cpu_model == sun4d)
		printk("%ld entries in page dir cache\n",pgd_cache_size);
#endif	
#endif
}

void __init sparc_context_init(int numctx)
{
	int ctx;

	ctx_list_pool = __alloc_bootmem(numctx * sizeof(struct ctx_list), SMP_CACHE_BYTES, 0UL);

	for(ctx = 0; ctx < numctx; ctx++) {
		struct ctx_list *clist;

		clist = (ctx_list_pool + ctx);
		clist->ctx_number = ctx;
		clist->ctx_mm = NULL;
	}
	ctx_free.next = ctx_free.prev = &ctx_free;
	ctx_used.next = ctx_used.prev = &ctx_used;
	for(ctx = 0; ctx < numctx; ctx++)
		add_to_free_ctxlist(ctx_list_pool + ctx);
}

extern unsigned long cmdline_memory_size;
unsigned long last_valid_pfn;

unsigned long calc_highpages(void)
{
	int i;
	int nr = 0;

	for (i = 0; sp_banks[i].num_bytes != 0; i++) {
		unsigned long start_pfn = sp_banks[i].base_addr >> PAGE_SHIFT;
		unsigned long end_pfn = (sp_banks[i].base_addr + sp_banks[i].num_bytes) >> PAGE_SHIFT;

		if (end_pfn <= max_low_pfn)
			continue;

		if (start_pfn < max_low_pfn)
			start_pfn = max_low_pfn;

		nr += end_pfn - start_pfn;
	}

	return nr;
}

static unsigned long calc_max_low_pfn(void)
{
	int i;
	unsigned long tmp = pfn_base + (SRMMU_MAXMEM >> PAGE_SHIFT);
	unsigned long curr_pfn, last_pfn;

	last_pfn = (sp_banks[0].base_addr + sp_banks[0].num_bytes) >> PAGE_SHIFT;
	for (i = 1; sp_banks[i].num_bytes != 0; i++) {
		curr_pfn = sp_banks[i].base_addr >> PAGE_SHIFT;

		if (curr_pfn >= tmp) {
			if (last_pfn < tmp)
				tmp = last_pfn;
			break;
		}

		last_pfn = (sp_banks[i].base_addr + sp_banks[i].num_bytes) >> PAGE_SHIFT;
	}

	return tmp;
}

unsigned long __init bootmem_init(unsigned long *pages_avail)
{
	unsigned long bootmap_size, start_pfn;
	unsigned long end_of_phys_memory = 0UL;
	unsigned long bootmap_pfn, bytes_avail, size;
	int i;

	bytes_avail = 0UL;
	for (i = 0; sp_banks[i].num_bytes != 0; i++) {
		end_of_phys_memory = sp_banks[i].base_addr +
			sp_banks[i].num_bytes;
		bytes_avail += sp_banks[i].num_bytes;
		if (cmdline_memory_size) {
			if (bytes_avail > cmdline_memory_size) {
				unsigned long slack = bytes_avail - cmdline_memory_size;

				bytes_avail -= slack;
				end_of_phys_memory -= slack;

				sp_banks[i].num_bytes -= slack;
				if (sp_banks[i].num_bytes == 0) {
					sp_banks[i].base_addr = 0xdeadbeef;
				} else {
					sp_banks[i+1].num_bytes = 0;
					sp_banks[i+1].base_addr = 0xdeadbeef;
				}
				break;
			}
		}
	}

	/*                                                         
            
  */
	start_pfn  = (unsigned long)__pa(PAGE_ALIGN((unsigned long) &_end));

	/*                                                            */
	start_pfn >>= PAGE_SHIFT;

	bootmap_pfn = start_pfn;

	max_pfn = end_of_phys_memory >> PAGE_SHIFT;

	max_low_pfn = max_pfn;
	highstart_pfn = highend_pfn = max_pfn;

	if (max_low_pfn > pfn_base + (SRMMU_MAXMEM >> PAGE_SHIFT)) {
		highstart_pfn = pfn_base + (SRMMU_MAXMEM >> PAGE_SHIFT);
		max_low_pfn = calc_max_low_pfn();
		printk(KERN_NOTICE "%ldMB HIGHMEM available.\n",
		    calc_highpages() >> (20 - PAGE_SHIFT));
	}

#ifdef CONFIG_BLK_DEV_INITRD
	/*                                                                          */
	if (sparc_ramdisk_image) {
		if (sparc_ramdisk_image >= (unsigned long)&_end - 2 * PAGE_SIZE)
			sparc_ramdisk_image -= KERNBASE;
		initrd_start = sparc_ramdisk_image + phys_base;
		initrd_end = initrd_start + sparc_ramdisk_size;
		if (initrd_end > end_of_phys_memory) {
			printk(KERN_CRIT "initrd extends beyond end of memory "
		                 	 "(0x%016lx > 0x%016lx)\ndisabling initrd\n",
			       initrd_end, end_of_phys_memory);
			initrd_start = 0;
		}
		if (initrd_start) {
			if (initrd_start >= (start_pfn << PAGE_SHIFT) &&
			    initrd_start < (start_pfn << PAGE_SHIFT) + 2 * PAGE_SIZE)
				bootmap_pfn = PAGE_ALIGN (initrd_end) >> PAGE_SHIFT;
		}
	}
#endif	
	/*                                     */
	bootmap_size = init_bootmem_node(NODE_DATA(0), bootmap_pfn, pfn_base,
					 max_low_pfn);

	/*                                                    
              
  */
	*pages_avail = 0;
	for (i = 0; sp_banks[i].num_bytes != 0; i++) {
		unsigned long curr_pfn, last_pfn;

		curr_pfn = sp_banks[i].base_addr >> PAGE_SHIFT;
		if (curr_pfn >= max_low_pfn)
			break;

		last_pfn = (sp_banks[i].base_addr + sp_banks[i].num_bytes) >> PAGE_SHIFT;
		if (last_pfn > max_low_pfn)
			last_pfn = max_low_pfn;

		/*
                                                 
                                       
   */
		if (last_pfn <= curr_pfn)
			continue;

		size = (last_pfn - curr_pfn) << PAGE_SHIFT;
		*pages_avail += last_pfn - curr_pfn;

		free_bootmem(sp_banks[i].base_addr, size);
	}

#ifdef CONFIG_BLK_DEV_INITRD
	if (initrd_start) {
		/*                                */
		size = initrd_end - initrd_start;
		reserve_bootmem(initrd_start, size, BOOTMEM_DEFAULT);
		*pages_avail -= PAGE_ALIGN(size) >> PAGE_SHIFT;

		initrd_start = (initrd_start - phys_base) + PAGE_OFFSET;
		initrd_end = (initrd_end - phys_base) + PAGE_OFFSET;		
	}
#endif
	/*                                   */
	size = (start_pfn << PAGE_SHIFT) - phys_base;
	reserve_bootmem(phys_base, size, BOOTMEM_DEFAULT);
	*pages_avail -= PAGE_ALIGN(size) >> PAGE_SHIFT;

	/*                                                    
                                                      
                        
  */
	size = bootmap_size;
	reserve_bootmem((bootmap_pfn << PAGE_SHIFT), size, BOOTMEM_DEFAULT);
	*pages_avail -= PAGE_ALIGN(size) >> PAGE_SHIFT;

	return max_pfn;
}

/*
                  
  
                                                                  
                                                             
                                                                 
                                
  
                                                 
 */
static int pgt_cache_water[2] = { 25, 50 };

void check_pgt_cache(void)
{
	do_check_pgt_cache(pgt_cache_water[0], pgt_cache_water[1]);
}

/*
                                                                  
                                                           
  
 */
extern void sun4c_paging_init(void);
extern void srmmu_paging_init(void);
extern void device_scan(void);

pgprot_t PAGE_SHARED __read_mostly;
EXPORT_SYMBOL(PAGE_SHARED);

void __init paging_init(void)
{
	switch(sparc_cpu_model) {
	case sun4c:
	case sun4e:
	case sun4:
		sun4c_paging_init();
		sparc_unmapped_base = 0xe0000000;
		BTFIXUPSET_SETHI(sparc_unmapped_base, 0xe0000000);
		break;
	case sparc_leon:
		leon_init();
		/*              */
	case sun4m:
	case sun4d:
		srmmu_paging_init();
		sparc_unmapped_base = 0x50000000;
		BTFIXUPSET_SETHI(sparc_unmapped_base, 0x50000000);
		break;
	default:
		prom_printf("paging_init: Cannot init paging on this Sparc\n");
		prom_printf("paging_init: sparc_cpu_model = %d\n", sparc_cpu_model);
		prom_printf("paging_init: Halting...\n");
		prom_halt();
	}

	/*                                                                        */
	protection_map[0] = PAGE_NONE;
	protection_map[1] = PAGE_READONLY;
	protection_map[2] = PAGE_COPY;
	protection_map[3] = PAGE_COPY;
	protection_map[4] = PAGE_READONLY;
	protection_map[5] = PAGE_READONLY;
	protection_map[6] = PAGE_COPY;
	protection_map[7] = PAGE_COPY;
	protection_map[8] = PAGE_NONE;
	protection_map[9] = PAGE_READONLY;
	protection_map[10] = PAGE_SHARED;
	protection_map[11] = PAGE_SHARED;
	protection_map[12] = PAGE_READONLY;
	protection_map[13] = PAGE_READONLY;
	protection_map[14] = PAGE_SHARED;
	protection_map[15] = PAGE_SHARED;
	btfixup();
	prom_build_devicetree();
	of_fill_in_cpu_data();
	device_scan();
}

static void __init taint_real_pages(void)
{
	int i;

	for (i = 0; sp_banks[i].num_bytes; i++) {
		unsigned long start, end;

		start = sp_banks[i].base_addr;
		end = start + sp_banks[i].num_bytes;

		while (start < end) {
			set_bit(start >> 20, sparc_valid_addr_bitmap);
			start += PAGE_SIZE;
		}
	}
}

static void map_high_region(unsigned long start_pfn, unsigned long end_pfn)
{
	unsigned long tmp;

#ifdef CONFIG_DEBUG_HIGHMEM
	printk("mapping high region %08lx - %08lx\n", start_pfn, end_pfn);
#endif

	for (tmp = start_pfn; tmp < end_pfn; tmp++) {
		struct page *page = pfn_to_page(tmp);

		ClearPageReserved(page);
		init_page_count(page);
		__free_page(page);
		totalhigh_pages++;
	}
}

void __init mem_init(void)
{
	int codepages = 0;
	int datapages = 0;
	int initpages = 0; 
	int reservedpages = 0;
	int i;

	if (PKMAP_BASE+LAST_PKMAP*PAGE_SIZE >= FIXADDR_START) {
		prom_printf("BUG: fixmap and pkmap areas overlap\n");
		prom_printf("pkbase: 0x%lx pkend: 0x%lx fixstart 0x%lx\n",
		       PKMAP_BASE,
		       (unsigned long)PKMAP_BASE+LAST_PKMAP*PAGE_SIZE,
		       FIXADDR_START);
		prom_printf("Please mail sparclinux@vger.kernel.org.\n");
		prom_halt();
	}


	/*                      */
	memset((void *)&empty_zero_page, 0, PAGE_SIZE);

	i = last_valid_pfn >> ((20 - PAGE_SHIFT) + 5);
	i += 1;
	sparc_valid_addr_bitmap = (unsigned long *)
		__alloc_bootmem(i << 2, SMP_CACHE_BYTES, 0UL);

	if (sparc_valid_addr_bitmap == NULL) {
		prom_printf("mem_init: Cannot alloc valid_addr_bitmap.\n");
		prom_halt();
	}
	memset(sparc_valid_addr_bitmap, 0, i << 2);

	taint_real_pages();

	max_mapnr = last_valid_pfn - pfn_base;
	high_memory = __va(max_low_pfn << PAGE_SHIFT);

	totalram_pages = free_all_bootmem();

	for (i = 0; sp_banks[i].num_bytes != 0; i++) {
		unsigned long start_pfn = sp_banks[i].base_addr >> PAGE_SHIFT;
		unsigned long end_pfn = (sp_banks[i].base_addr + sp_banks[i].num_bytes) >> PAGE_SHIFT;

		num_physpages += sp_banks[i].num_bytes >> PAGE_SHIFT;

		if (end_pfn <= highstart_pfn)
			continue;

		if (start_pfn < highstart_pfn)
			start_pfn = highstart_pfn;

		map_high_region(start_pfn, end_pfn);
	}
	
	totalram_pages += totalhigh_pages;

	codepages = (((unsigned long) &_etext) - ((unsigned long)&_start));
	codepages = PAGE_ALIGN(codepages) >> PAGE_SHIFT;
	datapages = (((unsigned long) &_edata) - ((unsigned long)&_etext));
	datapages = PAGE_ALIGN(datapages) >> PAGE_SHIFT;
	initpages = (((unsigned long) &__init_end) - ((unsigned long) &__init_begin));
	initpages = PAGE_ALIGN(initpages) >> PAGE_SHIFT;

	/*                                                                */
	for (i=0; i < max_low_pfn; i++)
		if (test_bit(i >> (20 - PAGE_SHIFT), sparc_valid_addr_bitmap)
		    && PageReserved(pfn_to_page(i)))
			reservedpages++;

	printk(KERN_INFO "Memory: %luk/%luk available (%dk kernel code, %dk reserved, %dk data, %dk init, %ldk highmem)\n",
	       nr_free_pages() << (PAGE_SHIFT-10),
	       num_physpages << (PAGE_SHIFT - 10),
	       codepages << (PAGE_SHIFT-10),
	       reservedpages << (PAGE_SHIFT - 10),
	       datapages << (PAGE_SHIFT-10), 
	       initpages << (PAGE_SHIFT-10),
	       totalhigh_pages << (PAGE_SHIFT-10));
}

void free_initmem (void)
{
	unsigned long addr;
	unsigned long freed;

	addr = (unsigned long)(&__init_begin);
	freed = (unsigned long)(&__init_end) - addr;
	for (; addr < (unsigned long)(&__init_end); addr += PAGE_SIZE) {
		struct page *p;

		memset((void *)addr, POISON_FREE_INITMEM, PAGE_SIZE);
		p = virt_to_page(addr);

		ClearPageReserved(p);
		init_page_count(p);
		__free_page(p);
		totalram_pages++;
		num_physpages++;
	}
	printk(KERN_INFO "Freeing unused kernel memory: %ldk freed\n",
		freed >> 10);
}

#ifdef CONFIG_BLK_DEV_INITRD
void free_initrd_mem(unsigned long start, unsigned long end)
{
	if (start < end)
		printk(KERN_INFO "Freeing initrd memory: %ldk freed\n",
			(end - start) >> 10);
	for (; start < end; start += PAGE_SIZE) {
		struct page *p;

		memset((void *)start, POISON_FREE_INITMEM, PAGE_SIZE);
		p = virt_to_page(start);

		ClearPageReserved(p);
		init_page_count(p);
		__free_page(p);
		totalram_pages++;
		num_physpages++;
	}
}
#endif

void sparc_flush_page_to_ram(struct page *page)
{
	unsigned long vaddr = (unsigned long)page_address(page);

	if (vaddr)
		__flush_page_to_ram(vaddr);
}
EXPORT_SYMBOL(sparc_flush_page_to_ram);
