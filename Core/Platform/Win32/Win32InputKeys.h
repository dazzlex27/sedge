/* 
===========================================================================
WindowsKeys.h

Lists all key codes as declared by the Windows OS.
As of 12/27/2016 the engine supports all keyboard keys listed below and 9 mouse buttons.
No support for gamepads or any other input devices just yet.
===========================================================================
*/

#pragma once

namespace sedge
{
	#define S3_FREE_CURSOR_KEY S3_KEY_0 

	#define S3_KEY_LMB				0xB0
	#define S3_KEY_RMB				0xB1
	#define S3_KEY_MMB				0xB2
	#define S3_KEY_CANCEL			0xB3
	#define S3_KEY_MBUTTON			0xB4
	#define S3_KEY_XBUTTON1			0xB5
	#define S3_KEY_XBUTTON2			0xB6
	#define S3_KEY_MWUP				0xB7
	#define S3_KEY_MWDOWN			0xB8
	
	#define S3_KEY_BACK				0x08 // BACKSPACE
	#define S3_KEY_TAB				0x09
	
	#define S3_KEY_CLEAR			0x0C
	#define S3_KEY_RETURN			0x0D // ENTER.
	
	#define S3_KEY_LSHIFT			0xA0
	#define S3_KEY_RSHIFT			0xA1
	#define S3_KEY_LCONTROL			0xA2
	#define S3_KEY_RCONTROL			0xA3
	#define S3_KEY_LMENU			0xA4
	#define S3_KEY_RMENU			0xA5
	
	#define S3_KEY_CAPSLOCK			0x14 // CAPS_LOCK
	#define S3_KEY_ESCAPE			0x1B
	#define S3_KEY_SPACE			0x20
	#define S3_KEY_PAGEUP			0x21 // PAGE UP.
	#define S3_KEY_PAGEDOWN			0x22 // PAGE DOWN.
	#define S3_KEY_END				0x23
	#define S3_KEY_HOME				0x24
	
	#define S3_KEY_LEFT				0x25
	#define S3_KEY_UP				0x26
	#define S3_KEY_RIGHT			0x27
	#define S3_KEY_DOWN				0x28
	
	#define S3_KEY_SELECT			0x29
	#define S3_KEY_PRINT			0x2A
	#define S3_KEY_EXECUTE			0x2B
	#define S3_KEY_SNAPSHOT			0x2C
	#define S3_KEY_INSERT			0x2D
	#define S3_KEY_DELETE			0x2E
	#define S3_KEY_HELP				0x2F
	
	#define S3_KEY_0				0x30
	#define S3_KEY_1				0x31
	#define S3_KEY_2				0x32
	#define S3_KEY_3				0x33
	#define S3_KEY_4				0x34
	#define S3_KEY_5				0x35
	#define S3_KEY_6				0x36
	#define S3_KEY_7				0x37
	#define S3_KEY_8				0x38
	#define S3_KEY_9				0x39
	
	#define S3_KEY_A				0x41 
	#define S3_KEY_B				0x42
	#define S3_KEY_C				0x43
	#define S3_KEY_D				0x44
	#define S3_KEY_E				0x45
	#define S3_KEY_F				0x46 
	#define S3_KEY_G				0x47
	#define S3_KEY_H				0x48
	#define S3_KEY_I				0x49
	#define S3_KEY_J				0x4A
	#define S3_KEY_K				0x4B
	#define S3_KEY_L				0x4C 
	#define S3_KEY_M				0x4D
	#define S3_KEY_N				0x4E
	#define S3_KEY_O				0x4F
	#define S3_KEY_P				0x50
	#define S3_KEY_Q				0x51
	#define S3_KEY_R				0x52
	#define S3_KEY_S				0x53
	#define S3_KEY_T				0x54 
	#define S3_KEY_U				0x55
	#define S3_KEY_V				0x56
	#define S3_KEY_W				0x57
	#define S3_KEY_X				0x58
	#define S3_KEY_Y				0x59
	#define S3_KEY_Z				0x5A
	
	#define S3_KEY_NUMPAD0			0x60
	#define S3_KEY_NUMPAD1			0x61
	#define S3_KEY_NUMPAD2			0x62
	#define S3_KEY_NUMPAD3			0x63
	#define S3_KEY_NUMPAD4			0x64
	#define S3_KEY_NUMPAD5			0x65
	#define S3_KEY_NUMPAD6			0x66
	#define S3_KEY_NUMPAD7			0x67
	#define S3_KEY_NUMPAD8			0x68
	#define S3_KEY_NUMPAD9			0x69
	#define S3_KEY_MULTIPLY			0x6A
	#define S3_KEY_ADD				0x6B
	#define S3_KEY_SEPARATOR		0x6C
	#define S3_KEY_SUBTRACT			0x6D
	#define S3_KEY_DECIMAL			0x6E
	#define S3_KEY_DIVIDE			0x6F
	#define S3_KEY_F1				0x70
	#define S3_KEY_F2				0x71
	#define S3_KEY_F3				0x72
	#define S3_KEY_F4				0x73
	#define S3_KEY_F5				0x74
	#define S3_KEY_F6				0x75
	#define S3_KEY_F7				0x76
	#define S3_KEY_F8				0x77
	#define S3_KEY_F9				0x78
	#define S3_KEY_F10				0x79
	#define S3_KEY_F11				0x7A
	#define S3_KEY_F12				0x7B
	#define S3_KEY_F13				0x7C
	#define S3_KEY_F14				0x7D
	#define S3_KEY_F15				0x7E
	#define S3_KEY_F16				0x7F
	#define S3_KEY_F17				0x80
	#define S3_KEY_F18				0x81
	#define S3_KEY_F19				0x82
	#define S3_KEY_F20				0x83
	#define S3_KEY_F21				0x84
	#define S3_KEY_F22				0x85
	#define S3_KEY_F23				0x86
	#define S3_KEY_F24				0x87
	
	#define S3_KEY_NUMLOCK			0x90
	#define S3_KEY_SCROLLLOCK		0x91
	
	#define S3_KEY_EQUALS			0x92   // '=' key on numpad
}