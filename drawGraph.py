import matplotlib.pyplot as plt


f = open('../file.txt')
w = f.read().replace("\n", " ").split(" ")
f.close()

w.pop(len(w)-1)
plt.plot(w)
plt.ylabel("smt")
plt.show()