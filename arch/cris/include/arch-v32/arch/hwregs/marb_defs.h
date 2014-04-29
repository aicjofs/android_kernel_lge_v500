#ifndef __marb_defs_h
#define __marb_defs_h

/*
                                  
                                                              
                                
                                             
  
                                                                                                             
                                                                    
                                 
  
                              
 */
/*                    */
#ifndef REG_RD
#define REG_RD( scope, inst, reg ) \
  REG_READ( reg_##scope##_##reg, \
            (inst) + REG_RD_ADDR_##scope##_##reg )
#endif

#ifndef REG_WR
#define REG_WR( scope, inst, reg, val ) \
  REG_WRITE( reg_##scope##_##reg, \
             (inst) + REG_WR_ADDR_##scope##_##reg, (val) )
#endif

#ifndef REG_RD_VECT
#define REG_RD_VECT( scope, inst, reg, index ) \
  REG_READ( reg_##scope##_##reg, \
            (inst) + REG_RD_ADDR_##scope##_##reg + \
	    (index) * STRIDE_##scope##_##reg )
#endif

#ifndef REG_WR_VECT
#define REG_WR_VECT( scope, inst, reg, index, val ) \
  REG_WRITE( reg_##scope##_##reg, \
             (inst) + REG_WR_ADDR_##scope##_##reg + \
	     (index) * STRIDE_##scope##_##reg, (val) )
#endif

#ifndef REG_RD_INT
#define REG_RD_INT( scope, inst, reg ) \
  REG_READ( int, (inst) + REG_RD_ADDR_##scope##_##reg )
#endif

#ifndef REG_WR_INT
#define REG_WR_INT( scope, inst, reg, val ) \
  REG_WRITE( int, (inst) + REG_WR_ADDR_##scope##_##reg, (val) )
#endif

#ifndef REG_RD_INT_VECT
#define REG_RD_INT_VECT( scope, inst, reg, index ) \
  REG_READ( int, (inst) + REG_RD_ADDR_##scope##_##reg + \
	    (index) * STRIDE_##scope##_##reg )
#endif

#ifndef REG_WR_INT_VECT
#define REG_WR_INT_VECT( scope, inst, reg, index, val ) \
  REG_WRITE( int, (inst) + REG_WR_ADDR_##scope##_##reg + \
	     (index) * STRIDE_##scope##_##reg, (val) )
#endif

#ifndef REG_TYPE_CONV
#define REG_TYPE_CONV( type, orgtype, val ) \
  ( { union { orgtype o; type n; } r; r.o = val; r.n; } )
#endif

#ifndef reg_page_size
#define reg_page_size 8192
#endif

#ifndef REG_ADDR
#define REG_ADDR( scope, inst, reg ) \
  ( (inst) + REG_RD_ADDR_##scope##_##reg )
#endif

#ifndef REG_ADDR_VECT
#define REG_ADDR_VECT( scope, inst, reg, index ) \
  ( (inst) + REG_RD_ADDR_##scope##_##reg + \
    (index) * STRIDE_##scope##_##reg )
#endif

/*                                */

#define STRIDE_marb_rw_int_slots 4
/*                                            */
typedef struct {
  unsigned int owner : 4;
  unsigned int dummy1 : 28;
} reg_marb_rw_int_slots;
#define REG_RD_ADDR_marb_rw_int_slots 0
#define REG_WR_ADDR_marb_rw_int_slots 0

#define STRIDE_marb_rw_ext_slots 4
/*                                            */
typedef struct {
  unsigned int owner : 4;
  unsigned int dummy1 : 28;
} reg_marb_rw_ext_slots;
#define REG_RD_ADDR_marb_rw_ext_slots 256
#define REG_WR_ADDR_marb_rw_ext_slots 256

#define STRIDE_marb_rw_regs_slots 4
/*                                             */
typedef struct {
  unsigned int owner : 4;
  unsigned int dummy1 : 28;
} reg_marb_rw_regs_slots;
#define REG_RD_ADDR_marb_rw_regs_slots 512
#define REG_WR_ADDR_marb_rw_regs_slots 512

/*                                            */
typedef struct {
  unsigned int bp0 : 1;
  unsigned int bp1 : 1;
  unsigned int bp2 : 1;
  unsigned int bp3 : 1;
  unsigned int dummy1 : 28;
} reg_marb_rw_intr_mask;
#define REG_RD_ADDR_marb_rw_intr_mask 528
#define REG_WR_ADDR_marb_rw_intr_mask 528

/*                                           */
typedef struct {
  unsigned int bp0 : 1;
  unsigned int bp1 : 1;
  unsigned int bp2 : 1;
  unsigned int bp3 : 1;
  unsigned int dummy1 : 28;
} reg_marb_rw_ack_intr;
#define REG_RD_ADDR_marb_rw_ack_intr 532
#define REG_WR_ADDR_marb_rw_ack_intr 532

/*                                     */
typedef struct {
  unsigned int bp0 : 1;
  unsigned int bp1 : 1;
  unsigned int bp2 : 1;
  unsigned int bp3 : 1;
  unsigned int dummy1 : 28;
} reg_marb_r_intr;
#define REG_RD_ADDR_marb_r_intr 536

/*                                            */
typedef struct {
  unsigned int bp0 : 1;
  unsigned int bp1 : 1;
  unsigned int bp2 : 1;
  unsigned int bp3 : 1;
  unsigned int dummy1 : 28;
} reg_marb_r_masked_intr;
#define REG_RD_ADDR_marb_r_masked_intr 540

/*                                            */
typedef struct {
  unsigned int dma0  : 1;
  unsigned int dma1  : 1;
  unsigned int dma2  : 1;
  unsigned int dma3  : 1;
  unsigned int dma4  : 1;
  unsigned int dma5  : 1;
  unsigned int dma6  : 1;
  unsigned int dma7  : 1;
  unsigned int dma8  : 1;
  unsigned int dma9  : 1;
  unsigned int cpui  : 1;
  unsigned int cpud  : 1;
  unsigned int iop   : 1;
  unsigned int slave : 1;
  unsigned int dummy1 : 18;
} reg_marb_rw_stop_mask;
#define REG_RD_ADDR_marb_rw_stop_mask 544
#define REG_WR_ADDR_marb_rw_stop_mask 544

/*                                        */
typedef struct {
  unsigned int dma0  : 1;
  unsigned int dma1  : 1;
  unsigned int dma2  : 1;
  unsigned int dma3  : 1;
  unsigned int dma4  : 1;
  unsigned int dma5  : 1;
  unsigned int dma6  : 1;
  unsigned int dma7  : 1;
  unsigned int dma8  : 1;
  unsigned int dma9  : 1;
  unsigned int cpui  : 1;
  unsigned int cpud  : 1;
  unsigned int iop   : 1;
  unsigned int slave : 1;
  unsigned int dummy1 : 18;
} reg_marb_r_stopped;
#define REG_RD_ADDR_marb_r_stopped 548

/*                                           */
typedef struct {
  unsigned int dma0  : 1;
  unsigned int dma1  : 1;
  unsigned int dma2  : 1;
  unsigned int dma3  : 1;
  unsigned int dma4  : 1;
  unsigned int dma5  : 1;
  unsigned int dma6  : 1;
  unsigned int dma7  : 1;
  unsigned int dma8  : 1;
  unsigned int dma9  : 1;
  unsigned int cpui  : 1;
  unsigned int cpud  : 1;
  unsigned int iop   : 1;
  unsigned int slave : 1;
  unsigned int dummy1 : 18;
} reg_marb_rw_no_snoop;
#define REG_RD_ADDR_marb_rw_no_snoop 832
#define REG_WR_ADDR_marb_rw_no_snoop 832

/*                                              */
typedef struct {
  unsigned int dummy1 : 10;
  unsigned int cpui : 1;
  unsigned int cpud : 1;
  unsigned int dummy2 : 20;
} reg_marb_rw_no_snoop_rq;
#define REG_RD_ADDR_marb_rw_no_snoop_rq 836
#define REG_WR_ADDR_marb_rw_no_snoop_rq 836


/*           */
enum {
  regk_marb_cpud                           = 0x0000000b,
  regk_marb_cpui                           = 0x0000000a,
  regk_marb_dma0                           = 0x00000000,
  regk_marb_dma1                           = 0x00000001,
  regk_marb_dma2                           = 0x00000002,
  regk_marb_dma3                           = 0x00000003,
  regk_marb_dma4                           = 0x00000004,
  regk_marb_dma5                           = 0x00000005,
  regk_marb_dma6                           = 0x00000006,
  regk_marb_dma7                           = 0x00000007,
  regk_marb_dma8                           = 0x00000008,
  regk_marb_dma9                           = 0x00000009,
  regk_marb_iop                            = 0x0000000c,
  regk_marb_no                             = 0x00000000,
  regk_marb_r_stopped_default              = 0x00000000,
  regk_marb_rw_ext_slots_default           = 0x00000000,
  regk_marb_rw_ext_slots_size              = 0x00000040,
  regk_marb_rw_int_slots_default           = 0x00000000,
  regk_marb_rw_int_slots_size              = 0x00000040,
  regk_marb_rw_intr_mask_default           = 0x00000000,
  regk_marb_rw_no_snoop_default            = 0x00000000,
  regk_marb_rw_no_snoop_rq_default         = 0x00000000,
  regk_marb_rw_regs_slots_default          = 0x00000000,
  regk_marb_rw_regs_slots_size             = 0x00000004,
  regk_marb_rw_stop_mask_default           = 0x00000000,
  regk_marb_slave                          = 0x0000000d,
  regk_marb_yes                            = 0x00000001
};
#endif /*               */
#ifndef __marb_bp_defs_h
#define __marb_bp_defs_h

/*
                                  
                                                              
                                
                                             
  
                                                                                                             
                                                                    
                                 
  
                              
 */
/*                    */
#ifndef REG_RD
#define REG_RD( scope, inst, reg ) \
  REG_READ( reg_##scope##_##reg, \
            (inst) + REG_RD_ADDR_##scope##_##reg )
#endif

#ifndef REG_WR
#define REG_WR( scope, inst, reg, val ) \
  REG_WRITE( reg_##scope##_##reg, \
             (inst) + REG_WR_ADDR_##scope##_##reg, (val) )
#endif

#ifndef REG_RD_VECT
#define REG_RD_VECT( scope, inst, reg, index ) \
  REG_READ( reg_##scope##_##reg, \
            (inst) + REG_RD_ADDR_##scope##_##reg + \
	    (index) * STRIDE_##scope##_##reg )
#endif

#ifndef REG_WR_VECT
#define REG_WR_VECT( scope, inst, reg, index, val ) \
  REG_WRITE( reg_##scope##_##reg, \
             (inst) + REG_WR_ADDR_##scope##_##reg + \
	     (index) * STRIDE_##scope##_##reg, (val) )
#endif

#ifndef REG_RD_INT
#define REG_RD_INT( scope, inst, reg ) \
  REG_READ( int, (inst) + REG_RD_ADDR_##scope##_##reg )
#endif

#ifndef REG_WR_INT
#define REG_WR_INT( scope, inst, reg, val ) \
  REG_WRITE( int, (inst) + REG_WR_ADDR_##scope##_##reg, (val) )
#endif

#ifndef REG_RD_INT_VECT
#define REG_RD_INT_VECT( scope, inst, reg, index ) \
  REG_READ( int, (inst) + REG_RD_ADDR_##scope##_##reg + \
	    (index) * STRIDE_##scope##_##reg )
#endif

#ifndef REG_WR_INT_VECT
#define REG_WR_INT_VECT( scope, inst, reg, index, val ) \
  REG_WRITE( int, (inst) + REG_WR_ADDR_##scope##_##reg + \
	     (index) * STRIDE_##scope##_##reg, (val) )
#endif

#ifndef REG_TYPE_CONV
#define REG_TYPE_CONV( type, orgtype, val ) \
  ( { union { orgtype o; type n; } r; r.o = val; r.n; } )
#endif

#ifndef reg_page_size
#define reg_page_size 8192
#endif

#ifndef REG_ADDR
#define REG_ADDR( scope, inst, reg ) \
  ( (inst) + REG_RD_ADDR_##scope##_##reg )
#endif

#ifndef REG_ADDR_VECT
#define REG_ADDR_VECT( scope, inst, reg, index ) \
  ( (inst) + REG_RD_ADDR_##scope##_##reg + \
    (index) * STRIDE_##scope##_##reg )
#endif

/*                                   */

/*                                                */
typedef unsigned int reg_marb_bp_rw_first_addr;
#define REG_RD_ADDR_marb_bp_rw_first_addr 0
#define REG_WR_ADDR_marb_bp_rw_first_addr 0

/*                                               */
typedef unsigned int reg_marb_bp_rw_last_addr;
#define REG_RD_ADDR_marb_bp_rw_last_addr 4
#define REG_WR_ADDR_marb_bp_rw_last_addr 4

/*                                        */
typedef struct {
  unsigned int rd         : 1;
  unsigned int wr         : 1;
  unsigned int rd_excl    : 1;
  unsigned int pri_wr     : 1;
  unsigned int us_rd      : 1;
  unsigned int us_wr      : 1;
  unsigned int us_rd_excl : 1;
  unsigned int us_pri_wr  : 1;
  unsigned int dummy1     : 24;
} reg_marb_bp_rw_op;
#define REG_RD_ADDR_marb_bp_rw_op 8
#define REG_WR_ADDR_marb_bp_rw_op 8

/*                                             */
typedef struct {
  unsigned int dma0  : 1;
  unsigned int dma1  : 1;
  unsigned int dma2  : 1;
  unsigned int dma3  : 1;
  unsigned int dma4  : 1;
  unsigned int dma5  : 1;
  unsigned int dma6  : 1;
  unsigned int dma7  : 1;
  unsigned int dma8  : 1;
  unsigned int dma9  : 1;
  unsigned int cpui  : 1;
  unsigned int cpud  : 1;
  unsigned int iop   : 1;
  unsigned int slave : 1;
  unsigned int dummy1 : 18;
} reg_marb_bp_rw_clients;
#define REG_RD_ADDR_marb_bp_rw_clients 12
#define REG_WR_ADDR_marb_bp_rw_clients 12

/*                                             */
typedef struct {
  unsigned int wrap : 1;
  unsigned int dummy1 : 31;
} reg_marb_bp_rw_options;
#define REG_RD_ADDR_marb_bp_rw_options 16
#define REG_WR_ADDR_marb_bp_rw_options 16

/*                                            */
typedef unsigned int reg_marb_bp_r_brk_addr;
#define REG_RD_ADDR_marb_bp_r_brk_addr 20

/*                                          */
typedef struct {
  unsigned int rd         : 1;
  unsigned int wr         : 1;
  unsigned int rd_excl    : 1;
  unsigned int pri_wr     : 1;
  unsigned int us_rd      : 1;
  unsigned int us_wr      : 1;
  unsigned int us_rd_excl : 1;
  unsigned int us_pri_wr  : 1;
  unsigned int dummy1     : 24;
} reg_marb_bp_r_brk_op;
#define REG_RD_ADDR_marb_bp_r_brk_op 24

/*                                               */
typedef struct {
  unsigned int dma0  : 1;
  unsigned int dma1  : 1;
  unsigned int dma2  : 1;
  unsigned int dma3  : 1;
  unsigned int dma4  : 1;
  unsigned int dma5  : 1;
  unsigned int dma6  : 1;
  unsigned int dma7  : 1;
  unsigned int dma8  : 1;
  unsigned int dma9  : 1;
  unsigned int cpui  : 1;
  unsigned int cpud  : 1;
  unsigned int iop   : 1;
  unsigned int slave : 1;
  unsigned int dummy1 : 18;
} reg_marb_bp_r_brk_clients;
#define REG_RD_ADDR_marb_bp_r_brk_clients 28

/*                                                    */
typedef struct {
  unsigned int dma0  : 1;
  unsigned int dma1  : 1;
  unsigned int dma2  : 1;
  unsigned int dma3  : 1;
  unsigned int dma4  : 1;
  unsigned int dma5  : 1;
  unsigned int dma6  : 1;
  unsigned int dma7  : 1;
  unsigned int dma8  : 1;
  unsigned int dma9  : 1;
  unsigned int cpui  : 1;
  unsigned int cpud  : 1;
  unsigned int iop   : 1;
  unsigned int slave : 1;
  unsigned int dummy1 : 18;
} reg_marb_bp_r_brk_first_client;
#define REG_RD_ADDR_marb_bp_r_brk_first_client 32

/*                                            */
typedef unsigned int reg_marb_bp_r_brk_size;
#define REG_RD_ADDR_marb_bp_r_brk_size 36

/*                                         */
typedef unsigned int reg_marb_bp_rw_ack;
#define REG_RD_ADDR_marb_bp_rw_ack 40
#define REG_WR_ADDR_marb_bp_rw_ack 40


/*           */
enum {
  regk_marb_bp_no                          = 0x00000000,
  regk_marb_bp_rw_op_default               = 0x00000000,
  regk_marb_bp_rw_options_default          = 0x00000000,
  regk_marb_bp_yes                         = 0x00000001
};
#endif /*                  */
