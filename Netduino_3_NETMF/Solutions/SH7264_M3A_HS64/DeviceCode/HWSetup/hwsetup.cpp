/***********************************************************************/
/*                                                                     */
/*  FILE        :hwsetup.cpp                                           */
/*  DATE        :Wed, Apr 22, 2009                                     */
/*  DESCRIPTION :Hardware Setup file                                   */
/*  CPU TYPE    :SH7264                                                */
/*                                                                     */
/*  This file is generated by Renesas Project Generator (Ver.4.9).     */
/*                                                                     */
/***********************************************************************/                 

#include <machine.h>
#include <tinyhal.h>

#ifdef __cplusplus
extern "C" {
#endif
extern void HardwareSetup(void);
#ifdef __cplusplus
}
#endif

#pragma section ResetPRG

#define SDRAM_MODE      (*(volatile unsigned short *)(0xfffc5040))

void HardwareSetup(void)
{
    volatile int j = 133;                   /* 200usec wait count   */
    long addr;
    /*====CPG setting====*/ 
    CPG.FRQCR.WORD = 0x1003;

    /* ---- The clock of all modules is permitted. ---- */
    CPG.STBCR3.BYTE = 0x02; 
                            
    CPG.STBCR4.BYTE = 0x00; 
    CPG.STBCR5.BYTE = 0x10; 
    CPG.STBCR6.BYTE = 0x02; 
    CPG.STBCR7.BYTE = 0x2a; 
    CPG.STBCR8.BYTE = 0x7e;     
    
    /*====CS0 initialization====*/  
        
	/* ==== PFC settings ==== */
	//PORT.PBCR5.BIT.PB21MD  = 1u;	/* Set A21 	*/
	//PORT.PBCR5.BIT.PB20MD  = 1u;	/* Set A20 	*/
	
	PORT.PDCR0.WORD = 0x1111;
	PORT.PDCR1.WORD = 0x1111;
	PORT.PDCR2.WORD = 0x1111;
	PORT.PDCR3.WORD = 0x1111;
	
	PORT.PBCR0.WORD = 0x1110;
	PORT.PBCR1.WORD = 0x1111;
	PORT.PBCR2.WORD = 0x1111;
	PORT.PBCR3.WORD = 0x1111;
	PORT.PBCR4.WORD = 0x1111;
	PORT.PBCR5.WORD = 0x0111;
	
	PORT.PCCR0.BIT.PC3MD   = 1u;	/* Set WE0# */
    /* ==== CS0WCR settings ====  */
    BSC.CS0WCR.NORMAL.LONG = 0x00000b41ul;
                                    /* Number of Delay Cycles from Adress,      */
                                    /*  CS0# Assertion to RD#,WEn Assertion     */
                                    /*  :1.5cycles                              */
                                    /* Number of Access Wait Cycles:6cycles     */
                                    /* Delay Cycles from RD,WEn# negation to    */
                                    /*  Address,CSn# negation:1.5cycles         */


    /* ==== CS0BCR settings ==== */
    BSC.CS0BCR.LONG = 0x10000400ul;
                                    /* Idle Cycles between Write-read Cycles    */
                                    /*  and Write-write Cycles :1idle cycles    */
                                    /* Data Bus Size:16-bit size                */
    
    /*====SDRAM area initialization====*/
    /* ==== PFC settings ==== */
    PORT.PCCR2.BIT.PC8MD = 1u;              /* CS3#     */
    PORT.PCCR1.BIT.PC7MD = 1u;              /* CKE      */
    PORT.PCCR1.BIT.PC6MD = 1u;              /* CAS#     */
    PORT.PCCR1.BIT.PC5MD = 1u;              /* RAS#     */
    PORT.PCCR1.BIT.PC4MD = 1u;              /* DQMU#    */
    PORT.PCCR0.BIT.PC3MD = 1u;              /* DQML#    */
    PORT.PCCR0.BIT.PC2MD = 1u;              /* RD/WR#   */

    /* ==== 200us interval elapsed ? ==== */
    while(j-- > 0){
        /* wait */
    }

    /* ==== CS3BCR settings ==== */
    BSC.CS3BCR.LONG = 0x00004400ul;
                                        /*
                                            Idle Cycles between Write-read Cycles
                                            and Write-write Cycles :0idle cycle
                                            Memory type :SDRAM
                                            Data Bus Size :16-bit size
                                        */

    /* ==== CS3WCR settings ==== */
    BSC.CS3WCR.SDRAM.LONG = 0x0000288aul;
                                        /*
                                            Precharge completion wait cycles:1cycle
                                            Wait cycles between ACTV command
                                            and READ(A)/WRITE(A) command :2cycle
                                            CAS latency for Area 3 :2cycles
                                            Auto-precharge startup wait cycles :1cycle
                                            Idle cycles from REF command/self-refresh
                                            Release to ACTV/REF/MRS command 
                                            :5cycles
                                        */


    /* ==== SDCR settings ==== */
    BSC.SDCR.LONG = 0x00000809ul;
                                        /* 
                                            Refresh Control :Refresh 
                                            RMODE :Auto-refresh is performed 
                                            BACTV :Auto-precharge mode 
                                            Row address for Area3 :12-bits 
                                            Column Address for Area3 :9-bits 
                                        */

    /* ==== RTCOR settings ==== */
    BSC.RTCOR = 0xa55a0046ul;           /* 
                                            15.625us/222ns 
                                            = 70(0x46)cycles per refresh 
                                        */          




    /* ==== RTCSR settings ==== */
    BSC.RTCSR.LONG = 0xa55a0010ul;  
                                        /* 
                                            Initialization sequence start
                                            Clock select B-phy/16
                                            Refresh count :Once 
                                        */

    /* ==== Pin function controller (PFC�j setting ==== */
    PORT.PJCR0.WORD = 0x0044;   

    /* WDT setting */
    WDT.WTCSR.WORD = 0xA502;
    
    /* Cache setting */
    CCNT.CCR1.LONG = 0x00000909;

    /* ==== Written in SDRAM Mode Register ==== */
    (*(volatile unsigned short *)(0xfffc5040)) = 0; 

    /*  RAM clear from 0c000000 to 0c0fffff */
    for (addr = 0x2C000000; addr<0x2C100000; addr+=4) (*(volatile long *)addr) = 0x00000000;
}
