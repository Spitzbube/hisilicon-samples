
CFLAGS += -DHI_DEMUX_PORT=32 \
          -DHI_DEMUX1_PORT=32 \
          -DHI_DEMUX2_PORT=32 \
          -DHI_DEMUX3_PORT=0 \
          -DHI_IF0_TYPE=2 \
          -DHI_IF0_BIT_SELECTOR=1 \
          -DHI_TSI0_TYPE=8 \
          -DHI_TSI0_CLK_PHASE_REVERSE=0 \
          -DHI_TSI0_BIT_SELECTOR=1 \
          -DHI_TSI1_TYPE=2 \
          -DHI_TSI1_CLK_PHASE_REVERSE=0 \
          -DHI_TSI1_BIT_SELECTOR=1 \
          -DHI_TSI2_TYPE=2 \
          -DHI_TSI2_CLK_PHASE_REVERSE=0 \
          -DHI_TSI2_BIT_SELECTOR=1 \
          -DHI_TSI3_TYPE=2 \
          -DHI_TSI3_CLK_PHASE_REVERSE=0 \
          -DHI_TSI3_BIT_SELECTOR=1 \
          -DHI_TSI4_TYPE=2 \
          -DHI_TSI4_CLK_PHASE_REVERSE=0 \
          -DHI_TSI4_BIT_SELECTOR=1 \
          -DHI_TSI5_TYPE=2 \
          -DHI_TSI5_CLK_PHASE_REVERSE=0 \
          -DHI_TSI5_BIT_SELECTOR=1

SYS_LIBS := -lpthread

COMMON_SRCS := hi_adp_hdmi.c \
               hi_adp_mpi.c

