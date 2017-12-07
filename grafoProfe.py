import numpy as np
np.random.seed(0)
# points = np.array([[0, 0], [0, 1.1], [1, 0], [1, 1]])
tamGrafo=100000
points = np.random.random((tamGrafo, 2))

from scipy.spatial import Delaunay
tri = Delaunay(points)


import matplotlib.pyplot as plt
from matplotlib import collections  as mc
import pylab as pl
from scipy.spatial import distance

rects = [
  [(0.4, 0.4), (0.6, 0.5)], 
  [(0.1, 0.1), (0.9, 0.15)],
  [(0.2, 0.7), (0.3, 0.8)],
  [(0.7, 0.7), (0.8, 0.8)]
#   [(0.2, 0.4), (0.6, 0.8)],
]

def inside(p, r):
  return r[0][0] <= p[0] <= r[1][0] and r[0][1] <= p[1] <= r[1][1]

def remove_edge(p1, p2, rects):
  remove = False
  for r in rects:
    if inside(p1, r) and inside(p2, r):
      remove = True

  return remove


edges = set()
for a, b, c in tri.simplices:
  p1, p2, p3 = points[a], points[b], points[c]

  if not remove_edge(p1, p2, rects):
    edges.add((a, b, distance.euclidean(p1, p2)))
    edges.add((b, a, distance.euclidean(p1, p2))) # podrian eliminar este si lo hacen no direccionado 

  if not remove_edge(p2, p3, rects):
    edges.add((b, c, distance.euclidean(p2, p3)))
    edges.add((c, b, distance.euclidean(p2, p3))) # podrian eliminar este si lo hacen no direccionado 

  if not remove_edge(p3, p1, rects):
    edges.add((c, a, distance.euclidean(p3, p1)))
    edges.add((a, c, distance.euclidean(p3, p1))) # podrian eliminar este si lo hacen no direccionado 



# plt.triplot(points[:,0], points[:,1], tri.simplices.copy())
# plt.plot(points[:,0], points[:,1], 'o')

# dibujar el grafo
lines = []
for e in edges: 
  lines.append([points[e[0]], points[e[1]]])
  
lc = mc.LineCollection(lines, linewidths=1)
fig, ax = pl.subplots()
ax.add_collection(lc)
ax.autoscale()
ax.margins(0.1)

# dibujar los vertices del path
 #path = [543, 471, 988, 687, 165, 843] # vertices del nodo
#path = [1, 0, 11, 13]

##### DIJKSTRA 
path = [39355, 27286, 90995, 8155, 18457, 52818, 39713, 97729, 46586, 18596, 60925, 63437, 42630, 61012, 9711, 22255, 73610, 22380, 8814, 88896, 83367, 24810, 68941, 11010, 65127, 29717, 27988, 12692, 2442, 19093, 45332, 87977, 99034, 98765, 31363, 82143, 28793, 24122, 63240, 40451, 63927, 16456, 37218, 91479, 45093, 43362, 51007, 49780, 48894, 41355, 76859, 53488, 80763, 63945, 91536, 54391, 90258, 28433, 18868, 78867, 34436, 63094, 56466, 71774, 23870, 64942, 26672, 65060, 90385, 78731, 88563, 37127, 57757, 56020, 35880, 41724, 97444, 71382, 43658, 71843, 86332, 44741, 83466, 48677, 12354, 50729, 18252, 25942, 51764, 21587, 52659, 31699, 81360, 32472, 47157, 83522, 54067, 95009, 36407, 84413, 67770, 79257, 5747, 14986, 17095, 95836, 64719, 64402, 13899, 98003, 83667, 26880, 89766, 66663, 28127, 77065, 26724, 96213, 24176, 78876, 12964, 44477, 70037, 58337, 82722, 52073, 26489, 89631, 35393, 26739, 54607, 38775, 8614, 67623, 31720, 72181, 28405, 86177, 99268, 51652, 811, 66960, 50066, 90214, 28125, 73812, 73466, 22112, 83652, 6267, 67134, 33392, 37653, 80010, 53494, 63872, 35021, 74488, 36520, 51174, 85937, 77661, 8124, 3838, 23692, 55815, 72960, 32933, 68550, 60732, 1500, 61612, 80626, 47361, 96736, 59815, 66059, 89312, 65407, 70772, 14978, 28226, 4885, 8049, 25262, 58925, 9999, 35749, 37501, 39816, 80610, 92876, 14861, 37754, 45866, 70142, 46015, 7426]
pps = points[path,:]
plt.plot(pps[:,0], pps[:,1], 'red')

##### A Star
path=[39355, 27286, 85410, 86607, 19113, 62725, 31586, 66738, 73555, 46153, 36707, 91697, 34069, 99354, 91117, 71686, 41454, 54835, 78816, 43107, 57122, 26526, 91194, 13062, 36987, 91244, 69419, 7625, 27549, 24342, 84813, 54499, 68411, 13408, 63610, 6336, 68663, 95336, 39268, 18004, 86133, 2606, 21485, 33524, 55212, 94120, 86102, 21918, 753, 95913, 25699, 625, 19451, 93213, 52968, 18872, 95634, 43456, 67818, 79091, 83971, 15913, 29024, 30978, 18948, 39170, 40075, 66623, 89975, 42473, 64718, 38973, 62608, 25973, 94934, 20030, 47926, 53359, 56778, 73230, 12332, 84483, 28841, 84181, 63602, 10818, 46382, 27849, 60780, 5335, 1770, 6183, 44153, 81384, 25448, 52655, 95384, 88872, 95855, 44235, 30282, 84009, 8767, 68578, 98922, 52635, 60726, 64300, 66217, 83687, 8632, 5050, 17191, 98144, 87547, 23048, 32129, 17166, 16175, 43123, 42409, 20441, 69246, 57903, 25774, 52731, 96652, 98741, 87164, 27811, 93882, 57265, 6028, 79198, 2842, 23987, 76255, 62464, 14900, 65920, 94104, 13268, 14322, 71176, 63248, 18297, 42900, 58752, 189, 24680, 86306, 38820, 79604, 21133, 45955, 91876, 78389, 58078, 76500, 24744, 43750, 38815, 17131, 17209, 756, 29152, 86498, 78355, 39933, 5536, 67248, 97943, 94791, 16228, 56736, 82755, 63611, 10824, 30400, 14289, 27570, 78770, 2678, 18144, 61445, 92876, 14861, 37754, 45866, 70142, 46015, 7426]
pps = points[path,:]
plt.plot(pps[:,0], pps[:,1], 'green')

plt.show()

 

#  create text file
f = open("grafo"+str(tamGrafo)+".txt",'w')
print len(points), len(edges)
print >>f,len(points), len(edges)
# print vertices
for p in points:
  #print p[0], p[1]
  print >>f,p[0], p[1]

# print aristas
for e in edges:
  #print e[0], e[1], e[2]
  print >>f,e[0], e[1], e[2]
