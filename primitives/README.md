# Controlled Preemption Primitives
The most important parameter for conducting controlled preemption, or all other timer-interrupt based side-channel attack, is to configure the right **interrupt interval**. If the interval is too large, the victim may execute too many instructions, leading to inaccurate side-channel measurement. If the interval is too small, the victim may not make any progress, thus waste the preemption budget. 

We provide eBPF tools to track the effectiveness of our interrupt interval. We also provide simple victim and attacker program for microbenchmark. 

## Run Microbenchmark
Please follow the instruction to run microbenchmark: 
1. Go to the mbench folder and compile all relevant program
```
cd mbench
make
``` 
2. Pin the victim program into one isolated CPU core specified as a boot parameter and run as a background process
```
taskset -c 4 ./constant_length_victim &
```
This command will run the PID of the victim program ```PID```
3. Run either attacker ```attack_nanosleep``` or ```attack_posix_timer``` with a interval as integer
```
taskset -c 4 ./attacker_nanosleep 1200
```
4. Run the eBPF program (TODO)

## Run Microbenchmark with Performance Degradation
The code for running microbenchmark with performance degradation is almost the same with previous experiments. 
One difference is we need to know what the address of the victim code page is. 
For simplicity, we run both victim and the attacker in the same process. 






