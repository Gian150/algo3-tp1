import os, sys
import subprocess as s
import json
import random as r

big_test = ["t20", "t16", "t17", "t15", "t4", "t18", "t19"]

def test_correctitud(executable, solutions):
	for test in os.listdir("Tests_para_correctitud"):
		t = open("Tests_para_correctitud/" + test, "r")
		
		if (executable == "./Ej1" or executable == "./Ej2") and (test in big_test):
			print(test + "... es demasiado grande para esta aplicación")
		else:
			print(test + "....", end="")
			out = s.check_output([executable], stdin=t, shell=True)
			if(int(out) == solutions[test]):
				print("OK", flush=True)
			else:
				print("ERROR: E:" + str(int(out))+ ", R: " + str(solutions[test]), flush=True)

		t.close()

def correctitud(what_to_test):
	real_solutions = json.load(open("soluciones_tests"))

	if(what_to_test == "b" or what_to_test == "a"):
		print("Checking Backtracking")
		print("=================================")
		test_correctitud("./Ej1", real_solutions)
		print("\n")
	
	if(what_to_test == "bb" or what_to_test == "a"):
		print("Checking Backtracking with bounds")
		print("=================================")
		test_correctitud("./Ej2", real_solutions)
		print("\n")

	if(what_to_test == "d" or what_to_test == "a"):
		print("Checking dynamic algorithm")
		print("=================================")
		test_correctitud("./Ej3", real_solutions)


def generate_random_samples(max_q):
	print("Creating random cases files...")
	for n in range(1, max_q):
		for repetition in range(0, 20):
			f = open("Random_cases/Test_" + str(n) + "_" + str(repetition), "w")
			f.write(str(n) + "\n")
			for i in range(0, n):
				f.write(str(r.randrange(-150,150)) + " ")
			f.close()
	print("Random cases files generated")


def test_timing(exercise, repetition, max_length):
	csvData = open("experimentsData", "r")
	csvData.write("Length,Number, Mean, SD, Max, Min")
	for test in os.listdir("Random_cases"):
		name = test.split("_")
		if(name[1] == max_length) break;

		f = open("Random_cases/" + test, "r")
		out = s.check_output(["./tiempos", repetition, exercise], stdin=f, shell=True)

def timing(what_to_test):
 	if len(os.listdir("Tests_para_tiempos")) == 0:
 		generate_random_samples()

 	if(what_to_test == "b" or what_to_test == "a"):
 		print("Running backtracking iterations")
 		print("===============================")
 		test_timing("b", 20, 60)

 	if(what_to_test == "bb" or what_to_test == "a"):
 		print("Running backtracking with bound iterations")
 		print("==========================================")
 		test_timing("bb", 20, 60)

 	if(what_to_test == "d" or what_to_test == "a"):
 		print("Running dynamic algorithm iterations")
 		print("====================================")
 		test_timing("d", 20, 200)

if __name__ == "__main__":
	print(sys.argv)
	if len(sys.argv)  == 1 or sys.argv[1] == "help":
		print("You must provide two or more parameters: \n")
		print("\t test -To test algorithms")
		print("\t\t  a (default) - test the three algorithms")
		print("\t\t  b 			 - test only Backtracking")
		print("\t\t  bb 		 - test only Backtracking with Bounds")
		print("\t\t  d 			 - test only dynamic algorithm")
		print("\t tim - To take execution times:")	
		print("\t\t  a (default) - of every algorithm")
		print("\t\t  b 			 - of the Backtracking algorithm")
		print("\t\t  bb 		 - of the Backtracking with Bounds algorithm")
		print("\t\t  d 			 - of the dynamic algorithm")
		print("\t gen - Generate random cases of sequences up to 200 elements")
	elif sys.argv[1] == "cor":
		if len(sys.argv) == 3:
			correctitud(sys.argv[2])
		else:
			correctitud("a")
	elif sys.argv[1] == "tim":
		if len(sys.argv) == 3:
			timing(sys.argv[2])
		else:
			timing("a")
	elif sys.argv[1] == "gen":
			generate_random_samples(200)