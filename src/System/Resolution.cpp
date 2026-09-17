#include <System/Resolution.hpp>
#include <dolphin/vi.h>

u16 SMSGetGameVideoWidth() { return 660; }

u16 SMSGetGameVideoHeight(u32 fmt)
{
	u16 ret = 448;
	switch (fmt) {
	case VI_MPAL:
	case VI_NTSC:
	case VI_EURGB60:
		ret = 448;
		break;
	case VI_PAL:
		ret = 530;
		break;
	default:
		break;
	}
	return ret;
}

// UNUSED
s32 SMSGetDisplayWidthMax() { return 720; }

// UNUSED
s32 SMSGetDisplayHeightMax() { return 574; }

u16 SMSGetTitleVideoWidth() { return 660; }

u16 SMSGetTitleVideoHeight(u32 fmt) { return SMSGetGameVideoHeight(fmt); }

u16 SMSGetGameRenderWidth() { return 640; }

u16 SMSGetGameRenderHeight() { return 448; }

u16 SMSGetTitleRenderWidth() { return 640; }

u16 SMSGetTitleRenderHeight() { return 448; }

u16 SMSGetGCLogoRenderWidth() { return 640; }

u16 SMSGetGCLogoRenderHeight() { return 448; }

u16 SMSGetGCLogoVideoWidth() { return 640; }

// TODO: nonmatching. This switch is byte-identical to
// SMSGetGameVideoHeight() above, and MWCC folds it into a `bl` to that
// function instead of emitting a duplicate switch, but the real GMSP01
// target keeps a fully duplicated switch here. The original source likely
// differed slightly (or used a different translation-unit-local ordering)
// in a way that suppressed the fold; needs further investigation.
u16 SMSGetGCLogoVideoHeight(u32 fmt)
{
	u16 ret = 448;
	switch (fmt) {
	case VI_MPAL:
	case VI_NTSC:
	case VI_EURGB60:
		ret = 448;
		break;
	case VI_PAL:
		ret = 530;
		break;
	default:
		break;
	}
	return ret;
}
