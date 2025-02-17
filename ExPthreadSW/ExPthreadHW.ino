#define LC_INIT(lc)
struct pt { unsigned short lc; };
#define PT_THREAD(name_args)  char name_args
#define PT_BEGIN(pt)          switch(pt->lc) { case 0:
#define PT_WAIT_UNTIL(pt, c)  pt->lc = __LINE__; case __LINE__: \
                              if(!(c)) return 0
#define PT_END(pt)            } pt->lc = 0; return 2
#define PT_INIT(pt)   LC_INIT((pt)->lc)
#define PT_SLEEP(pt, delay) \
{ \
  do { \
    static unsigned long protothreads_sleep; \
    protothreads_sleep = millis(); \
    PT_WAIT_UNTIL(pt, millis() - protothreads_sleep > delay); \
  } while(false); \
}
#define PT_EXITED  2
#define PT_SCHEDULE(f) ((f) < PT_EXITED)
//-----------------------------------------------------------------------------------------------------------
// se si usa questa libreria al posto delle macro sopra, togliere il commento iniziale all'include 
// e commentare le macro sopra
//#include "protothreads.h"
#define PDELAY  500
#define LDELAY  1500
#define BLINKDELAY  300
byte led1 = 12;
byte led2 = 13;

void setup()
{
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  PT_INIT(&ptSos);
  PT_INIT(&ptBlink);
}
 

// definizione protothread del pulsante
pt ptSos;
int SOSThread(struct pt* pt) {
  PT_BEGIN(pt);

  // Loop del protothread
  while(true) {
  // 3 punti
  digitalWrite(led1, HIGH); // 1
  PT_SLEEP(pt, PDELAY);
  digitalWrite(led1, LOW);
  PT_SLEEP(pt, PDELAY);
  digitalWrite(led1, HIGH); // 2
  PT_SLEEP(pt, PDELAY);
  digitalWrite(led1, LOW);
  PT_SLEEP(pt, PDELAY);
  digitalWrite(led1, HIGH); // 3
  PT_SLEEP(pt, PDELAY);
  digitalWrite(led1, LOW);
  PT_SLEEP(pt, PDELAY);
  // 1 linea
  digitalWrite(led1, HIGH); // 1 linea
  PT_SLEEP(pt, LDELAY);
  digitalWrite(led1, LOW);
  PT_SLEEP(pt, PDELAY);
  // 3 punti
  digitalWrite(led1, HIGH); // 1
  PT_SLEEP(pt, PDELAY);
  digitalWrite(led1, LOW);
  PT_SLEEP(pt, PDELAY);
  digitalWrite(led1, HIGH); // 2
  PT_SLEEP(pt, PDELAY);
  digitalWrite(led1, LOW);
  PT_SLEEP(pt, PDELAY);
  digitalWrite(led1, HIGH); // 3
  PT_SLEEP(pt, PDELAY);
  digitalWrite(led1, LOW);
  PT_SLEEP(pt, LDELAY);
  }
  PT_END(pt);
}

// definizione protothread del lampeggio
pt ptBlink;
int blinkThread(struct pt* pt) {
  PT_BEGIN(pt);

  // Loop del protothread
  while(true) {
  digitalWrite(led2, HIGH);     // turn the LED on (HIGH is the voltage level)
  PT_SLEEP(pt, BLINKDELAY);
  digitalWrite(led2, LOW);      // turn the LED off by making the voltage LOW
  PT_SLEEP(pt, BLINKDELAY);
  }
  PT_END(pt);
}

// loop principale
void loop()
{
  PT_SCHEDULE(SOSThread(&ptSos));     // esecuzione schedulatore protothreads
  PT_SCHEDULE(blinkThread(&ptBlink));   // esecuzione schedulatore protothreads
}
