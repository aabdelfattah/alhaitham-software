#include "isp1362_includes.h"
#include "Usb.h"
#include <altera_avalon_mailbox.h>
#include <altera_avalon_mailbox_regs.h>

#ifdef DEBUG_USB_ISR
    #define USB_ISR_DEBUG(x)    DEBUG(x)  
#else
    #define USB_ISR_DEBUG(x)
#endif

// ************************************************************************
//  Public static data
// ************************************************************************

extern D13FLAGS bD13flags;
extern USBCHECK_DEVICE_STATES bUSBCheck_Device_State;
extern CONTROL_XFER ControlData;
extern alt_mailbox_dev* recv_dev;

char counter = 0;
int sendingflag = 0;

report_t report2 =
{
	0x00,
	100,
	100,
	0
};
report_t reportBuffer[2];
void reconnect_USB(void);



// ************************************************************************
//  ISR Subroutine
// ************************************************************************
void fn_usb_isr(void)
{
    disable();
    Hal4D13_LockDevice(0);
  enable();
}

void usb_isr(void)
{
    ULONG   i_st;
    //IOWR(PIO_SEG7_B_BASE,0, 0xAAAAAAAA);
    disable();
    Hal4D13_LockDevice(0);
    bD13flags.bits.At_IRQL1 = 1;

    i_st = Hal4D13_ReadInterruptRegister();
 
    if(i_st != 0) 
    {
        //IOWR_ALTERA_AVALON_PIO_DATA(PIO_SEG7_A_BASE, i_st);
        //USB_ISR_DEBUG(("[ISR]i_st=%lX\r\n", i_st));
        if(i_st & D13REG_INTSRC_BUSRESET){  // 0x01
            USB_ISR_DEBUG(("[USB ISR] Bus Reset\r\n"));
            Isr_BusReset();
        }else if(i_st & D13REG_INTSRC_SUSPEND){  // 0x04
            USB_ISR_DEBUG(("[USB ISR] Suspend\r\n"));
            Isr_SuspendChange();
        }else if(i_st & D13REG_INTSRC_EOT){
            USB_ISR_DEBUG(("[USB ISR] EOT (End of Tx)\r\n"));
            Isr_DmaEot();
        }else if(i_st & (D13REG_INTSRC_SOF|D13REG_INTSRC_PSEUDO_SOF)){
            USB_ISR_DEBUG(("[USB ISR] SOF (start of frame)\r\n"));
            Isr_SOF();
        }else if(i_st & D13REG_INTSRC_SHORT_PACKET){
            USB_ISR_DEBUG(("[USB ISR] short packet\r\n"));
            Isr_SHORT_PACKET();
        }else if(i_st & D13REG_INTSRC_RESUME){
            USB_ISR_DEBUG(("[USB ISR] resume\n"));
            Hal4D13_LockDevice(0);
        }
        else 
        {
            USB_ISR_DEBUG(("[USB ISR] other, i_st = %lXh....resume\n", i_st));
            if(i_st & D13REG_INTSRC_EP0OUT)  
                Isr_Ep00RxDone();
            if(i_st & D13REG_INTSRC_EP0IN)
                Isr_Ep00TxDone();
            if(i_st & D13REG_INTSRC_EP01)
                Isr_Ep01Done();
            if(i_st & D13REG_INTSRC_EP02)
                Isr_Ep02Done();        
            if(i_st & D13REG_INTSRC_EP03)
                Isr_Ep03Done();
            if(i_st & D13REG_INTSRC_EP04)
                Isr_Ep04Done();
            if(i_st & D13REG_INTSRC_EP05)
                Isr_Ep05Done();
            if(i_st & D13REG_INTSRC_EP06)
                Isr_Ep06Done();
        }
    }

    enable();
    bD13flags.bits.At_IRQL1 = 0;
}

void Isr_BusReset(void)
{
    USB_ISR_DEBUG(("BUS RESET\r\n"));
    reconnect_USB();
  
    bD13flags.bits.DCP_state = 0x00;
    bD13flags.bits.dma_disable=0x00;

    bUSBCheck_Device_State.State_bits.DEVICE_DEFAULT_STATE = 1;
    bUSBCheck_Device_State.State_bits.DEVICE_ADDRESS_STATE = 0;
    bUSBCheck_Device_State.State_bits.DEVICE_CONFIGURATION_STATE = 0;
    config_endpoint();
}

void Isr_SuspendChange(void)
{

    bD13flags.bits.suspend=1;
/* richard ???    
        disable();
        bD13flags.bits.suspend= 0;
        enable();
*/        
}

void Isr_SHORT_PACKET(void)
{
    USB_ISR_DEBUG(("SHORT PACKET INTERRUPT\r\n"));
}

void Isr_DmaEot(void)
{
    bD13flags.bits.dma_disable =0;

    if(bD13flags.bits.dma_state == DMA_PENDING)
        bD13flags.bits.setup_dma = 1;
    else
        bD13flags.bits.dma_state = DMA_IDLE;
    USB_ISR_DEBUG(("EOT reached!!!\r\n"));
    if(bD13flags.bits.verbose==1)
        USB_ISR_DEBUG(("dma_counter = %x\r\n", Hal4D13_GetDMACounter()));
    USB_ISR_DEBUG(("\r\n"));       
}


void Isr_SOF(void)
{

}

void Isr_Ep00RxDone(void)
{
    UCHAR       ep_last, i;
    USB_ISR_DEBUG(("RX %d\r\n",bUSBCheck_Device_State.State_bits.FOUR_RESERVED_BITS++));
    ep_last = Hal4D13_GetEndpointStatusWInteruptClear(EPINDEX4EP0_CONTROL_OUT); /* Clear interrupt flag */

    if (ep_last & D13REG_EPSTS_SETUP)
    {
        if(bD13flags.bits.DCP_state == USBFSM4DCP_REQUESTPROC)
        {
            //printf("entering 1 if\n");
            ControlData.Abort = 1;
            bD13flags.bits.DCP_state = USBFSM4DCP_SETUPPROC;
        }
        else
        {
            //printf("entering 1 else\n");
            bD13flags.bits.DCP_state = USBFSM4DCP_SETUPPROC;
        }
    }
    else /* not a setup packet, just a Data Out Packet */
    {
        switch (bD13flags.bits.DCP_state)
        {
        case USBFSM4DCP_DATAOUT:

            i = Hal4D13_ReadEndpoint(EPINDEX4EP0_CONTROL_OUT, ControlData.dataBuffer + ControlData.wCount,
                EP0_PACKET_SIZE);
            //printf("entering else and data out\n");
            ControlData.wCount += i;
            if( i != EP0_PACKET_SIZE || ControlData.wCount >= ControlData.wLength)
            {
                //printf("entering else and data out if\n");
                bD13flags.bits.DCP_state = USBFSM4DCP_REQUESTPROC;

            }
            break;
        case USBFSM4DCP_HANDSHAKE:
            
            //printf("entering else and hs\n");
            bD13flags.bits.DCP_state = USBFSM4DCP_IDLE;
            break;

        case USBFSM4DCP_STALL:      break;

        case USBFSM4DCP_SETUPPROC:  break;

        case USBFSM4DCP_REQUESTPROC:break;

        case USBFSM4DCP_DATAIN:     break;

        default:
            USB_ISR_DEBUG(("Fatal Error: Isr_Ep0RxDone ReadLastTranactionStatus=%x\r\n",ep_last));
            bD13flags.bits.DCP_state = USBFSM4DCP_STALL;
            Hal4D13_StallEP0InControlWrite();
            break;
        }
    }
    return ;
}

void Isr_Ep00TxDone(void)
{
    short i = ControlData.wLength - ControlData.wCount;
    //printf("\n wLength = %d and wCount = %d",ControlData.wLength,ControlData.wCount);
    UCHAR ep_last;
    Hal4D13_ReadInterruptRegister();
    ep_last = Hal4D13_GetEndpointStatusWInteruptClear(EPINDEX4EP0_CONTROL_IN); /* Clear interrupt flag */
    //printf("Isr_Ep00TxDone\n");
    //printf("**i==%d**\n",i);
    switch (bD13flags.bits.DCP_state)
    {
    case USBFSM4DCP_HANDSHAKE:
        //printf("Isr_Ep00TxDone HS\n");
        break;
    case USBFSM4DCP_DATAIN:
        
        //printf("Isr_Ep00TxDone DI\n");
        if( i >= EP0_PACKET_SIZE)
        {
            //printf("Isr_Ep00TxDone DI 1 IF\n");
            Hal4D13_WriteEndpoint(EPINDEX4EP0_CONTROL_IN,ControlData.Addr.pData + ControlData.wCount, EP0_PACKET_SIZE);
            ControlData.wCount += EP0_PACKET_SIZE;
            // State remains at USBFSM4DCP_DATAIN
        }
        else if( i != 0)
        {
            //printf("Isr_Ep00TxDone DI else if 1\n");
            Hal4D13_WriteEndpoint(1, ControlData.Addr.pData + ControlData.wCount, i);
            ControlData.wCount += i;
            bD13flags.bits.DCP_state = USBFSM4DCP_HANDSHAKE;
        }
        else if (i == 0)
        {
            //printf("Isr_Ep00TxDone DI else if 2 \n");
            bD13flags.bits.DCP_state = USBFSM4DCP_HANDSHAKE;
      Hal4D13_SingleTransmitEP0(0, 0);
        }
        break;
    case USBFSM4DCP_REQUESTPROC://printf("Isr_Ep00TxDone R\n"); break;
    case USBFSM4DCP_IDLE:       //printf("Isr_Ep00TxDone I\n");break;
    case USBFSM4DCP_SETUPPROC:  //printf("Isr_Ep00TxDone S\n");break;
    case USBFSM4DCP_STALL:      //printf("Isr_Ep00TxDone Stall\n");break;
    case USBFSM4DCP_DATAOUT:    //printf("Isr_Ep00TxDone DO\n");break;
    default:
        USB_ISR_DEBUG(("Fatal Error: Isr_Ep0TxDone Unexpected FSMState=%x\r\n",bD13flags.bits.DCP_state));
        bD13flags.bits.DCP_state = USBFSM4DCP_STALL;
        Hal4D13_StallEP0InControlRead();
        break;
    }
}


void Isr_Ep01Done(void)
{
    printf("EP01\n");
    static USHORT i;
    static CHAR rbuff1[4]={0x00,0x00,0x00,0x00};
    UCHAR  c;
    static alt_u32 report;
    static alt_u32 r_message=0;
    static int err;

    //printf("hello USB ISR \n ");
    report=0;
	c = Hal4D13_GetEndpointStatusWInteruptClear(EPINDEX4EP01);
	report = altera_avalon_mailbox_get(recv_dev,&err);
	  		 printf("\t Report=%d\n\r",report);
	  		 if(report==0)
	  		 {
	  			 rbuff1[0]=0;
	  	 	     rbuff1[1]=0;
	    		 rbuff1[2]=0;

	  		 }
	  		 else
	  		 {
    		 rbuff1[0]=(report&0x000000FF);
    		 rbuff1[1]=((report&0x0000FF00)>>8)-127;

    		 rbuff1[2]=((report&0x00FF0000)>>16)-127;

	  		 }
    		 printf("\n*****%d %d %d****\n",rbuff1[0],rbuff1[1],rbuff1[2]);
    		 i=Hal4D13_WriteEndpoint(EPINDEX4EP01,(PUCHAR)&rbuff1,4);



}


void Isr_Ep02Done(void)
{
  unsigned char bbuf[8];
    USB_ISR_DEBUG(("Received From Endpoint 2\r\n")); 
  bbuf[0]=0x99;
    Hal4D13_GetEndpointStatusWInteruptClear(EPINDEX4EP02); 
}


void Isr_Ep03Done(void)
{
  UCHAR       ep_last;
  ep_last = Hal4D13_GetEndpointStatusWInteruptClear(EPINDEX4EP03); /* Clear interrupt flag*/
}


void Isr_Ep04Done(void)
{
  UCHAR       ep_last;
  ep_last = Hal4D13_GetEndpointStatusWInteruptClear(EPINDEX4EP04); /* Clear interrupt flag*/
}

void Isr_Ep05Done(void)
{
  
    UCHAR   ep_last, DoubleBuff=1;
    USHORT  ISO_Buffer[512], len;
    ep_last = Hal4D13_GetEndpointStatusWInteruptClear(EPINDEX4EP05); // Clear interrupt flag
    if((ep_last & (D13REG_EPSTS_DBF0|D13REG_EPSTS_DBF1)) == 0x00)
        DoubleBuff = 2;
    else
        DoubleBuff = 1;
    if (ep_last | D13REG_EPSTS_DBF0|D13REG_EPSTS_DBF1)
        return ;
    else //Data Out Packet
    {
        if((ep_last & 0x60) != 0x00)
        {
           if(DoubleBuff == 2)
           {
                while(DoubleBuff)
                {
                    len = Hal4D13_ReadISOEndpoint(EPINDEX4EP05, ISO_Buffer, 512);
                    Hal4D13_WriteISOEndpoint(EPINDEX4EP06, ISO_Buffer, len);
                    DoubleBuff--;
                    ep_last = Hal4D13_GetEndpointStatusWInteruptClear(EPINDEX4EP05); // Clear interrupt flag
                }
           }
           else
           {
                len = Hal4D13_ReadISOEndpoint(EPINDEX4EP05, ISO_Buffer, 512);
                Hal4D13_WriteISOEndpoint(EPINDEX4EP06, ISO_Buffer, len);
           }
        }
    }
   
}

void Isr_Ep06Done(void)
{
    UCHAR       ep_last;
    ep_last = Hal4D13_GetEndpointStatusWInteruptClear(EPINDEX4EP06); /* Clear interrupt flag*/
}

void Isr_Ep07Done(void)
{
//  UCHAR  c;
//  c = Hal4D13_GetEndpointStatusWInteruptClear(EPINDEX4EP07); /* Clear interrupt flag */
}
void Isr_Ep08Done(void)
{
//  UCHAR  c;
//  c = Hal4D13_GetEndpointStatusWInteruptClear(EPINDEX4EP08); /* Clear interrupt flag */
}
void Isr_Ep09Done(void)
{
//  UCHAR  c;
//  c = Hal4D13_GetEndpointStatusWInteruptClear(EPINDEX4EP09); /* Clear interrupt flag */
}
void Isr_Ep0ADone(void)
{
//  UCHAR  c;
//  c = Hal4D13_GetEndpointStatusWInteruptClear(EPINDEX4EP0A); /* Clear interrupt flag */
}
void Isr_Ep0BDone(void)
{
//  UCHAR  c;
//  c = Hal4D13_GetEndpointStatusWInteruptClear(EPINDEX4EP0B); /* Clear interrupt flag */
}
void Isr_Ep0CDone(void)
{
//  UCHAR  c;
//  c = Hal4D13_GetEndpointStatusWInteruptClear(EPINDEX4EP0C); /* Clear interrupt flag */
}
void Isr_Ep0DDone(void)
{
//  UCHAR  c;
//  c = Hal4D13_GetEndpointStatusWInteruptClear(EPINDEX4EP0D); /* Clear interrupt flag */
}
void Isr_Ep0EDone(void)
{
//  UCHAR  c;
//  c = Hal4D13_GetEndpointStatusWInteruptClear(EPINDEX4EP0E); /* Clear interrupt flag */
}

//*********************************************************************
// supporting Functions
//*********************************************************************



