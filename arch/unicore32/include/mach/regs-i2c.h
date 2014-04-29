/*
                                                   
 */

/*
                       
 */
#define I2C_CON		(PKUNITY_I2C_BASE + 0x0000)
/*
                              
 */
#define I2C_TAR		(PKUNITY_I2C_BASE + 0x0004)
/*
                                           
 */
#define I2C_DATACMD	(PKUNITY_I2C_BASE + 0x0010)
/*
                         
 */
#define I2C_ENABLE	(PKUNITY_I2C_BASE + 0x006C)
/*
                         
 */
#define I2C_STATUS	(PKUNITY_I2C_BASE + 0x0070)
/*
                                
 */
#define I2C_TXFLR	(PKUNITY_I2C_BASE + 0x0074)
/*
                                
 */
#define I2C_RXFLR	(PKUNITY_I2C_BASE + 0x0078)
/*
                                  
 */
#define I2C_ENSTATUS	(PKUNITY_I2C_BASE + 0x009C)

#define I2C_CON_MASTER          FIELD(1, 1, 0)
#define I2C_CON_SPEED_STD       FIELD(1, 2, 1)
#define I2C_CON_SPEED_FAST      FIELD(2, 2, 1)
#define I2C_CON_RESTART         FIELD(1, 1, 5)
#define I2C_CON_SLAVEDISABLE    FIELD(1, 1, 6)

#define I2C_DATACMD_READ        FIELD(1, 1, 8)
#define I2C_DATACMD_WRITE       FIELD(0, 1, 8)
#define I2C_DATACMD_DAT_MASK    FMASK(8, 0)
#define I2C_DATACMD_DAT(v)      FIELD((v), 8, 0)

#define I2C_ENABLE_ENABLE       FIELD(1, 1, 0)
#define I2C_ENABLE_DISABLE      FIELD(0, 1, 0)

#define I2C_STATUS_RFF          FIELD(1, 1, 4)
#define I2C_STATUS_RFNE         FIELD(1, 1, 3)
#define I2C_STATUS_TFE          FIELD(1, 1, 2)
#define I2C_STATUS_TFNF         FIELD(1, 1, 1)
#define I2C_STATUS_ACTIVITY     FIELD(1, 1, 0)

#define I2C_ENSTATUS_ENABLE	FIELD(1, 1, 0)

#define I2C_TAR_THERMAL	0x4f
#define I2C_TAR_SPD	0x50
#define I2C_TAR_PWIC    0x55
#define I2C_TAR_EEPROM	0x57
