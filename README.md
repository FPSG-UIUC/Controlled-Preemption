# Controlled Preemption
This repository is the open-source code for our ASPLOS 2025 paper: *Controlled Preemption: Amplifying Side-Channel Attacks from Userspace*

# Contact
Feel free to contact us if you have any questions about the paper!

Yongye Zhu [yongye.zhu@berkeley.edu](mailto:yongye.zhu@berkeley.edu)

# Abstract
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

# Repository Structure
This repository comprises the following artifacts:
```
.
|-- scripts: evaluation scripts on controlled preemption primitives
|-- poc: proof-of-concept attacks
```

# Citation
If you think our work is helpful and relevant for your research, please kindly cite our paper:
```bib
@inproceedings{zhu2025controlledpreemption,
    title={Controlled Preemption: Amplifying Side-Channel Attacks from Userspace},
    author={Zhu, Yongye and Chen, Boru and Zhao, Zirui Neil and Fletcher, Christopher W.},
    booktitle={ASPLOS},
    year={2025}
}
```

