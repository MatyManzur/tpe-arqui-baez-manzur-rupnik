#include <keyboard.h>


static kbEvent_t buffer[BUFFER_DIM];
static uint32_t readingIndex;
static uint32_t writingIndex;

static uint8_t shifted;

void keyboard_handler()
{
	static int specialKey;
	int scanCode = getScanCode();
	if(scanCode==0xE0)
	{
		specialKey = 1;
		return;
	}
	if(specialKey)
	{
		specialKey = 0;
		scanCode = -scanCode;
	}
	kbEvent_t kbEvent;
	if(scanCode > 0x80)
	{
		scanCode -= 0x80;
		kbEvent.action = RELEASED;
	}
	else if(scanCode < -0x80)
	{
		scanCode += 0x80;
		kbEvent.action = RELEASED;
	}
	else
	{
		kbEvent.action = PRESSED;
	}
	kbEvent.key = scanCode;
	buffer[(writingIndex++)%BUFFER_DIM] = kbEvent;
}

void readPrintables(char* bufferString, uint8_t count)
{
	cleanBuffer();
	int i=0;
	while(i<count)
	{
		if(readingIndex<writingIndex)
		{
			kbEvent_t kbEvent = buffer[(readingIndex++)%BUFFER_DIM];
			if(kbEvent.key==VK_LSHIFT || kbEvent.key==VK_RSHIFT)
			{
				shifted= !shifted;
				/*if(kbEvent.action==PRESSED)
					shifted = 1;
				else
					shifted = 0;
				*/
			}
			else if(kbEvent.key==VK_CAPITAL && kbEvent.action==PRESSED)
			{
				shifted = !shifted;
			}
			else if(kbEvent.key > 0 && kbEvent.action==PRESSED)
			{	
				char printableChar = printableKeys[shifted][kbEvent.key];
				if(printableChar!=0)
					bufferString[i++] = printableChar;
			}
		}
		else
		{
			_hlt();
		}
	}
}

void getNextKey(struct kbEvent_t* kbEvent)
{
	if(readingIndex==writingIndex) //No hay nada para leer
	{
		kbEvent->key=0;
		return;
	}
	kbEvent->key = buffer[(readingIndex)%BUFFER_DIM].key;
	kbEvent->action = buffer[(readingIndex)%BUFFER_DIM].action;
	readingIndex++;
}

void cleanBuffer()
{
	while(readingIndex < writingIndex)
	{
		kbEvent_t kbEvent = buffer[(readingIndex++)%BUFFER_DIM];
		if(kbEvent.key==VK_LSHIFT || kbEvent.key==VK_RSHIFT)
		{
			if(kbEvent.action==PRESSED)
				shifted = 1;
			else
				shifted = 0;
		}
		else if(kbEvent.key==VK_CAPITAL && kbEvent.action==PRESSED)
		{
			shifted = !shifted;
		}
	}
}
