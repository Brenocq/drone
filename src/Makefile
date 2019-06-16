# Text style
RED   = \033[0;31m
GREEN = \033[0;32m
NC    = \033[0m
BOLD   = \033[1m

# Compile MQTT files
CC ?= gcc
MQTTfolder = ../lib/MQTT/paho.mqtt.c/
srcdir =${MQTTfolder}src
blddir = ${MQTTfolder}build/output

MQTTLIB_A = paho-mqtt3a
MQTTLIB_AS = paho-mqtt3as

MQTTLIB_A_NAME = lib${MQTTLIB_A}.so.1.0
MQTTLIB_A_TARGET = ${blddir}/${MQTTLIB_A_NAME}

FLAGS_EXES = $(LDFLAGS) -I ${srcdir} ${START_GROUP} -lpthread -lrt -lssl -lcrypto ${END_GROUP} -L ${blddir}

SAMPLE_FILES_A = MQTTAsync_subscribe MQTTAsync_publish
ASYNC_SAMPLES = ${addprefix ${blddir}/samples/,${SAMPLE_FILES_A}}

.PHONY: all clean

all:
	@echo "${GREEN}${BOLD}Making MQTT Makefile...${NC}"
	@$(MAKE) -C ../lib/MQTT/paho.mqtt.c
	@echo "${GREEN}${BOLD}End of MQTT Makefile${NC}"
	@make build

build:
	@make ${ASYNC_SAMPLES}
	@echo batata

${ASYNC_SAMPLES}: ${blddir}/samples/%: ${srcdir}/samples/%.c $(MQTTLIB_A_TARGET)
	@echo arroba
	${CC} -o ${ASYNC_SAMPLES} $< -l${MQTTLIB_AS} ${FLAGS_EXES}

clean:
	@$(MAKE) -C ../lib/MQTT/paho.mqtt.c clean
