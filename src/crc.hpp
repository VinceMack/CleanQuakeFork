// crc.h -- CRC-16 checksum function declarations
#pragma once

namespace Common {

void CRC_Init(unsigned short* crcvalue);
void CRC_ProcessByte(unsigned short* crcvalue, byte data);
unsigned short CRC_Value(unsigned short crcvalue);

} // namespace Common

using namespace Common;
