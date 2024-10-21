CC=gcc
CFLAGS=-Wall -Werror -Wextra
CLIBS=-lm
BASH=bash

SOURCES=Lab2_1/1.c Lab2_2/2.c Lab2_3/3.c Lab2_4/4.c Lab2_5/5.c Lab2_7/7.c Lab2_8/8.c Lab2_9/9.c# Тут вы перечислятете файлы с вашими лабами по 1 файлу на задание
TEST_TEMPLATES_DIR=test_templates# Это директория с шаблонами тестов (если вы их разместите в той же директории что и лабы пишите ./)

SUCCESS_CMD = ./$(TARGET)
FAILED_CMD = ./$(TARGET) || echo "ERROR"


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


.PHONY: all clean

all:
	for dir in Lab2_1 Lab2_2 Lab2_3 Lab2_4 Lab2_5 Lab2_7 Lab2_8 Lab2_9; do \
		cd $$dir ;\
		make ;\
		mv *.a .. ;\
		cd .. ;\
	done



clean: # Чтобы удалить все исполняемые файлы надо ввести команду make clean
	rm -r -f Lab2_*/*.a

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


#test_command_args_1:
#	@$(FAILED_CMD) "Lab2_1/1.a" 2 "Ошибка: недостаточно аргументов"
#	@echo "TEST 1 PASSED"

#test_task_1: test_command_args_1 

# Правило для тестирования
test: $(TEST_TARGETS)
	@echo "Все тесты прошли успешно"

test_task1_command_args_1:
	@$(FAILED_CMD) "1.a" 2 "Ввод: <флаг> <строка>"
	@echo "TEST 1 PASSED"

test_task1_lflag_2:
	@$(SUCCESS_CMD) "1.a -l HelloWorld" "Длина: 10"
	@echo "TEST 2 L-FLAG PASSED"

test_task1_rflag_3:
	@$(SUCCESS_CMD) "1.a -r HelloWorld" "Реверс: dlroWolleH"
	@echo "TEST 3 R-FLAG PASSED"

test_task1_uflag_4:
	@$(SUCCESS_CMD) "1.a -u HelloWorld" "Верхний регистр на нечётных позициях: HElLoWoRlD"
	@echo "TEST 4 U-FLAG PASSED"

test_task1_nflag_5:
	@$(SUCCESS_CMD) "1.a -n H3ll0 W0rld!" "Отсортировано: 30Hll"
	@echo "TEST 5 N-FLAG PASSED"

test_task1_cflag_6:
	@$(SUCCESS_CMD) "1.a -c 1 2 3 4 5 6" "Конкатенация: 23465"
	@echo "TEST 6 C-FLAG PASSED"


test_task_1: test_task1_command_args_1 test_task1_lflag_2 test_task1_rflag_3 test_task1_uflag_4 test_task1_nflag_5 test_task1_cflag_6
	@echo "ALL TESTS TASK 1 PASSED"
#------------------------------------------------------------------------

#------------------------------------------------------------------------

test_task3_1:
	@$(SUCCESS_IFILE_OFILE) "3.a" "test_files/task_3_test_1_input" "test_files/task_3_test_1_output"
	@echo "TEST 9(task_3 sss) PASSED"


test_task3_2:
	@$(SUCCESS_IFILE_OFILE) "3.a" "test_files/task_3_test_2_input" "test_files/task_3_test_2_output"
	@echo "TEST 10 PASSED"

test_task3_3:
	@$(SUCCESS_IFILE_OFILE) "3.a" "test_files/task_3_test_3_input" "test_files/task_3_test_3_output"
	@echo "TEST 11 PASSED"

test_task_3: test_task3_1 test_task3_2 test_task3_3
	@echo "ALL TESTS TASK 3 PASSED"

test_task_allWithOut12:
	@./2.a
	@./4.a
	@./5.a
	@./7.a
	@./8.a
	@./9.a


test: test_task_1 test_task_3 test_task_allWithOut12


#------------------------------------------------------------------------
 #Здесь перечисляются все написанные вами тесты. Запуск тестов производится по команде make test


#-------------------------------------------------------------------------

