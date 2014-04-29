#ifndef __strmux_defs_asm_h
#define __strmux_defs_asm_h

/*
                                  
                                                                 
                                                                      
                                             
  
                                                                                                                               
                                                                          
                                 
  
                              
 */

#ifndef REG_FIELD
#define REG_FIELD( scope, reg, field, value ) \
  REG_FIELD_X_( value, reg_##scope##_##reg##___##field##___lsb )
#define REG_FIELD_X_( value, shift ) ((value) << shift)
#endif

#ifndef REG_STATE
#define REG_STATE( scope, reg, field, symbolic_value ) \
  REG_STATE_X_( regk_##scope##_##symbolic_value, reg_##scope##_##reg##___##field##___lsb )
#define REG_STATE_X_( k, shift ) (k << shift)
#endif

#ifndef REG_MASK
#define REG_MASK( scope, reg, field ) \
  REG_MASK_X_( reg_##scope##_##reg##___##field##___width, reg_##scope##_##reg##___##field##___lsb )
#define REG_MASK_X_( width, lsb ) (((1 << width)-1) << lsb)
#endif

#ifndef REG_LSB
#define REG_LSB( scope, reg, field ) reg_##scope##_##reg##___##field##___lsb
#endif

#ifndef REG_BIT
#define REG_BIT( scope, reg, field ) reg_##scope##_##reg##___##field##___bit
#endif

#ifndef REG_ADDR
#define REG_ADDR( scope, inst, reg ) REG_ADDR_X_(inst, reg_##scope##_##reg##_offset)
#define REG_ADDR_X_( inst, offs ) ((inst) + offs)
#endif

#ifndef REG_ADDR_VECT
#define REG_ADDR_VECT( scope, inst, reg, index ) \
         REG_ADDR_VECT_X_(inst, reg_##scope##_##reg##_offset, index, \
			 STRIDE_##scope##_##reg )
#define REG_ADDR_VECT_X_( inst, offs, index, stride ) \
                          ((inst) + offs + (index) * stride)
#endif

/*                                        */
#define reg_strmux_rw_cfg___dma0___lsb 0
#define reg_strmux_rw_cfg___dma0___width 3
#define reg_strmux_rw_cfg___dma1___lsb 3
#define reg_strmux_rw_cfg___dma1___width 3
#define reg_strmux_rw_cfg___dma2___lsb 6
#define reg_strmux_rw_cfg___dma2___width 3
#define reg_strmux_rw_cfg___dma3___lsb 9
#define reg_strmux_rw_cfg___dma3___width 3
#define reg_strmux_rw_cfg___dma4___lsb 12
#define reg_strmux_rw_cfg___dma4___width 3
#define reg_strmux_rw_cfg___dma5___lsb 15
#define reg_strmux_rw_cfg___dma5___width 3
#define reg_strmux_rw_cfg___dma6___lsb 18
#define reg_strmux_rw_cfg___dma6___width 3
#define reg_strmux_rw_cfg___dma7___lsb 21
#define reg_strmux_rw_cfg___dma7___width 3
#define reg_strmux_rw_cfg___dma8___lsb 24
#define reg_strmux_rw_cfg___dma8___width 3
#define reg_strmux_rw_cfg___dma9___lsb 27
#define reg_strmux_rw_cfg___dma9___width 3
#define reg_strmux_rw_cfg_offset 0


/*           */
#define regk_strmux_ata                           0x00000003
#define regk_strmux_eth0                          0x00000001
#define regk_strmux_eth1                          0x00000004
#define regk_strmux_ext0                          0x00000001
#define regk_strmux_ext1                          0x00000001
#define regk_strmux_ext2                          0x00000001
#define regk_strmux_ext3                          0x00000001
#define regk_strmux_iop0                          0x00000002
#define regk_strmux_iop1                          0x00000001
#define regk_strmux_off                           0x00000000
#define regk_strmux_p21                           0x00000004
#define regk_strmux_rw_cfg_default                0x00000000
#define regk_strmux_ser0                          0x00000002
#define regk_strmux_ser1                          0x00000002
#define regk_strmux_ser2                          0x00000004
#define regk_strmux_ser3                          0x00000003
#define regk_strmux_sser0                         0x00000003
#define regk_strmux_sser1                         0x00000003
#define regk_strmux_strcop                        0x00000002
#endif /*                     */
