#ifndef LIBUHID_H
#define LIBUHID_H

/*
 *  uHID Universal MCU Bootloader. App loader tool.
 *  Copyright (C) 2016  Andrew 'Necromant' Andrianov
 *
 *  This file is part of uHID project. uHID is loosely (very)
 *  based on bootloadHID avr bootloader by Christian Starkjohann
 *
 *  uHID is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  uHID is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with uHID.  If not, see <http://www.gnu.org/licenses/>.
*/
#define UISP_PART_NAME_LEN  8
#include <stdint.h>
#include <hidapi/hidapi.h>

struct partInfo {
	uint16_t      pageSize;
	uint32_t      size;
	uint8_t       ioSize;
	uint8_t       name[UISP_PART_NAME_LEN];
}  __attribute__((packed));

struct deviceInfo {
	uint8_t       reportId;
	uint8_t       reportId2; /*FixMe: This should be ditched from fw */
	uint8_t       numParts;
	uint8_t       cpuFreq;
	struct partInfo parts[];
} __attribute__((packed));

#include "uhid_export_glue.h"

UHID_API struct deviceInfo *uispReadInfo(hid_device *dev);
UHID_API hid_device *uispOpen(const wchar_t *devId, const wchar_t *serial);
UHID_API char *uispReadPart(hid_device *dev, int part, int *bytes_read);
UHID_API int uispWritePart(hid_device *dev, int part, const char *buf, int length);
UHID_API void uispClose(hid_device *dev);
UHID_API void uispCloseAndRun(hid_device *dev, int part);
UHID_API void uispPrintInfo(struct deviceInfo *inf);
UHID_API void uispOverrideLoaderInfo(int vendor, int product, const wchar_t *vstring);
UHID_API void uispProgressCb(void (*cb)(const char *label, int cur, int max));
UHID_API int uispWritePartFromFile(hid_device *dev, int part, const char *filename);
UHID_API int uispReadPartToFile(hid_device *dev, int part, const char *filename);
UHID_API int uispVerifyPart(hid_device *dev, int part, const char *buf, int len);
UHID_API int uispVerifyPartFromFile(hid_device *dev, int part, const char *filename);
UHID_API int uispLookupPart(hid_device *dev, const char *name);

#endif
