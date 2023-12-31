Irrigation Pump Control
=======================

This is an Arduino program to control an irrigation pump that has a filter. It prevents the pump of running while the filter is clogged and shows alerts through LEDs to let be known maintenance is needed.

It uses the [AC712-arduino](https://github.com/rkoptev/ACS712-arduino) library.

It detects if the pump is running using an ACS712 current detector. If the time defined on `PUMP_RUN_TIME` exceeds, the relay is turned off, the pump is shut down and the red LED turns on.

`CLEAN_FILTER_ALERT` sets the time that shows that maintenance is required, but the pump can keep working. The yellow LED lights on.
