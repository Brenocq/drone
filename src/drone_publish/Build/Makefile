## Begin MQTT variables
CC ?= gcc
MQTTfolder = $(shell pwd)/../../../lib/MQTT/paho.mqtt.c/
srcdir = ${MQTTfolder}src
blddir = ${MQTTfolder}build/output

MQTTLIB_A = paho-mqtt3a
MQTTLIB_AS = paho-mqtt3as

MQTTLIB_A_NAME = lib${MQTTLIB_A}.so.1.0
MQTTLIB_A_TARGET = ${blddir}/${MQTTLIB_A_NAME}

FLAGS_EXES = $(LDFLAGS) -I ${srcdir} ${START_GROUP} -lpthread -lrt -lssl -lcrypto ${END_GROUP} -L ${blddir}

SAMPLE_FILES_A = MQTTAsync_subscribe MQTTAsync_publish
ASYNC_SAMPLES = ${addprefix ${blddir}/samples/,${SAMPLE_FILES_A}}

## End MQTT variables

SDK_PATH:=$(shell pwd)/../../../lib/SDK/ARDroneLib
PC_TARGET=yes
USE_LINUX=yes

ifdef MYKONOS
   include $(ARDRONE_CUSTOM_CONFIG)
   include $(ARDRONE_BUILD_CONFIG)
else
   include $(SDK_PATH)/Soft/Build/custom.makefile
   include $(SDK_PATH)/Soft/Build/config.makefile
endif

ifeq "$(RELEASE_BUILD)" "yes"
   ARDRONE_TARGET_DIR=$(shell pwd)/../../Build/Release
else
   ARDRONE_TARGET_DIR=$(shell pwd)/../../Build/Debug
endif

TARGET=drone_publish

SRC_DIR:=$(shell pwd)/../Sources

# Define application source files
GENERIC_BINARIES_SOURCE_DIR:=$(SRC_DIR)

GENERIC_BINARIES_COMMON_SOURCE_FILES+=			\
   Navdata/navdata.c    \
   Video/video_stage.c

GENERIC_INCLUDES+=					\
	$(SRC_DIR) \
	$(LIB_DIR) \
	$(SDK_PATH)/Soft/Common \
	$(SDK_PATH)/Soft/Lib \
	$(srcdir)

GENERIC_TARGET_BINARIES_PREFIX=

GENERIC_TARGET_BINARIES_DIR=$(ARDRONE_TARGET_DIR)

GENERIC_BINARIES_SOURCE_ENTRYPOINTS+=			\
   ardrone_testing_tool.c

GENERIC_INCLUDES:=$(addprefix -I,$(GENERIC_INCLUDES))

GENERIC_LIB_PATHS=-L$(GENERIC_TARGET_BINARIES_DIR)
GENERIC_LIBS=-lpc_ardrone -lgtk-x11-2.0 -lrt -l${MQTTLIB_AS} -l${MQTTLIB_A}
 
SDK_FLAGS+="USE_APP=yes"
SDK_FLAGS+="APP_ID=linux_sdk_demo"

export GENERIC_CFLAGS
export GENERIC_LIBS
export GENERIC_LIB_PATHS
export GENERIC_INCLUDES
export GENERIC_BINARIES_SOURCE_DIR
export GENERIC_BINARIES_COMMON_SOURCE_FILES
export GENERIC_TARGET_BINARIES_PREFIX
export GENERIC_TARGET_BINARIES_DIR
export GENERIC_BINARIES_SOURCE_ENTRYPOINTS

# Bug fix ...
export GENERIC_LIBRARY_SOURCE_DIR=$(GENERIC_BINARIES_SOURCE_DIR)

.PHONY: $(TARGET) build_libs

all: build_libs $(TARGET)

$(TARGET):
	@echo "${GREEN}${BOLD}Making target...${NC}"
	@$(MAKE) -C $(SDK_PATH)/VP_SDK/Build $(TMP_SDK_FLAGS) $(SDK_FLAGS) $(MAKECMDGOALS) USE_LINUX=yes
	mv $(ARDRONE_TARGET_DIR)/ardrone_testing_tool $(TARGET)
	mv $(TARGET) $(ARDRONE_TARGET_DIR)/

${ASYNC_SAMPLES}: ${blddir}/samples/%: ${srcdir}/samples/%.c $(MQTTLIB_A_TARGET)
	${CC} -o ${ASYNC_SAMPLES} $< -l${MQTTLIB_AS} ${FLAGS_EXES}

$(MAKECMDGOALS): build_libs
	@$(MAKE) -C $(SDK_PATH)/VP_SDK/Build $(TMP_SDK_FLAGS) $(SDK_FLAGS) $(MAKECMDGOALS) USE_LINUX=yes

build_libs:		
	@$(MAKE) -C $(SDK_PATH)/Soft/Build $(TMP_SDK_FLAGS) $(SDK_FLAGS) $(MAKECMDGOALS) USE_LINUX=yes
