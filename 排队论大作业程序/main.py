from MMnSimulator import MMnSimulator

MMn = MMnSimulator(3., 5., 3)
print("Elq=%f" % MMn.run(30000))
print("Elq=%f" % MMn.theory())
