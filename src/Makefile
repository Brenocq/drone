# Text style
RED    = \033[0;31m
GREEN  = \033[0;32m
NC     = \033[0m
BOLD   = \033[1m

.PHONY: all

all:
	@echo "${GREEN}${BOLD}Making MQTT...${NC}"
	@$(MAKE) -C ../lib/MQTT/paho.mqtt.c
	@echo "${GREEN}${BOLD}End of MQTT${NC}"
	@${MAKE} ../lib/MQTT/paho.mqtt.c/build/output/samples/MQTTAsync_subscribe
	@${MAKE} ./test_subscriber/Build
#@echo "${GREEN}${BOLD}Making SDK...${NC}"
#@$(MAKE) -C ../lib/SDK/ARDroneLib/Soft/Build USE_LINUX=yes
#@echo "${GREEN}${BOLD}End of SDK${NC}"
#@echo "${GREEN}${BOLD}Making drone_publish...${NC}"
#@$(MAKE) -C drone_publish/Build USE_LINUX=yes
#@echo "${GREEN}${BOLD}End of drone_publish${NC}"
#@$(MAKE) ${DRONE_SAMPLES}



clean:
	@$(MAKE) -C ../lib/MQTT/paho.mqtt.c clean
