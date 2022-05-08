TARGET_SOURCE=$(CURDIR)/../www
ATTACKER_SOURCE=$(CURDIR)/../bad
TARGET_DIR=$(CURDIR)/www
ATTACKER_DIR=$(CURDIR)/bad
ID_FILE=$(CURDIR)/.studentid
PARAMS_FILE=$(CURDIR)/.params

.PHONY: all clean gen_db

all: $(TARGET_DIR) $(ATTACKER_DIR)


$(TARGET_DIR): $(PARAMS_FILE) $(ID_FILE)
	cp -r $(TARGET_SOURCE) $(CURDIR)
	$(CURDIR)/gen_target.sh "$(TARGET_DIR)" "$(PARAMS_FILE)" "$(ID_FILE)"

$(ATTACKER_DIR): $(PARAMS_FILE) $(ID_FILE)
	cp -r $(ATTACKER_SOURCE) $(CURDIR)
	$(CURDIR)/gen_attacker.sh "$(ATTACKER_DIR)" "$(PARAMS_FILE)" "$(ID_FILE)"

$(PARAMS_FILE): $(ID_FILE)
	$(CURDIR)/gen_params.sh $@

$(ID_FILE):
	$(CURDIR)/gen_userid.sh $@

gen_db: $(CURDIR)/setup.sql $(CURDIR)/table1.sql $(CURDIR)/table2.sql $(PARAMS_FILE) $(ID_FILE)
	$(CURDIR)/gen_db.sh $^

clean:
	rm -rf $(PARAMS_FILE) $(ID_FILE) $(TARGET_DIR) $(ATTACKER_DIR)

