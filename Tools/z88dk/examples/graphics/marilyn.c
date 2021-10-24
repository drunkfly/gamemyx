
#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <gfxprofile.h>

        unsigned char marilyn[]={
			0x80,
			0x9B,	0x65,	0x77,
			0xAB,	0x64,	0x78,
			0xAB,	0x63,	0x7A,
			0xAB,	0x61,	0x7A,
			0xAB,	0x5B,	0x7C,
			0xAB,	0x4C,	0x7C,
			0xAB,	0x4A,	0x7B,
			0xAB,	0x48,	0x7B,
			0xAB,	0x47,	0x7A,
			0xAB,	0x46,	0x7A,
			0xAB,	0x45,	0x79,
			0xAB,	0x44,	0x78,
			0xAB,	0x44,	0x76,
			0xAB,	0x42,	0x76,
			0xAB,	0x42,	0x74,
			0xAB,	0x43,	0x73,
			0xAB,	0x44,	0x72,
			0xAB,	0x46,	0x71,
			0xAB,	0x47,	0x70,
			0xAB,	0x49,	0x6F,
			0xAB,	0x4B,	0x6D,
			0xAB,	0x4D,	0x6D,
			0xAB,	0x4E,	0x6C,
			0xAB,	0x5C,	0x6C,
			0xAB,	0x5E,	0x6D,
			0xAB,	0x60,	0x6D,
			0xAB,	0x61,	0x6F,
			0xAB,	0x63,	0x70,
			0xAB,	0x64,	0x71,
			0xAB,	0x65,	0x73,
			0xAB,	0x67,	0x75,
			0xAB,	0x68,	0x76,
			0xAB,	0x68,	0x77,
			0xAB,	0x62,	0x77,
			0xAB,	0x61,	0x76,
			0xAB,	0x5E,	0x76,
			0xAB,	0x5D,	0x75,
			0xAB,	0x58,	0x75,
			0xAB,	0x50,	0x76,
			0xAB,	0x4E,	0x75,
			0xAB,	0x48,	0x75,
			0xAB,	0x47,	0x76,
			0xAB,	0x44,	0x76,
			//0xF8,
			// Add a bit of border to lips
			0xFF,
// inner mouth border

			0x9B,	0x64,	0x79,
			0xAB,	0x61,	0x78,
			0xAB,	0x5D,	0x79,
			0xAB,	0x5C,	0x78,
			0xAB,	0x5B,	0x78,
			0xAB,	0x59,	0x79,
			0xAB,	0x50,	0x7A,
			0xAB,	0x50,	0x79,
			0xAB,	0x4F,	0x77,
			0xAB,	0x4E,	0x76,
			0xAB,	0x4B,	0x77,
			0xAB,	0x49,	0x76,
			0xAB,	0x44,	0x77,
			0xF4,

			0x9B,	0x5E,	0x76,
			0xAB,	0x5D,	0x74,
			0xAB,	0x5C,	0x73,
			0xAB,	0x5B,	0x73,
			0xAB,	0x5B,	0x74,
			0xAB,	0x5A,	0x74,
			0xAB,	0x5A,	0x73,
			0xAB,	0x5A,	0x72,
			0xAB,	0x57,	0x72,
			0xAB,	0x56,	0x71,
			0xAB,	0x56,	0x72,
			0xAB,	0x55,	0x73,
			0xAB,	0x55,	0x72,
			0xAB,	0x54,	0x71,
			0xAB,	0x53,	0x71,
			0xAB,	0x52,	0x71,
			0xAB,	0x51,	0x72,
			0xAB,	0x50,	0x72,
			0xAB,	0x4F,	0x73,
			0xAB,	0x4E,	0x73,
			0xAB,	0x4E,	0x74,
			0xAB,	0x4C,	0x74,
			0xAB,	0x4C,	0x75,
			0xF0,

// spotlight on lips
			0x9B,	0x4B,	0x71,
			0xAB,	0x4B,	0x71,
			0xAB,	0x4B,	0x70,
			0xAB,	0x4D,	0x70,
			0xAB,	0x4D,	0x71,
			0xAB,	0x4C,	0x72,
			0xAB,	0x4C,	0x71,
			0xF2,

// spotlight on lips
			0x9B,	0x53,	0x6E,
			0xAB,	0x54,	0x6D,
			0xAB,	0x59,	0x6D,
			0xAB,	0x5A,	0x6E,
			0xAB,	0x5B,	0x6E,
			0xAB,	0x5B,	0x6F,
			0xAB,	0x5E,	0x6F,
			0xAB,	0x5E,	0x71,
			0xF3,

//Eyes
			0x9B,	0x68,	0x4E,
			0xAB,	0x6D,	0x4E,
			0xAB,	0x6D,	0x50,
			0xAB,	0x68,	0x4E,
			0xAB,	0x68,	0x50,
			0xF5,

			0x9B,	0x38,	0x4D,
			0xAB,	0x3E,	0x4D,
			0xAB,	0x3E,	0x50,
			0xAB,	0x38,	0x4D,
			0xAB,	0x38,	0x50,
			0xF5,

			0x1B,	0x80,	0x2D,
			0x2B,	0x82,	0x33,
			0x2B,	0x83,	0x37,
			0x2B,	0x84,	0x41,
			0x2B,	0x85,	0x47,
			0x2B,	0x84,	0x4A,
			0x2B,	0x85,	0x4E,
			0x2B,	0x84,	0x64,
			0x2B,	0x84,	0x67,
			0x2B,	0x83,	0x69,
			0x2B,	0x83,	0x6B,
			0x2B,	0x82,	0x6F,
			0x2B,	0x80,	0x73,
			0x2B,	0x7F,	0x78,
			0x2B,	0x7F,	0x7A,
			0x2B,	0x7E,	0x81,
			0x2B,	0x7C,	0x85,
			0x2B,	0x79,	0x8A,
			0x2B,	0x78,	0x8A,
			0x2B,	0x77,	0x8B,
			0x2B,	0x75,	0x8C,
			0x2B,	0x6E,	0x8E,
			0x2B,	0x6D,	0x8F,
			0x2B,	0x6B,	0x8F,
			0x2B,	0x64,	0x91,
			0x2B,	0x5F,	0x93,
			0x2B,	0x5D,	0x92,
			0x2B,	0x54,	0x91,
			0x2B,	0x50,	0x92,
			0x2B,	0x4D,	0x91,
			0x2B,	0x45,	0x91,
			0x2B,	0x3F,	0x8F,
			0x2B,	0x3C,	0x8C,
			0x2B,	0x3A,	0x8B,
			0x2B,	0x38,	0x89,
			0x2B,	0x36,	0x87,
			0x2B,	0x35,	0x86,
			0x2B,	0x34,	0x84,
			0x2B,	0x32,	0x81,
			0x2B,	0x31,	0x7F,
			0x2B,	0x30,	0x7F,
			0x2B,	0x30,	0x7D,
			0x2B,	0x30,	0x7C,
			0x2B,	0x2F,	0x7A,
			0x2B,	0x2E,	0x79,
			0x2B,	0x2D,	0x78,
			0x2B,	0x2C,	0x75,
			0x2B,	0x2B,	0x74,
			0x2B,	0x2B,	0x72,
			0x2B,	0x2C,	0x71,
			0x2B,	0x2C,	0x70,
			0x2B,	0x2C,	0x6F,
			0x2B,	0x2C,	0x6C,
			0x2B,	0x2C,	0x6A,
			0x2B,	0x2C,	0x68,
			0x2B,	0x2C,	0x66,
			0x2B,	0x2C,	0x64,
			0x2B,	0x2D,	0x62,
			0x2B,	0x2C,	0x5F,
			0x2B,	0x2C,	0x5D,
			0x2B,	0x2C,	0x5C,
			0x2B,	0x2C,	0x59,
			0x2B,	0x2C,	0x58,
			0x2B,	0x2B,	0x56,
			0x2B,	0x2C,	0x57,
			0x2B,	0x30,	0x56,
			0x2B,	0x32,	0x55,
			0x2B,	0x3B,	0x52,
			0x2B,	0x3E,	0x51,
			0x2B,	0x3E,	0x50,
			0x2B,	0x42,	0x4E,
			0x2B,	0x44,	0x4D,
			0x2B,	0x44,	0x4E,
			0x2B,	0x49,	0x4D,
			0x2B,	0x42,	0x4C,
			0x2B,	0x41,	0x4B,
			0x2B,	0x41,	0x4C,
			0x2B,	0x3B,	0x4D,
			0x2B,	0x38,	0x4C,
			0x2B,	0x37,	0x4D,
			0x2B,	0x36,	0x4C,
			0x2B,	0x34,	0x4E,
			0x2B,	0x33,	0x4F,
			0x2B,	0x30,	0x4E,
			0x2B,	0x2F,	0x4F,
			0x2B,	0x2F,	0x4D,
			0x2B,	0x2E,	0x4C,
			0x2B,	0x2D,	0x4B,
			0x2B,	0x2D,	0x4A,
			0x2B,	0x2C,	0x49,
			0x2B,	0x2B,	0x46,
			0x2B,	0x2C,	0x48,
			0x2B,	0x2E,	0x47,
//left eye

			0x1B,	0x2F,	0x46,
			0x2B,	0x30,	0x46,
			0x2B,	0x2F,	0x45,
			0x2B,	0x30,	0x44,
			0x2B,	0x32,	0x42,
			0x2B,	0x34,	0x40,
			0x2B,	0x35,	0x3F,
			0x2B,	0x36,	0x3E,
			0x2B,	0x38,	0x3E,
			0x2B,	0x39,	0x3E,
			0x2B,	0x3A,	0x3E,
			0x2B,	0x3B,	0x3D,
			0x2B,	0x3B,	0x3E,
			0x2B,	0x3C,	0x3E,
			0x2B,	0x3D,	0x3E,
			0x2B,	0x3E,	0x3E,
			0x2B,	0x3E,	0x3D,
			0x2B,	0x3F,	0x3E,
			0x2B,	0x41,	0x3E,
			0x2B,	0x42,	0x3F,
			0x2B,	0x45,	0x40,
			0x2B,	0x46,	0x41,
			0x2B,	0x47,	0x40,
			0x2B,	0x46,	0x3F,
			0x2B,	0x4B,	0x40,
			0x2B,	0x4B,	0x3F,
			0x2B,	0x4A,	0x3E,
			0x2B,	0x47,	0x3D,
			0x2B,	0x42,	0x3B,
			0x2B,	0x3D,	0x3A,
			0x2B,	0x36,	0x3B,
			0x2B,	0x34,	0x3E,
			0x2B,	0x32,	0x40,
			0x2B,	0x30,	0x42,
			
//
			0x1B,	0x2E,	0x44,
			0x2B,	0x2D,	0x45,
			0x2B,	0x2B,	0x44,
			0x2B,	0x2B,	0x43,
			0x2B,	0x28,	0x41,
			0x2B,	0x26,	0x3D,
			0x2B,	0x27,	0x34,
			0x2B,	0x28,	0x32,
			0x2B,	0x29,	0x2C,
			0x2B,	0x2A,	0x2A,
			0x2B,	0x2B,	0x28,
			0x2B,	0x2D,	0x26,
			0x2B,	0x30,	0x25,
			0x2B,	0x31,	0x23,
			0x2B,	0x35,	0x20,
			0x2B,	0x3C,	0x1E,
			0x2B,	0x4B,	0x1D,
			0x2B,	0x4F,	0x1E,
			0x2B,	0x52,	0x1F,
			0x2B,	0x55,	0x20,
			0x2B,	0x5B,	0x1F,
			0x2B,	0x5F,	0x1D,
			0x2B,	0x6A,	0x1D,
			0x2B,	0x6D,	0x1E,
			0x2B,	0x70,	0x20,
			0x2B,	0x73,	0x21,
			0x2B,	0x77,	0x24,
			0x2B,	0x7D,	0x2A,
			0x2B,	0x81,	0x2F,
			0x2B,	0x81,	0x31,


			0x1B,	0x4A,	0x4E,
			0x2B,	0x4D,	0x4E,
			0x2B,	0x4E,	0x4D,
			0x2B,	0x4E,	0x4B,
			0x2B,	0x4E,	0x4A,
			0x2B,	0x4E,	0x49,
			0x2B,	0x4E,	0x48,
			0x2B,	0x4D,	0x47,
			0x2B,	0x4C,	0x45,
			0x2B,	0x4B,	0x44,
			0x2B,	0x49,	0x43,
			0x2B,	0x47,	0x42,
			0x2B,	0x42,	0x43,
			0x2B,	0x45,	0x44,
			0x2B,	0x47,	0x45,
			0x2B,	0x49,	0x46,
			0x2B,	0x4A,	0x47,
			0x2B,	0x4C,	0x49,
			0x2B,	0x4C,	0x4A,
			0x2B,	0x4D,	0x4B,
			0x2B,	0x4D,	0x4C,
			0x2B,	0x4E,	0x4D,

			0x1B,	0x3E,	0x4E,
			0x2B,	0x3F,	0x4E,
			0x2B,	0x3F,	0x4F,
			0x2B,	0x3F,	0x4E,

			0x1B,	0x7F,	0x49,
			0x2B,	0x7D,	0x47,
			0x2B,	0x7C,	0x45,
			0x2B,	0x7A,	0x43,
			0x2B,	0x78,	0x40,
			0x2B,	0x76,	0x3E,
			0x2B,	0x73,	0x3D,
			0x2B,	0x66,	0x3E,
			0x2B,	0x63,	0x3F,
			0x2B,	0x61,	0x40,
			0x2B,	0x60,	0x42,
			0x2B,	0x60,	0x43,
			0x2B,	0x62,	0x43,
			0x2B,	0x63,	0x42,
			0x2B,	0x65,	0x42,
			0x2B,	0x66,	0x41,
			0x2B,	0x69,	0x41,
			0x2B,	0x6A,	0x40,
			0x2B,	0x71,	0x40,
			0x2B,	0x72,	0x3F,
			0x2B,	0x74,	0x3F,
			0x2B,	0x75,	0x40,
			0x2B,	0x76,	0x40,
			0x2B,	0x77,	0x41,
			0x2B,	0x78,	0x43,
			0x2B,	0x7A,	0x44,
			0x2B,	0x7B,	0x45,
			0x2B,	0x7B,	0x46,
			0x2B,	0x7C,	0x47,
			0x2B,	0x7C,	0x48,
			0x2B,	0x7E,	0x49,

			0x1B,	0x6E,	0x46,
			0x2B,	0x6D,	0x45,
			0x2B,	0x6B,	0x44,
			0x2B,	0x64,	0x44,
			0x2B,	0x62,	0x46,
			0x2B,	0x61,	0x47,
			0x2B,	0x60,	0x49,
			0x2B,	0x5F,	0x4A,
			0x2B,	0x5F,	0x4C,
			0x2B,	0x5F,	0x4E,
			0x2B,	0x5F,	0x4F,
			0x2B,	0x5F,	0x50,
			0x2B,	0x66,	0x50,
			0x2B,	0x66,	0x4F,
			0x2B,	0x67,	0x50,
			0x2B,	0x67,	0x51,
			0x2B,	0x68,	0x51,
			0x2B,	0x69,	0x52,
			0x2B,	0x6B,	0x52,
			0x2B,	0x6B,	0x53,
			0x2B,	0x6E,	0x53,
			0x2B,	0x6F,	0x54,
			0x2B,	0x6F,	0x55,
			0x2B,	0x6E,	0x55,
			0x2B,	0x70,	0x56,
			0x2B,	0x71,	0x55,
			0x2B,	0x73,	0x56,
			0x2B,	0x74,	0x56,
			0x2B,	0x76,	0x57,
			0x2B,	0x77,	0x57,
			0x2B,	0x75,	0x55,
			0x2B,	0x76,	0x54,
			0x2B,	0x77,	0x54,
			0x2B,	0x78,	0x53,
			0x2B,	0x7D,	0x53,

			0x1B,	0x6F,	0x47,
			0x2B,	0x6D,	0x46,
			0x2B,	0x6A,	0x46,
			0x2B,	0x67,	0x45,
			0x2B,	0x65,	0x46,
			0x2B,	0x63,	0x47,
			0x2B,	0x61,	0x49,
			0x2B,	0x60,	0x4A,
			0x2B,	0x60,	0x4B,
			0x2B,	0x5F,	0x4C,

			0x1B,	0x60,	0x4F,
			0x2B,	0x63,	0x4E,
			0x2B,	0x66,	0x4D,
			0x2B,	0x6B,	0x4D,
			0x2B,	0x6E,	0x4E,
			0x2B,	0x70,	0x4E,
			0x2B,	0x70,	0x4F,
			0x2B,	0x74,	0x4F,
			0x2B,	0x73,	0x50,
			0x2B,	0x74,	0x50,
			0x2B,	0x75,	0x4F,
			0x2B,	0x75,	0x50,
			0x2B,	0x76,	0x51,
			0x2B,	0x77,	0x50,
			0x2B,	0x79,	0x52,
			0x2B,	0x7B,	0x52,

			0x1B,	0x6A,	0x51,
			0x2B,	0x6A,	0x50,
			0x2B,	0x6B,	0x50,
			0x2B,	0x6B,	0x51,
			0x2B,	0x6A,	0x51,

			0x1B,	0x77,	0x53,
			0x2B,	0x78,	0x53,
			0x2B,	0x77,	0x54,
			0x2B,	0x76,	0x53,
			0x2B,	0x77,	0x53,


//Nose
			0x9B,	0x61,	0x63,
			0xAB,	0x5F,	0x66,
			0xAB,	0x5E,	0x65,
			0xAB,	0x5D,	0x65,
			0xAB,	0x5D,	0x64,
			0xAB,	0x5D,	0x63,
			0xAB,	0x59,	0x62,
			0XF3,
			0x9B,	0x58,	0x63,
			0xAB,	0x55,	0x64,
			0xAB,	0x51,	0x65,
			0xAB,	0x4B,	0x65,
			0xAB,	0x4A,	0x64,
			0xAB,	0x4A,	0x63,
			0xAB,	0x4A,	0x62,
			0xAB,	0x4B,	0x61,
			0XF3,
			0x9B,	0x4B,	0x62,
			0xAB,	0x4B,	0x62,
			0xAB,	0x4C,	0x63,
			0xAB,	0x4E,	0x62,
			0xAB,	0x4E,	0x60,
			0xAB,	0x4E,	0x5E,
			0xAB,	0x4E,	0x5C,
			0xAB,	0x4F,	0x5A,
			0xAB,	0x61,	0x63,
			0XF3,

			0x1B,	0x4F,	0x5B,
			0x2B,	0x50,	0x5C,

			0x1B,	0x51,	0x5C,
			0x2B,	0x52,	0x5E,
			0x2B,	0x53,	0x5F,
			0x2B,	0x54,	0x60,
			0x2B,	0x56,	0x61,
			0x2B,	0x59,	0x60,
			0x2B,	0x5A,	0x5F,
			0x2B,	0x5C,	0x5F,
			0x2B,	0x5C,	0x60,
			0x2B,	0x5D,	0x61,
			0x2B,	0x5E,	0x62,
			0x2B,	0x5E,	0x63,
			0x2B,	0x61,	0x64,

			0x1B,	0x33,	0x02,
			0x2B,	0x30,	0x03,
			0x2B,	0x2F,	0x03,
			0x2B,	0x2D,	0x06,
			0x2B,	0x2B,	0x07,
			0x2B,	0x28,	0x08,
			0x2B,	0x26,	0x0A,
			0x2B,	0x25,	0x0C,
			0x2B,	0x23,	0x0F,
			0x2B,	0x21,	0x11,
			0x2B,	0x1F,	0x14,
			0x2B,	0x1D,	0x15,
			0x2B,	0x1C,	0x18,
			0x2B,	0x1B,	0x1A,
			0x2B,	0x1A,	0x1B,
			0x2B,	0x19,	0x1D,
			0x2B,	0x17,	0x1F,
			0x2B,	0x17,	0x20,
			0x2B,	0x16,	0x20,
			0x2B,	0x14,	0x21,
			0x2B,	0x13,	0x23,
			0x2B,	0x14,	0x25,
			0x2B,	0x15,	0x25,
			0x2B,	0x14,	0x26,
			0x2B,	0x13,	0x26,
			0x2B,	0x11,	0x28,
			0x2B,	0x13,	0x28,
			0x2B,	0x14,	0x27,
			0x2B,	0x14,	0x28,
			0x2B,	0x12,	0x2A,
			0x2B,	0x10,	0x2A,
			0x2B,	0xF,	0x2A,

			0x1B,	0xE,	0x2C,
			0x2B,	0x10,	0x2C,
			0x2B,	0x12,	0x2B,
			0x2B,	0x12,	0x2C,
			0x2B,	0x11,	0x2C,
			0x2B,	0x11,	0x2D,
			0x2B,	0x10,	0x2E,
			0x2B,	0xE,	0x2E,

			0x1B,	0x71,	0x02,
			0x2B,	0x73,	0x04,
			0x2B,	0x74,	0x06,
			0x2B,	0x76,	0x08,
			0x2B,	0x77,	0x0B,
			0x2B,	0x78,	0x0D,
			0x2B,	0x79,	0x0F,
			0x2B,	0x7B,	0x11,
			0x2B,	0x7E,	0x14,
			0x2B,	0x80,	0x16,
			0x2B,	0x81,	0x19,
			0x2B,	0x82,	0x1B,
			0x2B,	0x83,	0x1C,
			0x2B,	0x83,	0x1E,
			0x2B,	0x84,	0x1F,
			0x2B,	0x84,	0x20,
			0x2B,	0x85,	0x21,
			0x2B,	0x85,	0x22,
			0x2B,	0x86,	0x23,
			0x2B,	0x87,	0x25,
			0x2B,	0x86,	0x26,
			0x2B,	0x86,	0x27,
			0x2B,	0x85,	0x29,
			0x2B,	0x84,	0x2A,
			0x2B,	0x83,	0x2B,
			0x2B,	0x84,	0x2C,
			0x2B,	0x85,	0x2B,
			0x2B,	0x86,	0x2A,
			0x2B,	0x88,	0x28,
			0x2B,	0x89,	0x27,
			0x2B,	0x8A,	0x27,
			0x2B,	0x89,	0x29,
			0x2B,	0x88,	0x2B,
			0x2B,	0x86,	0x2C,
			0x2B,	0x86,	0x2D,
			0x2B,	0x87,	0x2E,
			0x2B,	0x88,	0x2D,
			0x2B,	0x89,	0x2D,
			0x2B,	0x8B,	0x2C,
			0x2B,	0x89,	0x2E,
			0x2B,	0x89,	0x2F,
			0x2B,	0x8A,	0x2F,
			0x2B,	0x8B,	0x2F,
			0x2B,	0x8B,	0x2E,
			0x2B,	0x8B,	0x2F,
			0x2B,	0x8B,	0x30,
			0x2B,	0x8A,	0x31,
			0x2B,	0x89,	0x31,
			0x2B,	0x88,	0x32,
			0x2B,	0x89,	0x32,
			0x2B,	0x89,	0x33,
			0x2B,	0x8F,	0x33,
			0x2B,	0x8F,	0x34,
			0x2B,	0x8C,	0x34,

			0x1B,	0x9C,	0x4F,
			0x2B,	0x9A,	0x4D,
			0x2B,	0x9A,	0x4A,
			0x2B,	0x98,	0x48,
			0x2B,	0x99,	0x46,
			0x2B,	0x98,	0x45,
			0x2B,	0x98,	0x43,
			0x2B,	0x96,	0x42,
			0x2B,	0x96,	0x3F,
			0x2B,	0x95,	0x3E,
			0x2B,	0x93,	0x3D,
			0x2B,	0x92,	0x3C,
			0x2B,	0x91,	0x3B,
			0x2B,	0x91,	0x3A,
			0x2B,	0x91,	0x39,
			0x2B,	0x8F,	0x39,
			0x2B,	0x8F,	0x38,
			0x2B,	0x8E,	0x37,
			0x2B,	0x8D,	0x36,
			0x2B,	0x8B,	0x35,

			0x1B,	0x9D,	0x98,
			0x2B,	0x91,	0x93,
			0x2B,	0x8A,	0x92,
			0x2B,	0x7F,	0x93,
			0x2B,	0x7D,	0x95,
			0x2B,	0x7B,	0x97,
			0x2B,	0x79,	0x97,
			0x2B,	0x7B,	0x94,
			0x2B,	0x7D,	0x92,
			0x2B,	0x7E,	0x90,
			0x2B,	0x7D,	0x8E,
			0x2B,	0x7C,	0x8C,
			0x2B,	0x7C,	0x89,
			0x2B,	0x7C,	0x88,
			0x2B,	0x7B,	0x87,
			0x2B,	0x7A,	0x89,
			0x2B,	0x71,	0x94,
			0x2B,	0x6C,	0x98,
			0x2B,	0x63,	0x9E,
			0x2B,	0x5B,	0xA4,
			0x2B,	0x52,	0xA7,
			0x2B,	0x4F,	0xA7,
			0x2B,	0x4D,	0xA9,
			0x2B,	0x45,	0xA9,
			0x2B,	0x46,	0xA6,
			0x2B,	0x46,	0xA3,
			0x2B,	0x40,	0xA1,
			0x2B,	0x3B,	0xA2,
			0x2B,	0x38,	0xA6,
			0x2B,	0x31,	0xA6,
			0x2B,	0x26,	0xA5,
			0x2B,	0x20,	0xA7,
			0x2B,	0x1C,	0xA9,
			0x2B,	0x1A,	0xAA,
			0x2B,	0x16,	0xAB,
			0x2B,	0x13,	0xAD,
			0x2B,	0x11,	0xAE,
			0x2B,	0xF,	0xAF,

			0x1B,	0x1C,	0x63,
			0x2B,	0x1D,	0x66,
			0x2B,	0x1C,	0x69,
			0x2B,	0x1B,	0x6A,
			0x2B,	0x19,	0x6C,
			0x2B,	0x18,	0x6D,
			0x2B,	0x16,	0x6C,
			0x2B,	0x14,	0x6B,
			0x2B,	0x15,	0x69,
			0x2B,	0x14,	0x69,
			0x2B,	0x15,	0x68,
			0x2B,	0x14,	0x67,
			0x2B,	0x14,	0x64,
			0x2B,	0x15,	0x62,
			0x2B,	0x16,	0x5F,
			0x2B,	0x17,	0x5F,
			0x2B,	0x18,	0x60,
			0x2B,	0x18,	0x61,
			0x2B,	0x19,	0x61,
			0x2B,	0x19,	0x5F,
			0x2B,	0x1A,	0x60,
			0x2B,	0x1A,	0x61,
			0x2B,	0x1B,	0x62,
			0x2B,	0x1C,	0x63,

			0x1B,	0x2C,	0x66,
			0x2B,	0x2A,	0x68,
			0x2B,	0x29,	0x69,
			0x2B,	0x28,	0x6B,
			0x2B,	0x27,	0x6D,
			0x2B,	0x26,	0x6E,
			0x2B,	0x24,	0x70,
			0x2B,	0x23,	0x71,
			0x2B,	0x21,	0x71,
			0x2B,	0x20,	0x72,
			0x2B,	0x22,	0x73,
			0x2B,	0x23,	0x73,
			0x2B,	0x25,	0x74,
			0x2B,	0x26,	0x75,
			0x2B,	0x26,	0x76,
			0x2B,	0x24,	0x77,
			0x2B,	0x23,	0x7C,
			0x2B,	0x23,	0x7C,
			0x2B,	0x25,	0x7B,
			0x2B,	0x25,	0x7C,
			0x2B,	0x26,	0x7C,
			0x2B,	0x24,	0x7E,
			0x2B,	0x22,	0x80,
			0x2B,	0x22,	0x82,
			0x2B,	0x21,	0x82,
			0x2B,	0x20,	0x84,
			0x2B,	0x20,	0x85,
			0x2B,	0x22,	0x84,
			0x2B,	0x23,	0x83,
			0x2B,	0x24,	0x82,
			0x2B,	0x26,	0x81,
			0x2B,	0x27,	0x82,
			0x2B,	0x27,	0x81,
			0x2B,	0x28,	0x82,
			0x2B,	0x28,	0x85,
			0x2B,	0x27,	0x87,
			0x2B,	0x25,	0x88,
			0x2B,	0x1F,	0x89,
			0x2B,	0x1F,	0x91,
			0x2B,	0x20,	0x93,
			0x2B,	0x1F,	0x96,
			0x2B,	0x21,	0x99,
			0x2B,	0x20,	0x9C,
			0x2B,	0x22,	0x9D,
			0x2B,	0x23,	0x9E,
			0x2B,	0x25,	0x9F,
			0x2B,	0x25,	0xA1,
			0x2B,	0x22,	0xA4,
			0x2B,	0x1F,	0xA5,
			0x2B,	0x19,	0xA3,
			0x2B,	0x16,	0xA2,
			0x2B,	0x15,	0x9E,
			0x2B,	0x15,	0x9B,
			0x2B,	0x17,	0x9B,
			0x2B,	0x14,	0x98,
			0x2B,	0x13,	0x97,
			0x2B,	0xF,	0x96,

			0x1B,	0x89,	0x3C,
			0x2B,	0x87,	0x3B,
			0x2B,	0x85,	0x39,
			0x2B,	0x84,	0x37,
			0x2B,	0x82,	0x35,

			0x1B,	0x8D,	0x49,
			0x2B,	0x8B,	0x48,
			0x2B,	0x89,	0x47,
			0x2B,	0x88,	0x46,
			0x2B,	0x88,	0x47,
			0x2B,	0x88,	0x48,
			0x2B,	0x8A,	0x49,
			0x2B,	0x89,	0x4A,
			0x2B,	0x88,	0x48,
			0x2B,	0x87,	0x48,
			0x2B,	0x87,	0x47,
			0x2B,	0x86,	0x47,
			0x2B,	0x85,	0x4B,
			0x2B,	0x87,	0x4E,
			0x2B,	0x89,	0x51,
			0x2B,	0x8B,	0x53,
			0x2B,	0x8D,	0x55,
			0x2B,	0x8E,	0x56,
			0x2B,	0x8F,	0x58,
			0x2B,	0x8D,	0x56,
			0x2B,	0x8C,	0x56,
			0x2B,	0x8B,	0x54,
			0x2B,	0x89,	0x53,
			0x2B,	0x88,	0x52,
			0x2B,	0x87,	0x51,
			0x2B,	0x87,	0x59,
			0x2B,	0x89,	0x5B,
			0x2B,	0x8A,	0x5C,
			0x2B,	0x8B,	0x5F,
			0x2B,	0x8C,	0x61,
			0x2B,	0x8E,	0x62,
			0x2B,	0x90,	0x64,
			0x2B,	0x91,	0x66,
			0x2B,	0x93,	0x68,
			0x2B,	0x94,	0x6B,
			0x2B,	0x95,	0x6F,
			0x2B,	0x96,	0x74,
			0x2B,	0x96,	0x77,
			0x2B,	0x95,	0x7A,
			0x2B,	0x92,	0x7D,
			0x2B,	0x91,	0x7E,
			0x2B,	0x8C,	0x7F,
			0x2B,	0x89,	0x7F,
			0x2B,	0x88,	0x7E,
			0x2B,	0x87,	0x7D,
			0x2B,	0x88,	0x7D,
			0x2B,	0x8A,	0x7E,
			0x2B,	0x8E,	0x7E,
			0x2B,	0x8E,	0x7D,
			0x2B,	0x92,	0x7D,
			0x2B,	0x94,	0x7A,
			0x00
		};


int main ()
{
	clg();
	if (getmaxx() > 200) {
		draw_profile(-10, 0, getmaxy()*10/16, marilyn);
		draw_profile(160, 90, 55, marilyn);
	} else
		draw_profile(5, 0, getmaxy()*10/16, marilyn);
}

