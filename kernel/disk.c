#include "types.h"
#include "memlayout.h"
#include "printf.h"
#include "alloc.h"
#include "vm.h"

#define WRITE_32(addr,v) (*((volatile uint32*) (addr)) = v)
#define READ_32(addr) (*((volatile uint32*) (addr)))
#define VIRTIO_MMIO_DISK_IDX (0)


__attribute__ ((aligned (PAGESIZE))) struct disk disk[NDISK]; // virtques need to be Qalign aligned
struct virtio_blk_req blk_request_list[NRQST];


// Init free list
void freeinit(){
    for (uint32 i = 0; i < QUEUE_SIZE; i++){
        disk[0].free[i] = 1;
    }
    return;
}

void freedesc(uint16 i){
    disk[0].free[i] = 1;
    return;
}

// free [idx]
void free3desc(uint16* idx){
    for (uint8 i = 0 ; i < 3 ; i++){
        freedesc(i);
    }
    return;
}

void diskinit(){

    freeinit();

    uint32 status = 0;
    uint32 features;

    // Check it is a disk device
    if (READ_32(VIRTIO_MMIO_DISK_MAGIC_NUMBER(VIRTIO_MMIO_DISK_IDX)) != VIRTIO_MMIO_DISK_MN ||
        READ_32(VIRTIO_MMIO_DISK_VERSION(VIRTIO_MMIO_DISK_IDX)) != VIRTIO_MMIO_DISK_V ||
        READ_32(VIRTIO_MMIO_DISK_DEVICE_ID(VIRTIO_MMIO_DISK_IDX)) != VIRTIO_MMIO_DISK_DID) {
            printf("Bad device\n");
            printf("VIRIO MN: %p\n", READ_32(VIRTIO_MMIO_DISK_MAGIC_NUMBER(VIRTIO_MMIO_DISK_IDX)));
            printf("VIRIO V: %p\n", READ_32(VIRTIO_MMIO_DISK_VERSION(VIRTIO_MMIO_DISK_IDX)));
            printf("VIRIO DID: %p\n", READ_32(VIRTIO_MMIO_DISK_DEVICE_ID(VIRTIO_MMIO_DISK_IDX)));
            panic("");
        }
    
    // Acknowledge
    status = (1 << ACKNOWLEDGE);
    WRITE_32(VIRTIO_MMIO_DISK_DEVICE_STATUS(VIRTIO_MMIO_DISK_IDX),status);

    // Driver
    status |= (1 << DRIVER);
    WRITE_32(VIRTIO_MMIO_DISK_DEVICE_STATUS(VIRTIO_MMIO_DISK_IDX),status);

    // Feature
    features = READ_32(VIRTIO_MMIO_DISK_GUEST_FEATURES(VIRTIO_MMIO_DISK_IDX));
    features &= ~(1 << VIRTIO_BLK_F_RO);
    features &= ~(1 << VIRTIO_BLK_F_SCSI);
    features &= ~(1 << VIRTIO_BLK_F_CONFIG_WCE);
    features &= ~(1 << VIRTIO_BLK_F_MQ);
    features &= ~(1 << VIRTIO_F_ANY_LAYOUT);
    features &= ~(1 << VIRTIO_RING_F_EVENT_IDX);
    features &= ~(1 << VIRTIO_RING_F_INDIRECT_DESC);
    WRITE_32(VIRTIO_MMIO_DISK_GUEST_FEATURES(VIRTIO_MMIO_DISK_IDX), features);
    WRITE_32(VIRTIO_MMIO_DISK_GUEST_FEATURES_SEL(VIRTIO_MMIO_DISK_IDX), features);
    WRITE_32(VIRTIO_MMIO_DISK_HOST_FEATURES_SEL(VIRTIO_MMIO_DISK_IDX), features);

    status |= (1 < FEATURES_OK);
    WRITE_32(VIRTIO_MMIO_DISK_DEVICE_STATUS(VIRTIO_MMIO_DISK_IDX),status);

    // panic if features are not supported by the device
    if( READ_32(VIRTIO_MMIO_DISK_DEVICE_STATUS(VIRTIO_MMIO_DISK_IDX)) != status){
        printf("Status : %i\n", READ_32(VIRTIO_MMIO_DISK_DEVICE_STATUS(VIRTIO_MMIO_DISK_IDX)));
        panic("Bad status\n");
    }

    // Queue
    // n°0
    WRITE_32(VIRTIO_MMIO_DISK_QUEUE_SEL(VIRTIO_MMIO_DISK_IDX),0);
    if (*((volatile uint64*) (VIRTIO_MMIO_DISK_QUEUE_PFN(VIRTIO_MMIO_DISK_IDX))) != 0UL){
        panic("Queue in use\n");
    }

    uint32 max = READ_32(VIRTIO_MMIO_DISK_QUEUE_NUM_MAX(VIRTIO_MMIO_DISK_IDX));
    if (max == 0){
        panic("Queue size is not available (0)\n");
    }
    if (max < QUEUE_SIZE){
        panic("Queue size is too big\n");
    }
    WRITE_32(VIRTIO_MMIO_DISK_QUEUE_NUM(VIRTIO_MMIO_DISK_IDX),QUEUE_SIZE);

    disk[0].DescriptorArea = (struct virtq_desc*) &(disk[0].data[0]);
    disk[0].DriverArea = (struct virtq_avail*) &(disk[0].data[QUEUE_SIZE*(sizeof(struct virtq_desc))]);
    disk[0].DeviceArea = (struct virtq_used*) &(disk[0].data[PAGESIZE]);
    
    memset(disk[0].DescriptorArea,0,2*PAGESIZE);

    
    // printf("Desc :%p\n",disk[0].DescriptorArea);
    // printf("Desc :%p\n",disk[0].DriverArea);
    // printf("Desc :%p\n",disk[0].DeviceArea);

    WRITE_32(VIRTIO_MMIO_DISK_GUEST_PAGE_SIZE(VIRTIO_MMIO_DISK_IDX),PAGESIZE);

    WRITE_32(VIRTIO_MMIO_DISK_QUEUE_ALIGN(VIRTIO_MMIO_DISK_IDX),QALIGN);

    *((volatile uint64*) (VIRTIO_MMIO_DISK_QUEUE_PFN(VIRTIO_MMIO_DISK_IDX))) = ADR2PAGE(disk[0].DescriptorArea);
    
    //printf("QPFN: %p\n",*((uint64*) (VIRTIO_MMIO_DISK_QUEUE_PFN(VIRTIO_MMIO_DISK_IDX))));
    
    // Driver OK
    status |= DRIVER_OK;
    WRITE_32(VIRTIO_MMIO_DISK_DEVICE_STATUS(VIRTIO_MMIO_DISK_IDX), status);

    return;
}

// Allocate one descriptor and mark it as busy in disk[].free
// return the idx on sucess
// return 61 on failure
uint32 allocdesc(){
    for(uint16 i = 0; i < QUEUE_SIZE; i++){
        if (disk[0].free[i]){
            disk[0].free[i] = 0;
            return i;
        }
    }
    return -1;
}

// Alloc 3 descriptors into [idx]
// return 0 on success
// return -1 on failure
uint32 alloc3desc(uint16* idx){
    for (uint8 i = 0; i < 3; i++){
        if ((idx[i] = allocdesc()) == -1){
            for (uint8 j = 0; j < i; j++){
                freedesc(idx[j]);
            }
            return -1;
        };
    }
    return 0; 
}

struct virtio_blk_req* getrequest(){
    return &blk_request_list[0];
}

// Create request
void makerequest(struct virtio_blk_req* blk_request, uint32 t_rqt, uint64 blk){
    blk_request -> type = t_rqt;
    blk_request -> reserved = 0;
    blk_request -> sector = BLOCK2SEC(blk);

}
// Perfom [t_rqt] request on buffer [b]
void diskrequest(uint32 t_rqt,struct buf * b){
    uint16 idx[3];
    struct virtio_blk_req* blk_request = getrequest();

    while(alloc3desc(idx) == -1){
        ;
    }
    
    makerequest(blk_request,t_rqt,b->blk);


    disk[0].DescriptorArea[idx[0]].addr =(uint64) blk_request;
    disk[0].DescriptorArea[idx[0]].len = sizeof(*blk_request);
    disk[0].DescriptorArea[idx[0]].flags = VIRTQ_DESC_F_NEXT;
    disk[0].DescriptorArea[idx[0]].next = idx[1];

    
    disk[0].DescriptorArea[idx[1]].addr = (uint64) b->data;
    disk[0].DescriptorArea[idx[1]].len = sizeof(b->data);
    disk[0].DescriptorArea[idx[1]].flags = VIRTQ_DESC_F_NEXT | ((t_rqt == VIRTIO_BLK_T_IN) ? VIRTQ_DESC_F_WRITE : VIRTQ_DESC_F_READ);
    disk[0].DescriptorArea[idx[1]].next = idx[2];

    b -> status = VIRTIO_BLK_S_UNDEF;
    disk[0].DescriptorArea[idx[2]].addr = (uint64) &b->status;
    disk[0].DescriptorArea[idx[2]].len = sizeof(b->status);
    disk[0].DescriptorArea[idx[2]].flags = VIRTQ_DESC_F_WRITE;
    disk[0].DescriptorArea[idx[2]].next = 0;

    disk[0].DriverArea ->ring[disk[0].DriverArea -> idx] = idx[0];
    disk[0].DriverArea -> idx += 1; // no need modulo
    

    __sync_synchronize();
    WRITE_32(VIRTIO_MMIO_DISK_QUEUE_NOTIFY(VIRTIO_MMIO_DISK_IDX),0);
    

    while(b -> status == VIRTIO_BLK_S_UNDEF){
        if((b -> status ==  VIRTIO_BLK_S_IOERR) || (b -> status ==  VIRTIO_BLK_S_UNSUPP)){
            printf("Request has failed : status = %i\n",b->status);
            panic("");
        }
        printf("Status after request: %i\n",b->status);
    };

    free3desc(idx);

    return;   


}