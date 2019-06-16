RED   = \033[0;31m# Red color
GREEN = \033[0;32m# GREEN color
NC    = \033[0m# No color

.PHONY:

all:
	@echo "${GREEN}Making MQTT Makefile...${NC}"
	@$(MAKE) -C ../lib/MQTT/paho.mqtt.c
	@echo "${GREEN}End of MQTT Makefile${NC}"
	@echo "${GREEN}Making SDK ...${NC}"
	@$(MAKE) -C ../lib/SDK/ARDroneLib/Soft/Build USE_LINUX=yes        
	@echo "${GREEN}End of SDK${NC}"
	@echo "${RED}Making target: drone_publish${NC}"
	@$(MAKE) -C drone_publish/Build USE_LINUX=yes
	@echo "${RED}End of target${NC}"

$(MAKECMDGOALS):
	@$(MAKE) -C ../lib/MQTT/paho.mqtt.c $(MAKECMDGOALS)
	@$(MAKE) -C ../../ARDroneLib/Soft/Build USE_LINUX=yes $(MAKECMDGOALS)
        @$(MAKE) -C drone_publish/Build USE_LINUX=yes $(MAKECMDGOALS)
