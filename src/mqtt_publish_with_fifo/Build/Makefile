# Text style
RED    = \033[0;31m
GREEN  = \033[0;32m
NC     = \033[0m
BOLD   = \033[1m

.PHONY: all

CC ?= gcc
MQTTfolder = ../../../lib/MQTT/paho.mqtt.c/
MQTTsrc = ${MQTTfolder}src
MQTTbld = ${MQTTfolder}build/output

MQTTLIB_A = paho-mqtt3a
MQTTLIB_AS = paho-mqtt3as

MQTTLIB_A_NAME = lib${MQTTLIB_A}.so.1.0
MQTTLIB_A_TARGET = ${MQTTbld}/${MQTTLIB_A_NAME}

FLAGS_EXES = $(LDFLAGS) -I ${MQTTsrc} ${START_GROUP} -lpthread -lrt -lssl -lcrypto ${END_GROUP} -L ${MQTTbld}

DRONE_SRC = ../Sources
DRONE_BLD = .
DRONE_FILES_A = MQTTAsync_subscribe
DRONE_SAMPLES = ${addprefix ${DRONE_BLD}/,${DRONE_FILES_A}}

.PHONY: all clean

all: config.o
	@echo "${GREEN}${BOLD}Building...${NC}"
	@$(MAKE) ${DRONE_SAMPLES}
	@echo "${GREEN}${BOLD}End of build process${NC}"

init:
	@echo export LD_LIBRARY_PATH=$(subst src/test_subscriber/Build,lib/MQTT/paho.mqtt.c/build/output,$(shell pwd)) >> ~/.bashrc
	@echo "${GREEN}${BOLD}Added export files to bashrc${NC}"

${DRONE_SAMPLES}: ${DRONE_BLD}/%: ${DRONE_SRC}/%.c $(MQTTLIB_A_TARGET)
	@${CC} -o ${DRONE_SAMPLES} $< -l${MQTTLIB_AS} ${FLAGS_EXES}
	

config.o: ${DRONE_SRC}/config.h
	@${CC} ${DRONE_SRC}/config.h -c
	@echo "${GREEN}config.h compiled${NC}"

clean:
	@rm MQTTAsync_subscribe
	@echo "${GREEN}MQTTAsync_subscribe object-file deleted${NC}"


