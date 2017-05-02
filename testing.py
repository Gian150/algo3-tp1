from subprocess import Popen, PIPE, STDOUT
import os, sys
import subprocess as s
import json
import random as r

big_test = ["t20", "t16", "t17", "t15", "t4", "t18", "t19"]

def test_correctitud(executable, solutions):
	for test in os.listdir("tests"):
		t = open("tests/" + test, "r")
		
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


def generate_random_sample(length, sequenceType):
	f = open("random_sample", "w")
	f.write(str(length) + "\n")

	sample = r.sample(range(-150,150), length)

	if sequenceType == "crecent":
		sample.sort()
	elif sequenceType == "decrecent": 
		sample.sort(reverse=True)
	elif sequenceType == "same":
		sample = [r.randrange(-150,150)]*length;
	for e in sample:
		f.write(str(e) + " ")
	
	f.close()

def timing(algorithm, sample_type, max_length):
	print("Measuring algorithms execution time for random sequences")
	print("========================================================")
	csvData = open("experiment_" + sample_type + "_" + algorithm + "_data", "w")
	csvData.write("Length,Number, Mean\n")
	for l in range(1, max_length):
		for r in range(0,20):
			generate_random_sample(l, "random")
			print("sample_" + str(l) + "_" + str(r) + " measuring ... ", end="")		
			
			sample = open("random_sample", "r")
			out = s.check_output(["./tiempos 20 decode"], stdin=sample, shell=True)
			# if l < 44:
			# 	sample.seek(0)
			# 	outB = s.check_output(["./tiempos 20 bb "], stdin=sample, shell=True)

			# 	sample.seek(0)
			# 	outBB = s.check_output(["./tiempos 20 b "], stdin=sample, shell=True)
			
			sample.close()
			csvData.write(str(l) +","+ str(r) + "," + out.decode() + "\n")
			print("done", flush=True)
	csvData.close()

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
			#timing("d", "random", 200)
			#timing("d", "crecent", 200)
			#timing("d", "decrecent", 200)
			#timing("d", "same", 200)
			timing("b", "random",40)
			timing("b", "crecent",40)
			timing("b", "decrecent",40)
			timing("b", "same",40)
			#timing("bb", "random",40)
			#timing("bb", "crecent",40)
			#timing("bb", "decrecent",40)
			#timing("bb", "same",40)

	elif sys.argv[1] == "tim2":
		timing_up_to_200()