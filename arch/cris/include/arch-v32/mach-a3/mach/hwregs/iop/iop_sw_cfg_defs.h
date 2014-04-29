#ifndef __iop_sw_cfg_defs_h
#define __iop_sw_cfg_defs_h

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

/*                                      */

/*                                                      */
typedef struct {
  unsigned int cfg : 2;
  unsigned int dummy1 : 30;
} reg_iop_sw_cfg_rw_crc_par_owner;
#define REG_RD_ADDR_iop_sw_cfg_rw_crc_par_owner 0
#define REG_WR_ADDR_iop_sw_cfg_rw_crc_par_owner 0

/*                                                     */
typedef struct {
  unsigned int cfg : 2;
  unsigned int dummy1 : 30;
} reg_iop_sw_cfg_rw_dmc_in_owner;
#define REG_RD_ADDR_iop_sw_cfg_rw_dmc_in_owner 4
#define REG_WR_ADDR_iop_sw_cfg_rw_dmc_in_owner 4

/*                                                      */
typedef struct {
  unsigned int cfg : 2;
  unsigned int dummy1 : 30;
} reg_iop_sw_cfg_rw_dmc_out_owner;
#define REG_RD_ADDR_iop_sw_cfg_rw_dmc_out_owner 8
#define REG_WR_ADDR_iop_sw_cfg_rw_dmc_out_owner 8

/*                                                      */
typedef struct {
  unsigned int cfg : 2;
  unsigned int dummy1 : 30;
} reg_iop_sw_cfg_rw_fifo_in_owner;
#define REG_RD_ADDR_iop_sw_cfg_rw_fifo_in_owner 12
#define REG_WR_ADDR_iop_sw_cfg_rw_fifo_in_owner 12

/*                                                            */
typedef struct {
  unsigned int cfg : 2;
  unsigned int dummy1 : 30;
} reg_iop_sw_cfg_rw_fifo_in_extra_owner;
#define REG_RD_ADDR_iop_sw_cfg_rw_fifo_in_extra_owner 16
#define REG_WR_ADDR_iop_sw_cfg_rw_fifo_in_extra_owner 16

/*                                                       */
typedef struct {
  unsigned int cfg : 2;
  unsigned int dummy1 : 30;
} reg_iop_sw_cfg_rw_fifo_out_owner;
#define REG_RD_ADDR_iop_sw_cfg_rw_fifo_out_owner 20
#define REG_WR_ADDR_iop_sw_cfg_rw_fifo_out_owner 20

/*                                                             */
typedef struct {
  unsigned int cfg : 2;
  unsigned int dummy1 : 30;
} reg_iop_sw_cfg_rw_fifo_out_extra_owner;
#define REG_RD_ADDR_iop_sw_cfg_rw_fifo_out_extra_owner 24
#define REG_WR_ADDR_iop_sw_cfg_rw_fifo_out_extra_owner 24

/*                                                     */
typedef struct {
  unsigned int cfg : 2;
  unsigned int dummy1 : 30;
} reg_iop_sw_cfg_rw_sap_in_owner;
#define REG_RD_ADDR_iop_sw_cfg_rw_sap_in_owner 28
#define REG_WR_ADDR_iop_sw_cfg_rw_sap_in_owner 28

/*                                                      */
typedef struct {
  unsigned int cfg : 2;
  unsigned int dummy1 : 30;
} reg_iop_sw_cfg_rw_sap_out_owner;
#define REG_RD_ADDR_iop_sw_cfg_rw_sap_out_owner 32
#define REG_WR_ADDR_iop_sw_cfg_rw_sap_out_owner 32

/*                                                      */
typedef struct {
  unsigned int cfg : 2;
  unsigned int dummy1 : 30;
} reg_iop_sw_cfg_rw_scrc_in_owner;
#define REG_RD_ADDR_iop_sw_cfg_rw_scrc_in_owner 36
#define REG_WR_ADDR_iop_sw_cfg_rw_scrc_in_owner 36

/*                                                       */
typedef struct {
  unsigned int cfg : 2;
  unsigned int dummy1 : 30;
} reg_iop_sw_cfg_rw_scrc_out_owner;
#define REG_RD_ADDR_iop_sw_cfg_rw_scrc_out_owner 40
#define REG_WR_ADDR_iop_sw_cfg_rw_scrc_out_owner 40

/*                                                  */
typedef struct {
  unsigned int cfg : 1;
  unsigned int dummy1 : 31;
} reg_iop_sw_cfg_rw_spu_owner;
#define REG_RD_ADDR_iop_sw_cfg_rw_spu_owner 44
#define REG_WR_ADDR_iop_sw_cfg_rw_spu_owner 44

/*                                                         */
typedef struct {
  unsigned int cfg : 2;
  unsigned int dummy1 : 30;
} reg_iop_sw_cfg_rw_timer_grp0_owner;
#define REG_RD_ADDR_iop_sw_cfg_rw_timer_grp0_owner 48
#define REG_WR_ADDR_iop_sw_cfg_rw_timer_grp0_owner 48

/*                                                         */
typedef struct {
  unsigned int cfg : 2;
  unsigned int dummy1 : 30;
} reg_iop_sw_cfg_rw_timer_grp1_owner;
#define REG_RD_ADDR_iop_sw_cfg_rw_timer_grp1_owner 52
#define REG_WR_ADDR_iop_sw_cfg_rw_timer_grp1_owner 52

/*                                                           */
typedef struct {
  unsigned int cfg : 2;
  unsigned int dummy1 : 30;
} reg_iop_sw_cfg_rw_trigger_grp0_owner;
#define REG_RD_ADDR_iop_sw_cfg_rw_trigger_grp0_owner 56
#define REG_WR_ADDR_iop_sw_cfg_rw_trigger_grp0_owner 56

/*                                                           */
typedef struct {
  unsigned int cfg : 2;
  unsigned int dummy1 : 30;
} reg_iop_sw_cfg_rw_trigger_grp1_owner;
#define REG_RD_ADDR_iop_sw_cfg_rw_trigger_grp1_owner 60
#define REG_WR_ADDR_iop_sw_cfg_rw_trigger_grp1_owner 60

/*                                                           */
typedef struct {
  unsigned int cfg : 2;
  unsigned int dummy1 : 30;
} reg_iop_sw_cfg_rw_trigger_grp2_owner;
#define REG_RD_ADDR_iop_sw_cfg_rw_trigger_grp2_owner 64
#define REG_WR_ADDR_iop_sw_cfg_rw_trigger_grp2_owner 64

/*                                                           */
typedef struct {
  unsigned int cfg : 2;
  unsigned int dummy1 : 30;
} reg_iop_sw_cfg_rw_trigger_grp3_owner;
#define REG_RD_ADDR_iop_sw_cfg_rw_trigger_grp3_owner 68
#define REG_WR_ADDR_iop_sw_cfg_rw_trigger_grp3_owner 68

/*                                                           */
typedef struct {
  unsigned int cfg : 2;
  unsigned int dummy1 : 30;
} reg_iop_sw_cfg_rw_trigger_grp4_owner;
#define REG_RD_ADDR_iop_sw_cfg_rw_trigger_grp4_owner 72
#define REG_WR_ADDR_iop_sw_cfg_rw_trigger_grp4_owner 72

/*                                                           */
typedef struct {
  unsigned int cfg : 2;
  unsigned int dummy1 : 30;
} reg_iop_sw_cfg_rw_trigger_grp5_owner;
#define REG_RD_ADDR_iop_sw_cfg_rw_trigger_grp5_owner 76
#define REG_WR_ADDR_iop_sw_cfg_rw_trigger_grp5_owner 76

/*                                                           */
typedef struct {
  unsigned int cfg : 2;
  unsigned int dummy1 : 30;
} reg_iop_sw_cfg_rw_trigger_grp6_owner;
#define REG_RD_ADDR_iop_sw_cfg_rw_trigger_grp6_owner 80
#define REG_WR_ADDR_iop_sw_cfg_rw_trigger_grp6_owner 80

/*                                                           */
typedef struct {
  unsigned int cfg : 2;
  unsigned int dummy1 : 30;
} reg_iop_sw_cfg_rw_trigger_grp7_owner;
#define REG_RD_ADDR_iop_sw_cfg_rw_trigger_grp7_owner 84
#define REG_WR_ADDR_iop_sw_cfg_rw_trigger_grp7_owner 84

/*                                                 */
typedef struct {
  unsigned int byte0 : 8;
  unsigned int byte1 : 8;
  unsigned int byte2 : 8;
  unsigned int byte3 : 8;
} reg_iop_sw_cfg_rw_bus_mask;
#define REG_RD_ADDR_iop_sw_cfg_rw_bus_mask 88
#define REG_WR_ADDR_iop_sw_cfg_rw_bus_mask 88

/*                                                    */
typedef struct {
  unsigned int byte0 : 1;
  unsigned int byte1 : 1;
  unsigned int byte2 : 1;
  unsigned int byte3 : 1;
  unsigned int dummy1 : 28;
} reg_iop_sw_cfg_rw_bus_oe_mask;
#define REG_RD_ADDR_iop_sw_cfg_rw_bus_oe_mask 92
#define REG_WR_ADDR_iop_sw_cfg_rw_bus_oe_mask 92

/*                                                 */
typedef struct {
  unsigned int val : 32;
} reg_iop_sw_cfg_rw_gio_mask;
#define REG_RD_ADDR_iop_sw_cfg_rw_gio_mask 96
#define REG_WR_ADDR_iop_sw_cfg_rw_gio_mask 96

/*                                                    */
typedef struct {
  unsigned int val : 32;
} reg_iop_sw_cfg_rw_gio_oe_mask;
#define REG_RD_ADDR_iop_sw_cfg_rw_gio_oe_mask 100
#define REG_WR_ADDR_iop_sw_cfg_rw_gio_oe_mask 100

/*                                                   */
typedef struct {
  unsigned int bus_byte0 : 2;
  unsigned int bus_byte1 : 2;
  unsigned int bus_byte2 : 2;
  unsigned int bus_byte3 : 2;
  unsigned int gio3_0    : 2;
  unsigned int gio7_4    : 2;
  unsigned int gio11_8   : 2;
  unsigned int gio15_12  : 2;
  unsigned int gio19_16  : 2;
  unsigned int gio23_20  : 2;
  unsigned int gio27_24  : 2;
  unsigned int gio31_28  : 2;
  unsigned int dummy1    : 8;
} reg_iop_sw_cfg_rw_pinmapping;
#define REG_RD_ADDR_iop_sw_cfg_rw_pinmapping 104
#define REG_WR_ADDR_iop_sw_cfg_rw_pinmapping 104

/*                                                    */
typedef struct {
  unsigned int bus_lo    : 2;
  unsigned int bus_hi    : 2;
  unsigned int bus_lo_oe : 2;
  unsigned int bus_hi_oe : 2;
  unsigned int dummy1    : 24;
} reg_iop_sw_cfg_rw_bus_out_cfg;
#define REG_RD_ADDR_iop_sw_cfg_rw_bus_out_cfg 108
#define REG_WR_ADDR_iop_sw_cfg_rw_bus_out_cfg 108

/*                                                         */
typedef struct {
  unsigned int gio0    : 3;
  unsigned int gio0_oe : 1;
  unsigned int gio1    : 3;
  unsigned int gio1_oe : 1;
  unsigned int gio2    : 3;
  unsigned int gio2_oe : 1;
  unsigned int gio3    : 3;
  unsigned int gio3_oe : 1;
  unsigned int dummy1  : 16;
} reg_iop_sw_cfg_rw_gio_out_grp0_cfg;
#define REG_RD_ADDR_iop_sw_cfg_rw_gio_out_grp0_cfg 112
#define REG_WR_ADDR_iop_sw_cfg_rw_gio_out_grp0_cfg 112

/*                                                         */
typedef struct {
  unsigned int gio4    : 3;
  unsigned int gio4_oe : 1;
  unsigned int gio5    : 3;
  unsigned int gio5_oe : 1;
  unsigned int gio6    : 3;
  unsigned int gio6_oe : 1;
  unsigned int gio7    : 3;
  unsigned int gio7_oe : 1;
  unsigned int dummy1  : 16;
} reg_iop_sw_cfg_rw_gio_out_grp1_cfg;
#define REG_RD_ADDR_iop_sw_cfg_rw_gio_out_grp1_cfg 116
#define REG_WR_ADDR_iop_sw_cfg_rw_gio_out_grp1_cfg 116

/*                                                         */
typedef struct {
  unsigned int gio8     : 3;
  unsigned int gio8_oe  : 1;
  unsigned int gio9     : 3;
  unsigned int gio9_oe  : 1;
  unsigned int gio10    : 3;
  unsigned int gio10_oe : 1;
  unsigned int gio11    : 3;
  unsigned int gio11_oe : 1;
  unsigned int dummy1   : 16;
} reg_iop_sw_cfg_rw_gio_out_grp2_cfg;
#define REG_RD_ADDR_iop_sw_cfg_rw_gio_out_grp2_cfg 120
#define REG_WR_ADDR_iop_sw_cfg_rw_gio_out_grp2_cfg 120

/*                                                         */
typedef struct {
  unsigned int gio12    : 3;
  unsigned int gio12_oe : 1;
  unsigned int gio13    : 3;
  unsigned int gio13_oe : 1;
  unsigned int gio14    : 3;
  unsigned int gio14_oe : 1;
  unsigned int gio15    : 3;
  unsigned int gio15_oe : 1;
  unsigned int dummy1   : 16;
} reg_iop_sw_cfg_rw_gio_out_grp3_cfg;
#define REG_RD_ADDR_iop_sw_cfg_rw_gio_out_grp3_cfg 124
#define REG_WR_ADDR_iop_sw_cfg_rw_gio_out_grp3_cfg 124

/*                                                         */
typedef struct {
  unsigned int gio16    : 3;
  unsigned int gio16_oe : 1;
  unsigned int gio17    : 3;
  unsigned int gio17_oe : 1;
  unsigned int gio18    : 3;
  unsigned int gio18_oe : 1;
  unsigned int gio19    : 3;
  unsigned int gio19_oe : 1;
  unsigned int dummy1   : 16;
} reg_iop_sw_cfg_rw_gio_out_grp4_cfg;
#define REG_RD_ADDR_iop_sw_cfg_rw_gio_out_grp4_cfg 128
#define REG_WR_ADDR_iop_sw_cfg_rw_gio_out_grp4_cfg 128

/*                                                         */
typedef struct {
  unsigned int gio20    : 3;
  unsigned int gio20_oe : 1;
  unsigned int gio21    : 3;
  unsigned int gio21_oe : 1;
  unsigned int gio22    : 3;
  unsigned int gio22_oe : 1;
  unsigned int gio23    : 3;
  unsigned int gio23_oe : 1;
  unsigned int dummy1   : 16;
} reg_iop_sw_cfg_rw_gio_out_grp5_cfg;
#define REG_RD_ADDR_iop_sw_cfg_rw_gio_out_grp5_cfg 132
#define REG_WR_ADDR_iop_sw_cfg_rw_gio_out_grp5_cfg 132

/*                                                         */
typedef struct {
  unsigned int gio24    : 3;
  unsigned int gio24_oe : 1;
  unsigned int gio25    : 3;
  unsigned int gio25_oe : 1;
  unsigned int gio26    : 3;
  unsigned int gio26_oe : 1;
  unsigned int gio27    : 3;
  unsigned int gio27_oe : 1;
  unsigned int dummy1   : 16;
} reg_iop_sw_cfg_rw_gio_out_grp6_cfg;
#define REG_RD_ADDR_iop_sw_cfg_rw_gio_out_grp6_cfg 136
#define REG_WR_ADDR_iop_sw_cfg_rw_gio_out_grp6_cfg 136

/*                                                         */
typedef struct {
  unsigned int gio28    : 3;
  unsigned int gio28_oe : 1;
  unsigned int gio29    : 3;
  unsigned int gio29_oe : 1;
  unsigned int gio30    : 3;
  unsigned int gio30_oe : 1;
  unsigned int gio31    : 3;
  unsigned int gio31_oe : 1;
  unsigned int dummy1   : 16;
} reg_iop_sw_cfg_rw_gio_out_grp7_cfg;
#define REG_RD_ADDR_iop_sw_cfg_rw_gio_out_grp7_cfg 140
#define REG_WR_ADDR_iop_sw_cfg_rw_gio_out_grp7_cfg 140

/*                                                */
typedef struct {
  unsigned int bus0_in : 1;
  unsigned int bus1_in : 1;
  unsigned int dummy1  : 30;
} reg_iop_sw_cfg_rw_spu_cfg;
#define REG_RD_ADDR_iop_sw_cfg_rw_spu_cfg 144
#define REG_WR_ADDR_iop_sw_cfg_rw_spu_cfg 144

/*                                                       */
typedef struct {
  unsigned int ext_clk  : 3;
  unsigned int tmr0_en  : 2;
  unsigned int tmr1_en  : 2;
  unsigned int tmr2_en  : 2;
  unsigned int tmr3_en  : 2;
  unsigned int tmr0_dis : 2;
  unsigned int tmr1_dis : 2;
  unsigned int tmr2_dis : 2;
  unsigned int tmr3_dis : 2;
  unsigned int dummy1   : 13;
} reg_iop_sw_cfg_rw_timer_grp0_cfg;
#define REG_RD_ADDR_iop_sw_cfg_rw_timer_grp0_cfg 148
#define REG_WR_ADDR_iop_sw_cfg_rw_timer_grp0_cfg 148

/*                                                       */
typedef struct {
  unsigned int ext_clk  : 3;
  unsigned int tmr0_en  : 2;
  unsigned int tmr1_en  : 2;
  unsigned int tmr2_en  : 2;
  unsigned int tmr3_en  : 2;
  unsigned int tmr0_dis : 2;
  unsigned int tmr1_dis : 2;
  unsigned int tmr2_dis : 2;
  unsigned int tmr3_dis : 2;
  unsigned int dummy1   : 13;
} reg_iop_sw_cfg_rw_timer_grp1_cfg;
#define REG_RD_ADDR_iop_sw_cfg_rw_timer_grp1_cfg 152
#define REG_WR_ADDR_iop_sw_cfg_rw_timer_grp1_cfg 152

/*                                                         */
typedef struct {
  unsigned int grp0_dis : 1;
  unsigned int grp0_en  : 1;
  unsigned int grp1_dis : 1;
  unsigned int grp1_en  : 1;
  unsigned int grp2_dis : 1;
  unsigned int grp2_en  : 1;
  unsigned int grp3_dis : 1;
  unsigned int grp3_en  : 1;
  unsigned int grp4_dis : 1;
  unsigned int grp4_en  : 1;
  unsigned int grp5_dis : 1;
  unsigned int grp5_en  : 1;
  unsigned int grp6_dis : 1;
  unsigned int grp6_en  : 1;
  unsigned int grp7_dis : 1;
  unsigned int grp7_en  : 1;
  unsigned int dummy1   : 16;
} reg_iop_sw_cfg_rw_trigger_grps_cfg;
#define REG_RD_ADDR_iop_sw_cfg_rw_trigger_grps_cfg 156
#define REG_WR_ADDR_iop_sw_cfg_rw_trigger_grps_cfg 156

/*                                                */
typedef struct {
  unsigned int out_strb : 4;
  unsigned int in_src   : 2;
  unsigned int in_size  : 3;
  unsigned int in_last  : 2;
  unsigned int in_strb  : 4;
  unsigned int dummy1   : 17;
} reg_iop_sw_cfg_rw_pdp_cfg;
#define REG_RD_ADDR_iop_sw_cfg_rw_pdp_cfg 160
#define REG_WR_ADDR_iop_sw_cfg_rw_pdp_cfg 160

/*                                                */
typedef struct {
  unsigned int sdp_out_strb : 3;
  unsigned int sdp_in_data  : 3;
  unsigned int sdp_in_last  : 2;
  unsigned int sdp_in_strb  : 3;
  unsigned int dummy1       : 21;
} reg_iop_sw_cfg_rw_sdp_cfg;
#define REG_RD_ADDR_iop_sw_cfg_rw_sdp_cfg 164
#define REG_WR_ADDR_iop_sw_cfg_rw_sdp_cfg 164


/*           */
enum {
  regk_iop_sw_cfg_a                        = 0x00000001,
  regk_iop_sw_cfg_b                        = 0x00000002,
  regk_iop_sw_cfg_bus                      = 0x00000000,
  regk_iop_sw_cfg_bus_rot16                = 0x00000002,
  regk_iop_sw_cfg_bus_rot24                = 0x00000003,
  regk_iop_sw_cfg_bus_rot8                 = 0x00000001,
  regk_iop_sw_cfg_clk12                    = 0x00000000,
  regk_iop_sw_cfg_cpu                      = 0x00000000,
  regk_iop_sw_cfg_gated_clk0               = 0x0000000e,
  regk_iop_sw_cfg_gated_clk1               = 0x0000000f,
  regk_iop_sw_cfg_gio0                     = 0x00000004,
  regk_iop_sw_cfg_gio1                     = 0x00000001,
  regk_iop_sw_cfg_gio2                     = 0x00000005,
  regk_iop_sw_cfg_gio3                     = 0x00000002,
  regk_iop_sw_cfg_gio4                     = 0x00000006,
  regk_iop_sw_cfg_gio5                     = 0x00000003,
  regk_iop_sw_cfg_gio6                     = 0x00000007,
  regk_iop_sw_cfg_gio7                     = 0x00000004,
  regk_iop_sw_cfg_gio_in18                 = 0x00000002,
  regk_iop_sw_cfg_gio_in19                 = 0x00000003,
  regk_iop_sw_cfg_gio_in20                 = 0x00000004,
  regk_iop_sw_cfg_gio_in21                 = 0x00000005,
  regk_iop_sw_cfg_gio_in26                 = 0x00000006,
  regk_iop_sw_cfg_gio_in27                 = 0x00000007,
  regk_iop_sw_cfg_gio_in4                  = 0x00000000,
  regk_iop_sw_cfg_gio_in5                  = 0x00000001,
  regk_iop_sw_cfg_last_timer_grp0_tmr2     = 0x00000001,
  regk_iop_sw_cfg_last_timer_grp1_tmr2     = 0x00000002,
  regk_iop_sw_cfg_last_timer_grp1_tmr3     = 0x00000003,
  regk_iop_sw_cfg_mpu                      = 0x00000001,
  regk_iop_sw_cfg_none                     = 0x00000000,
  regk_iop_sw_cfg_pdp_out                  = 0x00000001,
  regk_iop_sw_cfg_pdp_out_hi               = 0x00000001,
  regk_iop_sw_cfg_pdp_out_lo               = 0x00000000,
  regk_iop_sw_cfg_rw_bus_mask_default      = 0x00000000,
  regk_iop_sw_cfg_rw_bus_oe_mask_default   = 0x00000000,
  regk_iop_sw_cfg_rw_bus_out_cfg_default   = 0x00000000,
  regk_iop_sw_cfg_rw_crc_par_owner_default = 0x00000000,
  regk_iop_sw_cfg_rw_dmc_in_owner_default  = 0x00000000,
  regk_iop_sw_cfg_rw_dmc_out_owner_default = 0x00000000,
  regk_iop_sw_cfg_rw_fifo_in_extra_owner_default = 0x00000000,
  regk_iop_sw_cfg_rw_fifo_in_owner_default = 0x00000000,
  regk_iop_sw_cfg_rw_fifo_out_extra_owner_default = 0x00000000,
  regk_iop_sw_cfg_rw_fifo_out_owner_default = 0x00000000,
  regk_iop_sw_cfg_rw_gio_mask_default      = 0x00000000,
  regk_iop_sw_cfg_rw_gio_oe_mask_default   = 0x00000000,
  regk_iop_sw_cfg_rw_gio_out_grp0_cfg_default = 0x00000000,
  regk_iop_sw_cfg_rw_gio_out_grp1_cfg_default = 0x00000000,
  regk_iop_sw_cfg_rw_gio_out_grp2_cfg_default = 0x00000000,
  regk_iop_sw_cfg_rw_gio_out_grp3_cfg_default = 0x00000000,
  regk_iop_sw_cfg_rw_gio_out_grp4_cfg_default = 0x00000000,
  regk_iop_sw_cfg_rw_gio_out_grp5_cfg_default = 0x00000000,
  regk_iop_sw_cfg_rw_gio_out_grp6_cfg_default = 0x00000000,
  regk_iop_sw_cfg_rw_gio_out_grp7_cfg_default = 0x00000000,
  regk_iop_sw_cfg_rw_pdp_cfg_default       = 0x00000000,
  regk_iop_sw_cfg_rw_pinmapping_default    = 0x00555555,
  regk_iop_sw_cfg_rw_sap_in_owner_default  = 0x00000000,
  regk_iop_sw_cfg_rw_sap_out_owner_default = 0x00000000,
  regk_iop_sw_cfg_rw_scrc_in_owner_default = 0x00000000,
  regk_iop_sw_cfg_rw_scrc_out_owner_default = 0x00000000,
  regk_iop_sw_cfg_rw_sdp_cfg_default       = 0x00000000,
  regk_iop_sw_cfg_rw_spu_cfg_default       = 0x00000000,
  regk_iop_sw_cfg_rw_spu_owner_default     = 0x00000000,
  regk_iop_sw_cfg_rw_timer_grp0_cfg_default = 0x00000000,
  regk_iop_sw_cfg_rw_timer_grp0_owner_default = 0x00000000,
  regk_iop_sw_cfg_rw_timer_grp1_cfg_default = 0x00000000,
  regk_iop_sw_cfg_rw_timer_grp1_owner_default = 0x00000000,
  regk_iop_sw_cfg_rw_trigger_grp0_owner_default = 0x00000000,
  regk_iop_sw_cfg_rw_trigger_grp1_owner_default = 0x00000000,
  regk_iop_sw_cfg_rw_trigger_grp2_owner_default = 0x00000000,
  regk_iop_sw_cfg_rw_trigger_grp3_owner_default = 0x00000000,
  regk_iop_sw_cfg_rw_trigger_grp4_owner_default = 0x00000000,
  regk_iop_sw_cfg_rw_trigger_grp5_owner_default = 0x00000000,
  regk_iop_sw_cfg_rw_trigger_grp6_owner_default = 0x00000000,
  regk_iop_sw_cfg_rw_trigger_grp7_owner_default = 0x00000000,
  regk_iop_sw_cfg_rw_trigger_grps_cfg_default = 0x00000000,
  regk_iop_sw_cfg_sdp_out                  = 0x00000004,
  regk_iop_sw_cfg_size16                   = 0x00000002,
  regk_iop_sw_cfg_size24                   = 0x00000003,
  regk_iop_sw_cfg_size32                   = 0x00000004,
  regk_iop_sw_cfg_size8                    = 0x00000001,
  regk_iop_sw_cfg_spu                      = 0x00000002,
  regk_iop_sw_cfg_spu_bus_out0_hi          = 0x00000002,
  regk_iop_sw_cfg_spu_bus_out0_lo          = 0x00000002,
  regk_iop_sw_cfg_spu_bus_out1_hi          = 0x00000003,
  regk_iop_sw_cfg_spu_bus_out1_lo          = 0x00000003,
  regk_iop_sw_cfg_spu_g0                   = 0x00000007,
  regk_iop_sw_cfg_spu_g1                   = 0x00000007,
  regk_iop_sw_cfg_spu_g2                   = 0x00000007,
  regk_iop_sw_cfg_spu_g3                   = 0x00000007,
  regk_iop_sw_cfg_spu_g4                   = 0x00000007,
  regk_iop_sw_cfg_spu_g5                   = 0x00000007,
  regk_iop_sw_cfg_spu_g6                   = 0x00000007,
  regk_iop_sw_cfg_spu_g7                   = 0x00000007,
  regk_iop_sw_cfg_spu_gio0                 = 0x00000000,
  regk_iop_sw_cfg_spu_gio1                 = 0x00000001,
  regk_iop_sw_cfg_spu_gio5                 = 0x00000005,
  regk_iop_sw_cfg_spu_gio6                 = 0x00000006,
  regk_iop_sw_cfg_spu_gio7                 = 0x00000007,
  regk_iop_sw_cfg_spu_gio_out0             = 0x00000008,
  regk_iop_sw_cfg_spu_gio_out1             = 0x00000009,
  regk_iop_sw_cfg_spu_gio_out2             = 0x0000000a,
  regk_iop_sw_cfg_spu_gio_out3             = 0x0000000b,
  regk_iop_sw_cfg_spu_gio_out4             = 0x0000000c,
  regk_iop_sw_cfg_spu_gio_out5             = 0x0000000d,
  regk_iop_sw_cfg_spu_gio_out6             = 0x0000000e,
  regk_iop_sw_cfg_spu_gio_out7             = 0x0000000f,
  regk_iop_sw_cfg_spu_gioout0              = 0x00000000,
  regk_iop_sw_cfg_spu_gioout1              = 0x00000000,
  regk_iop_sw_cfg_spu_gioout10             = 0x00000007,
  regk_iop_sw_cfg_spu_gioout11             = 0x00000007,
  regk_iop_sw_cfg_spu_gioout12             = 0x00000007,
  regk_iop_sw_cfg_spu_gioout13             = 0x00000007,
  regk_iop_sw_cfg_spu_gioout14             = 0x00000007,
  regk_iop_sw_cfg_spu_gioout15             = 0x00000007,
  regk_iop_sw_cfg_spu_gioout16             = 0x00000007,
  regk_iop_sw_cfg_spu_gioout17             = 0x00000007,
  regk_iop_sw_cfg_spu_gioout18             = 0x00000007,
  regk_iop_sw_cfg_spu_gioout19             = 0x00000007,
  regk_iop_sw_cfg_spu_gioout2              = 0x00000001,
  regk_iop_sw_cfg_spu_gioout20             = 0x00000007,
  regk_iop_sw_cfg_spu_gioout21             = 0x00000007,
  regk_iop_sw_cfg_spu_gioout22             = 0x00000007,
  regk_iop_sw_cfg_spu_gioout23             = 0x00000007,
  regk_iop_sw_cfg_spu_gioout24             = 0x00000007,
  regk_iop_sw_cfg_spu_gioout25             = 0x00000007,
  regk_iop_sw_cfg_spu_gioout26             = 0x00000007,
  regk_iop_sw_cfg_spu_gioout27             = 0x00000007,
  regk_iop_sw_cfg_spu_gioout28             = 0x00000007,
  regk_iop_sw_cfg_spu_gioout29             = 0x00000007,
  regk_iop_sw_cfg_spu_gioout3              = 0x00000001,
  regk_iop_sw_cfg_spu_gioout30             = 0x00000007,
  regk_iop_sw_cfg_spu_gioout31             = 0x00000007,
  regk_iop_sw_cfg_spu_gioout4              = 0x00000002,
  regk_iop_sw_cfg_spu_gioout5              = 0x00000002,
  regk_iop_sw_cfg_spu_gioout6              = 0x00000003,
  regk_iop_sw_cfg_spu_gioout7              = 0x00000003,
  regk_iop_sw_cfg_spu_gioout8              = 0x00000007,
  regk_iop_sw_cfg_spu_gioout9              = 0x00000007,
  regk_iop_sw_cfg_strb_timer_grp0_tmr0     = 0x00000001,
  regk_iop_sw_cfg_strb_timer_grp0_tmr1     = 0x00000002,
  regk_iop_sw_cfg_strb_timer_grp1_tmr0     = 0x00000003,
  regk_iop_sw_cfg_strb_timer_grp1_tmr1     = 0x00000002,
  regk_iop_sw_cfg_timer_grp0               = 0x00000000,
  regk_iop_sw_cfg_timer_grp0_rot           = 0x00000001,
  regk_iop_sw_cfg_timer_grp0_strb0         = 0x00000005,
  regk_iop_sw_cfg_timer_grp0_strb1         = 0x00000005,
  regk_iop_sw_cfg_timer_grp0_strb2         = 0x00000005,
  regk_iop_sw_cfg_timer_grp0_strb3         = 0x00000005,
  regk_iop_sw_cfg_timer_grp0_tmr0          = 0x00000002,
  regk_iop_sw_cfg_timer_grp1               = 0x00000000,
  regk_iop_sw_cfg_timer_grp1_rot           = 0x00000001,
  regk_iop_sw_cfg_timer_grp1_strb0         = 0x00000006,
  regk_iop_sw_cfg_timer_grp1_strb1         = 0x00000006,
  regk_iop_sw_cfg_timer_grp1_strb2         = 0x00000006,
  regk_iop_sw_cfg_timer_grp1_strb3         = 0x00000006,
  regk_iop_sw_cfg_timer_grp1_tmr0          = 0x00000003,
  regk_iop_sw_cfg_trig0_0                  = 0x00000000,
  regk_iop_sw_cfg_trig0_1                  = 0x00000000,
  regk_iop_sw_cfg_trig0_2                  = 0x00000000,
  regk_iop_sw_cfg_trig0_3                  = 0x00000000,
  regk_iop_sw_cfg_trig1_0                  = 0x00000000,
  regk_iop_sw_cfg_trig1_1                  = 0x00000000,
  regk_iop_sw_cfg_trig1_2                  = 0x00000000,
  regk_iop_sw_cfg_trig1_3                  = 0x00000000,
  regk_iop_sw_cfg_trig2_0                  = 0x00000001,
  regk_iop_sw_cfg_trig2_1                  = 0x00000001,
  regk_iop_sw_cfg_trig2_2                  = 0x00000001,
  regk_iop_sw_cfg_trig2_3                  = 0x00000001,
  regk_iop_sw_cfg_trig3_0                  = 0x00000001,
  regk_iop_sw_cfg_trig3_1                  = 0x00000001,
  regk_iop_sw_cfg_trig3_2                  = 0x00000001,
  regk_iop_sw_cfg_trig3_3                  = 0x00000001,
  regk_iop_sw_cfg_trig4_0                  = 0x00000002,
  regk_iop_sw_cfg_trig4_1                  = 0x00000002,
  regk_iop_sw_cfg_trig4_2                  = 0x00000002,
  regk_iop_sw_cfg_trig4_3                  = 0x00000002,
  regk_iop_sw_cfg_trig5_0                  = 0x00000002,
  regk_iop_sw_cfg_trig5_1                  = 0x00000002,
  regk_iop_sw_cfg_trig5_2                  = 0x00000002,
  regk_iop_sw_cfg_trig5_3                  = 0x00000002,
  regk_iop_sw_cfg_trig6_0                  = 0x00000003,
  regk_iop_sw_cfg_trig6_1                  = 0x00000003,
  regk_iop_sw_cfg_trig6_2                  = 0x00000003,
  regk_iop_sw_cfg_trig6_3                  = 0x00000003,
  regk_iop_sw_cfg_trig7_0                  = 0x00000003,
  regk_iop_sw_cfg_trig7_1                  = 0x00000003,
  regk_iop_sw_cfg_trig7_2                  = 0x00000003,
  regk_iop_sw_cfg_trig7_3                  = 0x00000003
};
#endif /*                     */
