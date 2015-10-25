#include "common.h"
#include "memory.h"
#include <string.h>
#include <elf.h>

#define ELF_OFFSET_IN_DISK 0

#ifdef HAS_DEVICE
void ide_read(uint8_t *, uint32_t, uint32_t);
#else

void ramdisk_read(uint8_t *, uint32_t, uint32_t);
#endif
void ramdisk_write(uint8_t*,uint32_t,uint32_t);
#define STACK_SIZE (1 << 20)

void create_video_mapping();
uint32_t get_ucr3();
#define SIZE (0xa0000-1)
uint32_t loader() {
	Elf32_Ehdr *elf;
	Elf32_Phdr *ph = NULL;

	uint8_t buf[SIZE];

#ifdef HAS_DEVICE
	ide_read(buf, ELF_OFFSET_IN_DISK, SIZE);
#else
	ramdisk_read(buf, ELF_OFFSET_IN_DISK, SIZE);
#endif

	elf = (void*)buf;

	/* TODO: fix the magic number with the correct one */
	const uint32_t elf_magic = 0x464c457f;
	uint32_t *p_magic = (void *)buf;
	nemu_assert(*p_magic == elf_magic);
       int i;
	/* Load each program segment */
//	panic("please implement me");
	for(i=0;i<elf->e_phnum;++i) {
		/* Scan the program header table, load each segment into memory */
	ph = (void*)(buf + elf->e_ehsize + i * elf->e_phentsize);
		if(ph->p_type == PT_LOAD) {

			/* TODO: read the content of the segment from the ELF file 
			 * to the memory region [VirtAddr, VirtAddr + FileSiz)
			 */
			//int j;
			uint32_t hwaddr=mm_malloc(ph->p_vaddr,ph->p_memsz);
			memcpy((void*) hwaddr,(void*)(buf+ph->p_offset),ph->p_filesz);
		//	memcpy((void *)ph->p_vaddr, (void *)(buf + ph->p_offset), ph->p_filesz);
			 
	          //      for(i = ph->p_filesz; i < ph->p_memsz; i ++) 
		//	memcpy((void *)ph->p_vaddr + i, (void *)0, 1);
			memset((void*) hwaddr + ph->p_filesz, 0, ph->p_memsz - ph->p_filesz);
		// uint8_t zero=0;
//	                for(j=ph->p_filesz;j<ph->p_memsz;++j)
//				ramdisk_write(&zero, ph->p_vaddr + j, 1);
			//memcpy(ph->p_filesz,&zero,ph->p_memsz-ph->filesz);
			/* TODO: zero the memory region 
			 * [VirtAddr + FileSiz, VirtAddr + MemSiz)
			 */


#ifdef IA32_PAGE
			/* Record the program break for future use. */
			extern uint32_t brk;
			uint32_t new_brk = ph->p_vaddr + ph->p_memsz - 1;
			if(brk < new_brk) { brk = new_brk; }
#endif
		}
	}

	volatile uint32_t entry = elf->e_entry;

#ifdef IA32_PAGE
	mm_malloc(KOFFSET - STACK_SIZE, STACK_SIZE);

#ifdef HAS_DEVICE
	create_video_mapping();
#endif

	write_cr3(get_ucr3());
#endif

	return entry;
}
