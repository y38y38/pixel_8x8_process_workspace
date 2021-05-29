/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"

#define 	MY_IP_ADDRESS	(0xa0010000)
#define 	RAM_ADDRESSS (0xa0000000)
//#define   WAIT_TIME (0)
#define   WAIT_TIME (20)


#define SRC_OFFSET_ADDRESS (0x0)
#define DST_OFFSET_ADDRESS (0x80)

int main()
{
    init_platform();

    print("Hello World\n\r");
    for(int i=0;i<WAIT_TIME;i++)  {
        xil_printf("Hello World %d\n\r",i);
        sleep(1);

    }

    uint32_t *ptr = RAM_ADDRESSS;
    for(int i=0;i<0x20;i++) {

        *(ptr+i) = (i*2) |  (((i*2)+1)<<16);
    }
    for (int i=0;i<0x40;i++) {
        xil_printf("ram = %08x %08x\r\n", (ptr+i), *(ptr+i));
//        ptr++;
    }
 //   ptr = (RAM_ADDRESSS + 0x40);
 //   xil_printf("ram = %x %x\r\n", ptr, *ptr);
//    return 0;

    uint32_t *controller = MY_IP_ADDRESS;
    *(controller + 1) = SRC_OFFSET_ADDRESS;
    *(controller + 2) = DST_OFFSET_ADDRESS;
    *controller = 0x1;
    sleep(1);
    xil_printf("controller = %x %x\r\n", controller, *controller);
    xil_printf("status = %x %x\r\n", (controller+3), *(controller+3));
    xil_printf("status = %x %x\r\n", (controller+4), *(controller+4));

    ptr = (RAM_ADDRESSS);
//    xil_printf("ram = %x %x\r\n", ptr, *ptr);
//    ptr = RAM_ADDRESSS;
//    xil_printf("ram = %x %x\r\n", ptr, *ptr);

    for (int i=0;i<0x40;i++) {
        xil_printf("ram = %08x %08x\r\n", (ptr+i), *(ptr+i));
//        ptr++;
    }

    print("Successfully ran Hello World application");
    cleanup_platform();
    return 0;
}
