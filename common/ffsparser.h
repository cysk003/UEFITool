/* ffsparser.h

Copyright (c) 2016, Nikolaj Schlej. All rights reserved.
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHWARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
*/

#ifndef __FFSPARSER_H__
#define __FFSPARSER_H__

#include <vector>

#include <QByteArray>

#include "basetypes.h"
#include "treemodel.h"
#include "utility.h"
#include "peimage.h"
#include "parsingdata.h"
#include "types.h"
#include "treemodel.h"
#include "descriptor.h"
#include "ffs.h"
#include "gbe.h"
#include "me.h"
#include "fit.h"

class TreeModel;

class FfsParser
{
public:
    // Default constructor and destructor
    FfsParser(TreeModel* treeModel);
    ~FfsParser();

    // Returns messages 
    std::vector<std::pair<ModelIndex, CBString> > getMessages() const;
    // Clears messages
    void clearMessages();

    // Firmware image parsing
    STATUS parse(const QByteArray &buffer);
    
    // Retuns index of the last VTF after parsing is done
    const ModelIndex getLastVtf() {return lastVtf;};

private:
    TreeModel *model;
    std::vector<std::pair<ModelIndex, CBString> > messagesVector;
    ModelIndex lastVtf;
    UINT32 capsuleOffsetFixup;
    
    STATUS parseRawArea(const QByteArray & data, const ModelIndex & index);
    STATUS parseVolumeHeader(const QByteArray & volume, const UINT32 parentOffset, const ModelIndex & parent, ModelIndex & index);
    STATUS parseVolumeBody(const ModelIndex & index);
    STATUS parseFileHeader(const QByteArray & file, const UINT32 parentOffset, const ModelIndex & parent, ModelIndex & index);
    STATUS parseFileBody(const ModelIndex & index);
    STATUS parseSectionHeader(const QByteArray & section, const UINT32 parentOffset, const ModelIndex & parent, ModelIndex & index, const bool preparse = false);
    STATUS parseSectionBody(const ModelIndex & index);

    STATUS parseIntelImage(const QByteArray & intelImage, const UINT32 parentOffset, const ModelIndex & parent, ModelIndex & root);
    STATUS parseGbeRegion(const QByteArray & gbe, const UINT32 parentOffset, const ModelIndex & parent, ModelIndex & index);
    STATUS parseMeRegion(const QByteArray & me, const UINT32 parentOffset, const ModelIndex & parent, ModelIndex & index);
    STATUS parseBiosRegion(const QByteArray & bios, const UINT32 parentOffset, const ModelIndex & parent, ModelIndex & index);
    STATUS parsePdrRegion(const QByteArray & pdr, const UINT32 parentOffset, const ModelIndex & parent, ModelIndex & index);
    STATUS parseGeneralRegion(const UINT8 subtype, const QByteArray & region, const UINT32 parentOffset, const ModelIndex & parent, ModelIndex & index);

    STATUS parsePadFileBody(const ModelIndex & index);
    STATUS parseVolumeNonUefiData(const QByteArray & data, const UINT32 parentOffset, const ModelIndex & index);

    STATUS parseSections(const QByteArray & sections, const ModelIndex & index, const bool preparse = false);
    STATUS parseCommonSectionHeader(const QByteArray & section, const UINT32 parentOffset, const ModelIndex & parent, ModelIndex & index, const bool preparse);
    STATUS parseCompressedSectionHeader(const QByteArray & section, const UINT32 parentOffset, const ModelIndex & parent, ModelIndex & index, const bool preparse);
    STATUS parseGuidedSectionHeader(const QByteArray & section, const UINT32 parentOffset, const ModelIndex & parent, ModelIndex & index, const bool preparse);
    STATUS parseFreeformGuidedSectionHeader(const QByteArray & section, const UINT32 parentOffset, const ModelIndex & parent, ModelIndex & index, const bool preparse);
    STATUS parseVersionSectionHeader(const QByteArray & section, const UINT32 parentOffset, const ModelIndex & parent, ModelIndex & index, const bool preparse);
    STATUS parsePostcodeSectionHeader(const QByteArray & section, const UINT32 parentOffset, const ModelIndex & parent, ModelIndex & index, const bool preparse);

    STATUS parseCompressedSectionBody(const ModelIndex & index);
    STATUS parseGuidedSectionBody(const ModelIndex & index);
    STATUS parseVersionSectionBody(const ModelIndex & index);
    STATUS parseDepexSectionBody(const ModelIndex & index);
    STATUS parseUiSectionBody(const ModelIndex & index);
    STATUS parseRawSectionBody(const ModelIndex & index);
    STATUS parsePeImageSectionBody(const ModelIndex & index);
    STATUS parseTeImageSectionBody(const ModelIndex & index);

    UINT8  getPaddingType(const QByteArray & padding);
    STATUS parseAprioriRawSection(const QByteArray & body, CBString & parsed);
    STATUS findNextVolume(const ModelIndex & index, const QByteArray & bios, const UINT32 parentOffset, const UINT32 volumeOffset, UINT32 & nextVolumeOffset);
    STATUS getVolumeSize(const QByteArray & bios, const UINT32 volumeOffset, UINT32 & volumeSize, UINT32 & bmVolumeSize);
    UINT32 getFileSize(const QByteArray & volume, const UINT32 fileOffset, const UINT8 ffsVersion);
    UINT32 getSectionSize(const QByteArray & file, const UINT32 sectionOffset, const UINT8 ffsVersion);

    STATUS performFirstPass(const QByteArray & imageFile, ModelIndex & index);
    STATUS performSecondPass(const ModelIndex & index);
    STATUS addOffsetsRecursive(const ModelIndex & index);
    STATUS addMemoryAddressesRecursive(const ModelIndex & index, const UINT32 diff);

    // Message helper
    void msg(const ModelIndex &index, const char* fmt, ...);
};

#endif
