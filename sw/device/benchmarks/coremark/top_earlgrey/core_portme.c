/*
        File : core_portme.c
*/
/*
        Author : Shay Gal-On, EEMBC
        Legal : TODO!
*/
#include "sw/device/benchmarks/coremark/top_earlgrey/core_portme.h"
#include "sw/vendor/eembc_coremark/coremark.h"
#include "sw/device/lib/oled_driver.h"

#if VALIDATION_RUN
volatile ee_s32 seed1_volatile = 0x3415;
volatile ee_s32 seed2_volatile = 0x3415;
volatile ee_s32 seed3_volatile = 0x66;
#endif
#if PERFORMANCE_RUN
volatile ee_s32 seed1_volatile = 0x0;
volatile ee_s32 seed2_volatile = 0x0;
volatile ee_s32 seed3_volatile = 0x66;
#endif
#if PROFILE_RUN
volatile ee_s32 seed1_volatile = 0x8;
volatile ee_s32 seed2_volatile = 0x8;
volatile ee_s32 seed3_volatile = 0x8;
#endif
volatile ee_s32 seed4_volatile = ITERATIONS;
volatile ee_s32 seed5_volatile = 0;
/* Porting : Timing functions
        How to capture time and convert to seconds must be ported to whatever is
   supported by the platform. e.g. Read value from on board RTC, read value from
   cpu clock cycles performance counter etc. Sample implementation for standard
   time.h and windows.h definitions included.
*/
CORETIMETYPE barebones_clock() {
  ee_u32 result;
  __asm__ volatile("csrr %0, mcycle;" : "=r"(result));
  return result;
}
/* Define : TIMER_RES_DIVIDER
        Divider to trade off timer resolution and total time that can be
   measured.

        Use lower values to increase resolution, but make sure that overflow
   does not occur. If there are issues with the return value overflowing,
   increase this value.
        */
#define GETMYTIME(_t) (*_t = barebones_clock())
#define MYTIMEDIFF(fin, ini) ((fin) - (ini))
#define TIMER_RES_DIVIDER 1
#define SAMPLE_TIME_IMPLEMENTATION 1
#define CLOCKS_PER_SEC 25000000
#define EE_TICKS_PER_SEC (CLOCKS_PER_SEC / TIMER_RES_DIVIDER)

void pcount_reset() {
  asm volatile(
      "csrw minstret,       x0\n"
      "csrw mcycle,         x0\n"
      "csrw mhpmcounter3,   x0\n"
      "csrw mhpmcounter4,   x0\n"
      "csrw mhpmcounter5,   x0\n"
      "csrw mhpmcounter6,   x0\n"
      "csrw mhpmcounter7,   x0\n"
      "csrw mhpmcounter8,   x0\n"
      "csrw mhpmcounter9,   x0\n"
      "csrw mhpmcounter10,  x0\n"
      "csrw mhpmcounter11,  x0\n"
      "csrw mhpmcounter12,  x0\n"
      "csrw mhpmcounter13,  x0\n"
      "csrw mhpmcounter14,  x0\n"
      "csrw mhpmcounter15,  x0\n"
      "csrw mhpmcounter16,  x0\n"
      "csrw mhpmcounter17,  x0\n"
      "csrw mhpmcounter18,  x0\n"
      "csrw mhpmcounter19,  x0\n"
      "csrw mhpmcounter20,  x0\n"
      "csrw mhpmcounter21,  x0\n"
      "csrw mhpmcounter22,  x0\n"
      "csrw mhpmcounter23,  x0\n"
      "csrw mhpmcounter24,  x0\n"
      "csrw mhpmcounter25,  x0\n"
      "csrw mhpmcounter26,  x0\n"
      "csrw mhpmcounter27,  x0\n"
      "csrw mhpmcounter28,  x0\n"
      "csrw mhpmcounter29,  x0\n"
      "csrw mhpmcounter30,  x0\n"
      "csrw mhpmcounter31,  x0\n"
      "csrw minstreth,      x0\n"
      "csrw mcycleh,        x0\n"
      "csrw mhpmcounter3h,  x0\n"
      "csrw mhpmcounter4h,  x0\n"
      "csrw mhpmcounter5h,  x0\n"
      "csrw mhpmcounter6h,  x0\n"
      "csrw mhpmcounter7h,  x0\n"
      "csrw mhpmcounter8h,  x0\n"
      "csrw mhpmcounter9h,  x0\n"
      "csrw mhpmcounter10h, x0\n"
      "csrw mhpmcounter11h, x0\n"
      "csrw mhpmcounter12h, x0\n"
      "csrw mhpmcounter13h, x0\n"
      "csrw mhpmcounter14h, x0\n"
      "csrw mhpmcounter15h, x0\n"
      "csrw mhpmcounter16h, x0\n"
      "csrw mhpmcounter17h, x0\n"
      "csrw mhpmcounter18h, x0\n"
      "csrw mhpmcounter19h, x0\n"
      "csrw mhpmcounter20h, x0\n"
      "csrw mhpmcounter21h, x0\n"
      "csrw mhpmcounter22h, x0\n"
      "csrw mhpmcounter23h, x0\n"
      "csrw mhpmcounter24h, x0\n"
      "csrw mhpmcounter25h, x0\n"
      "csrw mhpmcounter26h, x0\n"
      "csrw mhpmcounter27h, x0\n"
      "csrw mhpmcounter28h, x0\n"
      "csrw mhpmcounter29h, x0\n"
      "csrw mhpmcounter30h, x0\n"
      "csrw mhpmcounter31h, x0\n");
}

void pcount_enable(int enable) {
  // Note cycle is disabled with everything else
  unsigned int inhibit_val = enable ? 0x0 : 0xFFFFFFFF;
  // mucounteren == mcountinhibit but binutils doesn't seem to known the
  // mcountinhibit name
  asm volatile("csrw  mucounteren, %0\n" : : "r"(inhibit_val));
}

void pcount_read(uint32_t pcount_out[]) {
  asm volatile(
      "csrr %0, minstret\n"
      : "=r"(pcount_out[0])
  );

  asm volatile(
      "csrr %0, mhpmcounter3\n"
      : "=r"(pcount_out[1])
  );

  asm volatile(
      "csrr %0, mhpmcounter4\n"
      : "=r"(pcount_out[2])
  );

  asm volatile(
      "csrr %0, mhpmcounter5\n"
      : "=r"(pcount_out[3])
  );

  asm volatile(
      "csrr %0, mhpmcounter6\n"
      : "=r"(pcount_out[4])
  );

  asm volatile(
      "csrr %0, mhpmcounter7\n"
      : "=r"(pcount_out[5])
  );

  asm volatile(
      "csrr %0, mhpmcounter8\n"
      : "=r"(pcount_out[6])
  );

  asm volatile(
      "csrr %0, mhpmcounter9\n"
      : "=r"(pcount_out[7])
  );

  asm volatile(
      "csrr %0, mhpmcounter10\n"
      : "=r"(pcount_out[8])
  );
}

const char* pcount_names[] = {
  "Instructions Retired",
  "LSU Busy",
  "IFetch wait",
  "Loads",
  "Stores",
  "Jumps",
  "Branches",
  "Taken Branches",
  "Compressed Instructions"
};

const uint32_t pcount_num = 9;

void dump_pcounts() {
  uint32_t pcounts[9];

  pcount_read(pcounts);
  ee_printf("Performance Counters\n"
            "--------------------\n");
  for (uint32_t i = 0;i  < pcount_num; ++i) {
    ee_printf("%s: %u\n", pcount_names[i], pcounts[i]);
  }
  ee_printf("\n");
}

void output_coremark_mhz() {
  uint32_t cycles;
  float coremark_mhz;
  char oled_out_buf[128];

  cycles = barebones_clock();

  coremark_mhz = 1000000.0f / ((float)cycles / (float)ITERATIONS);


  ee_printf("CoreMark / MHz: %f\n", coremark_mhz);

  ee_vsprintf(oled_out_buf, "%.2f", coremark_mhz);

  oled_clear(1);

  oled_write_str("CoreMark / MHz", 0, 2);
  oled_write_str(oled_out_buf, 2, 12);

  oled_write_disp();
}

/** Define Host specific (POSIX), or target specific global time variables. */
static CORETIMETYPE start_time_val, stop_time_val;

/* Function : start_time
        This function will be called right before starting the timed portion of
   the benchmark.

        Implementation may be capturing a system timer (as implemented in the
   example code) or zeroing some system parameters - e.g. setting the cpu clocks
   cycles to 0.
*/
void start_time(void) {
  ee_printf("#*#*#*\n");

  oled_clear(1);

  oled_write_str("CoreMark", 1, 8);

  oled_write_disp();

  ee_printf("\n");
  ee_printf("-----------------------------------------------------\n");
  ee_printf(" _____                    ___  ___              _    \n");
  ee_printf("/  __ \\                   |  \\/  |             | |   \n");
  ee_printf("| /  \\/  ___   _ __   ___ | .  . |  __ _  _ __ | | __\n");
  ee_printf("| |     / _ \\ | '__| / _ \\| |\\/| | / _` || '__|| |/ /\n");
  ee_printf("| \\__/\\| (_) || |   |  __/| |  | || (_| || |   |   < \n");
  ee_printf(" \\____/ \\___/ |_|    \\___|\\_|  |_/ \\__,_||_|   |_|\\_\\\n");
  ee_printf("-----------------------------------------------------\n");
  ee_printf("\n");

  pcount_enable(0);
  pcount_reset();
  pcount_enable(1);
  GETMYTIME(&start_time_val);
}
/* Function : stop_time
        This function will be called right after ending the timed portion of the
   benchmark.

        Implementation may be capturing a system timer (as implemented in the
   example code) or other system parameters - e.g. reading the current value of
   cpu cycles counter.
*/
void stop_time(void) {
  GETMYTIME(&stop_time_val);
  pcount_enable(0);
}
/* Function : get_time
        Return an abstract "ticks" number that signifies time on the system.

        Actual value returned may be cpu cycles, milliseconds or any other
   value, as long as it can be converted to seconds by <time_in_secs>. This
   methodology is taken to accomodate any hardware or simulated platform. The
   sample implementation returns millisecs by default, and the resolution is
   controlled by <TIMER_RES_DIVIDER>
*/
CORE_TICKS get_time(void) {
  CORE_TICKS elapsed = (CORE_TICKS)(MYTIMEDIFF(stop_time_val, start_time_val));
  return elapsed;
}
/* Function : time_in_secs
        Convert the value returned by get_time to seconds.

        The <secs_ret> type is used to accomodate systems with no support for
   floating point. Default implementation implemented by the EE_TICKS_PER_SEC
   macro above.
*/
secs_ret time_in_secs(CORE_TICKS ticks) {
  return ((secs_ret)ticks) / ((secs_ret)EE_TICKS_PER_SEC);
}

ee_u32 default_num_contexts = 1;

/* Function : portable_init
        Target specific initialization code
        Test for some common mistakes.
*/
void portable_init(core_portable *p, int *argc, char *argv[]) {
  uart_init(UART_BAUD_RATE);

  if (sizeof(ee_ptr_int) != sizeof(ee_u8 *)) {
    ee_printf(
        "ERROR! Please define ee_ptr_int to a type that holds a pointer!\n");
  }
  if (sizeof(ee_u32) != 4) {
    ee_printf("ERROR! Please define ee_u32 to a 32b unsigned type!\n");
  }
  p->portable_id = 1;
}
/* Function : portable_fini
        Target specific final code
*/
void portable_fini(core_portable *p) {
  output_coremark_mhz();
  dump_pcounts();
  ee_printf("#*#*#*\n");
  p->portable_id = 0;
}

