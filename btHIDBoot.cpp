/* 

This software may be distributed and modified under the terms of the GNU
General Public License version 2 (GPL2) as published by the Free Software
Foundation and appearing in the file GPL2.TXT included in the packaging of
this file. Please note that GPL2 Section 2[b] requires that all works based
on this software must also be made publicly available under the terms of
the GPL2 ("Copyleft").

Contact information
-------------------

LSChyi
e-mail   : alan81920@gmail.com 
 */
#include "btHIDBoot.h"

void BtMouseReportParser::Parse(HID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf) {
        MOUSEINFO *pmi = (MOUSEINFO*)buf;

#if 0
        if (prevState.mouseInfo.bmLeftButton == 0 && pmi->bmLeftButton == 1)
                OnLeftButtonDown(pmi);

        if (prevState.mouseInfo.bmLeftButton == 1 && pmi->bmLeftButton == 0)
                OnLeftButtonUp(pmi);

        if (prevState.mouseInfo.bmRightButton == 0 && pmi->bmRightButton == 1)
                OnRightButtonDown(pmi);

        if (prevState.mouseInfo.bmRightButton == 1 && pmi->bmRightButton == 0)
                OnRightButtonUp(pmi);

        if (prevState.mouseInfo.bmMiddleButton == 0 && pmi->bmMiddleButton == 1)
                OnMiddleButtonDown(pmi);

        if (prevState.mouseInfo.bmMiddleButton == 1 && pmi->bmMiddleButton == 0)
                OnMiddleButtonUp(pmi);

        if (prevState.mouseInfo.dX != pmi->dX || prevState.mouseInfo.dY != pmi->dY)
                OnMouseMove(pmi);

        if (len > sizeof (MOUSEINFO))
                for (uint8_t i = 0; i<sizeof (MOUSEINFO); i++)
                        prevState.bInfo[i] = buf[i];
#else
        if(prevState.mouseInfo.bmLeftButton != pmi->bmLeftButton ) {
                if(pmi->bmLeftButton) {
                        OnLeftButtonDown(pmi);
                } else {
                        OnLeftButtonUp(pmi);
                }
        }

        if(prevState.mouseInfo.bmRightButton != pmi->bmRightButton) {
                if(pmi->bmRightButton) {
                        OnRightButtonDown(pmi);
                } else {
                        OnRightButtonUp(pmi);
                }
        }

        if(prevState.mouseInfo.bmMiddleButton != pmi->bmMiddleButton) {
                if(pmi->bmMiddleButton) {
                        OnMiddleButtonDown(pmi);
                } else {
                        OnMiddleButtonUp(pmi);
                }
        }

        //
        // Scroll wheel(s), are not part of the spec, but we could support it.
        // Logitech wireless keyboard and mouse combo reports scroll wheel in byte 4
        // We wouldn't even need to save this information.
        //if(len > 3) {
        //}
        //

        // Mice only report motion when they actually move!
        // Why not just pass the x/y values to simplify things??
        if(pmi->dX || pmi->dY) {
                OnMouseMove(pmi);
                // Future:
                // event = true;
        }

        // Only the first byte matters (buttons). We do NOT need to save position info.
        prevState.bInfo[0] = buf[0];
#endif

};

void BtKeyboardReportParser::Parse(HID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf) {
        // On error - return
        if (buf[2] == 1)
                return;

        for (uint8_t i = 0; i < 8; i++) {
                bool down = false;
                bool up = false;

                for (uint8_t j = 0; j < 8; j++) {
                        if (buf[i] == prevState.bInfo[j] && buf[i] != 1)
                                down = true;
                        if (buf[j] == prevState.bInfo[i] && prevState.bInfo[i] != 1)
                                up = true;
                }
                if (!down) {
                        HandleLockingKeys(hid, buf[i]);
                        OnKeyDown(*buf, buf[i], buf);
                }
                if (!up)
                        OnKeyUp(prevState.bInfo[0], prevState.bInfo[i], buf);
        }
        for (uint8_t i = 0; i < 8; i++)
                prevState.bInfo[i] = buf[i];
};

const uint8_t BtKeyboardReportParser::numKeys[10] PROGMEM = {'!', '@', '#', '$', '%', '^', '&', '*', '(', ')'};
const uint8_t BtKeyboardReportParser::symKeysUp[12] PROGMEM = {'_', '+', '{', '}', '|', '~', ':', '"', '~', '<', '>', '?'};
const uint8_t BtKeyboardReportParser::symKeysLo[12] PROGMEM = {'-', '=', '[', ']', '\\', ' ', ';', '\'', '`', ',', '.', '/'};
const uint8_t BtKeyboardReportParser::padKeys[5] PROGMEM = {'/', '*', '-', '+', 0x13};
