main:
	make --no-print-directory -C src

clean:
	make --no-print-directory -C src clean

unit_test:
	make --no-print-directory -C src unit_test

rebuild: clean main