import os, sys, subprocess, json

bigTests = ["t20", "t16", "t17", "t15", "t4", "t18", "t19"]

def correctitud():
	backtrackingValues = {}
	bboundValues = {}
	dynamicValues = {}

	for test in os.listdir("Tests"):
		t = open("Tests/" + test, "r")
		if (not (test in bigTests)):
			out = subprocess.check_output(["./Ej1"], stdin=t, shell=True)
			backtrackingValues[test] = int(out);

			out = subprocess.check_output(["./Ej2"], stdin=t, shell=True)
			bboundValues[test] = int(out);

		#out = subprocess.check_output(["./Ej3"], stdin=t, shell=True)
		#dynamicValues[test] = int(out);

	realSolutions = json.load("soluciones_tests")


def testAlgorithms():
	correctitud()


if __name__ == "__main__":
	
	if len(sys.argv)  == 1:
		print("Debe suministra uno o mas parametros: \n")
		print("\t cor - Para testear correctitud")
		print("\t tim - Para testear tiempos")	
	elif sys.argv[1] == "cor":
		correctitud()
#	else:
#		testearTiempos()