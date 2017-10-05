
This repertory contains the source code of the DUAL-POB I2C library.

General Information
===================


The library manage the DUAL-POB device from i2c bus.

You can modify the source code of this library for your specific platform.


How to use
==========


- Upload the default DUAL-POB firmware (dualpob_firmware.hex) into the DUAL-POB device

- Configure the library by open dualpob_i2c_lib.c

- By default, the dualpob_i2c_lib.c works for POB-EYE platform.

- Change the include section with your own include .

- Change the i2c functions sections with your own i2c functions:
i2c_start_sendaddr, i2c_write, i2c_read_ack, i2c_read_noack and i2c_stop

- Compile the dualpob_i2c_lib.c for your platform.



