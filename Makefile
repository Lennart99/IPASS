.PHONY: clean All

All:
	@echo "----------Building project:[ Opdracht5_6 -  ]----------"
	@cd "Opdracht5_6" && "$(MAKE)" -f  "Opdracht5_6.mk"
clean:
	@echo "----------Cleaning project:[ Opdracht5_6 -  ]----------"
	@cd "Opdracht5_6" && "$(MAKE)" -f  "Opdracht5_6.mk" clean
