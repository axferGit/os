#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "kernel/memlayout.h"
#include "kernel/types.h"


#define min(a,b) (((a) < (b)) ? (a) : (b))

uint32 ninode = 0;
int fdfs;

uint8 idx(uint8 tab){
    for (int i = 0 ; i < (8*sizeof(uint8)); i++){
        if(((tab >> i) & 0x01) == 0x00){
            return i;
        }
    }
    printf("Can not find free bit\n");
    exit(1);
}

// Write [buf] to block nb [blk]
void wblock(uint64 blk, void* buf){
    if(!((0 <= blk) && (blk < NBLOCK))){
        printf("blk out of range: %li\n",blk);
        exit(1);
    }
    if (lseek(fdfs, blk * BLOCK_SIZE,SEEK_SET) == -1){
        printf("lseek failed\n");
        exit(1);
    }
    if (write(fdfs,buf,BLOCK_SIZE) == -1){
        printf("write failed\n");
        exit(1);
    }
    return;
}

// Read block nb [blk] to [buf] 
void rblock(uint64 blk, void* buf){
    if(!((0 <= blk) && (blk < NBLOCK))){
        printf("blk out of range: %li\n",blk);
        exit(1);
    }
    if(!blk){
        printf("blk is 0\n");
        exit(1);
    }
    if (lseek(fdfs, blk * BLOCK_SIZE,SEEK_SET) == -1){
        printf("lseek failed\n");
        exit(1);
    }
    if (read(fdfs,buf,BLOCK_SIZE) == -1){
        printf("write failed\n");
        exit(1);
    }
    return;
}

// Return a new data block number
uint64 dalloc(){
    uint8 bitmap [BLOCK_SIZE];
    uint64 i;
    rblock(SBITMAP,bitmap);
    for (i = 0; i < NDATA; i++){
        if(bitmap[i] != 0xff){
            uint8 id = idx(bitmap[i]);
            bitmap[i] |= (1 << id);
            wblock(SBITMAP,bitmap);
            return (SDATA + id + i*(8*sizeof(uint8)));
        }
    }
    if (i == NDATA){
        printf("No more data block available\n");
        exit(1);
    }
}

// Set all blocks to 0
void fsinit(){
    uint8 buf[BLOCK_SIZE];
    memset(buf,0,sizeof(buf));
    for (int i = 0; i < NBLOCK; i++){
        wblock(i,buf);
    };
    return;
}

// Write superblock
void wsb(struct superblock* sb){
    uint8 buf[BLOCK_SIZE];
    memset(buf,0,sizeof(buf));
    memcpy(buf,sb,sizeof(sb));
    wblock(SSB,buf);
    return;
}

// Write inode [inum] pointed by [di]
void winode(uint16 inum, struct dinode* di){
    uint8 buf[BLOCK_SIZE];
    uint64 blk = IBLOCK(inum);
    uint32 offset = IBLOCKOFF(inum);
    
    if (! ((SINODE <= blk) && (blk < (SINODE + NINODE)))){
        printf("inode out of range : %li\n",blk);
        exit(1);
    }

    rblock(blk,buf);
    memcpy(((struct dinode*)buf) + offset,di,sizeof(*di));
    wblock(blk,buf);

    return;
}

// Read inode [inum] to [di]
void rinode(uint16 inum, struct dinode* di){
    uint8 buf[BLOCK_SIZE];
    uint64 blk = IBLOCK(inum);
    uint32 offset = IBLOCKOFF(inum);

    if (! ((SINODE <= blk) && (blk < (SINODE + NINODE)))){
        printf("inode out of range : %li\n",blk);
        exit(1);
    }

    rblock(blk,buf);
    memcpy(di,(struct dinode*)buf + offset,sizeof(*di));

    return;
}

// Write a new inode of typr [type] into disk
// Return its inum
uint16 ialloc(uint16 type){
    if(ninode > (MAXINODE)){
        printf("No more inode available\n");
        exit(1);
    }

    struct dinode di;
    di.type = type;
    di.size = 0;
    for (int i = 0; i < NADDR; i++){
        di.data[i] = 0;
    }
    winode(ninode,&di);
    return ninode++;
}

// Append to inode [inum] [sz] bytes from [data]
void ainode(uint16 inum, void* data, int sz){
    uint32 wsz = 0;

    while (sz) {
        struct dinode di;
        uint8 buf [BLOCK_SIZE];
        uint32 fbn;
        uint32 off;
        inodeent* barray;
        

        rinode(inum, &di);
        fbn = di.size / (BLOCK_SIZE);
        off = di.size % (BLOCK_SIZE);

        if (fbn < NADDR){
            barray = di.data;
            if (off == 0){
                barray[fbn] = dalloc();
            }
        }
        else {

            uint8 indirect [BLOCK_SIZE];

            if (di.data[NADDR] == 0){
                di.data[NADDR] = dalloc();
            }
            rblock(di.data[NADDR],indirect);
            barray = (inodeent*) indirect;
            fbn -= NADDR;

            if (fbn > NINDADDR){
                printf("Exeed NINDADDR\n");
                exit(1);
            };

            if (off == 0){
                barray[fbn] = dalloc();
                wblock(di.data[NADDR],indirect);
            };
        };
        
        // number of bytes to be read from data and written to buffer
        uint32 nb = min(sz,BLOCK_SIZE - off);

        rblock(barray[fbn],buf);
        memcpy(buf + off,((uint8*) data) + wsz, nb);
        wblock(barray[fbn],buf);
        
        sz -= nb;
        wsz += nb;
        di.size += nb;

        winode(inum,&di);

    };
    
    return;
}

// Append a directoty entry [inum,name] into inode [inum_parent] 
void adirent(uint16 inum_parent, char* name, uint16 inum){
    struct dirent de;
    de.inum = inum;
    strncpy(de.name,name,NCHAR-1);
    de.name[NCHAR]= '\0';
    ainode(inum_parent,&de,sizeof(de));
    return;
}

int main(int argc, char *argv[]){
    uint8 buf[BLOCK_SIZE];
    struct superblock sb;
    struct dinode rinode;

    if ((fdfs = open("fs.img",O_RDWR | O_CREAT | O_TRUNC)) == -1){
        printf("fs can not be oponed\n");
        exit(1);
    };

    fsinit();
    

    // Block 0: do nothing

    // Block 1 : write sb

    sb.magic = FS_MAGIC;
    sb.nblock = NBLOCK;
    sb.slog = SLOG;
    sb.nlog = NLOG;
    sb.sinode = SINODE;
    sb.ninode = NINODE;
    sb.sdata = SDATA;
    sb.ndata = NDATA;
    wsb(&sb);

    // Block SINODE +-> NINODE : inodes
    // Inode 0 : "/"

    ialloc(T_DIR);

    // Inodes ... : Files
    for (int i = 1; i < argc; i++){
        int fd;
        uint32 sz;
        uint16 inum = ialloc(T_FILE);
        
        adirent(0,argv[i],inum);

        if ((fd = open(argv[i],O_RDONLY)) == -1){
            printf("%s can not be oponed\n",argv[i]);
            exit(1);
        }
        
        while((sz = read(fd,buf,BLOCK_SIZE))){
            ainode(inum,buf,sz);
        }

        if(close(fd) == -1){
            printf("Failed to clode fd: %s\n",argv[i]);
            exit(1);
        }
    }

    return 0;
}