typedef struct { char status, int memPage } PageData;

PageData *PageTables[maxProc];

void virtualToPhysical(int pid, int virtualAddr) {
    PageData *thisProcess = PageTables[pid];
    int pageno = virtualAddr/pagesize;
    int offset = virtualAddr%pagesize;
    PageData *p = thisProcess[pageno];
    if (load(p->status)) return p->memPage*pagesize + offset
    else
}
