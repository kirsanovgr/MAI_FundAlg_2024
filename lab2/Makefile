CС=gcc
CFLAGS= -Wall -Werror -Wextra
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
	for dir in ex1 ex2 ex3 ex4 ex5 ex6 ex7 ex8 ex9 ex10; do \
		cd $$dir ;\
		make ;\
		mv $$dir.a ../$$dir.a ;\
		cd .. ;\
	done


clean: # Чтобы удалить все исполняемые файлы надо ввести команду make clean
	rm -r -f *.a


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



test_task1_command_args_1:
	@$(FAILED_CMD) "ex1.a" 6 "Incorrect options"
	@echo "TEST 1 (task_1 COUNT ARGS=0) PASSED"

test_task1_lflag_2:
	@$(SUCCESS_CMD) "ex1.a -l HelloWorld" "10"
	@echo "TEST 2 L-FLAG(task_1 CORRECT COUNT ARGS) PASSED"

test_task1_lflag_3:
	@$(FAILED_CMD) "ex1.a -l HelloWorld friend" 6 "Incorrect options"
	@echo "TEST 3 L-FLAG(task_1 INCORRECT COUNT ARGS) PASSED"


test_task1_rflag_4:
	@$(SUCCESS_CMD) "ex1.a -r HelloWorld" "dlroWolleH"
	@echo "TEST 4 R-FLAG(task_1 CORRECT COUNT ARGS) PASSED"

test_task1_uflag_5:
	@$(SUCCESS_CMD) "ex1.a -u HelloWorldMyFriend" "HElLoWoRlDMYFRiEnD"
	@echo "TEST 5 U-FLAG(task_1 CORRECT COUNT ARGS) PASSED"

test_task1_nflag_6:
	@$(SUCCESS_CMD) "ex1.a -n H9e..1l2l3o4W5o0rldMyFriend" "9123450HelloWorldMyFriend.."
	@echo "TEST 6 N-FLAG(task_1 CORRECT COUNT ARGS) PASSED"


test_task_1: test_task1_command_args_1 test_task1_lflag_2 test_task1_lflag_3 test_task1_rflag_4 test_task1_uflag_5 test_task1_nflag_6
	@echo "ALL TESTS TASK 1 PASSED"


test_task3_1:
	@$(SUCCESS_IFILE_OFILE) "ex3.a" "test_files/task_3_test_1_input" "test_files/task_3_test_1_output"
	@echo "TEST 7(task_3 sss) PASSED"

test_task3_2:
	@$(SUCCESS_IFILE_OFILE) "ex3.a" "test_files/task_3_test_2_input" "test_files/task_3_test_2_output"
	@echo "TEST 8(task_3 many separators) PASSED"

test_task3_3:
	@$(SUCCESS_IFILE_OFILE) "ex3.a" "test_files/task_3_test_3_input" "test_files/task_3_test_3_output"
	@echo "TEST 9(task_3 ssss) PASSED"

test_task_3: test_task3_1 test_task3_2 test_task3_3
	@echo "ALL TESTS TASK 3 PASSED"

test_task_allWithOut13:
	@./ex2.a
	@./ex4.a
	@./ex5.a
	@./ex6.a
	@./ex7.a
	@./ex8.a
	@./ex9.a
	@./ex10.a


test: test_task_1 test_task_3 test_task_allWithOut13