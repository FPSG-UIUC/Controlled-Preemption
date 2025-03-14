# Controlled Preemption
This repository is the open-source code for our ASPLOS 2025 paper: *Controlled Preemption: Amplifying Side-Channel Attacks from Userspace*

## Contact
Feel free to contact us if you have any questions about the paper!

Yongye Zhu [yongye.zhu@berkeley.edu](mailto:yongye.zhu@berkeley.edu)

## Abstract
Microarchitectural side channels are an ongoing threat in today’s systems.
Yet, many side-channel methodologies suffer from low temporal resolution measurement, which can either preclude or significantly complicate an attack.

This paper introduces *Controlled Preemption*, an attack primitive enabling a *single unprivileged* (user-level) attacker thread to repeatedly preempt a victim thread after colocating with that victim thread on the same logical core.
Between preemptions, the victim thread executes zero to several instructions---sufficiently few to enable high-resolution side channel measurements.

The key idea in *Controlled Preemption* is to exploit scheduler fairness heuristics. 
Namely, that modern thread schedulers give a thread $A$ the ability to preempt another thread $B$ until a fairness tripwire (signaling that $A$ is starving $B$) fires.
We show how this idea enables hundreds of short preemptions before tripping the fairness tripwire is robust to noise and applies to both the Linux CFS and EEVDF schedulers.
We also develop a technique that helps colocate the attacker and victim threads
onto the same logical core, an attacker capability overlooked by prior work.

Our evaluation tests *Controlled Preemption* in the context of several different victim programs, victim privilege levels (inside and outside of Intel SGX) and 
choices of side channel.
In each attack, we demonstrate results that are competitive with prior work but make fewer assumptions (e.g., require only user-level privilege or require fewer colocated attacker threads).

## Repository Structure
This repository comprises the following artifacts:
```
.
|-- primitives: evaluation scripts on controlled preemption primitives
|-- poc: proof-of-concept attacks
```

## System Setup
All the experiments are run on Ubuntu 22.04.4 LTS with Intel Core i9-9900K machine and 64GB RAM. We use off-the-shelf Linux Kernel 6.5 for experimenst on CFS and 6.12-rc1 for EEVDF.
### Compiling Kernels
Our experiments requires kernel support for eBPF and kprobe. Off-the-shelf kernel configuration have all relevant configurations on by default. If you want to modify your own system, please leave these configutations on. 
```
CONFIG_BPF=y
CONFIG_BPF_SYSCALL=y
CONFIG_BPF_JIT=y
CONFIG_HAVE_BPF_JIT=y
CONFIG_HAVE_EBPF_JIT=y
CONFIG_BPF_EVENTS=y
CONFIG_IKHEADERS=y
```
For more information on eBPF kernel configurations, please visit [here](https://github.com/iovisor/bcc/blob/82f9d1cb633aa3b4ebcbbc5d8b809f48d3dfa222/docs/kernel_config.md).

### Getting eBPF toolchain
Install eBPF toolchain bcc
```bash
sudo apt-get install bpfcc-tools linux-headers-$(uname -r)
```
If you use costom built kernel, follow the [instruction](https://www.kernel.org/doc/Documentation/kbuild/headers_install.txt) to install kernel header. 

### Booting Linux
To run primitive experiments, it is best to isolate cores thus normal system processes won't affect the experiment. To do that, add ```isolcpus=``` in your boot config, assuming an eight physical core system, both SMT core need to be isolated
```
GRUB_CMDLINE_LINUX_DEFAULT="quiet splash isolcpus=4,5,12,13"
```

## Primitive Evaluation
This evaluation corresponds to Section 4.3 on the paper. See [here](https://github.com/FPSG-UIUC/Controlled-Preemption/tree/main/primitives) for more details.

## Proof-of-Concept Attacks
The proof-of-concept attacks corresponds to Section 5 on the paper. See [here](https://github.com/FPSG-UIUC/Controlled-Preemption/tree/main/poc) for more details.

## Citation
If you think our work is helpful and relevant for your research, please kindly cite our paper:
```bib
@inproceedings{zhu2025controlledpreemption,
    title={Controlled Preemption: Amplifying Side-Channel Attacks from Userspace},
    author={Zhu, Yongye and Chen, Boru and Zhao, Zirui Neil and Fletcher, Christopher W.},
    booktitle={ASPLOS},
    year={2025}
}
```

