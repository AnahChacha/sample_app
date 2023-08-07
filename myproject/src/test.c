#define HX_APP_VARIABLES
#undef HX_APP_VARIABLES

#ifdef HX_APP_VARIABLES
#define EXTERN
#else
#define EXTERN extern
#endif

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <ctype.h>
#include <stdarg.h>

#include "coredef.h"
#include "poslib.h"
#include "struct.h"

#include "../inc/logo_fonts.h"

const APP_MSG App_Msg = { "ICBC", "ICBC-BANK", "A0ICBC10", "VANSTONE", __DATE__ " " __TIME__, "", 0, 0, 0, "" };

int event_main(SET_EVENT_MSG *msg) { return 0; }

char PartionStrBufApp(char *dest, char *src, char len)
{
  char seat, block;

  seat = 0;
  do {
    if (*src == 0) { break; }
    if ((*src == 0x0a) || (*src == 0x0d)) {
      seat++;
      break;
    }
    // ����
    if (*src > 0x80) {
      block = 2;
    } else {
      block = 1;
    }
    if ((seat + block) > len) {
      break;
    } else {
      seat += block;
    }

    while (block) {
      *dest = *src;
      dest++;
      src++;
      block--;
    };
  } while (1);

  *dest = 0;
  return seat;
}

void DispWellcome(int Line, u8 IsRoll)
{
  u8 DispBuf[500], FirstDisp[500];
  int FirDispLen = 0;
  // char DisVer[]= "_F-POSC V3.24.01.2";
  static unsigned int DispOffset = 0;

  memset(DispBuf, 0, sizeof(DispBuf));
  memset(FirstDisp, 0, sizeof(FirstDisp));

  memset(FirstDisp, 0, sizeof(FirstDisp));
  strcpy_s((char *)FirstDisp, sizeof FirstDisp, "Welcome Use POS");
  //	strcpy((char*)FirstDisp, "Welcome Use POS");

  strcat_s((char *)FirstDisp, sizeof FirstDisp, "_F-POSC 3.36.01.4");
  //	strcat((char*)FirstDisp , "_F-POSC 3.36.01.4");

  memset(DispBuf, 0, sizeof(DispBuf));
  PartionStrBufApp((char *)DispBuf, (char *)&FirstDisp[DispOffset], 21);
  ScrDisp_Api(Line, 0, (char *)DispBuf, 0);

  if (!IsRoll) return;
  if (FirstDisp[DispOffset] & 0x80) {
    (DispOffset) += 2;
  } else {
    (DispOffset)++;
  }
  if (DispOffset >= strlen((char *)FirstDisp)) { DispOffset = 0; }
}

void IcbcLogo(unsigned char x, unsigned char y) { ScrDrLogoxyRam_Api(92, 24, x, y, ICBCLOGO); }

void DispMainFace(void)
{
  IcbcLogo(16, 0);
  DispPhoneIcon_Api(108, 3);
  ScrBrush_Api();
}

int WaitEvent(void)
{
  u8 Key;
  char Dispbuf[32];
  u32 TimerId;
  int Ret = 0;
  struct DATE_USER Dt;
  struct TIME_USER Tm, TmBak;
  static char gFaceTimeTemp[40];

  memset(Dispbuf, 0, sizeof(Dispbuf));
  memset(&TmBak, 0, sizeof(TmBak));

  PhoneHookEnable_Api();
  TimerId = TimerSet_Api();
  KBFlush_Api();

  while (1) {
    GetTime_Api(&Dt, &Tm);
    if (memcmp(&TmBak, &Tm, sizeof(TmBak)) != 0) {
      memcpy(&TmBak, &Tm, sizeof(TmBak));
      sprintf_s(Dispbuf, sizeof Dispbuf, "%04d/%02d/%02d", Dt.year, Dt.mon, Dt.day);
      //			sprintf(Dispbuf, "%04d/%02d/%02d", Dt.year, Dt.mon,
      // Dt.day);
      ScrClrLineRam_Api(LINE3, LINE4);
      ScrDispRam_Api(LINE3, 0, Dispbuf, FDISP | CDISP);
      memset(Dispbuf, 0, sizeof(Dispbuf));

      if (Dt.dow == 0) Dt.dow = 7;
      sprintf_s(Dispbuf, sizeof Dispbuf, "%d %02d:%02d:%02d", Dt.dow, Tm.hour, Tm.min, Tm.sec);
      //			sprintf(Dispbuf, "%d %02d:%02d:%02d", Dt.dow , Tm.hour,
      // Tm.min, Tm.sec);
      ScrDispRam_Api(LINE4, 0, Dispbuf, FDISP | CDISP);
      DispWellcome(LINE5, (u8)1);
      ScrBrush_Api();
    }

    Key = GetKey_Api();

    Key = TelephoneEvent_Api((int)Key);
    if (Key != 0) return Key;
  }

  return 0;
}

void InitSys(void) {}

int main(int argc, char *argv[])
{
  int Result = 0;

  SystemInit_Api(argc, argv);

  InitSys();

  MagClose_Api();

  Result = 1;

  while (1) {
    if (Result) { ScrClsRam_Api(); }
    DispMainFace();

    Result = WaitEvent();

    if (Result == 0xfe) continue;

    if (Result != 0) {
      switch (Result) {
      case ENTER:
        break;
      default:
        Result = 0;
        continue;
      }
    }
  }// end while(1)
}
