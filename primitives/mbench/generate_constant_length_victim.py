# Define the content of the C program
c_program_code = """
#include <stdio.h>
#include <asm/param.h>
#include <unistd.h>
#include <inttypes.h>
#include <time.h>
#define BILLION  1000000000L

char mem[4096];

//#define DEBUG  // uncomment to find out how long a loop takes  

int main(){
    int index = 0;

    long int ns, end_ns;
    uint64_t all, end_ts;
    time_t sec, end_sec;
    struct timespec start, end;

    __asm__ volatile(
            "movq   %0, %%r10\\n\\t"
            "mov    %1, %%r11d\\n\\t"
            "mov    $0x0fff, %%r15w\\n\\t"
            :
            : "r"(mem), "r"(index)
            : "r10", "r11", "r15"
        );

    while(1){
#ifdef DEBUG
        clock_gettime(CLOCK_REALTIME, &start);
#endif
        __asm__ volatile(
            PROGRAM
            :
            : 
            : "r10", "r11", "r15"
        );
#ifdef DEBUG
        clock_gettime(CLOCK_REALTIME, &end);
        sec = start.tv_sec;
        ns = start.tv_nsec;
        end_sec = end.tv_sec;
        end_ns = end.tv_nsec;

        all = (uint64_t) sec * BILLION + (uint64_t) ns;
        end_ts = (uint64_t) end_sec * BILLION + (uint64_t) end_ns;

        printf("Current time: %ld nanoseconds since the Epoch\\n", end_ts - all);
#endif
    }

}
"""

# Specify the name of the C source file to be created
c_file_name = "constant_length_victim.c"
asm_program = """"movb   %%r11b, (%%r10, %%r11)\\n\\t"
            "inc    %%r11w\\n\\t"
            "and    %%r15w, %%r11w\\n\\t" \n\t\t\t"""

c_program_code = c_program_code.replace("PROGRAM", asm_program * 1000000)

# Write the C program code to the file
with open(c_file_name, "w") as c_file:
    c_file.write(c_program_code)


