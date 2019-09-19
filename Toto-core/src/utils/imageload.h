#pragma once

#include <string>
#include <FreeImage.h>

namespace toto {
	static BYTE* load_image(const char* filename, GLsizei* width, GLsizei* height) {

		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		FIBITMAP *dib = nullptr;
		fif = FreeImage_GetFileType(filename, 0);
		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(filename);
		if (fif == FIF_UNKNOWN)
			return nullptr;

		if (FreeImage_FIFSupportsReading(fif))
			dib = FreeImage_Load(fif, filename);
		if (!dib)
			return nullptr;

		BYTE* pixels = FreeImage_GetBits(dib);
		*width = FreeImage_GetWidth(dib);
		*height = FreeImage_GetHeight(dib);
		unsigned int BPP = FreeImage_GetBPP(dib);


		int size = *width * *height * (BPP / 8) + (*width%4 * (*height - 1)); // specialni vzorec, nad kterym jsem stravil asi 3 hodiny
		BYTE* result = new BYTE[size];
		memcpy(result, pixels, size);
		FreeImage_Unload(dib);

		//std::cout << size << ", " << *width % 4 * (*height - 1)<< std::endl;

		return result;
	}
}