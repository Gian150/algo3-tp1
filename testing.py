import os, sys, subprocess, json

bigTests = ["t20", "t16", "t17", "t15", "t4", "t18", "t19"]

def testCorrectitud(executable, solutions):
	for test in os.listdir("Tests"):
		t = open("Tests/" + test, "r")
		
		if (executable == "./Ej1" or executable == "./Ej2") and (test in bigTests):
			print(test + "... es demasiado grande para esta aplicación")
		else:
			print(test + "....", end="")
			out = subprocess.check_output([executable], stdin=t, shell=True)
			if(int(out) == solutions[test]):
				print("OK", flush=True)
			else:
				print("ERROR: E:" + str(int(out))+ ", R: " + str(solutions[test]), flush=True)

		t.close()

def correctitud(whatToTest):
	realSolutions = json.load(open("soluciones_tests"))

	if(whatToTest == "b" or whatToTest == "a"):
		print("Checking Backtracking")
		print("=================================")
		testCorrectitud("./Ej1", realSolutions)

	if(whatToTest == "bb" or whatToTest == "a"):
		print("Checking Backtracking with bounds")
		print("=================================")
		testCorrectitud("./Ej2", realSolutions)
	
	if(whatToTest == "d" or whatToTest == "a"):
		print("Checking dynamic algorithm")
		print("=================================")
		testCorrectitud("./Ej3", realSolutions)

def testAlgorithms():
	correctitud()


if __name__ == "__main__":
	
	if len(sys.argv)  == 1:
		print("Debe suministra uno o mas parametros: \n")
		print("\t cor - Para testear correctitud")
		print("\t\t  a (default) - de los 3 algoritmos")
		print("\t\t  b 			 - del Backtracking")
		print("\t\t  bb 		 - del Backtracking con podas")
		print("\t\t  d 			 - del de programación Dinamica")
		print("\t tim - Para testear tiempos")	
	elif sys.argv[1] == "cor":
		if len(sys.argv) == 3:
			correctitud(sys.argv[2])
		else:
			correctitud("a")
#	else:
#		testearTiempos()