# 12V Fan Controller with STM32 and PID control
## Overview

This project implements a closed-loop fan controller on a custom 4-layer PCB (manufactured at JLCPCB) with an STM32G0 micrcontroller.
The fan speed is controlled using a PWM signal and regulated to a target RPM using a PID controller.
The tachometer output of the fan is measured with a timer input capture unit, filtered, and fed into the control loop.
Fairly satisfactory control performances have been achieved with Kp=0.01, Ki=0.015, and Kd = 0.001 at 10Hz.

<img width="1418" height="967" alt="image" src="https://github.com/user-attachments/assets/66057595-5b39-46c2-b9a2-18021f8db56d" />


## Hardware features

4 layer board designed with KiCAD, and manufactured at JLCPCB for roughly 100 euros total (including shipping) for 2PCBA and 3PCBs, very minimal and cheap BOM. Production files are in Hardware/Production.

* **Buck Converter** takes 12V input from DC input jack and generates 5V rail (for PWM)
* **Linear Regulator** generates 3.3V rail from 5V (for MCU signals)
* **N-channel MOSFET** for low-side switching to generate appropriate PWM signals for 4-wire fan, inverting logic in firmware
* **Tachometer** open collector input for fan RPM measurement (hardware timer)

Schematics are given below:

<img width="1390" height="983" alt="image" src="https://github.com/user-attachments/assets/26eaa4dc-7006-489e-bc98-745311775731" />

PCB layout:

<img width="1203" height="837" alt="image" src="https://github.com/user-attachments/assets/3d25aa15-9e0b-496b-9d34-15d699efd6f6" />

3D view:

<img width="1657" height="926" alt="image" src="https://github.com/user-attachments/assets/73dcfffc-3a6d-4e86-a8b9-5f80f6a74672" />

Manufactured & assembled boards:

<img width="1200" height="1600" alt="image" src="https://github.com/user-attachments/assets/5eeb956a-3dbf-4cc8-a35b-756ae7c1dee9" />

<img width="739" height="1600" alt="image" src="https://github.com/user-attachments/assets/b41d1412-45b6-4add-ad62-e61a913fb459" />


## System Architecture

* **Tachometer**: Measures period between tach pulses, converts to RPM (tachometer.h, tachometer.c)
* **First order IIR low pass filter**: Smooths RPM measurement (low_pass_filter.h, low_pass_filter.c)
* **PID controller**: Computes duty cycle command from target vs. measured RPM (pid_controller.h, pid_controller.c)
* **Fan speed controller**: Applies PWM duty cycle to MOSFET (fan_speed_controller.h, fan_speed_controller.c)
* **Application loop**: Handles control functions at 10 Hz, heartbeat at 1Hz, logging at 0.5Hz

```
  while (1)
  {
    /**************************** CONTROL LOOP (10 Hz) ****************** */
    tachometer_update_rpm(&fan_tachometer, HAL_GetTick());
    low_pass_filter_update(&rpm_filter, fan_tachometer.current_rpm, HAL_GetTick());
    uint8_t command = pid_controller_step(&pid, (uint32_t)rpm_filter.last_sample, RPM_SETPOINT, HAL_GetTick());
    if(command != PID_NO_UPDATE)
    {
      fan_set_rpm_percent(&fan_controller, command);
    }
    /******************************************************************** */

    /************************** HEARTBEAT LED & PERIODIC UART MESSAGES ****** */
    heartbeat_toggle(&heartbeat_led, HAL_GetTick());
    logging_send_periodic_msg(HAL_GetTick(), "Fan RPM: %d \n", fan_tachometer.current_rpm);
    /************************************************************************ */
  }
```

## System performances

After tuning PID controller and testing various setpoints, we have reached the following system response.

For 5000 RPM:
<img width="1418" height="967" alt="image" src="https://github.com/user-attachments/assets/3f5d046e-d461-4484-86d1-4624208999de" />
For 8000 RPM:
<img width="1418" height="967" alt="image" src="https://github.com/user-attachments/assets/c1732cab-7195-4d30-a55f-2c220508482c" />
It's possible to achieve better performances, but for the sake of this project and for my use-case, this is satisfying enough.
The plots were generated with MCUViewer, which enables live capture of global variables with static addresses through SWD/JTAG.

<img width="1536" height="2048" alt="image" src="https://github.com/user-attachments/assets/0d3eb95d-85ed-4847-89f6-c3a6c4e538b4" />

## Building

To build the code, it is enough to run "make" in the "Software" directory. Assuming arm-none-eabi-gcc is correctly installed and configured for $PATH.
KiCAD Files are provided in Hardware/, and JLCPCB production files in Hardware/Production.




