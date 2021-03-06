# allows to call make Q= all and quiet will be disabled
Q=@ 

.PHONY: clean doc

all: debug

release:
	$(Q)$(MAKE) -C src/crypto release
	$(Q)$(MAKE) -C src/ release
	-$(Q)$(MAKE) -C tests/ all

debug:
	$(Q)$(MAKE) -C src/crypto debug
	$(Q)$(MAKE) -C src/ debug
	$(Q)$(MAKE) -C tests/ all

coverage:
	$(Q)$(MAKE) -C src/crypto coverage
	$(Q)$(MAKE) -C src/ coverage
	$(Q)$(MAKE) -C tests/ coverage

clean:
	$(Q)$(MAKE) -C src/crypto clean
	$(Q)$(MAKE) -C tests/ clean
	$(Q)$(MAKE) -C src/ clean
	$(Q)rm -Rf doc

test:
	$(Q)$(MAKE) -C tests/ test

doc:
	$(Q)doxygen
