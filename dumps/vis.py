import matplotlib.pyplot as plt
import matplotlib.ticker as mtick
from sys import argv as args

for i in args[1:]:
    handle = open(i, "r")
    
    dev1 = []
    dev2 = []

    for date in handle:
        dev1.append(int(date.split(" ")[0]))
        dev2.append(int(date.split(" ")[1]))

    max1 = max(dev1)
    for j in range(len(dev1)):
        dev1[j] /= max1 * 0.01

    max2 = max(dev2)
    for j in range(len(dev2)):
        dev2[j] /= max2 * 0.01

    plt.ylabel("Common rate")
    plt.xlabel("Epoch")
    plt.title(i)

    plt.gca().yaxis.set_major_formatter(mtick.PercentFormatter())
    plt.plot([i for i in range(len(dev1))], dev1, 'b', label = "Success rate")
    plt.plot([i for i in range(len(dev2))], dev2, 'g', label = "Death rate", linestyle = ":")
    plt.legend()
    plt.show()
