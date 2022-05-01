#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/mman.h>

#define PRU_ADDR        0x4A300000      // Start of the PRU Memory (TRM Page 184)
#define PRU_LEN         0x80000         // Length of PRU 
#define SHM_OFFSET      2048
#define PRU_SHAREDMEM   0x4000          // Points to the start of the shared memory

unsigned int *pruShared_ptr;

int main(void) {
    unsigned int *pru;
    
    int fd, i;
    
    FILE *fp = fopen("shared_results.txt", "w+");
    
    fd = open( "/dev/mem", O_RDWR | O_SYNC);
    if (fd == -1) {
        printf ("ERROR: could not open /dev/mem.\n\n");
        return 1;
    }
    
    pru = mmap(0, 
               PRU_LEN,
               PROT_READ,
               MAP_SHARED,
               fd,
               PRU_ADDR
               );
             
    if (pru == MAP_FAILED) {
        printf ("ERROR: could not map memory.\n\n");
        return 1;
    }
    
    pruShared_ptr = pru + PRU_SHAREDMEM;
    
    for (i = 0; i < 12228; i++) {
        fprintf(fp, "Address %X: %X\n", &pruShared_ptr[i], pruShared_ptr[i]);
    }
    
    fclose(fp);

    if(munmap(pru, PRU_LEN)) {
        printf("munmap failed\n");
    } else {
        printf("munmap succeeded\n");
    }
    
    return 0;
}
