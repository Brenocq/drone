# Text style
RED    = \033[0;31m
GREEN  = \033[0;32m
NC     = \033[0m
BOLD   = \033[1m

.PHONY: all

CC ?= gcc
MQTTfolder =../lib/MQTT/paho.mqtt.c/
srcdir = ${MQTTfolder}src
blddir = ${MQTTfolder}build/output

MQTTLIB_A = paho-mqtt3a
MQTTLIB_AS = paho-mqtt3as

MQTTLIB_A_NAME = lib${MQTTLIB_A}.so.1.0
MQTTLIB_A_TARGET = ${blddir}/${MQTTLIB_A_NAME}

FLAGS_EXES = $(LDFLAGS) -I ${srcdir} ${START_GROUP} -lpthread -lrt -lssl -lcrypto ${END_GROUP} -L ${blddir}

SAMPLE_FILES_A = MQTTAsync_subscribe MQTTAsync_publish
ASYNC_SAMPLES = ${addprefix ${blddir}/samples/,${SAMPLE_FILES_A}}

DRONE_SRC = drone_subscriber/Sources
DRONE_BLD = drone_subscriber/Build
DRONE_FILES_A = MQTTAsync_subscribe
DRONE_SAMPLES = ${addprefix ${DRONE_BLD}/,${DRONE_FILES_A}}
.PHONY: all clean


all:
#@echo "${GREEN}${BOLD}Making MQTT...${NC}"
#@$(MAKE) -C ../lib/MQTT/paho.mqtt.c
#@echo "${GREEN}${BOLD}End of MQTT${NC}"
#@${MAKE} ../lib/MQTT/paho.mqtt.c/build/output/samples/MQTTAsync_subscribe
#@echo "${GREEN}${BOLD}Making SDK...${NC}"
#@$(MAKE) -C ../lib/SDK/ARDroneLib/Soft/Build USE_LINUX=yes
#@echo "${GREEN}${BOLD}End of SDK${NC}"
#@echo "${GREEN}${BOLD}Making drone_publish...${NC}"
#@$(MAKE) -C drone_publish/Build USE_LINUX=yes
#@echo "${GREEN}${BOLD}End of drone_publish${NC}"
	@$(MAKE) ${DRONE_SAMPLES}

${ASYNC_SAMPLES}: ${blddir}/samples/%: ${srcdir}/samples/%.c $(MQTTLIB_A_TARGET)
	${CC} -o ${ASYNC_SAMPLES} $< -l${MQTTLIB_AS} ${FLAGS_EXES}

${DRONE_SAMPLES}: ${DRONE_BLD}/%: ${DRONE_SRC}/%.c $(MQTTLIB_A_TARGET)
	${CC} -o ${DRONE_SAMPLES} $< -l${MQTTLIB_AS} ${FLAGS_EXES}


clean:
	@$(MAKE) -C ../lib/MQTT/paho.mqtt.c clean
