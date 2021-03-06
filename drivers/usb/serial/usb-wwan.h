/*
                                                    
 */

#ifndef __LINUX_USB_USB_WWAN
#define __LINUX_USB_USB_WWAN

extern void usb_wwan_dtr_rts(struct usb_serial_port *port, int on);
extern int usb_wwan_open(struct tty_struct *tty, struct usb_serial_port *port);
extern void usb_wwan_close(struct usb_serial_port *port);
extern int usb_wwan_startup(struct usb_serial *serial);
extern void usb_wwan_disconnect(struct usb_serial *serial);
extern void usb_wwan_release(struct usb_serial *serial);
extern int usb_wwan_write_room(struct tty_struct *tty);
extern void usb_wwan_set_termios(struct tty_struct *tty,
				 struct usb_serial_port *port,
				 struct ktermios *old);
extern int usb_wwan_tiocmget(struct tty_struct *tty);
extern int usb_wwan_tiocmset(struct tty_struct *tty,
			     unsigned int set, unsigned int clear);
extern int usb_wwan_ioctl(struct tty_struct *tty,
			  unsigned int cmd, unsigned long arg);
extern int usb_wwan_send_setup(struct usb_serial_port *port);
extern int usb_wwan_write(struct tty_struct *tty, struct usb_serial_port *port,
			  const unsigned char *buf, int count);
extern int usb_wwan_chars_in_buffer(struct tty_struct *tty);
extern void usb_wwan_throttle(struct tty_struct *tty);
extern void usb_wwan_unthrottle(struct tty_struct *tty);
#ifdef CONFIG_PM
extern int usb_wwan_suspend(struct usb_serial *serial, pm_message_t message);
extern int usb_wwan_resume(struct usb_serial *serial);
#endif

/*                       */

#define N_IN_URB 5
#define N_OUT_URB 5
#define IN_BUFLEN 16384
#define OUT_BUFLEN 65536

struct usb_wwan_intf_private {
	spinlock_t susp_lock;
	unsigned int suspended:1;
	int in_flight;
	int (*send_setup) (struct usb_serial_port *port);
	void *private;
};

struct usb_wwan_port_private {
	/*                                          */
	struct urb *in_urbs[N_IN_URB];
	u8 *in_buffer[N_IN_URB];
	/*                                           */
	struct urb *out_urbs[N_OUT_URB];
	u8 *out_buffer[N_OUT_URB];
	unsigned long out_busy;	/*                           */
	int opened;
	struct usb_anchor submitted;
	struct usb_anchor delayed;
	struct list_head in_urb_list;
	spinlock_t in_lock;
	ssize_t n_read;
	struct work_struct in_work;

	/*                       */
	int rts_state;		/*                            */
	int dtr_state;
	int cts_state;		/*                           */
	int dsr_state;
	int dcd_state;
	int ri_state;

	unsigned long tx_start_time[N_OUT_URB];
};

#endif /*                      */
