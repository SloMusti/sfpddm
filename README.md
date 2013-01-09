sfpddm
======

Arduino library for interfacing SFP modules and reading DDM information as per SFF-8472. The library is following the standard but is not yet fully compliant, some additional rarely used functions need to be implemented for that.


How it works
------------

The library offers functions that return measurements in the form specified by the standerd. Handles the externally callibrated data as well, performs the necessary calculations and outputs the results as if they were internaly calibrated.

For communication the specified I2C library is internally initialized, the default Arduino I2C library is not reliable enough and can not be used.
Please obtain and install the I2C library by Wayne Truchsess http://dsscircuits.com/articles/arduino-i2c-master-library.html

Hardware connections
-------------
Connect the SFP module to the I2C port of your Arduino. Accessing the I2C port of the SFP module is generally possible only with a SFP cradle attached to a PCB or hacking an existing circuit, such as TP-Link MC220L media converter.

Function description
-------------
Available in the main library file.
