/*
 * Copyright (C) 2025 pdnguyen of HCMC University of Technology VNU-HCM
 */

/* Sierra release
 * Source Code License Grant: The authors hereby grant to Licensee
 * personal permission to use and modify the Licensed Source Code
 * for the sole purpose of studying while attending the course CO2018.
 */

#include "common.h"
#include "syscall.h"
#include "stdio.h"
#include "libmem.h"
#include "string.h" //Tu them
#include "queue.h" //Tu them
int __sys_killall(struct pcb_t *caller, struct sc_regs* regs)
{
    char proc_name[100];
    uint32_t data;

    //hardcode for demo only
    uint32_t memrg = regs->a1;
    
    /* TODO: Get name of the target proc */
    //proc_name = libread..
    int i = 0;
    data = 0;
    while(data != -1){
        libread(caller, memrg, i, &data);
        proc_name[i]= data;
        if(data == -1) proc_name[i]='\0';
        i++;
    }
    printf("The procname retrieved from memregionid %d is \"%s\"\n", memrg, proc_name);

    /* TODO: Traverse proclist to terminate the proc
     *       stcmp to check the process match proc_name
     */
    //caller->running_list
    //caller->mlq_ready_queu

    /* TODO Maching and terminating 
     *       all processes with given
     *        name in var proc_name
     */
    #define KILL_FROM_QUEUE(q) \
    { \
         for (int j = 0; j < q->size;) { \
             struct pcb_t *proc = (q)->proc[j]; \
             if (strcmp(proc->path, proc_name) == 0) { \
                 free_pcb_memph(proc); \
                 for (int k = j; k < (q)->size - 1; ++k) { \
                     (q)->proc[k] = (q)->proc[k + 1]; \
                 } \
                 (q)->proc[(q)->size - 1] = NULL; \
                 (q)->size--; \
             } else { \
                 j++; \
             } \
         } \
    } 


    if (caller->ready_queue) KILL_FROM_QUEUE(caller->ready_queue);
    if (caller->running_list) KILL_FROM_QUEUE(caller->running_list);
    if (caller->mlq_ready_queue) KILL_FROM_QUEUE(caller->mlq_ready_queue);
    
    
    return 0; 
}
