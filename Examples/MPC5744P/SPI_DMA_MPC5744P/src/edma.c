/*
 * edma.c
 *
 *  Created on: Feb 23, 2016
 *      Author: B55457
 */

/* edma.c - DMA example TCD initialization */

#include "project.h"
#include "edma.h"

uint8_t TCD0_SourceData[] = {"Hello World\n"};
//#pragma alignvar (16)          /* Align for cache inhibit variable with SMPU */
uint8_t TCD0_Destination[13];
//#pragma alignvar (16)

uint8_t TCD1_SourceData[] = {0x1,0x0,0x1,0x0,0x1,0x0,0x1,0x0,0x1,0x0,0x1,0x0};

void initTCDs(void) {                 /* Transfer string to port pin output */

  DMA_0.TCD[0].SADDR.R = (vuint32_t) &TCD0_SourceData;  /* Load source address*/
  DMA_0.TCD[0].ATTR.B.SSIZE = 0;           /* Read 2**0 = 1 byte per transfer */
  DMA_0.TCD[0].ATTR.B.SMOD = 0;            /* Source modulo feature not used */
  DMA_0.TCD[0].SOFF.R = 1;                 /* After transfer add 1 to src addr*/
  DMA_0.TCD[0].SLAST.R = -12;              /* After major loop, reset src addr*/

  DMA_0.TCD[0].DADDR.R = (vuint32_t) &TCD0_Destination ; /* Load dest. address*/
  DMA_0.TCD[0].ATTR.B.DSIZE = 0;           /* Write 2**0 = 1 byte per transfer*/
  DMA_0.TCD[0].ATTR.B.DMOD = 0;            /* Dest. modulo feature not used */
  DMA_0.TCD[0].DOFF.R = 1;                 /* After transfer add 1 to dst addr*/
  DMA_0.TCD[0].DLASTSGA.R = 0;             /* After major loop no dest addr change*/

  DMA_0.TCD[0].NBYTES.MLNO.R = 1;          /* Transfer 1 byte per minor loop */
  DMA_0.TCD[0].BITER.ELINKNO.B.ELINK = 0;  /* No Enabling channel LINKing */
  DMA_0.TCD[0].BITER.ELINKNO.B.BITER = 13; /* 12 minor loop iterations */
  DMA_0.TCD[0].CITER.ELINKNO.B.ELINK = 0;  /* No Enabling channel LINKing */
  DMA_0.TCD[0].CITER.ELINKNO.B.CITER = 13; /* Init. current iteraction count */

  DMA_0.TCD[0].CSR.B.DREQ = 1;        /* Disable channel when major loop is done*/
  DMA_0.TCD[0].CSR.B.INTHALF = 0;     /* No interrupt when major count half complete */
  DMA_0.TCD[0].CSR.B.INTMAJOR = 0;    /* No interrupt when major count completes */
  DMA_0.TCD[0].CSR.B.MAJORELINK = 0;  /* Dynamic program is not used */
  DMA_0.TCD[0].CSR.B.MAJORLINKCH = 0; /* No link channel # used */
  DMA_0.TCD[0].CSR.B.ESG = 0;         /* Scatter Gather not Enabled */
  DMA_0.TCD[0].CSR.B.BWC = 0;         /* Default bandwidth control- no stalls */
  DMA_0.TCD[0].CSR.B.START = 0;       /* Initialize status flags START, DONE, ACTIVE */
  DMA_0.TCD[0].CSR.B.DONE = 0;
  DMA_0.TCD[0].CSR.B.ACTIVE = 0;


  DMA_0.TCD[1].SADDR.R = (vuint32_t) &TCD1_SourceData;  /* Load source address*/
  DMA_0.TCD[1].ATTR.B.SSIZE = 0;           /* Read 2**0 = 1 byte per transfer */
  DMA_0.TCD[1].ATTR.B.SMOD = 0;            /* Source modulo feature not used */
  DMA_0.TCD[1].SOFF.R = 1;                 /* After transfer add 1 to src addr*/
  DMA_0.TCD[1].SLAST.R = -12;              /* After major loop, reset src addr*/
  DMA_0.TCD[1].DADDR.R = (vuint32_t) &SIUL2.GPDO[PG2].R ; /* Dest. addr. port 98*/
  DMA_0.TCD[1].ATTR.B.DSIZE = 0;           /* Write 2**0 = 1 byte per transfer*/
  DMA_0.TCD[1].ATTR.B.DMOD = 0;            /* Dest. modulo feature not used */
  DMA_0.TCD[1].DOFF.R = 0;                 /* After transfer add 1 to dst addr*/
  DMA_0.TCD[1].DLASTSGA.R = 0;             /* After major loop no dest addr change*/

  DMA_0.TCD[1].NBYTES.MLNO.R = 1;          /* Transfer 1 byte per minor loop */
  DMA_0.TCD[1].BITER.ELINKNO.B.ELINK = 0;  /* No Enabling channel LINKing */
  DMA_0.TCD[1].BITER.ELINKNO.B.BITER = 12; /* 12 minor loop iterations */
  DMA_0.TCD[1].CITER.ELINKNO.B.ELINK = 0;  /* No Enabling channel LINKing */
  DMA_0.TCD[1].CITER.ELINKNO.B.CITER = 12; /* Init. current iteraction count */

  DMA_0.TCD[1].CSR.B.DREQ = 1;        /* Disable channel when major loop is done*/
  DMA_0.TCD[1].CSR.B.INTHALF = 0;     /* No interrupt when major count half complete */
  DMA_0.TCD[1].CSR.B.INTMAJOR = 0;    /* No interrupt when major count completes */
  DMA_0.TCD[1].CSR.B.MAJORELINK = 0;  /* Dynamic program is not used */
  DMA_0.TCD[1].CSR.B.MAJORLINKCH = 0; /* No link channel # used */
  DMA_0.TCD[1].CSR.B.ESG = 0;         /* Scatter Gather not Enabled */
  DMA_0.TCD[1].CSR.B.BWC = 0;         /* Default bandwidth control- no stalls */
  DMA_0.TCD[1].CSR.B.START = 0;       /* Initialize status flags START, DONE, ACTIVE */
  DMA_0.TCD[1].CSR.B.DONE = 0;
  DMA_0.TCD[1].CSR.B.ACTIVE = 0;
}

void init_edma_channel_arbitration (void) { /* Use default fixed arbitration */

  DMA_0.CR.R = 0x0000E400; /* Fixed priority arbitration for groups, channels */

  DMA_0.DCHPRI[0].R  = 0x00; /* Grp 0 chan 00, no suspension, no premption */
  DMA_0.DCHPRI[1].R  = 0x01; /* Grp 0 chan 01, no suspension, no premption */
  DMA_0.DCHPRI[2].R  = 0x02; /* Grp 0 chan 02, no suspension, no premption */
  DMA_0.DCHPRI[3].R  = 0x03; /* Grp 0 chan 03, no suspension, no premption */
  DMA_0.DCHPRI[4].R  = 0x04; /* Grp 0 chan 04, no suspension, no premption */
  DMA_0.DCHPRI[5].R  = 0x05; /* Grp 0 chan 05, no suspension, no premption */
  DMA_0.DCHPRI[6].R  = 0x06; /* Grp 0 chan 06, no suspension, no premption */
  DMA_0.DCHPRI[7].R  = 0x07; /* Grp 0 chan 07, no suspension, no premption */
  DMA_0.DCHPRI[8].R  = 0x08; /* Grp 0 chan 08, no suspension, no premption */
  DMA_0.DCHPRI[9].R  = 0x09; /* Grp 0 chan 09, no suspension, no premption */
  DMA_0.DCHPRI[10].R = 0x0A; /* Grp 0 chan 10, no suspension, no premption */
  DMA_0.DCHPRI[11].R = 0x0B; /* Grp 0 chan 11, no suspension, no premption */
  DMA_0.DCHPRI[12].R = 0x0C; /* Grp 0 chan 12, no suspension, no premption */
  DMA_0.DCHPRI[13].R = 0x0D; /* Grp 0 chan 13, no suspension, no premption */
  DMA_0.DCHPRI[14].R = 0x0E; /* Grp 0 chan 14, no suspension, no premption */
  DMA_0.DCHPRI[15].R = 0x0F; /* Grp 0 chan 15, no suspension, no premption */

  DMA_0.DCHPRI[16].R = 0x10; /* Grp 1 chan 00, no suspension, no premption */
  DMA_0.DCHPRI[17].R = 0x11; /* Grp 1 chan 01, no suspension, no premption */
  DMA_0.DCHPRI[18].R = 0x12; /* Grp 1 chan 02, no suspension, no premption */
  DMA_0.DCHPRI[19].R = 0x13; /* Grp 1 chan 03, no suspension, no premption */
  DMA_0.DCHPRI[20].R = 0x14; /* Grp 1 chan 04, no suspension, no premption */
  DMA_0.DCHPRI[21].R = 0x15; /* Grp 1 chan 05, no suspension, no premption */
  DMA_0.DCHPRI[22].R = 0x16; /* Grp 1 chan 06, no suspension, no premption */
  DMA_0.DCHPRI[23].R = 0x17; /* Grp 1 chan 07, no suspension, no premption */
  DMA_0.DCHPRI[24].R = 0x18; /* Grp 1 chan 08, no suspension, no premption */
  DMA_0.DCHPRI[25].R = 0x19; /* Grp 1 chan 09, no suspension, no premption */
  DMA_0.DCHPRI[26].R = 0x1A; /* Grp 1 chan 10, no suspension, no premption */
  DMA_0.DCHPRI[27].R = 0x1B; /* Grp 1 chan 11, no suspension, no premption */
  DMA_0.DCHPRI[28].R = 0x1C; /* Grp 1 chan 12, no suspension, no premption */
  DMA_0.DCHPRI[29].R = 0x1D; /* Grp 1 chan 13, no suspension, no premption */
  DMA_0.DCHPRI[30].R = 0x1E; /* Grp 1 chan 14, no suspension, no premption */
  DMA_0.DCHPRI[31].R = 0x1F; /* Grp 1 chan 15, no suspension, no premption */
}


/*****************************************************************************/

/* The transmit buffer includes data and the DSPI Command Word for each transfer */
/* In this example, we do not use continuous Chip Select */
/* In testing on the Freescale EVB it was found DSPI required at least 100ns between data */

const unsigned int TransmitBuffer[] =
{
  (  0 | 0x00010000), (  1 | 0x00010000), (  2 | 0x00010000), (  3 | 0x00010000),
  (  4 | 0x00010000), (  5 | 0x00010000), (  6 | 0x00010000), (  7 | 0x00010000),
  (  8 | 0x00010000), (  9 | 0x00010000), ( 10 | 0x00010000), ( 11 | 0x00010000),
  ( 12 | 0x00010000), ( 13 | 0x00010000), ( 14 | 0x00010000), ( 15 | 0x00010000),
  ( 16 | 0x00010000), ( 17 | 0x00010000), ( 18 | 0x00010000), ( 19 | 0x00010000),
  ( 20 | 0x00010000), ( 21 | 0x00010000), ( 22 | 0x00010000), ( 23 | 0x00010000),
  ( 24 | 0x00010000), ( 25 | 0x00010000), ( 26 | 0x00010000), ( 27 | 0x00010000),
  ( 28 | 0x00010000), ( 29 | 0x00010000), ( 30 | 0x00010000), ( 31 | 0x00010000),
  ( 32 | 0x00010000), ( 33 | 0x00010000), ( 34 | 0x00010000), ( 35 | 0x00010000),
  ( 36 | 0x00010000), ( 37 | 0x00010000), ( 38 | 0x00010000), ( 39 | 0x00010000),
  ( 40 | 0x00010000), ( 41 | 0x00010000), ( 42 | 0x00010000), ( 43 | 0x00010000),
  ( 44 | 0x00010000), ( 45 | 0x00010000), ( 46 | 0x00010000), ( 47 | 0x00010000),
  ( 48 | 0x00010000), ( 49 | 0x00010000), ( 50 | 0x00010000), ( 51 | 0x00010000),
  ( 52 | 0x00010000), ( 53 | 0x00010000), ( 54 | 0x00010000), ( 55 | 0x00010000),
  ( 56 | 0x00010000), ( 57 | 0x00010000), ( 58 | 0x00010000), ( 59 | 0x00010000),
  ( 60 | 0x00010000), ( 61 | 0x00010000), ( 62 | 0x00010000), ( 63 | 0x00010000),
  ( 64 | 0x00010000), ( 65 | 0x00010000), ( 66 | 0x00010000), ( 67 | 0x00010000),
  ( 68 | 0x00010000), ( 69 | 0x00010000), ( 70 | 0x00010000), ( 71 | 0x00010000),
  ( 72 | 0x00010000), ( 73 | 0x00010000), ( 74 | 0x00010000), ( 75 | 0x00010000),
  ( 76 | 0x00010000), ( 77 | 0x00010000), ( 78 | 0x00010000), ( 79 | 0x00010000),
  ( 80 | 0x00010000), ( 81 | 0x00010000), ( 82 | 0x00010000), ( 83 | 0x00010000),
  ( 84 | 0x00010000), ( 85 | 0x00010000), ( 86 | 0x00010000), ( 87 | 0x00010000),
  ( 88 | 0x00010000), ( 89 | 0x00010000), ( 90 | 0x00010000), ( 91 | 0x00010000),
  ( 92 | 0x00010000), ( 93 | 0x00010000), ( 94 | 0x00010000), ( 95 | 0x00010000),
  ( 96 | 0x00010000), ( 97 | 0x00010000), ( 98 | 0x00010000), ( 99 | 0x00010000),
  (100 | 0x00010000), (101 | 0x00010000), (102 | 0x00010000), (103 | 0x00010000),
  (104 | 0x00010000), (105 | 0x00010000), (106 | 0x00010000), (107 | 0x00010000),
  (108 | 0x00010000), (109 | 0x00010000), (110 | 0x00010000), (111 | 0x00010000),
  (112 | 0x00010000), (113 | 0x00010000), (114 | 0x00010000), (115 | 0x00010000),
  (116 | 0x00010000), (117 | 0x00010000), (118 | 0x00010000), (119 | 0x00010000),
  (120 | 0x00010000), (121 | 0x00010000), (122 | 0x00010000), (123 | 0x00010000),
  (124 | 0x00010000), (125 | 0x00010000), (126 | 0x00010000), (127 | 0x00010000),
  (128 | 0x00010000), (120 | 0x00010000), (130 | 0x00010000), (131 | 0x00010000),
  (132 | 0x00010000), (133 | 0x00010000), (134 | 0x00010000), (135 | 0x00010000),
  (136 | 0x00010000), (137 | 0x00010000), (138 | 0x00010000), (139 | 0x00010000),
  (140 | 0x00010000), (141 | 0x00010000), (142 | 0x00010000), (143 | 0x00010000),
  (144 | 0x00010000), (145 | 0x00010000), (146 | 0x00010000), (147 | 0x00010000),
  (148 | 0x00010000), (149 | 0x00010000), (150 | 0x00010000), (151 | 0x00010000),
  (152 | 0x00010000), (153 | 0x00010000), (154 | 0x00010000), (155 | 0x00010000),
  (156 | 0x00010000), (157 | 0x00010000), (158 | 0x00010000), (159 | 0x00010000),
  (160 | 0x00010000), (161 | 0x00010000), (162 | 0x00010000), (163 | 0x00010000),
  (154 | 0x00010000), (165 | 0x00010000), (166 | 0x00010000), (167 | 0x00010000),
  (168 | 0x00010000), (169 | 0x00010000), (170 | 0x00010000), (171 | 0x00010000),
  (172 | 0x00010000), (173 | 0x00010000), (174 | 0x00010000), (175 | 0x00010000),
  (176 | 0x00010000), (177 | 0x00010000), (178 | 0x00010000), (179 | 0x00010000),
  (180 | 0x00010000), (181 | 0x00010000), (182 | 0x00010000), (183 | 0x00010000),
  (184 | 0x00010000), (185 | 0x00010000), (186 | 0x00010000), (187 | 0x00010000),
  (188 | 0x00010000), (189 | 0x00010000), (190 | 0x00010000), (191 | 0x00010000),
  (192 | 0x00010000), (193 | 0x00010000), (194 | 0x00010000), (195 | 0x00010000),
  (196 | 0x00010000), (197 | 0x00010000), (198 | 0x00010000), (199 | 0x00010000),
  (200 | 0x00010000), (201 | 0x00010000), (201 | 0x00010000), (203 | 0x00010000),
  (204 | 0x00010000), (205 | 0x00010000), (206 | 0x00010000), (207 | 0x00010000),
  (208 | 0x00010000), (209 | 0x00010000), (210 | 0x00010000), (211 | 0x00010000),
  (212 | 0x00010000), (213 | 0x00010000), (214 | 0x00010000), (215 | 0x00010000),
  (216 | 0x00010000), (217 | 0x00010000), (218 | 0x00010000), (219 | 0x00010000),
  (220 | 0x00010000), (221 | 0x00010000), (222 | 0x00010000), (223 | 0x00010000),
  (224 | 0x00010000), (225 | 0x00010000), (226 | 0x00010000), (227 | 0x00010000),
  (228 | 0x00010000), (229 | 0x00010000), (230 | 0x00010000), (231 | 0x00010000),
  (232 | 0x00010000), (233 | 0x00010000), (234 | 0x00010000), (235 | 0x00010000),
  (236 | 0x00010000), (237 | 0x00010000), (238 | 0x00010000), (239 | 0x00010000),
  (240 | 0x00010000), (241 | 0x00010000), (242 | 0x00010000), (243 | 0x00010000),
  (244 | 0x00010000), (245 | 0x00010000), (246 | 0x00010000), (247 | 0x00010000),
  (248 | 0x00010000), (249 | 0x00010000), (250 | 0x00010000), (251 | 0x00010000),
  (252 | 0x00010000), (253 | 0x00010000), (254 | 0x00010000), (255 | 0x08010000)
};

unsigned char ReceiveBuffer[NUMBER_OF_BYTES];

/*****************************************************************************/

void init_dma_mux()
{
	DMAMUX_0.CHCFG[15].R = 0x82; /* DMA Chan 15 enbales DSPI_2 RX (src 2) */
	DMAMUX_1.CHCFG[0].R = 0x83; /* DMA Chan 16 enables DSPI_1 TX (src 3) */
}

/*****************************************************************************/

void init_edma_tcd_15()        /* This is for DSPI_2 Receive */
{
  /* SADDR Note: 1 byte is transferred in this TCD on each DMA request (minor loop). */
  /*     The byte is 4th one in the 32-bit POPR register. */
  /*     Therefore a +3 byte offset is added to POPR address for the source address SADDR */

  DMA_0.TCD[15].SADDR.R = ((unsigned int)&SPI_2.POPR.R) + 3; /* Load address of source data */
  DMA_0.TCD[15].ATTR.B.SSIZE = 0;            /* Read 2**0 = 1 byte per transfer */
  DMA_0.TCD[15].ATTR.B.SMOD = 0;             /* Source modulo feature not used  */
  DMA_0.TCD[15].SOFF.R = 0;                  /* After transfer, add 0 to src addr */
  DMA_0.TCD[15].SLAST.R = 0;                 /* No addr adjustment after major loops  */

  DMA_0.TCD[15].DADDR.R = (unsigned int)ReceiveBuffer;	/* Destination address */
  DMA_0.TCD[15].ATTR.B.DSIZE = 0;            /* Write 2**0 = 1 byte per transfer  */
  DMA_0.TCD[15].ATTR.B.DMOD = 0;             /* Destination modulo feature not used  */
  DMA_0.TCD[15].DOFF.R = 1;                  /* Increment destination addr by 1 */
             /* If repeating major loop, subtract NUMBER_OF_BYTES from dest. addr. */
  DMA_0.TCD[15].DLASTSGA.R = 0;              /* No addr adjustment after major loop */

             /* If repeating major loop, set this to 0 to keep the channel enabled */
  DMA_0.TCD[15].CSR.B.DREQ = 1;              /* Disable channel when major loop is done*/
  DMA_0.TCD[15].NBYTES.MLNO.R = 1;           /* NBYTES - Transfer 1 byte per minor loop */
  DMA_0.TCD[15].CITER.ELINKNO.B.ELINK = 0;   /* No Enabling channel LINKing */
  DMA_0.TCD[15].CITER.ELINKNO.B.CITER = NUMBER_OF_BYTES;  /* Init. current interaction count */
  DMA_0.TCD[15].BITER.ELINKNO.B.ELINK = 0;   /* No Enabling channel LINKing */
  DMA_0.TCD[15].BITER.ELINKNO.B.BITER = NUMBER_OF_BYTES;  /* Minor loop iterations */
  DMA_0.TCD[15].CSR.B.MAJORELINK = 0;        /* Dynamic program is not used */
  DMA_0.TCD[15].CSR.B.ESG = 0;               /* Scatter Gather not Enabled */
  DMA_0.TCD[15].CSR.B.BWC = 0;               /* Default bandwidth control- no stalls */
  DMA_0.TCD[15].CSR.B.INTHALF = 0;           /* No interrupt when major count half complete */
  DMA_0.TCD[15].CSR.B.INTMAJOR = 0;          /* No interrupt when major count completes */
  DMA_0.TCD[15].CSR.B.MAJORLINKCH = 0;       /* No link channel # used */
  DMA_0.TCD[15].CSR.B.START = 0;             /* Initialize status flags START, DONE, ACTIVE */
  DMA_0.TCD[15].CSR.B.DONE = 0;
  DMA_0.TCD[15].CSR.B.ACTIVE = 0;
}

/*****************************************************************************/

void init_edma_tcd_16()       /* This is for DSPI_1 Transmit */
{
//  DMA_0.TCD[16].SADDR.R = (unsigned int)&TransmitBuffer;     /* Source address */
//	DMA_0.TCD[16].SADDR.R = (unsigned int)&TransmitBuffer[0];
  DMA_0.TCD[16].SADDR.R = (unsigned int)TransmitBuffer;	/* Source address */
  DMA_0.TCD[16].ATTR.B.SSIZE = 2;             /* Read 2**2 = 4 bytes per transfer */
  DMA_0.TCD[16].ATTR.B.SMOD = 0;              /* Source modulo feature not used  */
  DMA_0.TCD[16].SOFF.R = 4;                   /* After transfer, add 4 to src addr */
  DMA_0.TCD[16].SLAST.R = 0;                  /* No addr adjustment after major loop  */

  DMA_0.TCD[16].DADDR.R = (unsigned int)&SPI_1.PUSHR.PUSHR.R; /* Destination address */
  DMA_0.TCD[16].ATTR.B.DSIZE = 2;             /* Write 2**0 = 1 byte per transfer  */
  DMA_0.TCD[16].ATTR.B.DMOD = 0;              /* Destination modulo feature not used  */
  DMA_0.TCD[16].DOFF.R = 0;                   /* No addr adjustment after major loop */
             /* If repeating major loop, subtract NUMBER_OF_BYTES from dest. addr. */
  DMA_0.TCD[16].DLASTSGA.R = 0;               /* After major loop, adjust the destination address */

             /* If repeating major loop, set this to 0 to keep the channel enabled */
  DMA_0.TCD[16].CSR.B.DREQ = 1;               /* Disable channel when major loop is done*/
  DMA_0.TCD[16].NBYTES.MLNO.R = 4;            /* NBYTES - Transfer 1 byte per minor loop */
  DMA_0.TCD[16].CITER.ELINKNO.B.ELINK = 0;    /* No Enabling channel LINKing */
  DMA_0.TCD[16].CITER.ELINKNO.B.CITER = NUMBER_OF_BYTES;     /* Init. current interaction count */
  DMA_0.TCD[16].BITER.ELINKNO.B.ELINK = 0;    /* No Enabling channel LINKing */
  DMA_0.TCD[16].BITER.ELINKNO.B.BITER = NUMBER_OF_BYTES;     /* Minor loop iterations */
  DMA_0.TCD[16].CSR.B.MAJORELINK = 0;         /* Dynamic program is not used */
  DMA_0.TCD[16].CSR.B.ESG = 0;                /* Scatter Gather not Enabled */
  DMA_0.TCD[16].CSR.B.BWC = 0;                /* Default bandwidth control- no stalls */
  DMA_0.TCD[16].CSR.B.INTHALF = 0;            /* No interrupt when major count half complete */
  DMA_0.TCD[16].CSR.B.INTMAJOR = 0;           /* No interrupt when major count completes */
  DMA_0.TCD[16].CSR.B.MAJORLINKCH = 0;        /* No link channel # used */
  DMA_0.TCD[16].CSR.B.START = 0;              /* Initialize status flags START, DONE, ACTIVE */
  DMA_0.TCD[16].CSR.B.DONE = 0;
  DMA_0.TCD[16].CSR.B.ACTIVE = 0;
}

