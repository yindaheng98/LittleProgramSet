from MMnSimulator import MMnSimulator
from nMM1Simulator import nMM1Simulator

MMn = MMnSimulator(3., 5., 3)
nMM1 = nMM1Simulator(3., 5., 3)
print("Elq=%f" % MMn.run(30000))
print("Elq=%f" % MMn.theory())
print("Elq=%f" % nMM1.run(30000))
print("Elq=%f" % nMM1.theory())
