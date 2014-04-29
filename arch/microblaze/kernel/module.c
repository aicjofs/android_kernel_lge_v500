/*
 * Copyright (C) 2007-2009 Michal Simek <monstr@monstr.eu>
 * Copyright (C) 2007-2009 PetaLogix
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/moduleloader.h>
#include <linux/kernel.h>
#include <linux/elf.h>
#include <linux/vmalloc.h>
#include <linux/fs.h>
#include <linux/string.h>

#include <asm/pgtable.h>
#include <asm/cacheflush.h>

int apply_relocate_add(Elf32_Shdr *sechdrs, const char *strtab,
	unsigned int symindex, unsigned int relsec, struct module *module)
{

	unsigned int i;
	Elf32_Rela *rela = (void *)sechdrs[relsec].sh_addr;
	Elf32_Sym *sym;
	unsigned long int *location;
	unsigned long int value;
#if __GNUC__ < 4
	unsigned long int old_value;
#endif

	pr_debug("Applying add relocation section %u to %u\n",
		relsec, sechdrs[relsec].sh_info);

	for (i = 0; i < sechdrs[relsec].sh_size / sizeof(*rela); i++) {

		location = (void *)sechdrs[sechdrs[relsec].sh_info].sh_addr +
				rela[i].r_offset;
		sym = (Elf32_Sym *)sechdrs[symindex].sh_addr +
			ELF32_R_SYM(rela[i].r_info);
		value = sym->st_value + rela[i].r_addend;

		switch (ELF32_R_TYPE(rela[i].r_info)) {

		/*
                                                             
                                                            
                                                             
                                  
   */

		case R_MICROBLAZE_32:
#if __GNUC__ < 4
			old_value = *location;
			*location = value + old_value;

			pr_debug("R_MICROBLAZE_32 (%08lx->%08lx)\n",
				old_value, value);
#else
			*location = value;
#endif
			break;

		case R_MICROBLAZE_64:
#if __GNUC__ < 4
			/*                                              */
			old_value = ((location[0] & 0x0000FFFF) << 16) |
					(location[1] & 0x0000FFFF);
			value += old_value;
#endif
			location[0] = (location[0] & 0xFFFF0000) |
					(value >> 16);
			location[1] = (location[1] & 0xFFFF0000) |
					(value & 0xFFFF);
#if __GNUC__ < 4
			pr_debug("R_MICROBLAZE_64 (%08lx->%08lx)\n",
				old_value, value);
#endif
			break;

		case R_MICROBLAZE_64_PCREL:
#if __GNUC__ < 4
			old_value = (location[0] & 0xFFFF) << 16 |
				(location[1] & 0xFFFF);
			value -= old_value;
#endif
			value -= (unsigned long int)(location) + 4;
			location[0] = (location[0] & 0xFFFF0000) |
					(value >> 16);
			location[1] = (location[1] & 0xFFFF0000) |
					(value & 0xFFFF);
			pr_debug("R_MICROBLAZE_64_PCREL (%08lx)\n",
				value);
			break;

		case R_MICROBLAZE_32_PCREL_LO:
			pr_debug("R_MICROBLAZE_32_PCREL_LO\n");
			break;

		case R_MICROBLAZE_64_NONE:
			pr_debug("R_MICROBLAZE_64_NONE\n");
			break;

		case R_MICROBLAZE_NONE:
			pr_debug("R_MICROBLAZE_NONE\n");
			break;

		default:
			printk(KERN_ERR "module %s: "
				"Unknown relocation: %u\n",
				module->name,
				ELF32_R_TYPE(rela[i].r_info));
			return -ENOEXEC;
		}
	}
	return 0;
}

int module_finalize(const Elf32_Ehdr *hdr, const Elf_Shdr *sechdrs,
		struct module *module)
{
	flush_dcache();
	return 0;
}
