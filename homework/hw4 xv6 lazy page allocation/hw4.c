int mappages(pde_t *pgdir, void *va, uint size, uint pa, int perm);

void
trap(struct trapframe *tf)
{
  uint faultingva;
  char *mem;
  
  /* ...... */
  
  if(tf->trapno == T_PGFLT) {
    faultingva = PGROUNDDOWN(rcr2());
    mem = kalloc();
    if(mem == 0){
      cprintf("alloc lazy page, out of memory\n");
      return;
    }
    memset(mem, 0, PGSIZE);
    cprintf("pagefault at %x\n", faultingva);
    if(mappages(myproc()->pgdir, (char*)faultingva, PGSIZE, V2P(mem), PTE_W|PTE_U) < 0){
      cprintf("alloc lazy page, out of memory\n");
      kfree(mem);
    }
    cprintf("alloc lazy page for %x finished\n", faultingva);
    return;
    };


  /* ...... */
}
