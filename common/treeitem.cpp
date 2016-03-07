/* treeitem.cpp

Copyright (c) 2015, Nikolaj Schlej. All rights reserved.
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution. The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

*/

#include "treeitem.h"
#include "types.h"

TreeItem::TreeItem(const UINT8 type, const UINT8 subtype, 
    const CBString & name, const CBString & text, const CBString & info,
    const ByteArray & header, const ByteArray & body, 
    const bool fixed, const bool compressed, const ByteArray & parsingData,
    TreeItem *parent) : 
    itemAction(Actions::NoAction),
    itemType(type),
    itemSubtype(subtype),
    itemName(name),
    itemText(text),
    itemInfo(info),
    itemHeader(header),
    itemBody(body),
    itemParsingData(parsingData),
    itemFixed(fixed),
    itemCompressed(compressed),
    parentItem(parent)
{
}

TreeItem::~TreeItem() {
    std::list<TreeItem*>::iterator begin = childItems.begin();
    while (begin != childItems.end()) {
        delete *begin;
        ++begin;
    }
}

UINT8 TreeItem::insertChildBefore(TreeItem *item, TreeItem *newItem)
{
    std::list<TreeItem*>::iterator found = std::find(std::begin(childItems), std::end(childItems), item);
    if (found == std::end(childItems))
        return ERR_ITEM_NOT_FOUND;
    childItems.insert(found, newItem);
    return ERR_SUCCESS;
}

UINT8 TreeItem::insertChildAfter(TreeItem *item, TreeItem *newItem)
{
    std::list<TreeItem*>::iterator found = std::find(std::begin(childItems), std::end(childItems), item);
    if (found == std::end(childItems))
        return ERR_ITEM_NOT_FOUND;
    childItems.insert(++found, newItem);
    return ERR_SUCCESS;
}

CBString TreeItem::data(int column) const
{
    switch (column)
    {
    case 0: // Name
        return itemName;
    case 1: // Action
        return actionTypeToString(itemAction);
    case 2: // Type
        return itemTypeToString(itemType);
    case 3: // Subtype
        return itemSubtypeToString(itemType, itemSubtype);
    case 4: // Text
        return itemText;
    default:
        return CBString();
    }
}

int TreeItem::row() const
{
    if (parentItem) {
        std::list<TreeItem*>::const_iterator iter = parentItem->childItems.cbegin();
        for (int i = 0; i < (int)parentItem->childItems.size(); ++i, ++iter) {
            if (const_cast<TreeItem*>(this) == *iter)
                return i;
        }
    }
    return 0;
}
