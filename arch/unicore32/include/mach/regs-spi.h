/*
                                                      
 */
/*
                         
 */
#define SPI_CR0		(PKUNITY_SPI_BASE + 0x0000)
/*
                         
 */
#define SPI_CR1		(PKUNITY_SPI_BASE + 0x0004)
/*
                        
 */
#define SPI_SSIENR	(PKUNITY_SPI_BASE + 0x0008)
/*
                    
 */
#define SPI_SR		(PKUNITY_SPI_BASE + 0x0028)
/*
                             
 */
#define SPI_IMR		(PKUNITY_SPI_BASE + 0x002C)
/*
                               
 */
#define SPI_ISR		(PKUNITY_SPI_BASE + 0x0030)

/*
                                      
 */
#define SPI_SSIENR_EN		FIELD(1, 1, 0)

/*
                       
 */
#define SPI_SR_BUSY		FIELD(1, 1, 0)
/*
                                     
 */
#define SPI_SR_TFNF		FIELD(1, 1, 1)
/*
                                 
 */
#define SPI_SR_TFE		FIELD(1, 1, 2)
/*
                                     
 */
#define SPI_SR_RFNE		FIELD(1, 1, 3)
/*
                               
 */
#define SPI_SR_RFF		FIELD(1, 1, 4)

/*
                                                   
 */
#define SPI_ISR_TXEIS		FIELD(1, 1, 0)
/*
                                                      
 */
#define SPI_ISR_TXOIS		FIELD(1, 1, 1)
/*
                                                        
 */
#define SPI_ISR_RXUIS		FIELD(1, 1, 2)
/*
                                                       
 */
#define SPI_ISR_RXOIS		FIELD(1, 1, 3)
/*
                                                   
 */
#define SPI_ISR_RXFIS		FIELD(1, 1, 4)
#define SPI_ISR_MSTIS		FIELD(1, 1, 5)

/*
                                                 
 */
#define SPI_IMR_TXEIM		FIELD(1, 1, 0)
/*
                                                    
 */
#define SPI_IMR_TXOIM		FIELD(1, 1, 1)
/*
                                                      
 */
#define SPI_IMR_RXUIM		FIELD(1, 1, 2)
/*
                                                     
 */
#define SPI_IMR_RXOIM		FIELD(1, 1, 3)
/*
                                                 
 */
#define SPI_IMR_RXFIM		FIELD(1, 1, 4)
#define SPI_IMR_MSTIM		FIELD(1, 1, 5)

