#include "types.h"
#include "memlayout.h"
#include "printf.h"
#include "alloc.h"

#define WRITE_32(addr,v) (*((volatile uint32*) (addr)) = v)
#define READ_32(addr) (*((volatile uint32*) (addr)))
#define VIRTIO_MMIO_DISK_IDX (0)

__attribute__ ((aligned (PAGESIZE))) struct disk disk[NDISK];

void diskinit(){

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

    WRITE_32(VIRTIO_MMIO_DISK_QUEUE_ALIGN(VIRTIO_MMIO_DISK_IDX),PAGESIZE);

    *((volatile uint64*) (VIRTIO_MMIO_DISK_QUEUE_PFN(VIRTIO_MMIO_DISK_IDX))) = ADR2PAGE(disk[0].DescriptorArea);
    
    //printf("QPFN: %p\n",*((uint64*) (VIRTIO_MMIO_DISK_QUEUE_PFN(VIRTIO_MMIO_DISK_IDX))));
    
    // Driver OK
    status |= DRIVER_OK;
    WRITE_32(VIRTIO_MMIO_DISK_DEVICE_STATUS(VIRTIO_MMIO_DISK_IDX), status);

    return;
}

void diskread(){
    struct virtio_blk_req blk_request;
    blk_request.type = VIRTIO_BLK_T_IN;
    blk_request.reserved = 0;
    blk_request.sector = 0;

    disk[0].DescriptorArea[0].addr =(uint64) &blk_request;
    disk[0].DescriptorArea[0].len = sizeof(blk_request);
    disk[0].DescriptorArea[0].flags = VIRTQ_DESC_F_NEXT;
    disk[0].DescriptorArea[0].next = 1;

    uint8 buffer_data[512];
    memset(buffer_data,0x62,sizeof(buffer_data));

    disk[0].DescriptorArea[1].addr = (uint64) buffer_data;
    disk[0].DescriptorArea[1].len = sizeof(buffer_data);
    disk[0].DescriptorArea[1].flags = VIRTQ_DESC_F_NEXT | VIRTQ_DESC_F_WRITE;
    disk[0].DescriptorArea[1].next = 2;

    uint8 buffer_status[1];
    buffer_status[0] = 3; //TODO: robust

    disk[0].DescriptorArea[2].addr = (uint64) &buffer_status;
    disk[0].DescriptorArea[2].len = 1;
    disk[0].DescriptorArea[2].flags = VIRTQ_DESC_F_WRITE;
    disk[0].DescriptorArea[2].next = 0;

    disk[0].DriverArea ->ring[disk[0].DriverArea -> idx] = 0;
    disk[0].DriverArea -> idx += 1;
    __sync_synchronize();
    WRITE_32(VIRTIO_MMIO_DISK_QUEUE_NOTIFY(VIRTIO_MMIO_DISK_IDX),0);

    while(disk[0].DeviceArea ->idx == 0){
        printf("Status after request: %p\n",buffer_status[0]);
    };

    printf("Virtq_used_elm: id: %i --len: %i\n",disk[0].DeviceArea->ring[0].id, disk[0].DeviceArea->ring[0].len);
    printf("Virtq_used_elm: id: %i --len: %i\n",disk[0].DeviceArea->ring[1].id, disk[0].DeviceArea->ring[1].len);
    printf("Virtq_used_elm: id: %i --len: %i\n",disk[0].DeviceArea->ring[2].id, disk[0].DeviceArea->ring[2].len);

    for (int i = 0; i < sizeof(buffer_data); i++){
        printf("%i",buffer_data[i]);
    };
    printf("\n");

    printf("Interrupt status: %p\n",READ_32(VIRTIO_MMIO_DISK_INTERRUPT_STATUS(VIRTIO_MMIO_DISK_IDX)));
    printf("used idx: %p\n",disk[0].DeviceArea ->idx);
    printf("Status: %p\n",(uint64) buffer_status[0]);
   

    panic("OK!\n");

    return;   


}