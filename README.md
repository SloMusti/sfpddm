sfpddm
======

Arduino library for interfacing SFP modules and reading DDM information as per SFF-8472


How it works.

The library offers functions that return measurements in the form specified by the standerd. Handles the externally callibrated data as well, performs the necessary calculations and outputs the results as if they were internaly calibrated.

For communication the specified I2C library is internally initialized, the default Arduino I2C library is not reliable enough and can not be used.

