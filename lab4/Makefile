CС=gcc
CFLAGS= -Wall -Werror -Wextra -std=c99
CLIBS= -lm

TEST_TEMPLATES_DIR=./test_templates# Это директория с шаблонами тестов (если вы их разместите в той же директории что и лабы пишите ./)
EXECUTABLES=$(SOURCES:.c=.a)
BASH=bash


SUCCESS_CMD=$(BASH) $(TEST_TEMPLATES_DIR)/success_cmd
FAILED_CMD=$(BASH) $(TEST_TEMPLATES_DIR)/failed_cmd

SUCCESS_RFILE_CMD=$(BASH) $(TEST_TEMPLATES_DIR)/success_rfile_cmd

SUCCESS_OFILE=$(BASH) $(TEST_TEMPLATES_DIR)/success_ofile
FAILED_OFILE=$(BASH) $(TEST_TEMPLATES_DIR)/failed_ofile

SUCCESS_RFILE_OFILE=$(BASH) $(TEST_TEMPLATES_DIR)/success_rfile_ofile

SUCCESS_IFILE_OFILE=$(BASH) $(TEST_TEMPLATES_DIR)/success_ifile_ofile
SUCCESS_IFILE_RFILE_OFILE=$(BASH) $(TEST_TEMPLATES_DIR)/success_ifile_rfile_ofile
FAILED_IFILE_OFILE=$(BASH) $(TEST_TEMPLATES_DIR)/failed_ifile_ofile
FAILED_IFILE_RFILE_OFILE=$(BASH) $(TEST_TEMPLATES_DIR)/failed_ifile_rfile_ofile


.PHONY: all test clean

all:
	cd lib/mstring/ && make
	cd lib/vector/ && make
	cd lib/SystemErrors/ && make
	for dir in ex1 ex2; do \
		cd $$dir ;\
		make ;\
		mv $$dir.a ../$$dir.a ;\
		cd .. ;\
	done


clean: # Чтобы удалить все исполняемые файлы надо ввести команду make clean
	rm -r -f *.a
	rm -r -d ex2/out*.txt


# Принцип формирования названия выполняемого теста:
#
# (SUCESS|FAILED)[_IFILE][_RFILE](CMD|OFILE)
#		 1			2		3		 4
#
# 1){ОБЯЗАТЕЛЬНЫЙ} В зависимости от предполагаемого окончания теста мы выбираем либо успешный вариант - SUCCESS, либо провальный - FAILED
# 2){ОПЦИОНАЛЬНЫЙ} При необходимости ввода в консоль программы (использвуя scanf или аналоги) добавляется суффикс _IFILE
# 3){ОПЦИОНАЛЬНЫЙ} Если программа предполагает наличие выходного файла с данными добавляется суффикс _RFILE
# 4){ОБЯЗАТЕЛЬНЫЙ} В зависимости от того однострочный или многострочный вывод в консоль ожидается у программы выбираем окончание CMD - для однострочного вывода и OFILE для многострочного
#


# Все тесты разделены на категории по результату работы программы и формату ввода:
#
# В случае если ввод в программу только с помощью аругментов командной строки:
# 	В случае если вывод в консоль у программы однострочный:
# 		1) Успешный с выводом в консоль (вывод сравнивается со строкой) - $(SUCCESS_CMD)
# 		2) Провальный с выводом в консоль (вывод сравнивается со строкой) - $(FAILED_CMD)
# 		3) Успешный с выводом в консоль и в файл (вывод сравнивается со строкой, а выходной файл с подготовленным файлом) - $(SUCCESS_RFILE_CMD)
#
# 	В случае если вывод в консоль у программы многострочный:
# 		1) Успешный с выводом в консоль (вывод сравнивается со строками из файла) - $(SUCCESS_OFILE)
# 		2) Провальный с выводом в консоль (вывод сравнивается со строками из файла) - $(FAILED_OFILE)
# 		3) Успешный с выводом в консоль и в выходной файл (вывод сравнивается со строками из файла, а выходной файл с подготовленным файлом) - $(SUCCESS_RFILE_OFILE)
#
# В случае если ввод в консоль программы осуществляется из подготовленного файла а вывод у программы многострочный:
# 	1) Успешный с вводом из файла, выводом в консоль (вывод сравнивается со строками из файла) - $(SUCCESS_IFILE_OFILE)
# 	2) Успешный с водом из файла, выводом в консоль и выходной файл (вывод сравнивается со строками из файла, а выходной файл с подготовленным файлом) - $(SUCCESS_IFILE_RFILE_OFILE)
# 	3) Провальный с вводом из файла, выводом в консоль (вывод сравнивается со строками из файла) - $(FAILED_IFILE_OFILE)
#


# Использование тестов:
#
# 1) $(SUCCESS_CMD) "<вызов исполняемого файла с его аргументами>" "<ожидаемый в консоль вывод>"
# 2) $(FAILED_CMD) "<вызов исполняемого файла с его аргументами>" "<ожидаемый код возврата отличный от 0>" "<ожидаемый в консоль вывод>"
# 3) $(SUCCESS_RFILE_CMD) "<вызов исполняемого файла с его аргументами>" "<ожидаемый в консоль вывод>" "<выходной файл>" "<файл с которым должен совпадать выходной файл>"
#
# 1) $(SUCCESS_OFILE) "<вызов исполняемого файла с его аргументами>" "<файл с ожидаемым в консоль выводом>"
# 2) $(FAIED_OFILE) "<вызов исполняемого файла с его аргументами>" "<ожидаемый код возврата отличный от 0>" "<файл с ожидаемым в консоль выводом>"
# 3) $(SUCCESS_RFILE_OFILE) "<вызов исполняемого файла с его аргументами>" "<файл с ожидаемым в консоль выводом>" "<выходной файл>" "<файл с которым должен совпадать выходной файл>"
#
# 1) $(SUCCESS_IFILE_OFILE) "<вызов исполняемого файла с его аргументами>" "<файл данными которые вводятся в консоль через stdin>" "<файл с ожидаемым в консоль выводом>"
# 2) $(SUCCESS_IFILE_RFILE_OFILE) "<вызов исполняемого файла с его аргументами>" "<файл данными которые вводятся в консоль через stdin>" "<файл с ожидаемым в консоль выводом>" "<выходной файл>" "<файл с которым должен совпадать выходной файл>"
# 3) $(FAILED_IFILE_OFILE) "<вызов исполняемого файла с его аргументами>" "<ожидаемый код возврата отличный от 0>" "<файл данными которые вводятся в консоль через stdin>" "<файл с ожидаемым в консоль выводом>"



#
# Ниже приведены примеры тестов. В выводе после теста должна быть краткая информация о том что это был за тест. "TEST N PASSED" это не информативно и принято не будет.
# Символ @ необходимо писать для подавления лишнего вывода в консоль при выполнении make файла.
#



task_1_test_1:
	@$(FAILED_CMD) "ex1.a" 6 ""
	@echo "TEST 1 (Incorrect count args) PASSED"

task_1_test_2:
	@$(SUCCESS_OFILE) "ex1.a test_files/task_1_test_2_input" "test_files/task_1_test_2_correct_output"
	@echo "TEST 2 (def_name is full words) PASSED"

task_1_test_3:
	@$(SUCCESS_OFILE) "ex1.a test_files/task_1_test_3_input" "test_files/task_1_test_3_correct_output"
	@echo "TEST 3 (def_name is substring words) PASSED"

test_task_1: task_1_test_1 task_1_test_2 task_1_test_3

task_2_test_1:
	@$(FAILED_CMD) "ex2.a" 6 ""
	@echo "TEST 4 (Incorrect count args) PASSED"

task_2_test_2:
	@$(SUCCESS_OFILE) "ex2.a test_files/task_2_input_file" "test_files/task_2_test_2_correct_output_stdout"
	@echo "TEST 5(correct stdin) PASSED"

task_2_test_3:
	@$(SUCCESS_RFILE_OFILE) "ex2.a test_files/task_2_input_file" "test_files/task_2_test_2_correct_output_stdout" "test_files/out.txt" "test_files/task_2_test_2_correct_output_file1"
	@echo "TEST 6(correct out.txt) PASSED"

task_2_test_4:
	@$(SUCCESS_RFILE_OFILE) "ex2.a test_files/task_2_input_file" "test_files/task_2_test_2_correct_output_stdout" "test_files/out1.txt" "test_files/task_2_test_3_correct_output_file2"
	@echo "TEST 6(correct out1.txt) PASSED"

task_2_test_5:
	@$(SUCCESS_RFILE_OFILE) "ex2.a test_files/task_2_input_file" "test_files/task_2_test_2_correct_output_stdout" "test_files/out2.txt" "test_files/task_2_test_4_correct_output_file3"
	@echo "TEST 7(correct out2.txt) PASSED"

task_2_test_6 :
	@$(SUCCESS_RFILE_OFILE) "ex2.a test_files/task_2_input_file" "test_files/task_2_test_2_correct_output_stdout" "test_files/out_c.txt" "test_files/task_2_test_5_correct_output_file4"
	@echo "TEST 8(correct out_c.txt) PASSED"




test_task_2: task_2_test_1 task_2_test_2 task_2_test_3 task_2_test_4 task_2_test_5  task_2_test_6

test: test_task_1 test_task_2