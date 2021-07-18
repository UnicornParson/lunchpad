//#define ENABLE_SERIAL_LOGGING 1
#define LOG_CODE_POINTS 1
#define PERF_WARNINGS 1

const u32 SerialSpeed = 115200;
const int EventsQueueSize = 16;
const int EventDataSize = 8;
const u32 LoopTimeWarningLimit = 10; // ms
using u32 = uint32_t;
using S = String;

#ifdef LOG_CODE_POINTS
#define DBG_LEGEND (S("(in ") + S(__FUNCTION__) + S(".") + S(__LINE__) + S(") "))
#else
#define DBG_LEGEND (S())
#endif

enum DPin : u32
{
  D2 = 2,
  D3 = 3,
  D4 = 4,
  D5 = 5,
  D6 = 6,
  D7 = 7,
  D8 = 8,
  D9 = 9,
  D10 = 10,
  D11 = 11,
  D12 = 12,
  D13 = 13
};


//--------------[ SERIAL API ]--------------
const char ApiEventPrefix = '@';
const char ApiDebugPrefix = '#';
const char ApiSysInfoPrefix = ':';
inline void sendEvent(const char* payload)
{
  Serial.print(ApiEventPrefix);
  Serial.println(payload);
}
inline void debug(const char* message)
{
  Serial.print(ApiDebugPrefix);
  Serial.println(message);
}
inline void debugS(const String& str)
{
  static const u32 bufsize = 256;
  char buf[bufsize];
  str.toCharArray(buf, bufsize - 1);
  Serial.print(ApiDebugPrefix);
  Serial.println(buf);
}
//--------------[ SERIAL API ]--------------


struct btnInfo_t
{
  u32 ioIndex = 0; // btn name (for api)
  u32 pinIndex = 0; // board pin
  u32 bounceTimer = 0;
  bool bounceFlag = false;
};

const u32 btnPins[] = {D2, D3, D4, D5, D6, D7, D8, D9, D10, D11, D12};
const u32 btnsCount = sizeof(btnPins) / sizeof(u32);
char Events[EventsQueueSize][EventDataSize] = {0};
int EventsCursor = 0;
btnInfo_t btns[btnsCount];

void setup()
{
  Serial.begin(SerialSpeed);
#ifdef ENABLE_SERIAL_LOGGING
  debugS(DBG_LEGEND + S("buttons count:") + S(btnsCount));
  S mappingStr("buttons mapping: ");
#endif
  for (u32 i = 0; i < btnsCount; ++i)
  {
    btns[i].ioIndex = i;
    btns[i].pinIndex = btnPins[i];
#ifdef ENABLE_SERIAL_LOGGING
    mappingStr += S("(") +  S(i) + S(" => pin") + S(btns[i].pinIndex) + S(") ");
#endif
    pinMode(btns[i].pinIndex, INPUT_PULLUP);
  }
  EventsCursor = 0;
#ifdef ENABLE_SERIAL_LOGGING
  debugS(DBG_LEGEND + mappingStr);
  debugS(DBG_LEGEND + S("ready"));
#endif
}



void sendQueue()
{
  for (int i = 0; i < EventsQueueSize; ++i)
  {
    if (Events[i][0] != 0)
    {
      sendEvent((char*)Events[i]);
    }
  }
  EventsCursor = 0;
  for (int i = 0; i < EventsQueueSize; ++i)
  {
    for (int j = 0; j < EventDataSize; ++j)
    {
      Events[i][j] = char(0);
    }
  }
}

void stashEvent(char code, int data)
{
  if (EventsCursor >= EventsQueueSize)
  {
    debugS(DBG_LEGEND + S("EventsQueue full!") + S(EventsCursor) + S("/") + S(EventsQueueSize) + S(" ignore event"));
    return;
  }
  const int bufSize = 8;
  Events[EventsCursor][0] = code;
  itoa(data, &Events[EventsCursor][1], DEC);
  for (int i = strlen(Events[EventsCursor]); i < bufSize; ++i)
  {
    Events[EventsCursor][i] = char(0);
  }
  Events[EventsCursor][bufSize - 1] = 0;
#ifdef ENABLE_SERIAL_LOGGING
  debugS(DBG_LEGEND + Events[EventsCursor]);
#endif
  ++EventsCursor;
}

void processBtn(int i)
{
  int btnState = 1 - digitalRead(btns[i].pinIndex);
  if (btnState && !btns[i].bounceFlag && ((millis() - btns[i].bounceTimer) > 50))
  {
    btns[i].bounceFlag = true;
    btns[i].bounceTimer = millis();
    stashEvent('p', btns[i].ioIndex);
  }
  if (btnState && btns[i].bounceFlag && ((millis() - btns[i].bounceTimer) > 200))
  {
    btns[i].bounceTimer = millis();
    stashEvent('h', btns[i].ioIndex);
  }
  if (!btnState && btns[i].bounceFlag && ((millis() - btns[i].bounceTimer) > 200))
  {
    btns[i].bounceFlag = false;
    btns[i].bounceTimer = millis();
    stashEvent('r', btns[i].ioIndex);
  }
}

void loop()
{
#ifdef PERF_WARNINGS
  u32 start = millis();
#endif
  for (int i = 0; i < btnsCount; ++i)
  {
    processBtn(i);
  }
  sendQueue();
#ifdef PERF_WARNINGS
  u32 delta = millis() - start;
  if (delta >= LoopTimeWarningLimit)
  {
    debugS(S("WARNING: loop time:") + S(delta));
  }
#endif
}
