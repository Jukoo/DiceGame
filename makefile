#!/usr/bin/env make 

AVRC = amake 
uc_serial_port = /dev/ttyUSB0 




avr_check : 
	$(AVRC) -v 

avr_upload : 
	$(AVRC) -u 

avr_serial :
	$(AVRC) -s 


avr_all : 
	$(AVRC) -v && \
		$(AVRC) -u && \
		$(AVRC) -s


