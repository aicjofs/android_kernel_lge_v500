/* Copyright (c) 2012, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef _MPQ_STREAM_BUFFER_H
#define _MPQ_STREAM_BUFFER_H

#include "dvb_ringbuffer.h"


/* 
                         
  
                                                                            
                                                                          
                                                         
  
                                                               
                                                           
                                                       
  
                                                                     
                                                                               
                                                                               
                                                 
  
                                                                              
                                                                     
                                                                              
                                                                              
                                                                              
                  
                                                                              
                                       
                                                                 
  
                                                                         
                                                               
                                                                   
                                                                        
                                                                
                                              
                                         
  
                                                             
                                 
  
                                   
  
                                                                    
                                                      
  
                                        
  
                                                                 
                                       
  
                                                                                
                                                                               
                                                                           
  
                                   
  
                                    
                                                      
  
                                                                            
                                                                             
  
                                 
                                    
                                                       
                                          
  
                                    
                                     
  
                                                                       
  
                                                
                                       
  
                                                                            
                                                                   
                                                                                
                                                                        
                                                                             
              
  
                                                                        
                                                                          
                                                                           
                                                            
  
                         
                                         
  
                                                                             
                                                                                
                                                                          

  
 */

struct mpq_streambuffer;

typedef void (*mpq_streambuffer_pkt_dispose_cb) (
	struct mpq_streambuffer *sbuff,
	void *user_data);

enum mpq_streambuffer_mode {
	MPQ_STREAMBUFFER_BUFFER_MODE_RING,
	MPQ_STREAMBUFFER_BUFFER_MODE_LINEAR
};

/* 
                                                             
  
                                                                            
                                                      
                                                                           
                          
                                                                              
            
                                                 
                                                                             
                       
 */
struct mpq_streambuffer {
	struct dvb_ringbuffer raw_data;
	struct dvb_ringbuffer packet_data;
	struct mpq_streambuffer_buffer_desc *buffers;
	enum mpq_streambuffer_mode mode;
	u32 buffers_num;
	u32 pending_buffers_count;
	mpq_streambuffer_pkt_dispose_cb cb;
	void *cb_user_data;
};

/* 
                               
                                                  
                                                   
                                   
                        
                                                               
                                                                 
 */
struct mpq_streambuffer_buffer_desc {
	int	handle;
	void	*base;
	u32	size;
	u32	read_ptr;
	u32	write_ptr;
};

/* 
                                                                               
                                                     
                                                                    
                                                                           
                                                                    
  
                                                            
                
                  
                  
               
                          
 */
struct mpq_streambuffer_packet_header {
	u32 user_data_len;
	int raw_data_handle;
	u32 raw_data_offset;
	u32 raw_data_len;
} __packed;

/* 
                                                         
  
                                   
                                                     
                                                                 
                                         
                                                 
                                             
                                              
  
                                                                   
  
        
                                                                            
                                                                              
                                                                           
                                   
 */
int mpq_streambuffer_init(
		struct mpq_streambuffer *sbuff,
		enum mpq_streambuffer_mode mode,
		struct mpq_streambuffer_buffer_desc *data_buffers,
		u32 data_buff_num,
		void *packet_buff,
		size_t packet_buff_size);

/* 
                                                                         
  
                            
                                                                     
                          
                                          
  
                                                           
  
                                                                
                                                             
                                                                             
 */
ssize_t mpq_streambuffer_pkt_next(
		struct mpq_streambuffer *sbuff,
		ssize_t idx, size_t *pktlen);

/* 
                                                                            
  
                            
                                           
                                    
                                         
  
                                                                    
                                                  
  
                                                                          
                                                                         
                                                                        
                                                                        
                                                           
 */
ssize_t mpq_streambuffer_pkt_read(
		struct mpq_streambuffer *sbuff,
		size_t idx,
		struct mpq_streambuffer_packet_header *packet,
		u8 *user_data);

/* 
                                                                          
  
                            
                                               
                                                                         
                                                                 
  
                                                              
  
                                                                   
                                                                        
 */
int mpq_streambuffer_pkt_dispose(
		struct mpq_streambuffer *sbuff,
		size_t idx,
		int dispose_data);

/* 
                                                                        
  
                            
                                      
                                                  
  
                                                                        
 */
int mpq_streambuffer_pkt_write(
		struct mpq_streambuffer *sbuff,
		struct mpq_streambuffer_packet_header *packet,
		u8 *user_data);

/* 
                                                              
  
                            
                                                  
                                      
  
                                                           
                               
 */
ssize_t mpq_streambuffer_data_write(
		struct mpq_streambuffer *sbuff,
		const u8 *buf, size_t len);

/* 
                                                                               
                                                        
  
                            
                                                            
  
                       
 */
int mpq_streambuffer_data_write_deposit(
		struct mpq_streambuffer *sbuff,
		size_t len);

/* 
                                                                          
  
                            
                                                
                                                             
  
                                                        
  
                                                            
                                                                        
                                                                 
                                                         
                                     
 */
ssize_t mpq_streambuffer_data_read(
		struct mpq_streambuffer *sbuff,
		u8 *buf, size_t len);

/* 
                                  
  
                                                                             
          
 */
ssize_t mpq_streambuffer_data_read_user(
		struct mpq_streambuffer *sbuff,
		u8 __user *buf, size_t len);

/* 
                                                                             
                                                      
  
                            
                                                  
  
                                                                    
                
  
                                                                   
                                                      
 */
int mpq_streambuffer_data_read_dispose(
		struct mpq_streambuffer *sbuff,
		size_t len);
/* 
                                                                         
              
                            
                                                                           
                                           
                                                                 
                                                                   
                 
                
                           
  
                      
                                    
                                                                             
 */
int mpq_streambuffer_get_buffer_handle(
	struct mpq_streambuffer *sbuff,
	int read_buffer,
	int *handle);

/* 
                                                                            
                                   
  
                                                                             
                             
 */
ssize_t mpq_streambuffer_data_free(
	struct mpq_streambuffer *sbuff);

/* 
                                                                            
               
                                   
  
                                                                             
                            
 */
ssize_t mpq_streambuffer_data_avail(
	struct mpq_streambuffer *sbuff);

/* 
                                                                            
                          
               
                                   
                                   
                                                           
  
                       
                                   
 */
int mpq_streambuffer_register_pkt_dispose(
	struct mpq_streambuffer *sbuff,
	mpq_streambuffer_pkt_dispose_cb cb_func,
	void *user_data);

/* 
                                                                               
          
                                   
                                     
                                       
  
                                                                 
                       
                                   
 */
int mpq_streambuffer_get_data_rw_offset(
	struct mpq_streambuffer *sbuff,
	u32 *read_offset,
	u32 *write_offset);

#endif /*                      */

