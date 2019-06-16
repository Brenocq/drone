RED   = \033[0;31m# Red color
GREEN = \033[0;32m# GREEN color
NC    = \033[0m# No color

all:
	@echo "${GREEN}Making MQTT Makefile...${NC}"
	@$(MAKE) -C ../lib/MQTT/paho.mqtt.c
	@echo "${GREEN}End of MQTT Makefile${NC}"

clean:
	@$(MAKE) -C ../lib/MQTT/paho.mqtt.c clean
