#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/mman.h>

#define PRU_DDR 0x00000000  // DDR starts at 0x0000_0000 to 0x0007_FFFF
#define DDR_LEN 0x100

unsigned int *pruDDR_ptr;

int main(void) {
    unsigned int *pru;
    
    int fd;
    
    fd = open( "/dev/mem", O_RDWR | O_SYNC);
    if (fd == -1) {
        printf ("ERROR: could not open /dev/mem.\n\n");
        return 1;
    }
    
    pru = mmap(0, 
               DDR_LEN,
               PROT_READ,
               MAP_SHARED,
               fd,
               PRU_DDR
               );
             
    if (pru == MAP_FAILED) {
        printf ("ERROR: could not map memory.\n\n");
        return 1;
    }
    
    pruDDR_ptr = pru;
    
    printf("%X\n", pruDDR_ptr[0]);
    
    if(munmap(pru, DDR_LEN)) {
        printf("munmap failed\n");
    } else {
        printf("munmap succeeded\n");
    }
    
    return 0;
}
