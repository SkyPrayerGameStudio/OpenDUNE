/* $Id$ */

#include <assert.h>
#include <stdio.h>
#include <stdarg.h>
#include "types.h"
#include "libemu.h"
#include "../global.h"
#include "gui.h"
#include "../os/strings.h"

extern void f__24D0_000D_0039_C17D();
extern void f__2598_0000_0017_EB80();
extern void f__2642_0002_005E_87F6();
extern void f__2642_0069_0008_D517();
extern void emu_GUI_DrawFilledRectangle();
extern void emu_GUI_DrawLine();
extern void emu_GUI_DrawText_Wrapper();
extern void emu_Unknown_07AE_0000();

/**
 * Draw a wired rectangle.
 * @param left The left position of the rectangle.
 * @param top The top position of the rectangle.
 * @param right The right position of the rectangle.
 * @param bottom The bottom position of the rectangle.
 * @param colour The colour of the rectangle.
 */
void GUI_DrawWiredRectangle(uint16 left, uint16 top, uint16 right, uint16 bottom, uint16 colour)
{
	emu_push(colour);
	emu_push(top);
	emu_push(right);
	emu_push(top);
	emu_push(left);
	emu_push(emu_cs); emu_push(0x001E); emu_cs = 0x22A6; emu_GUI_DrawLine();
	emu_sp += 10;

	emu_push(colour);
	emu_push(bottom);
	emu_push(right);
	emu_push(bottom);
	emu_push(left);
	emu_push(emu_cs); emu_push(0x0038); emu_cs = 0x22A6; emu_GUI_DrawLine();
	emu_sp += 10;

	emu_push(colour);
	emu_push(bottom);
	emu_push(left);
	emu_push(top);
	emu_push(left);
	emu_push(emu_cs); emu_push(0x004E); emu_cs = 0x22A6; emu_GUI_DrawLine();
	emu_sp += 10;

	emu_push(colour);
	emu_push(bottom);
	emu_push(right);
	emu_push(top);
	emu_push(right);
	emu_push(emu_cs); emu_push(0x0068); emu_cs = 0x22A6; emu_GUI_DrawLine();
	emu_sp += 10;
}

/**
 * Display a text.
 * @param str The text to display.
 * @param arg0A ??.
 * @param ... The args for the text.
 */
void GUI_DisplayText(const char *str, uint16 arg0A, ...)
{
	char buffer[80];
	buffer[0] = '\0';

	if (str != NULL) {
		va_list ap;

		va_start(ap, arg0A);
		vsnprintf(buffer, sizeof(buffer), str, ap);
		va_end(ap);
	}

	if (arg0A == 0xFFFF) {
		g_global->variable_3734 = 0xFFFF;
		g_global->variable_3736 = 0xFFFF;
		g_global->variable_3738 = 0xFFFF;

		g_global->variable_3644[0] = '\0';
		g_global->variable_3694[0] = '\0';
		g_global->variable_36E4[0] = '\0';

		g_global->variable_373A = 0;
		g_global->variable_373C = 0;
		return;
	}

	if (arg0A == 0xFFFE) {
		if (g_global->variable_373A == 0) {
			g_global->variable_3736 = 0xFFFF;
			g_global->variable_3694[0] = '\0';
		}
		g_global->variable_3738 = 0xFFFF;
		g_global->variable_36E4[0] = '\0';
	}

	if (g_global->variable_373A != 0) {
		uint16 loc04;
		uint16 loc06;

		if (buffer[0] != '\0') {
			if (strcasecmp(buffer, g_global->variable_3694) != 0 && (int16)arg0A >= (int16)g_global->variable_3738) {
				strcpy(g_global->variable_36E4, buffer);
				g_global->variable_3738 = arg0A;
			}
		}
		if ((int32)g_global->variable_373C > (int32)g_global->variable_76AC) return;

		emu_push(7);
		emu_push(emu_cs); emu_push(0x0AA4); emu_cs = 0x07AE; emu_Unknown_07AE_0000();
		emu_sp += 2;

		loc04 = emu_ax;

		if (g_global->variable_38C4 != 0) {
			uint16 loc02;

			emu_push(2);
			emu_push(emu_cs); emu_push(0x0ABB); emu_cs = 0x2598; f__2598_0000_0017_EB80();
			emu_sp += 2;

			loc02 = emu_ax;

			assert(g_global->variable_6668.csip == 0x22A60D31);

			emu_push(g_global->variable_6D59);
			emu_push(23);
			emu_push(319);
			emu_push(0);
			emu_push(0);
			emu_push(emu_cs); emu_push(0x0ADB); emu_cs = 0x22A6; emu_GUI_DrawFilledRectangle();
			emu_sp += 10;

			emu_push(18);
			emu_push(0);
			emu_push(g_global->variable_8ADA);
			emu_push(2);
			emu_push(g_global->variable_992D << 3);
			emu_push(0x353F); emu_push(0x3694); /* g_global->variable_3694 */
			emu_push(emu_cs); emu_push(0x0AFF); emu_GUI_DrawText_Wrapper();
			emu_sp += 14;

			emu_push(18);
			emu_push(0);
			emu_push(g_global->variable_8AD8);
			emu_push(13);
			emu_push(g_global->variable_992D << 3);
			emu_push(0x353F); emu_push(0x3644); /* g_global->variable_3644 */
			emu_push(emu_cs); emu_push(0x0B23); emu_GUI_DrawText_Wrapper();
			emu_sp += 14;

			g_global->variable_38C4 = 0;

			emu_push(loc02);
			emu_push(emu_cs); emu_push(0x0B34); emu_cs = 0x2598; f__2598_0000_0017_EB80();
			emu_sp += 2;
		}

		emu_push(7);
		emu_push(emu_cs); emu_push(0x0B3E); emu_cs = 0x2642; f__2642_0002_005E_87F6();
		emu_sp += 2;

		if (g_global->variable_3740 + g_global->variable_9931 > 24) {
			loc06 = 24 - g_global->variable_3740;
		} else {
			loc06 = g_global->variable_9931;
		}

		emu_push(0);
		emu_push(2);
		emu_push(loc06);
		emu_push(g_global->variable_992F);
		emu_push(g_global->variable_992B);
		emu_push(g_global->variable_992D);
		emu_push(g_global->variable_3740);
		emu_push(g_global->variable_992D);
		emu_push(emu_cs); emu_push(0x0B7D); emu_cs = 0x24D0; f__24D0_000D_0039_C17D();
		emu_sp += 16;

		emu_push(emu_cs); emu_push(0x0B85); emu_cs = 0x2642; f__2642_0069_0008_D517();

		emu_push(loc04);
		emu_push(emu_cs); emu_push(0x0B8D); emu_cs = 0x07AE; emu_Unknown_07AE_0000();
		emu_sp += 2;

		if (g_global->variable_3740 != 0) {
			if ((int16)g_global->variable_3738 <= (int16)g_global->variable_3736) {
				g_global->variable_373C = g_global->variable_76AC + 1;
			}
			g_global->variable_3740--;
			return;
		}

		strcpy(g_global->variable_3644, g_global->variable_3694);

		g_global->variable_8AD8 = g_global->variable_8ADA;
		g_global->variable_3734 = (g_global->variable_3736 != 0) ? g_global->variable_3736 - 1 : 0;

		strcpy(g_global->variable_3694, g_global->variable_36E4);

		g_global->variable_3736 = g_global->variable_3738;
		g_global->variable_8ADA = g_global->variable_8ADC;
		g_global->variable_36E4[0] = '\0';
		g_global->variable_3738 = 0xFFFF;
		g_global->variable_38C4 = 1;
		g_global->variable_373C = g_global->variable_76AC + ((int16)g_global->variable_3736 <= (int16)g_global->variable_3734 ? 900 : 1);
		g_global->variable_373A = 0;
		return;
	}

	if (buffer[0] != '\0') {
		if (strcasecmp(buffer, g_global->variable_3644) != 0 && strcasecmp(buffer, g_global->variable_3694) != 0 && strcasecmp(buffer, g_global->variable_36E4) != 0) {
			if ((int16)arg0A >= (int16)g_global->variable_3736) {
				strcpy(g_global->variable_36E4, g_global->variable_3694);

				g_global->variable_8ADC = g_global->variable_8ADA;
				g_global->variable_3738 = g_global->variable_3736;

				strcpy(g_global->variable_3694, buffer);

				g_global->variable_8ADA = 12;
				g_global->variable_3736 = arg0A;
			} else if ((int16)arg0A >= (int16)g_global->variable_3738) {
				strcpy(g_global->variable_36E4, buffer);
				g_global->variable_3738 = arg0A;
				g_global->variable_8ADC = 12;
			}
		}
	} else {
		if (g_global->variable_3644[0] == '\0' && g_global->variable_3694[0] == '\0') return;
	}

	if ((int16)g_global->variable_3736 <= (int16)g_global->variable_3734 && (int32)g_global->variable_373C >= (int32)g_global->variable_76AC) return;

	g_global->variable_373A = 1;
	g_global->variable_3740 = 10;
	g_global->variable_373C = 0;
}
