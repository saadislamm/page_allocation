#include <stdio.h>
#include <stdint.h>		// For uint64_t
#include <fcntl.h>		// For O_RDONLY in get_physical_addr fn
#include <unistd.h>		// For pread in get_physical_addr fn
#include <sys/mman.h>	// For mmap

#define PAGE_COUNT 10
#define PAGE_SIZE 4096


// get_physical_addr function has been taken from
// https://github.com/IAIK/flipfloyd/blob/master/waylaying/check.c

static uint64_t get_physical_addr(uint64_t virtual_addr) {
  static int g_pagemap_fd = -1;
  uint64_t value;
  
  // open the pagemap
  if(g_pagemap_fd == -1) {
      g_pagemap_fd = open("/proc/self/pagemap", O_RDONLY);
  }
  if(g_pagemap_fd == -1) return 0;
  
  // read physical address
  off_t offset = (virtual_addr / 4096) * sizeof(value);
  int got = pread(g_pagemap_fd, &value, sizeof(value), offset);
  if(got != 8) return 0;

  // Check the "page present" flag.
  if(!(value & (1ULL << 63))) return 0;

  // return physical address
  uint64_t frame_num = value & ((1ULL << 55) - 1);
  return (frame_num * 4096) | (virtual_addr & (4095));
}

void main() {

	uint8_t * buffer;
	
	printf("____________________________________________________\n");
	printf("\n			MAP\n");
	printf("____________________________________________________\n");
	buffer = mmap(NULL, PAGE_COUNT * PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_POPULATE | MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);			// Mapping all pages at once.
	for (int i = 0; i < PAGE_COUNT; i++) {
		printf("Virtual : %p \t", &buffer[i*PAGE_SIZE]);
		printf("Physical : %lx \n", get_physical_addr((uint64_t)&buffer[i*PAGE_SIZE]));
	}
	
	printf("____________________________________________________\n");
	printf("\n			MUNMAP\n");
	printf("____________________________________________________\n");
	
	//munmap(&buffer[0], PAGE_SIZE*PAGE_COUNT);		// Unmap all pages at once.
	for (int i = 0; i < PAGE_COUNT; i++) {
		munmap(&buffer[i*PAGE_SIZE], PAGE_SIZE);	// Unmapping one page at a time.
	}
	for (int i = 0; i < PAGE_COUNT; i++) {
		printf("Virtual : %p \t", &buffer[i*PAGE_SIZE]);
		printf("Physical : %lx \n", get_physical_addr((uint64_t)&buffer[i*PAGE_SIZE]));
	}
	
	printf("____________________________________________________\n");
	printf("\n			MAP\n");
	printf("____________________________________________________\n");
	buffer = mmap(NULL, PAGE_COUNT * PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_POPULATE | MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);			// Mapping all pages at once.
	for (int i = 0; i < PAGE_COUNT; i++) {
		printf("Virtual : %p \t", &buffer[i*PAGE_SIZE]);
		printf("Physical : %lx \n", get_physical_addr((uint64_t)&buffer[i*PAGE_SIZE]));
	}
}
