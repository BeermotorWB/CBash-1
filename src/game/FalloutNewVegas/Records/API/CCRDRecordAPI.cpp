/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is CBash code.
 *
 * The Initial Developer of the Original Code is
 * Waruddar.
 * Portions created by the Initial Developer are Copyright (C) 2010
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */
#include "common/Common.h"
#include "..\CCRDRecord.h"

namespace FNV
{
uint32_t CCRDRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
    {
    switch(FieldID)
        {
        case 0: //recType
            return GetType();
        case 1: //flags1
            return CB_UINT32_FLAG_FIELD;
        case 2: //fid
            return CB_FORMID_FIELD;
        case 3: //versionControl1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 4: //eid
            return CB_ISTRING_FIELD;
        case 5: //formVersion
            return CB_UINT16_FIELD;
        case 6: //versionControl2
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 2;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 7: //boundX
            return CB_SINT16_FIELD;
        case 8: //boundY
            return CB_SINT16_FIELD;
        case 9: //boundZ
            return CB_SINT16_FIELD;
        case 10: //full
            return CB_STRING_FIELD;
        case 11: //modPath
            return CB_ISTRING_FIELD;
        case 12: //modb
            return CB_FLOAT32_FIELD;
        case 13: //modt_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MODL.IsLoaded() ? MODL->MODT.GetSize() : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 14: //altTextures
            if(!MODL.IsLoaded())
                return CB_UNKNOWN_FIELD;

            if(ListFieldID == 0) //altTextures
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return MODL->Textures.MODS.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= MODL->Textures.MODS.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //name
                    return CB_STRING_FIELD;
                case 2: //texture
                    return CB_FORMID_FIELD;
                case 3: //index
                    return CB_SINT32_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }

        case 17: //modelFlags
            return CB_UINT8_FIELD;
        case 18: //iconPath
            return CB_ISTRING_FIELD;
        case 19: //smallIconPath
            return CB_ISTRING_FIELD;
        case 20: //script
            return CB_FORMID_FIELD;
        case 21: //ynam Sound - Pick Up
            return CB_FORMID_FIELD;
        case 22: //znam Sound - Drop
            return CB_FORMID_FIELD;
        case 23: //tx00 Face
            return CB_ISTRING_FIELD;
        case 24: //tx01 Back
            return CB_ISTRING_FIELD;
        case 25: //intv Suit
            return CB_UINT32_FIELD;
        case 26: //intv Value
            return CB_UINT32_FIELD;
        case 27: //data Value
            return CB_UINT32_FIELD;
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * CCRDRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
    {
    switch(FieldID)
        {
        case 1: //flags1
            return &flags;
        case 2: //fid
            return &formID;
        case 3: //versionControl1
            *FieldValues = &flagsUnk;
            return NULL;
        case 4: //eid
            return EDID.value;
        case 5: //formVersion
            return &formVersion;
        case 6: //versionControl2
            *FieldValues = &versionControl2[0];
            return NULL;
        case 7: //boundX
            return OBND.IsLoaded() ? &OBND->x1 : NULL;
        case 8: //boundY
            return OBND.IsLoaded() ? &OBND->y1 : NULL;
        case 9: //boundZ
            return OBND.IsLoaded() ? &OBND->z1 : NULL;
        case 10: //full
            return FULL.value;
        case 11: //modPath
            return MODL.IsLoaded() ? MODL->MODL.value : NULL;
        case 12: //modb
            return MODL.IsLoaded() ? &MODL->MODB.value : NULL;
        case 13: //modt_p
            *FieldValues = MODL.IsLoaded() ? MODL->MODT.value : NULL;
            return NULL;
        case 14: //mods Alternate Textures
            return NULL;
            //return MODL.IsLoaded() ? MODL->Textures.MODS.value : NULL;
        case 15: //mods Alternate Textures
            return NULL;
            //return MODL.IsLoaded() ? &MODL->Textures.MODS->value15 : NULL;
        case 16: //mods Alternate Textures
            return NULL;
            //return MODL.IsLoaded() ? &MODL->Textures.MODS->value16 : NULL;
        case 17: //modelFlags
            return MODL.IsLoaded() ? &MODL->MODD.value : NULL;
        case 18: //iconPath
            return ICON.value;
        case 19: //smallIconPath
            return MICO.value;
        case 20: //script
            return SCRI.IsLoaded() ? &SCRI.value : NULL;
        case 21: //ynam Sound - Pick Up
            return YNAM.IsLoaded() ? &YNAM.value : NULL;
        case 22: //znam Sound - Drop
            return ZNAM.IsLoaded() ? &ZNAM.value : NULL;
        case 23: //tx00 Face
            return TX00.IsLoaded() ? TX00.value : NULL;
        case 24: //tx01 Back
            return TX01.IsLoaded() ? TX01.value : NULL;
        case 25: //intv Suit
            return INTV1.IsLoaded() ? &INTV1.value : NULL;
        case 26: //intv Value
            return INTV2.IsLoaded() ? &INTV2.value : NULL;
        case 27: //data Value
            return DATA.IsLoaded() ? &DATA.value : NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool CCRDRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
    {
    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(*(uint32_t *)FieldValue);
            break;
        case 3: //versionControl1
            if(ArraySize != 4)
                break;
            ((UINT8ARRAY)&flagsUnk)[0] = ((UINT8ARRAY)FieldValue)[0];
            ((UINT8ARRAY)&flagsUnk)[1] = ((UINT8ARRAY)FieldValue)[1];
            ((UINT8ARRAY)&flagsUnk)[2] = ((UINT8ARRAY)FieldValue)[2];
            ((UINT8ARRAY)&flagsUnk)[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 4: //eid
            EDID.Copy((char *)FieldValue);
            break;
        case 5: //formVersion
            formVersion = *(uint16_t *)FieldValue;
            break;
        case 6: //versionControl2
            if(ArraySize != 2)
                break;
            versionControl2[0] = ((UINT8ARRAY)FieldValue)[0];
            versionControl2[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 7: //boundX
            OBND.Load();
            OBND->x1 = *(int16_t *)FieldValue;
            break;
        case 8: //boundY
            OBND.Load();
            OBND->y1 = *(int16_t *)FieldValue;
            break;
        case 9: //boundZ
            OBND.Load();
            OBND->z1 = *(int16_t *)FieldValue;
            break;
        case 10: //full
            FULL.Copy((char *)FieldValue);
            break;
        case 11: //modPath
            MODL.Load();
            MODL->MODL.Copy((char *)FieldValue);
            break;
        case 12: //modb
            MODL.Load();
            MODL->MODB.value = *(float *)FieldValue;
            break;
        case 13: //modt_p
            MODL.Load();
            MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 14: //mods Alternate Textures
            MODL.Load();
            //MODL->Textures.MODS.Copy((char *)FieldValue);
            break;
        case 15: //mods Alternate Textures
            MODL.Load();
            //MODL->Textures.MODS.Load();
            //MODL->Textures.MODS->value15 = *(FORMID *)FieldValue;
            return true;
        case 16: //mods Alternate Textures
            MODL.Load();
            //MODL->Textures.MODS.Load();
            //MODL->Textures.MODS->value16 = *(int32_t *)FieldValue;
            break;
        case 17: //modelFlags
            MODL.Load();
            MODL->MODD.Load();
            MODL->MODD.value = *(uint8_t *)FieldValue;
            break;
        case 18: //iconPath
            ICON.Copy((char *)FieldValue);
            break;
        case 19: //smallIconPath
            MICO.Copy((char *)FieldValue);
            break;
        case 20: //script
            SCRI.Load();
            SCRI.value = *(FORMID *)FieldValue;
            return true;
        case 21: //ynam Sound - Pick Up
            YNAM.Load();
            YNAM.value = *(FORMID *)FieldValue;
            return true;
        case 22: //znam Sound - Drop
            ZNAM.Load();
            ZNAM.value = *(FORMID *)FieldValue;
            return true;
        case 23: //tx00 Face
            TX00.Load();
            TX00.Copy((char *)FieldValue);
            break;
        case 24: //tx01 Back
            TX01.Load();
            TX01.Copy((char *)FieldValue);
            break;
        case 25: //intv Suit
            INTV1.Load();
            INTV1.value = *(uint32_t *)FieldValue;
            break;
        case 26: //intv Value
            INTV2.Load();
            INTV2.value = *(uint32_t *)FieldValue;
            break;
        case 27: //data Value
            DATA.Load();
            DATA.value = *(uint32_t *)FieldValue;
            break;
        default:
            break;
        }
    return false;
    }

void CCRDRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(0);
            return;
        case 3: //versionControl1
            flagsUnk = 0;
            return;
        case 4: //eid
            EDID.Unload();
            return;
        case 5: //formVersion
            formVersion = 0;
            return;
        case 6: //versionControl2
            versionControl2[0] = 0;
            versionControl2[1] = 0;
            return;
        case 7: //boundX
            if (OBND.IsLoaded())
                OBND->x1 = 0; // defaultOBND.x;
            return;
        case 8: //boundY
            if (OBND.IsLoaded())
                OBND->y1 = 0; // defaultOBND.y;
            return;
        case 9: //boundZ
            if (OBND.IsLoaded())
                OBND->z1 = 0; // defaultOBND.z;
            return;
        case 10: //full
            FULL.Unload();
            return;
        case 11: //modPath
            if(MODL.IsLoaded())
                MODL->MODL.Unload();
            return;
        case 12: //modb
            if(MODL.IsLoaded())
                MODL->MODB.Unload();
            return;
        case 13: //modt_p
            if(MODL.IsLoaded())
                MODL->MODT.Unload();
            return;
        case 14: //mods Alternate Textures
            if(MODL.IsLoaded())
                MODL->Textures.Unload();
            return;
        case 15: //mods Alternate Textures
            if(MODL.IsLoaded())
                MODL->Textures.Unload();
            return;
        case 16: //mods Alternate Textures
            if(MODL.IsLoaded())
                MODL->Textures.Unload();
            return;
        case 17: //modelFlags
            if(MODL.IsLoaded())
                MODL->MODD.Unload();
            return;
        case 18: //iconPath
            ICON.Unload();
            return;
        case 19: //smallIconPath
            MICO.Unload();
            return;
        case 20: //script
            SCRI.Unload();
            return;
        case 21: //ynam Sound - Pick Up
            YNAM.Unload();
            return;
        case 22: //znam Sound - Drop
            ZNAM.Unload();
            return;
        case 23: //tx00 Face
            if(TX00.IsLoaded())
                TX00.Unload();
            return;
        case 24: //tx01 Back
            if(TX00.IsLoaded())
                TX01.Unload();
            return;
        case 25: //intv Suit
            if(INTV1.IsLoaded())
                INTV1.Unload();
            return;
        case 26: //intv Value
            INTV2.Unload();
            return;
        case 27: //data Value
            DATA.Unload();
            return;
        default:
            return;
        }
    }
}