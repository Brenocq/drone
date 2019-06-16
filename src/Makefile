# Text style
RED    = \033[0;31m
GREEN  = \033[0;32m
NC     = \033[0m
BOLD   = \033[1m

.PHONY: all

MQTTLIB_A = paho-mqtt3a
MQTTLIB_AS = paho-mqtt3as

MQTTLIB_A_NAME = lib${MQTTLIB_A}.so.1.0
MQTTLIB_A_TARGET = ${blddir}/${MQTTLIB_A_NAME}

FLAGS_EXES = $(LDFLAGS) -I ${srcdir} ${START_GROUP} -lpthread -lrt -lssl -lcrypto ${END_GROUP} -L ${blddir}

SAMPLE_FILES_A = MQTTAsync_subscribe MQTTAsync_publish
ASYNC_SAMPLES = ${addprefix ${blddir}/samples/,${SAMPLE_FILES_A}}

.PHONY: all clean


all:
	@echo "${GREEN}${BOLD}Making MQTT...${NC}"
	@$(MAKE) -C ../lib/MQTT/paho.mqtt.c
	@echo "${GREEN}${BOLD}End of MQTT${NC}"
	@echo "${GREEN}${BOLD}Making SDK...${NC}"
	@$(MAKE) -C ../lib/SDK/ARDroneLib/Soft/Build USE_LINUX=yes
	@echo "${GREEN}${BOLD}End of SDK${NC}"
	@echo "${GREEN}${BOLD}Making drone_publish...${NC}"
	@$(MAKE) -C drone_publish/Build USE_LINUX=yes
	@echo "${GREEN}${BOLD}End of drone_publish${NC}"

$(MAKECMDGOALS):
	@$(MAKE) -C ../lib/MQTT/paho.mqtt.c $(MAKECMDGOALS)
	@$(MAKE) -C ../../ARDroneLib/Soft/Build USE_LINUX=yes $(MAKECMDGOALS)
	@$(MAKE) -C drone_publish/Build USE_LINUX=yes $(MAKECMDGOALS)

clean:
	@$(MAKE) -C ../lib/MQTT/paho.mqtt.c clean
