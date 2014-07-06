import matplotlib.pyplot as pp
from sys import *

with open(argv[1]) as f:
    content = f.readlines();

pp.plot(content)
pp.ylabel("Temperature (degrees C)")
pp.xlabel("Reading cardinality");

#pp.savefig("/home/dragostea/Dev/Robotics/UnderwaterSensor/graph.png", bbox_inches="tight")
pp.show()

exit(0)
