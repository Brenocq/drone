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
