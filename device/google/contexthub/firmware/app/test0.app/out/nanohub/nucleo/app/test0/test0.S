
out/nanohub/nucleo/app/test0/test0.elf:     file format elf32-littlearm


Disassembly of section .flash:

10000000 <_mAppVer-0x4>:
10000000:	4e49424e 	cdpmi	2, 4, cr4, cr9, cr14, {2}

10000004 <_mAppVer>:
10000004:	00000000 	andeq	r0, r0, r0
10000008:	80000000 	andhi	r0, r0, r0
1000000c:	80000000 	andhi	r0, r0, r0
10000010:	10000270 	andne	r0, r0, r0, ror r2
10000014:	80000024 	andhi	r0, r0, r4, lsr #32
10000018:	8000002c 	andhi	r0, r0, ip, lsr #32
1000001c:	80000004 	andhi	r0, r0, r4
10000020:	80000024 	andhi	r0, r0, r4, lsr #32
10000024:	10000294 	mulne	r0, r4, r2
10000028:	10000294 	mulne	r0, r4, r2

1000002c <_mAppFuncs>:
1000002c:	10000065 	andne	r0, r0, r5, rrx
10000030:	10000055 	andne	r0, r0, r5, asr r0
10000034:	100000a5 	andne	r0, r0, r5, lsr #1

10000038 <eOsLog>:
{
    eOsLogvInternal(level, str, VA_LIST_TO_INTEGER(vl));
}

static inline void eOsLog(enum LogLevel level, const char *str, ...)
{
10000038:	b40e      	push	{r1, r2, r3}
1000003a:	b083      	sub	sp, #12
1000003c:	ab03      	add	r3, sp, #12
1000003e:	4601      	mov	r1, r0
10000040:	f853 2b04 	ldr.w	r2, [r3], #4
    va_list vl;

    va_start(vl, str);
10000044:	9301      	str	r3, [sp, #4]
    (void)syscallDo3P(SYSCALL_NO(SYSCALL_DOMAIN_OS, SYSCALL_OS_MAIN, SYSCALL_OS_MAIN_LOGGING, SYSCALL_OS_MAIN_LOG_LOGV), level, str, args_list);
10000046:	f44f 7000 	mov.w	r0, #512	@ 0x200
1000004a:	df01      	svc	1
    eOsLogvInternal(level, str, VA_LIST_TO_INTEGER(vl));
    va_end(vl);
}
1000004c:	b003      	add	sp, #12
1000004e:	b003      	add	sp, #12
10000050:	4770      	bx	lr
10000052:	ffff  	vtbl.8	d20, {d15-d18}, d2

10000054 <end_task>:
    return eOsEventSubscribe(myTid, EVT_APP_START);
}

static void end_task(void)
{
    eOsLog(LOG_DEBUG, "App 0 terminating");
10000054:	4b02      	ldr	r3, [pc, #8]	@ (10000060 <end_task+0xc>)
10000056:	2044      	movs	r0, #68	@ 0x44
10000058:	f859 1003 	ldr.w	r1, [r9, r3]
1000005c:	f7ff bfec 	b.w	10000038 <eOsLog>
10000060:	00000004 	andeq	r0, r0, r4

10000064 <start_task>:
    mMyTid = myTid;
10000064:	4b08      	ldr	r3, [pc, #32]	@ (10000088 <start_task+0x24>)
10000066:	f859 3003 	ldr.w	r3, [r9, r3]
1000006a:	6018      	str	r0, [r3, #0]
    cnt = 100;
1000006c:	4b07      	ldr	r3, [pc, #28]	@ (1000008c <start_task+0x28>)
1000006e:	f859 3003 	ldr.w	r3, [r9, r3]
10000072:	2264      	movs	r2, #100	@ 0x64
{
10000074:	4601      	mov	r1, r0
    cnt = 100;
10000076:	601a      	str	r2, [r3, #0]
    return syscallDo2P(SYSCALL_NO(SYSCALL_DOMAIN_OS, SYSCALL_OS_MAIN, SYSCALL_OS_MAIN_EVENTQ, SYSCALL_OS_MAIN_EVTQ_SUBCRIBE), tid, evtType);
10000078:	2000      	movs	r0, #0
1000007a:	f44f 6280 	mov.w	r2, #1024	@ 0x400
1000007e:	df01      	svc	1
}
10000080:	3800      	subs	r0, #0
10000082:	bf18      	it	ne
10000084:	2001      	movne	r0, #1
10000086:	4770      	bx	lr
10000088:	00000008 	andeq	r0, r0, r8
1000008c:	0000000c 	andeq	r0, r0, ip

10000090 <syscallDoGeneric.constprop.0>:
#define _INC_SYSCALL_DEFS_H_

#include <cpu/syscallDo.h>

/* it is always safe to use this, but using syscallDo0P .. syscallDo4P macros may produce faster code for free */
static inline uintptr_t syscallDoGeneric(uint32_t syscallNo, ...)
10000090:	b40f      	push	{r0, r1, r2, r3}
10000092:	b082      	sub	sp, #8
{
    uintptr_t ret;
    va_list vl;

    va_start(vl, syscallNo);
10000094:	a903      	add	r1, sp, #12
10000096:	9101      	str	r1, [sp, #4]
    #ifdef SYSCALL_PARAMS_PASSED_AS_PTRS
        ret = cpuSyscallDo(syscallNo, &vl);
    #else
        ret = cpuSyscallDo(syscallNo, *(uint32_t*)&vl);
10000098:	f240 6001 	movw	r0, #1537	@ 0x601
1000009c:	df00      	svc	0
    #endif
    va_end(vl);

    return ret;
}
1000009e:	b002      	add	sp, #8
100000a0:	b004      	add	sp, #16
100000a2:	4770      	bx	lr

100000a4 <handle_event>:
}

static void handle_event(uint32_t evtType, const void* evtData)
{
100000a4:	e92d 4cf0 	stmdb	sp!, {r4, r5, r6, r7, sl, fp, lr}
    const struct TimerEvent *te;
    const struct AppEventFreeData *aefd;
    uint32_t timerId;
    struct ExtMsg *extMsg;

    if (evtType == EVT_APP_START) {
100000a8:	f5b0 6f80 	cmp.w	r0, #1024	@ 0x400
{
100000ac:	b08b      	sub	sp, #44	@ 0x2c
100000ae:	460d      	mov	r5, r1
    if (evtType == EVT_APP_START) {
100000b0:	d11c      	bne.n	100000ec <handle_event+0x48>
        timerId = eOsTimTimerSet(1000000000ULL, 50, 50, mMyTid, (void *)&cnt, false);
100000b2:	4b47      	ldr	r3, [pc, #284]	@ (100001d0 <handle_event+0x12c>)
static inline uint32_t eOsTimTimerSet(uint64_t length, uint32_t jitterPpm, uint32_t driftPpm, uint32_t tid, void* cookie, bool oneShot)
{
    uint32_t lengthLo = length;
    uint32_t lengthHi = length >> 32;

    return syscallDoGeneric(SYSCALL_NO(SYSCALL_DOMAIN_OS, SYSCALL_OS_MAIN, SYSCALL_OS_MAIN_TIME, SYSCALL_OS_MAIN_TIME_SET_TIMER), lengthLo, lengthHi, jitterPpm, driftPpm, tid, cookie, (int)oneShot);
100000b4:	4945      	ldr	r1, [pc, #276]	@ (100001cc <handle_event+0x128>)
100000b6:	f859 3003 	ldr.w	r3, [r9, r3]
100000ba:	2200      	movs	r2, #0
100000bc:	681c      	ldr	r4, [r3, #0]
100000be:	4b45      	ldr	r3, [pc, #276]	@ (100001d4 <handle_event+0x130>)
100000c0:	9203      	str	r2, [sp, #12]
100000c2:	f859 3003 	ldr.w	r3, [r9, r3]
100000c6:	e9cd 4301 	strd	r4, r3, [sp, #4]
100000ca:	2332      	movs	r3, #50	@ 0x32
100000cc:	9300      	str	r3, [sp, #0]
100000ce:	f240 6001 	movw	r0, #1537	@ 0x601
100000d2:	f7ff ffdd 	bl	10000090 <syscallDoGeneric.constprop.0>
        eOsLog(LOG_INFO, "App 0 started with tid %u timerid %u\n", mMyTid, timerId);
100000d6:	4a40      	ldr	r2, [pc, #256]	@ (100001d8 <handle_event+0x134>)
100000d8:	f859 1002 	ldr.w	r1, [r9, r2]
100000dc:	4603      	mov	r3, r0
100000de:	4622      	mov	r2, r4
100000e0:	2049      	movs	r0, #73	@ 0x49
    } else if (evtType == EVT_APP_FREE_EVT_DATA) {
        aefd = evtData;
        if (aefd->evtType == EVT_APP_TO_HOST)
            eOsHeapFree(aefd->evtData);
    }
}
100000e2:	b00b      	add	sp, #44	@ 0x2c
100000e4:	e8bd 4cf0 	ldmia.w	sp!, {r4, r5, r6, r7, sl, fp, lr}
        eOsLog(LOG_INFO, "App 0 started with tid %u timerid %u\n", mMyTid, timerId);
100000e8:	f7ff bfa6 	b.w	10000038 <eOsLog>
    } else if (evtType == EVT_APP_TIMER) {
100000ec:	28df      	cmp	r0, #223	@ 0xdf
100000ee:	d162      	bne.n	100001b6 <handle_event+0x112>
        eOsLog(LOG_INFO, "App 0 received timer %u callback: %d (TIM: %lld, RTC: %lld, SENSOR: %lld, HOST: %lld)\n", te->timerId, *(int *)te->data, eOsTimGetTime(), eOsRtcGetTime(), eOsSensorGetTime(), eOsHostGetTime());
100000f0:	e9d1 2300 	ldrd	r2, r3, [r1]
    syscallDo1P(SYSCALL_NO(SYSCALL_DOMAIN_OS, SYSCALL_OS_MAIN, SYSCALL_OS_MAIN_TIME, SYSCALL_OS_MAIN_TIME_GET_TIME), &timeNanos);
100000f4:	f44f 60c0 	mov.w	r0, #1536	@ 0x600
100000f8:	681b      	ldr	r3, [r3, #0]
100000fa:	a908      	add	r1, sp, #32
100000fc:	df01      	svc	1
}

static inline uint64_t eOsRtcGetTime(void)
{
    uint64_t timeNanos;
    syscallDo1P(SYSCALL_NO(SYSCALL_DOMAIN_OS, SYSCALL_OS_MAIN, SYSCALL_OS_MAIN_RTC, SYSCALL_OS_MAIN_RTC_GET_TIME), &timeNanos);
100000fe:	f44f 6060 	mov.w	r0, #3584	@ 0xe00
    return timeNanos;
10000102:	e9dd 6708 	ldrd	r6, r7, [sp, #32]
    syscallDo1P(SYSCALL_NO(SYSCALL_DOMAIN_OS, SYSCALL_OS_MAIN, SYSCALL_OS_MAIN_RTC, SYSCALL_OS_MAIN_RTC_GET_TIME), &timeNanos);
10000106:	a908      	add	r1, sp, #32
10000108:	df01      	svc	1
    syscallDo1P(SYSCALL_NO(SYSCALL_DOMAIN_OS, SYSCALL_OS_MAIN, SYSCALL_OS_MAIN_SENSOR, SYSCALL_OS_MAIN_SENSOR_GET_TIME), &timeNanos);
1000010a:	f240 400a 	movw	r0, #1034	@ 0x40a
    return timeNanos;
1000010e:	e9dd ab08 	ldrd	sl, fp, [sp, #32]
    syscallDo1P(SYSCALL_NO(SYSCALL_DOMAIN_OS, SYSCALL_OS_MAIN, SYSCALL_OS_MAIN_SENSOR, SYSCALL_OS_MAIN_SENSOR_GET_TIME), &timeNanos);
10000112:	a908      	add	r1, sp, #32
10000114:	df01      	svc	1
    syscallDo1P(SYSCALL_NO(SYSCALL_DOMAIN_OS, SYSCALL_OS_MAIN, SYSCALL_OS_MAIN_HOST, SYSCALL_OS_MAIN_HOST_GET_TIME), &timeNanos);
10000116:	f44f 6040 	mov.w	r0, #3072	@ 0xc00
    return timeNanos;
1000011a:	ed9d 7b08 	vldr	d7, [sp, #32]
    syscallDo1P(SYSCALL_NO(SYSCALL_DOMAIN_OS, SYSCALL_OS_MAIN, SYSCALL_OS_MAIN_HOST, SYSCALL_OS_MAIN_HOST_GET_TIME), &timeNanos);
1000011e:	a908      	add	r1, sp, #32
10000120:	df01      	svc	1
10000122:	ed9d 6b08 	vldr	d6, [sp, #32]
10000126:	492d      	ldr	r1, [pc, #180]	@ (100001dc <handle_event+0x138>)
10000128:	2049      	movs	r0, #73	@ 0x49
1000012a:	f859 1001 	ldr.w	r1, [r9, r1]
1000012e:	ed8d 6b06 	vstr	d6, [sp, #24]
10000132:	ed8d 7b04 	vstr	d7, [sp, #16]
10000136:	e9cd ab02 	strd	sl, fp, [sp, #8]
1000013a:	e9cd 6700 	strd	r6, r7, [sp]
1000013e:	f7ff ff7b 	bl	10000038 <eOsLog>
    return (void*)syscallDo1P(SYSCALL_NO(SYSCALL_DOMAIN_OS, SYSCALL_OS_MAIN, SYSCALL_OS_MAIN_HEAP, SYSCALL_OS_MAIN_HEAP_ALLOC), sz);
10000142:	f44f 6000 	mov.w	r0, #2048	@ 0x800
10000146:	210e      	movs	r1, #14
10000148:	df01      	svc	1
        extMsg->hdr.appId = APP_ID_MAKE(NANOHUB_VENDOR_GOOGLE, 0x548000);
1000014a:	2300      	movs	r3, #0
1000014c:	7003      	strb	r3, [r0, #0]
1000014e:	f06f 037f 	mvn.w	r3, #127	@ 0x7f
10000152:	7043      	strb	r3, [r0, #1]
10000154:	2354      	movs	r3, #84	@ 0x54
10000156:	7083      	strb	r3, [r0, #2]
10000158:	236c      	movs	r3, #108	@ 0x6c
1000015a:	70c3      	strb	r3, [r0, #3]
1000015c:	2367      	movs	r3, #103	@ 0x67
1000015e:	7103      	strb	r3, [r0, #4]
10000160:	236f      	movs	r3, #111	@ 0x6f
10000162:	7143      	strb	r3, [r0, #5]
10000164:	7183      	strb	r3, [r0, #6]
10000166:	2347      	movs	r3, #71	@ 0x47
10000168:	71c3      	strb	r3, [r0, #7]
        extMsg->hdr.dataLen = 5;
1000016a:	2305      	movs	r3, #5
1000016c:	7203      	strb	r3, [r0, #8]
        extMsg->msg = 0x01;
1000016e:	2301      	movs	r3, #1
10000170:	7243      	strb	r3, [r0, #9]
        extMsg->val = *(int *)te->data;
10000172:	686b      	ldr	r3, [r5, #4]
10000174:	681b      	ldr	r3, [r3, #0]
10000176:	f8c0 300a 	str.w	r3, [r0, #10]
        if (!(eOsEnqueueEvt(EVT_APP_TO_HOST, extMsg, mMyTid)))
1000017a:	4b15      	ldr	r3, [pc, #84]	@ (100001d0 <handle_event+0x12c>)
1000017c:	f859 3003 	ldr.w	r3, [r9, r3]
10000180:	4604      	mov	r4, r0
    return syscallDo3P(SYSCALL_NO(SYSCALL_DOMAIN_OS, SYSCALL_OS_MAIN, SYSCALL_OS_MAIN_EVENTQ, SYSCALL_OS_MAIN_EVTQ_ENQUEUE), evtType, evtData, tidOfWhoWillFreeThisEvent);
10000182:	681b      	ldr	r3, [r3, #0]
10000184:	2002      	movs	r0, #2
10000186:	f240 4101 	movw	r1, #1025	@ 0x401
1000018a:	4622      	mov	r2, r4
1000018c:	df01      	svc	1
1000018e:	b918      	cbnz	r0, 10000198 <handle_event+0xf4>
    (void)syscallDo1P(SYSCALL_NO(SYSCALL_DOMAIN_OS, SYSCALL_OS_MAIN, SYSCALL_OS_MAIN_HEAP, SYSCALL_OS_MAIN_HEAP_FREE), ptr);
10000190:	f640 0001 	movw	r0, #2049	@ 0x801
10000194:	4621      	mov	r1, r4
10000196:	df01      	svc	1
        if (cnt-- <= 0)
10000198:	4b0e      	ldr	r3, [pc, #56]	@ (100001d4 <handle_event+0x130>)
1000019a:	f859 2003 	ldr.w	r2, [r9, r3]
1000019e:	6813      	ldr	r3, [r2, #0]
100001a0:	1e59      	subs	r1, r3, #1
100001a2:	2b00      	cmp	r3, #0
100001a4:	6011      	str	r1, [r2, #0]
100001a6:	dc03      	bgt.n	100001b0 <handle_event+0x10c>
    return syscallDo1P(SYSCALL_NO(SYSCALL_DOMAIN_OS, SYSCALL_OS_MAIN, SYSCALL_OS_MAIN_TIME, SYSCALL_OS_MAIN_TIME_CANCEL_TIMER), timerId);
100001a8:	6829      	ldr	r1, [r5, #0]
100001aa:	f240 6002 	movw	r0, #1538	@ 0x602
    (void)syscallDo1P(SYSCALL_NO(SYSCALL_DOMAIN_OS, SYSCALL_OS_MAIN, SYSCALL_OS_MAIN_HEAP, SYSCALL_OS_MAIN_HEAP_FREE), ptr);
100001ae:	df01      	svc	1
}
100001b0:	b00b      	add	sp, #44	@ 0x2c
100001b2:	e8bd 8cf0 	ldmia.w	sp!, {r4, r5, r6, r7, sl, fp, pc}
    } else if (evtType == EVT_APP_FREE_EVT_DATA) {
100001b6:	28ff      	cmp	r0, #255	@ 0xff
100001b8:	d1fa      	bne.n	100001b0 <handle_event+0x10c>
        if (aefd->evtType == EVT_APP_TO_HOST)
100001ba:	680a      	ldr	r2, [r1, #0]
100001bc:	f240 4301 	movw	r3, #1025	@ 0x401
100001c0:	429a      	cmp	r2, r3
100001c2:	d1f5      	bne.n	100001b0 <handle_event+0x10c>
100001c4:	6849      	ldr	r1, [r1, #4]
100001c6:	f640 0001 	movw	r0, #2049	@ 0x801
100001ca:	e7f0      	b.n	100001ae <handle_event+0x10a>
100001cc:	3b9aca00 	blcc	e6b29d4 <_mAppVer-0x194d630>
100001d0:	00000008 	andeq	r0, r0, r8
100001d4:	0000000c 	andeq	r0, r0, ip
100001d8:	00000010 	andeq	r0, r0, r0, lsl r0
100001dc:	00000014 	andeq	r0, r0, r4, lsl r0
100001e0:	20707041 	rsbscs	r7, r0, r1, asr #32
100001e4:	65742030 	ldrbvs	r2, [r4, #-48]!	@ 0xffffffd0
100001e8:	6e696d72 	mcrvs	13, 3, r6, cr9, cr2, {3}
100001ec:	6e697461 	cdpvs	4, 6, cr7, cr9, cr1, {3}
100001f0:	70410067 	subvc	r0, r1, r7, rrx
100001f4:	20302070 	eorscs	r2, r0, r0, ror r0
100001f8:	72617473 	rsbvc	r7, r1, #1929379840	@ 0x73000000
100001fc:	20646574 	rsbcs	r6, r4, r4, ror r5
10000200:	68746977 	ldmdavs	r4!, {r0, r1, r2, r4, r5, r6, r8, fp, sp, lr}^
10000204:	64697420 	strbtvs	r7, [r9], #-1056	@ 0xfffffbe0
10000208:	20752520 	rsbscs	r2, r5, r0, lsr #10
1000020c:	656d6974 	strbvs	r6, [sp, #-2420]!	@ 0xfffff68c
10000210:	20646972 	rsbcs	r6, r4, r2, ror r9
10000214:	000a7525 	andeq	r7, sl, r5, lsr #10
10000218:	20707041 	rsbscs	r7, r0, r1, asr #32
1000021c:	65722030 	ldrbvs	r2, [r2, #-48]!	@ 0xffffffd0
10000220:	76696563 	strbtvc	r6, [r9], -r3, ror #10
10000224:	74206465 	strtvc	r6, [r0], #-1125	@ 0xfffffb9b
10000228:	72656d69 	rsbvc	r6, r5, #6720	@ 0x1a40
1000022c:	20752520 	rsbscs	r2, r5, r0, lsr #10
10000230:	6c6c6163 	stfvse	f6, [ip], #-396	@ 0xfffffe74
10000234:	6b636162 	blvs	118d87c4 <__rel_end+0x18d8530>
10000238:	6425203a 	strtvs	r2, [r5], #-58	@ 0xffffffc6
1000023c:	49542820 	ldmdbmi	r4, {r5, fp, sp}^
10000240:	25203a4d 	strcs	r3, [r0, #-2637]!	@ 0xfffff5b3
10000244:	2c646c6c 	stclcs	12, cr6, [r4], #-432	@ 0xfffffe50
10000248:	43545220 	cmpmi	r4, #32, 4
1000024c:	6c25203a 	stcvs	0, cr2, [r5], #-232	@ 0xffffff18
10000250:	202c646c 	eorcs	r6, ip, ip, ror #8
10000254:	534e4553 	movtpl	r4, #58707	@ 0xe553
10000258:	203a524f 	eorscs	r5, sl, pc, asr #4
1000025c:	646c6c25 	strbtvs	r6, [ip], #-3109	@ 0xfffff3db
10000260:	4f48202c 	svcmi	0x0048202c
10000264:	203a5453 	eorscs	r5, sl, r3, asr r4
10000268:	646c6c25 	strbtvs	r6, [ip], #-3109	@ 0xfffff3db
1000026c:	ff000a29 			@ <UNDEFINED> instruction: 0xff000a29

Disassembly of section .data:

80000000 <_GLOBAL_OFFSET_TABLE_-0x18>:
80000000:	00000000 	andeq	r0, r0, r0
80000004:	100001e0 	andne	r0, r0, r0, ror #3
80000008:	80000028 	andhi	r0, r0, r8, lsr #32
8000000c:	80000024 	andhi	r0, r0, r4, lsr #32
80000010:	100001f2 	strdne	r0, [r0], -r2
80000014:	10000218 	andne	r0, r0, r8, lsl r2

80000018 <_GLOBAL_OFFSET_TABLE_>:
	...

Disassembly of section .bss:

80000024 <cnt>:
80000024:	00000000 	andeq	r0, r0, r0

80000028 <mMyTid>:
80000028:	00000000 	andeq	r0, r0, r0

Disassembly of section .debug_info:

00000000 <.debug_info>:
   0:	00000b99 	muleq	r0, r9, fp
   4:	04010005 	streq	r0, [r1], #-5
   8:	00000000 	andeq	r0, r0, r0
   c:	00020d21 	andeq	r0, r2, r1, lsr #26
  10:	00c41d00 	sbceq	r1, r4, r0, lsl #26
  14:	03de0000 	bicseq	r0, lr, #0
  18:	00ab0000 	adceq	r0, fp, r0
	...
  24:	08050000 	stmdaeq	r5, {}	@ <UNPREDICTABLE>
  28:	00017a07 	andeq	r7, r1, r7, lsl #20
  2c:	07040500 	streq	r0, [r4, -r0, lsl #10]
  30:	00000184 	andeq	r0, r0, r4, lsl #3
  34:	69050422 	stmdbvs	r5, {r1, r5, sl}
  38:	0500746e 	streq	r7, [r0, #-1134]	@ 0xfffffb92
  3c:	00ed0508 	rsceq	r0, sp, r8, lsl #10
  40:	08050000 	stmdaeq	r5, {}	@ <UNPREDICTABLE>
  44:	00015904 	andeq	r5, r1, r4, lsl #18
  48:	06010500 	streq	r0, [r1], -r0, lsl #10
  4c:	00000167 	andeq	r0, r0, r7, ror #2
  50:	00011d08 	andeq	r1, r1, r8, lsl #26
  54:	182b0400 	stmdane	fp!, {sl}
  58:	0000005c 	andeq	r0, r0, ip, asr r0
  5c:	65080105 	strvs	r0, [r8, #-261]	@ 0xfffffefb
  60:	05000001 	streq	r0, [r0, #-1]
  64:	001b0502 	andseq	r0, fp, r2, lsl #10
  68:	02050000 	andeq	r0, r5, #0
  6c:	00037e07 	andeq	r7, r3, r7, lsl #28
  70:	05040500 	streq	r0, [r4, #-1280]	@ 0xfffffb00
  74:	000000f2 	strdeq	r0, [r0], -r2
  78:	00005008 	andeq	r5, r0, r8
  7c:	194f0400 	stmdbne	pc, {sl}^	@ <UNPREDICTABLE>
  80:	00000084 	andeq	r0, r0, r4, lsl #1
  84:	7f070405 	svcvc	0x00070405
  88:	08000001 	stmdaeq	r0, {r0}
  8c:	0000039b 	muleq	r0, fp, r3
  90:	26196904 	ldrcs	r6, [r9], -r4, lsl #18
  94:	08000000 	stmdaeq	r0, {}	@ <UNPREDICTABLE>
  98:	00000433 	andeq	r0, r0, r3, lsr r4
  9c:	2d1ae804 	ldccs	8, cr14, [sl, #-16]
  a0:	23000000 	movwcs	r0, #0
  a4:	00fb2404 	rscseq	r2, fp, r4, lsl #8
  a8:	0a040000 	beq	1000b0 <_mAppVer-0xfefff54>
  ac:	0000bc00 	andeq	fp, r0, r0, lsl #24
  b0:	01e92500 	mvneq	r2, r0, lsl #10
  b4:	00a30000 	adceq	r0, r3, r0
  b8:	00000000 	andeq	r0, r0, r0
  bc:	0000c10a 	andeq	ip, r0, sl, lsl #2
  c0:	01052600 	tsteq	r5, r0, lsl #12
  c4:	00016e08 	andeq	r6, r1, r8, lsl #28
  c8:	00c21000 	sbceq	r1, r2, r0
  cc:	c90a0000 	stmdbgt	sl, {}	@ <UNPREDICTABLE>
  d0:	0a000000 	beq	d8 <_mAppVer-0xfffff2c>
  d4:	000000d8 	ldrdeq	r0, [r0], -r8
  d8:	011f0827 	tsteq	pc, r7, lsr #16
  dc:	18050000 	stmdane	r5, {}	@ <UNPREDICTABLE>
  e0:	00005013 	andeq	r5, r0, r3, lsl r0
  e4:	00520800 	subseq	r0, r2, r0, lsl #16
  e8:	30050000 	andcc	r0, r5, r0
  ec:	00007814 	andeq	r7, r0, r4, lsl r8
  f0:	00e51000 	rsceq	r1, r5, r0
  f4:	9d080000 	stcls	0, cr0, [r8, #-0]
  f8:	05000003 	streq	r0, [r0, #-3]
  fc:	008b143c 	addeq	r1, fp, ip, lsr r4
 100:	35080000 	strcc	r0, [r8, #-0]
 104:	05000004 	streq	r0, [r0, #-4]
 108:	00971552 	addseq	r1, r7, r2, asr r5
 10c:	3f080000 	svccc	0x00080000
 110:	06000004 	streq	r0, [r0], -r4
 114:	00a51b28 	adceq	r1, r5, r8, lsr #22
 118:	fd080000 	stc2	0, cr0, [r8, #-0]
 11c:	06000000 	streq	r0, [r0], -r0
 120:	010e1863 	tsteq	lr, r3, ror #16
 124:	ee110000 	cdp	0, 1, cr0, cr1, cr0, {0}
 128:	09000001 	stmdbeq	r0, {r0}
 12c:	014d3407 	cmpeq	sp, r7, lsl #8
 130:	000b0000 	andeq	r0, fp, r0
 134:	07000000 	streq	r0, [r0, -r0]
 138:	00f60e35 	rscseq	r0, r6, r5, lsr lr
 13c:	0b000000 	bleq	144 <_mAppVer-0xffffec0>
 140:	000001d0 	ldrdeq	r0, [r0], -r0	@ <UNPREDICTABLE>
 144:	d90d3607 	stmdble	sp, {r0, r1, r2, r9, sl, ip, sp}
 148:	08000000 	stmdaeq	r0, {}	@ <UNPREDICTABLE>
 14c:	005d1100 	subseq	r1, sp, r0, lsl #2
 150:	080c0000 	stmdaeq	ip, {}	@ <UNPREDICTABLE>
 154:	00018131 	andeq	r8, r1, r1, lsr r1
 158:	01ff0b00 	mvnseq	r0, r0, lsl #22
 15c:	33080000 	movwcc	r0, #32768	@ 0x8000
 160:	00019c0c 	andeq	r9, r1, ip, lsl #24
 164:	65150000 	ldrvs	r0, [r5, #-0]
 168:	0800646e 	stmdaeq	r0, {r1, r2, r3, r5, r6, sl, sp, lr}
 16c:	00bc0c34 	adcseq	r0, ip, r4, lsr ip
 170:	0b040000 	bleq	100178 <_mAppVer-0xfeffe8c>
 174:	00000173 	andeq	r0, r0, r3, ror r1
 178:	b10c3608 	tstlt	ip, r8, lsl #12
 17c:	08000001 	stmdaeq	r0, {r0}
 180:	014d1000 	mrseq	r1, (UNDEF: 77)
 184:	95280000 	strls	r0, [r8, #-0]!
 188:	95000001 	strls	r0, [r0, #-1]
 18c:	17000001 	strne	r0, [r0, -r1]
 190:	000000e5 	andeq	r0, r0, r5, ror #1
 194:	02010500 	andeq	r0, r1, #0, 10
 198:	000001ca 	andeq	r0, r0, sl, asr #3
 19c:	0001860a 	andeq	r8, r1, sl, lsl #12
 1a0:	01b12900 			@ <UNDEFINED> instruction: 0x01b12900
 1a4:	e5170000 	ldr	r0, [r7, #-0]
 1a8:	17000000 	strne	r0, [r0, -r0]
 1ac:	000000d3 	ldrdeq	r0, [r0], -r3
 1b0:	01a10a00 			@ <UNDEFINED> instruction: 0x01a10a00
 1b4:	d8110000 	ldmdale	r1, {}	@ <UNPREDICTABLE>
 1b8:	08000001 	stmdaeq	r0, {r0}
 1bc:	01dd7c08 	bicseq	r7, sp, r8, lsl #24
 1c0:	a90b0000 	stmdbge	fp, {}	@ <UNPREDICTABLE>
 1c4:	08000000 	stmdaeq	r0, {}	@ <UNPREDICTABLE>
 1c8:	00e50e7d 	rsceq	r0, r5, sp, ror lr
 1cc:	0b000000 	bleq	1d4 <_mAppVer-0xffffe30>
 1d0:	00000455 	andeq	r0, r0, r5, asr r4
 1d4:	a30b7e08 	movwge	r7, #48648	@ 0xbe08
 1d8:	04000000 	streq	r0, [r0], #-0
 1dc:	01b61000 			@ <UNDEFINED> instruction: 0x01b61000
 1e0:	142a0000 	strtne	r0, [sl], #-0
 1e4:	07000001 	streq	r0, [r0, -r1]
 1e8:	00005c01 	andeq	r5, r0, r1, lsl #24
 1ec:	012d0800 			@ <UNDEFINED> instruction: 0x012d0800
 1f0:	00021406 	andeq	r1, r2, r6, lsl #8
 1f4:	00b11200 	adcseq	r1, r1, r0, lsl #4
 1f8:	12450000 	subne	r0, r5, #0
 1fc:	00000080 	andeq	r0, r0, r0, lsl #1
 200:	00661257 	rsbeq	r1, r6, r7, asr r2
 204:	12490000 	subne	r0, r9, #0
 208:	00000141 	andeq	r0, r0, r1, asr #2
 20c:	000f1244 	andeq	r1, pc, r4, asr #4
 210:	00560000 	subseq	r0, r6, r0
 214:	00046f11 	andeq	r6, r4, r1, lsl pc
 218:	1e090800 	cdpne	8, 0, cr0, cr9, cr0, {0}
 21c:	0000023b 	andeq	r0, r0, fp, lsr r2
 220:	0004250b 	andeq	r2, r4, fp, lsl #10
 224:	0e1f0900 	vnmlseq.f16	s0, s30, s0	@ <UNPREDICTABLE>
 228:	000000e5 	andeq	r0, r0, r5, ror #1
 22c:	03a60b00 			@ <UNDEFINED> instruction: 0x03a60b00
 230:	20090000 	andcs	r0, r9, r0
 234:	0000a30b 	andeq	sl, r0, fp, lsl #6
 238:	10000400 	andne	r0, r0, r0, lsl #8
 23c:	00000214 	andeq	r0, r0, r4, lsl r2
 240:	d7040405 	strle	r0, [r4, -r5, lsl #8]
 244:	2b000000 	blcs	24c <_mAppVer-0xffffdb8>
 248:	0000002e 	andeq	r0, r0, lr, lsr #32
 24c:	e5111801 	ldr	r1, [r1, #-2049]	@ 0xfffff7ff
 250:	05000000 	streq	r0, [r0, #-0]
 254:	00002803 	andeq	r2, r0, r3, lsl #16
 258:	6e631d80 	cdpvs	13, 6, cr1, cr3, cr0, {4}
 25c:	19010074 	stmdbne	r1, {r2, r4, r5, r6}
 260:	0000340c 	andeq	r3, r0, ip, lsl #8
 264:	24030500 	strcs	r0, [r3], #-1280	@ 0xfffffb00
 268:	11800000 	orrne	r0, r0, r0
 26c:	000001b4 			@ <UNDEFINED> instruction: 0x000001b4
 270:	9f1b010e 	svcls	0x001b010e
 274:	15000002 	strne	r0, [r0, #-2]
 278:	00726468 	rsbseq	r6, r2, r8, ror #8
 27c:	261d1d01 	ldrcs	r1, [sp], -r1, lsl #26
 280:	00000001 	andeq	r0, r0, r1
 284:	67736d15 			@ <UNDEFINED> instruction: 0x67736d15
 288:	0d1e0100 	ldfeqs	f0, [lr, #-0]
 28c:	000000d9 	ldrdeq	r0, [r0], -r9
 290:	61761509 	cmnvs	r6, r9, lsl #10
 294:	1f01006c 	svcne	0x0001006c
 298:	0000e50e 	andeq	lr, r0, lr, lsl #10
 29c:	2c000a00 			@ <UNDEFINED> instruction: 0x2c000a00
 2a0:	0000005b 	andeq	r0, r0, fp, asr r0
 2a4:	81014c01 	tsthi	r1, r1, lsl #24
 2a8:	2d000001 	stccs	0, cr0, [r0, #-4]
 2ac:	0000029f 	muleq	r0, pc, r2	@ <UNPREDICTABLE>
 2b0:	002c0305 	eoreq	r0, ip, r5, lsl #6
 2b4:	bb2e1000 	bllt	b842bc <_mAppVer-0xf47bd48>
 2b8:	01000000 	mrseq	r0, (UNDEF: 0)
 2bc:	00f1014c 	rscseq	r0, r1, ip, asr #2
 2c0:	03050000 	movweq	r0, #20480	@ 0x5000
 2c4:	10000004 	andne	r0, r0, r4
 2c8:	00003518 	andeq	r3, r0, r8, lsl r5
 2cc:	0d2f0100 	stfeqs	f0, [pc, #-0]	@ 2d4 <_mAppVer-0xffffd30>
 2d0:	100000a4 	andne	r0, r0, r4, lsr #1
 2d4:	0000013c 	andeq	r0, r0, ip, lsr r1
 2d8:	06a39c01 	strteq	r9, [r3], r1, lsl #24
 2dc:	a9160000 	ldmdbge	r6, {}	@ <UNPREDICTABLE>
 2e0:	01000000 	mrseq	r0, (UNDEF: 0)
 2e4:	00e5232f 	rsceq	r2, r5, pc, lsr #6
 2e8:	00180000 	andseq	r0, r8, r0
 2ec:	000c0000 	andeq	r0, ip, r0
 2f0:	55160000 	ldrpl	r0, [r6, #-0]
 2f4:	01000004 	tsteq	r0, r4
 2f8:	00d3382f 	sbcseq	r3, r3, pc, lsr #16
 2fc:	00580000 	subseq	r0, r8, r0
 300:	004a0000 	subeq	r0, sl, r0
 304:	742f0000 	strtvc	r0, [pc], #-0	@ 30c <_mAppVer-0xffffcf8>
 308:	31010065 	tstcc	r1, r5, rrx
 30c:	0006a31e 	andeq	sl, r6, lr, lsl r3
 310:	00008d00 	andeq	r8, r0, r0, lsl #26
 314:	00008900 	andeq	r8, r0, r0, lsl #18
 318:	03bb1900 			@ <UNDEFINED> instruction: 0x03bb1900
 31c:	24320000 	ldrtcs	r0, [r2], #-0
 320:	000006a8 	andeq	r0, r0, r8, lsr #13
 324:	000000a2 	andeq	r0, r0, r2, lsr #1
 328:	0000009e 	muleq	r0, lr, r0
 32c:	00042519 	andeq	r2, r4, r9, lsl r5
 330:	e50e3300 	str	r3, [lr, #-768]	@ 0xfffffd00
 334:	b6000000 	strlt	r0, [r0], -r0
 338:	b2000000 	andlt	r0, r0, #0
 33c:	19000000 	stmdbne	r0, {}	@ <UNPREDICTABLE>
 340:	0000047a 	andeq	r0, r0, sl, ror r4
 344:	06ad1434 			@ <UNDEFINED> instruction: 0x06ad1434
 348:	00ca0000 	sbceq	r0, sl, r0
 34c:	00c60000 	sbceq	r0, r6, r0
 350:	610c0000 	mrsvs	r0, (UNDEF: 12)
 354:	be000008 	cdplt	0, 0, cr0, cr0, cr8, {0}
 358:	00100000 	andseq	r0, r0, r0
 35c:	0000000c 	andeq	r0, r0, ip
 360:	04101337 	ldreq	r1, [r0], #-823	@ 0xfffffcc9
 364:	71030000 	mrsvc	r0, (UNDEF: 3)
 368:	dc000008 	stcle	0, cr0, [r0], {8}
 36c:	da000000 	ble	374 <_mAppVer-0xffffc90>
 370:	03000000 	movweq	r0, #0
 374:	0000087d 	andeq	r0, r0, sp, ror r8
 378:	000000f0 	strdeq	r0, [r0], -r0	@ <UNPREDICTABLE>
 37c:	000000ee 	andeq	r0, r0, lr, ror #1
 380:	00088903 	andeq	r8, r8, r3, lsl #18
 384:	0000f000 	andeq	pc, r0, r0
 388:	0000ee00 	andeq	lr, r0, r0, lsl #28
 38c:	08a00300 	stmiaeq	r0!, {r8, r9}
 390:	00fd0000 	rscseq	r0, sp, r0
 394:	00fb0000 	rscseq	r0, fp, r0
 398:	ac030000 	stcge	0, cr0, [r3], {-0}
 39c:	0d000008 	stceq	0, cr0, [r0, #-32]	@ 0xffffffe0
 3a0:	0b000001 	bleq	3ac <_mAppVer-0xffffc58>
 3a4:	03000001 	movweq	r0, #1
 3a8:	00000895 	muleq	r0, r5, r8
 3ac:	00000119 	andeq	r0, r0, r9, lsl r1
 3b0:	00000117 	andeq	r0, r0, r7, lsl r1
 3b4:	00000c13 	andeq	r0, r0, r3, lsl ip
 3b8:	08b81a00 	ldmeq	r8!, {r9, fp, ip}
 3bc:	01240000 			@ <UNDEFINED> instruction: 0x01240000
 3c0:	01220000 			@ <UNDEFINED> instruction: 0x01220000
 3c4:	c21a0000 	andsgt	r0, sl, #0
 3c8:	34000008 	strcc	r0, [r0], #-8
 3cc:	32000001 	andcc	r0, r0, #1
 3d0:	1e000001 	cdpne	0, 0, cr0, cr0, cr1, {0}
 3d4:	100000d6 	ldrdne	r0, [r0], -r6
 3d8:	00000b4b 	andeq	r0, r0, fp, asr #22
 3dc:	03500104 	cmpeq	r0, #4, 2
 3e0:	0406010a 	streq	r0, [r6], #-266	@ 0xfffffef6
 3e4:	0c055101 	stfeqs	f5, [r5], {1}
 3e8:	3b9aca00 	blcc	fe6b2bf0 <__bss_end+0x7e6b2bc4>
 3ec:	02520104 	subseq	r0, r2, #4, 2
 3f0:	01040072 	tsteq	r4, r2, ror r0
 3f4:	00730253 	rsbseq	r0, r3, r3, asr r2
 3f8:	007d0204 	rsbseq	r0, sp, r4, lsl #4
 3fc:	04007302 	streq	r7, [r0], #-770	@ 0xfffffcfe
 400:	02047d02 	andeq	r7, r4, #2, 26	@ 0x80
 404:	02040074 	andeq	r0, r4, #116	@ 0x74
 408:	72020c7d 	andvc	r0, r2, #32000	@ 0x7d00
 40c:	00000000 	andeq	r0, r0, r0
 410:	0008cd0c 	andeq	ip, r8, ip, lsl #26
 414:	0000fa00 	andeq	pc, r0, r0, lsl #20
 418:	001e0010 	andseq	r0, lr, r0, lsl r0
 41c:	093b0000 	ldmdbeq	fp!, {}	@ <UNPREDICTABLE>
 420:	0000044b 	andeq	r0, r0, fp, asr #8
 424:	00001e13 	andeq	r1, r0, r3, lsl lr
 428:	08dd0100 	ldmeq	sp, {r8}^
 42c:	91020000 	mrsls	r0, (UNDEF: 2)
 430:	08e70d58 	stmiaeq	r7!, {r3, r4, r6, r8, sl, fp}^
 434:	002d0000 	eoreq	r0, sp, r0
 438:	e8010000 	stmda	r1, {}	@ <UNPREDICTABLE>
 43c:	01000008 	tsteq	r0, r8
 440:	08f40150 	ldmeq	r4!, {r4, r6, r8}^
 444:	51010000 	mrspl	r0, (UNDEF: 1)
 448:	0c000000 	stceq	0, cr0, [r0], {-0}
 44c:	0000075b 	andeq	r0, r0, fp, asr r7
 450:	10000106 	andne	r0, r0, r6, lsl #2
 454:	00003900 	andeq	r3, r0, r0, lsl #18
 458:	86093b00 	strhi	r3, [r9], -r0, lsl #22
 45c:	13000004 	movwne	r0, #4
 460:	00000039 	andeq	r0, r0, r9, lsr r0
 464:	00076b01 	andeq	r6, r7, r1, lsl #22
 468:	58910200 	ldmpl	r1, {r9}
 46c:	0007750d 	andeq	r7, r7, sp, lsl #10
 470:	00004800 	andeq	r4, r0, r0, lsl #16
 474:	07760100 	ldrbeq	r0, [r6, -r0, lsl #2]!
 478:	50010000 	andpl	r0, r1, r0
 47c:	00078201 	andeq	r8, r7, r1, lsl #4
 480:	00510100 	subseq	r0, r1, r0, lsl #2
 484:	020c0000 	andeq	r0, ip, #0
 488:	12000009 	andne	r0, r0, #9
 48c:	00100001 	andseq	r0, r0, r1
 490:	00000054 	andeq	r0, r0, r4, asr r0
 494:	04c1093b 	strbeq	r0, [r1], #2363	@ 0x93b
 498:	54130000 	ldrpl	r0, [r3], #-0
 49c:	01000000 	mrseq	r0, (UNDEF: 0)
 4a0:	00000912 	andeq	r0, r0, r2, lsl r9
 4a4:	0d589102 	ldfeqp	f1, [r8, #-8]
 4a8:	0000091c 	andeq	r0, r0, ip, lsl r9
 4ac:	00000063 	andeq	r0, r0, r3, rrx
 4b0:	00091d01 	andeq	r1, r9, r1, lsl #26
 4b4:	01500100 	cmpeq	r0, r0, lsl #2
 4b8:	00000929 	andeq	r0, r0, r9, lsr #18
 4bc:	00005101 	andeq	r5, r0, r1, lsl #2
 4c0:	07900c00 	ldreq	r0, [r0, r0, lsl #24]
 4c4:	011e0000 	tsteq	lr, r0
 4c8:	6f001000 	svcvs	0x00001000
 4cc:	3b000000 	blcc	4d4 <_mAppVer-0xffffb30>
 4d0:	0004fc09 	andeq	pc, r4, r9, lsl #24
 4d4:	006f1300 	rsbeq	r1, pc, r0, lsl #6
 4d8:	a0010000 	andge	r0, r1, r0
 4dc:	02000007 	andeq	r0, r0, #7
 4e0:	aa0d5891 	bge	35672c <_mAppVer-0xfca98d8>
 4e4:	6f000007 	svcvs	0x00000007
 4e8:	01000000 	mrseq	r0, (UNDEF: 0)
 4ec:	000007ab 	andeq	r0, r0, fp, lsr #15
 4f0:	b7015001 	strlt	r5, [r1, -r1]
 4f4:	01000007 	tsteq	r0, r7
 4f8:	00000051 	andeq	r0, r0, r1, asr r0
 4fc:	0007f50c 	andeq	pc, r7, ip, lsl #10
 500:	00014200 	andeq	r4, r1, r0, lsl #4
 504:	007b0110 	rsbseq	r0, fp, r0, lsl r1
 508:	123c0000 	eorsne	r0, ip, #0
 50c:	00000536 	andeq	r0, r0, r6, lsr r5
 510:	00080503 	andeq	r0, r8, r3, lsl #10
 514:	00014000 	andeq	r4, r1, r0
 518:	00013e00 	andeq	r3, r1, r0, lsl #28
 51c:	080f0d00 	stmdaeq	pc, {r8, sl, fp}	@ <UNPREDICTABLE>
 520:	00870000 	addeq	r0, r7, r0
 524:	10010000 	andne	r0, r1, r0
 528:	01000008 	tsteq	r0, r8
 52c:	081c0150 	ldmdaeq	ip, {r4, r6, r8}
 530:	51010000 	mrspl	r0, (UNDEF: 1)
 534:	471b0000 	ldrmi	r0, [fp, -r0]
 538:	8200000a 	andhi	r0, r0, #10
 53c:	06100001 	ldreq	r0, [r0], -r1
 540:	10000182 	andne	r0, r0, r2, lsl #3
 544:	0000000c 	andeq	r0, r0, ip
 548:	05a00f41 	streq	r0, [r0, #3905]!	@ 0xf41
 54c:	57030000 	strpl	r0, [r3, -r0]
 550:	4c00000a 	stcmi	0, cr0, [r0], {10}
 554:	4a000001 	bmi	560 <_mAppVer-0xffffaa4>
 558:	03000001 	movweq	r0, #1
 55c:	00000a6f 	andeq	r0, r0, pc, ror #20
 560:	0000015a 	andeq	r0, r0, sl, asr r1
 564:	00000158 	andeq	r0, r0, r8, asr r1
 568:	000a6303 	andeq	r6, sl, r3, lsl #6
 56c:	00016b00 	andeq	r6, r1, r0, lsl #22
 570:	00016700 	andeq	r6, r1, r0, lsl #14
 574:	0a7b0e00 	beq	1ec3d7c <_mAppVer-0xe13c288>
 578:	01820000 	orreq	r0, r2, r0
 57c:	000c1000 	andeq	r1, ip, r0
 580:	7c010000 	stcvc	0, cr0, [r1], {-0}
 584:	0100000a 	tsteq	r0, sl
 588:	0a880150 	beq	fe200ad0 <__bss_end+0x7e200aa4>
 58c:	51010000 	mrspl	r0, (UNDEF: 1)
 590:	000a9401 	andeq	r9, sl, r1, lsl #8
 594:	01520100 	cmpeq	r2, r0, lsl #2
 598:	00000aa0 	andeq	r0, r0, r0, lsr #21
 59c:	00005301 	andeq	r5, r0, r1, lsl #6
 5a0:	0007c51b 	andeq	ip, r7, fp, lsl r5
 5a4:	00019000 	andeq	r9, r1, r0
 5a8:	01900110 	orrseq	r0, r0, r0, lsl r1
 5ac:	00081000 	andeq	r1, r8, r0
 5b0:	0d420000 	stcleq	0, cr0, [r2, #-0]
 5b4:	000005e2 	andeq	r0, r0, r2, ror #11
 5b8:	0007cf03 	andeq	ip, r7, r3, lsl #30
 5bc:	00017d00 	andeq	r7, r1, r0, lsl #26
 5c0:	00017b00 	andeq	r7, r1, r0, lsl #22
 5c4:	07da0e00 	ldrbeq	r0, [sl, r0, lsl #28]
 5c8:	01900000 	orrseq	r0, r0, r0
 5cc:	00081000 	andeq	r1, r8, r0
 5d0:	db010000 	blle	405d8 <_mAppVer-0xffbfa2c>
 5d4:	01000007 	tsteq	r0, r7
 5d8:	07e70150 	ubfxeq	r0, r0, #2, #8
 5dc:	51010000 	mrspl	r0, (UNDEF: 1)
 5e0:	2a1b0000 	bcs	6c05e8 <_mAppVer-0xf93fa1c>
 5e4:	a8000008 	stmdage	r0, {r3}
 5e8:	01100001 	tsteq	r0, r1
 5ec:	100001a8 	andne	r0, r0, r8, lsr #3
 5f0:	00000006 	andeq	r0, r0, r6
 5f4:	06240d44 	strteq	r0, [r4], -r4, asr #26
 5f8:	3a030000 	bcc	c0600 <_mAppVer-0xff3fa04>
 5fc:	88000008 	stmdahi	r0, {r3}
 600:	86000001 	strhi	r0, [r0], -r1
 604:	0e000001 	cdpeq	0, 0, cr0, cr0, cr1, {0}
 608:	00000846 	andeq	r0, r0, r6, asr #16
 60c:	100001a8 	andne	r0, r0, r8, lsr #3
 610:	00000006 	andeq	r0, r0, r6
 614:	00084701 	andeq	r4, r8, r1, lsl #14
 618:	01500100 	cmpeq	r0, r0, lsl #2
 61c:	00000853 	andeq	r0, r0, r3, asr r8
 620:	00005101 	andeq	r5, r0, r1, lsl #2
 624:	0007c50c 	andeq	ip, r7, ip, lsl #10
 628:	0001c400 	andeq	ip, r1, r0, lsl #8
 62c:	00930110 	addseq	r0, r3, r0, lsl r1
 630:	0d480000 	stcleq	0, cr0, [r8, #-0]
 634:	0000065e 	andeq	r0, r0, lr, asr r6
 638:	0007cf03 	andeq	ip, r7, r3, lsl #30
 63c:	00019600 	andeq	r9, r1, r0, lsl #12
 640:	00019200 	andeq	r9, r1, r0, lsl #4
 644:	07da0d00 	ldrbeq	r0, [sl, r0, lsl #26]
 648:	009f0000 	addseq	r0, pc, r0
 64c:	db010000 	blle	40654 <_mAppVer-0xffbf9b0>
 650:	01000007 	tsteq	r0, r7
 654:	07e70150 	ubfxeq	r0, r0, #2, #8
 658:	51010000 	mrspl	r0, (UNDEF: 1)
 65c:	ec300000 	ldc	0, cr0, [r0], #-0
 660:	37100000 	ldrcc	r0, [r0, -r0]
 664:	72000009 	andvc	r0, r0, #9
 668:	04000006 	streq	r0, [r0], #-6
 66c:	08025001 	stmdaeq	r2, {r0, ip, lr}
 670:	421e0049 	andsmi	r0, lr, #73	@ 0x49
 674:	37100001 	ldrcc	r0, [r0, -r1]
 678:	04000009 	streq	r0, [r0], #-9
 67c:	08025001 	stmdaeq	r2, {r0, ip, lr}
 680:	7d020449 	cfstrsvc	mvf0, [r2, #-292]	@ 0xfffffedc
 684:	06a50300 	strteq	r0, [r5], r0, lsl #6
 688:	7d020426 	cfstrsvc	mvf0, [r2, #-152]	@ 0xffffff68
 68c:	0aa50308 	beq	fe9412b4 <__bss_end+0x7e941288>
 690:	7d020426 	cfstrsvc	mvf0, [r2, #-152]	@ 0xffffff68
 694:	4ea50310 	mcrmi	3, 5, r0, cr5, cr0, {0}
 698:	7d020426 	cfstrsvc	mvf0, [r2, #-152]	@ 0xffffff68
 69c:	4ca50318 	stcmi	3, cr0, [r5], #96	@ 0x60
 6a0:	0a000026 	beq	740 <_mAppVer-0xffff8c4>
 6a4:	0000023b 	andeq	r0, r0, fp, lsr r2
 6a8:	0001dd0a 	andeq	sp, r1, sl, lsl #26
 6ac:	026b0a00 	rsbeq	r0, fp, #0, 20
 6b0:	04180000 	ldreq	r0, [r8], #-0
 6b4:	01000002 	tsteq	r0, r2
 6b8:	00540d2a 	subseq	r0, r4, sl, lsr #26
 6bc:	00101000 	andseq	r1, r0, r0
 6c0:	9c010000 	stcls	0, cr0, [r1], {-0}
 6c4:	000006d9 	ldrdeq	r0, [r0], -r9
 6c8:	00006031 	andeq	r6, r0, r1, lsr r0
 6cc:	00093710 	andeq	r3, r9, r0, lsl r7
 6d0:	50010400 	andpl	r0, r1, r0, lsl #8
 6d4:	00440802 	subeq	r0, r4, r2, lsl #16
 6d8:	009e3200 	addseq	r3, lr, r0, lsl #4
 6dc:	22010000 	andcs	r0, r1, #0
 6e0:	0001950d 	andeq	r9, r1, sp, lsl #10
 6e4:	00006400 	andeq	r6, r0, r0, lsl #8
 6e8:	00002c10 	andeq	r2, r0, r0, lsl ip
 6ec:	5b9c0100 	blpl	fe700af4 <__bss_end+0x7e700ac8>
 6f0:	16000007 	strne	r0, [r0], -r7
 6f4:	000000e7 	andeq	r0, r0, r7, ror #1
 6f8:	e5212201 	str	r2, [r1, #-513]!	@ 0xfffffdff
 6fc:	ad000000 	stcge	0, cr0, [r0, #-0]
 700:	a7000001 	strge	r0, [r0, -r1]
 704:	1f000001 	svcne	0x00000001
 708:	00000aae 	andeq	r0, r0, lr, lsr #21
 70c:	10000078 	andne	r0, r0, r8, ror r0
 710:	00007801 	andeq	r7, r0, r1, lsl #16
 714:	00000810 	andeq	r0, r0, r0, lsl r8
 718:	0c270100 	stfeqs	f0, [r7], #-0
 71c:	000ac903 	andeq	ip, sl, r3, lsl #18
 720:	0001c700 	andeq	ip, r1, r0, lsl #14
 724:	0001c500 	andeq	ip, r1, r0, lsl #10
 728:	0abe0300 	beq	fef81330 <__bss_end+0x7ef81304>
 72c:	01d90000 	bicseq	r0, r9, r0
 730:	01d30000 	bicseq	r0, r3, r0
 734:	d50e0000 	strle	r0, [lr, #-0]
 738:	7800000a 	stmdavc	r0, {r1, r3}
 73c:	08100000 	ldmdaeq	r0, {}	@ <UNPREDICTABLE>
 740:	01000000 	mrseq	r0, (UNDEF: 0)
 744:	00000ad6 	ldrdeq	r0, [r0], -r6
 748:	e2015001 	and	r5, r1, #1
 74c:	0100000a 	tsteq	r0, sl
 750:	0aee0151 	beq	ffb80c9c <__bss_end+0x7fb80c70>
 754:	52010000 	andpl	r0, r1, #0
 758:	09000000 	stmdbeq	r0, {}	@ <UNPREDICTABLE>
 75c:	0000014b 	andeq	r0, r0, fp, asr #2
 760:	f618e302 			@ <UNDEFINED> instruction: 0xf618e302
 764:	90000000 	andls	r0, r0, r0
 768:	0f000007 	svceq	0x00000007
 76c:	00000374 	andeq	r0, r0, r4, ror r3
 770:	0000f6e5 	andeq	pc, r0, r5, ror #13
 774:	5f020700 	svcpl	0x00020700
 778:	02003072 	andeq	r3, r0, #114	@ 0x72
 77c:	00e505e6 	rsceq	r0, r5, r6, ror #11
 780:	5f020000 	svcpl	0x00020000
 784:	02003172 	andeq	r3, r0, #-2147483620	@ 0x8000001c
 788:	00e505e6 	rsceq	r0, r5, r6, ror #11
 78c:	00000000 	andeq	r0, r0, r0
 790:	0001bb09 	andeq	fp, r1, r9, lsl #22
 794:	18dc0200 	ldmne	ip, {r9}^
 798:	000000f6 	strdeq	r0, [r0], -r6
 79c:	000007c5 	andeq	r0, r0, r5, asr #15
 7a0:	0003740f 	andeq	r7, r3, pc, lsl #8
 7a4:	00f6de00 	rscseq	sp, r6, r0, lsl #28
 7a8:	02070000 	andeq	r0, r7, #0
 7ac:	0030725f 	eorseq	r7, r0, pc, asr r2
 7b0:	e505df02 	str	sp, [r5, #-3842]	@ 0xfffff0fe
 7b4:	02000000 	andeq	r0, r0, #0
 7b8:	0031725f 	eorseq	r7, r1, pc, asr r2
 7bc:	e505df02 	str	sp, [r5, #-3842]	@ 0xfffff0fe
 7c0:	00000000 	andeq	r0, r0, r0
 7c4:	00922000 	addseq	r2, r2, r0
 7c8:	f5c30000 			@ <UNDEFINED> instruction: 0xf5c30000
 7cc:	14000007 	strne	r0, [r0], #-7
 7d0:	00727470 	rsbseq	r7, r2, r0, ror r4
 7d4:	00a326c3 	adceq	r2, r3, r3, asr #13
 7d8:	02070000 	andeq	r0, r7, #0
 7dc:	0030725f 	eorseq	r7, r0, pc, asr r2
 7e0:	e50bc502 	str	ip, [fp, #-1282]	@ 0xfffffafe
 7e4:	02000000 	andeq	r0, r0, #0
 7e8:	0031725f 	eorseq	r7, r1, pc, asr r2
 7ec:	e50bc502 	str	ip, [fp, #-1282]	@ 0xfffffafe
 7f0:	00000000 	andeq	r0, r0, r0
 7f4:	03d10900 	bicseq	r0, r1, #0, 18
 7f8:	be020000 	cdplt	0, 0, cr0, cr2, cr0, {0}
 7fc:	0000a315 	andeq	sl, r0, r5, lsl r3
 800:	00082a00 	andeq	r2, r8, r0, lsl #20
 804:	7a731400 	bvc	1cc580c <_mAppVer-0xe33a7f8>
 808:	e52bbe00 	str	fp, [fp, #-3584]!	@ 0xfffff200
 80c:	07000000 	streq	r0, [r0, -r0]
 810:	30725f02 	rsbscc	r5, r2, r2, lsl #30
 814:	13c00200 	bicne	r0, r0, #0, 4
 818:	000000e5 	andeq	r0, r0, r5, ror #1
 81c:	31725f02 	cmncc	r2, r2, lsl #30
 820:	13c00200 	bicne	r0, r0, #0, 4
 824:	000000e5 	andeq	r0, r0, r5, ror #1
 828:	91090000 	mrsls	r0, (UNDEF: 9)
 82c:	02000001 	andeq	r0, r0, #1
 830:	019514b9 			@ <UNDEFINED> instruction: 0x019514b9
 834:	08610000 	stmdaeq	r1!, {}^	@ <UNPREDICTABLE>
 838:	25060000 	strcs	r0, [r6, #-0]
 83c:	02000004 	andeq	r0, r0, #4
 840:	00e52fb9 	strhteq	r2, [r5], #249	@ 0xf9
 844:	02070000 	andeq	r0, r7, #0
 848:	0030725f 	eorseq	r7, r0, pc, asr r2
 84c:	e50cbb02 	str	fp, [ip, #-2818]	@ 0xfffff4fe
 850:	02000000 	andeq	r0, r0, #0
 854:	0031725f 	eorseq	r7, r1, pc, asr r2
 858:	e50cbb02 	str	fp, [ip, #-2818]	@ 0xfffff4fe
 85c:	00000000 	andeq	r0, r0, r0
 860:	01050900 	tsteq	r5, r0, lsl #18
 864:	b1020000 	mrslt	r0, (UNDEF: 2)
 868:	0000e518 	andeq	lr, r0, r8, lsl r5
 86c:	0008cd00 	andeq	ip, r8, r0, lsl #26
 870:	00d00600 	sbcseq	r0, r0, r0, lsl #12
 874:	b1020000 	mrslt	r0, (UNDEF: 2)
 878:	0000f630 	andeq	pc, r0, r0, lsr r6	@ <UNPREDICTABLE>
 87c:	03910600 	orrseq	r0, r1, #0, 12
 880:	b1020000 	mrslt	r0, (UNDEF: 2)
 884:	0000e541 	andeq	lr, r0, r1, asr #10
 888:	00060600 	andeq	r0, r6, r0, lsl #12
 88c:	b1020000 	mrslt	r0, (UNDEF: 2)
 890:	0000e555 	andeq	lr, r0, r5, asr r5
 894:	69741400 	ldmdbvs	r4!, {sl, ip}^
 898:	68b10064 	ldmvs	r1!, {r2, r5, r6}
 89c:	000000e5 	andeq	r0, r0, r5, ror #1
 8a0:	00044e06 	andeq	r4, r4, r6, lsl #28
 8a4:	73b10200 			@ <UNDEFINED> instruction: 0x73b10200
 8a8:	000000a3 	andeq	r0, r0, r3, lsr #1
 8ac:	00048106 	andeq	r8, r4, r6, lsl #2
 8b0:	80b10200 	adcshi	r0, r1, r0, lsl #4
 8b4:	00000195 	muleq	r0, r5, r1
 8b8:	0000890f 	andeq	r8, r0, pc, lsl #18
 8bc:	00e5b300 	rsceq	fp, r5, r0, lsl #6
 8c0:	250f0000 	strcs	r0, [pc, #-0]	@ 8c8 <_mAppVer-0xffff73c>
 8c4:	b4000000 	strlt	r0, [r0], #-0
 8c8:	000000e5 	andeq	r0, r0, r5, ror #1
 8cc:	04170900 	ldreq	r0, [r7], #-2304	@ 0xfffff700
 8d0:	aa020000 	bge	808d8 <_mAppVer-0xff7f72c>
 8d4:	0000f618 	andeq	pc, r0, r8, lsl r6	@ <UNPREDICTABLE>
 8d8:	00090200 	andeq	r0, r9, r0, lsl #4
 8dc:	03740f00 	cmneq	r4, #0, 30
 8e0:	f6ac0000 			@ <UNDEFINED> instruction: 0xf6ac0000
 8e4:	07000000 	streq	r0, [r0, -r0]
 8e8:	30725f02 	rsbscc	r5, r2, r2, lsl #30
 8ec:	05ad0200 	streq	r0, [sp, #512]!	@ 0x200
 8f0:	000000e5 	andeq	r0, r0, r5, ror #1
 8f4:	31725f02 	cmncc	r2, r2, lsl #30
 8f8:	05ad0200 	streq	r0, [sp, #512]!	@ 0x200
 8fc:	000000e5 	andeq	r0, r0, r5, ror #1
 900:	a3090000 	movwge	r0, #36864	@ 0x9000
 904:	02000001 	andeq	r0, r0, #1
 908:	00f6189e 	smlalseq	r1, r6, lr, r8
 90c:	09370000 	ldmdbeq	r7!, {}	@ <UNPREDICTABLE>
 910:	740f0000 	strvc	r0, [pc], #-0	@ 918 <_mAppVer-0xffff6ec>
 914:	a0000003 	andge	r0, r0, r3
 918:	000000f6 	strdeq	r0, [r0], -r6
 91c:	725f0207 	subsvc	r0, pc, #1879048192	@ 0x70000000
 920:	a1020030 	tstge	r2, r0, lsr r0
 924:	0000e505 	andeq	lr, r0, r5, lsl #10
 928:	725f0200 	subsvc	r0, pc, #0, 4
 92c:	a1020031 	tstge	r2, r1, lsr r0
 930:	0000e505 	andeq	lr, r0, r5, lsl #10
 934:	18000000 	stmdane	r0, {}	@ <UNPREDICTABLE>
 938:	0000006f 	andeq	r0, r0, pc, rrx
 93c:	38145a02 	ldmdacc	r4, {r1, r9, fp, ip, lr}
 940:	1a100000 	bne	400948 <_mAppVer-0xfbff6bc>
 944:	01000000 	mrseq	r0, (UNDEF: 0)
 948:	0009e79c 	muleq	r9, ip, r7
 94c:	042d1600 	strteq	r1, [sp], #-1536	@ 0xfffffa00
 950:	5a020000 	bpl	80958 <_mAppVer-0xff7f6ac>
 954:	0001e229 	andeq	lr, r1, r9, lsr #4
 958:	0001f500 	andeq	pc, r1, r0, lsl #10
 95c:	0001f100 	andeq	pc, r1, r0, lsl #2
 960:	74733300 	ldrbtvc	r3, [r3], #-768	@ 0xfffffd00
 964:	5a020072 	bpl	80b34 <_mAppVer-0xff7f4d0>
 968:	0000ce3c 	andeq	ip, r0, ip, lsr lr
 96c:	74910200 	ldrvc	r0, [r1], #512	@ 0x200
 970:	6c761d1c 	ldclvs	13, cr1, [r6], #-112	@ 0xffffff90
 974:	0d5c0200 	lfmeq	f0, 2, [ip, #-0]
 978:	0000011a 	andeq	r0, r0, sl, lsl r1
 97c:	1f6c9102 	svcne	0x006c9102
 980:	000009e7 	andeq	r0, r0, r7, ror #19
 984:	10000046 	andne	r0, r0, r6, asr #32
 988:	00004601 	andeq	r4, r0, r1, lsl #12
 98c:	00000610 	andeq	r0, r0, r0, lsl r6
 990:	055f0200 	ldrbeq	r0, [pc, #-512]	@ 798 <_mAppVer-0xffff86c>
 994:	000a0803 	andeq	r0, sl, r3, lsl #16
 998:	00020c00 	andeq	r0, r2, r0, lsl #24
 99c:	00020800 	andeq	r0, r2, r0, lsl #16
 9a0:	09fd0300 	ldmibeq	sp!, {r8, r9}^
 9a4:	02220000 	eoreq	r0, r2, #0
 9a8:	021e0000 	andseq	r0, lr, #0
 9ac:	f1030000 			@ <UNDEFINED> instruction: 0xf1030000
 9b0:	36000009 	strcc	r0, [r0], -r9
 9b4:	34000002 	strcc	r0, [r0], #-2
 9b8:	0e000002 	cdpeq	0, 0, cr0, cr0, cr2, {0}
 9bc:	00000a14 	andeq	r0, r0, r4, lsl sl
 9c0:	10000046 	andne	r0, r0, r6, asr #32
 9c4:	00000006 	andeq	r0, r0, r6
 9c8:	000a1501 	andeq	r1, sl, r1, lsl #10
 9cc:	01500100 	cmpeq	r0, r0, lsl #2
 9d0:	00000a21 	andeq	r0, r0, r1, lsr #20
 9d4:	2d015101 	stfcss	f5, [r1, #-4]
 9d8:	0100000a 	tsteq	r0, sl
 9dc:	0a390152 	beq	e40f2c <_mAppVer-0xf1bf0d8>
 9e0:	53010000 	movwpl	r0, #4096	@ 0x1000
 9e4:	20000000 	andcs	r0, r0, r0
 9e8:	000003ab 	andeq	r0, r0, fp, lsr #7
 9ec:	000a4750 	andeq	r4, sl, r0, asr r7
 9f0:	042d0600 	strteq	r0, [sp], #-1536	@ 0xfffffa00
 9f4:	50020000 	andpl	r0, r2, r0
 9f8:	0001e232 	andeq	lr, r1, r2, lsr r2
 9fc:	74731400 	ldrbtvc	r1, [r3], #-1024	@ 0xfffffc00
 a00:	45500072 	ldrbmi	r0, [r0, #-114]	@ 0xffffff8e
 a04:	000000ce 	andeq	r0, r0, lr, asr #1
 a08:	00007606 	andeq	r7, r0, r6, lsl #12
 a0c:	54500200 	ldrbpl	r0, [r0], #-512	@ 0xfffffe00
 a10:	00000102 	andeq	r0, r0, r2, lsl #2
 a14:	725f0207 	subsvc	r0, pc, #1879048192	@ 0x70000000
 a18:	52020030 	andpl	r0, r2, #48	@ 0x30
 a1c:	0000e50b 	andeq	lr, r0, fp, lsl #10
 a20:	725f0200 	subsvc	r0, pc, #0, 4
 a24:	52020031 	andpl	r0, r2, #49	@ 0x31
 a28:	0000e50b 	andeq	lr, r0, fp, lsl #10
 a2c:	725f0200 	subsvc	r0, pc, #0, 4
 a30:	52020032 	andpl	r0, r2, #50	@ 0x32
 a34:	0000e50b 	andeq	lr, r0, fp, lsl #10
 a38:	725f0200 	subsvc	r0, pc, #0, 4
 a3c:	52020033 	andpl	r0, r2, #51	@ 0x33
 a40:	0000e50b 	andeq	lr, r0, fp, lsl #10
 a44:	09000000 	stmdbeq	r0, {}	@ <UNPREDICTABLE>
 a48:	00000042 	andeq	r0, r0, r2, asr #32
 a4c:	95143402 	ldrls	r3, [r4, #-1026]	@ 0xfffffbfe
 a50:	ae000001 	cdpge	0, 0, cr0, cr0, cr1, {0}
 a54:	0600000a 	streq	r0, [r0], -sl
 a58:	000000a9 	andeq	r0, r0, r9, lsr #1
 a5c:	e52b3402 	str	r3, [fp, #-1026]!	@ 0xfffffbfe
 a60:	06000000 	streq	r0, [r0], -r0
 a64:	00000455 	andeq	r0, r0, r5, asr r4
 a68:	a33a3402 	teqge	sl, #33554432	@ 0x2000000
 a6c:	06000000 	streq	r0, [r0], -r0
 a70:	00000127 	andeq	r0, r0, r7, lsr #2
 a74:	e54c3402 	strb	r3, [ip, #-1026]	@ 0xfffffbfe
 a78:	07000000 	streq	r0, [r0, -r0]
 a7c:	30725f02 	rsbscc	r5, r2, r2, lsl #30
 a80:	0c360200 	lfmeq	f0, 4, [r6], #-0
 a84:	000000e5 	andeq	r0, r0, r5, ror #1
 a88:	31725f02 	cmncc	r2, r2, lsl #30
 a8c:	0c360200 	lfmeq	f0, 4, [r6], #-0
 a90:	000000e5 	andeq	r0, r0, r5, ror #1
 a94:	32725f02 	rsbscc	r5, r2, #2, 30
 a98:	0c360200 	lfmeq	f0, 4, [r6], #-0
 a9c:	000000e5 	andeq	r0, r0, r5, ror #1
 aa0:	33725f02 	cmncc	r2, #2, 30
 aa4:	0c360200 	lfmeq	f0, 4, [r6], #-0
 aa8:	000000e5 	andeq	r0, r0, r5, ror #1
 aac:	5d090000 	stcpl	0, cr0, [r9, #-0]
 ab0:	02000004 	andeq	r0, r0, #4
 ab4:	0195142a 	orrseq	r1, r5, sl, lsr #8
 ab8:	0afc0000 	beq	fff00ac0 <__bss_end+0x7ff00a94>
 abc:	74140000 	ldrvc	r0, [r4], #-0
 ac0:	2a006469 	bcs	19c6c <_mAppVer-0xffe6398>
 ac4:	0000e52f 	andeq	lr, r0, pc, lsr #10
 ac8:	00a90600 	adceq	r0, r9, r0, lsl #12
 acc:	2a020000 	bcs	80ad4 <_mAppVer-0xff7f530>
 ad0:	0000e53d 	andeq	lr, r0, sp, lsr r5
 ad4:	5f020700 	svcpl	0x00020700
 ad8:	02003072 	andeq	r3, r0, #114	@ 0x72
 adc:	00e50c2c 	rsceq	r0, r5, ip, lsr #24
 ae0:	5f020000 	svcpl	0x00020000
 ae4:	02003172 	andeq	r3, r0, #-2147483620	@ 0x8000001c
 ae8:	00e50c2c 	rsceq	r0, r5, ip, lsr #24
 aec:	5f020000 	svcpl	0x00020000
 af0:	02003272 	andeq	r3, r0, #536870919	@ 0x20000007
 af4:	00e50c2c 	rsceq	r0, r5, ip, lsr #24
 af8:	00000000 	andeq	r0, r0, r0
 afc:	0003c009 	andeq	ip, r3, r9
 b00:	19170300 	ldmdbne	r7, {r8, r9}
 b04:	00000102 	andeq	r0, r0, r2, lsl #2
 b08:	00000b4b 	andeq	r0, r0, fp, asr #22
 b0c:	0000dd06 	andeq	sp, r0, r6, lsl #26
 b10:	33170300 	tstcc	r7, #0, 6
 b14:	000000e5 	andeq	r0, r0, r5, ror #1
 b18:	6572021c 	ldrbvs	r0, [r2, #-540]!	@ 0xfffffde4
 b1c:	19030074 	stmdbne	r3, {r2, r4, r5, r6}
 b20:	0001020f 	andeq	r0, r1, pc, lsl #4
 b24:	6c760200 	lfmvs	f0, 2, [r6], #-0
 b28:	0d1a0300 	ldceq	3, cr0, [sl, #-0]
 b2c:	0000011a 	andeq	r0, r0, sl, lsl r1
 b30:	725f0207 	subsvc	r0, pc, #1879048192	@ 0x70000000
 b34:	20030030 	andcs	r0, r3, r0, lsr r0
 b38:	0000e50f 	andeq	lr, r0, pc, lsl #10
 b3c:	725f0200 	subsvc	r0, pc, #0, 4
 b40:	20030031 	andcs	r0, r3, r1, lsr r0
 b44:	0000e50f 	andeq	lr, r0, pc, lsl #10
 b48:	34000000 	strcc	r0, [r0], #-0
 b4c:	00000afc 	strdeq	r0, [r0], -ip
 b50:	10000090 	mulne	r0, r0, r0
 b54:	00000014 	andeq	r0, r0, r4, lsl r0
 b58:	0c359c01 	ldceq	12, cr9, [r5], #-4
 b5c:	0200000b 	andeq	r0, r0, #11
 b60:	1a1c7091 	bne	71cdac <_mAppVer-0xf8e3258>
 b64:	00000b19 	andeq	r0, r0, r9, lsl fp
 b68:	00000241 	andeq	r0, r0, r1, asr #4
 b6c:	0000023f 	andeq	r0, r0, pc, lsr r2
 b70:	000b2501 	andeq	r2, fp, r1, lsl #10
 b74:	6c910200 	lfmvs	f0, 4, [r1], {0}
 b78:	000b0c36 	andeq	r0, fp, r6, lsr ip
 b7c:	0e060100 	adfeqs	f0, f6, f0
 b80:	00000b30 	andeq	r0, r0, r0, lsr fp
 b84:	10000098 	mulne	r0, r8, r0
 b88:	00000006 	andeq	r0, r0, r6
 b8c:	000b3101 	andeq	r3, fp, r1, lsl #2
 b90:	01500100 	cmpeq	r0, r0, lsl #2
 b94:	00000b3d 	andeq	r0, r0, sp, lsr fp
 b98:	00005101 	andeq	r5, r0, r1, lsl #2
	...

Disassembly of section .debug_abbrev:

00000000 <.debug_abbrev>:
   0:	31003401 	tstcc	r0, r1, lsl #8
   4:	00180213 	andseq	r0, r8, r3, lsl r2
   8:	00340200 	eorseq	r0, r4, r0, lsl #4
   c:	0b3a0803 	bleq	e82020 <_mAppVer-0xf17dfe4>
  10:	0b390b3b 	bleq	e42d04 <_mAppVer-0xf1bd300>
  14:	00001349 	andeq	r1, r0, r9, asr #6
  18:	31000503 	tstcc	r0, r3, lsl #10
  1c:	b7170213 			@ <UNDEFINED> instruction: 0xb7170213
  20:	00001742 	andeq	r1, r0, r2, asr #14
  24:	02004904 	andeq	r4, r0, #4, 18	@ 0x10000
  28:	00187e18 	andseq	r7, r8, r8, lsl lr
  2c:	00240500 	eoreq	r0, r4, r0, lsl #10
  30:	0b3e0b0b 	bleq	f82c64 <_mAppVer-0xf07d3a0>
  34:	00000e03 	andeq	r0, r0, r3, lsl #28
  38:	03000506 	movweq	r0, #1286	@ 0x506
  3c:	3b0b3a0e 	blcc	2ce87c <_mAppVer-0xfd31788>
  40:	490b390b 	stmdbmi	fp, {r0, r1, r3, r8, fp, ip, sp}
  44:	07000013 	smladeq	r0, r3, r0, r0
  48:	0000010b 	andeq	r0, r0, fp, lsl #2
  4c:	03001608 	movweq	r1, #1544	@ 0x608
  50:	3b0b3a0e 	blcc	2ce890 <_mAppVer-0xfd31774>
  54:	490b390b 	stmdbmi	fp, {r0, r1, r3, r8, fp, ip, sp}
  58:	09000013 	stmdbeq	r0, {r0, r1, r4}
  5c:	0e03012e 	adfeqsp	f0, f3, #0.5
  60:	0b3b0b3a 	bleq	ec2d50 <_mAppVer-0xf13d2b4>
  64:	19270b39 	stmdbne	r7!, {r0, r3, r4, r5, r8, r9, fp}
  68:	21201349 			@ <UNDEFINED> instruction: 0x21201349
  6c:	00130103 	andseq	r0, r3, r3, lsl #2
  70:	000f0a00 	andeq	r0, pc, r0, lsl #20
  74:	4904210b 	stmdbmi	r4, {r0, r1, r3, r8, sp}
  78:	0b000013 	bleq	cc <_mAppVer-0xfffff38>
  7c:	0e03000d 	cdpeq	0, 0, cr0, cr3, cr13, {0}
  80:	0b3b0b3a 	bleq	ec2d70 <_mAppVer-0xf13d294>
  84:	13490b39 	movtne	r0, #39737	@ 0x9b39
  88:	00000b38 	andeq	r0, r0, r8, lsr fp
  8c:	31011d0c 	tstcc	r1, ip, lsl #26
  90:	b8015213 	stmdalt	r1, {r0, r1, r4, r9, ip, lr}
  94:	17550b42 	ldrbne	r0, [r5, -r2, asr #22]
  98:	59012158 	stmdbpl	r1, {r3, r4, r6, r8, sp}
  9c:	010b570b 	tsteq	fp, fp, lsl #14
  a0:	0d000013 	stceq	0, cr0, [r0, #-76]	@ 0xffffffb4
  a4:	1331010b 	teqne	r1, #-1073741822	@ 0xc0000002
  a8:	00001755 	andeq	r1, r0, r5, asr r7
  ac:	31010b0e 	tstcc	r1, lr, lsl #22
  b0:	12011113 	andne	r1, r1, #-1073741820	@ 0xc0000004
  b4:	0f000006 	svceq	0x00000006
  b8:	0e030034 	mcreq	0, 0, r0, cr3, cr4, {1}
  bc:	3b02213a 	blcc	885ac <_mAppVer-0xff77a58>
  c0:	0e21390b 	vmuleq.f16	s6, s2, s22	@ <UNPREDICTABLE>
  c4:	00001349 	andeq	r1, r0, r9, asr #6
  c8:	49002610 	stmdbmi	r0, {r4, r9, sl, sp}
  cc:	11000013 	tstne	r0, r3, lsl r0
  d0:	0e030113 	mcreq	1, 0, r0, cr3, cr3, {0}
  d4:	0b3a0b0b 	bleq	e82d08 <_mAppVer-0xf17d2fc>
  d8:	21390b3b 	teqcs	r9, fp, lsr fp
  dc:	00130108 	andseq	r0, r3, r8, lsl #2
  e0:	00281200 	eoreq	r1, r8, r0, lsl #4
  e4:	0b1c0e03 	bleq	7038f8 <_mAppVer-0xf8fc70c>
  e8:	0b130000 	bleq	4c00f0 <_mAppVer-0xfb3ff14>
  ec:	00175501 	andseq	r5, r7, r1, lsl #10
  f0:	00051400 	andeq	r1, r5, r0, lsl #8
  f4:	213a0803 	teqcs	sl, r3, lsl #16
  f8:	390b3b02 	stmdbcc	fp, {r1, r8, r9, fp, ip, sp}
  fc:	0013490b 	andseq	r4, r3, fp, lsl #18
 100:	000d1500 	andeq	r1, sp, r0, lsl #10
 104:	0b3a0803 	bleq	e82118 <_mAppVer-0xf17deec>
 108:	0b390b3b 	bleq	e42dfc <_mAppVer-0xf1bd208>
 10c:	0b381349 	bleq	e04e38 <_mAppVer-0xf1fb1cc>
 110:	05160000 	ldreq	r0, [r6, #-0]
 114:	3a0e0300 	bcc	380d1c <_mAppVer-0xfc7f2e8>
 118:	390b3b0b 	stmdbcc	fp, {r0, r1, r3, r8, r9, fp, ip, sp}
 11c:	0213490b 	andseq	r4, r3, #180224	@ 0x2c000
 120:	1742b717 	smlaldne	fp, r2, r7, r7
 124:	05170000 	ldreq	r0, [r7, #-0]
 128:	00134900 	andseq	r4, r3, r0, lsl #18
 12c:	012e1800 			@ <UNDEFINED> instruction: 0x012e1800
 130:	0b3a0e03 	bleq	e83944 <_mAppVer-0xf17c6c0>
 134:	0b390b3b 	bleq	e42e28 <_mAppVer-0xf1bd1dc>
 138:	01111927 	tsteq	r1, r7, lsr #18
 13c:	18400612 	stmdane	r0, {r1, r4, r9, sl}^
 140:	1301197a 	movwne	r1, #6522	@ 0x197a
 144:	34190000 	ldrcc	r0, [r9], #-0
 148:	3a0e0300 	bcc	380d50 <_mAppVer-0xfc7f2b4>
 14c:	0b3b0121 	bleq	ec05d8 <_mAppVer-0xf13fa2c>
 150:	13490b39 	movtne	r0, #39737	@ 0x9b39
 154:	42b71702 	adcsmi	r1, r7, #524288	@ 0x80000
 158:	1a000017 	bne	1bc <_mAppVer-0xffffe48>
 15c:	13310034 	teqne	r1, #52	@ 0x34
 160:	42b71702 	adcsmi	r1, r7, #524288	@ 0x80000
 164:	1b000017 	blne	1c8 <_mAppVer-0xffffe3c>
 168:	1331011d 	teqne	r1, #1073741831	@ 0x40000007
 16c:	42b80152 	adcsmi	r0, r8, #-2147483628	@ 0x80000014
 170:	1201110b 	andne	r1, r1, #-1073741822	@ 0xc0000002
 174:	01215806 			@ <UNDEFINED> instruction: 0x01215806
 178:	0b570b59 	bleq	15c2ee4 <_mAppVer-0xea3d120>
 17c:	00001301 	andeq	r1, r0, r1, lsl #6
 180:	0000181c 	andeq	r1, r0, ip, lsl r8
 184:	00341d00 	eorseq	r1, r4, r0, lsl #26
 188:	0b3a0803 	bleq	e8219c <_mAppVer-0xf17de68>
 18c:	0b390b3b 	bleq	e42e80 <_mAppVer-0xf1bd184>
 190:	18021349 	stmdane	r2, {r0, r3, r6, r8, r9, ip}
 194:	481e0000 	ldmdami	lr, {}	@ <UNPREDICTABLE>
 198:	7f017d01 	svcvc	0x00017d01
 19c:	1f000013 	svcne	0x00000013
 1a0:	1331011d 	teqne	r1, #1073741831	@ 0x40000007
 1a4:	42b80152 	adcsmi	r0, r8, #-2147483628	@ 0x80000014
 1a8:	1201110b 	andne	r1, r1, #-1073741822	@ 0xc0000002
 1ac:	590b5806 	stmdbpl	fp, {r1, r2, fp, ip, lr}
 1b0:	000b570b 	andeq	r5, fp, fp, lsl #14
 1b4:	012e2000 			@ <UNDEFINED> instruction: 0x012e2000
 1b8:	213a0e03 	teqcs	sl, r3, lsl #28
 1bc:	390b3b02 	stmdbcc	fp, {r1, r8, r9, fp, ip, sp}
 1c0:	19271421 	stmdbne	r7!, {r0, r5, sl, ip}
 1c4:	01032120 	tsteq	r3, r0, lsr #2
 1c8:	21000013 	tstcs	r0, r3, lsl r0
 1cc:	0e250111 	mcreq	1, 1, r0, cr5, cr1, {0}
 1d0:	0e030b13 	vmoveq.32	d3[0], r0
 1d4:	17550e1b 	smmlane	r5, fp, lr, r0
 1d8:	17100111 			@ <UNDEFINED> instruction: 0x17100111
 1dc:	24220000 	strtcs	r0, [r2], #-0
 1e0:	3e0b0b00 	vmlacc.f64	d0, d11, d0
 1e4:	0008030b 	andeq	r0, r8, fp, lsl #6
 1e8:	000f2300 	andeq	r2, pc, r0, lsl #6
 1ec:	00000b0b 	andeq	r0, r0, fp, lsl #22
 1f0:	03011324 	movweq	r1, #4900	@ 0x1324
 1f4:	3a0b0b0e 	bcc	2c2e34 <_mAppVer-0xfd3d1d0>
 1f8:	010b3b0b 	tsteq	fp, fp, lsl #22
 1fc:	25000013 	strcs	r0, [r0, #-19]	@ 0xffffffed
 200:	0e03000d 	cdpeq	0, 0, cr0, cr3, cr13, {0}
 204:	0b381349 	bleq	e04f30 <_mAppVer-0xf1fb0d4>
 208:	00001934 	andeq	r1, r0, r4, lsr r9
 20c:	27001526 	strcs	r1, [r0, -r6, lsr #10]
 210:	27000019 	smladcs	r0, r9, r0, r0
 214:	00000026 	andeq	r0, r0, r6, lsr #32
 218:	27011528 	strcs	r1, [r1, -r8, lsr #10]
 21c:	01134919 	tsteq	r3, r9, lsl r9
 220:	29000013 	stmdbcs	r0, {r0, r1, r4}
 224:	19270115 	stmdbne	r7!, {r0, r2, r4, r8}
 228:	00001301 	andeq	r1, r0, r1, lsl #6
 22c:	0301042a 	movweq	r0, #5162	@ 0x142a
 230:	0b0b3e0e 	bleq	2cfa70 <_mAppVer-0xfd30594>
 234:	3a13490b 	bcc	4d2668 <_mAppVer-0xfb2d99c>
 238:	39053b0b 	stmdbcc	r5, {r0, r1, r3, r8, r9, fp, ip, sp}
 23c:	0013010b 	andseq	r0, r3, fp, lsl #2
 240:	00342b00 	eorseq	r2, r4, r0, lsl #22
 244:	0b3a0e03 	bleq	e83a58 <_mAppVer-0xf17c5ac>
 248:	0b390b3b 	bleq	e42f3c <_mAppVer-0xf1bd0c8>
 24c:	18021349 	stmdane	r2, {r0, r3, r6, r8, r9, ip}
 250:	342c0000 	strtcc	r0, [ip], #-0
 254:	3a0e0300 	bcc	380e5c <_mAppVer-0xfc7f1a8>
 258:	390b3b0b 	stmdbcc	fp, {r0, r1, r3, r8, r9, fp, ip, sp}
 25c:	3f13490b 	svccc	0x0013490b
 260:	00193c19 	andseq	r3, r9, r9, lsl ip
 264:	00342d00 	eorseq	r2, r4, r0, lsl #26
 268:	18021347 	stmdane	r2, {r0, r1, r2, r6, r8, r9, ip}
 26c:	342e0000 	strtcc	r0, [lr], #-0
 270:	3a0e0300 	bcc	380e78 <_mAppVer-0xfc7f18c>
 274:	390b3b0b 	stmdbcc	fp, {r0, r1, r3, r8, r9, fp, ip, sp}
 278:	3f13490b 	svccc	0x0013490b
 27c:	00180219 	andseq	r0, r8, r9, lsl r2
 280:	00342f00 	eorseq	r2, r4, r0, lsl #30
 284:	0b3a0803 	bleq	e82298 <_mAppVer-0xf17dd6c>
 288:	0b390b3b 	bleq	e42f7c <_mAppVer-0xf1bd088>
 28c:	17021349 	strne	r1, [r2, -r9, asr #6]
 290:	001742b7 			@ <UNDEFINED> instruction: 0x001742b7
 294:	01483000 	mrseq	r3, (UNDEF: 72)
 298:	0182017d 	orreq	r0, r2, sp, ror r1
 29c:	01137f19 	tsteq	r3, r9, lsl pc
 2a0:	31000013 	tstcc	r0, r3, lsl r0
 2a4:	017d0148 	cmneq	sp, r8, asr #2
 2a8:	7f190182 	svcvc	0x00190182
 2ac:	32000013 	andcc	r0, r0, #19
 2b0:	0e03012e 	adfeqsp	f0, f3, #0.5
 2b4:	0b3b0b3a 	bleq	ec2fa4 <_mAppVer-0xf13d060>
 2b8:	19270b39 	stmdbne	r7!, {r0, r3, r4, r5, r8, r9, fp}
 2bc:	01111349 	tsteq	r1, r9, asr #6
 2c0:	18400612 	stmdane	r0, {r1, r4, r9, sl}^
 2c4:	1301197a 	movwne	r1, #6522	@ 0x197a
 2c8:	05330000 	ldreq	r0, [r3, #-0]!
 2cc:	3a080300 	bcc	200ed4 <_mAppVer-0xfdff130>
 2d0:	390b3b0b 	stmdbcc	fp, {r0, r1, r3, r8, r9, fp, ip, sp}
 2d4:	0213490b 	andseq	r4, r3, #180224	@ 0x2c000
 2d8:	34000018 	strcc	r0, [r0], #-24	@ 0xffffffe8
 2dc:	1331012e 	teqne	r1, #-2147483637	@ 0x8000000b
 2e0:	06120111 			@ <UNDEFINED> instruction: 0x06120111
 2e4:	197a1840 	ldmdbne	sl!, {r6, fp, ip}^
 2e8:	05350000 	ldreq	r0, [r5, #-0]!
 2ec:	02133100 	andseq	r3, r3, #0, 2
 2f0:	36000018 			@ <UNDEFINED> instruction: 0x36000018
 2f4:	13310005 	teqne	r1, #5
 2f8:	0000051c 	andeq	r0, r0, ip, lsl r5
	...

Disassembly of section .debug_loclists:

00000000 <.debug_loclists>:
   0:	00000246 	andeq	r0, r0, r6, asr #4
   4:	00040005 	andeq	r0, r4, r5
	...
  18:	0000a406 	andeq	sl, r0, r6, lsl #8
  1c:	2e000410 	cfmvdlrcs	mvd0, r0
  20:	2e045001 	cdpcs	0, 0, cr5, cr4, cr1, {0}
  24:	01a30448 			@ <UNDEFINED> instruction: 0x01a30448
  28:	48049f50 	stmdami	r4, {r4, r6, r8, r9, sl, fp, ip, pc}
  2c:	04500154 	ldrbeq	r0, [r0], #-340	@ 0xfffffeac
  30:	04029254 	streq	r9, [r2], #-596	@ 0xfffffdac
  34:	9f5001a3 	svcls	0x005001a3
  38:	a6029204 	strge	r9, [r2], -r4, lsl #4
  3c:	04500102 	ldrbeq	r0, [r0], #-258	@ 0xfffffefe
  40:	02bc02a6 	adcseq	r0, ip, #1610612746	@ 0x6000000a
  44:	5001a304 	andpl	sl, r1, r4, lsl #6
  48:	0000009f 	muleq	r0, pc, r0	@ <UNPREDICTABLE>
	...
  58:	0000a406 	andeq	sl, r0, r6, lsl #8
  5c:	12000410 	andne	r0, r0, #16, 8	@ 0x10000000
  60:	12045101 	andne	r5, r4, #1073741824	@ 0x40000000
  64:	04550144 	ldrbeq	r0, [r5], #-324	@ 0xfffffebc
  68:	a3044844 	movwge	r4, #18500	@ 0x4844
  6c:	049f5101 	ldreq	r5, [pc], #257	@ 74 <_mAppVer-0xfffff90>
  70:	51015848 	tstpl	r1, r8, asr #16
  74:	02925804 	addseq	r5, r2, #4, 16	@ 0x40000
  78:	92045501 	andls	r5, r4, #4194304	@ 0x400000
  7c:	0102a202 	tsteq	r2, r2, lsl #4
  80:	02a20451 	adceq	r0, r2, #1358954496	@ 0x51000000
  84:	550102bc 	strpl	r0, [r1, #-700]	@ 0xfffffd44
  88:	00000100 	andeq	r0, r0, r0, lsl #2
  8c:	00f00602 	rscseq	r0, r0, r2, lsl #12
  90:	00041000 	andeq	r1, r4, r0
  94:	0451010c 	ldrbeq	r0, [r1], #-268	@ 0xfffffef4
  98:	0101be0c 	tsteq	r1, ip, lsl #28
  9c:	00010055 	andeq	r0, r1, r5, asr r0
  a0:	ba060000 	blt	1800a8 <_mAppVer-0xfe7ff5c>
  a4:	04100001 	ldreq	r0, [r0], #-1
  a8:	51010c00 	tstpl	r1, r0, lsl #24
  ac:	01260c04 			@ <UNDEFINED> instruction: 0x01260c04
  b0:	00000055 	andeq	r0, r0, r5, asr r0
  b4:	de060000 	cdple	0, 0, cr0, cr6, cr0, {0}
  b8:	04100000 	ldreq	r0, [r0], #-0
  bc:	50010400 	andpl	r0, r1, r0, lsl #8
  c0:	010d0404 	tsteq	sp, r4, lsl #8
  c4:	00000053 	andeq	r0, r0, r3, asr r0
  c8:	82060200 	andhi	r0, r6, #0, 4
  cc:	04100001 	ldreq	r0, [r0], #-1
  d0:	50010400 	andpl	r0, r1, r0, lsl #8
  d4:	012c0404 			@ <UNDEFINED> instruction: 0x012c0404
  d8:	00010054 	andeq	r0, r1, r4, asr r0
  dc:	0000be08 	andeq	fp, r0, r8, lsl #28
  e0:	9e0a1810 	mcrls	8, 0, r1, cr10, cr0, {0}
  e4:	9aca0008 	bls	ff28010c <__bss_end+0x7f2800e0>
  e8:	0000003b 	andeq	r0, r0, fp, lsr r0
  ec:	00010000 	andeq	r0, r1, r0
  f0:	0000be08 	andeq	fp, r0, r8, lsl #28
  f4:	08031810 	stmdaeq	r3, {r4, fp, ip}
  f8:	01009f32 	tsteq	r0, r2, lsr pc
  fc:	00be0800 	adcseq	r0, lr, r0, lsl #16
 100:	06181000 	ldreq	r1, [r8], -r0
 104:	00002403 	andeq	r2, r0, r3, lsl #8
 108:	01009f80 	smlabbeq	r0, r0, pc, r9	@ <UNPREDICTABLE>
 10c:	00be0800 	adcseq	r0, lr, r0, lsl #16
 110:	02181000 	andseq	r1, r8, #0
 114:	00009f30 	andeq	r9, r0, r0, lsr pc
 118:	00be0800 	adcseq	r0, lr, r0, lsl #16
 11c:	01181000 	tsteq	r8, r0
 120:	00020054 	andeq	r0, r2, r4, asr r0
 124:	0000be08 	andeq	fp, r0, r8, lsl #28
 128:	0c061810 	stceq	8, cr1, [r6], {16}
 12c:	3b9aca00 	blcc	fe6b2934 <__bss_end+0x7e6b2908>
 130:	0003009f 	muleq	r3, pc, r0	@ <UNPREDICTABLE>
 134:	0000be08 	andeq	fp, r0, r8, lsl #28
 138:	30021810 	andcc	r1, r2, r0, lsl r8
 13c:	0002009f 	muleq	r2, pc, r0	@ <UNPREDICTABLE>
 140:	00014208 	andeq	r4, r1, r8, lsl #4
 144:	3e024010 	mcrcc	0, 0, r4, cr2, cr0, {0}
 148:	0107009f 	swpeq	r0, pc, [r7]	@ <UNPREDICTABLE>
 14c:	00018208 	andeq	r8, r1, r8, lsl #4
 150:	0a040c10 	beq	103198 <_mAppVer-0xfefce6c>
 154:	009f0401 	addseq	r0, pc, r1, lsl #8
 158:	82080106 	andhi	r0, r8, #-2147483647	@ 0x80000001
 15c:	0c100001 	ldceq	0, cr0, [r0], {1}
 160:	00280305 	eoreq	r0, r8, r5, lsl #6
 164:	06008000 	streq	r8, [r0], -r0
 168:	06010000 	streq	r0, [r1], -r0
 16c:	10000182 	andne	r0, r0, r2, lsl #3
 170:	01040004 	tsteq	r4, r4
 174:	0c040450 	cfstrseq	mvf0, [r4], {80}	@ 0x50
 178:	01005401 	tsteq	r0, r1, lsl #8
 17c:	01900801 	orrseq	r0, r0, r1, lsl #16
 180:	01081000 	mrseq	r1, (UNDEF: 8)
 184:	02010054 	andeq	r0, r1, #84	@ 0x54
 188:	0001a808 	andeq	sl, r1, r8, lsl #16
 18c:	75020610 	strvc	r0, [r2, #-1552]	@ 0xfffff9f0
 190:	00010000 	andeq	r0, r1, r0
 194:	c4060000 	strgt	r0, [r6], #-0
 198:	04100001 	ldreq	r0, [r0], #-1
 19c:	71020200 	mrsvc	r0, R10_usr
 1a0:	1c020404 	cfstrsne	mvf0, [r2], {4}
 1a4:	00005101 	andeq	r5, r0, r1, lsl #2
 1a8:	00000000 	andeq	r0, r0, r0
 1ac:	00640600 	rsbeq	r0, r4, r0, lsl #12
 1b0:	00041000 	andeq	r1, r4, r0
 1b4:	04500116 	ldrbeq	r0, [r0], #-278	@ 0xfffffeea
 1b8:	51011c16 	tstpl	r1, r6, lsl ip
 1bc:	042c1c04 	strteq	r1, [ip], #-3076	@ 0xfffff3fc
 1c0:	9f5001a3 	svcls	0x005001a3
 1c4:	08010200 	stmdaeq	r1, {r9}
 1c8:	10000078 	andne	r0, r0, r8, ror r0
 1cc:	000a0408 	andeq	r0, sl, r8, lsl #8
 1d0:	01009f04 	tsteq	r0, r4, lsl #30
 1d4:	00000000 	andeq	r0, r0, r0
 1d8:	00780601 	rsbseq	r0, r8, r1, lsl #12
 1dc:	00041000 	andeq	r1, r4, r0
 1e0:	04500102 	ldrbeq	r0, [r0], #-258	@ 0xfffffefe
 1e4:	51010802 	tstpl	r1, r2, lsl #16
 1e8:	04080804 	streq	r0, [r8], #-2052	@ 0xfffff7fc
 1ec:	9f5001a3 	svcls	0x005001a3
 1f0:	00000000 	andeq	r0, r0, r0
 1f4:	00380600 	eorseq	r0, r8, r0, lsl #12
 1f8:	00041000 	andeq	r1, r4, r0
 1fc:	04500112 	ldrbeq	r0, [r0], #-274	@ 0xfffffeee
 200:	a3041a12 	movwge	r1, #18962	@ 0x4a12
 204:	009f5001 	addseq	r5, pc, r1
 208:	01000001 	tsteq	r0, r1
 20c:	00004608 	andeq	r4, r0, r8, lsl #12
 210:	53010610 	movwpl	r0, #5648	@ 0x1610
 214:	00004c08 	andeq	r4, r0, r8, lsl #24
 218:	91020010 	tstls	r2, r0, lsl r0
 21c:	00010054 	andeq	r0, r1, r4, asr r0
 220:	46080100 	strmi	r0, [r8], -r0, lsl #2
 224:	06100000 	ldreq	r0, [r0], -r0
 228:	4c085201 	sfmmi	f5, 4, [r8], {1}
 22c:	00100000 	andseq	r0, r0, r0
 230:	005c9102 	subseq	r9, ip, r2, lsl #2
 234:	46080001 	strmi	r0, [r8], -r1
 238:	06100000 	ldreq	r0, [r0], -r0
 23c:	01005101 	tsteq	r0, r1, lsl #2
 240:	009e0800 	addseq	r0, lr, r0, lsl #16
 244:	01061000 	mrseq	r1, (UNDEF: 6)
 248:	Address 0x248 is out of bounds.


Disassembly of section .debug_aranges:

00000000 <.debug_aranges>:
   0:	0000003c 	andeq	r0, r0, ip, lsr r0
   4:	00000002 	andeq	r0, r0, r2
   8:	00040000 	andeq	r0, r4, r0
   c:	00000000 	andeq	r0, r0, r0
  10:	10000038 	andne	r0, r0, r8, lsr r0
  14:	0000001a 	andeq	r0, r0, sl, lsl r0
  18:	10000054 	andne	r0, r0, r4, asr r0
  1c:	00000010 	andeq	r0, r0, r0, lsl r0
  20:	10000064 	andne	r0, r0, r4, rrx
  24:	0000002c 	andeq	r0, r0, ip, lsr #32
  28:	10000090 	mulne	r0, r0, r0
  2c:	00000014 	andeq	r0, r0, r4, lsl r0
  30:	100000a4 	andne	r0, r0, r4, lsr #1
  34:	0000013c 	andeq	r0, r0, ip, lsr r1
	...

Disassembly of section .debug_rnglists:

00000000 <.debug_rnglists>:
   0:	000000c7 	andeq	r0, r0, r7, asr #1
   4:	00040005 	andeq	r0, r4, r5
   8:	00000000 	andeq	r0, r0, r0
   c:	0000b405 	andeq	fp, r0, r5, lsl #8
  10:	02000410 	andeq	r0, r0, #16, 8	@ 0x10000000
  14:	04080604 	streq	r0, [r8], #-1540	@ 0xfffff9fc
  18:	2804220a 	stmdacs	r4, {r1, r3, r9, sp}
  1c:	f405002a 	vst4.8	{d0-d3}, [r5 :128], sl
  20:	04100000 	ldreq	r0, [r0], #-0
  24:	06040400 	streq	r0, [r4], -r0, lsl #8
  28:	120e040a 	andne	r0, lr, #167772160	@ 0xa000000
  2c:	00f40500 	rscseq	r0, r4, r0, lsl #10
  30:	00041000 	andeq	r1, r4, r0
  34:	0a060404 	beq	18104c <_mAppVer-0xfe7efb8>
  38:	00fe0500 	rscseq	r0, lr, r0, lsl #10
  3c:	00041000 	andeq	r1, r4, r0
  40:	0c080404 	cfstrseq	mvf0, [r8], {4}
  44:	00141004 	andseq	r1, r4, r4
  48:	0000fe05 	andeq	pc, r0, r5, lsl #28
  4c:	04000410 	streq	r0, [r0], #-1040	@ 0xfffffbf0
  50:	000c0804 	andeq	r0, ip, r4, lsl #16
  54:	00010a05 	andeq	r0, r1, r5, lsl #20
  58:	04000410 	streq	r0, [r0], #-1040	@ 0xfffffbf0
  5c:	040c0804 	streq	r0, [ip], #-2052	@ 0xfffff7fc
  60:	05001410 	streq	r1, [r0, #-1040]	@ 0xfffffbf0
  64:	1000010a 	andne	r0, r0, sl, lsl #2
  68:	04040004 	streq	r0, [r4], #-4
  6c:	05000c08 	streq	r0, [r0, #-3080]	@ 0xfffff3f8
  70:	10000116 	andne	r0, r0, r6, lsl r1
  74:	04040004 	streq	r0, [r4], #-4
  78:	05000c08 	streq	r0, [r0, #-3080]	@ 0xfffff3f8
  7c:	10000142 	andne	r0, r0, r2, asr #2
  80:	04080004 	streq	r0, [r8], #-4
  84:	0500403e 	streq	r4, [r0, #-62]	@ 0xffffffc2
  88:	10000142 	andne	r0, r0, r2, asr #2
  8c:	04080004 	streq	r0, [r8], #-4
  90:	0500403e 	streq	r4, [r0, #-62]	@ 0xffffffc2
  94:	100001ae 	andne	r0, r0, lr, lsr #3
  98:	04020004 	streq	r0, [r2], #-4
  9c:	05003216 	streq	r3, [r0, #-534]	@ 0xfffffdea
  a0:	100001ae 	andne	r0, r0, lr, lsr #3
  a4:	04020004 	streq	r0, [r2], #-4
  a8:	07003216 	smladeq	r0, r6, r2, r3
  ac:	10000038 	andne	r0, r0, r8, lsr r0
  b0:	0054071a 	subseq	r0, r4, sl, lsl r7
  b4:	07101000 	ldreq	r1, [r0, -r0]
  b8:	10000064 	andne	r0, r0, r4, rrx
  bc:	0090072c 	addseq	r0, r0, ip, lsr #14
  c0:	07141000 	ldreq	r1, [r4, -r0]
  c4:	100000a4 	andne	r0, r0, r4, lsr #1
  c8:	Address 0xc8 is out of bounds.


Disassembly of section .debug_line:

00000000 <.debug_line>:
   0:	00000429 	andeq	r0, r0, r9, lsr #8
   4:	01780003 	cmneq	r8, r3
   8:	01020000 	mrseq	r0, (UNDEF: 2)
   c:	000d0efb 	strdeq	r0, [sp], -fp
  10:	01010101 	tsteq	r1, r1, lsl #2
  14:	01000000 	mrseq	r0, (UNDEF: 0)
  18:	2e010000 	cdpcs	0, 0, cr0, cr1, cr0, {0}
  1c:	2e2e2f2e 	cdpcs	15, 2, cr2, cr14, cr14, {1}
  20:	2f736f2f 	svccs	0x00736f2f
  24:	00636e69 	rsbeq	r6, r3, r9, ror #28
  28:	6f72702f 	svcvs	0x0072702f
  2c:	7463656a 	strbtvc	r6, [r3], #-1386	@ 0xfffffa96
  30:	6363672f 	cmnvs	r3, #12320768	@ 0xbc0000
  34:	6d72612f 	ldfvse	f6, [r2, #-188]!	@ 0xffffff44
  38:	756e672d 	strbvc	r6, [lr, #-1837]!	@ 0xfffff8d3
  3c:	6f6f742d 	svcvs	0x006f742d
  40:	6168636c 	cmnvs	r8, ip, ror #6
  44:	312d6e69 			@ <UNDEFINED> instruction: 0x312d6e69
  48:	2f333032 	svccs	0x00333032
  4c:	2d6d7261 	sfmcs	f7, 2, [sp, #-388]!	@ 0xfffffe7c
  50:	656e6f6e 	strbvs	r6, [lr, #-3950]!	@ 0xfffff092
  54:	6261652d 	rsbvs	r6, r1, #188743680	@ 0xb400000
  58:	6e692f69 	cdpvs	15, 6, cr2, cr9, cr9, {3}
  5c:	64756c63 	ldrbtvs	r6, [r5], #-3171	@ 0xfffff39d
  60:	616d2f65 	cmnvs	sp, r5, ror #30
  64:	6e696863 	cdpvs	8, 6, cr6, cr9, cr3, {3}
  68:	702f0065 	eorvc	r0, pc, r5, rrx
  6c:	656a6f72 	strbvs	r6, [sl, #-3954]!	@ 0xfffff08e
  70:	672f7463 	strvs	r7, [pc, -r3, ror #8]!
  74:	612f6363 			@ <UNDEFINED> instruction: 0x612f6363
  78:	672d6d72 			@ <UNDEFINED> instruction: 0x672d6d72
  7c:	742d756e 	strtvc	r7, [sp], #-1390	@ 0xfffffa92
  80:	636c6f6f 	cmnvs	ip, #444	@ 0x1bc
  84:	6e696168 	powvsez	f6, f1, #0.0
  88:	3032312d 	eorscc	r3, r2, sp, lsr #2
  8c:	72612f33 	rsbvc	r2, r1, #51, 30	@ 0xcc
  90:	6f6e2d6d 	svcvs	0x006e2d6d
  94:	652d656e 	strvs	r6, [sp, #-1390]!	@ 0xfffffa92
  98:	2f696261 	svccs	0x00696261
  9c:	6c636e69 	stclvs	14, cr6, [r3], #-420	@ 0xfffffe5c
  a0:	2f656475 	svccs	0x00656475
  a4:	00737973 	rsbseq	r7, r3, r3, ror r9
  a8:	6f72702f 	svcvs	0x0072702f
  ac:	7463656a 	strbtvc	r6, [r3], #-1386	@ 0xfffffa96
  b0:	6363672f 	cmnvs	r3, #12320768	@ 0xbc0000
  b4:	6d72612f 	ldfvse	f6, [r2, #-188]!	@ 0xffffff44
  b8:	756e672d 	strbvc	r6, [lr, #-1837]!	@ 0xfffff8d3
  bc:	6f6f742d 	svcvs	0x006f742d
  c0:	6168636c 	cmnvs	r8, ip, ror #6
  c4:	312d6e69 			@ <UNDEFINED> instruction: 0x312d6e69
  c8:	2f333032 	svccs	0x00333032
  cc:	2f62696c 	svccs	0x0062696c
  d0:	2f636367 	svccs	0x00636367
  d4:	2d6d7261 	sfmcs	f7, 2, [sp, #-388]!	@ 0xfffffe7c
  d8:	656e6f6e 	strbvs	r6, [lr, #-3950]!	@ 0xfffff092
  dc:	6261652d 	rsbvs	r6, r1, #188743680	@ 0xb400000
  e0:	32312f69 	eorscc	r2, r1, #420	@ 0x1a4
  e4:	312e332e 			@ <UNDEFINED> instruction: 0x312e332e
  e8:	636e692f 	cmnvs	lr, #770048	@ 0xbc000
  ec:	6564756c 	strbvs	r7, [r4, #-1388]!	@ 0xfffffa94
  f0:	65740000 	ldrbvs	r0, [r4, #-0]!
  f4:	615f7473 	cmpvs	pc, r3, ror r4	@ <UNPREDICTABLE>
  f8:	2e307070 	mrccs	0, 1, r7, cr0, cr0, {3}
  fc:	00000063 	andeq	r0, r0, r3, rrx
 100:	73797300 	cmnvc	r9, #0, 6
 104:	6c6c6163 	stfvse	f6, [ip], #-396	@ 0xfffffe74
 108:	682e6f44 	stmdavs	lr!, {r2, r6, r8, r9, sl, fp, sp, lr}
 10c:	00000100 	andeq	r0, r0, r0, lsl #2
 110:	63737973 	cmnvs	r3, #1884160	@ 0x1cc000
 114:	5f6c6c61 	svcpl	0x006c6c61
 118:	73666564 	cmnvc	r6, #100, 10	@ 0x19000000
 11c:	0100682e 	tsteq	r0, lr, lsr #16
 120:	645f0000 	ldrbvs	r0, [pc], #-0	@ 128 <_mAppVer-0xffffedc>
 124:	75616665 	strbvc	r6, [r1, #-1637]!	@ 0xfffff99b
 128:	745f746c 	ldrbvc	r7, [pc], #-1132	@ 130 <_mAppVer-0xffffed4>
 12c:	73657079 	cmnvc	r5, #121	@ 0x79
 130:	0200682e 	andeq	r6, r0, #3014656	@ 0x2e0000
 134:	735f0000 	cmpvc	pc, #0
 138:	6e696474 	mcrvs	4, 3, r6, cr9, cr4, {3}
 13c:	00682e74 	rsbeq	r2, r8, r4, ror lr
 140:	73000003 	movwvc	r0, #3
 144:	72616474 	rsbvc	r6, r1, #116, 8	@ 0x74000000
 148:	00682e67 	rsbeq	r2, r8, r7, ror #28
 14c:	65000004 	strvs	r0, [r0, #-4]
 150:	746e6576 	strbtvc	r6, [lr], #-1398	@ 0xfffffa8a
 154:	736d756e 	cmnvc	sp, #461373440	@ 0x1b800000
 158:	0100682e 	tsteq	r0, lr, lsr #16
 15c:	65730000 	ldrbvs	r0, [r3, #-0]!
 160:	682e736f 	stmdavs	lr!, {r0, r1, r2, r3, r5, r6, r8, r9, ip, sp, lr}
 164:	00000100 	andeq	r0, r0, r0, lsl #2
 168:	656d6974 	strbvs	r6, [sp, #-2420]!	@ 0xfffff68c
 16c:	00682e72 	rsbeq	r2, r8, r2, ror lr
 170:	3c000001 	stccc	0, cr0, [r0], {1}
 174:	6c697562 	cfstr64vs	mvdx7, [r9], #-392	@ 0xfffffe78
 178:	6e692d74 	mcrvs	13, 3, r2, cr9, cr4, {3}
 17c:	0000003e 	andeq	r0, r0, lr, lsr r0
 180:	02040000 	andeq	r0, r4, #0
 184:	05000105 	streq	r0, [r0, #-261]	@ 0xfffffefb
 188:	00003802 	andeq	r3, r0, r2, lsl #16
 18c:	00da0310 	sbcseq	r0, sl, r0, lsl r3
 190:	13050501 	movwne	r0, #21761	@ 0x5501
 194:	06010514 			@ <UNDEFINED> instruction: 0x06010514
 198:	05052e0f 	streq	r2, [r5, #-3599]	@ 0xfffff1f1
 19c:	0521064d 	streq	r0, [r1, #-1613]!	@ 0xfffff9b3
 1a0:	01710314 	cmneq	r1, r4, lsl r3
 1a4:	05140505 	ldreq	r0, [r4, #-1285]	@ 0xfffffafb
 1a8:	012e010b 			@ <UNDEFINED> instruction: 0x012e010b
 1ac:	06200101 	strteq	r0, [r0], -r1, lsl #2
 1b0:	06050501 	streq	r0, [r5], -r1, lsl #10
 1b4:	05010e03 	streq	r0, [r1, #-3587]	@ 0xfffff1fd
 1b8:	02130601 	andseq	r0, r3, #1048576	@ 0x100000
 1bc:	01010003 	tsteq	r1, r3
 1c0:	05000105 	streq	r0, [r0, #-261]	@ 0xfffffefb
 1c4:	00005402 	andeq	r5, r0, r2, lsl #8
 1c8:	012a0310 			@ <UNDEFINED> instruction: 0x012a0310
 1cc:	02130505 	andseq	r0, r3, #20971520	@ 0x1400000
 1d0:	01010008 	tsteq	r1, r8
 1d4:	05000105 	streq	r0, [r0, #-261]	@ 0xfffffefb
 1d8:	00006402 	andeq	r6, r0, r2, lsl #8
 1dc:	01220310 			@ <UNDEFINED> instruction: 0x01220310
 1e0:	05130505 	ldreq	r0, [r3, #-1285]	@ 0xfffffafb
 1e4:	0501060c 	streq	r0, [r1, #-1548]	@ 0xfffff9f4
 1e8:	054b0605 	strbeq	r0, [fp, #-1541]	@ 0xfffff9fb
 1ec:	05010609 	streq	r0, [r1, #-1545]	@ 0xfffff9f7
 1f0:	09054801 	stmdbeq	r5, {r0, fp, lr}
 1f4:	06050522 	streq	r0, [r5], -r2, lsr #10
 1f8:	05020422 	streq	r0, [r2, #-1058]	@ 0xfffffbde
 1fc:	05051514 	streq	r1, [r5, #-1300]	@ 0xfffffaec
 200:	010c0514 	tsteq	ip, r4, lsl r5
 204:	202e0120 	eorcs	r0, lr, r0, lsr #2
 208:	01040106 	tsteq	r4, r6, lsl #2
 20c:	020e0105 	andeq	r0, lr, #1073741825	@ 0x40000001
 210:	01010008 	tsteq	r1, r8
 214:	19050304 	stmdbne	r5, {r2, r8, r9}
 218:	90020500 	andls	r0, r2, r0, lsl #10
 21c:	03100000 	tsteq	r0, #0
 220:	05050116 	streq	r0, [r5, #-278]	@ 0xfffffeea
 224:	05141314 	ldreq	r1, [r4, #-788]	@ 0xfffffcec
 228:	050d0619 	streq	r0, [sp, #-1561]	@ 0xfffff9e7
 22c:	09053305 	stmdbeq	r5, {r0, r2, r8, r9, ip, sp}
 230:	0f053206 	svceq	0x00053206
 234:	20012e01 	andcs	r2, r1, r1, lsl #28
 238:	05050106 	streq	r0, [r5, #-262]	@ 0xfffffefa
 23c:	05141406 	ldreq	r1, [r4, #-1030]	@ 0xfffffbfa
 240:	02130601 	andseq	r0, r3, #1048576	@ 0x100000
 244:	01010003 	tsteq	r1, r3
 248:	05000105 	streq	r0, [r0, #-261]	@ 0xfffffefb
 24c:	0000a402 	andeq	sl, r0, r2, lsl #8
 250:	012f0310 			@ <UNDEFINED> instruction: 0x012f0310
 254:	13130505 	tstne	r3, #20971520	@ 0x1400000
 258:	05141313 	ldreq	r1, [r4, #-787]	@ 0xfffffced
 25c:	7a030601 	bvc	c1a68 <_mAppVer-0xff3e59c>
 260:	34080501 	strcc	r0, [r8], #-1281	@ 0xfffffaff
 264:	7a030105 	bvc	c0680 <_mAppVer-0xff3f984>
 268:	0805202e 	stmdaeq	r5, {r1, r2, r3, r5, sp}
 26c:	06090526 	streq	r0, [r9], -r6, lsr #10
 270:	06130521 	ldreq	r0, [r3], -r1, lsr #10
 274:	05020401 	streq	r0, [r2, #-1025]	@ 0xfffffbff
 278:	00ff030c 	rscseq	r0, pc, ip, lsl #6
 27c:	01042020 	tsteq	r4, r0, lsr #32
 280:	81031305 	tsthi	r3, r5, lsl #6
 284:	0204017f 	andeq	r0, r4, #-1073741793	@ 0xc000001f
 288:	ff030c05 			@ <UNDEFINED> instruction: 0xff030c05
 28c:	01042e00 	tsteq	r4, r0, lsl #28
 290:	81031305 	tsthi	r3, r5, lsl #6
 294:	0204207f 	andeq	r2, r4, #127	@ 0x7f
 298:	03061805 	movweq	r1, #26629	@ 0x6805
 29c:	052000fa 	streq	r0, [r0, #-250]!	@ 0xffffff06
 2a0:	14131405 	ldrne	r1, [r3], #-1029	@ 0xfffffbfb
 2a4:	01060c05 	tsteq	r6, r5, lsl #24
 2a8:	01042e9e 			@ <UNDEFINED> instruction: 0x01042e9e
 2ac:	82030905 	andhi	r0, r3, #81920	@ 0x14000
 2b0:	0204017f 	andeq	r0, r4, #-1073741793	@ 0xc000001f
 2b4:	fe030c05 	cdp2	12, 0, cr0, cr3, cr5, {0}
 2b8:	04203c00 	strteq	r3, [r0], #-3072	@ 0xfffff400
 2bc:	06090501 	streq	r0, [r9], -r1, lsl #10
 2c0:	017f8203 	cmneq	pc, r3, lsl #4
 2c4:	03060105 	movweq	r0, #24837	@ 0x6105
 2c8:	09052e12 	stmdbeq	r5, {r1, r4, r9, sl, fp, sp}
 2cc:	053c6e03 	ldreq	r6, [ip, #-3587]!	@ 0xfffff1fd
 2d0:	052f060c 	streq	r0, [pc, #-1548]!	@ fffffccc <__bss_end+0x7ffffca0>
 2d4:	0501060f 	streq	r0, [r1, #-1551]	@ 0xfffff9f1
 2d8:	132f0609 			@ <UNDEFINED> instruction: 0x132f0609
 2dc:	05050204 	streq	r0, [r5, #-516]	@ 0xfffffdfc
 2e0:	00f20306 	rscseq	r0, r2, r6, lsl #6
 2e4:	01042e2e 	tsteq	r4, lr, lsr #28
 2e8:	8e030905 	vmlahi.f16	s0, s6, s10	@ <UNPREDICTABLE>
 2ec:	0204017f 	andeq	r0, r4, #-1073741793	@ 0xc000001f
 2f0:	03061805 	movweq	r1, #26629	@ 0x6805
 2f4:	052000ef 	streq	r0, [r0, #-239]!	@ 0xffffff11
 2f8:	01131405 	tsteq	r3, r5, lsl #8
 2fc:	13202001 			@ <UNDEFINED> instruction: 0x13202001
 300:	01380306 	teqeq	r8, r6, lsl #6
 304:	48030c05 	stmdami	r3, {r0, r2, sl, fp}
 308:	0618052e 	ldreq	r0, [r8], -lr, lsr #10
 30c:	052e3503 	streq	r3, [lr, #-1283]!	@ 0xfffffafd
 310:	01131405 	tsteq	r3, r5, lsl #8
 314:	13202001 			@ <UNDEFINED> instruction: 0x13202001
 318:	7fba0306 	svcvc	0x00ba0306
 31c:	030c0501 	movweq	r0, #50433	@ 0xc501
 320:	052e00c6 	streq	r0, [lr, #-198]!	@ 0xffffff3a
 324:	b7030618 	smladlt	r3, r8, r6, r0
 328:	05052e7f 	streq	r2, [r5, #-3711]	@ 0xfffff181
 32c:	01011314 	tsteq	r1, r4, lsl r3
 330:	06132020 	ldreq	r2, [r3], -r0, lsr #32
 334:	05013d03 	streq	r3, [r1, #-3331]	@ 0xfffff2fd
 338:	2e43030c 	cdpcs	3, 4, cr0, cr3, cr12, {0}
 33c:	03061805 	movweq	r1, #26629	@ 0x6805
 340:	05052e3a 	streq	r2, [r5, #-3642]	@ 0xfffff1c6
 344:	01011314 	tsteq	r1, r4, lsl r3
 348:	04132020 	ldreq	r2, [r3], #-32	@ 0xffffffe0
 34c:	06090501 	streq	r0, [r9], -r1, lsl #10
 350:	017edb03 	cmneq	lr, r3, lsl #22
 354:	0204f306 	andeq	pc, r4, #402653184	@ 0x18000000
 358:	82031505 	andhi	r1, r3, #20971520	@ 0x1400000
 35c:	05050101 	streq	r0, [r5, #-257]	@ 0xfffffeff
 360:	01130514 	tsteq	r3, r4, lsl r5
 364:	0420202e 	strteq	r2, [r0], #-46	@ 0xffffffd2
 368:	061b0501 	ldreq	r0, [fp], -r1, lsl #10
 36c:	017efd03 	cmneq	lr, r3, lsl #26	@ <UNPREDICTABLE>
 370:	05f31d05 	ldrbeq	r1, [r3, #3333]!	@ 0xd05
 374:	17052f15 	smladne	r5, r5, pc, r2	@ <UNPREDICTABLE>
 378:	2015052f 	andscs	r0, r5, pc, lsr #10
 37c:	043d0f05 	ldrteq	r0, [sp], #-3845	@ 0xfffff0fb
 380:	03130502 	tsteq	r3, #8388608	@ 0x800000
 384:	203c00ff 	ldrshtcs	r0, [ip], -pc
 388:	09050104 	stmdbeq	r5, {r2, r8}
 38c:	7efd0306 	cdpvc	3, 15, cr0, cr13, cr6, {0}
 390:	13131301 	tstne	r3, #67108864	@ 0x4000000
 394:	05020413 	streq	r0, [r2, #-1043]	@ 0xfffffbed
 398:	01730314 	cmneq	r3, r4, lsl r3
 39c:	05140505 	ldreq	r0, [r4, #-1285]	@ 0xfffffafb
 3a0:	2e2e010c 	sufcse	f0, f6, #4.0
 3a4:	06200120 	strteq	r0, [r0], -r0, lsr #2
 3a8:	03010401 	movweq	r0, #5121	@ 0x1401
 3ac:	0d05010b 	stfeqs	f0, [r5, #-44]	@ 0xffffffd4
 3b0:	02042106 	andeq	r2, r4, #-2147483647	@ 0x80000001
 3b4:	81031405 	tsthi	r3, r5, lsl #8
 3b8:	05050101 	streq	r0, [r5, #-257]	@ 0xfffffeff
 3bc:	010b0514 	tsteq	fp, r4, lsl r5
 3c0:	0620202e 	strteq	r2, [r0], -lr, lsr #32
 3c4:	05010401 	streq	r0, [r1, #-1025]	@ 0xfffffbff
 3c8:	fe030609 	cdp2	6, 0, cr0, cr3, cr9, {0}
 3cc:	1005017e 	andne	r0, r5, lr, ror r1
 3d0:	0c050106 	stfeqs	f0, [r5], {6}
 3d4:	20100558 	andscs	r0, r0, r8, asr r5
 3d8:	05200c05 	streq	r0, [r0, #-3077]!	@ 0xfffff3fb
 3dc:	0421060d 	strteq	r0, [r1], #-1549	@ 0xfffff9f3
 3e0:	03140502 	tsteq	r4, #8388608	@ 0x800000
 3e4:	050100f5 	streq	r0, [r1, #-245]	@ 0xffffff0b
 3e8:	0c051405 	cfstrseq	mvf1, [r5], {5}
 3ec:	06013c01 	streq	r3, [r1], -r1, lsl #24
 3f0:	060b0501 	streq	r0, [fp], -r1, lsl #10
 3f4:	20010a03 	andcs	r0, r1, r3, lsl #20
 3f8:	01050104 	tsteq	r5, r4, lsl #2
 3fc:	7f850306 	svcvc	0x00850306
 400:	060c0501 	streq	r0, [ip], -r1, lsl #10
 404:	060f0537 			@ <UNDEFINED> instruction: 0x060f0537
 408:	06090501 	streq	r0, [r9], -r1, lsl #10
 40c:	0c05132f 	stceq	3, cr1, [r5], {47}	@ 0x2f
 410:	0d050106 	stfeqs	f0, [r5, #-24]	@ 0xffffffe8
 414:	02045906 	andeq	r5, r4, #98304	@ 0x18000
 418:	fb031405 	blx	c5436 <_mAppVer-0xff3abce>
 41c:	05050100 	streq	r0, [r5, #-256]	@ 0xffffff00
 420:	010b0514 	tsteq	fp, r4, lsl r5
 424:	2e062006 	cdpcs	0, 0, cr2, cr6, cr6, {0}
 428:	01000b02 	tsteq	r0, r2, lsl #22
 42c:	Address 0x42c is out of bounds.


Disassembly of section .debug_str:

00000000 <.debug_str>:
   0:	49707061 	ldmdbmi	r0!, {r0, r5, r6, ip, sp, lr}^
   4:	72640064 	rsbvc	r0, r4, #100	@ 0x64
   8:	50746669 	rsbspl	r6, r4, r9, ror #12
   c:	4c006d70 	stcmi	13, cr6, [r0], {112}	@ 0x70
  10:	565f474f 	ldrbpl	r4, [pc], -pc, asr #14
  14:	4f425245 	svcmi	0x00425245
  18:	73004553 	movwvc	r4, #1363	@ 0x553
  1c:	74726f68 	ldrbtvc	r6, [r2], #-3944	@ 0xfffff098
  20:	746e6920 	strbtvc	r6, [lr], #-2336	@ 0xfffff6e0
  24:	6e656c00 	cdpvs	12, 6, cr6, cr5, cr0, {0}
  28:	48687467 	stmdami	r8!, {r0, r1, r2, r5, r6, sl, ip, sp, lr}^
  2c:	4d6d0069 	stclmi	0, cr0, [sp, #-420]!	@ 0xfffffe5c
  30:	64695479 	strbtvs	r5, [r9], #-1145	@ 0xfffffb87
  34:	6e616800 	cdpvs	8, 6, cr6, cr1, cr0, {0}
  38:	5f656c64 	svcpl	0x00656c64
  3c:	6e657665 	cdpvs	6, 6, cr7, cr5, cr5, {3}
  40:	4f650074 	svcmi	0x00650074
  44:	716e4573 	smcvc	58451	@ 0xe453
  48:	65756575 	ldrbvs	r6, [r5, #-1397]!	@ 0xfffffa8b
  4c:	00747645 	rsbseq	r7, r4, r5, asr #12
  50:	69755f5f 	ldmdbvs	r5!, {r0, r1, r2, r3, r4, r6, r8, r9, sl, fp, ip, lr}^
  54:	3233746e 	eorscc	r7, r3, #1845493760	@ 0x6e000000
  58:	5f00745f 	svcpl	0x0000745f
  5c:	7070416d 	rsbsvc	r4, r0, sp, ror #2
  60:	636e7546 	cmnvs	lr, #293601280	@ 0x11800000
  64:	4f4c0073 	svcmi	0x004c0073
  68:	4e495f47 	cdpmi	15, 4, cr5, cr9, cr7, {2}
  6c:	65004f46 	strvs	r4, [r0, #-3910]	@ 0xfffff0ba
  70:	6f4c734f 	svcvs	0x004c734f
  74:	72610067 	rsbvc	r0, r1, #103	@ 0x67
  78:	6c5f7367 	mrrcvs	3, 6, r7, pc, cr7	@ <UNPREDICTABLE>
  7c:	00747369 	rsbseq	r7, r4, r9, ror #6
  80:	5f474f4c 	svcpl	0x00474f4c
  84:	4e524157 	mrcmi	1, 2, r4, cr2, cr7, {2}
  88:	6e656c00 	cdpvs	12, 6, cr6, cr5, cr0, {0}
  8c:	4c687467 	cfstrdmi	mvd7, [r8], #-412	@ 0xfffffe64
  90:	4f65006f 	svcmi	0x0065006f
  94:	61654873 	smcvs	21635	@ 0x5483
  98:	65724670 	ldrbvs	r4, [r2, #-1648]!	@ 0xfffff990
  9c:	74730065 	ldrbtvc	r0, [r3], #-101	@ 0xffffff9b
  a0:	5f747261 	svcpl	0x00747261
  a4:	6b736174 	blvs	1cd867c <_mAppVer-0xe327988>
  a8:	74766500 	ldrbtvc	r6, [r6], #-1280	@ 0xfffffb00
  ac:	65707954 	ldrbvs	r7, [r0, #-2388]!	@ 0xfffff6ac
  b0:	474f4c00 	strbmi	r4, [pc, -r0, lsl #24]
  b4:	5252455f 	subspl	r4, r2, #398458880	@ 0x17c00000
  b8:	5f00524f 	svcpl	0x0000524f
  bc:	7070416d 	rsbsvc	r4, r0, sp, ror #2
  c0:	00726556 	rsbseq	r6, r2, r6, asr r5
  c4:	74736574 	ldrbtvc	r6, [r3], #-1396	@ 0xfffffa8c
  c8:	7070615f 	rsbsvc	r6, r0, pc, asr r1
  cc:	00632e30 	rsbeq	r2, r3, r0, lsr lr
  d0:	676e656c 	strbvs	r6, [lr, -ip, ror #10]!
  d4:	66006874 			@ <UNDEFINED> instruction: 0x66006874
  d8:	74616f6c 	strbtvc	r6, [r1], #-3948	@ 0xfffff094
  dc:	73797300 	cmnvc	r9, #0, 6
  e0:	6c6c6163 	stfvse	f6, [ip], #-396	@ 0xfffffe74
  e4:	6d006f4e 	stcvs	15, cr6, [r0, #-312]	@ 0xfffffec8
  e8:	64695479 	strbtvs	r5, [r9], #-1145	@ 0xfffffb87
  ec:	6e6f6c00 	cdpvs	12, 6, cr6, cr15, cr0, {0}
  f0:	6f6c2067 	svcvs	0x006c2067
  f4:	6920676e 	stmdbvs	r0!, {r1, r2, r3, r5, r6, r8, r9, sl, sp, lr}
  f8:	5f00746e 	svcpl	0x0000746e
  fc:	5f61765f 	svcpl	0x0061765f
 100:	7473696c 	ldrbtvc	r6, [r3], #-2412	@ 0xfffff694
 104:	734f6500 	movtvc	r6, #62720	@ 0xf500
 108:	546d6954 	strbtpl	r6, [sp], #-2388	@ 0xfffff6ac
 10c:	72656d69 	rsbvc	r6, r5, #6720	@ 0x1a40
 110:	00746553 	rsbseq	r6, r4, r3, asr r5
 114:	4c676f4c 	stclmi	15, cr6, [r7], #-304	@ 0xfffffed0
 118:	6c657665 	stclvs	6, cr7, [r5], #-404	@ 0xfffffe6c
 11c:	755f5f00 	ldrbvc	r5, [pc, #-3840]	@ fffff224 <__bss_end+0x7ffff1f8>
 120:	38746e69 	ldmdacc	r4!, {r0, r3, r5, r6, r9, sl, fp, sp, lr}^
 124:	7400745f 	strvc	r7, [r0], #-1119	@ 0xfffffba1
 128:	664f6469 	strbvs	r6, [pc], -r9, ror #8
 12c:	576f6857 			@ <UNDEFINED> instruction: 0x576f6857
 130:	466c6c69 	strbtmi	r6, [ip], -r9, ror #24
 134:	54656572 	strbtpl	r6, [r5], #-1394	@ 0xfffffa8e
 138:	45736968 	ldrbmi	r6, [r3, #-2408]!	@ 0xfffff698
 13c:	746e6576 	strbtvc	r6, [lr], #-1398	@ 0xfffffa8a
 140:	474f4c00 	strbmi	r4, [pc, -r0, lsl #24]
 144:	4245445f 	submi	r4, r5, #1593835520	@ 0x5f000000
 148:	65004755 	strvs	r4, [r0, #-1877]	@ 0xfffff8ab
 14c:	7452734f 	ldrbvc	r7, [r2], #-847	@ 0xfffffcb1
 150:	74654763 	strbtvc	r4, [r5], #-1891	@ 0xfffff89d
 154:	656d6954 	strbvs	r6, [sp, #-2388]!	@ 0xfffff6ac
 158:	6e6f6c00 	cdpvs	12, 6, cr6, cr15, cr0, {0}
 15c:	6f642067 	svcvs	0x00642067
 160:	656c6275 	strbvs	r6, [ip, #-629]!	@ 0xfffffd8b
 164:	736e7500 	cmnvc	lr, #0, 10
 168:	656e6769 	strbvs	r6, [lr, #-1897]!	@ 0xfffff897
 16c:	68632064 	stmdavs	r3!, {r2, r5, r6, sp}^
 170:	68007261 	stmdavs	r0, {r0, r5, r6, r9, ip, sp, lr}
 174:	6c646e61 	stclvs	14, cr6, [r4], #-388	@ 0xfffffe7c
 178:	6f6c0065 	svcvs	0x006c0065
 17c:	6c20676e 	stcvs	7, cr6, [r0], #-440	@ 0xfffffe48
 180:	20676e6f 	rsbcs	r6, r7, pc, ror #28
 184:	69736e75 	ldmdbvs	r3!, {r0, r2, r4, r5, r6, r9, sl, fp, sp, lr}^
 188:	64656e67 	strbtvs	r6, [r5], #-3687	@ 0xfffff199
 18c:	746e6920 	strbtvc	r6, [lr], #-2336	@ 0xfffff6e0
 190:	734f6500 	movtvc	r6, #62720	@ 0xf500
 194:	546d6954 	strbtpl	r6, [sp], #-2388	@ 0xfffff6ac
 198:	72656d69 	rsbvc	r6, r5, #6720	@ 0x1a40
 19c:	636e6143 	cmnvs	lr, #-1073741808	@ 0xc0000010
 1a0:	65006c65 	strvs	r6, [r0, #-3173]	@ 0xfffff39b
 1a4:	6553734f 	ldrbvs	r7, [r3, #-847]	@ 0xfffffcb1
 1a8:	726f736e 	rsbvc	r7, pc, #-1207959551	@ 0xb8000001
 1ac:	54746547 	ldrbtpl	r6, [r4], #-1351	@ 0xfffffab9
 1b0:	00656d69 	rsbeq	r6, r5, r9, ror #26
 1b4:	4d747845 	ldclmi	8, cr7, [r4, #-276]!	@ 0xfffffeec
 1b8:	65006773 	strvs	r6, [r0, #-1907]	@ 0xfffff88d
 1bc:	6f48734f 	svcvs	0x0048734f
 1c0:	65477473 	strbvs	r7, [r7, #-1139]	@ 0xfffffb8d
 1c4:	6d695474 	cfstrdvs	mvd5, [r9, #-464]!	@ 0xfffffe30
 1c8:	425f0065 	subsmi	r0, pc, #101	@ 0x65
 1cc:	006c6f6f 	rsbeq	r6, ip, pc, ror #30
 1d0:	61746164 	cmnvs	r4, r4, ror #2
 1d4:	006e654c 	rsbeq	r6, lr, ip, asr #10
 1d8:	45707041 	ldrbmi	r7, [r0, #-65]!	@ 0xffffffbf
 1dc:	746e6576 	strbtvc	r6, [lr], #-1398	@ 0xfffffa8a
 1e0:	65657246 	strbvs	r7, [r5, #-582]!	@ 0xfffffdba
 1e4:	61746144 	cmnvs	r4, r4, asr #2
 1e8:	615f5f00 	cmpvs	pc, r0, lsl #30
 1ec:	6f480070 	svcvs	0x00480070
 1f0:	75487473 	strbvc	r7, [r8, #-1139]	@ 0xfffffb8d
 1f4:	77615262 	strbvc	r5, [r1, -r2, ror #4]!
 1f8:	6b636150 	blvs	18d8740 <_mAppVer-0xe7278c4>
 1fc:	69007465 	stmdbvs	r0, {r0, r2, r5, r6, sl, ip, sp, lr}
 200:	0074696e 	rsbseq	r6, r4, lr, ror #18
 204:	5f646e65 	svcpl	0x00646e65
 208:	6b736174 	blvs	1cd87e0 <_mAppVer-0xe327824>
 20c:	554e4700 	strbpl	r4, [lr, #-1792]	@ 0xfffff900
 210:	37314320 	ldrcc	r4, [r1, -r0, lsr #6]!
 214:	2e323120 	rsfcssp	f3, f2, f0
 218:	20312e33 	eorscs	r2, r1, r3, lsr lr
 21c:	33323032 	teqcc	r2, #50	@ 0x32
 220:	36323630 			@ <UNDEFINED> instruction: 0x36323630
 224:	6e6d2d20 	cdpvs	13, 6, cr2, cr13, cr0, {1}
 228:	69702d6f 	ldmdbvs	r0!, {r0, r1, r2, r3, r5, r6, r8, sl, fp, sp}^
 22c:	61642d63 	cmnvs	r4, r3, ror #26
 230:	692d6174 	pushvs	{r2, r4, r5, r6, r8, sp, lr}
 234:	65742d73 	ldrbvs	r2, [r4, #-3443]!	@ 0xfffff28d
 238:	722d7478 	eorvc	r7, sp, #120, 8	@ 0x78000000
 23c:	74616c65 	strbtvc	r6, [r1], #-3173	@ 0xfffff39b
 240:	20657669 	rsbcs	r7, r5, r9, ror #12
 244:	69736d2d 	ldmdbvs	r3!, {r0, r2, r3, r5, r8, sl, fp, sp, lr}^
 248:	656c676e 	strbvs	r6, [ip, #-1902]!	@ 0xfffff892
 24c:	6369702d 	cmnvs	r9, #45	@ 0x2d
 250:	7361622d 	cmnvc	r1, #-805306366	@ 0xd0000002
 254:	6d2d2065 	stcvs	0, cr2, [sp, #-404]!	@ 0xfffffe6c
 258:	2d636970 			@ <UNDEFINED> instruction: 0x2d636970
 25c:	69676572 	stmdbvs	r7!, {r1, r4, r5, r6, r8, sl, sp, lr}^
 260:	72657473 	rsbvc	r7, r5, #1929379840	@ 0x73000000
 264:	2039723d 	eorscs	r7, r9, sp, lsr r2
 268:	68746d2d 	ldmdavs	r4!, {r0, r2, r3, r5, r8, sl, fp, sp, lr}^
 26c:	20626d75 	rsbcs	r6, r2, r5, ror sp
 270:	70636d2d 	rsbvc	r6, r3, sp, lsr #26
 274:	6f633d75 	svcvs	0x00633d75
 278:	78657472 	stmdavc	r5!, {r1, r4, r5, r6, sl, ip, sp, lr}^
 27c:	20346d2d 	eorscs	r6, r4, sp, lsr #26
 280:	6c666d2d 	stclvs	13, cr6, [r6], #-180	@ 0xffffff4c
 284:	2d74616f 	ldfcse	f6, [r4, #-444]!	@ 0xfffffe44
 288:	3d696261 	sfmcc	f6, 2, [r9, #-388]!	@ 0xfffffe7c
 28c:	74666f73 	strbtvc	r6, [r6], #-3955	@ 0xfffff08d
 290:	2d207066 	stccs	0, cr7, [r0, #-408]!	@ 0xfffffe68
 294:	7570666d 	ldrbvc	r6, [r0, #-1645]!	@ 0xfffff993
 298:	7670663d 			@ <UNDEFINED> instruction: 0x7670663d
 29c:	70732d34 	rsbsvc	r2, r3, r4, lsr sp
 2a0:	3631642d 	ldrtcc	r6, [r1], -sp, lsr #8
 2a4:	6e6d2d20 	cdpvs	13, 6, cr2, cr13, cr0, {1}
 2a8:	68742d6f 	ldmdavs	r4!, {r0, r1, r2, r3, r5, r6, r8, sl, fp, sp}^
 2ac:	2d626d75 	stclcs	13, cr6, [r2, #-468]!	@ 0xfffffe2c
 2b0:	65746e69 	ldrbvs	r6, [r4, #-3689]!	@ 0xfffff197
 2b4:	726f7772 	rsbvc	r7, pc, #29884416	@ 0x1c80000
 2b8:	6d2d206b 	stcvs	0, cr2, [sp, #-428]!	@ 0xfffffe54
 2bc:	68637261 	stmdavs	r3!, {r0, r5, r6, r9, ip, sp, lr}^
 2c0:	6d72613d 	ldfvse	f6, [r2, #-244]!	@ 0xffffff0c
 2c4:	2d653776 	stclcs	7, cr3, [r5, #-472]!	@ 0xfffffe28
 2c8:	70662b6d 	rsbvc	r2, r6, sp, ror #22
 2cc:	20672d20 	rsbcs	r2, r7, r0, lsr #26
 2d0:	20734f2d 	rsbscs	r4, r3, sp, lsr #30
 2d4:	6970662d 	ldmdbvs	r0!, {r0, r2, r3, r5, r9, sl, sp, lr}^
 2d8:	662d2063 	strtvs	r2, [sp], -r3, rrx
 2dc:	74736166 	ldrbtvc	r6, [r3], #-358	@ 0xfffffe9a
 2e0:	74616d2d 	strbtvc	r6, [r1], #-3373	@ 0xfffff2d3
 2e4:	662d2068 	strtvs	r2, [sp], -r8, rrx
 2e8:	676e6973 			@ <UNDEFINED> instruction: 0x676e6973
 2ec:	702d656c 	eorvc	r6, sp, ip, ror #10
 2f0:	69636572 	stmdbvs	r3!, {r1, r4, r5, r6, r8, sl, sp, lr}^
 2f4:	6e6f6973 			@ <UNDEFINED> instruction: 0x6e6f6973
 2f8:	6e6f632d 	cdpvs	3, 6, cr6, cr15, cr13, {1}
 2fc:	6e617473 	mcrvs	4, 3, r7, cr1, cr3, {3}
 300:	662d2074 			@ <UNDEFINED> instruction: 0x662d2074
 304:	732d6f6e 			@ <UNDEFINED> instruction: 0x732d6f6e
 308:	63697274 	cmnvs	r9, #116, 4	@ 0x40000007
 30c:	6c612d74 	stclvs	13, cr2, [r1], #-464	@ 0xfffffe30
 310:	69736169 	ldmdbvs	r3!, {r0, r3, r5, r6, r8, sp, lr}^
 314:	2d20676e 	stccs	7, cr6, [r0, #-440]!	@ 0xfffffe48
 318:	73697666 	cmnvc	r9, #106954752	@ 0x6600000
 31c:	6c696269 	sfmvs	f6, 2, [r9], #-420	@ 0xfffffe5c
 320:	3d797469 	cfldrdcc	mvd7, [r9, #-420]!	@ 0xfffffe5c
 324:	64646968 	strbtvs	r6, [r4], #-2408	@ 0xfffff698
 328:	2d206e65 	stccs	14, cr6, [r0, #-404]!	@ 0xfffffe6c
 32c:	2d6f6e66 	stclcs	14, cr6, [pc, #-408]!	@ 19c <_mAppVer-0xffffe68>
 330:	69776e75 	ldmdbvs	r7!, {r0, r2, r4, r5, r6, r9, sl, fp, sp, lr}^
 334:	742d646e 	strtvc	r6, [sp], #-1134	@ 0xfffffb92
 338:	656c6261 	strbvs	r6, [ip, #-609]!	@ 0xfffffd9f
 33c:	662d2073 			@ <UNDEFINED> instruction: 0x662d2073
 340:	63617473 	cmnvs	r1, #1929379840	@ 0x73000000
 344:	65722d6b 	ldrbvs	r2, [r2, #-3435]!	@ 0xfffff295
 348:	3d657375 	stclcc	3, cr7, [r5, #-468]!	@ 0xfffffe2c
 34c:	206c6c61 	rsbcs	r6, ip, r1, ror #24
 350:	7566662d 	strbvc	r6, [r6, #-1581]!	@ 0xfffff9d3
 354:	6974636e 	ldmdbvs	r4!, {r1, r2, r3, r5, r6, r8, r9, sp, lr}^
 358:	732d6e6f 			@ <UNDEFINED> instruction: 0x732d6e6f
 35c:	69746365 	ldmdbvs	r4!, {r0, r2, r5, r6, r8, r9, sp, lr}^
 360:	20736e6f 	rsbscs	r6, r3, pc, ror #28
 364:	6164662d 	cmnvs	r4, sp, lsr #12
 368:	732d6174 			@ <UNDEFINED> instruction: 0x732d6174
 36c:	69746365 	ldmdbvs	r4!, {r0, r2, r5, r6, r8, r9, sp, lr}^
 370:	00736e6f 	rsbseq	r6, r3, pc, ror #28
 374:	656d6974 	strbvs	r6, [sp, #-2420]!	@ 0xfffff68c
 378:	6f6e614e 	svcvs	0x006e614e
 37c:	68730073 	ldmdavs	r3!, {r0, r1, r4, r5, r6}^
 380:	2074726f 	rsbscs	r7, r4, pc, ror #4
 384:	69736e75 	ldmdbvs	r3!, {r0, r2, r4, r5, r6, r9, sl, fp, sp, lr}^
 388:	64656e67 	strbtvs	r6, [r5], #-3687	@ 0xfffff199
 38c:	746e6920 	strbtvc	r6, [lr], #-2336	@ 0xfffff6e0
 390:	74696a00 	strbtvc	r6, [r9], #-2560	@ 0xfffff600
 394:	50726574 	rsbspl	r6, r2, r4, ror r5
 398:	5f006d70 	svcpl	0x00006d70
 39c:	6e69755f 	mcrvs	5, 3, r7, cr9, cr15, {2}
 3a0:	5f343674 	svcpl	0x00343674
 3a4:	61640074 	smcvs	16388	@ 0x4004
 3a8:	65006174 	strvs	r6, [r0, #-372]	@ 0xfffffe8c
 3ac:	6f4c734f 	svcvs	0x004c734f
 3b0:	6e497667 	cdpvs	6, 4, cr7, cr9, cr7, {3}
 3b4:	6e726574 	mrcvs	5, 3, r6, cr2, cr4, {3}
 3b8:	61006c61 	tstvs	r0, r1, ror #24
 3bc:	00646665 	rsbeq	r6, r4, r5, ror #12
 3c0:	63737973 	cmnvs	r3, #1884160	@ 0x1cc000
 3c4:	446c6c61 	strbtmi	r6, [ip], #-3169	@ 0xfffff39f
 3c8:	6e65476f 	cdpvs	7, 6, cr4, cr5, cr15, {3}
 3cc:	63697265 	cmnvs	r9, #1342177286	@ 0x50000006
 3d0:	734f6500 	movtvc	r6, #62720	@ 0xf500
 3d4:	70616548 	rsbvc	r6, r1, r8, asr #10
 3d8:	6f6c6c41 	svcvs	0x006c6c41
 3dc:	702f0063 	eorvc	r0, pc, r3, rrx
 3e0:	656a6f72 	strbvs	r6, [sl, #-3954]!	@ 0xfffff08e
 3e4:	642f7463 	strtvs	r7, [pc], #-1123	@ 3ec <_mAppVer-0xffffc18>
 3e8:	63697665 	cmnvs	r9, #105906176	@ 0x6500000
 3ec:	6f672f65 	svcvs	0x00672f65
 3f0:	656c676f 	strbvs	r6, [ip, #-1903]!	@ 0xfffff891
 3f4:	6e6f632f 	cdpvs	3, 6, cr6, cr15, cr15, {1}
 3f8:	74786574 	ldrbtvc	r6, [r8], #-1396	@ 0xfffffa8c
 3fc:	2f627568 	svccs	0x00627568
 400:	6d726966 			@ <UNDEFINED> instruction: 0x6d726966
 404:	65726177 	ldrbvs	r6, [r2, #-375]!	@ 0xfffffe89
 408:	7070612f 	rsbsvc	r6, r0, pc, lsr #2
 40c:	7365742f 	cmnvc	r5, #788529152	@ 0x2f000000
 410:	612e3074 			@ <UNDEFINED> instruction: 0x612e3074
 414:	65007070 	strvs	r7, [r0, #-112]	@ 0xffffff90
 418:	6954734f 	ldmdbvs	r4, {r0, r1, r2, r3, r6, r8, r9, ip, sp, lr}^
 41c:	7465476d 	strbtvc	r4, [r5], #-1901	@ 0xfffff893
 420:	656d6954 	strbvs	r6, [sp, #-2388]!	@ 0xfffff6ac
 424:	6d697400 	cfstrdvs	mvd7, [r9, #-0]
 428:	64497265 	strbvs	r7, [r9], #-613	@ 0xfffffd9b
 42c:	76656c00 	strbtvc	r6, [r5], -r0, lsl #24
 430:	5f006c65 	svcpl	0x00006c65
 434:	6e69755f 	mcrvs	5, 3, r7, cr9, cr15, {2}
 438:	72747074 	rsbsvc	r7, r4, #116	@ 0x74
 43c:	5f00745f 	svcpl	0x0000745f
 440:	756e675f 	strbvc	r6, [lr, #-1887]!	@ 0xfffff8a1
 444:	61765f63 	cmnvs	r6, r3, ror #30
 448:	73696c5f 	cmnvc	r9, #24320	@ 0x5f00
 44c:	6f630074 	svcvs	0x00630074
 450:	65696b6f 	strbvs	r6, [r9, #-2927]!	@ 0xfffff491
 454:	74766500 	ldrbtvc	r6, [r6], #-1280	@ 0xfffffb00
 458:	61746144 	cmnvs	r4, r4, asr #2
 45c:	734f6500 	movtvc	r6, #62720	@ 0xf500
 460:	6e657645 	cdpvs	6, 6, cr7, cr5, cr5, {2}
 464:	62755374 	rsbsvs	r5, r5, #116, 6	@ 0xd0000001
 468:	69726373 	ldmdbvs	r2!, {r0, r1, r4, r5, r6, r8, r9, sp, lr}^
 46c:	54006562 	strpl	r6, [r0], #-1378	@ 0xfffffa9e
 470:	72656d69 	rsbvc	r6, r5, #6720	@ 0x1a40
 474:	6e657645 	cdpvs	6, 6, cr7, cr5, cr5, {2}
 478:	78650074 	stmdavc	r5!, {r2, r4, r5, r6}^
 47c:	67734d74 			@ <UNDEFINED> instruction: 0x67734d74
 480:	656e6f00 	strbvs	r6, [lr, #-3840]!	@ 0xfffff100
 484:	746f6853 	strbtvc	r6, [pc], #-2131	@ 48c <_mAppVer-0xffffb78>
	...

Disassembly of section .comment:

00000000 <.comment>:
   0:	3a434347 	bcc	10d0d24 <_mAppVer-0xef2f2e0>
   4:	72412820 	subvc	r2, r1, #32, 16	@ 0x200000
   8:	4e47206d 	cdpmi	0, 4, cr2, cr7, cr13, {3}
   c:	6f542055 	svcvs	0x00542055
  10:	68636c6f 	stmdavs	r3!, {r0, r1, r2, r3, r5, r6, sl, fp, sp, lr}^
  14:	206e6961 	rsbcs	r6, lr, r1, ror #18
  18:	332e3231 			@ <UNDEFINED> instruction: 0x332e3231
  1c:	6c65522e 	sfmvs	f5, 2, [r5], #-184	@ 0xffffff48
  20:	42282031 	eormi	r2, r8, #49	@ 0x31
  24:	646c6975 	strbtvs	r6, [ip], #-2421	@ 0xfffff68b
  28:	6d726120 	ldfvse	f6, [r2, #-128]!	@ 0xffffff80
  2c:	2e32312d 	rsfcssp	f3, f2, #5.0
  30:	29293533 	stmdbcs	r9!, {r0, r1, r4, r5, r8, sl, ip, sp}
  34:	2e323120 	rsfcssp	f3, f2, f0
  38:	20312e33 	eorscs	r2, r1, r3, lsr lr
  3c:	33323032 	teqcc	r2, #50	@ 0x32
  40:	36323630 			@ <UNDEFINED> instruction: 0x36323630
	...

Disassembly of section .ARM.attributes:

00000000 <.ARM.attributes>:
   0:	00002941 	andeq	r2, r0, r1, asr #18
   4:	61656100 	cmnvs	r5, r0, lsl #2
   8:	01006962 	tsteq	r0, r2, ror #18
   c:	0000001f 	andeq	r0, r0, pc, lsl r0
  10:	2d453705 	stclcs	7, cr3, [r5, #-20]	@ 0xffffffec
  14:	0d06004d 	stceq	0, cr0, [r6, #-308]	@ 0xfffffecc
  18:	02094d07 	andeq	r4, r9, #448	@ 0x1c0
  1c:	0412060a 	ldreq	r0, [r2], #-1546	@ 0xfffff9f6
  20:	01180117 	tsteq	r8, r7, lsl r1
  24:	011b011a 	tsteq	fp, sl, lsl r1
  28:	Address 0x28 is out of bounds.


Disassembly of section .debug_frame:

00000000 <.debug_frame>:
   0:	0000000c 	andeq	r0, r0, ip
   4:	ffffffff 			@ <UNDEFINED> instruction: 0xffffffff
   8:	7c020001 	stcvc	0, cr0, [r2], {1}
   c:	000d0c0e 	andeq	r0, sp, lr, lsl #24
  10:	00000024 	andeq	r0, r0, r4, lsr #32
  14:	00000000 	andeq	r0, r0, r0
  18:	10000038 	andne	r0, r0, r8, lsr r0
  1c:	0000001a 	andeq	r0, r0, sl, lsl r0
  20:	810c0e41 	tsthi	ip, r1, asr #28
  24:	83028203 	movwhi	r8, #8707	@ 0x2203
  28:	180e4101 	stmdane	lr, {r0, r8, lr}
  2c:	410c0e49 	tstmi	ip, r9, asr #28
  30:	0ec1c2c3 	cdpeq	2, 12, cr12, cr1, cr3, {6}
  34:	00000000 	andeq	r0, r0, r0
  38:	0000000c 	andeq	r0, r0, ip
  3c:	00000000 	andeq	r0, r0, r0
  40:	10000054 	andne	r0, r0, r4, asr r0
  44:	00000010 	andeq	r0, r0, r0, lsl r0
  48:	0000000c 	andeq	r0, r0, ip
  4c:	00000000 	andeq	r0, r0, r0
  50:	10000064 	andne	r0, r0, r4, rrx
  54:	0000002c 	andeq	r0, r0, ip, lsr #32
  58:	00000024 	andeq	r0, r0, r4, lsr #32
  5c:	00000000 	andeq	r0, r0, r0
  60:	10000090 	mulne	r0, r0, r0
  64:	00000014 	andeq	r0, r0, r4, lsl r0
  68:	80100e41 	andshi	r0, r0, r1, asr #28
  6c:	82038104 	andhi	r8, r3, #4, 2
  70:	41018302 	tstmi	r1, r2, lsl #6
  74:	0e46180e 	cdpeq	8, 4, cr1, cr6, cr14, {0}
  78:	c2c34110 	sbcgt	r4, r3, #16, 2
  7c:	000ec0c1 	andeq	ip, lr, r1, asr #1
  80:	00000038 	andeq	r0, r0, r8, lsr r0
  84:	00000000 	andeq	r0, r0, r0
  88:	100000a4 	andne	r0, r0, r4, lsr #1
  8c:	0000013c 	andeq	r0, r0, ip, lsr r1
  90:	841c0e42 	ldrhi	r0, [ip], #-3650	@ 0xfffff1be
  94:	86068507 	strhi	r8, [r6], -r7, lsl #10
  98:	8a048705 	bhi	121cb4 <_mAppVer-0xfede350>
  9c:	8e028b03 	vmlahi.f64	d8, d2, d3
  a0:	480e4301 	stmdami	lr, {r0, r8, r9, lr}
  a4:	1c0e0a5b 			@ <UNDEFINED> instruction: 0x1c0e0a5b
  a8:	cacbce42 	bgt	ff2f39b8 <__bss_end+0x7f2f398c>
  ac:	c4c5c6c7 	strbgt	ip, [r5], #1735	@ 0x6c7
  b0:	0b42000e 	bleq	10800f0 <_mAppVer-0xef7ff14>
  b4:	0e0a6302 	cdpeq	3, 0, cr6, cr10, cr2, {0}
  b8:	000b421c 	andeq	r4, fp, ip, lsl r2
