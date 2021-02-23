from MMnSimulator import MMnSimulator
from nMM1Simulator import nMM1Simulator
from nEnM1Simulator import nEnM1Simulator
'''
MMn = MMnSimulator(3., 5., 3)
print("Elq=%f" % MMn.run(30000))
print("Elq=%f" % MMn.Elq_theory)
nMM1 = nMM1Simulator(3., 5., 3)
print("Elq=%f" % nMM1.run(30000))
print("Elq=%f" % nMM1.Elq_theory)
'''
nEnM1 = nEnM1Simulator(3., 5., 3)
print("Elq=%f" % nEnM1.run(30000))
print("Elq=%f" % nEnM1.Elq_theory)
