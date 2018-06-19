.PHONY: clean All

All:
	@echo "----------Building project:[ unit_tests -  ]----------"
	@cd "unit_tests" && "$(MAKE)" -f  "unit_tests.mk"
clean:
	@echo "----------Cleaning project:[ unit_tests -  ]----------"
	@cd "unit_tests" && "$(MAKE)" -f  "unit_tests.mk" clean
