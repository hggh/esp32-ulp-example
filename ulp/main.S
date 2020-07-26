#include "soc/rtc_cntl_reg.h"
#include "soc/rtc_io_reg.h"
#include "soc/soc_ulp.h"

	.bss

	.global p1_status
p1_status:
	.long 0

p1_status_next:
	.long 0

	.global p2_status
p2_status:
	.long 0

p2_status_next:
	.long 0

	.global p3_status
p3_status:
	.long 0

p3_status_next:
	.long 0

	.global event_counter
event_counter:
	.long 0

	.text

bump_event_counter:
	move r3, event_counter
	ld r2, r3, 0
	add r2, r2, 1
	st r2, r3, 0

	jump wakeup

exit:
	halt

wakeup:
	/* try to wakeup SoC, if not => halt */
	STAGE_INC  1
	JUMPS exit, 10, GT

	READ_RTC_FIELD(RTC_CNTL_LOW_POWER_ST_REG, RTC_CNTL_RDY_FOR_WAKEUP)
	AND r0, r0, 1
	JUMP wakeup, eq
	wake

	halt

p1_status_changed:
	move r3, p1_status_next
        ld r2, r3, 0
        add r2, r2, 1
        and r2, r2, 1
        st r2, r3, 0

	jump bump_event_counter

p2_status_changed:
	move r3, p2_status_next
        ld r2, r3, 0
        add r2, r2, 1
        and r2, r2, 1
        st r2, r3, 0

	jump bump_event_counter

p3_status_changed:
	move r3, p3_status_next
        ld r2, r3, 0
        add r2, r2, 1
        and r2, r2, 1
        st r2, r3, 0

	jump bump_event_counter

	.global entry
entry:
	STAGE_RST

	/* read the RTC pins and store it into global variables ; just read the pin register once and store it into R1 */
	READ_RTC_REG(RTC_GPIO_IN_REG, RTC_GPIO_IN_NEXT_S, 16)
	move r1, r0

	move r3, p1_status
        rsh r0, r1, 7
	and r0, r0, 1
	st r0, r3, 0

	move r3, p2_status
        rsh r0, r1, 8
	and r0, r0, 1
	st r0, r3, 0

	move r3, p3_status
        rsh r0, r1, 9
	and r0, r0, 1
	st r0, r3, 0

	/* check if p1 status changed */
        rsh r0, r1, 7
	and r0, r0, 1
	move r3, p1_status_next
	ld r3, r3, 0
	add r3, r0, r3
        and r3, r3, 1
	jump p1_status_changed, eq

	/* check if p2 status changed */
        rsh r0, r1, 8
	and r0, r0, 1
	move r3, p2_status_next
	ld r3, r3, 0
	add r3, r0, r3
        and r3, r3, 1
	jump p2_status_changed, eq

	/* check if p3 status changed */
        rsh r0, r1, 9
	and r0, r0, 1
	move r3, p3_status_next
	ld r3, r3, 0
	add r3, r0, r3
        and r3, r3, 1
	jump p3_status_changed, eq


	halt
