/* utility.h

Copyright (c) 2016, Nikolaj Schlej. All rights reserved.
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

*/

#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <QByteArray>
#include "basetypes.h"
#include "parsingdata.h"
#include "cbstring.h"
#include "treemodel.h"

// Returns either new parsing data instance or obtains it from index
PARSING_DATA parsingDataFromQModelIndex(const ModelIndex & index);

// Converts parsing data to byte array
QByteArray parsingDataToQByteArray(const PARSING_DATA & pdata);

// Converts error code to string
extern CBString errorCodeToString(UINT8 errorCode);

// Decompression routine
extern STATUS decompress(const QByteArray & compressed, UINT8 & algorithm, QByteArray & decompressed, QByteArray & efiDecompressed);

// Compression routine
//STATUS compress(const QByteArray & decompressed, QByteArray & compressed, const UINT8 & algorithm);

// CRC32 calculation routine
extern UINT32 crc32(UINT32 initial, const UINT8* buffer, UINT32 length);

// 8bit checksum calculation routine
extern UINT8 calculateChecksum8(const UINT8* buffer, UINT32 bufferSize);

// 16bit checksum calculation routine
extern UINT16 calculateChecksum16(const UINT16* buffer, UINT32 bufferSize);

#endif
