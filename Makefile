.PHONY: all
all:
	PLATFORMIO_DISABLE_COLOR=true pio run

.PHONY: install
install:
	PLATFORMIO_DISABLE_COLOR=true pio run --target upload
