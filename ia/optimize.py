import os
import time

# w = [69 for i in range(10)]
pw = "w.txt"
pr = "../archive/tournois/configuration.txt"

def write_table(pathw, weights):
	with open(pathw, 'w') as file:
		file.write(" ".join([str(i) for i in weights]))

def read_score(pathr):
	with open(pathr, 'r') as file:
		f=file.readlines()
	return int(f[0].split(" ")[1].lstrip())

#average

def play_ai():
	os.system("cd ../archive/tournois/ && ./tournois_simulation & cd ../ia && ./2048_IA".format(pr))

a = 0
scores =[]
for i in range(2):
	for j in range(2):
		for k in range(2):
			for l in range(2):
				for m in range(2):
					for n in range(2):
						for o in range(2):
							for p in range(2):
								for q in range(1):
									for r in range(1):
										write_table(pw,[i,j,k,l,m,n,o,p,q,r])
										play_ai()
										print("game:{}\n".format(a))
										a+=1
										scores.append(read_score(pr))
										print(read_score(pr))

print(scores)