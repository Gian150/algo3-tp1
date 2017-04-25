import os, sys
import subprocess as s
import json
import random as r
from ipywidgets import IntProgress, HTML, VBox
from IPython.display import display

def log_progress(sequence, every=None, size=None):

    is_iterator = False
    if size is None:
        try:
            size = len(sequence)
        except TypeError:
            is_iterator = True
    if size is not None:
        if every is None:
            if size <= 200:
                every = 1
            else:
                every = int(size / 200)     # every 0.5%
    else:
        assert every is not None, 'sequence is iterator, set every'

    if is_iterator:
        progress = IntProgress(min=0, max=1, value=1)
        progress.bar_style = 'info'
    else:
        progress = IntProgress(min=0, max=size, value=0)
    label = HTML()
    box = VBox(children=[label, progress])
    display(box)

    index = 0
    try:
        for index, record in enumerate(sequence, 1):
            if index == 1 or index % every == 0:
                if is_iterator:
                    label.value = '{index} / ?'.format(index=index)
                else:
                    progress.value = index
                    label.value = u'{index} / {size}'.format(
                        index=index,
                        size=size
                    )
            yield record
    except:
        progress.bar_style = 'danger'
        raise
    else:
        progress.bar_style = 'success'
        progress.value = index
        label.value = str(index or '?')


bigTests = ["t20", "t16", "t17", "t15", "t4", "t18", "t19"]

def testCorrectitud(executable, solutions):
	for test in os.listdir("Tests_para_correctitud"):
		t = open("Tests/" + test, "r")
		
		if (executable == "./Ej1" or executable == "./Ej2") and (test in bigTests):
			print(test + "... es demasiado grande para esta aplicación")
		else:
			print(test + "....", end="")
			out = s.check_output([executable], stdin=t, shell=True)
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
		progressrint("=================================")
		testCorrectitud("./Ej3", realSolutions)


def generateRandomSamples():
	for n in range(1, 200):
		for repetition in log_progress(range(0, 20)):
			f = open("Tests_para_tiempos/Test_" + str(n) + "_" + str(repetition), "w")
			f.write(str(n) + "\n")
			for i in range(0, n):
				f.write(str(r.randrange(-150,150)) + " ")
			f.close()

def timing(whatToTest):
	if len(os.listdir("Tests_para_tiempos")) == 0:
		print("Creating tests files")
		generateRandomSamples()
	print("Test files generated")

#	if(whatToTest == "b" or whatToTest == "a")
#		print("Running backtracking iterations")
#		print("===============================")

if __name__ == "__main__":
	
	if len(sys.argv)  == 1:
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
		
	elif sys.argv[1] == "test":
		if len(sys.argv) == 3:
			correctitud(sys.argv[2])
		else:
			correctitud("a")
	elif sys.argv[1] == "tim":
		if len(sys.argv) == 3:
			timing(sys.argv[2])
		else:
			timing("a")